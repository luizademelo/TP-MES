Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_SECURITY_CREDENTIALS_H
#define GRPCPP_SECURITY_CREDENTIALS_H

// Include necessary headers for security constants, channels, and other utilities
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
// Function to get OAuth2 access token for testing purposes
std::string GetOauth2AccessToken();
}

// Creates a custom gRPC channel with specified credentials and arguments
std::shared_ptr<Channel> CreateCustomChannel(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args);

namespace experimental {
// Creates a custom gRPC channel with interceptors in addition to credentials and arguments
std::shared_ptr<grpc::Channel> CreateCustomChannelWithInterceptors(
    const grpc::string& target,
    const std::shared_ptr<grpc::ChannelCredentials>& creds,
    const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);
}

// Creates XDS credentials with fallback credentials
std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds);

// Base class for channel credentials
class ChannelCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~ChannelCredentials() override;

 protected:
  // Constructor taking raw gRPC channel credentials
  explicit ChannelCredentials(grpc_channel_credentials* creds);

  // Returns the underlying C credentials object
  grpc_channel_credentials* c_creds() { return c_creds_; }

 private:
  // Friend declarations for functions that need access to private members
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

  // Creates a channel implementation (can be overridden by derived classes)
  virtual std::shared_ptr<Channel> CreateChannelImpl(
      const grpc::string& target, const ChannelArguments& args) {
    return CreateChannelWithInterceptors(target, args, {});
  }

  // Creates a channel with interceptors
  virtual std::shared_ptr<Channel> CreateChannelWithInterceptors(
      const grpc::string& target, const ChannelArguments& args,
      std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>
          interceptor_creators);

  // The underlying C credentials object
  grpc_channel_credentials* const c_creds_;
};

// Base class for call credentials
class CallCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~CallCredentials() override;

  // Applies these credentials to a call
  bool ApplyToCall(grpc_call* call);

  // Returns debug information about these credentials
  grpc::string DebugString();

 protected:
  // Constructor taking raw gRPC call credentials
  explicit CallCredentials(grpc_call_credentials* creds);

 private:
  // Friend declarations for functions that need access to private members
  friend std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
      const std::shared_ptr<ChannelCredentials>& channel_creds,
      const std::shared_ptr<CallCredentials>& call_creds);
  friend class CompositeCallCredentialsImpl;
  friend std::string grpc::testing::GetOauth2AccessToken();

  // The underlying C credentials object
  grpc_call_credentials* c_creds_ = nullptr;
};

// Structure holding SSL credentials options
struct SslCredentialsOptions {
  // PEM-encoded root certificates
  grpc::string pem_root_certs;

  // PEM-encoded private key
  grpc::string pem_private_key;

  // PEM-encoded certificate chain
  grpc::string pem_cert_chain;
};

// Factory functions for various types of credentials:

// Gets Google default credentials
std::shared_ptr<ChannelCredentials> GoogleDefaultCredentials();

// Creates SSL credentials from the given options
std::shared_ptr<ChannelCredentials> SslCredentials(
    const SslCredentialsOptions& options);

// Gets Google Compute Engine credentials
std::shared_ptr<CallCredentials> GoogleComputeEngineCredentials();

// Maximum lifetime for auth tokens (1 hour)
constexpr long kMaxAuthTokenLifetimeSecs = 3600;

// Creates JWT access credentials from a service account JSON key
std::shared_ptr<CallCredentials> ServiceAccountJWTAccessCredentials(
    const grpc::string& json_key,
    long token_lifetime_seconds = kMaxAuthTokenLifetimeSecs);

// Creates credentials from a Google refresh token
std::shared_ptr<CallCredentials> GoogleRefreshTokenCredentials(
    const grpc::string& json_refresh_token);

// Creates credentials from an access token
std::shared_ptr<CallCredentials> AccessTokenCredentials(
    const grpc::string& access_token);

// Creates Google IAM credentials
std::shared_ptr<CallCredentials> GoogleIAMCredentials(
    const grpc::string& authorization_token,
    const grpc::string& authority_selector);

// Combines channel and call credentials
std::shared_ptr<ChannelCredentials> CompositeChannelCredentials(
    const std::shared_ptr<ChannelCredentials>& channel_creds,
    const std::shared_ptr<CallCredentials>& call_creds);

// Combines two call credentials
std::shared_ptr<CallCredentials> CompositeCallCredentials(
    const std::shared_ptr<CallCredentials>& creds1,
    const std::shared_ptr<CallCredentials>& creds2);

// Creates insecure channel credentials (no encryption)
std::shared_ptr<ChannelCredentials> InsecureChannelCredentials();

// Interface for metadata credentials plugins
class MetadataCredentialsPlugin {
 public:
  virtual ~MetadataCredentialsPlugin() {}

  // Whether the plugin is blocking (synchronous)
  virtual bool IsBlocking() const { return true; }

  // Returns the type of the plugin
  virtual const char* GetType() const { return ""; }

  // Gets metadata to be added to calls
  virtual grpc::Status GetMetadata(
      grpc::string_ref service_url, grpc::string_ref method_name,
      const grpc::AuthContext& channel_auth_context,
      std::multimap<grpc::string, grpc::string>* metadata) = 0;

  // Returns debug information about the plugin
  virtual grpc::string DebugString() {
    return "MetadataCredentialsPlugin did not provide a debug string";
  }
};

// Creates call credentials from a metadata plugin
std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin);

// Creates external account credentials
std::shared_ptr<CallCredentials> ExternalAccountCredentials(
    const grpc::string& json_string, const std::vector<grpc::string>& scopes);

namespace experimental {

// Options for STS (Security Token Service) credentials
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

// Parses STS options from JSON
grpc::Status StsCredentialsOptionsFromJson(const std::string& json_string,
                                           StsCredentialsOptions* options);

// Gets STS options from environment variables
grpc::Status StsCredentialsOptionsFromEnv(StsCredentialsOptions* options);

// Creates STS credentials
std::shared_ptr<CallCredentials> StsCredentials(
    const StsCredentialsOptions& options);

// Creates metadata credentials from plugin with minimum security level
std::shared_ptr<CallCredentials> MetadataCredentialsFromPlugin(
    std::unique_ptr<MetadataCredentialsPlugin> plugin,
    grpc_security_level min_security_level);

// Options for ALTS (Application Layer Transport Security) credentials
struct AltsCredentialsOptions {
  // Target service accounts
  std::vector<grpc::string> target_service_accounts;
};

// Creates ALTS credentials
std::shared_ptr<ChannelCredentials> AltsCredentials(
    const AltsCredentialsOptions& options);

// Creates local credentials (for local connections)
std::shared_ptr<ChannelCredentials> LocalCredentials(
    grpc_local_connect_type type);

// Creates TLS credentials
std::shared_ptr<ChannelCredentials> TlsCredentials(
    const TlsChannelCredentialsOptions& options);

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_CREDENTIALS_H
```