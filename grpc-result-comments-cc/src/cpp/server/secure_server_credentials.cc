Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for secure server credentials functionality
#include "src/cpp/server/secure_server_credentials.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <memory>
#include <utility>
#include <vector>

#include "src/cpp/common/secure_auth_context.h"

namespace grpc {

// Destroys the AuthMetadataProcessorAsyncWrapper instance
void AuthMetadataProcessorAsyncWrapper::Destroy(void* wrapper) {
  auto* w = static_cast<AuthMetadataProcessorAsyncWrapper*>(wrapper);
  delete w;
}

// Processes authentication metadata asynchronously
void AuthMetadataProcessorAsyncWrapper::Process(
    void* wrapper, grpc_auth_context* context, const grpc_metadata* md,
    size_t num_md, grpc_process_auth_metadata_done_cb cb, void* user_data) {
  auto* w = static_cast<AuthMetadataProcessorAsyncWrapper*>(wrapper);
  if (!w->processor_) {
    // If no processor is set, immediately callback with success
    cb(user_data, nullptr, 0, nullptr, 0, GRPC_STATUS_OK, nullptr);
    return;
  }
  if (w->processor_->IsBlocking()) {
    // For blocking processors, add to thread pool for async processing
    w->thread_pool_->Add([w, context, md, num_md, cb, user_data] {
      w->AuthMetadataProcessorAsyncWrapper::InvokeProcessor(context, md, num_md,
                                                            cb, user_data);
    });
  } else {
    // For non-blocking processors, invoke directly
    w->InvokeProcessor(context, md, num_md, cb, user_data);
  }
}

// Invokes the actual metadata processor and prepares the response
void AuthMetadataProcessorAsyncWrapper::InvokeProcessor(
    grpc_auth_context* context, const grpc_metadata* md, size_t num_md,
    grpc_process_auth_metadata_done_cb cb, void* user_data) {
  // Convert input metadata to a map
  AuthMetadataProcessor::InputMetadata metadata;
  for (size_t i = 0; i < num_md; i++) {
    metadata.insert(std::pair(StringRefFromSlice(&md[i].key),
                              StringRefFromSlice(&md[i].value)));
  }
  
  // Create secure auth context and output metadata containers
  SecureAuthContext ctx(context);
  AuthMetadataProcessor::OutputMetadata consumed_metadata;
  AuthMetadataProcessor::OutputMetadata response_metadata;

  // Process the metadata
  Status status = processor_->Process(metadata, &ctx, &consumed_metadata,
                                      &response_metadata);

  // Convert consumed metadata to gRPC format
  std::vector<grpc_metadata> consumed_md;
  for (const auto& consumed : consumed_metadata) {
    grpc_metadata md_entry;
    md_entry.key = SliceReferencingString(consumed.first);
    md_entry.value = SliceReferencingString(consumed.second);
    consumed_md.push_back(md_entry);
  }

  // Convert response metadata to gRPC format
  std::vector<grpc_metadata> response_md;
  for (const auto& response : response_metadata) {
    grpc_metadata md_entry;
    md_entry.key = SliceReferencingString(response.first);
    md_entry.value = SliceReferencingString(response.second);
    response_md.push_back(md_entry);
  }

  // Prepare data for callback
  auto consumed_md_data = consumed_md.empty() ? nullptr : &consumed_md[0];
  auto response_md_data = response_md.empty() ? nullptr : &response_md[0];
  
  // Invoke callback with results
  cb(user_data, consumed_md_data, consumed_md.size(), response_md_data,
     response_md.size(), static_cast<grpc_status_code>(status.error_code()),
     status.error_message().c_str());
}

// Constructor for SecureServerCredentials
SecureServerCredentials::SecureServerCredentials(grpc_server_credentials* creds)
    : ServerCredentials(creds) {}

// Sets the auth metadata processor for these credentials
void SecureServerCredentials::SetAuthMetadataProcessor(
    const std::shared_ptr<grpc::AuthMetadataProcessor>& processor) {
  auto* wrapper = new grpc::AuthMetadataProcessorAsyncWrapper(processor);
  grpc_server_credentials_set_auth_metadata_processor(
      c_creds(), {grpc::AuthMetadataProcessorAsyncWrapper::Process,
                  grpc::AuthMetadataProcessorAsyncWrapper::Destroy, wrapper});
}

// Creates SSL server credentials with the given options
std::shared_ptr<ServerCredentials> SslServerCredentials(
    const grpc::SslServerCredentialsOptions& options) {
  // Convert key-cert pairs to gRPC format
  std::vector<grpc_ssl_pem_key_cert_pair> pem_key_cert_pairs;
  for (const auto& key_cert_pair : options.pem_key_cert_pairs) {
    grpc_ssl_pem_key_cert_pair p = {key_cert_pair.private_key.c_str(),
                                    key_cert_pair.cert_chain.c_str()};
    pem_key_cert_pairs.push_back(p);
  }
  
  // Create SSL server credentials
  grpc_server_credentials* c_creds = grpc_ssl_server_credentials_create_ex(
      options.pem_root_certs.empty() ? nullptr : options.pem_root_certs.c_str(),
      pem_key_cert_pairs.empty() ? nullptr : &pem_key_cert_pairs[0],
      pem_key_cert_pairs.size(),
      options.force_client_auth
          ? GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY
          : options.client_certificate_request,
      nullptr);
  return std::shared_ptr<ServerCredentials>(
      new SecureServerCredentials(c_creds));
}

namespace experimental {

// Creates ALTS server credentials
std::shared_ptr<ServerCredentials> AltsServerCredentials(
    const AltsServerCredentialsOptions& ) {
  grpc_alts_credentials_options* c_options =
      grpc_alts_credentials_server_options_create();
  grpc_server_credentials* c_creds =
      grpc_alts_server_credentials_create(c_options);
  grpc_alts_credentials_options_destroy(c_options);
  return std::shared_ptr<ServerCredentials>(
      new SecureServerCredentials(c_creds));
}

// Creates local server credentials for inter-process communication
std::shared_ptr<ServerCredentials> LocalServerCredentials(
    grpc_local_connect_type type) {
  return std::shared_ptr<ServerCredentials>(
      new SecureServerCredentials(grpc_local_server_credentials_create(type)));
}

// Creates TLS server credentials with the given options
std::shared_ptr<ServerCredentials> TlsServerCredentials(
    const grpc::experimental::TlsServerCredentialsOptions& options) {
  grpc_server_credentials* c_creds =
      grpc_tls_server_credentials_create(options.c_credentials_options());
  if (c_creds == nullptr) {
    return nullptr;
  }
  return std::shared_ptr<ServerCredentials>(
      new SecureServerCredentials(c_creds));
}

}  // namespace experimental
}  // namespace grpc
```