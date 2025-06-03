Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET  // Windows-specific socket implementation

#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <limits.h>

// Various utility and core headers
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/tcp_windows.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "src/core/util/useful.h"

// Define FIONBIO command differently for MSYS64
#if defined(__MSYS__) && defined(GPR_ARCH_64)
#define GRPC_FIONBIO _IOW('f', 126, uint32_t)
#else
#define GRPC_FIONBIO FIONBIO
#endif

// Sets a socket to non-blocking mode
grpc_error_handle grpc_tcp_set_non_block(SOCKET sock) {
  int status;
  uint32_t param = 1;  // Enable non-blocking
  DWORD ret;
  status = WSAIoctl(sock, GRPC_FIONBIO, &param, sizeof(param), NULL, 0, &ret,
                    NULL, NULL);
  return status == 0
             ? absl::OkStatus()
             : GRPC_WSA_ERROR(WSAGetLastError(), "WSAIoctl(GRPC_FIONBIO)");
}

// Disables IPv6-only mode to allow dual-stack sockets (IPv4 and IPv6)
static grpc_error_handle set_dualstack(SOCKET sock) {
  int status;
  unsigned long param = 0;  // 0 = dualstack enabled
  status = setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (const char*)&param,
                      sizeof(param));
  return status == 0
             ? absl::OkStatus()
             : GRPC_WSA_ERROR(WSAGetLastError(), "setsockopt(IPV6_V6ONLY)");
}

// Enables TCP_NODELAY to disable Nagle's algorithm for lower latency
static grpc_error_handle enable_socket_low_latency(SOCKET sock) {
  int status;
  BOOL param = TRUE;  // Enable TCP_NODELAY
  status = ::setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
                        reinterpret_cast<char*>(&param), sizeof(param));
  if (status == SOCKET_ERROR) {
    status = WSAGetLastError();
  }
  return status == 0 ? absl::OkStatus()
                     : GRPC_WSA_ERROR(status, "setsockopt(TCP_NODELAY)");
}

// Prepares a socket by setting common options
grpc_error_handle grpc_tcp_prepare_socket(SOCKET sock) {
  grpc_error_handle err;
  // Set non-blocking mode
  err = grpc_tcp_set_non_block(sock);
  if (!err.ok()) return err;
  // Enable dual-stack
  err = set_dualstack(sock);
  if (!err.ok()) return err;
  // Enable low latency
  err = enable_socket_low_latency(sock);
  if (!err.ok()) return err;
  return absl::OkStatus();
}

// TCP endpoint structure for Windows
typedef struct grpc_tcp {
  grpc_endpoint base;  // Base endpoint structure
  
  grpc_winsocket* socket;  // Windows socket handle
  
  gpr_refcount refcount;  // Reference counting
  
  // I/O callbacks
  grpc_closure on_read;
  grpc_closure on_write;
  
  // Current callbacks
  grpc_closure* read_cb;
  grpc_closure* write_cb;
  
  // Buffer management
  grpc_slice_buffer last_read_buffer;
  grpc_slice_buffer* write_slices;
  grpc_slice_buffer* read_slices;
  
  // Synchronization
  gpr_mu mu;
  int shutting_down;  // Flag indicating shutdown state
  
  // Connection info
  std::string peer_string;
  std::string local_address;
} grpc_tcp;

// Frees TCP endpoint resources
static void tcp_free(grpc_tcp* tcp) {
  grpc_winsocket_destroy(tcp->socket);
  gpr_mu_destroy(&tcp->mu);
  grpc_slice_buffer_destroy(&tcp->last_read_buffer);
  delete tcp;
}

// Debug versions of ref/unref with tracing
#ifndef NDEBUG
#define TCP_UNREF(tcp, reason) tcp_unref((tcp), (reason), __FILE__, __LINE__)
#define TCP_REF(tcp, reason) tcp_ref((tcp), (reason), __FILE__, __LINE__)
static void tcp_unref(grpc_tcp* tcp, const char* reason, const char* file,
                      int line) {
  if (GRPC_TRACE_FLAG_ENABLED(tcp)) {
    gpr_atm val = gpr_atm_no_barrier_load(&tcp->refcount.count);
    VLOG(2).AtLocation(file, line) << "TCP unref " << tcp << " : " << reason
                                   << " " << val << " -> " << val - 1;
  }
  if (gpr_unref(&tcp->refcount)) {
    tcp_free(tcp);
  }
}

static void tcp_ref(grpc_tcp* tcp, const char* reason, const char* file,
                    int line) {
  if (GRPC_TRACE_FLAG_ENABLED(tcp)) {
    gpr_atm val = gpr_atm_no_barrier_load(&tcp->refcount.count);
    VLOG(2).AtLocation(file, line) << "TCP   ref " << tcp << " : " << reason
                                   << " " << val << " -> " << val + 1;
  }
  gpr_ref(&tcp->refcount);
}
#else
// Production versions of ref/unref without tracing
#define TCP_UNREF(tcp, reason) tcp_unref((tcp))
#define TCP_REF(tcp, reason) tcp_ref((tcp))
static void tcp_unref(grpc_tcp* tcp) {
  if (gpr_unref(&tcp->refcount)) {
    tcp_free(tcp);
  }
}

static void tcp_ref(grpc_tcp* tcp) { gpr_ref(&tcp->refcount); }
#endif

// Callback for completed read operations
static void on_read(void* tcpp, grpc_error_handle error) {
  grpc_tcp* tcp = (grpc_tcp*)tcpp;
  grpc_closure* cb = tcp->read_cb;
  grpc_winsocket* socket = tcp->socket;
  grpc_winsocket_callback_info* info = &socket->read_info;

  GRPC_TRACE_LOG(tcp, INFO) << "TCP:" << tcp << " on_read";

  if (error.ok()) {
    if (info->wsa_error != 0 && !tcp->shutting_down) {
      // Handle socket error
      error = GRPC_WSA_ERROR(info->wsa_error, "IOCP/Socket");
      grpc_slice_buffer_reset_and_unref(tcp->read_slices);
    } else {
      if (info->bytes_transferred != 0 && !tcp->shutting_down) {
        // Validate bytes transferred
        CHECK((size_t)info->bytes_transferred <= tcp->read_slices->length);
        if (static_cast<size_t>(info->bytes_transferred) !=
            tcp->read_slices->length) {
          // Trim unused buffer space
          grpc_slice_buffer_trim_end(
              tcp->read_slices,
              tcp->read_slices->length -
                  static_cast<size_t>(info->bytes_transferred),
              &tcp->last_read_buffer);
        }
        CHECK((size_t)info->bytes_transferred == tcp->read_slices->length);

        // Debug logging of received data
        if (GRPC_TRACE_FLAG_ENABLED(tcp) && ABSL_VLOG_IS_ON(2)) {
          size_t i;
          for (i = 0; i < tcp->read_slices->count; i++) {
            char* dump = grpc_dump_slice(tcp->read_slices->slices[i],
                                         GPR_DUMP_HEX | GPR_DUMP_ASCII);
            VLOG(2) << "READ " << tcp << " (peer=" << tcp->peer_string
                    << "): " << dump;
            gpr_free(dump);
          }
        }
      } else {
        // Handle end of stream or shutdown
        GRPC_TRACE_LOG(tcp, INFO) << "TCP:" << tcp << " unref read_slice";
        grpc_slice_buffer_reset_and_unref(tcp->read_slices);
        error = grpc_error_set_int(
            tcp->shutting_down ? GRPC_ERROR_CREATE("TCP stream shutting down")
                               : GRPC_ERROR_CREATE("End of TCP stream"),
            grpc_core::StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE);
      }
    }
  }

  // Clean up and invoke user callback
  tcp->read_cb = NULL;
  TCP_UNREF(tcp, "read");
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, cb, error);
}

// Constants for read operations
#define DEFAULT_TARGET_READ_SIZE 8192  // Default read buffer size
#define MAX_WSABUF_COUNT 16           // Maximum WSABUF structures per call

// Initiates a read operation on the endpoint
static void win_read(grpc_endpoint* ep, grpc_slice_buffer* read_slices,
                     grpc_closure* cb, bool /*urgent*/, int /*min_progress_size*/) {
  grpc_tcp* tcp = (grpc_tcp*)ep;
  grpc_winsocket* handle = tcp->socket;
  grpc_winsocket_callback_info* info = &handle->read_info;
  int status;
  DWORD bytes_read = 0;
  DWORD flags = 0;
  WSABUF buffers[MAX_WSABUF_COUNT];
  size_t i;

  GRPC_TRACE_LOG(tcp, INFO) << "TCP:" << tcp << " win_read";

  // Check for shutdown state
  if (tcp->shutting_down) {
    grpc_core::ExecCtx::Run(
        DEBUG_LOCATION, cb,
        grpc_error_set_int(GRPC_ERROR_CREATE("TCP socket is shutting down"),
                           grpc_core::StatusIntProperty::kRpcStatus,
                           GRPC_STATUS_UNAVAILABLE));
    return;
  }

  // Setup read operation
  tcp->read_cb = cb;
  tcp->read_slices = read_slices;
  grpc_slice_buffer_reset_and_unref(read_slices);
  grpc_slice_buffer_swap(read_slices, &tcp->last_read_buffer);

  // Allocate more buffer space if needed
  if (tcp->read_slices->length < DEFAULT_TARGET_READ_SIZE / 2 &&
      tcp->read_slices->count < MAX_WSABUF_COUNT) {
    grpc_slice_buffer_add(tcp->read_slices,
                          GRPC_SLICE_MALLOC(DEFAULT_TARGET_READ_SIZE));
  }

  // Prepare WSABUF structures
  CHECK(tcp->read_slices->count <= MAX_WSABUF_COUNT);
  for (i = 0; i < tcp->read_slices->count; i++) {
    buffers[i].len = (ULONG)GRPC_SLICE_LENGTH(tcp->read_slices->slices[i]);
    buffers[i].buf = (char*)GRPC_SLICE_START_PTR(tcp->read_slices->slices[i]);
  }

  TCP_REF(tcp, "read");

  // Attempt immediate read
  status = WSARecv(tcp->socket->socket, buffers, (DWORD)tcp->read_slices->count,
                   &bytes_read, &flags, NULL, NULL);
  info->wsa_error = status == 0 ? 0 : WSAGetLastError();

  // If data was immediately available, process it
  if (info->wsa_error != WSAEWOULDBLOCK) {
    info->bytes_transferred = bytes_read;
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, &tcp->on_read, absl::OkStatus());
    return;
  }

  // Otherwise setup asynchronous read
  memset(&tcp->socket->read_info.overlapped, 0, sizeof(OVERLAPPED));
  status = WSARecv(tcp->socket->socket, buffers, (DWORD)tcp->read_slices->count,
                   &bytes_read, &flags, &info->overlapped, NULL);

  if (status != 0) {
    int wsa_error = WSAGetLastError();
    if (wsa_error != WSA_IO_PENDING) {
      info->wsa_error = wsa_error;
      grpc_core::ExecCtx::Run(DEBUG_LOCATION, &tcp->on_read,
                              GRPC_WSA_ERROR(info->wsa_error, "WSARecv"));
      return;
    }
  }

  // Register for completion notification
  grpc_socket_notify_on_read(tcp->socket, &tcp->on_read);
}

// Callback for completed write operations
static void on_write(void* tcpp, grpc_error_handle error) {
  grpc_tcp* tcp = (grpc_tcp*)tcpp;
  grpc_winsocket* handle = tcp->socket;
  grpc_winsocket_callback_info* info = &handle->write_info;
  grpc_closure* cb;

  GRPC_TRACE_LOG(tcp, INFO) << "TCP:" << tcp << " on_write";

  // Retrieve and clear the write callback
  gpr_mu_lock(&tcp->mu);
  cb = tcp->write_cb;
  tcp->write_cb = NULL;
  gpr_mu_unlock(&tcp->mu);

  // Process operation result
  if (error.ok()) {
    if (info->wsa_error != 0) {
      error = GRPC_WSA_ERROR(info->wsa_error, "WSASend");
    } else {
      CHECK(info->bytes_transferred <= tcp->write_slices->length);
    }
  }

  // Clean up and invoke user callback
  TCP_UNREF(tcp, "write");
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, cb, error);
}

// Initiates a write operation on the endpoint
static void win_write(grpc_endpoint* ep, grpc_slice_buffer* slices,
                      grpc_closure* cb,
                      grpc_event_engine::experimental::EventEngine::Endpoint::
                          WriteArgs /*args*/) {
  grpc_tcp* tcp = (grpc_tcp*)ep;
  grpc_winsocket* socket = tcp->socket;
  grpc_winsocket_callback_info* info = &socket->write_info;
  unsigned i;
  DWORD bytes_sent;
  int status;
  WSABUF local_buffers[MAX_WSABUF_COUNT];
  WSABUF* allocated = NULL;
  WSABUF* buffers = local_buffers;
  size_t len, async_buffers_offset = 0;

  // Debug logging of data to be written
  if (GRPC_TRACE_FLAG_ENABLED(tcp) && ABSL_VLOG_IS_ON(2)) {
    size_t i;
    for (i = 0; i < slices->count; i++) {
      char* data =
          grpc_dump_slice(slices->slices[i], GPR_DUMP_HEX | GPR_DUMP_ASCII);
      VLOG(2) << "WRITE " << tcp << " (peer=" << tcp->peer_string
              << "): " << data;
      gpr_free(data);
    }
  }

  // Check for shutdown state
  if (tcp->shutting_down) {
    grpc_core::ExecCtx::Run(
        DEBUG_LOCATION, cb,
        grpc_error_set_int(GRPC_ERROR_CREATE("TCP socket is shutting down"),
                           grpc_core::StatusIntProperty::kRpcStatus,
                           GRPC_STATUS_UNAVAILABLE));
    return;
  }

  // Setup write operation
  tcp->write_cb = cb;
  tcp->write_slices = slices;
  CHECK(tcp->write_slices->count <= UINT_MAX);
  
  // Allocate buffers if needed
  if (tcp->write_slices->count > GPR_ARRAY_SIZE(local_buffers)) {
    buffers = (WSABUF*)gpr_malloc(sizeof(WSABUF) * tcp->write_slices->count);
    allocated = buffers;
  }

  // Prepare WSABUF structures
  for (i = 0; i < tcp->write_slices->count; i++) {
    len = GRPC_SLICE_LENGTH(tcp->write_slices->slices[i]);
    CHECK(len <= ULONG_MAX);
    buffers[i].len = (ULONG)len;
    buffers[i].buf = (char*)GRPC_SLICE_START_PTR(tcp->write_slices->slices[i]);
  }

  // Attempt immediate write
  status = WSASend(socket->socket, buffers, (DWORD)tcp->write