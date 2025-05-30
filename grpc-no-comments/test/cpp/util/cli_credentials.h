
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_CLI_CREDENTIALS_H
#define GRPC_TEST_CPP_UTIL_CLI_CREDENTIALS_H

#include <grpcpp/security/credentials.h>
#include <grpcpp/support/config.h>

namespace grpc {
namespace testing {

class CliCredentials {
 public:
  virtual ~CliCredentials() {}
  std::shared_ptr<grpc::ChannelCredentials> GetCredentials() const;
  virtual std::string GetCredentialUsage() const;
  virtual std::string GetSslTargetNameOverride() const;

 protected:

  virtual std::string GetDefaultChannelCredsType() const;

  virtual std::string GetDefaultCallCreds() const;

  virtual std::shared_ptr<grpc::ChannelCredentials> GetChannelCredentials()
      const;

  virtual std::shared_ptr<grpc::CallCredentials> GetCallCredentials() const;
};

}
}

#endif
