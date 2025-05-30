
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <gtest/gtest.h>

#include <deque>
#include <list>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "gmock/gmock.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"
#include "src/core/util/tmpfile.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

#define CA_CERT_PATH "src/core/tsi/test_creds/ca.pem"
#define SERVER_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SERVER_KEY_PATH "src/core/tsi/test_creds/server1.key"
#define CA_CERT_PATH_2 "src/core/tsi/test_creds/multi-domain.pem"
#define SERVER_CERT_PATH_2 "src/core/tsi/test_creds/server0.pem"
#define SERVER_KEY_PATH_2 "src/core/tsi/test_creds/server0.key"
#define INVALID_PATH "invalid/path"
#define MALFORMED_CERT_PATH "src/core/tsi/test_creds/malformed-cert.pem"
#define MALFORMED_KEY_PATH "src/core/tsi/test_creds/malformed-key.pem"

namespace grpc_core {

namespace testing {

constexpr const char* kCertName = "cert_name";
constexpr const char* kRootError = "Unable to get latest root certificates.";
constexpr const char* kIdentityError =
    "Unable to get latest identity certificates.";

class GrpcTlsCertificateProviderTest : public ::testing::Test {
 protected:

  class TlsCertificatesTestWatcher;

  struct CredentialInfo {
    std::string root_certs;
    PemKeyCertPairList key_cert_pairs;
    CredentialInfo(std::string root, PemKeyCertPairList key_cert)
        : root_certs(std::move(root)), key_cert_pairs(std::move(key_cert)) {}
    bool operator==(const CredentialInfo& other) const {
      return root_certs == other.root_certs &&
             key_cert_pairs == other.key_cert_pairs;
    }
  };

  struct ErrorInfo {
    std::string root_cert_str;
    std::string identity_cert_str;
    ErrorInfo(std::string root, std::string identity)
        : root_cert_str(std::move(root)),
          identity_cert_str(std::move(identity)) {}
    bool operator==(const ErrorInfo& other) const {
      return root_cert_str == other.root_cert_str &&
             identity_cert_str == other.identity_cert_str;
    }
  };

  struct WatcherState {
    TlsCertificatesTestWatcher* watcher = nullptr;
    std::deque<CredentialInfo> cert_update_queue;
    std::deque<ErrorInfo> error_queue;
    Mutex mu;

    std::deque<CredentialInfo> GetCredentialQueue() {

      MutexLock lock(&mu);
      return std::move(cert_update_queue);
    }
    std::deque<ErrorInfo> GetErrorQueue() {

      MutexLock lock(&mu);
      return std::move(error_queue);
    }
  };

  class TlsCertificatesTestWatcher : public grpc_tls_certificate_distributor::
                                         TlsCertificatesWatcherInterface {
   public:

    explicit TlsCertificatesTestWatcher(WatcherState* state) : state_(state) {
      state_->watcher = this;
    }

    ~TlsCertificatesTestWatcher() override { state_->watcher = nullptr; }

    void OnCertificatesChanged(
        std::optional<absl::string_view> root_certs,
        std::optional<PemKeyCertPairList> key_cert_pairs) override {
      MutexLock lock(&state_->mu);
      std::string updated_root;
      if (root_certs.has_value()) {
        updated_root = std::string(*root_certs);
      }
      PemKeyCertPairList updated_identity;
      if (key_cert_pairs.has_value()) {
        updated_identity = std::move(*key_cert_pairs);
      }
      state_->cert_update_queue.emplace_back(std::move(updated_root),
                                             std::move(updated_identity));
    }

    void OnError(grpc_error_handle root_cert_error,
                 grpc_error_handle identity_cert_error) override {
      MutexLock lock(&state_->mu);
      CHECK(!root_cert_error.ok() || !identity_cert_error.ok());
      std::string root_error_str;
      if (!root_cert_error.ok()) {
        root_error_str = std::string(root_cert_error.message());
      }
      std::string identity_error_str;
      if (!identity_cert_error.ok()) {
        identity_error_str = std::string(identity_cert_error.message());
      }
      state_->error_queue.emplace_back(std::move(root_error_str),
                                       std::move(identity_error_str));
    }

   private:
    WatcherState* state_;
  };

  void SetUp() override {
    root_cert_ = GetFileContents(CA_CERT_PATH);
    cert_chain_ = GetFileContents(SERVER_CERT_PATH);
    private_key_ = GetFileContents(SERVER_KEY_PATH);
    root_cert_2_ = GetFileContents(CA_CERT_PATH_2);
    cert_chain_2_ = GetFileContents(SERVER_CERT_PATH_2);
    private_key_2_ = GetFileContents(SERVER_KEY_PATH_2);
    malformed_cert_ = GetFileContents(MALFORMED_CERT_PATH);
    malformed_key_ = GetFileContents(MALFORMED_KEY_PATH);
  }

  WatcherState* MakeWatcher(
      RefCountedPtr<grpc_tls_certificate_distributor> distributor,
      std::optional<std::string> root_cert_name,
      std::optional<std::string> identity_cert_name) {
    MutexLock lock(&mu_);
    distributor_ = distributor;
    watchers_.emplace_back();

    auto watcher =
        std::make_unique<TlsCertificatesTestWatcher>(&watchers_.back());
    distributor_->WatchTlsCertificates(std::move(watcher),
                                       std::move(root_cert_name),
                                       std::move(identity_cert_name));
    return &watchers_.back();
  }

  void CancelWatch(WatcherState* state) {
    MutexLock lock(&mu_);
    distributor_->CancelTlsCertificatesWatch(state->watcher);
    EXPECT_EQ(state->watcher, nullptr);
  }

  std::string root_cert_;
  std::string private_key_;
  std::string cert_chain_;
  std::string root_cert_2_;
  std::string private_key_2_;
  std::string cert_chain_2_;
  std::string malformed_cert_;
  std::string malformed_key_;
  RefCountedPtr<grpc_tls_certificate_distributor> distributor_;

  std::list<WatcherState> watchers_;

  Mutex mu_;
};

TEST_F(GrpcTlsCertificateProviderTest, StaticDataCertificateProviderCreation) {
  StaticDataCertificateProvider provider(
      root_cert_, MakeCertKeyPairs(private_key_.c_str(), cert_chain_.c_str()));

  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 =
      MakeWatcher(provider.distributor(), kCertName, std::nullopt);
  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(root_cert_, {})));
  CancelWatch(watcher_state_2);

  WatcherState* watcher_state_3 =
      MakeWatcher(provider.distributor(), std::nullopt, kCertName);
  EXPECT_THAT(
      watcher_state_3->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          "", MakeCertKeyPairs(private_key_.c_str(), cert_chain_.c_str()))));
  CancelWatch(watcher_state_3);
}

TEST_F(GrpcTlsCertificateProviderTest,
       StaticDataCertificateProviderWithGoodPathsAndCredentialValidation) {
  StaticDataCertificateProvider provider(
      root_cert_, MakeCertKeyPairs(private_key_.c_str(), cert_chain_.c_str()));
  EXPECT_EQ(provider.ValidateCredentials(), absl::OkStatus());
}

TEST_F(GrpcTlsCertificateProviderTest,
       StaticDataCertificateProviderWithMalformedRootCertificate) {
  StaticDataCertificateProvider provider(
      malformed_cert_,
      MakeCertKeyPairs(private_key_.c_str(), cert_chain_.c_str()));
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::FailedPreconditionError(
                "Failed to parse root certificates as PEM: Invalid PEM."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       StaticDataCertificateProviderWithMalformedIdentityCertificate) {
  StaticDataCertificateProvider provider(
      root_cert_,
      MakeCertKeyPairs(private_key_.c_str(), malformed_cert_.c_str()));
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::FailedPreconditionError(
                "Failed to parse certificate chain as PEM: Invalid PEM."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       StaticDataCertificateProviderWithMalformedIdentityKey) {
  StaticDataCertificateProvider provider(
      root_cert_,
      MakeCertKeyPairs(malformed_key_.c_str(), cert_chain_.c_str()));
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::NotFoundError(
                "Failed to parse private key as PEM: No private key found."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithGoodPaths) {
  FileWatcherCertificateProvider provider(SERVER_KEY_PATH, SERVER_CERT_PATH,
                                          CA_CERT_PATH, 1);

  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 =
      MakeWatcher(provider.distributor(), kCertName, std::nullopt);
  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(root_cert_, {})));
  CancelWatch(watcher_state_2);

  WatcherState* watcher_state_3 =
      MakeWatcher(provider.distributor(), std::nullopt, kCertName);
  EXPECT_THAT(
      watcher_state_3->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          "", MakeCertKeyPairs(private_key_.c_str(), cert_chain_.c_str()))));
  CancelWatch(watcher_state_3);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithGoodPathsAndCredentialValidation) {
  FileWatcherCertificateProvider provider(SERVER_KEY_PATH, SERVER_CERT_PATH,
                                          CA_CERT_PATH, 1);
  EXPECT_EQ(provider.ValidateCredentials(), absl::OkStatus());
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithMalformedRootCertificate) {
  FileWatcherCertificateProvider provider(SERVER_KEY_PATH_2, SERVER_CERT_PATH_2,
                                          MALFORMED_CERT_PATH, 1);
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::FailedPreconditionError(
                "Failed to parse root certificates as PEM: Invalid PEM."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithMalformedIdentityCertificate) {
  FileWatcherCertificateProvider provider(
      SERVER_KEY_PATH_2, MALFORMED_CERT_PATH, CA_CERT_PATH_2, 1);
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::FailedPreconditionError(
                "Failed to parse certificate chain as PEM: Invalid PEM."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithMalformedIdentityKey) {
  FileWatcherCertificateProvider provider(
      MALFORMED_KEY_PATH, SERVER_CERT_PATH_2, CA_CERT_PATH_2, 1);
  EXPECT_EQ(provider.ValidateCredentials(),
            absl::NotFoundError(
                "Failed to parse private key as PEM: No private key found."));
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithBadPaths) {
  FileWatcherCertificateProvider provider(INVALID_PATH, INVALID_PATH,
                                          INVALID_PATH, 1);

  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootError, kIdentityError)));
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 =
      MakeWatcher(provider.distributor(), kCertName, std::nullopt);
  EXPECT_THAT(watcher_state_2->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootError, "")));
  EXPECT_THAT(watcher_state_2->GetCredentialQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_2);

  WatcherState* watcher_state_3 =
      MakeWatcher(provider.distributor(), std::nullopt, kCertName);
  EXPECT_THAT(watcher_state_3->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kIdentityError)));
  EXPECT_THAT(watcher_state_3->GetCredentialQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_3);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderOnBothCertsRefreshed) {

  TmpFile tmp_root_cert(root_cert_);
  TmpFile tmp_identity_key(private_key_);
  TmpFile tmp_identity_cert(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key.name(),
                                          tmp_identity_cert.name(),
                                          tmp_root_cert.name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_root_cert.RewriteFile(root_cert_2_);
  tmp_identity_key.RewriteFile(private_key_2_);
  tmp_identity_cert.RewriteFile(cert_chain_2_);

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_2_, MakeCertKeyPairs(private_key_2_.c_str(),
                                                 cert_chain_2_.c_str()))));

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderOnRootCertsRefreshed) {

  TmpFile tmp_root_cert(root_cert_);
  TmpFile tmp_identity_key(private_key_);
  TmpFile tmp_identity_cert(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key.name(),
                                          tmp_identity_cert.name(),
                                          tmp_root_cert.name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_root_cert.RewriteFile(root_cert_2_);

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_2_, MakeCertKeyPairs(private_key_.c_str(),
                                                 cert_chain_.c_str()))));

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderOnIdentityCertsRefreshed) {

  TmpFile tmp_root_cert(root_cert_);
  TmpFile tmp_identity_key(private_key_);
  TmpFile tmp_identity_cert(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key.name(),
                                          tmp_identity_cert.name(),
                                          tmp_root_cert.name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_identity_key.RewriteFile(private_key_2_);
  tmp_identity_cert.RewriteFile(cert_chain_2_);

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_2_.c_str(),
                                               cert_chain_2_.c_str()))));

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithGoodAtFirstThenDeletedBothCerts) {

  auto tmp_root_cert = std::make_unique<TmpFile>(root_cert_);
  auto tmp_identity_key = std::make_unique<TmpFile>(private_key_);
  auto tmp_identity_cert = std::make_unique<TmpFile>(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key->name(),
                                          tmp_identity_cert->name(),
                                          tmp_root_cert->name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_root_cert.reset();
  tmp_identity_key.reset();
  tmp_identity_cert.reset();

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::Contains(ErrorInfo(kRootError, kIdentityError)));
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithGoodAtFirstThenDeletedRootCerts) {

  auto tmp_root_cert = std::make_unique<TmpFile>(root_cert_);
  TmpFile tmp_identity_key(private_key_);
  TmpFile tmp_identity_cert(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key.name(),
                                          tmp_identity_cert.name(),
                                          tmp_root_cert->name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_root_cert.reset();

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::Contains(ErrorInfo(kRootError, "")));
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderWithGoodAtFirstThenDeletedIdentityCerts) {

  TmpFile tmp_root_cert(root_cert_);
  auto tmp_identity_key = std::make_unique<TmpFile>(private_key_);
  auto tmp_identity_cert = std::make_unique<TmpFile>(cert_chain_);

  FileWatcherCertificateProvider provider(tmp_identity_key->name(),
                                          tmp_identity_cert->name(),
                                          tmp_root_cert.name(), 1);
  WatcherState* watcher_state_1 =
      MakeWatcher(provider.distributor(), kCertName, kCertName);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  root_cert_, MakeCertKeyPairs(private_key_.c_str(),
                                               cert_chain_.c_str()))));

  tmp_identity_key.reset();
  tmp_identity_cert.reset();

  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(2, GPR_TIMESPAN)));

  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::Contains(ErrorInfo("", kIdentityError)));
  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());

  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateProviderTest,
       FileWatcherCertificateProviderTooShortRefreshIntervalIsOverwritten) {
  FileWatcherCertificateProvider provider(SERVER_KEY_PATH, SERVER_CERT_PATH,
                                          CA_CERT_PATH, 0);
  ASSERT_THAT(provider.TestOnlyGetRefreshIntervalSecond(), 1);
}

TEST_F(GrpcTlsCertificateProviderTest, FailedKeyCertMatchOnEmptyPrivateKey) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch("", cert_chain_);
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.status().message(), "Private key string is empty.");
}

TEST_F(GrpcTlsCertificateProviderTest, FailedKeyCertMatchOnEmptyCertificate) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch(private_key_2_, "");
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.status().message(), "Certificate string is empty.");
}

TEST_F(GrpcTlsCertificateProviderTest, FailedKeyCertMatchOnInvalidCertFormat) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch(private_key_2_, "invalid_certificate");
  EXPECT_FALSE(status.ok());
  EXPECT_EQ(status.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.status().message(),
            "Conversion from PEM string to X509 failed.");
}

TEST_F(GrpcTlsCertificateProviderTest,
       FailedKeyCertMatchOnInvalidPrivateKeyFormat) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch("invalid_private_key", cert_chain_2_);
  EXPECT_EQ(status.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(status.status().message(),
            "Conversion from PEM string to EVP_PKEY failed.");
}

TEST_F(GrpcTlsCertificateProviderTest, SuccessfulKeyCertMatch) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch(private_key_2_, cert_chain_2_);
  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(*status);
}

TEST_F(GrpcTlsCertificateProviderTest, FailedKeyCertMatchOnInvalidPair) {
  absl::StatusOr<bool> status =
      PrivateKeyAndCertificateMatch(private_key_2_, cert_chain_);
  EXPECT_TRUE(status.ok());
  EXPECT_FALSE(*status);
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
