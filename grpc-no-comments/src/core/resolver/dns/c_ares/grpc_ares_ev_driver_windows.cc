
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)

#include <ares.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <string.h>

#include <map>
#include <memory>
#include <unordered_set>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/sockaddr_windows.h"
#include "src/core/lib/iomgr/socket_windows.h"
#include "src/core/lib/iomgr/tcp_windows.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_ev_driver.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/util/crash.h"
#include "src/core/util/memory.h"
#include "src/core/util/string.h"

struct iovec {
  void* iov_base;
  size_t iov_len;
};

namespace grpc_core {

namespace {

class WSAErrorContext final {
 public:
  explicit WSAErrorContext() {};

  ~WSAErrorContext() {
    if (error_ != 0) {
      WSASetLastError(error_);
    }
  }

  WSAErrorContext(const WSAErrorContext&) = delete;
  WSAErrorContext& operator=(const WSAErrorContext&) = delete;

  void SetWSAError(int error) { error_ = error; }

 private:
  int error_ = 0;
};

class GrpcPolledFdWindows final : public GrpcPolledFd {
 public:
  enum WriteState {
    WRITE_IDLE,
    WRITE_REQUESTED,
    WRITE_PENDING,
    WRITE_WAITING_FOR_VERIFICATION_UPON_RETRY,
  };

  GrpcPolledFdWindows(ares_socket_t as, Mutex* mu, int address_family,
                      int socket_type,
                      absl::AnyInvocable<void()> on_shutdown_locked)
      : mu_(mu),
        read_buf_(grpc_empty_slice()),
        write_buf_(grpc_empty_slice()),
        name_(absl::StrFormat("c-ares socket: %" PRIdPTR, as)),
        address_family_(address_family),
        socket_type_(socket_type),
        on_shutdown_locked_(std::move(on_shutdown_locked)) {

    GRPC_CLOSURE_INIT(&outer_read_closure_,
                      &GrpcPolledFdWindows::OnIocpReadable, this,
                      grpc_schedule_on_exec_ctx);
    GRPC_CLOSURE_INIT(&outer_write_closure_,
                      &GrpcPolledFdWindows::OnIocpWriteable, this,
                      grpc_schedule_on_exec_ctx);
    GRPC_CLOSURE_INIT(&on_tcp_connect_locked_,
                      &GrpcPolledFdWindows::OnTcpConnect, this,
                      grpc_schedule_on_exec_ctx);
    winsocket_ = grpc_winsocket_create(as, name_.c_str());
  }

  ~GrpcPolledFdWindows() override {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:|" << GetName()
        << "| ~GrpcPolledFdWindows shutdown_called_: " << shutdown_called_;
    CSliceUnref(read_buf_);
    CSliceUnref(write_buf_);
    CHECK_EQ(read_closure_, nullptr);
    CHECK_EQ(write_closure_, nullptr);
    if (!shutdown_called_) {

      grpc_winsocket_shutdown(winsocket_);
    }
    grpc_winsocket_destroy(winsocket_);
  }

  void ScheduleAndNullReadClosure(grpc_error_handle error) {
    ExecCtx::Run(DEBUG_LOCATION, read_closure_, error);
    read_closure_ = nullptr;
  }

  void ScheduleAndNullWriteClosure(grpc_error_handle error) {
    ExecCtx::Run(DEBUG_LOCATION, write_closure_, error);
    write_closure_ = nullptr;
  }

  void RegisterForOnReadableLocked(grpc_closure* read_closure) override {
    CHECK_EQ(read_closure_, nullptr);
    read_closure_ = read_closure;
    CHECK_EQ(GRPC_SLICE_LENGTH(read_buf_), 0);
    CSliceUnref(read_buf_);
    CHECK(!read_buf_has_data_);
    read_buf_ = GRPC_SLICE_MALLOC(4192);
    if (connect_done_) {
      ContinueRegisterForOnReadableLocked();
    } else {
      CHECK(pending_continue_register_for_on_readable_locked_ == false);
      pending_continue_register_for_on_readable_locked_ = true;
    }
  }

  void ContinueRegisterForOnReadableLocked() {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:|" << GetName()
        << "| ContinueRegisterForOnReadableLocked "
        << "wsa_connect_error_:" << wsa_connect_error_;
    CHECK(connect_done_);
    if (wsa_connect_error_ != 0) {
      ScheduleAndNullReadClosure(GRPC_WSA_ERROR(wsa_connect_error_, "connect"));
      return;
    }
    WSABUF buffer;
    buffer.buf = (char*)GRPC_SLICE_START_PTR(read_buf_);
    buffer.len = GRPC_SLICE_LENGTH(read_buf_);
    memset(&winsocket_->read_info.overlapped, 0, sizeof(OVERLAPPED));
    recv_from_source_addr_len_ = sizeof(recv_from_source_addr_);
    DWORD flags = 0;
    if (WSARecvFrom(grpc_winsocket_wrapped_socket(winsocket_), &buffer, 1,
                    nullptr, &flags, (sockaddr*)recv_from_source_addr_,
                    &recv_from_source_addr_len_,
                    &winsocket_->read_info.overlapped, nullptr)) {
      int wsa_last_error = WSAGetLastError();
      char* msg = gpr_format_message(wsa_last_error);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:|" << GetName()
          << "| RegisterForOnReadableLocked WSARecvFrom error code:|"
          << wsa_last_error << "| msg:|" << msg << "|";
      gpr_free(msg);
      if (wsa_last_error != WSA_IO_PENDING) {
        ScheduleAndNullReadClosure(
            GRPC_WSA_ERROR(wsa_last_error, "WSARecvFrom"));
        return;
      }
    }
    grpc_socket_notify_on_read(winsocket_, &outer_read_closure_);
  }

  void RegisterForOnWriteableLocked(grpc_closure* write_closure) override {
    if (socket_type_ == SOCK_DGRAM) {
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:|" << GetName()
          << "| RegisterForOnWriteableLocked called";
    } else {
      CHECK(socket_type_ == SOCK_STREAM);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:|" << GetName()
          << "| RegisterForOnWriteableLocked called tcp_write_state_: "
          << tcp_write_state_ << " connect_done_: " << connect_done_;
    }
    CHECK_EQ(write_closure_, nullptr);
    write_closure_ = write_closure;
    if (!connect_done_) {
      CHECK(!pending_continue_register_for_on_writeable_locked_);
      pending_continue_register_for_on_writeable_locked_ = true;

      grpc_socket_notify_on_write(winsocket_, &on_tcp_connect_locked_);
    } else {
      ContinueRegisterForOnWriteableLocked();
    }
  }

  void ContinueRegisterForOnWriteableLocked() {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:|" << GetName()
        << "| ContinueRegisterForOnWriteableLocked "
        << "wsa_connect_error_:" << wsa_connect_error_;
    CHECK(connect_done_);
    if (wsa_connect_error_ != 0) {
      ScheduleAndNullWriteClosure(
          GRPC_WSA_ERROR(wsa_connect_error_, "connect"));
      return;
    }
    if (socket_type_ == SOCK_DGRAM) {
      ScheduleAndNullWriteClosure(absl::OkStatus());
    } else {
      CHECK(socket_type_ == SOCK_STREAM);
      int wsa_error_code = 0;
      switch (tcp_write_state_) {
        case WRITE_IDLE:
          ScheduleAndNullWriteClosure(absl::OkStatus());
          break;
        case WRITE_REQUESTED:
          tcp_write_state_ = WRITE_PENDING;
          if (SendWriteBuf(nullptr, &winsocket_->write_info.overlapped,
                           &wsa_error_code) != 0) {
            ScheduleAndNullWriteClosure(
                GRPC_WSA_ERROR(wsa_error_code, "WSASend (overlapped)"));
          } else {
            grpc_socket_notify_on_write(winsocket_, &outer_write_closure_);
          }
          break;
        case WRITE_PENDING:
        case WRITE_WAITING_FOR_VERIFICATION_UPON_RETRY:
          abort();
      }
    }
  }

  bool IsFdStillReadableLocked() override { return read_buf_has_data_; }

  void ShutdownLocked(grpc_error_handle ) override {
    CHECK(!shutdown_called_);
    shutdown_called_ = true;
    on_shutdown_locked_();
    grpc_winsocket_shutdown(winsocket_);
  }

  ares_socket_t GetWrappedAresSocketLocked() override {
    return grpc_winsocket_wrapped_socket(winsocket_);
  }

  const char* GetName() const override { return name_.c_str(); }

  ares_ssize_t RecvFrom(WSAErrorContext* wsa_error_ctx, void* data,
                        ares_socket_t data_len, int ,
                        struct sockaddr* from, ares_socklen_t* from_len) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName()
        << " RecvFrom called read_buf_has_data:" << read_buf_has_data_
        << " Current read buf length:" << GRPC_SLICE_LENGTH(read_buf_);
    if (!read_buf_has_data_) {
      wsa_error_ctx->SetWSAError(WSAEWOULDBLOCK);
      return -1;
    }
    ares_ssize_t bytes_read = 0;
    for (size_t i = 0; i < GRPC_SLICE_LENGTH(read_buf_) && i < data_len; i++) {
      ((char*)data)[i] = GRPC_SLICE_START_PTR(read_buf_)[i];
      bytes_read++;
    }
    read_buf_ = grpc_slice_sub_no_ref(read_buf_, bytes_read,
                                      GRPC_SLICE_LENGTH(read_buf_));
    if (GRPC_SLICE_LENGTH(read_buf_) == 0) {
      read_buf_has_data_ = false;
    }

    if (from != nullptr) {
      CHECK(*from_len >= recv_from_source_addr_len_);
      memcpy(from, &recv_from_source_addr_, recv_from_source_addr_len_);
      *from_len = recv_from_source_addr_len_;
    }
    return bytes_read;
  }

  grpc_slice FlattenIovec(const struct iovec* iov, int iov_count) {
    int total = 0;
    for (int i = 0; i < iov_count; i++) {
      total += iov[i].iov_len;
    }
    grpc_slice out = GRPC_SLICE_MALLOC(total);
    size_t cur = 0;
    for (int i = 0; i < iov_count; i++) {
      for (size_t k = 0; k < iov[i].iov_len; k++) {
        GRPC_SLICE_START_PTR(out)[cur++] = ((char*)iov[i].iov_base)[k];
      }
    }
    return out;
  }

  int SendWriteBuf(LPDWORD bytes_sent_ptr, LPWSAOVERLAPPED overlapped,
                   int* wsa_error_code) {
    WSABUF buf;
    buf.len = GRPC_SLICE_LENGTH(write_buf_);
    buf.buf = (char*)GRPC_SLICE_START_PTR(write_buf_);
    DWORD flags = 0;
    int out = WSASend(grpc_winsocket_wrapped_socket(winsocket_), &buf, 1,
                      bytes_sent_ptr, flags, overlapped, nullptr);
    *wsa_error_code = WSAGetLastError();
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName()
        << " SendWriteBuf WSASend buf.len:" << buf.len << " *bytes_sent_ptr:"
        << (bytes_sent_ptr != nullptr ? *bytes_sent_ptr : 0)
        << " overlapped:" << overlapped << " return:" << out
        << " *wsa_error_code:" << *wsa_error_code;
    return out;
  }

  ares_ssize_t SendV(WSAErrorContext* wsa_error_ctx, const struct iovec* iov,
                     int iov_count) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName()
        << " SendV called connect_done_:" << connect_done_
        << " wsa_connect_error_:" << wsa_connect_error_;
    if (!connect_done_) {
      wsa_error_ctx->SetWSAError(WSAEWOULDBLOCK);
      return -1;
    }
    if (wsa_connect_error_ != 0) {
      wsa_error_ctx->SetWSAError(wsa_connect_error_);
      return -1;
    }
    switch (socket_type_) {
      case SOCK_DGRAM:
        return SendVUDP(wsa_error_ctx, iov, iov_count);
      case SOCK_STREAM:
        return SendVTCP(wsa_error_ctx, iov, iov_count);
      default:
        abort();
    }
  }

  ares_ssize_t SendVUDP(WSAErrorContext* wsa_error_ctx, const struct iovec* iov,
                        int iov_count) {

    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName() << " SendVUDP called";
    CHECK_EQ(GRPC_SLICE_LENGTH(write_buf_), 0);
    CSliceUnref(write_buf_);
    write_buf_ = FlattenIovec(iov, iov_count);
    DWORD bytes_sent = 0;
    int wsa_error_code = 0;
    if (SendWriteBuf(&bytes_sent, nullptr, &wsa_error_code) != 0) {
      CSliceUnref(write_buf_);
      write_buf_ = grpc_empty_slice();
      wsa_error_ctx->SetWSAError(wsa_error_code);
      char* msg = gpr_format_message(wsa_error_code);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:" << GetName()
          << " SendVUDP SendWriteBuf error code:" << wsa_error_code
          << " msg:" << msg;
      gpr_free(msg);
      return -1;
    }
    write_buf_ = grpc_slice_sub_no_ref(write_buf_, bytes_sent,
                                       GRPC_SLICE_LENGTH(write_buf_));
    return bytes_sent;
  }

  ares_ssize_t SendVTCP(WSAErrorContext* wsa_error_ctx, const struct iovec* iov,
                        int iov_count) {

    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName()
        << " SendVTCP called tcp_write_state_:" << tcp_write_state_;
    switch (tcp_write_state_) {
      case WRITE_IDLE:
        tcp_write_state_ = WRITE_REQUESTED;
        CHECK_EQ(GRPC_SLICE_LENGTH(write_buf_), 0);
        CSliceUnref(write_buf_);
        write_buf_ = FlattenIovec(iov, iov_count);
        wsa_error_ctx->SetWSAError(WSAEWOULDBLOCK);
        return -1;
      case WRITE_REQUESTED:
      case WRITE_PENDING:
        wsa_error_ctx->SetWSAError(WSAEWOULDBLOCK);
        return -1;
      case WRITE_WAITING_FOR_VERIFICATION_UPON_RETRY:

        grpc_slice currently_attempted = FlattenIovec(iov, iov_count);
        CHECK(GRPC_SLICE_LENGTH(currently_attempted) >=
              GRPC_SLICE_LENGTH(write_buf_));
        ares_ssize_t total_sent = 0;
        for (size_t i = 0; i < GRPC_SLICE_LENGTH(write_buf_); i++) {
          CHECK(GRPC_SLICE_START_PTR(currently_attempted)[i] ==
                GRPC_SLICE_START_PTR(write_buf_)[i]);
          total_sent++;
        }
        CSliceUnref(currently_attempted);
        tcp_write_state_ = WRITE_IDLE;
        return total_sent;
    }
    abort();
  }

  static void OnTcpConnect(void* arg, grpc_error_handle error) {
    GrpcPolledFdWindows* grpc_polled_fd =
        static_cast<GrpcPolledFdWindows*>(arg);
    MutexLock lock(grpc_polled_fd->mu_);
    grpc_polled_fd->OnTcpConnectLocked(error);
  }

  void OnTcpConnectLocked(grpc_error_handle error) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName()
        << " InnerOnTcpConnectLocked error:" << StatusToString(error)
        << " pending_register_for_readable:"
        << pending_continue_register_for_on_readable_locked_
        << " pending_register_for_writeable:"
        << pending_continue_register_for_on_writeable_locked_;
    CHECK(!connect_done_);
    connect_done_ = true;
    CHECK_EQ(wsa_connect_error_, 0);
    if (!error.ok() || shutdown_called_) {
      wsa_connect_error_ = WSA_OPERATION_ABORTED;
    } else {
      DWORD transferred_bytes = 0;
      DWORD flags;
      BOOL wsa_success =
          WSAGetOverlappedResult(grpc_winsocket_wrapped_socket(winsocket_),
                                 &winsocket_->write_info.overlapped,
                                 &transferred_bytes, FALSE, &flags);
      CHECK_EQ(transferred_bytes, 0);
      if (!wsa_success) {
        wsa_connect_error_ = WSAGetLastError();
        char* msg = gpr_format_message(wsa_connect_error_);
        GRPC_TRACE_VLOG(cares_resolver, 2)
            << "(c-ares resolver) fd:" << GetName()
            << " InnerOnTcpConnectLocked WSA overlapped result code:"
            << wsa_connect_error_ << " msg:" << msg;
        gpr_free(msg);
      }
    }
    if (pending_continue_register_for_on_readable_locked_) {
      ContinueRegisterForOnReadableLocked();
    }
    if (pending_continue_register_for_on_writeable_locked_) {
      ContinueRegisterForOnWriteableLocked();
    }
  }

  int Connect(WSAErrorContext* wsa_error_ctx, const struct sockaddr* target,
              ares_socklen_t target_len) {
    switch (socket_type_) {
      case SOCK_DGRAM:
        return ConnectUDP(wsa_error_ctx, target, target_len);
      case SOCK_STREAM:
        return ConnectTCP(wsa_error_ctx, target, target_len);
      default:
        abort();
    }
  }

  int ConnectUDP(WSAErrorContext* wsa_error_ctx, const struct sockaddr* target,
                 ares_socklen_t target_len) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName() << " ConnectUDP";
    CHECK(!connect_done_);
    CHECK_EQ(wsa_connect_error_, 0);
    SOCKET s = grpc_winsocket_wrapped_socket(winsocket_);
    int out =
        WSAConnect(s, target, target_len, nullptr, nullptr, nullptr, nullptr);
    wsa_connect_error_ = WSAGetLastError();
    wsa_error_ctx->SetWSAError(wsa_connect_error_);
    connect_done_ = true;
    char* msg = gpr_format_message(wsa_connect_error_);
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName() << " WSAConnect error code:|"
        << wsa_connect_error_ << "| msg:|" << msg << "|";
    gpr_free(msg);

    return out == 0 ? 0 : -1;
  }

  int ConnectTCP(WSAErrorContext* wsa_error_ctx, const struct sockaddr* target,
                 ares_socklen_t target_len) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << GetName() << " ConnectTCP";
    LPFN_CONNECTEX ConnectEx;
    GUID guid = WSAID_CONNECTEX;
    DWORD ioctl_num_bytes;
    SOCKET s = grpc_winsocket_wrapped_socket(winsocket_);
    if (WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid),
                 &ConnectEx, sizeof(ConnectEx), &ioctl_num_bytes, nullptr,
                 nullptr) != 0) {
      int wsa_last_error = WSAGetLastError();
      wsa_error_ctx->SetWSAError(wsa_last_error);
      char* msg = gpr_format_message(wsa_last_error);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:" << GetName()
          << " WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER) error code:"
          << wsa_last_error << " msg:|" << msg << "|";
      gpr_free(msg);
      connect_done_ = true;
      wsa_connect_error_ = wsa_last_error;
      return -1;
    }
    grpc_resolved_address wildcard4_addr;
    grpc_resolved_address wildcard6_addr;
    grpc_sockaddr_make_wildcards(0, &wildcard4_addr, &wildcard6_addr);
    grpc_resolved_address* local_address = nullptr;
    if (address_family_ == AF_INET) {
      local_address = &wildcard4_addr;
    } else {
      local_address = &wildcard6_addr;
    }
    if (bind(s, (struct sockaddr*)local_address->addr,
             (int)local_address->len) != 0) {
      int wsa_last_error = WSAGetLastError();
      wsa_error_ctx->SetWSAError(wsa_last_error);
      char* msg = gpr_format_message(wsa_last_error);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:" << GetName()
          << " bind error code:" << wsa_last_error << " msg:|" << msg << "|";
      gpr_free(msg);
      connect_done_ = true;
      wsa_connect_error_ = wsa_last_error;
      return -1;
    }
    int out = 0;
    if (ConnectEx(s, target, target_len, nullptr, 0, nullptr,
                  &winsocket_->write_info.overlapped) == 0) {
      out = -1;
      int wsa_last_error = WSAGetLastError();
      wsa_error_ctx->SetWSAError(wsa_last_error);
      char* msg = gpr_format_message(wsa_last_error);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:" << GetName()
          << " ConnectEx error code:" << wsa_last_error << " msg:|" << msg
          << "|";
      gpr_free(msg);
      if (wsa_last_error == WSA_IO_PENDING) {

        wsa_error_ctx->SetWSAError(WSAEWOULDBLOCK);
      } else {

        connect_done_ = true;
        wsa_connect_error_ = wsa_last_error;
        return -1;
      }
    }

    return out;
  }

  static void OnIocpReadable(void* arg, grpc_error_handle error) {
    GrpcPolledFdWindows* polled_fd = static_cast<GrpcPolledFdWindows*>(arg);
    MutexLock lock(polled_fd->mu_);
    polled_fd->OnIocpReadableLocked(error);
  }

  void OnIocpReadableLocked(grpc_error_handle error) {
    if (error.ok()) {
      if (winsocket_->read_info.wsa_error != 0) {

        if (winsocket_->read_info.wsa_error != WSAEMSGSIZE) {
          error = GRPC_WSA_ERROR(winsocket_->read_info.wsa_error,
                                 "OnIocpReadableInner");
          GRPC_TRACE_VLOG(cares_resolver, 2)
              << "(c-ares resolver) fd:|" << GetName()
              << "| OnIocpReadableInner winsocket_->read_info.wsa_error "
                 "code:|"
              << winsocket_->read_info.wsa_error << "| msg:|"
              << StatusToString(error) << "|";
        }
      }
    }
    if (error.ok()) {
      read_buf_ = grpc_slice_sub_no_ref(
          read_buf_, 0, winsocket_->read_info.bytes_transferred);
      read_buf_has_data_ = true;
    } else {
      CSliceUnref(read_buf_);
      read_buf_ = grpc_empty_slice();
    }
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:|" << GetName()
        << "| OnIocpReadable finishing. read buf length now:|"
        << GRPC_SLICE_LENGTH(read_buf_) << "|";
    ScheduleAndNullReadClosure(error);
  }

  static void OnIocpWriteable(void* arg, grpc_error_handle error) {
    GrpcPolledFdWindows* polled_fd = static_cast<GrpcPolledFdWindows*>(arg);
    MutexLock lock(polled_fd->mu_);
    polled_fd->OnIocpWriteableLocked(error);
  }

  void OnIocpWriteableLocked(grpc_error_handle error) {
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) OnIocpWriteableInner. fd:|" << GetName() << "|";
    CHECK(socket_type_ == SOCK_STREAM);
    if (error.ok()) {
      if (winsocket_->write_info.wsa_error != 0) {
        error = GRPC_WSA_ERROR(winsocket_->write_info.wsa_error,
                               "OnIocpWriteableInner");
        GRPC_TRACE_VLOG(cares_resolver, 2)
            << "(c-ares resolver) fd:|" << GetName()
            << "| OnIocpWriteableInner. winsocket_->write_info.wsa_error "
               "code:|"
            << winsocket_->write_info.wsa_error << "| msg:|"
            << StatusToString(error) << "|";
      }
    }
    CHECK(tcp_write_state_ == WRITE_PENDING);
    if (error.ok()) {
      tcp_write_state_ = WRITE_WAITING_FOR_VERIFICATION_UPON_RETRY;
      write_buf_ = grpc_slice_sub_no_ref(
          write_buf_, 0, winsocket_->write_info.bytes_transferred);
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) fd:|" << GetName()
          << "| OnIocpWriteableInner. bytes transferred:"
          << winsocket_->write_info.bytes_transferred;
    } else {
      CSliceUnref(write_buf_);
      write_buf_ = grpc_empty_slice();
    }
    ScheduleAndNullWriteClosure(error);
  }

 private:
  Mutex* mu_;
  char recv_from_source_addr_[200];
  ares_socklen_t recv_from_source_addr_len_;
  grpc_slice read_buf_;
  bool read_buf_has_data_ = false;
  grpc_slice write_buf_;
  grpc_closure* read_closure_ = nullptr;
  grpc_closure* write_closure_ = nullptr;
  grpc_closure outer_read_closure_;
  grpc_closure outer_write_closure_;
  grpc_winsocket* winsocket_;
  const std::string name_;
  bool shutdown_called_ = false;
  int address_family_;
  int socket_type_;

  grpc_closure on_tcp_connect_locked_;
  bool connect_done_ = false;
  int wsa_connect_error_ = 0;
  WriteState tcp_write_state_ = WRITE_IDLE;

  bool pending_continue_register_for_on_readable_locked_ = false;
  bool pending_continue_register_for_on_writeable_locked_ = false;
  absl::AnyInvocable<void()> on_shutdown_locked_;
};

class GrpcPolledFdFactoryWindows final : public GrpcPolledFdFactory {
 public:
  explicit GrpcPolledFdFactoryWindows(Mutex* mu) : mu_(mu) {}

  ~GrpcPolledFdFactoryWindows() override {

    for (auto& it : sockets_) {
      delete it.second;
    }
  }

  GrpcPolledFd* NewGrpcPolledFdLocked(
      ares_socket_t as, grpc_pollset_set* ) override {
    auto it = sockets_.find(as);
    CHECK(it != sockets_.end());
    return it->second;
  }

  void ConfigureAresChannelLocked(ares_channel channel) override {
    ares_set_socket_functions(channel, &kCustomSockFuncs, this);
  }

 private:

  static ares_socket_t Socket(int af, int type, int protocol, void* user_data) {
    if (type != SOCK_DGRAM && type != SOCK_STREAM) {
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) Socket called with invalid socket type:"
          << type;
      return INVALID_SOCKET;
    }
    GrpcPolledFdFactoryWindows* self =
        static_cast<GrpcPolledFdFactoryWindows*>(user_data);
    SOCKET s = WSASocket(af, type, protocol, nullptr, 0,
                         grpc_get_default_wsa_socket_flags());
    if (s == INVALID_SOCKET) {
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) WSASocket failed with params af:" << af
          << " type:" << type << " protocol:" << protocol;
      return s;
    }
    grpc_error_handle error = grpc_tcp_set_non_block(s);
    if (!error.ok()) {
      GRPC_TRACE_VLOG(cares_resolver, 2)
          << "(c-ares resolver) WSAIoctl failed with error: "
          << StatusToString(error);
      return INVALID_SOCKET;
    }
    auto on_shutdown_locked = [self, s]() {

      self->sockets_.erase(s);
    };
    auto polled_fd = new GrpcPolledFdWindows(s, self->mu_, af, type,
                                             std::move(on_shutdown_locked));
    GRPC_TRACE_VLOG(cares_resolver, 2)
        << "(c-ares resolver) fd:" << polled_fd->GetName()
        << " created with params af:" << af << " type:" << type
        << " protocol:" << protocol;
    CHECK(self->sockets_.insert({s, polled_fd}).second);
    return s;
  }

  static int Connect(ares_socket_t as, const struct sockaddr* target,
                     ares_socklen_t target_len, void* user_data) {
    WSAErrorContext wsa_error_ctx;
    GrpcPolledFdFactoryWindows* self =
        static_cast<GrpcPolledFdFactoryWindows*>(user_data);
    auto it = self->sockets_.find(as);
    CHECK(it != self->sockets_.end());
    return it->second->Connect(&wsa_error_ctx, target, target_len);
  }

  static ares_ssize_t SendV(ares_socket_t as, const struct iovec* iov,
                            int iovec_count, void* user_data) {
    WSAErrorContext wsa_error_ctx;
    GrpcPolledFdFactoryWindows* self =
        static_cast<GrpcPolledFdFactoryWindows*>(user_data);
    auto it = self->sockets_.find(as);
    CHECK(it != self->sockets_.end());
    return it->second->SendV(&wsa_error_ctx, iov, iovec_count);
  }

  static ares_ssize_t RecvFrom(ares_socket_t as, void* data, size_t data_len,
                               int flags, struct sockaddr* from,
                               ares_socklen_t* from_len, void* user_data) {
    WSAErrorContext wsa_error_ctx;
    GrpcPolledFdFactoryWindows* self =
        static_cast<GrpcPolledFdFactoryWindows*>(user_data);
    auto it = self->sockets_.find(as);
    CHECK(it != self->sockets_.end());
    return it->second->RecvFrom(&wsa_error_ctx, data, data_len, flags, from,
                                from_len);
  }

  static int CloseSocket(SOCKET , void* ) { return 0; }

  const struct ares_socket_functions kCustomSockFuncs = {
      &GrpcPolledFdFactoryWindows::Socket ,
      &GrpcPolledFdFactoryWindows::CloseSocket ,
      &GrpcPolledFdFactoryWindows::Connect ,
      &GrpcPolledFdFactoryWindows::RecvFrom ,
      &GrpcPolledFdFactoryWindows::SendV ,
  };

  Mutex* mu_;
  std::map<SOCKET, GrpcPolledFdWindows*> sockets_;
};

}

std::unique_ptr<GrpcPolledFdFactory> NewGrpcPolledFdFactory(Mutex* mu) {
  return std::make_unique<GrpcPolledFdFactoryWindows>(mu);
}

}

#endif
