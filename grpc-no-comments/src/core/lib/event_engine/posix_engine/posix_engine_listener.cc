// Copyright 2022 gRPC Authors

#include <grpc/support/port_platform.h>

#include "src/core/lib/event_engine/posix.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <errno.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_endpoint.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_listener.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/iomgr/socket_mutator.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/strerror.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

PosixEngineListenerImpl::PosixEngineListenerImpl(
    PosixEventEngineWithFdSupport::PosixAcceptCallback on_accept,
    absl::AnyInvocable<void(absl::Status)> on_shutdown,
    const grpc_event_engine::experimental::EndpointConfig& config,
    std::unique_ptr<grpc_event_engine::experimental::MemoryAllocatorFactory>
        memory_allocator_factory,
    PosixEventPoller* poller, std::shared_ptr<EventEngine> engine)
    : poller_(poller),
      options_(TcpOptionsFromEndpointConfig(config)),
      engine_(std::move(engine)),
      acceptors_(this),
      on_accept_(std::move(on_accept)),
      on_shutdown_(std::move(on_shutdown)),
      memory_allocator_factory_(std::move(memory_allocator_factory)) {}

absl::StatusOr<int> PosixEngineListenerImpl::Bind(
    const EventEngine::ResolvedAddress& addr,
    PosixListenerWithFdSupport::OnPosixBindNewFdCallback on_bind_new_fd) {
  grpc_core::MutexLock lock(&this->mu_);
  if (this->started_) {
    return absl::FailedPreconditionError(
        "Listener is already started, ports can no longer be bound");
  }
  EventEngine::ResolvedAddress res_addr = addr;
  EventEngine::ResolvedAddress addr6_v4mapped;
  int requested_port = ResolvedAddressGetPort(res_addr);
  CHECK(addr.size() <= EventEngine::ResolvedAddress::MAX_SIZE_BYTES);
  UnlinkIfUnixDomainSocket(addr);

  for (auto it = acceptors_.begin();
       requested_port == 0 && it != acceptors_.end(); it++) {
    EventEngine::ResolvedAddress sockname_temp;
    socklen_t len = static_cast<socklen_t>(sizeof(struct sockaddr_storage));
    if (0 == getsockname((*it)->Socket().sock.Fd(),
                         const_cast<sockaddr*>(sockname_temp.address()),
                         &len)) {
      int used_port = ResolvedAddressGetPort(sockname_temp);
      if (used_port > 0) {
        requested_port = used_port;
        ResolvedAddressSetPort(res_addr, requested_port);
        break;
      }
    }
  }

  auto used_port = MaybeGetWildcardPortFromAddress(res_addr);

  acceptors_.UpdateOnAppendCallback(std::move(on_bind_new_fd));
  if (used_port.has_value()) {
    requested_port = *used_port;
    return ListenerContainerAddWildcardAddresses(acceptors_, options_,
                                                 requested_port);
  }
  if (ResolvedAddressToV4Mapped(res_addr, &addr6_v4mapped)) {
    res_addr = addr6_v4mapped;
  }

  auto result = CreateAndPrepareListenerSocket(options_, res_addr);
  GRPC_RETURN_IF_ERROR(result.status());
  acceptors_.Append(*result);
  return result->port;
}

void PosixEngineListenerImpl::AsyncConnectionAcceptor::Start() {
  Ref();
  handle_->NotifyOnRead(notify_on_accept_);
}

void PosixEngineListenerImpl::AsyncConnectionAcceptor::NotifyOnAccept(
    absl::Status status) {
  GRPC_TRACE_LOG(event_engine_endpoint, INFO)
      << "Acceptor[" << this << "]: NotifyOnAccept: " << status;
  if (!status.ok()) {

    Unref();
    return;
  }

  for (;;) {
    EventEngine::ResolvedAddress addr;
    memset(const_cast<sockaddr*>(addr.address()), 0, addr.size());
    // Note: If we ever decide to return this address to the user, remember to

    int fd = Accept4(handle_->WrappedFd(), addr, 1, 1);
    if (fd < 0) {
      switch (errno) {
        case EINTR:
          continue;
        case EMFILE:

          LOG_EVERY_N_SEC(ERROR, 1)
              << "File descriptor limit reached. Retrying.";
          handle_->NotifyOnRead(notify_on_accept_);

          if (retry_timer_armed_.exchange(true)) return;

          Ref();
          std::ignore =
              engine_->RunAfter(grpc_core::Duration::Seconds(1), [this]() {
                retry_timer_armed_.store(false);
                if (!handle_->IsHandleShutdown()) {
                  handle_->SetReadable();
                }
                Unref();
              });
          return;
        case EAGAIN:
        case ECONNABORTED:
          handle_->NotifyOnRead(notify_on_accept_);
          return;
        default:
          LOG(ERROR) << "Closing acceptor. Failed accept4: "
                     << grpc_core::StrError(errno);

          Unref();
          return;
      }
    }

    if (addr.address()->sa_family == AF_UNIX) {
      socklen_t len = EventEngine::ResolvedAddress::MAX_SIZE_BYTES;
      if (getpeername(fd, const_cast<sockaddr*>(addr.address()), &len) < 0) {
        auto listener_addr_uri = ResolvedAddressToURI(socket_.addr);
        LOG(ERROR) << "Failed getpeername: " << grpc_core::StrError(errno)
                   << ". Dropping the connection, and continuing "
                      "to listen on "
                   << (listener_addr_uri.ok() ? *listener_addr_uri
                                              : "<unknown>")
                   << ":" << socket_.port;
        close(fd);
        handle_->NotifyOnRead(notify_on_accept_);
        return;
      }
      addr = EventEngine::ResolvedAddress(addr.address(), len);
    }

    PosixSocketWrapper sock(fd);
    (void)sock.SetSocketNoSigpipeIfPossible();
    auto result = sock.ApplySocketMutatorInOptions(
        GRPC_FD_SERVER_CONNECTION_USAGE, listener_->options_);
    if (!result.ok()) {
      LOG(ERROR) << "Closing acceptor. Failed to apply socket mutator: "
                 << result;

      Unref();
      return;
    }

    auto peer_name = ResolvedAddressToURI(addr);
    if (!peer_name.ok()) {
      LOG(ERROR) << "Invalid address: " << peer_name.status();

      Unref();
      return;
    }
    auto endpoint = CreatePosixEndpoint(
        listener_->poller_->CreateHandle(
            fd, *peer_name, listener_->poller_->CanTrackErrors()),
        nullptr, listener_->engine_,

        listener_->memory_allocator_factory_->CreateMemoryAllocator(
            absl::StrCat("endpoint-tcp-server-connection: ", *peer_name)),
        listener_->options_);

    grpc_core::EnsureRunInExecCtx([this, peer_name = std::move(*peer_name),
                                   endpoint = std::move(endpoint)]() mutable {

      listener_->on_accept_(
          handle_->WrappedFd(),
          std::move(endpoint),
          false,

          listener_->memory_allocator_factory_->CreateMemoryAllocator(
              absl::StrCat("on-accept-tcp-server-connection: ", peer_name)),
          nullptr);
    });
  }
  GPR_UNREACHABLE_CODE(return);
}

absl::Status PosixEngineListenerImpl::HandleExternalConnection(
    int listener_fd, int fd, SliceBuffer* pending_data) {
  if (listener_fd < 0) {
    return absl::UnknownError(absl::StrCat(
        "HandleExternalConnection: Invalid listener socket: ", listener_fd));
  }
  if (fd < 0) {
    return absl::UnknownError(
        absl::StrCat("HandleExternalConnection: Invalid peer socket: ", fd));
  }
  PosixSocketWrapper sock(fd);
  (void)sock.SetSocketNoSigpipeIfPossible();
  auto peer_name = sock.PeerAddressString();
  if (!peer_name.ok()) {
    return absl::UnknownError(
        absl::StrCat("HandleExternalConnection: peer not connected: ",
                     peer_name.status().ToString()));
  }
  grpc_core::EnsureRunInExecCtx([this, peer_name = std::move(*peer_name),
                                 pending_data, listener_fd, fd]() mutable {
    auto endpoint = CreatePosixEndpoint(
        poller_->CreateHandle(fd, peer_name,
                                         poller_->CanTrackErrors()),
        nullptr, engine_,

        memory_allocator_factory_->CreateMemoryAllocator(absl::StrCat(
            "external:endpoint-tcp-server-connection: ", peer_name)),
        options_);
    on_accept_(
        listener_fd, std::move(endpoint),
        true,

        memory_allocator_factory_->CreateMemoryAllocator(absl::StrCat(
            "external:on-accept-tcp-server-connection: ", peer_name)),
        pending_data);
  });
  return absl::OkStatus();
}

void PosixEngineListenerImpl::AsyncConnectionAcceptor::Shutdown() {

  handle_->ShutdownHandle(absl::InternalError("Shutting down acceptor"));
  Unref();
}

absl::Status PosixEngineListenerImpl::Start() {
  grpc_core::MutexLock lock(&this->mu_);

  CHECK(!this->started_);
  this->started_ = true;
  for (auto it = acceptors_.begin(); it != acceptors_.end(); it++) {
    (*it)->Start();
  }
  return absl::OkStatus();
}

void PosixEngineListenerImpl::TriggerShutdown() {

  grpc_core::MutexLock lock(&this->mu_);
  for (auto it = acceptors_.begin(); it != acceptors_.end(); it++) {

    (*it)->Shutdown();
  }
}

PosixEngineListenerImpl::~PosixEngineListenerImpl() {

  if (on_shutdown_ != nullptr) {
    on_shutdown_(absl::OkStatus());
  }
}

}

#endif
