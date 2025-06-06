
// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>

#include <string>

#include <grpc/credentials.h>

#include "gmock/gmock.h"
#include "src/core/credentials/transport/xds/xds_credentials.h"
#include "src/core/credentials/transport/tls/grpc_tls_credentials_options.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

TEST(TlsCredentialsOptionsComparatorTest, DifferentCertRequestType) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_cert_request_type(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE);
  options_2->set_cert_request_type(GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentVerifyServerCert) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_verify_server_cert(false);
  options_2->set_verify_server_cert(true);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentMinTlsVersion) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_min_tls_version(grpc_tls_version::TLS1_2);
  options_2->set_min_tls_version(grpc_tls_version::TLS1_3);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentMaxTlsVersion) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_max_tls_version(grpc_tls_version::TLS1_2);
  options_2->set_max_tls_version(grpc_tls_version::TLS1_3);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentCertificateVerifier) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_certificate_verifier(MakeRefCounted<HostNameCertificateVerifier>());
  options_2->set_certificate_verifier(MakeRefCounted<XdsCertificateVerifier>(nullptr));
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentCheckCallHost) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_check_call_host(false);
  options_2->set_check_call_host(true);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentCertificateProvider) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_certificate_provider(MakeRefCounted<StaticDataCertificateProvider>("root_cert_1", PemKeyCertPairList()));
  options_2->set_certificate_provider(MakeRefCounted<StaticDataCertificateProvider>("root_cert_2", PemKeyCertPairList()));
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentWatchRootCert) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_watch_root_cert(false);
  options_2->set_watch_root_cert(true);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentRootCertName) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_root_cert_name("root_cert_name_1");
  options_2->set_root_cert_name("root_cert_name_2");
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentWatchIdentityPair) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_watch_identity_pair(false);
  options_2->set_watch_identity_pair(true);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentIdentityCertName) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_identity_cert_name("identity_cert_name_1");
  options_2->set_identity_cert_name("identity_cert_name_2");
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentTlsSessionKeyLogFilePath) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_tls_session_key_log_file_path("file_path_1");
  options_2->set_tls_session_key_log_file_path("file_path_2");
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentCrlDirectory) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_crl_directory("crl_directory_1");
  options_2->set_crl_directory("crl_directory_2");
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentCrlProvider) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_crl_provider(*experimental::CreateStaticCrlProvider({}));
  options_2->set_crl_provider(*experimental::CreateStaticCrlProvider({}));
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}
TEST(TlsCredentialsOptionsComparatorTest, DifferentSendClientCaListValues) {
  auto* options_1 = grpc_tls_credentials_options_create();
  auto* options_2 = grpc_tls_credentials_options_create();
  options_1->set_send_client_ca_list(false);
  options_2->set_send_client_ca_list(true);
  EXPECT_FALSE(*options_1 == *options_2);
  EXPECT_FALSE(*options_2 == *options_1);
  delete options_1;
  delete options_2;
}

}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
