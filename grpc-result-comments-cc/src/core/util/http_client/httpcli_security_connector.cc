Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC and support headers
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <optional>
#include <string>

// Include ABSL (Abseil) libraries for logging and string operations
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

// Include internal gRPC core headers for security and transport functionality
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

namespace {

// Implementation of SSL channel security connector for HTTP client
class grpc_httpcli_ssl_channel_security_connector final
    : public grpc_channel_security_connector {
 public:
  // Constructor takes a secure peer name for certificate verification
  explicit grpc_httpcli_ssl_channel_security_connector(char* secure_peer_name)
      : grpc_channel_security_connector(
            {},  // No URL scheme needed for HTTP client
            nullptr,  // No channel credentials
            nullptr), // No request metadata
        secure_peer_name_(secure_peer_name) {}

  // Destructor cleans up handshaker factory and secure peer name
  ~grpc_httpcli_ssl_channel_security_connector() override {
    if (handshaker_factory_ != nullptr) {
      tsi_ssl_client_handshaker_factory_unref(handshaker_factory_);
    }
    if (secure_peer_name_ != nullptr) {
      gpr_free(secure_peer_name_);
    }
  }

  // Initialize SSL handshaker factory with root certificates
  tsi_result InitHandshakerFactory(const char* pem_root_certs,
                                   const tsi_ssl_root_certs_store* root_store) {
    tsi_ssl_client_handshaker_options options;
    options.pem_root_certs = pem_root_certs;  // PEM encoded root certificates
    options.root_store = root_store;          // Root certificate store
    return tsi_create_ssl_client_handshaker_factory_with_options(
        &options, &handshaker_factory_);
  }

  // Add handshakers to the handshake manager for establishing secure connection
  void add_handshakers(const ChannelArgs& args,
                       grpc_pollset_set* /*interested_parties*/,
                       HandshakeManager* handshake_mgr) override {
    tsi_handshaker* handshaker = nullptr;
    if (handshaker_factory_ != nullptr) {
      tsi_result result = tsi_ssl_client_handshaker_factory_create_handshaker(
          handshaker_factory_, secure_peer_name_, 0, /* network_bio_buf_size */
          0, /* ssl_bio_buf_size */
          args.GetOwnedString(GRPC_ARG_TRANSPORT_PROTOCOLS), &handshaker);
      if (result != TSI_OK) {
        LOG(ERROR) << "Handshaker creation failed with error "
                   << tsi_result_to_string(result);
      }
    }
    handshake_mgr->Add(SecurityHandshakerCreate(handshaker, this, args));
  }

  // Getter for handshaker factory
  tsi_ssl_client_handshaker_factory* handshaker_factory() const {
    return handshaker_factory_;
  }

  // Verify peer certificate matches the expected secure peer name
  void check_peer(tsi_peer peer, grpc_endpoint* /*ep*/,
                  const ChannelArgs& /*args*/,
                  RefCountedPtr<grpc_auth_context>* /*auth_context*/,
                  grpc_closure* on_peer_checked) override {
    grpc_error_handle error;

    if (secure_peer_name_ != nullptr &&
        !tsi_ssl_peer_matches_name(&peer, secure_peer_name_)) {
      error = GRPC_ERROR_CREATE(absl::StrCat("Peer name ", secure_peer_name_,
                                             " is not in peer certificate"));
    }
    ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
    tsi_peer_destruct(&peer);
  }

  // Cancel ongoing peer check (no-op implementation)
  void cancel_check_peer(grpc_closure* /*on_peer_checked*/,
                         grpc_error_handle /*error*/) override {}

  // Compare security connectors based on secure peer name
  int cmp(const grpc_security_connector* other_sc) const override {
    auto* other =
        reinterpret_cast<const grpc_httpcli_ssl_channel_security_connector*>(
            other_sc);
    return strcmp(secure_peer_name_, other->secure_peer_name_);
  }

  // Verify host name during call (always returns success for HTTP client)
  ArenaPromise<absl::Status> CheckCallHost(absl::string_view,
                                           grpc_auth_context*) override {
    return ImmediateOkStatus();
  }

  // Getter for secure peer name
  const char* secure_peer_name() const { return secure_peer_name_; }

 private:
  tsi_ssl_client_handshaker_factory* handshaker_factory_ = nullptr;
  char* secure_peer_name_;  // Expected peer name for certificate verification
};

// Factory function to create HTTP client SSL security connector
RefCountedPtr<grpc_channel_security_connector>
httpcli_ssl_channel_security_connector_create(
    const char* pem_root_certs, const tsi_ssl_root_certs_store* root_store,
    const char* secure_peer_name) {
  // Validate inputs
  if (secure_peer_name != nullptr && pem_root_certs == nullptr) {
    LOG(ERROR) << "Cannot assert a secure peer name without a trust root.";
    return nullptr;
  }
  // Create security connector instance
  RefCountedPtr<grpc_httpcli_ssl_channel_security_connector> c =
      MakeRefCounted<grpc_httpcli_ssl_channel_security_connector>(
          secure_peer_name == nullptr ? nullptr : gpr_strdup(secure_peer_name));
  // Initialize handshaker factory
  tsi_result result = c->InitHandshakerFactory(pem_root_certs, root_store);
  if (result != TSI_OK) {
    LOG(ERROR) << "Handshaker factory creation failed with "
               << tsi_result_to_string(result);
    return nullptr;
  }
  return c;
}

// Implementation of HTTP request SSL credentials
class HttpRequestSSLCredentials : public grpc_channel_credentials {
 public:
  // Create security connector for HTTP requests
  RefCountedPtr<grpc_channel_security_connector> create_security_connector(
      RefCountedPtr<grpc_call_credentials> /*call_creds*/, const char* target,
      ChannelArgs* args) override {
    // Get default root certificates
    const char* pem_root_certs = DefaultSslRootStore::GetPemRootCerts();
    const tsi_ssl_root_certs_store* root_store =
        DefaultSslRootStore::GetRootStore();
    if (root_store == nullptr) {
      LOG(ERROR) << "Could not get default pem root certs.";
      return nullptr;
    }
    // Get target name (either from args or use provided target)
    std::optional<std::string> target_string =
        args->GetOwnedString(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG)
            .value_or(target);
    return httpcli_ssl_channel_security_connector_create(
        pem_root_certs, root_store, target_string->c_str());
  }

  // Create duplicate without call credentials
  RefCountedPtr<grpc_channel_credentials> duplicate_without_call_credentials()
      override {
    return Ref();
  }

  // Get type name for these credentials
  UniqueTypeName type() const override {
    static UniqueTypeName::Factory kFactory("HttpRequestSSL");
    return kFactory.Create();
  }

 private:
  // Comparison implementation (always equal for HTTP SSL credentials)
  int cmp_impl(const grpc_channel_credentials* /*other*/) const override {
    return 0;
  }
};

}  // namespace

// Factory function to create HTTP request SSL credentials
RefCountedPtr<grpc_channel_credentials> CreateHttpRequestSSLCredentials() {
  // Use a static instance since these credentials are stateless
  static auto* creds = new HttpRequestSSLCredentials();
  return creds->Ref();
}

}  // namespace grpc_core
```