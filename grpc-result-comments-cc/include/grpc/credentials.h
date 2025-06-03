Here's the commented version of the code:

```c++
/*
 * Copyright 2024 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GRPC_CREDENTIALS_H
#define GRPC_CREDENTIALS_H

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations for credential types
typedef struct grpc_call_credentials grpc_call_credentials;
typedef struct grpc_auth_context grpc_auth_context;

// Creates JWT access credentials from a service account JSON key
GRPCAPI grpc_call_credentials*
grpc_service_account_jwt_access_credentials_create(const char* json_key,
                                                   gpr_timespec token_lifetime,
                                                   void* reserved);

// Creates external account credentials from JSON string and scopes
GRPCAPI grpc_call_credentials* grpc_external_account_credentials_create(
    const char* json_string, const char* scopes_string);

// Creates refresh token credentials from a JSON refresh token
GRPCAPI grpc_call_credentials* grpc_google_refresh_token_credentials_create(
    const char* json_refresh_token, void* reserved);

// Creates access token credentials from an access token
GRPCAPI grpc_call_credentials* grpc_access_token_credentials_create(
    const char* access_token, void* reserved);

// Creates Google IAM credentials from authorization token and authority selector
GRPCAPI grpc_call_credentials* grpc_google_iam_credentials_create(
    const char* authorization_token, const char* authority_selector,
    void* reserved);

// Options for STS (Security Token Service) credentials
typedef struct {
  const char* token_exchange_service_uri;  // STS endpoint URI
  const char* resource;                    // Resource identifier
  const char* audience;                    // Intended audience
  const char* scope;                       // Scope of access
  const char* requested_token_type;        // Type of token requested
  const char* subject_token_path;          // Path to subject token
  const char* subject_token_type;          // Type of subject token
  const char* actor_token_path;            // Path to actor token (optional)
  const char* actor_token_type;            // Type of actor token (optional)
} grpc_sts_credentials_options;

// Creates STS credentials using provided options
GRPCAPI grpc_call_credentials* grpc_sts_credentials_create(
    const grpc_sts_credentials_options* options, void* reserved);

// Context for auth metadata operations
typedef struct {
  const char* service_url;                  // URL of the service
  const char* method_name;                  // Method being called
  const grpc_auth_context* channel_auth_context; // Channel auth context
  void* reserved;                           // Reserved for future use
} grpc_auth_metadata_context;

// Copies auth metadata context from one struct to another
GRPCAPI void grpc_auth_metadata_context_copy(grpc_auth_metadata_context* from,
                                             grpc_auth_metadata_context* to);

// Resets auth metadata context
GRPCAPI void grpc_auth_metadata_context_reset(
    grpc_auth_metadata_context* context);

// Callback for credential plugin metadata operations
typedef void (*grpc_credentials_plugin_metadata_cb)(
    void* user_data, const grpc_metadata* creds_md, size_t num_creds_md,
    grpc_status_code status, const char* error_details);

// Maximum number of synchronous metadata entries for plugins
#define GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX 4

// Structure defining a metadata credentials plugin
typedef struct {
  // Function to get metadata synchronously or asynchronously
  int (*get_metadata)(
      void* state, grpc_auth_metadata_context context,
      grpc_credentials_plugin_metadata_cb cb, void* user_data,
      grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
      size_t* num_creds_md, grpc_status_code* status,
      const char** error_details);

  // Function to get debug string for the plugin
  char* (*debug_string)(void* state);

  // Function to destroy plugin state
  void (*destroy)(void* state);

  void* state;        // Plugin state
  const char* type;   // Plugin type identifier
} grpc_metadata_credentials_plugin;

// Creates call credentials from a metadata plugin
GRPCAPI grpc_call_credentials* grpc_metadata_credentials_create_from_plugin(
    grpc_metadata_credentials_plugin plugin,
    grpc_security_level min_security_level, void* reserved);

// Releases call credentials
GRPCAPI void grpc_call_credentials_release(grpc_call_credentials* creds);

// Creates default Google credentials
GRPCAPI grpc_channel_credentials* grpc_google_default_credentials_create(
    grpc_call_credentials* call_credentials);

// Forward declarations for SSL certificate types
typedef struct grpc_ssl_server_certificate_config
    grpc_ssl_server_certificate_config;

// Structure holding PEM-encoded key/cert pair
typedef struct {
  const char* private_key;  // PEM-encoded private key
  const char* cert_chain;   // PEM-encoded certificate chain
} grpc_ssl_pem_key_cert_pair;

// Creates SSL server certificate configuration
GRPCAPI grpc_ssl_server_certificate_config*
grpc_ssl_server_certificate_config_create(
    const char* pem_root_certs,
    const grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs);

// Destroys SSL server certificate configuration
GRPCAPI void grpc_ssl_server_certificate_config_destroy(
    grpc_ssl_server_certificate_config* config);

// Callback for SSL certificate reloading
typedef grpc_ssl_certificate_config_reload_status (
    *grpc_ssl_server_certificate_config_callback)(
    void* user_data, grpc_ssl_server_certificate_config** config);

// Options for peer verification
typedef struct {
  // Callback to verify peer certificate
  int (*verify_peer_callback)(const char* target_name, const char* peer_pem,
                              void* userdata);
  void* verify_peer_callback_userdata;  // User data for callback
  void (*verify_peer_destruct)(void* userdata);  // Destructor for user data
} verify_peer_options;

// Options for SSL peer verification (duplicate definition)
typedef struct {
  int (*verify_peer_callback)(const char* target_name, const char* peer_pem,
                              void* userdata);
  void* verify_peer_callback_userdata;
  void (*verify_peer_destruct)(void* userdata);
} grpc_ssl_verify_peer_options;

// Creates SSL channel credentials
GRPCAPI grpc_channel_credentials* grpc_ssl_credentials_create(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const verify_peer_options* verify_options, void* reserved);

// Creates SSL channel credentials with extended options
GRPCAPI grpc_channel_credentials* grpc_ssl_credentials_create_ex(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const grpc_ssl_verify_peer_options* verify_options, void* reserved);

// Creates SSL server credentials
GRPCAPI grpc_server_credentials* grpc_ssl_server_credentials_create(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs, int force_client_auth, void* reserved);

// Creates SSL server credentials with extended options
GRPCAPI grpc_server_credentials* grpc_ssl_server_credentials_create_ex(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs,
    grpc_ssl_client_certificate_request_type client_certificate_request,
    void* reserved);

// Forward declaration for SSL server credentials options
typedef struct grpc_ssl_server_credentials_options
    grpc_ssl_server_credentials_options;

// Creates SSL server credentials options using static config
GRPCAPI grpc_ssl_server_credentials_options*
grpc_ssl_server_credentials_create_options_using_config(
    grpc_ssl_client_certificate_request_type client_certificate_request,
    grpc_ssl_server_certificate_config* certificate_config);

// Creates SSL server credentials options using config fetcher
GRPCAPI grpc_ssl_server_credentials_options*
grpc_ssl_server_credentials_create_options_using_config_fetcher(
    grpc_ssl_client_certificate_request_type client_certificate_request,
    grpc_ssl_server_certificate_config_callback cb, void* user_data);

// Destroys SSL server credentials options
GRPCAPI void grpc_ssl_server_credentials_options_destroy(
    grpc_ssl_server_credentials_options* options);

// Creates SSL server credentials from options
GRPCAPI grpc_server_credentials*
grpc_ssl_server_credentials_create_with_options(
    grpc_ssl_server_credentials_options* options);

// Callback for auth metadata processing completion
typedef void (*grpc_process_auth_metadata_done_cb)(
    void* user_data, const grpc_metadata* consumed_md, size_t num_consumed_md,
    const grpc_metadata* response_md, size_t num_response_md,
    grpc_status_code status, const char* error_details);

// Structure defining auth metadata processor
typedef struct {
  // Function to process auth metadata
  void (*process)(void* state, grpc_auth_context* context,
                  const grpc_metadata* md, size_t num_md,
                  grpc_process_auth_metadata_done_cb cb, void* user_data);
  void (*destroy)(void* state);  // Function to destroy processor state
  void* state;                   // Processor state
} grpc_auth_metadata_processor;

// Sets auth metadata processor for server credentials
GRPCAPI void grpc_server_credentials_set_auth_metadata_processor(
    grpc_server_credentials* creds, grpc_auth_metadata_processor processor);

// Creates composite call credentials from two credentials
GRPCAPI grpc_call_credentials* grpc_composite_call_credentials_create(
    grpc_call_credentials* creds1, grpc_call_credentials* creds2,
    void* reserved);

// Creates Google Compute Engine credentials
GRPCAPI grpc_call_credentials* grpc_google_compute_engine_credentials_create(
    void* reserved);

// Creates composite channel credentials
GRPCAPI grpc_channel_credentials* grpc_composite_channel_credentials_create(
    grpc_channel_credentials* channel_creds, grpc_call_credentials* call_creds,
    void* reserved);

// Forward declaration for ALTS credentials options
typedef struct grpc_alts_credentials_options grpc_alts_credentials_options;

// Creates ALTS client credentials options
GRPCAPI grpc_alts_credentials_options*
grpc_alts_credentials_client_options_create(void);

// Creates ALTS server credentials options
GRPCAPI grpc_alts_credentials_options*
grpc_alts_credentials_server_options_create(void);

// Adds target service account to ALTS client options
GRPCAPI void grpc_alts_credentials_client_options_add_target_service_account(
    grpc_alts_credentials_options* options, const char* service_account);

// Destroys ALTS credentials options
GRPCAPI void grpc_alts_credentials_options_destroy(
    grpc_alts_credentials_options* options);

// Creates ALTS channel credentials
GRPCAPI grpc_channel_credentials* grpc_alts_credentials_create(
    const grpc_alts_credentials_options* options);

// Creates ALTS server credentials
GRPCAPI grpc_server_credentials* grpc_alts_server_credentials_create(
    const grpc_alts_credentials_options* options);

// Forward declarations for TLS credentials types
typedef struct grpc_tls_credentials_options grpc_tls_credentials_options;
typedef struct grpc_tls_certificate_provider grpc_tls_certificate_provider;
typedef struct grpc_tls_identity_pairs grpc_tls_identity_pairs;

// Creates TLS identity pairs container
GRPCAPI grpc_tls_identity_pairs* grpc_tls_identity_pairs_create();

// Adds key/cert pair to TLS identity pairs
GRPCAPI void grpc_tls_identity_pairs_add_pair(grpc_tls_identity_pairs* pairs,
                                              const char* private_key,
                                              const char* cert_chain);

// Destroys TLS identity pairs
GRPCAPI void grpc_tls_identity_pairs_destroy(grpc_tls_identity_pairs* pairs);

// Creates static data certificate provider
GRPCAPI grpc_tls_certificate_provider*
grpc_tls_certificate_provider_static_data_create(
    const char* root_certificate, grpc_tls_identity_pairs* pem_key_cert_pairs);

// Creates file watcher certificate provider
GRPCAPI grpc_tls_certificate_provider*
grpc_tls_certificate_provider_file_watcher_create(
    const char* private_key_path, const char* identity_certificate_path,
    const char* root_cert_path, unsigned int refresh_interval_sec);

// Releases certificate provider
GRPCAPI void grpc_tls_certificate_provider_release(
    grpc_tls_certificate_provider* provider);

// Structure for custom certificate verification request
typedef struct grpc_tls_custom_verification_check_request {
  const char* target_name;  // Target hostname

  struct peer_info {
    const char* common_name;  // Certificate common name

    struct san_names {
      char** uri_names;       // URI SANs
      size_t uri_names_size;
      char** dns_names;       // DNS SANs
      size_t dns_names_size;
      char** email_names;     // Email SANs
      size_t email_names_size;
      char** ip_names;        // IP SANs
      size_t ip_names_size;
    } san_names;

    const char* peer_cert;             // Peer certificate
    const char* peer_cert_full_chain;  // Full certificate chain
    const char* verified_root_cert_subject;  // Verified root cert subject
  } peer_info;
} grpc_tls_custom_verification_check_request;

// Callback for custom verification completion
typedef void (*grpc_tls_on_custom_verification_check_done_cb)(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details);

// Forward declaration for TLS certificate verifier
typedef struct grpc_tls_certificate_verifier grpc_tls_certificate_verifier;

// Structure for external TLS certificate verifier
typedef struct grpc_tls_certificate_verifier_external {
  void* user_data;  // User data for verifier

  // Verification function
  int (*verify)(void* user_data,
                grpc_tls_custom_verification_check_request* request,
                grpc_tls_on_custom_verification_check_done_cb callback,
                void* callback_arg, grpc_status_code* sync_status,
                char** sync_error_details);

  // Function to cancel verification
  void (*cancel)(void* user_data,
                 grpc_tls_custom_verification_check_request* request);

  // Destructor function
  void (*destruct)(void* user_data);
} grpc_tls_certificate_verifier_external;

// Creates external certificate verifier
grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_external_create(
    grpc_tls_certificate_verifier_external* external_verifier);

// Creates no-op certificate verifier
grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_no_op_create();

// Creates hostname verifier
grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_host_name_create();

// Releases certificate verifier
void grpc_tls_certificate_verifier_release(
    grpc_tls_certificate_verifier* verifier);

// Performs certificate verification
int grpc_tls_certificate_verifier_verify(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request,
    grpc_tls_on_custom_verification_check_done_cb callback, void* callback_arg,
    grpc_status_code* sync_status, char** sync_error_details);

// Cancels certificate verification
void grpc_tls_certificate_verifier_cancel(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request);

// Creates TLS credentials options
GRPCAPI grpc_tls_credentials_options* grpc_tls_credentials_options_create(void);

// Creates TLS channel credentials
grpc_channel_credentials* grpc_tls_credentials_create(
    grpc_tls_credentials_options* options);

// Creates TLS server credentials
grpc_server_credentials* grpc_tls_server_credentials_create(
    grpc_tls_credentials_options* options);

// Sets minimum TLS version for credentials options
GRPCAPI void grpc_tls_credentials_options_set_min_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version min_tls_version);

// Sets maximum TLS version for credentials options
GRPCAPI void grpc_tls_credentials_options_set_max_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version max_tls_version);