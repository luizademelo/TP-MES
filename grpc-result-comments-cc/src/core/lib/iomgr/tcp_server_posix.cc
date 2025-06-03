Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/slice_buffer.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>

#include <utility>

// FIXME: "posix" files shouldn't be depending on _GNU_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP_SERVER

#include <errno.h>
#include <fcntl.h>
#include <grpc/byte_buffer.h>
#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/event_engine/memory_allocator_factory.h"
#include "src/core/lib/event_engine/posix_engine/posix_endpoint.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/event_engine_shims/closure.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/lib/iomgr/systemd_utils.h"
#include "src/core/lib/iomgr/tcp_posix.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/tcp_server_utils_posix.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/iomgr/vsock.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/strerror.h"

// Global counter for dropped connections due to high memory pressure
static std::atomic<int64_t> num_dropped_connections{0};
// Time to wait before retrying accept when file descriptor limit is reached
static constexpr grpc_core::Duration kRetryAcceptWaitTime{
    grpc_core::Duration::Seconds(1)};

// Event Engine related type aliases
using ::grpc_event_engine::experimental::EndpointConfig;
using ::grpc_event_engine::experimental::EventEngine;
using ::grpc_event_engine::experimental::MemoryAllocator;
using ::grpc_event_engine::experimental::MemoryQuotaBasedMemoryAllocatorFactory;
using ::grpc_event_engine::experimental::PosixEventEngineWithFdSupport;
using ::grpc_event_engine::experimental::SliceBuffer;

// Finishes server shutdown by cleaning up resources and invoking shutdown callback
static void finish_shutdown(grpc_tcp_server* s) {
  gpr_mu_lock(&s->mu);
  CHECK(s->shutdown);
  gpr_mu_unlock(&s->mu);
  if (s->shutdown_complete != nullptr) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, s->shutdown_complete,
                            absl::OkStatus());
  }
  gpr_mu_destroy(&s->mu);
  // Free all listener structures
  while (s->head) {
    grpc_tcp_listener* sp = s->head;
    s->head = sp->next;
    gpr_free(sp);
  }
  delete s->fd_handler;
  delete s;
}

// Creates an EventEngine listener for the TCP server
static grpc_error_handle CreateEventEngineListener(
    grpc_tcp_server* s, grpc_closure* shutdown_complete,
    const EndpointConfig& config, grpc_tcp_server** server) {
  absl::StatusOr<std::unique_ptr<EventEngine::Listener>> listener;
  auto* engine = reinterpret_cast<EventEngine*>(
      config.GetVoidPointer(GRPC_INTERNAL_ARG_EVENT_ENGINE));

  std::shared_ptr<EventEngine> keeper;
  if (engine == nullptr) {
    keeper = grpc_event_engine::experimental::GetDefaultEventEngine();
    engine = keeper.get();
  }
  
  // Check if the EventEngine supports file descriptors
  auto* event_engine_supports_fd =
      grpc_event_engine::experimental::QueryExtension<
          grpc_event_engine::experimental::EventEngineSupportsFdExtension>(
          engine);
  
  if (event_engine_supports_fd != nullptr) {
    // Callback for accepting new connections with FD support
    PosixEventEngineWithFdSupport::PosixAcceptCallback accept_cb =
        [s](int listener_fd, std::unique_ptr<EventEngine::Endpoint> ep,
            bool is_external, MemoryAllocator ,
            SliceBuffer* pending_data) {
          grpc_core::ExecCtx exec_ctx;
          grpc_pollset* read_notifier_pollset;
          grpc_tcp_server_acceptor* acceptor;
          void* cb_arg;

          {
            grpc_core::MutexLockForGprMu lock(&s->mu);
            if (s->shutdown) {
              return;
            }
            cb_arg = s->on_accept_cb_arg;
            acceptor = static_cast<grpc_tcp_server_acceptor*>(
                gpr_malloc(sizeof(*acceptor)));
            acceptor->from_server = s;
            acceptor->port_index = -1;
            acceptor->fd_index = -1;
            if (!is_external) {
              // Map listener FD to port and FD indices
              auto it = s->listen_fd_to_index_map.find(listener_fd);
              if (it != s->listen_fd_to_index_map.end()) {
                acceptor->port_index = std::get<0>(it->second);
                acceptor->fd_index = std::get<1>(it->second);
              }
            } else {
              // Handle external connection
              grpc_resolved_address addr;
              memset(&addr, 0, sizeof(addr));
              addr.len =
                  static_cast<socklen_t>(sizeof(struct sockaddr_storage));

              int fd =
                  reinterpret_cast<
                      grpc_event_engine::experimental::PosixEndpoint*>(ep.get())
                      ->GetWrappedFd();
              if (getpeername(fd, reinterpret_cast<struct sockaddr*>(addr.addr),
                              &(addr.len)) < 0) {
                LOG(ERROR) << "Failed getpeername: "
                           << grpc_core::StrError(errno);
                close(fd);
                return;
              }
              (void)grpc_set_socket_no_sigpipe_if_possible(fd);
              auto addr_uri = grpc_sockaddr_to_uri(&addr);
              if (!addr_uri.ok()) {
                LOG(ERROR) << "Invalid address: "
                           << addr_uri.status().ToString();
                return;
              }
              GRPC_TRACE_LOG(tcp, INFO) << "SERVER_CONNECT: incoming external "
                                           "connection: "
                                        << addr_uri->c_str();
            }
            // Assign a pollset for this connection in round-robin fashion
            read_notifier_pollset =
                (*(s->pollsets))[static_cast<size_t>(
                                     gpr_atm_no_barrier_fetch_add(
                                         &s->next_pollset_to_assign, 1)) %
                                 s->pollsets->size()];
            acceptor->external_connection = is_external;
            acceptor->listener_fd = listener_fd;
            grpc_byte_buffer* buf = nullptr;
            if (pending_data != nullptr && pending_data->Length() > 0) {
              buf = grpc_raw_byte_buffer_create(nullptr, 0);
              grpc_slice_buffer_swap(&buf->data.raw.slice_buffer,
                                     pending_data->c_slice_buffer());
              pending_data->Clear();
            }
            acceptor->pending_data = buf;
          }
          // Invoke the accept callback with the new connection
          s->on_accept_cb(cb_arg,
                          grpc_event_engine::experimental::
                              grpc_event_engine_endpoint_create(std::move(ep)),
                          read_notifier_pollset, acceptor);
        };
    // Create listener with FD support
    listener = event_engine_supports_fd->CreatePosixListener(
        std::move(accept_cb),
        [s, shutdown_complete](absl::Status status) {
          grpc_event_engine::experimental::RunEventEngineClosure(
              shutdown_complete, absl_status_to_grpc_error(status));
          finish_shutdown(s);
        },
        config,
        std::make_unique<MemoryQuotaBasedMemoryAllocatorFactory>(
            s->memory_quota));
  } else {
    // Callback for accepting new connections without FD support
    EventEngine::Listener::AcceptCallback accept_cb =
        [s](std::unique_ptr<EventEngine::Endpoint> ep, MemoryAllocator) {
          grpc_core::ExecCtx exec_ctx;
          void* cb_arg;
          {
            grpc_core::MutexLockForGprMu lock(&s->mu);
            if (s->shutdown) {
              return;
            }
            cb_arg = s->on_accept_cb_arg;
          }
          s->on_accept_cb(cb_arg,
                          grpc_event_engine::experimental::
                              grpc_event_engine_endpoint_create(std::move(ep)),
                          nullptr, nullptr);
        };
    // Create listener without FD support
    listener = engine->CreateListener(
        std::move(accept_cb),
        [s, ee = keeper, shutdown_complete](absl::Status status) {
          CHECK_EQ(gpr_atm_no_barrier_load(&s->refs.count), 0);
          grpc_event_engine::experimental::RunEventEngineClosure(
              shutdown_complete, absl_status_to_grpc_error(status));
          finish_shutdown(s);
        },
        config,
        std::make_unique<MemoryQuotaBasedMemoryAllocatorFactory>(
            s->memory_quota));
  }
  if (!listener.ok()) {
    delete s;
    *server = nullptr;
    return listener.status();
  }
  s->ee_listener = std::move(*listener);
  return absl::OkStatus();
}

// Creates a new TCP server instance
static grpc_error_handle tcp_server_create(grpc_closure* shutdown_complete,
                                           const EndpointConfig& config,
                                           grpc_tcp_server_cb on_accept_cb,
                                           void* on_accept_cb_arg,
                                           grpc_tcp_server** server) {
  grpc_tcp_server* s = new grpc_tcp_server;
  // Initialize server properties from config
  s->so_reuseport = grpc_is_socket_reuse_port_supported();
  s->expand_wildcard_addrs = false;
  auto value = config.GetInt(GRPC_ARG_ALLOW_REUSEPORT);
  if (value.has_value()) {
    s->so_reuseport = (grpc_is_socket_reuse_port_supported() && *value != 0);
  }
  value = config.GetInt(GRPC_ARG_EXPAND_WILDCARD_ADDRS);
  if (value.has_value()) {
    s->expand_wildcard_addrs = (*value != 0);
  }
  // Initialize reference count and mutex
  gpr_ref_init(&s->refs, 1);
  gpr_mu_init(&s->mu);
  // Initialize server state
  s->active_ports = 0;
  s->destroyed_ports = 0;
  s->shutdown = false;
  s->shutdown_starting.head = nullptr;
  s->shutdown_starting.tail = nullptr;
  if (!grpc_event_engine::experimental::UseEventEngineListener()) {
    s->shutdown_complete = shutdown_complete;
  } else {
    s->shutdown_complete = nullptr;
  }
  s->on_accept_cb = on_accept_cb;
  s->on_accept_cb_arg = on_accept_cb_arg;
  s->head = nullptr;
  s->tail = nullptr;
  s->nports = 0;
  s->options = ::TcpOptionsFromEndpointConfig(config);
  s->fd_handler = nullptr;
  CHECK(s->options.resource_quota != nullptr);
  CHECK(s->on_accept_cb);
  s->memory_quota = s->options.resource_quota->memory_quota();
  s->pre_allocated_fd = -1;
  gpr_atm_no_barrier_store(&s->next_pollset_to_assign, 0);
  s->n_bind_ports = 0;
  new (&s->listen_fd_to_index_map)
      absl::flat_hash_map<int, std::tuple<int, int>>();
  *server = s;
  // Create EventEngine listener if enabled
  if (grpc_event_engine::experimental::UseEventEngineListener()) {
    return CreateEventEngineListener(s, shutdown_complete, config, server);
  }
  return absl::OkStatus();
}

// Callback when a port is destroyed
static void destroyed_port(void* server, grpc_error_handle ) {
  grpc_tcp_server* s = static_cast<grpc_tcp_server*>(server);
  gpr_mu_lock(&s->mu);
  s->destroyed_ports++;
  // If all ports are destroyed, finish shutdown
  if (s->destroyed_ports == s->nports) {
    gpr_mu_unlock(&s->mu);
    finish_shutdown(s);
  } else {
    CHECK(s->destroyed_ports < s->nports);
    gpr_mu_unlock(&s->mu);
  }
}

// Deactivates all ports and cleans up resources
static void deactivated_all_ports(grpc_tcp_server* s) {
  gpr_mu_lock(&s->mu);
  CHECK(s->shutdown);

  if (s->head) {
    grpc_tcp_listener* sp;
    // Clean up all listeners
    for (sp = s->head; sp; sp = sp->next) {
      if (grpc_tcp_server_pre_allocated_fd(s) <= 0) {
        grpc_unlink_if_unix_domain_socket(&sp->addr);
      }
      GRPC_CLOSURE_INIT(&sp->destroyed_closure, destroyed_port, s,
                        grpc_schedule_on_exec_ctx);
      grpc_fd_orphan(sp->emfd, &sp->destroyed_closure, nullptr,
                     "tcp_listener_shutdown");
    }
    gpr_mu_unlock(&s->mu);
  } else {
    gpr_mu_unlock(&s->mu);
    if (grpc_event_engine::experimental::UseEventEngineListener()) {
      // Reset EventEngine listener
      s->ee_listener.reset();
    } else {
      finish_shutdown(s);
    }
  }
}

// Initiates server destruction
static void tcp_server_destroy(grpc_tcp_server* s) {
  gpr_mu_lock(&s->mu);
  CHECK(!s->shutdown);
  s->shutdown = true;

  if (s->active_ports) {
    // Shutdown all active ports
    grpc_tcp_listener* sp;
    for (sp = s->head; sp; sp = sp->next) {
      grpc_fd_shutdown(sp->emfd, GRPC_ERROR_CREATE("Server destroyed"));
    }
    gpr_mu_unlock(&s->mu);
  } else {
    gpr_mu_unlock(&s->mu);
    deactivated_all_ports(s);
  }
}

// Callback for read events on listener sockets
static void on_read(void* arg, grpc_error_handle err) {
  grpc_tcp_listener* sp = static_cast<grpc_tcp_listener*>(arg);
  grpc_pollset* read_notifier_pollset;
  if (!err.ok()) {
    goto error;
  }

  // Continuous accept loop
  for (;;) {
    grpc_resolved_address addr;
    memset(&addr, 0, sizeof(addr));
    addr.len = static_cast<socklen_t>(sizeof(struct sockaddr_storage));
    // Note: If we ever decide to return this address to the user, remember to

    // Accept new connection
    int fd = grpc_accept4(sp->fd, &addr, 1, 1);
    if (fd < 0) {
      if (errno == EINTR) {
        continue;
      }

      if (errno == EMFILE) {
        // Handle file descriptor limit reached
        LOG_EVERY_N_SEC(ERROR, 1) << "File descriptor limit reached. Retrying.";
        grpc_fd_notify_on_read(sp->emfd, &sp->read_closure);
        if (gpr_atm_full_xchg(&sp->retry_timer_armed, true)) return;
        grpc_timer_init(&sp->retry_timer,
                        grpc_core::Timestamp::Now() + kRetryAcceptWaitTime,
                        &sp->retry_closure);
        return;
      }
      if (errno == EAGAIN || errno == ECONNABORTED || errno == EWOULDBLOCK) {
        grpc_fd_notify_on_read(sp->emfd, &sp->read_closure);
        return;
      }
      gpr_mu_lock(&sp->server->mu);
      if (!sp->server->shutdown_listeners) {
        LOG(ERROR) << "Failed accept4: " << grpc_core::StrError(errno);
      } else {
        // Silent error during