Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific includes and configuration
#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// Only compile this file for POSIX systems with TCP client support
#ifdef GRPC_POSIX_SOCKET_TCP_CLIENT

// Standard C includes
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

// Memory management
#include <memory>

// gRPC includes
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>

// Abseil includes
#include "absl/container/flat_hash_map.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

// gRPC internal includes
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/event_engine_shims/tcp_client.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/tcp_client_posix.h"
#include "src/core/lib/iomgr/tcp_posix.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/iomgr/vsock.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/string.h"

using ::grpc_event_engine::experimental::EndpointConfig;

// Structure to track asynchronous TCP connection state
struct async_connect {
  gpr_mu mu;  // Mutex for thread safety
  grpc_fd* fd;  // File descriptor for the connection
  grpc_timer alarm;  // Timer for connection timeout
  grpc_closure on_alarm;  // Closure to call on timeout
  int refs;  // Reference count for cleanup
  grpc_closure write_closure;  // Closure for write events
  grpc_pollset_set* interested_parties;  // Parties interested in this connection
  std::string addr_str;  // String representation of the address
  grpc_endpoint** ep;  // Pointer to store the resulting endpoint
  grpc_closure* closure;  // User callback to invoke when done
  int64_t connection_handle;  // Unique ID for this connection
  bool connect_cancelled;  // Flag indicating if connection was cancelled
  grpc_core::PosixTcpOptions options;  // TCP connection options
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine;  // Event engine
};

// Shard structure for managing pending connections
struct ConnectionShard {
  grpc_core::Mutex mu;  // Mutex for thread safety
  // Map of pending connections by their handle
  absl::flat_hash_map<int64_t, async_connect*> pending_connections
      ABSL_GUARDED_BY(&mu);
};

namespace {

// Global initialization control
gpr_once g_tcp_client_posix_init = GPR_ONCE_INIT;
std::vector<ConnectionShard>* g_connection_shards = nullptr;
std::atomic<int64_t> g_connection_id{1};  // Atomic counter for connection IDs

// Initialize TCP client global state
void do_tcp_client_global_init(void) {
  // Create shards based on number of CPU cores (minimum 1)
  size_t num_shards = std::max(2 * gpr_cpu_num_cores(), 1u);
  g_connection_shards = new std::vector<struct ConnectionShard>(num_shards);
}

}  // namespace

// Public API to initialize TCP client
void grpc_tcp_client_global_init() {
  gpr_once_init(&g_tcp_client_posix_init, do_tcp_client_global_init);
}

// Prepares a socket with the given options
static grpc_error_handle prepare_socket(
    const grpc_resolved_address* addr, int fd,
    const grpc_core::PosixTcpOptions& options) {
  grpc_error_handle err;

  CHECK_GE(fd, 0);  // Ensure we have a valid file descriptor

  // Set socket to non-blocking mode
  err = grpc_set_socket_nonblocking(fd, 1);
  if (!err.ok()) goto error;
  // Set close-on-exec flag
  err = grpc_set_socket_cloexec(fd, 1);
  if (!err.ok()) goto error;
  // Set receive buffer size if specified
  if (options.tcp_receive_buffer_size != options.kReadBufferSizeUnset) {
    err = grpc_set_socket_rcvbuf(fd, options.tcp_receive_buffer_size);
    if (!err.ok()) goto error;
  }
  // Additional settings for non-Unix/non-VSock sockets
  if (!grpc_is_unix_socket(addr) && !grpc_is_vsock(addr)) {
    // Enable low latency mode
    err = grpc_set_socket_low_latency(fd, 1);
    if (!err.ok()) goto error;
    // Enable address reuse
    err = grpc_set_socket_reuse_addr(fd, 1);
    if (!err.ok()) goto error;
    // Set DSCP (Differentiated Services Code Point)
    err = grpc_set_socket_dscp(fd, options.dscp);
    if (!err.ok()) goto error;
    // Set TCP user timeout
    err = grpc_set_socket_tcp_user_timeout(fd, options, true);
    if (!err.ok()) goto error;
  }
  // Disable SIGPIPE if possible
  err = grpc_set_socket_no_sigpipe_if_possible(fd);
  if (!err.ok()) goto error;

  // Apply any additional socket mutators
  err = grpc_apply_socket_mutator_in_args(fd, GRPC_FD_CLIENT_CONNECTION_USAGE,
                                          options);
  if (!err.ok()) goto error;

  goto done;

error:
  // Clean up on error
  if (fd >= 0) {
    close(fd);
  }
done:
  return err;
}

// Callback for connection timeout
static void tc_on_alarm(void* acp, grpc_error_handle error) {
  int done;
  async_connect* ac = static_cast<async_connect*>(acp);
  GRPC_TRACE_LOG(tcp, INFO)
      << "CLIENT_CONNECT: " << ac->addr_str
      << ": on_alarm: error=" << grpc_core::StatusToString(error);
  gpr_mu_lock(&ac->mu);
  if (ac->fd != nullptr) {
    // Shutdown the connection if it's still pending
    grpc_fd_shutdown(ac->fd, GRPC_ERROR_CREATE("connect() timed out"));
  }
  done = (--ac->refs == 0);  // Check if we can clean up
  gpr_mu_unlock(&ac->mu);
  if (done) {
    // Clean up the async_connect structure
    gpr_mu_destroy(&ac->mu);
    delete ac;
  }
}

// Creates a TCP endpoint from a file descriptor
static grpc_endpoint* grpc_tcp_client_create_from_fd(
    grpc_fd* fd, const grpc_core::PosixTcpOptions& options,
    absl::string_view addr_str) {
  return grpc_tcp_create(fd, options, addr_str);
}

// Public API to create TCP endpoint from fd with EndpointConfig
grpc_endpoint* grpc_tcp_create_from_fd(
    grpc_fd* fd, const grpc_event_engine::experimental::EndpointConfig& config,
    absl::string_view addr_str) {
  return grpc_tcp_create(fd, config, addr_str);
}

// Callback when socket becomes writable (connection progress)
static void on_writable(void* acp, grpc_error_handle error) {
  async_connect* ac = static_cast<async_connect*>(acp);
  int so_error = 0;
  socklen_t so_error_size;
  int err;
  int done;
  grpc_endpoint** ep = ac->ep;
  grpc_closure* closure = ac->closure;
  std::string addr_str = ac->addr_str;
  grpc_fd* fd;

  GRPC_TRACE_LOG(tcp, INFO)
      << "CLIENT_CONNECT: " << ac->addr_str
      << ": on_writable: error=" << grpc_core::StatusToString(error);

  // Get the fd and check if connection was cancelled
  gpr_mu_lock(&ac->mu);
  CHECK(ac->fd);
  fd = ac->fd;
  ac->fd = nullptr;
  bool connect_cancelled = ac->connect_cancelled;
  gpr_mu_unlock(&ac->mu);

  // Cancel the timeout alarm
  grpc_timer_cancel(&ac->alarm);

  gpr_mu_lock(&ac->mu);
  if (!error.ok()) {
    error = grpc_core::AddMessagePrefix("Timeout occurred", error);
    goto finish;
  }

  if (connect_cancelled) {
    // Connection was cancelled, just clean up
    error = absl::OkStatus();
    goto finish;
  }

  // Check socket error status
  do {
    so_error_size = sizeof(so_error);
    err = getsockopt(grpc_fd_wrapped_fd(fd), SOL_SOCKET, SO_ERROR, &so_error,
                     &so_error_size);
  } while (err < 0 && errno == EINTR);
  if (err < 0) {
    error = GRPC_OS_ERROR(errno, "getsockopt");
    goto finish;
  }

  // Handle different socket error cases
  switch (so_error) {
    case 0:
      // Success - create endpoint
      grpc_pollset_set_del_fd(ac->interested_parties, fd);
      *ep = grpc_tcp_client_create_from_fd(fd, ac->options, ac->addr_str);
      fd = nullptr;
      break;
    case ENOBUFS:
      // Kernel out of buffers - retry
      LOG(ERROR) << "kernel out of buffers";
      gpr_mu_unlock(&ac->mu);
      grpc_fd_notify_on_write(fd, &ac->write_closure);
      return;
    case ECONNREFUSED:
      // Connection refused
      error = GRPC_OS_ERROR(so_error, "connect");
      break;
    default:
      // Other errors
      error = GRPC_OS_ERROR(so_error, "getsockopt(SO_ERROR)");
      break;
  }

finish:
  // Clean up connection from shard if not cancelled
  if (!connect_cancelled) {
    int shard_number = ac->connection_handle % (*g_connection_shards).size();
    struct ConnectionShard* shard = &(*g_connection_shards)[shard_number];
    {
      grpc_core::MutexLock lock(&shard->mu);
      shard->pending_connections.erase(ac->connection_handle);
    }
  }
  // Clean up file descriptor if still exists
  if (fd != nullptr) {
    grpc_pollset_set_del_fd(ac->interested_parties, fd);
    grpc_fd_orphan(fd, nullptr, nullptr, "tcp_client_orphan");
    fd = nullptr;
  }
  done = (--ac->refs == 0);  // Check if we can clean up
  gpr_mu_unlock(&ac->mu);
  if (!error.ok()) {
    error =
        grpc_core::AddMessagePrefix("Failed to connect to remote host", error);
  }
  auto engine = ac->engine;
  if (done) {
    // Final cleanup of async_connect structure
    gpr_mu_destroy(&ac->mu);
    delete ac;
  }

  // Invoke user callback if connection wasn't cancelled
  if (!connect_cancelled) {
    engine->Run([closure, error]() {
      grpc_core::ExecCtx exec_ctx;
      closure->cb(closure->cb_arg, error);
    });
  }
}

// Prepares a socket for TCP connection
grpc_error_handle grpc_tcp_client_prepare_fd(
    const grpc_core::PosixTcpOptions& options,
    const grpc_resolved_address* addr, grpc_resolved_address* mapped_addr,
    int* fd) {
  grpc_dualstack_mode dsmode;
  grpc_error_handle error;
  *fd = -1;

  // Convert to v4mapped address if needed
  if (!grpc_sockaddr_to_v4mapped(addr, mapped_addr)) {
    memcpy(mapped_addr, addr, sizeof(*mapped_addr));
  }
  // Create socket
  error =
      grpc_create_dualstack_socket(mapped_addr, SOCK_STREAM, 0, &dsmode, fd);
  if (!error.ok()) {
    return error;
  }
  // Handle IPv4-only case
  if (dsmode == GRPC_DSMODE_IPV4) {
    if (!grpc_sockaddr_is_v4mapped(addr, mapped_addr)) {
      memcpy(mapped_addr, addr, sizeof(*mapped_addr));
    }
  }
  // Prepare socket with options
  if ((error = prepare_socket(mapped_addr, *fd, options)) != absl::OkStatus()) {
    return error;
  }
  return absl::OkStatus();
}

// Creates TCP client from a prepared socket
int64_t grpc_tcp_client_create_from_prepared_fd(
    grpc_pollset_set* interested_parties, grpc_closure* closure, const int fd,
    const grpc_event_engine::experimental::EndpointConfig& config,
    const grpc_resolved_address* addr, grpc_core::Timestamp deadline,
    grpc_endpoint** ep) {
  int err;
  // Attempt connection
  do {
    err = connect(fd, reinterpret_cast<const grpc_sockaddr*>(addr->addr),
                  addr->len);
  } while (err < 0 && errno == EINTR);
  int connect_errno = (err < 0) ? errno : 0;

  // Convert address to URI
  auto addr_uri = grpc_sockaddr_to_uri(addr);
  if (!addr_uri.ok()) {
    grpc_error_handle error = GRPC_ERROR_CREATE(addr_uri.status().ToString());
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, error);
    return 0;
  }

  std::string name = absl::StrCat("tcp-client:", *addr_uri);
  grpc_fd* fdobj = grpc_fd_create(fd, name.c_str(), true);
  int64_t connection_id = 0;
  
  // If connection is in progress, get a new connection ID
  if (connect_errno == EWOULDBLOCK || connect_errno == EINPROGRESS) {
    connection_id = g_connection_id.fetch_add(1, std::memory_order_acq_rel);
  }

  // Handle immediate success case
  if (err >= 0) {
    *ep = grpc_tcp_create_from_fd(fdobj, config, *addr_uri);
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
    return 0;
  }
  // Handle immediate failure case
  if (connect_errno != EWOULDBLOCK && connect_errno != EINPROGRESS) {
    grpc_error_handle error = GRPC_OS_ERROR(connect_errno, "connect");
    grpc_fd_orphan(fdobj, nullptr, nullptr, "tcp_client_connect_error");
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, error);
    return 0;
  }

  // Connection is in progress - setup async tracking
  grpc_pollset_set_add_fd(interested_parties, fdobj);

  async_connect* ac = new async_connect();
  ac->closure = closure;
  ac->ep = ep;
  ac->fd = fdobj;
  ac->interested_parties = interested_parties;
  ac->addr_str = addr_uri.value();
  ac->connection_handle = connection_id;
  ac->connect_cancelled = false;
  ac->engine = grpc_event_engine::experimental::GetDefaultEventEngine();
  gpr_mu_init(&ac->mu);
  ac->refs = 2;  // One for timer, one for operation
  GRPC_CLOSURE_INIT(&ac->write_closure, on_writable, ac,
                    grpc_schedule_on_exec_ctx);
  ac->options = TcpOptionsFromEndpointConfig(config);

  GRPC_TRACE_LOG(tcp, INFO) << "CLIENT_CONNECT: " << ac->addr_str
                            << ": asynchronously connecting fd " << fdobj;

  // Add to connection shard
  int shard_number = connection_id % (*g_connection_shards).size();
  struct ConnectionShard* shard = &(*g_connection_shards)[shard_number];
  {
    grpc_core::MutexLock lock(&shard->mu);
    shard->pending_connections.insert_or_assign(connection_id, ac);
  }

  // Setup timeout and write notification
  gpr_mu_lock(&ac->mu);
  GRPC_CLOSURE_INIT(&ac->on_alarm, tc_on_alarm, ac, grpc_schedule_on_exec_ctx);
  grpc_timer_init(&ac->alarm, deadline, &ac->on_alarm);