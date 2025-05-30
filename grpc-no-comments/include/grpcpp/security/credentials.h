
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SECURITY_CREDENTIALS_H
#define GRPCPP_SECURITY_CREDENTIALS_H

#include <grpc/grpc_security_constants.h>
#include <grpcpp/channel.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <map>
#include <memory>
#include <vector>

struct grpc_call;

namespace grpc {
class CallCredentials;
class ChannelCredentials;
namespace testing {
std::string GetOauth2AccessToken();
}

std::shared_ptr<Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args);

namespace experimental {
std::shared_ptr<grpc::Channel> CreateCustomChannelWithInterceptors(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);
}

std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds);

class ChannelCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~ChannelCredentials() override;

 protected:
  explicit ChannelCredentials(grpc_channel_credentials* creds);

  grpc_channel_credentials* c_creds() { return c_creds_; }

 private:
  friend std::shared_ptr<grpc::Channel> CreateCustomChannel(
      const grpc::string& target,
      const std::shared_ptr<grpc::ChannelCredentials>& creds,
      const grpc::ChannelArguments& args);
  friend std::shared_ptr<grpc::Channel>
  grpc::experimental::CreateCustomChannelWithInterceptors(
      const grpc::string& target,
      const std::shared_ptr<grpc::ChannelCredentials>& creds,
      const grpc::ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators);
  friend std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
      const std::shared_ptr<ChannelCredentials>& channel_creds,
      const std::shared_ptr<CallCredentials>& call_creds);
  friend class XdsChannelCredentialsImpl;

  virtual std::shared_ptr<Channel> CreateChannelImpl(
      const grpc::string& target, const ChannelArguments& args) {
    return CreateChannelWithInterceptors(target, args, {});
  }

  virtual std::shared_ptr<Channel> CreateChannelWithInterceptors(
      const grpc::string& target, const ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators);

  grpc_channel_credentials* const c_creds_;
};

class CallCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~CallCredentials() override;

  bool ApplyToCall(grpc_call* call);

  grpc::string DebugString();

 protected:
  explicit CallCredentials(grpc_call_credentials* creds);

 private:
  friend std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
      const std::shared_ptr<ChannelCredentials>& channel_creds,
      const std::shared_ptr<CallCredentials>& call_creds);
  friend class CompositeCallCredentialsImpl;
  friend std::string grpc::testing::GetOauth2AccessToken();

  grpc_call_credentials* c_creds_ = nullptr;
};

struct SslCredentialsOptions {

  grpc::string pem_root_certs;

  grpc::string pem_private_key;

  grpc::string pem_cert_chain;
};

std::shared_ptr<ChannelCredentials> GoogleDefaultCredentials();

std::shared_ptr<ChannelCredentials> SslCredentials(
    const SslCredentialsOptions& options);

std::shared_ptr<CallCredentials> GoogleComputeEngineCredentials();

constexpr long kMaxAuthTokenLifetimeSecs = 3600;

std::shared_ptr<CallCredentials> ServiceAccountJWTAccessCredentials(
    const grpc::string& json_key,
    long token_lifetime_seconds = kMaxAuthTokenLifetimeSecs);

std::shared_ptr<CallCredentials> GoogleRefreshTokenCredentials(
    const grpc::string& json_refresh_token);

std::shared_ptr<CallCredentials> AccessTokenCredentials(
    const grpc::string& access_token);

std::shared_ptr<CallCredentials> GoogleIAMCredentials(
    const grpc::string& authorization_token,
    const grpc::string& authority_selector);

std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
    const std::shared_ptr<ChannelCredentials>& channel_creds,
    const std::shared_ptr<CallCredentials>& call_creds);

std::shared_ptr<CallCredentials> CompositeCallCredentials(
    const std::shared_ptr<CallCredentials>& creds1,
    const std::shared_ptr<CallCredentials>& creds2);

std::shared_ptr<ChannelCredentials> InsecureChannelCredentials();

class MetadataCredentialsPlugin {
 public:
  virtual ~MetadataCredentialsPlugin() {}

  virtual bool IsBlocking() const { return true; }

  virtual const char* GetType() const { return ""; }

  virtual grpc::Status GetMetadata(
      grpc::string_ref service_url, grpc::string_ref method_name,
      const grpc::AuthContext& channel_auth_context,
      std::multimap<grpc::string, grpc::string>* metadata) = 0;

  virtual grpc::string DebugString() {
    return "MetadataCredentialsPlugin did not provide a debug string";
  }
};

std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin);

std::shared_ptr<CallCredentials> ExternalAccountCredentials(
    const grpc::string& json_string, const std::vector<grpc::string>& scopes);

namespace experimental {

struct StsCredentialsOptions {
  grpc::string token_exchange_service_uri;
  grpc::string resource;
  grpc::string audience;
  grpc::string scope;
  grpc::string requested_token_type;
  grpc::string subject_token_path;
  grpc::string subject_token_type;
  grpc::string actor_token_path;
  grpc::string actor_token_type;
};

grpc::Status StsCredentialsOptionsFromJson(const std::string& json_string,
                                           StsCredentialsOptions* options);

grpc::Status StsCredentialsOptionsFromEnv(StsCredentialsOptions* options);

std::shared_ptr<CallCredentials> StsCredentials(
    const StsCredentialsOptions& options);

std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin,
    grpc_security_level min_security_level);

struct AltsCredentialsOptions {

  std::vector<grpc::string> target_service_accounts;
};

std::shared_ptr<ChannelCredentials> AltsCredentials(
    const AltsCredentialsOptions& options);

std::shared_ptr<ChannelCredentials> LocalCredentials(
    grpc_local_connect_type type);

std::shared_ptr<ChannelCredentials> TlsCredentials(
    const TlsChannelCredentialsOptions& options);

}
}

#endif
