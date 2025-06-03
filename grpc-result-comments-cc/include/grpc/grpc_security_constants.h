Here's the commented version of the code:

```c++
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

/* Constants for transport security types */
#define GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME "transport_security_type"
#define GRPC_SSL_TRANSPORT_SECURITY_TYPE "ssl"      // SSL transport security
#define GRPC_TLS_TRANSPORT_SECURITY_TYPE "tls"      // TLS transport security

/* Constants for X.509 certificate properties */
#define GRPC_X509_CN_PROPERTY_NAME "x509_common_name"               // Common Name
#define GRPC_X509_SUBJECT_PROPERTY_NAME "x509_subject"              // Subject
#define GRPC_X509_SAN_PROPERTY_NAME "x509_subject_alternative_name" // Subject Alternative Name
#define GRPC_X509_PEM_CERT_PROPERTY_NAME "x509_pem_cert"            // PEM-encoded certificate

/* Additional security-related properties */
#define GRPC_X509_PEM_CERT_CHAIN_PROPERTY_NAME "x509_pem_cert_chain" // PEM-encoded certificate chain
#define GRPC_SSL_SESSION_REUSED_PROPERTY "ssl_session_reused"        // SSL session reuse flag
#define GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME "security_level" // Security level
#define GRPC_PEER_DNS_PROPERTY_NAME "peer_dns"                       // Peer DNS name
#define GRPC_PEER_SPIFFE_ID_PROPERTY_NAME "peer_spiffe_id"           // Peer SPIFFE ID
#define GRPC_PEER_URI_PROPERTY_NAME "peer_uri"                       // Peer URI
#define GRPC_PEER_EMAIL_PROPERTY_NAME "peer_email"                   // Peer email
#define GRPC_PEER_IP_PROPERTY_NAME "peer_ip"                         // Peer IP address

/* Environment variable for default SSL roots file path */
#define GRPC_DEFAULT_SSL_ROOTS_FILE_PATH_ENV_VAR \
  "GRPC_DEFAULT_SSL_ROOTS_FILE_PATH"

/* Environment variable for Google credentials */
#define GRPC_GOOGLE_CREDENTIALS_ENV_VAR "GOOGLE_APPLICATION_CREDENTIALS"

/* Enum for SSL roots override results */
typedef enum {
  GRPC_SSL_ROOTS_OVERRIDE_OK,                  // Roots override succeeded
  GRPC_SSL_ROOTS_OVERRIDE_FAIL_PERMANENTLY,    // Roots override failed permanently
  GRPC_SSL_ROOTS_OVERRIDE_FAIL                 // Roots override failed
} grpc_ssl_roots_override_result;

/* Enum for SSL certificate config reload status */
typedef enum {
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_UNCHANGED, // Config unchanged
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_NEW,       // New config loaded
  GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_FAIL        // Config reload failed
} grpc_ssl_certificate_config_reload_status;

/* Enum for SSL client certificate request types */
typedef enum {
  GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE,                      // Don't request client cert
  GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_BUT_DONT_VERIFY,           // Request but don't verify
  GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY,                // Request and verify
  GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_BUT_DONT_VERIFY, // Require but don't verify
  GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY     // Require and verify
} grpc_ssl_client_certificate_request_type;

/* Enum for security levels */
typedef enum {
  GRPC_SECURITY_MIN,
  GRPC_SECURITY_NONE = GRPC_SECURITY_MIN,        // No security
  GRPC_INTEGRITY_ONLY,                           // Integrity protection only
  GRPC_PRIVACY_AND_INTEGRITY,                    // Both privacy and integrity
  GRPC_SECURITY_MAX = GRPC_PRIVACY_AND_INTEGRITY,
} grpc_security_level;

/* Enum for local connection types */
typedef enum { 
  UDS = 0,        // Unix Domain Socket
  LOCAL_TCP       // Local TCP connection
} grpc_local_connect_type;

/* Enum for TLS versions */
typedef enum { 
  TLS1_2,         // TLS 1.2
  TLS1_3          // TLS 1.3
} grpc_tls_version;

#ifdef __cplusplus
}
#endif

#endif /* GRPC_GRPC_SECURITY_CONSTANTS_H */
```

The comments added:
1. Grouped and explained related constants
2. Added descriptions for each enum value
3. Explained the purpose of each section
4. Added a closing comment for the header guard
5. Made sure comments are clear and concise while providing necessary context
6. Maintained consistent commenting style throughout

The comments should help developers understand:
- The purpose of each constant and enum
- The security-related properties available
- The different security levels and configurations
- The types of transport security supported
- The certificate verification options