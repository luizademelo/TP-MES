
// Copyright 2023 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_crl_provider.h"

#include <grpc/grpc.h>
#include <grpc/grpc_audit_logging.h>
#include <grpc/grpc_crl_provider.h>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/util/wait_for_single_owner.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"
#include "test/core/tsi/transport_security_test_lib.h"

static constexpr absl::string_view kCrlPath =
    "test/core/tsi/test_creds/crl_data/crls/current.crl";
static constexpr absl::string_view kCrlName = "current.crl";
static constexpr absl::string_view kCrlIntermediateIssuerPath =
    "test/core/tsi/test_creds/crl_data/intermediate_ca.pem";
static constexpr absl::string_view kCrlDirectory =
    "test/core/tsi/test_creds/crl_data/crls";
static constexpr absl::string_view kRootCert =
    "test/core/tsi/test_creds/crl_data/ca.pem";

using ::grpc_core::experimental::CertificateInfoImpl;
using ::grpc_core::experimental::Crl;
using ::grpc_core::experimental::CrlProvider;

namespace grpc_core {
namespace testing {

class FakeDirectoryReader : public DirectoryReader {
 public:
  ~FakeDirectoryReader() override = default;
  absl::Status ForEach(
      absl::FunctionRef<void(absl::string_view)> callback) override {
    if (!files_in_directory_.ok()) {
      return files_in_directory_.status();
    }
    for (const auto& file : *files_in_directory_) {
      callback(file);
    }
    return absl::OkStatus();
  }
  absl::string_view Name() const override { return kCrlDirectory; }

  void SetFilesInDirectory(std::vector<std::string> files) {
    files_in_directory_ = std::move(files);
  }

  void SetStatus(absl::Status status) { files_in_directory_ = status; }

 private:
  absl::StatusOr<std::vector<std::string>> files_in_directory_ =
      std::vector<std::string>();
};

class CrlProviderTest : public ::testing::Test {
 public:
  void SetUp() override {
    std::string pem_cert = GetFileContents(kRootCert.data());
    X509* issuer = ReadPemCert(pem_cert);
    auto base_crl_issuer = IssuerFromCert(issuer);
    ASSERT_EQ(base_crl_issuer.status(), absl::OkStatus());
    base_crl_issuer_ = *base_crl_issuer;
    std::string intermediate_string =
        GetFileContents(kCrlIntermediateIssuerPath.data());
    X509* intermediate_issuer = ReadPemCert(intermediate_string);
    auto intermediate_crl_issuer = IssuerFromCert(intermediate_issuer);
    ASSERT_EQ(intermediate_crl_issuer.status(), absl::OkStatus());
    intermediate_crl_issuer_ = *intermediate_crl_issuer;
    X509_free(issuer);
    X509_free(intermediate_issuer);
  }

  void TearDown() override {}

 protected:
  std::string base_crl_issuer_;
  std::string intermediate_crl_issuer_;
};

class DirectoryReloaderCrlProviderTest : public CrlProviderTest {
 public:
  void SetUp() override {
    CrlProviderTest::SetUp();
    event_engine_ =
        std::make_shared<grpc_event_engine::experimental::FuzzingEventEngine>(
            grpc_event_engine::experimental::FuzzingEventEngine::Options(),
            fuzzing_event_engine::Actions());

    grpc_timer_manager_set_start_threaded(false);
    grpc_init();
  }
  void TearDown() override {
    ExecCtx exec_ctx;
    event_engine_->FuzzingDone();
    exec_ctx.Flush();
    event_engine_->TickUntilIdle();
    WaitForSingleOwner(std::move(event_engine_));
    grpc_shutdown_blocking();
    event_engine_.reset();
  }

 protected:

  absl::StatusOr<std::shared_ptr<CrlProvider>> CreateCrlProvider(
      std::chrono::seconds refresh_duration,
      std::function<void(absl::Status)> reload_error_callback,
      std::shared_ptr<DirectoryReader> directory_reader = nullptr) {
    if (directory_reader == nullptr) directory_reader = directory_reader_;
    auto provider =
        std::make_shared<experimental::DirectoryReloaderCrlProvider>(
            refresh_duration, std::move(reload_error_callback), event_engine_,
            std::move(directory_reader));
    provider->UpdateAndStartTimer();
    return provider;
  }

  absl::StatusOr<std::shared_ptr<CrlProvider>> CreateCrlProvider(
      absl::string_view directory, std::chrono::seconds refresh_duration,
      std::function<void(absl::Status)> reload_error_callback) {
    return CreateCrlProvider(refresh_duration, std::move(reload_error_callback),
                             MakeDirectoryReader(directory));
  }

  std::shared_ptr<FakeDirectoryReader> directory_reader_ =
      std::make_shared<FakeDirectoryReader>();
  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
      event_engine_;
};

TEST_F(CrlProviderTest, CanParseCrl) {
  std::string crl_string = GetFileContents(kCrlPath.data());
  absl::StatusOr<std::shared_ptr<Crl>> crl = Crl::Parse(crl_string);
  ASSERT_TRUE(crl.ok()) << crl.status();
  ASSERT_NE(*crl, nullptr);
  EXPECT_EQ((*crl)->Issuer(), base_crl_issuer_);
}

TEST_F(CrlProviderTest, InvalidFile) {
  std::string crl_string = "INVALID CRL FILE";
  absl::StatusOr<std::shared_ptr<Crl>> crl = Crl::Parse(crl_string);
  EXPECT_EQ(crl.status(),
            absl::InvalidArgumentError(
                "Conversion from PEM string to X509 CRL failed."));
}

TEST_F(CrlProviderTest, StaticCrlProviderLookup) {
  std::vector<std::string> crl_strings = {GetFileContents(kCrlPath.data())};
  absl::StatusOr<std::shared_ptr<CrlProvider>> provider =
      experimental::CreateStaticCrlProvider(crl_strings);
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl cert(base_crl_issuer_);
  auto crl = (*provider)->GetCrl(cert);
  ASSERT_NE(crl, nullptr);
  EXPECT_EQ(crl->Issuer(), base_crl_issuer_);
}

TEST_F(CrlProviderTest, StaticCrlProviderLookupIssuerNotFound) {
  std::vector<std::string> crl_strings = {GetFileContents(kCrlPath.data())};
  absl::StatusOr<std::shared_ptr<CrlProvider>> provider =
      experimental::CreateStaticCrlProvider(crl_strings);
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl bad_cert("BAD CERT");
  auto crl = (*provider)->GetCrl(bad_cert);
  EXPECT_EQ(crl, nullptr);
}

TEST_F(DirectoryReloaderCrlProviderTest, CrlLookupGood) {
  auto provider =
      CreateCrlProvider(kCrlDirectory, std::chrono::seconds(60), nullptr);
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl cert(base_crl_issuer_);
  auto crl = (*provider)->GetCrl(cert);
  ASSERT_NE(crl, nullptr);
  EXPECT_EQ(crl->Issuer(), base_crl_issuer_);
  CertificateInfoImpl intermediate(intermediate_crl_issuer_);
  auto intermediate_crl = (*provider)->GetCrl(intermediate);
  ASSERT_NE(intermediate_crl, nullptr);
  EXPECT_EQ(intermediate_crl->Issuer(), intermediate_crl_issuer_);
}

TEST_F(DirectoryReloaderCrlProviderTest, CrlLookupMissingIssuer) {
  auto provider =
      CreateCrlProvider(kCrlDirectory, std::chrono::seconds(60), nullptr);
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl bad_cert("BAD CERT");
  auto crl = (*provider)->GetCrl(bad_cert);
  ASSERT_EQ(crl, nullptr);
}

TEST_F(DirectoryReloaderCrlProviderTest, ReloadsAndDeletes) {
  const std::chrono::seconds kRefreshDuration(60);
  auto provider = CreateCrlProvider(kRefreshDuration, nullptr);
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl cert(base_crl_issuer_);
  auto should_be_no_crl = (*provider)->GetCrl(cert);
  ASSERT_EQ(should_be_no_crl, nullptr);

  directory_reader_->SetFilesInDirectory({std::string(kCrlName)});
  event_engine_->TickForDuration(kRefreshDuration);
  auto crl = (*provider)->GetCrl(cert);
  ASSERT_NE(crl, nullptr);
  EXPECT_EQ(crl->Issuer(), base_crl_issuer_);

  directory_reader_->SetFilesInDirectory({});
  event_engine_->TickForDuration(kRefreshDuration);
  auto crl_should_be_deleted = (*provider)->GetCrl(cert);
  ASSERT_EQ(crl_should_be_deleted, nullptr);
}

TEST_F(DirectoryReloaderCrlProviderTest, WithCorruption) {
  directory_reader_->SetFilesInDirectory({std::string(kCrlName)});
  const std::chrono::seconds kRefreshDuration(60);
  std::vector<absl::Status> reload_errors;
  std::function<void(absl::Status)> reload_error_callback =
      [&](const absl::Status& status) { reload_errors.push_back(status); };
  auto provider =
      CreateCrlProvider(kRefreshDuration, std::move(reload_error_callback));
  ASSERT_TRUE(provider.ok()) << provider.status();
  CertificateInfoImpl cert(base_crl_issuer_);
  auto crl = (*provider)->GetCrl(cert);
  ASSERT_NE(crl, nullptr);
  EXPECT_EQ(crl->Issuer(), base_crl_issuer_);
  EXPECT_EQ(reload_errors.size(), 0);

  directory_reader_->SetFilesInDirectory({std::string(kRootCert)});
  event_engine_->TickForDuration(kRefreshDuration);
  auto crl_post_update = (*provider)->GetCrl(cert);
  ASSERT_NE(crl_post_update, nullptr);
  EXPECT_EQ(crl_post_update->Issuer(), base_crl_issuer_);
  EXPECT_EQ(reload_errors.size(), 1);
}

TEST_F(DirectoryReloaderCrlProviderTest, WithBadInitialDirectoryStatus) {
  absl::Status status = absl::UnknownError("");
  directory_reader_->SetStatus(status);
  std::vector<absl::Status> reload_errors;
  std::function<void(absl::Status)> reload_error_callback =
      [&](const absl::Status& status) { reload_errors.push_back(status); };
  const std::chrono::seconds kRefreshDuration(60);
  auto provider =
      CreateCrlProvider(kRefreshDuration, reload_error_callback, nullptr);

  ASSERT_TRUE(provider.ok()) << provider.status();
  EXPECT_EQ(reload_errors.size(), 1);
}

TEST(CertificateInfoImplTest, CanFetchValues) {
  experimental::CertificateInfoImpl cert =
      CertificateInfoImpl("issuer", "akid");
  EXPECT_EQ(cert.Issuer(), "issuer");
  EXPECT_EQ(cert.AuthorityKeyIdentifier(), "akid");
}

TEST(CertificateInfoImplTest, NoAkid) {
  experimental::CertificateInfoImpl cert = CertificateInfoImpl("issuer");
  EXPECT_EQ(cert.Issuer(), "issuer");
  EXPECT_EQ(cert.AuthorityKeyIdentifier(), "");
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
