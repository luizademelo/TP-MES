
/*
 *
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
 *
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

typedef struct grpc_call_credentials grpc_call_credentials;
typedef struct grpc_auth_context grpc_auth_context;

GRPCAPI grpc_call_credentials*
grpc_service_account_jwt_access_credentials_create(const char* json_key,
                                                   gpr_timespec token_lifetime,
                                                   void* reserved);

GRPCAPI grpc_call_credentials* grpc_external_account_credentials_create(
    const char* json_string, const char* scopes_string);

GRPCAPI grpc_call_credentials* grpc_google_refresh_token_credentials_create(
    const char* json_refresh_token, void* reserved);

GRPCAPI grpc_call_credentials* grpc_access_token_credentials_create(
    const char* access_token, void* reserved);

GRPCAPI grpc_call_credentials* grpc_google_iam_credentials_create(
    const char* authorization_token, const char* authority_selector,
    void* reserved);

typedef struct {
  const char* token_exchange_service_uri;
  const char* resource;
  const char* audience;
  const char* scope;
  const char* requested_token_type;
  const char* subject_token_path;
  const char* subject_token_type;
  const char* actor_token_path;
  const char* actor_token_type;
} grpc_sts_credentials_options;

GRPCAPI grpc_call_credentials* grpc_sts_credentials_create(
    const grpc_sts_credentials_options* options, void* reserved);

typedef struct {

  const char* service_url;

  const char* method_name;

  const grpc_auth_context* channel_auth_context;

  void* reserved;
} grpc_auth_metadata_context;

GRPCAPI void grpc_auth_metadata_context_copy(grpc_auth_metadata_context* from,
                                             grpc_auth_metadata_context* to);

GRPCAPI void grpc_auth_metadata_context_reset(
    grpc_auth_metadata_context* context);

typedef void (*grpc_credentials_plugin_metadata_cb)(
    void* user_data, const grpc_metadata* creds_md, size_t num_creds_md,
    grpc_status_code status, const char* error_details);

#define GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX 4

typedef struct {

  int (*get_metadata)(
      void* state, grpc_auth_metadata_context context,
      grpc_credentials_plugin_metadata_cb cb, void* user_data,
      grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
      size_t* num_creds_md, grpc_status_code* status,
      const char** error_details);

  char* (*debug_string)(void* state);

  void (*destroy)(void* state);

  void* state;

  const char* type;
} grpc_metadata_credentials_plugin;

GRPCAPI grpc_call_credentials* grpc_metadata_credentials_create_from_plugin(
    grpc_metadata_credentials_plugin plugin,
    grpc_security_level min_security_level, void* reserved);

GRPCAPI void grpc_call_credentials_release(grpc_call_credentials* creds);

GRPCAPI grpc_channel_credentials* grpc_google_default_credentials_create(
    grpc_call_credentials* call_credentials);

typedef struct grpc_ssl_server_certificate_config
    grpc_ssl_server_certificate_config;

typedef struct {

  const char* private_key;

  const char* cert_chain;
} grpc_ssl_pem_key_cert_pair;

GRPCAPI grpc_ssl_server_certificate_config*
grpc_ssl_server_certificate_config_create(
    const char* pem_root_certs,
    const grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs);

GRPCAPI void grpc_ssl_server_certificate_config_destroy(
    grpc_ssl_server_certificate_config* config);

typedef grpc_ssl_certificate_config_reload_status (
    *grpc_ssl_server_certificate_config_callback)(
    void* user_data, grpc_ssl_server_certificate_config** config);

typedef struct {

  int (*verify_peer_callback)(const char* target_name, const char* peer_pem,
                              void* userdata);

  void* verify_peer_callback_userdata;

  void (*verify_peer_destruct)(void* userdata);
} verify_peer_options;

typedef struct {

  int (*verify_peer_callback)(const char* target_name, const char* peer_pem,
                              void* userdata);

  void* verify_peer_callback_userdata;

  void (*verify_peer_destruct)(void* userdata);
} grpc_ssl_verify_peer_options;

GRPCAPI grpc_channel_credentials* grpc_ssl_credentials_create(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const verify_peer_options* verify_options, void* reserved);

GRPCAPI grpc_channel_credentials* grpc_ssl_credentials_create_ex(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const grpc_ssl_verify_peer_options* verify_options, void* reserved);

GRPCAPI grpc_server_credentials* grpc_ssl_server_credentials_create(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs, int force_client_auth, void* reserved);

GRPCAPI grpc_server_credentials* grpc_ssl_server_credentials_create_ex(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs,
    grpc_ssl_client_certificate_request_type client_certificate_request,
    void* reserved);

typedef struct grpc_ssl_server_credentials_options
    grpc_ssl_server_credentials_options;

GRPCAPI grpc_ssl_server_credentials_options*
grpc_ssl_server_credentials_create_options_using_config(
    grpc_ssl_client_certificate_request_type client_certificate_request,
    grpc_ssl_server_certificate_config* certificate_config);

GRPCAPI grpc_ssl_server_credentials_options*
grpc_ssl_server_credentials_create_options_using_config_fetcher(
    grpc_ssl_client_certificate_request_type client_certificate_request,
    grpc_ssl_server_certificate_config_callback cb, void* user_data);

GRPCAPI void grpc_ssl_server_credentials_options_destroy(
    grpc_ssl_server_credentials_options* options);

GRPCAPI grpc_server_credentials*
grpc_ssl_server_credentials_create_with_options(
    grpc_ssl_server_credentials_options* options);

typedef void (*grpc_process_auth_metadata_done_cb)(
    void* user_data, const grpc_metadata* consumed_md, size_t num_consumed_md,
    const grpc_metadata* response_md, size_t num_response_md,
    grpc_status_code status, const char* error_details);

typedef struct {

  void (*process)(void* state, grpc_auth_context* context,
                  const grpc_metadata* md, size_t num_md,
                  grpc_process_auth_metadata_done_cb cb, void* user_data);
  void (*destroy)(void* state);
  void* state;
} grpc_auth_metadata_processor;

GRPCAPI void grpc_server_credentials_set_auth_metadata_processor(
    grpc_server_credentials* creds, grpc_auth_metadata_processor processor);

GRPCAPI grpc_call_credentials* grpc_composite_call_credentials_create(
    grpc_call_credentials* creds1, grpc_call_credentials* creds2,
    void* reserved);

GRPCAPI grpc_call_credentials* grpc_google_compute_engine_credentials_create(
    void* reserved);

GRPCAPI grpc_channel_credentials* grpc_composite_channel_credentials_create(
    grpc_channel_credentials* channel_creds, grpc_call_credentials* call_creds,
    void* reserved);

typedef struct grpc_alts_credentials_options grpc_alts_credentials_options;

GRPCAPI grpc_alts_credentials_options*
grpc_alts_credentials_client_options_create(void);

GRPCAPI grpc_alts_credentials_options*
grpc_alts_credentials_server_options_create(void);

GRPCAPI void grpc_alts_credentials_client_options_add_target_service_account(
    grpc_alts_credentials_options* options, const char* service_account);

GRPCAPI void grpc_alts_credentials_options_destroy(
    grpc_alts_credentials_options* options);

GRPCAPI grpc_channel_credentials* grpc_alts_credentials_create(
    const grpc_alts_credentials_options* options);

GRPCAPI grpc_server_credentials* grpc_alts_server_credentials_create(
    const grpc_alts_credentials_options* options);

typedef struct grpc_tls_credentials_options grpc_tls_credentials_options;

typedef struct grpc_tls_certificate_provider grpc_tls_certificate_provider;

typedef struct grpc_tls_identity_pairs grpc_tls_identity_pairs;

GRPCAPI grpc_tls_identity_pairs* grpc_tls_identity_pairs_create();

GRPCAPI void grpc_tls_identity_pairs_add_pair(grpc_tls_identity_pairs* pairs,
                                              const char* private_key,
                                              const char* cert_chain);

GRPCAPI void grpc_tls_identity_pairs_destroy(grpc_tls_identity_pairs* pairs);

GRPCAPI grpc_tls_certificate_provider*
grpc_tls_certificate_provider_static_data_create(
    const char* root_certificate, grpc_tls_identity_pairs* pem_key_cert_pairs);

GRPCAPI grpc_tls_certificate_provider*
grpc_tls_certificate_provider_file_watcher_create(
    const char* private_key_path, const char* identity_certificate_path,
    const char* root_cert_path, unsigned int refresh_interval_sec);

GRPCAPI void grpc_tls_certificate_provider_release(
    grpc_tls_certificate_provider* provider);

typedef struct grpc_tls_custom_verification_check_request {

  const char* target_name;

  struct peer_info {

    const char* common_name;

    struct san_names {
      char** uri_names;
      size_t uri_names_size;
      char** dns_names;
      size_t dns_names_size;
      char** email_names;
      size_t email_names_size;
      char** ip_names;
      size_t ip_names_size;
    } san_names;

    const char* peer_cert;

    const char* peer_cert_full_chain;

    const char* verified_root_cert_subject;
  } peer_info;
} grpc_tls_custom_verification_check_request;

typedef void (*grpc_tls_on_custom_verification_check_done_cb)(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details);

typedef struct grpc_tls_certificate_verifier grpc_tls_certificate_verifier;

typedef struct grpc_tls_certificate_verifier_external {
  void* user_data;

  int (*verify)(void* user_data,
                grpc_tls_custom_verification_check_request* request,
                grpc_tls_on_custom_verification_check_done_cb callback,
                void* callback_arg, grpc_status_code* sync_status,
                char** sync_error_details);

  void (*cancel)(void* user_data,
                 grpc_tls_custom_verification_check_request* request);

  void (*destruct)(void* user_data);
} grpc_tls_certificate_verifier_external;

grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_external_create(
    grpc_tls_certificate_verifier_external* external_verifier);

grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_no_op_create();

grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_host_name_create();

void grpc_tls_certificate_verifier_release(
    grpc_tls_certificate_verifier* verifier);

int grpc_tls_certificate_verifier_verify(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request,
    grpc_tls_on_custom_verification_check_done_cb callback, void* callback_arg,
    grpc_status_code* sync_status, char** sync_error_details);

void grpc_tls_certificate_verifier_cancel(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request);

GRPCAPI grpc_tls_credentials_options* grpc_tls_credentials_options_create(void);

grpc_channel_credentials* grpc_tls_credentials_create(
    grpc_tls_credentials_options* options);

grpc_server_credentials* grpc_tls_server_credentials_create(
    grpc_tls_credentials_options* options);

GRPCAPI void grpc_tls_credentials_options_set_min_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version min_tls_version);

GRPCAPI void grpc_tls_credentials_options_set_max_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version max_tls_version);

GRPCAPI grpc_tls_credentials_options* grpc_tls_credentials_options_copy(
    grpc_tls_credentials_options* options);

GRPCAPI void grpc_tls_credentials_options_destroy(
    grpc_tls_credentials_options* options);

typedef struct grpc_tls_certificate_provider grpc_tls_certificate_provider;

GRPCAPI void grpc_tls_credentials_options_set_certificate_provider(
    grpc_tls_credentials_options* options,
    grpc_tls_certificate_provider* provider);

GRPCAPI void grpc_tls_credentials_options_watch_root_certs(
    grpc_tls_credentials_options* options);

GRPCAPI void grpc_tls_credentials_options_set_root_cert_name(
    grpc_tls_credentials_options* options, const char* root_cert_name);

GRPCAPI void grpc_tls_credentials_options_watch_identity_key_cert_pairs(
    grpc_tls_credentials_options* options);

GRPCAPI void grpc_tls_credentials_options_set_identity_cert_name(
    grpc_tls_credentials_options* options, const char* identity_cert_name);

GRPCAPI void grpc_tls_credentials_options_set_cert_request_type(
    grpc_tls_credentials_options* options,
    grpc_ssl_client_certificate_request_type type);

GRPCAPI void grpc_tls_credentials_options_set_crl_directory(
    grpc_tls_credentials_options* options, const char* crl_directory);

GRPCAPI void grpc_tls_credentials_options_set_verify_server_cert(
    grpc_tls_credentials_options* options, int verify_server_cert);

GRPCAPI void grpc_tls_credentials_options_set_send_client_ca_list(
    grpc_tls_credentials_options* options, bool send_client_ca_list);

typedef struct grpc_ssl_session_cache grpc_ssl_session_cache;

GRPCAPI grpc_ssl_session_cache* grpc_ssl_session_cache_create_lru(
    size_t capacity);

GRPCAPI void grpc_ssl_session_cache_destroy(grpc_ssl_session_cache* cache);

GRPCAPI grpc_arg
grpc_ssl_session_cache_create_channel_arg(grpc_ssl_session_cache* cache);

typedef grpc_ssl_roots_override_result (*grpc_ssl_roots_override_callback)(
    char** pem_root_certs);

GRPCAPI void grpc_set_ssl_roots_override_callback(
    grpc_ssl_roots_override_callback cb);

GRPCAPI gpr_timespec grpc_max_auth_token_lifetime(void);

GRPCAPI grpc_channel_credentials* grpc_insecure_credentials_create();

GRPCAPI grpc_server_credentials* grpc_insecure_server_credentials_create();

GRPCAPI grpc_channel_credentials* grpc_xds_credentials_create(
    grpc_channel_credentials* fallback_credentials);

GRPCAPI grpc_server_credentials* grpc_xds_server_credentials_create(
    grpc_server_credentials* fallback_credentials);

GRPCAPI grpc_channel_credentials* grpc_local_credentials_create(
    grpc_local_connect_type type);

GRPCAPI grpc_server_credentials* grpc_local_server_credentials_create(
    grpc_local_connect_type type);

typedef struct grpc_tls_certificate_verifier grpc_tls_certificate_verifier;

void grpc_tls_credentials_options_set_certificate_verifier(
    grpc_tls_credentials_options* options,
    grpc_tls_certificate_verifier* verifier);

GRPCAPI void grpc_tls_credentials_options_set_check_call_host(
    grpc_tls_credentials_options* options, int check_call_host);

GRPCAPI void grpc_tls_credentials_options_set_tls_session_key_log_file_path(
    grpc_tls_credentials_options* options, const char* path);

#ifdef __cplusplus
}
#endif

#endif
