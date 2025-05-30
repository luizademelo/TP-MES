
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_EXTERNAL_CONNECTION_ACCEPTOR_IMPL_H
#define GRPC_SRC_CPP_SERVER_EXTERNAL_CONNECTION_ACCEPTOR_IMPL_H

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <string>

#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/util/sync.h"

namespace grpc {
namespace internal {

class ExternalConnectionAcceptorImpl
    : public std::enable_shared_from_this<ExternalConnectionAcceptorImpl> {
 public:
  ExternalConnectionAcceptorImpl(
      const std::string& name,
      ServerBuilder::experimental_type::ExternalConnectionType type,
      std::shared_ptr<ServerCredentials> creds);

  std::unique_ptr<experimental::ExternalConnectionAcceptor> GetAcceptor();

  void HandleNewConnection(
      experimental::ExternalConnectionAcceptor::NewConnectionParameters* p);

  void Shutdown();

  void Start();

  const char* name() { return name_.c_str(); }

  ServerCredentials* GetCredentials() { return creds_.get(); }

  void SetToChannelArgs(grpc::ChannelArguments* args);

 private:
  const std::string name_;
  std::shared_ptr<ServerCredentials> creds_;
  grpc_core::TcpServerFdHandler* handler_ = nullptr;
  grpc_core::Mutex mu_;
  bool has_acceptor_ = false;
  bool started_ = false;
  bool shutdown_ = false;
};

}
}

#endif
