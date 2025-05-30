
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_TEST_CREDENTIALS_PROVIDER_H
#define GRPC_TEST_CPP_UTIL_TEST_CREDENTIALS_PROVIDER_H

#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>

namespace grpc {
namespace testing {

const char kInsecureCredentialsType[] = "INSECURE_CREDENTIALS";

const char kTlsCredentialsType[] = "ssl";
const char kAltsCredentialsType[] = "alts";
const char kGoogleDefaultCredentialsType[] = "google_default_credentials";

class CredentialTypeProvider {
 public:
  virtual ~CredentialTypeProvider() {}

  virtual std::shared_ptr<ChannelCredentials> GetChannelCredentials(
      ChannelArguments* args) = 0;
  virtual std::shared_ptr<ServerCredentials> GetServerCredentials() = 0;
};

class CredentialsProvider {
 public:
  virtual ~CredentialsProvider() {}

  virtual void AddSecureType(
      const std::string& type,
      std::unique_ptr<CredentialTypeProvider> type_provider) = 0;

  virtual std::shared_ptr<ChannelCredentials> GetChannelCredentials(
      const std::string& type, ChannelArguments* args) = 0;

  virtual std::shared_ptr<ServerCredentials> GetServerCredentials(
      const std::string& type) = 0;

  virtual std::vector<std::string> GetSecureCredentialsTypeList() = 0;
};

CredentialsProvider* GetCredentialsProvider();

void SetCredentialsProvider(CredentialsProvider* provider);

}
}

#endif
