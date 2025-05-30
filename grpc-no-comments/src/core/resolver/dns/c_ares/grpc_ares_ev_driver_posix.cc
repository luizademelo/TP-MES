
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#if GRPC_ARES == 1 && defined(GRPC_POSIX_SOCKET_ARES_EV_DRIVER)

#include <ares.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/socket_utils_posix.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_ev_driver.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class GrpcPolledFdPosix final : public GrpcPolledFd {
 public:
  GrpcPolledFdPosix(ares_socket_t as, grpc_pollset_set* driver_pollset_set)
      : name_(absl::StrCat("c-ares fd: ", static_cast<int>(as))), as_(as) {
    fd_ = grpc_fd_create(static_cast<int>(as), name_.c_str(), false);
    driver_pollset_set_ = driver_pollset_set;
    grpc_pollset_set_add_fd(driver_pollset_set_, fd_);
  }

  ~GrpcPolledFdPosix() override {
    grpc_pollset_set_del_fd(driver_pollset_set_, fd_);

    int phony_release_fd;
    grpc_fd_orphan(fd_, nullptr, &phony_release_fd, "c-ares query finished");
  }

  void RegisterForOnReadableLocked(grpc_closure* read_closure)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) override {
    grpc_fd_notify_on_read(fd_, read_closure);
  }

  void RegisterForOnWriteableLocked(grpc_closure* write_closure)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) override {
    grpc_fd_notify_on_write(fd_, write_closure);
  }

  bool IsFdStillReadableLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) override {
    size_t bytes_available = 0;
    return ioctl(grpc_fd_wrapped_fd(fd_), FIONREAD, &bytes_available) == 0 &&
           bytes_available > 0;
  }

  void ShutdownLocked(grpc_error_handle error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) override {
    grpc_fd_shutdown(fd_, error);
  }

  ares_socket_t GetWrappedAresSocketLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) override {
    return as_;
  }

  const char* GetName() const override { return name_.c_str(); }

 private:
  const std::string name_;
  const ares_socket_t as_;
  grpc_fd* fd_ ABSL_GUARDED_BY(&grpc_ares_request::mu);
  grpc_pollset_set* driver_pollset_set_ ABSL_GUARDED_BY(&grpc_ares_request::mu);
};

class GrpcPolledFdFactoryPosix final : public GrpcPolledFdFactory {
 public:
  ~GrpcPolledFdFactoryPosix() override {
    for (auto& fd : owned_fds_) {
      close(fd);
    }
  }

  GrpcPolledFd* NewGrpcPolledFdLocked(
      ares_socket_t as, grpc_pollset_set* driver_pollset_set) override {
    auto insert_result = owned_fds_.insert(as);
    CHECK(insert_result.second);
    return new GrpcPolledFdPosix(as, driver_pollset_set);
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
    grpc_error_handle err;
    err = grpc_set_socket_nonblocking(fd, true);
    if (!err.ok()) return -1;
    err = grpc_set_socket_cloexec(fd, true);
    if (!err.ok()) return -1;
    if (type == SOCK_STREAM) {
      err = grpc_set_socket_low_latency(fd, true);
      if (!err.ok()) return -1;
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

  std::unordered_set<ares_socket_t> owned_fds_;
};

std::unique_ptr<GrpcPolledFdFactory> NewGrpcPolledFdFactory(Mutex* ) {
  return std::make_unique<GrpcPolledFdFactoryPosix>();
}

}

#endif
