// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_GRPC_POLLED_FD_POSIX_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_GRPC_POLLED_FD_POSIX_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/sync.h"

#if GRPC_ARES == 1 && defined(GRPC_POSIX_SOCKET_ARES_EV_DRIVER)

#include <ares.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

#include <string>
#include <unordered_set>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/event_engine/grpc_polled_fd.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"

namespace grpc_event_engine::experimental {

class GrpcPolledFdPosix : public GrpcPolledFd {
 public:
  GrpcPolledFdPosix(ares_socket_t as, EventHandle* handle)
      : name_(absl::StrCat("c-ares fd: ", static_cast<int>(as))),
        as_(as),
        handle_(handle) {}

  ~GrpcPolledFdPosix() override {

    int phony_release_fd;
    handle_->OrphanHandle(nullptr, &phony_release_fd,
                          "c-ares query finished");
  }

  void RegisterForOnReadableLocked(
      absl::AnyInvocable<void(absl::Status)> read_closure) override {
    handle_->NotifyOnRead(new PosixEngineClosure(std::move(read_closure),
                                                 false));
  }

  void RegisterForOnWriteableLocked(
      absl::AnyInvocable<void(absl::Status)> write_closure) override {
    handle_->NotifyOnWrite(new PosixEngineClosure(std::move(write_closure),
                                                  false));
  }

  bool IsFdStillReadableLocked() override {
    size_t bytes_available = 0;
    return ioctl(handle_->WrappedFd(), FIONREAD, &bytes_available) == 0 &&
           bytes_available > 0;
  }

  bool ShutdownLocked(absl::Status error) override {
    handle_->ShutdownHandle(error);
    return true;
  }

  ares_socket_t GetWrappedAresSocketLocked() override { return as_; }

  const char* GetName() const override { return name_.c_str(); }

 private:
  const std::string name_;
  const ares_socket_t as_;
  EventHandle* handle_;
};

class GrpcPolledFdFactoryPosix : public GrpcPolledFdFactory {
 public:
  explicit GrpcPolledFdFactoryPosix(PosixEventPoller* poller)
      : poller_(poller) {}

  ~GrpcPolledFdFactoryPosix() override {
    for (auto& fd : owned_fds_) {
      close(fd);
    }
  }

  void Initialize(grpc_core::Mutex*, EventEngine*) override {}

  std::unique_ptr<GrpcPolledFd> NewGrpcPolledFdLocked(
      ares_socket_t as) override {
    owned_fds_.insert(as);
    return std::make_unique<GrpcPolledFdPosix>(
        as,
        poller_->CreateHandle(as, "c-ares socket", poller_->CanTrackErrors()));
  }

  void ConfigureAresChannelLocked(ares_channel channel) override {
    ares_set_socket_functions(channel, &kSockFuncs, this);
    ares_set_socket_configure_callback(
        channel, &GrpcPolledFdFactoryPosix::ConfigureSocket, nullptr);
  }

 private:

  static ares_socket_t Socket(int af, int type, int protocol,
                              void* ) {
    return socket(af, type, protocol);
  }

  static int Connect(ares_socket_t as, const struct sockaddr* target,
                     ares_socklen_t target_len, void* ) {
    return connect(as, target, target_len);
  }

  static ares_ssize_t WriteV(ares_socket_t as, const struct iovec* iov,
                             int iovec_count, void* ) {
    return writev(as, iov, iovec_count);
  }

  static ares_ssize_t RecvFrom(ares_socket_t as, void* data, size_t data_len,
                               int flags, struct sockaddr* from,
                               ares_socklen_t* from_len, void* ) {
    return recvfrom(as, data, data_len, flags, from, from_len);
  }

  static int Close(ares_socket_t as, void* user_data) {
    GrpcPolledFdFactoryPosix* self =
        static_cast<GrpcPolledFdFactoryPosix*>(user_data);
    if (self->owned_fds_.find(as) == self->owned_fds_.end()) {

      return close(as);
    }
    return 0;
  }

  static int ConfigureSocket(ares_socket_t fd, int type, void* ) {

#define RETURN_IF_ERROR(expr) if (!(expr).ok()) { return -1; }

    PosixSocketWrapper sock(fd);
    RETURN_IF_ERROR(sock.SetSocketNonBlocking(1));
    RETURN_IF_ERROR(sock.SetSocketCloexec(1));
    if (type == SOCK_STREAM) {
      RETURN_IF_ERROR(sock.SetSocketLowLatency(1));
    }
    return 0;
  }

  const struct ares_socket_functions kSockFuncs = {
      &GrpcPolledFdFactoryPosix::Socket ,
      &GrpcPolledFdFactoryPosix::Close ,
      &GrpcPolledFdFactoryPosix::Connect ,
      &GrpcPolledFdFactoryPosix::RecvFrom ,
      &GrpcPolledFdFactoryPosix::WriteV ,
  };

  PosixEventPoller* poller_;

  std::unordered_set<ares_socket_t> owned_fds_;
};

}

#endif
#endif
