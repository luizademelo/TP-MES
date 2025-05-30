
// Copyright 2019 gRPC authors.

#include "src/cpp/server/external_connection_acceptor_impl.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc {
namespace internal {
namespace {

class AcceptorWrapper : public experimental::ExternalConnectionAcceptor {
 public:
  explicit AcceptorWrapper(std::shared_ptr<ExternalConnectionAcceptorImpl> impl)
      : impl_(std::move(impl)) {}
  void HandleNewConnection(NewConnectionParameters* p) override {
    impl_->HandleNewConnection(p);
  }

 private:
  std::shared_ptr<ExternalConnectionAcceptorImpl> impl_;
};
}

ExternalConnectionAcceptorImpl::ExternalConnectionAcceptorImpl(
    const std::string& name,
    ServerBuilder::experimental_type::ExternalConnectionType type,
    std::shared_ptr<ServerCredentials> creds)
    : name_(name), creds_(std::move(creds)) {
  CHECK(type ==
        ServerBuilder::experimental_type::ExternalConnectionType::FROM_FD);
}

std::unique_ptr<experimental::ExternalConnectionAcceptor>
ExternalConnectionAcceptorImpl::GetAcceptor() {
  grpc_core::MutexLock lock(&mu_);
  CHECK(!has_acceptor_);
  has_acceptor_ = true;
  return std::unique_ptr<experimental::ExternalConnectionAcceptor>(
      new AcceptorWrapper(shared_from_this()));
}

void ExternalConnectionAcceptorImpl::HandleNewConnection(
    experimental::ExternalConnectionAcceptor::NewConnectionParameters* p) {
  grpc_core::MutexLock lock(&mu_);
  if (shutdown_ || !started_) {

    LOG(ERROR) << "NOT handling external connection with fd " << p->fd
               << ", started " << started_ << ", shutdown " << shutdown_;
    return;
  }
  if (handler_) {
    handler_->Handle(p->listener_fd, p->fd, p->read_buffer.c_buffer());
  }
}

void ExternalConnectionAcceptorImpl::Shutdown() {
  grpc_core::MutexLock lock(&mu_);
  shutdown_ = true;
}

void ExternalConnectionAcceptorImpl::Start() {
  grpc_core::MutexLock lock(&mu_);
  CHECK(!started_);
  CHECK(has_acceptor_);
  CHECK(!shutdown_);
  started_ = true;
}

void ExternalConnectionAcceptorImpl::SetToChannelArgs(ChannelArguments* args) {
  args->SetPointer(name_, &handler_);
}

}
}
