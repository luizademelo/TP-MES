
/*
 *
 * Copyright 2016 gRPC authors.
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

#ifndef GRPC_GRPC_SECURITY_CONSTANTS_H
#define GRPC_GRPC_SECURITY_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME "transport_security_type"
#define GRPC_SSL_TRANSPORT_SECURITY_TYPE "ssl"
#define GRPC_TLS_TRANSPORT_SECURITY_TYPE "tls"

#define GRPC_X509_CN_PROPERTY_NAME "x509_common_name"
#define GRPC_X509_SUBJECT_PROPERTY_NAME "x509_subject"
#define GRPC_X509_SAN_PROPERTY_NAME "x509_subject_alternative_name"
#define GRPC_X509_PEM_CERT_PROPERTY_NAME "x509_pem_cert"

#define GRPC_X509_PEM_CERT_CHAIN_PROPERTY_NAME "x509_pem_cert_chain"
#define GRPC_SSL_SESSION_REUSED_PROPERTY "ssl_session_reused"
#define GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME "security_level"
#define GRPC_PEER_DNS_PROPERTY_NAME "peer_dns"
#define GRPC_PEER_SPIFFE_ID_PROPERTY_NAME "peer_spiffe_id"
#define GRPC_PEER_URI_PROPERTY_NAME "peer_uri"
#define GRPC_PEER_EMAIL_PROPERTY_NAME "peer_email"
#define GRPC_PEER_IP_PROPERTY_NAME "peer_ip"

#define GRPC_DEFAULT_SSL_ROOTS_FILE_PATH_ENV_VAR \
  "GRPC_DEFAULT_SSL_ROOTS_FILE_PATH"

#define GRPC_GOOGLE_CREDENTIALS_ENV_VAR "GOOGLE_APPLICATION_CREDENTIALS"

typedef enum {
  GRPC_SSL_ROOTS_OVERRIDE_OK,
  GRPC_SSL_ROOTS_OVERRIDE_FAIL_PERMANENTLY,
  GRPC_SSL_ROOTS_OVERRIDE_FAIL
} grpc_ssl_roots_override_result;

typedef enum {
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_UNCHANGED,
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_NEW,
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_FAIL
} grpc_ssl_certificate_config_reload_status;

typedef enum {

  GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE,

  GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_BUT_DONT_VERIFY,

  GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY,

  GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_BUT_DONT_VERIFY,

  GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY
} grpc_ssl_client_certificate_request_type;

typedef enum {
  GRPC_SECURITY_MIN,
  GRPC_SECURITY_NONE = GRPC_SECURITY_MIN,
  GRPC_INTEGRITY_ONLY,
  GRPC_PRIVACY_AND_INTEGRITY,
  GRPC_SECURITY_MAX = GRPC_PRIVACY_AND_INTEGRITY,
} grpc_security_level;

typedef enum { UDS = 0, LOCAL_TCP } grpc_local_connect_type;

typedef enum { TLS1_2, TLS1_3 } grpc_tls_version;

#ifdef __cplusplus
}
#endif

#endif
