
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_WINSOCK_SOCKET

#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <winsock2.h>

#include <limits>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/lib/iomgr/timer.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/crash.h"
#include "src/core/util/thd.h"

static ULONG g_iocp_kick_token;
static OVERLAPPED g_iocp_custom_overlap;

static gpr_atm g_custom_events = 0;
static gpr_atm g_pending_socket_shutdowns = 0;

static HANDLE g_iocp;

static DWORD deadline_to_millis_timeout(grpc_core::Timestamp deadline) {
  if (deadline == grpc_core::Timestamp::InfFuture()) {
    return INFINITE;
  }
  grpc_core::Timestamp now = grpc_core::Timestamp::Now();
  if (deadline < now) return 0;
  grpc_core::Duration timeout = deadline - now;
  if (timeout.millis() > std::numeric_limits<DWORD>::max()) return INFINITE;
  return static_cast<DWORD>(timeout.millis());
}

grpc_iocp_work_status grpc_iocp_work(grpc_core::Timestamp deadline) {
  BOOL success;
  DWORD bytes = 0;
  DWORD flags = 0;
  ULONG_PTR completion_key;
  LPOVERLAPPED overlapped;
  grpc_winsocket* socket;
  grpc_winsocket_callback_info* info;
  success =
      GetQueuedCompletionStatus(g_iocp, &bytes, &completion_key, &overlapped,
                                deadline_to_millis_timeout(deadline));
  grpc_core::ExecCtx::Get()->InvalidateNow();
  if (success == 0 && overlapped == NULL) {
    return GRPC_IOCP_WORK_TIMEOUT;
  }
  CHECK(completion_key);
  CHECK(overlapped);
  if (overlapped == &g_iocp_custom_overlap) {
    gpr_atm_full_fetch_add(&g_custom_events, -1);
    if (completion_key == (ULONG_PTR)&g_iocp_kick_token) {

      return GRPC_IOCP_WORK_KICK;
    }
    grpc_core::Crash("Unknown custom completion key.");
  }

  socket = (grpc_winsocket*)completion_key;
  if (overlapped == &socket->write_info.overlapped) {
    info = &socket->write_info;
  } else if (overlapped == &socket->read_info.overlapped) {
    info = &socket->read_info;
  } else {
    abort();
  }
  gpr_mu_lock(&socket->state_mu);
  if (socket->shutdown_called) {
    info->bytes_transferred = 0;
    info->wsa_error = WSA_OPERATION_ABORTED;
  } else {
    success = WSAGetOverlappedResult(socket->socket, &info->overlapped, &bytes,
                                     FALSE, &flags);
    info->bytes_transferred = bytes;
    info->wsa_error = success ? 0 : WSAGetLastError();
  }
  CHECK(overlapped == &info->overlapped);
  bool should_destroy = grpc_socket_become_ready(socket, info);
  gpr_mu_unlock(&socket->state_mu);
  if (should_destroy) {
    grpc_winsocket_finish(socket);
  }
  return GRPC_IOCP_WORK_WORK;
}

void grpc_iocp_init(void) {
  g_iocp =
      CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)NULL, 0);
  CHECK(g_iocp);
}

void grpc_iocp_kick(void) {
  BOOL success;

  gpr_atm_full_fetch_add(&g_custom_events, 1);
  success = PostQueuedCompletionStatus(g_iocp, 0, (ULONG_PTR)&g_iocp_kick_token,
                                       &g_iocp_custom_overlap);
  CHECK(success);
}

void grpc_iocp_flush(void) {
  grpc_core::ExecCtx exec_ctx;
  grpc_iocp_work_status work_status;

  do {
    work_status = grpc_iocp_work(grpc_core::Timestamp::InfPast());
  } while (work_status == GRPC_IOCP_WORK_KICK ||
           grpc_core::ExecCtx::Get()->Flush() ||
           gpr_atm_acq_load(&g_pending_socket_shutdowns) != 0);
}

void grpc_iocp_shutdown(void) {
  grpc_core::ExecCtx exec_ctx;
  while (gpr_atm_acq_load(&g_custom_events)) {
    grpc_iocp_work(grpc_core::Timestamp::InfFuture());
    grpc_core::ExecCtx::Get()->Flush();
  }

  CHECK(CloseHandle(g_iocp));
}

void grpc_iocp_add_socket(grpc_winsocket* socket) {
  HANDLE ret;
  if (socket->added_to_iocp) return;
  ret = CreateIoCompletionPort((HANDLE)socket->socket, g_iocp,
                               (uintptr_t)socket, 0);
  if (!ret) {
    char* utf8_message = gpr_format_message(WSAGetLastError());
    LOG(ERROR) << "Unable to add socket to iocp: " << utf8_message;
    gpr_free(utf8_message);
    __debugbreak();
    abort();
  }
  socket->added_to_iocp = 1;
  CHECK(ret == g_iocp);
}

void grpc_iocp_register_socket_shutdown_socket_locked(grpc_winsocket* socket) {
  if (!socket->shutdown_registered) {
    socket->shutdown_registered = true;
    gpr_atm_full_fetch_add(&g_pending_socket_shutdowns, 1);
  }
}

void grpc_iocp_finish_socket_shutdown(grpc_winsocket* socket) {
  if (socket->shutdown_registered) {
    gpr_atm_full_fetch_add(&g_pending_socket_shutdowns, -1);
  }
}

#endif
