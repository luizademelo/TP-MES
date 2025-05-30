
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <gtest/gtest.h>

#include <deque>
#include <list>
#include <string>
#include <thread>

#include "absl/log/check.h"
#include "gmock/gmock.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

namespace grpc_core {

namespace testing {

constexpr const char* kCertName1 = "cert_1_name";
constexpr const char* kCertName2 = "cert_2_name";
constexpr const char* kRootCert1Name = "root_cert_1_name";
constexpr const char* kRootCert1Contents = "root_cert_1_contents";
constexpr const char* kRootCert2Name = "root_cert_2_name";
constexpr const char* kRootCert2Contents = "root_cert_2_contents";
constexpr const char* kIdentityCert1Name = "identity_cert_1_name";
constexpr const char* kIdentityCert1PrivateKey = "identity_private_key_1";
constexpr const char* kIdentityCert1Contents = "identity_cert_1_contents";
constexpr const char* kIdentityCert2Name = "identity_cert_2_name";
constexpr const char* kIdentityCert2PrivateKey = "identity_private_key_2";
constexpr const char* kIdentityCert2Contents = "identity_cert_2_contents";
constexpr const char* kErrorMessage = "error_message";
constexpr const char* kRootErrorMessage = "root_error_message";
constexpr const char* kIdentityErrorMessage = "identity_error_message";

class GrpcTlsCertificateDistributorTest : public ::testing::Test {
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

    std::deque<CredentialInfo> GetCredentialQueue() {

      return std::move(cert_update_queue);
    }
    std::deque<ErrorInfo> GetErrorQueue() {

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

  struct CallbackStatus {
    std::string cert_name;
    bool root_being_watched;
    bool identity_being_watched;
    CallbackStatus(std::string name, bool root_watched, bool identity_watched)
        : cert_name(std::move(name)),
          root_being_watched(root_watched),
          identity_being_watched(identity_watched) {}
    bool operator==(const CallbackStatus& other) const {
      return cert_name == other.cert_name &&
             root_being_watched == other.root_being_watched &&
             identity_being_watched == other.identity_being_watched;
    }
  };

  void SetUp() override {
    distributor_.SetWatchStatusCallback([this](std::string cert_name,
                                               bool root_being_watched,
                                               bool identity_being_watched) {
      callback_queue_.emplace_back(std::move(cert_name), root_being_watched,
                                   identity_being_watched);
    });
  }

  WatcherState* MakeWatcher(std::optional<std::string> root_cert_name,
                            std::optional<std::string> identity_cert_name) {
    MutexLock lock(&mu_);
    watchers_.emplace_back();

    auto watcher =
        std::make_unique<TlsCertificatesTestWatcher>(&watchers_.back());
    distributor_.WatchTlsCertificates(std::move(watcher),
                                      std::move(root_cert_name),
                                      std::move(identity_cert_name));
    return &watchers_.back();
  }

  void CancelWatch(WatcherState* state) {
    MutexLock lock(&mu_);
    distributor_.CancelTlsCertificatesWatch(state->watcher);
    EXPECT_EQ(state->watcher, nullptr);
  }

  std::deque<CallbackStatus> GetCallbackQueue() {

    return std::move(callback_queue_);
  }

  grpc_tls_certificate_distributor distributor_;

  std::list<WatcherState> watchers_;
  std::deque<CallbackStatus> callback_queue_;

  Mutex mu_;
};

TEST_F(GrpcTlsCertificateDistributorTest, BasicCredentialBehaviors) {
  EXPECT_FALSE(distributor_.HasRootCerts(kRootCert1Name));
  EXPECT_FALSE(distributor_.HasKeyCertPairs(kIdentityCert1Name));

  distributor_.SetKeyMaterials(kRootCert1Name, kRootCert1Contents,
                               std::nullopt);
  EXPECT_TRUE(distributor_.HasRootCerts(kRootCert1Name));
  distributor_.SetKeyMaterials(
      kIdentityCert1Name, std::nullopt,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));
  EXPECT_TRUE(distributor_.HasKeyCertPairs(kIdentityCert1Name));

  EXPECT_FALSE(distributor_.HasRootCerts(kRootCert2Name));
  EXPECT_FALSE(distributor_.HasKeyCertPairs(kIdentityCert2Name));
}

TEST_F(GrpcTlsCertificateDistributorTest, UpdateCredentialsOnAnySide) {
  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));
  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));

  distributor_.SetKeyMaterials(kCertName1, kRootCert2Contents, std::nullopt);
  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert2Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));

  distributor_.SetKeyMaterials(
      kCertName1, std::nullopt,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));
  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert2Contents,
          MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents))));
  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateDistributorTest, SameIdentityNameDiffRootName) {

  WatcherState* watcher_state_1 =
      MakeWatcher(kRootCert1Name, kIdentityCert1Name);
  EXPECT_THAT(
      GetCallbackQueue(),
      ::testing::ElementsAre(CallbackStatus(kRootCert1Name, true, false),
                             CallbackStatus(kIdentityCert1Name, false, true)));

  WatcherState* watcher_state_2 =
      MakeWatcher(kRootCert2Name, kIdentityCert1Name);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre(CallbackStatus(
                                      kRootCert2Name, true, false)));

  distributor_.SetKeyMaterials(kRootCert1Name, kRootCert1Contents,
                               std::nullopt);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert1Contents, {})));

  distributor_.SetKeyMaterials(kRootCert2Name, kRootCert2Contents,
                               std::nullopt);

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert2Contents, {})));

  distributor_.SetKeyMaterials(
      kIdentityCert1Name, std::nullopt,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));
  EXPECT_THAT(
      watcher_state_2->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert2Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre(CallbackStatus(
                                      kRootCert1Name, false, false)));

  CancelWatch(watcher_state_2);
  EXPECT_THAT(
      GetCallbackQueue(),
      ::testing::ElementsAre(CallbackStatus(kRootCert2Name, false, false),
                             CallbackStatus(kIdentityCert1Name, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest, SameRootNameDiffIdentityName) {

  WatcherState* watcher_state_1 =
      MakeWatcher(kRootCert1Name, kIdentityCert1Name);
  EXPECT_THAT(
      GetCallbackQueue(),
      ::testing::ElementsAre(CallbackStatus(kRootCert1Name, true, false),
                             CallbackStatus(kIdentityCert1Name, false, true)));

  WatcherState* watcher_state_2 =
      MakeWatcher(kRootCert1Name, kIdentityCert2Name);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre(CallbackStatus(
                                      kIdentityCert2Name, false, true)));

  distributor_.SetKeyMaterials(kRootCert1Name, kRootCert1Contents,
                               std::nullopt);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert1Contents, {})));

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert1Contents, {})));

  distributor_.SetKeyMaterials(
      kIdentityCert1Name, std::nullopt,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));

  distributor_.SetKeyMaterials(
      kIdentityCert2Name, std::nullopt,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));

  EXPECT_THAT(
      watcher_state_2->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents))));

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre(CallbackStatus(
                                      kIdentityCert1Name, false, false)));

  CancelWatch(watcher_state_2);
  EXPECT_THAT(
      GetCallbackQueue(),
      ::testing::ElementsAre(CallbackStatus(kRootCert1Name, false, false),
                             CallbackStatus(kIdentityCert2Name, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest,
       AddAndCancelFirstWatcherForSameRootAndIdentityCertName) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest,
       AddAndCancelFirstWatcherForIdentityCertNameWithRootBeingWatched) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, std::nullopt);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, false)));

  WatcherState* watcher_state_2 = MakeWatcher(std::nullopt, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert1Contents, {})));

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  "", MakeCertKeyPairs(kIdentityCert1PrivateKey,
                                       kIdentityCert1Contents))));

  distributor_.SetKeyMaterials(kCertName1, kRootCert2Contents, std::nullopt);

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert2Contents, {})));

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(), ::testing::ElementsAre());

  distributor_.SetKeyMaterials(
      kCertName1, std::nullopt,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  "", MakeCertKeyPairs(kIdentityCert2PrivateKey,
                                       kIdentityCert2Contents))));
  watcher_state_2->cert_update_queue.clear();

  CancelWatch(watcher_state_2);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, false)));

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest,
       AddAndCancelFirstWatcherForRootCertNameWithIdentityBeingWatched) {

  WatcherState* watcher_state_1 = MakeWatcher(std::nullopt, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, true)));

  WatcherState* watcher_state_2 = MakeWatcher(kCertName1, std::nullopt);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  "", MakeCertKeyPairs(kIdentityCert1PrivateKey,
                                       kIdentityCert1Contents))));

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert1Contents, {})));

  distributor_.SetKeyMaterials(kCertName1, kRootCert2Contents, std::nullopt);

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert2Contents, {})));

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(), ::testing::ElementsAre());

  distributor_.SetKeyMaterials(
      kCertName1, std::nullopt,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(), ::testing::ElementsAre());

  EXPECT_THAT(watcher_state_1->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  "", MakeCertKeyPairs(kIdentityCert2PrivateKey,
                                       kIdentityCert2Contents))));

  CancelWatch(watcher_state_2);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, true)));

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest,
       RemoveAllWatchersForCertNameAndAddAgain) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));
  WatcherState* watcher_state_2 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre());

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  CancelWatch(watcher_state_2);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre());

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, false)));

  WatcherState* watcher_state_3 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert2Contents,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));

  EXPECT_THAT(
      watcher_state_3->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert2Contents,
          MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents))));

  CancelWatch(watcher_state_3);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, false, false)));
}

TEST_F(GrpcTlsCertificateDistributorTest, ResetCallbackToNull) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);
  EXPECT_THAT(GetCallbackQueue(),
              ::testing::ElementsAre(CallbackStatus(kCertName1, true, true)));

  distributor_.SetWatchStatusCallback(nullptr);

  CancelWatch(watcher_state_1);
  EXPECT_THAT(GetCallbackQueue(), ::testing::ElementsAre());
}

TEST_F(GrpcTlsCertificateDistributorTest, SetKeyMaterialsInCallback) {
  distributor_.SetWatchStatusCallback([this](std::string cert_name,
                                             bool ,
                                             bool ) {
    distributor_.SetKeyMaterials(
        cert_name, kRootCert1Contents,
        MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));
  });
  auto verify_function = [this](std::string cert_name) {
    WatcherState* watcher_state_1 = MakeWatcher(cert_name, cert_name);

    EXPECT_THAT(
        watcher_state_1->GetCredentialQueue(),
        ::testing::ElementsAre(CredentialInfo(
            kRootCert1Contents, MakeCertKeyPairs(kIdentityCert1PrivateKey,
                                                 kIdentityCert1Contents))));
    CancelWatch(watcher_state_1);
  };

  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(verify_function, std::to_string(i));
  }
  for (auto& th : threads) {
    th.join();
  }
}

TEST_F(GrpcTlsCertificateDistributorTest, WatchACertInfoWithValidCredentials) {

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  distributor_.SetKeyMaterials(kRootCert2Name, kRootCert2Contents,
                               std::nullopt);

  distributor_.SetKeyMaterials(
      kIdentityCert2Name, std::nullopt,
      MakeCertKeyPairs(kIdentityCert2PrivateKey, kIdentityCert2Contents));

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 = MakeWatcher(kRootCert2Name, std::nullopt);

  EXPECT_THAT(watcher_state_2->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(kRootCert2Contents, {})));

  WatcherState* watcher_state_3 = MakeWatcher(std::nullopt, kIdentityCert2Name);

  EXPECT_THAT(watcher_state_3->GetCredentialQueue(),
              ::testing::ElementsAre(CredentialInfo(
                  "", MakeCertKeyPairs(kIdentityCert2PrivateKey,
                                       kIdentityCert2Contents))));
  CancelWatch(watcher_state_2);
  CancelWatch(watcher_state_3);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForCertForBothRootAndIdentity) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(
                  ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kErrorMessage),
                               std::nullopt);
  EXPECT_THAT(
      watcher_state_1->GetErrorQueue(),
      ::testing::ElementsAre(ErrorInfo(kErrorMessage, kIdentityErrorMessage)));

  distributor_.SetErrorForCert(kCertName1, std::nullopt,
                               GRPC_ERROR_CREATE(kErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kErrorMessage, kErrorMessage)));
  distributor_.CancelTlsCertificatesWatch(watcher_state_1->watcher);
  EXPECT_EQ(watcher_state_1->watcher, nullptr);
}

TEST_F(GrpcTlsCertificateDistributorTest, SetErrorForCertForRootOrIdentity) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, std::nullopt);

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               std::nullopt);
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootErrorMessage, "")));

  distributor_.SetErrorForCert(kCertName1, std::nullopt,
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootErrorMessage, "")));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 = MakeWatcher(std::nullopt, kCertName1);

  distributor_.SetErrorForCert(kCertName1, std::nullopt,
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_2->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kIdentityErrorMessage)));

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               std::nullopt);
  EXPECT_THAT(watcher_state_2->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_2->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kIdentityErrorMessage)));
  CancelWatch(watcher_state_2);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForIdentityNameWithPreexistingErrorForRootName) {

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName2);

  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootErrorMessage, "")));

  distributor_.SetErrorForCert(kCertName2, std::nullopt,
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(
                  ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));
  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForCertForRootNameWithSameNameForIdentityErrored) {

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));

  WatcherState* watcher_state_1 = MakeWatcher(kCertName2, kCertName1);

  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kIdentityErrorMessage)));

  distributor_.SetErrorForCert(kCertName2, GRPC_ERROR_CREATE(kRootErrorMessage),
                               std::nullopt);
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(
                  ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));
  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForIdentityNameWithoutErrorForRootName) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName2);

  EXPECT_THAT(watcher_state_1->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName2, std::nullopt,
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kIdentityErrorMessage)));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 = MakeWatcher(kRootCert1Name, kCertName2);

  EXPECT_THAT(watcher_state_2->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName2, std::nullopt,
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_2->error_queue,
              ::testing::ElementsAre(ErrorInfo("", kIdentityErrorMessage)));
  CancelWatch(watcher_state_2);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForRootNameWithPreexistingErrorForIdentityName) {
  WatcherState* watcher_state_1 = MakeWatcher(kCertName2, kCertName1);

  EXPECT_THAT(watcher_state_1->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName2, GRPC_ERROR_CREATE(kRootErrorMessage),
                               std::nullopt);
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootErrorMessage, "")));
  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 = MakeWatcher(kCertName2, kIdentityCert1Name);

  EXPECT_THAT(watcher_state_2->GetErrorQueue(), ::testing::ElementsAre());

  distributor_.SetErrorForCert(kCertName2, GRPC_ERROR_CREATE(kRootErrorMessage),
                               std::nullopt);
  EXPECT_THAT(watcher_state_2->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kRootErrorMessage, "")));
  CancelWatch(watcher_state_2);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       CancelTheLastWatcherOnAnErroredCertInfo) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(
                  ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));

  CancelWatch(watcher_state_1);

  WatcherState* watcher_state_2 = MakeWatcher(kCertName1, kCertName1);

  EXPECT_THAT(watcher_state_2->GetErrorQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_2);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       WatchErroredCertInfoWithValidCredentialData) {

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(
                  ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));
  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateDistributorTest,
       SetErrorForCertThenSuccessfulCredentialUpdates) {

  distributor_.SetErrorForCert(kCertName1, GRPC_ERROR_CREATE(kRootErrorMessage),
                               GRPC_ERROR_CREATE(kIdentityErrorMessage));

  distributor_.SetKeyMaterials(
      kCertName1, kRootCert1Contents,
      MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents));

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  EXPECT_THAT(
      watcher_state_1->GetCredentialQueue(),
      ::testing::ElementsAre(CredentialInfo(
          kRootCert1Contents,
          MakeCertKeyPairs(kIdentityCert1PrivateKey, kIdentityCert1Contents))));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_1);
}

TEST_F(GrpcTlsCertificateDistributorTest, WatchCertInfoThenInvokeSetError) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, kCertName1);

  WatcherState* watcher_state_2 = MakeWatcher(kRootCert1Name, std::nullopt);

  WatcherState* watcher_state_3 = MakeWatcher(std::nullopt, kIdentityCert1Name);
  distributor_.SetError(GRPC_ERROR_CREATE(kErrorMessage));
  EXPECT_THAT(watcher_state_1->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kErrorMessage, kErrorMessage)));
  EXPECT_THAT(watcher_state_2->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo(kErrorMessage, "")));
  EXPECT_THAT(watcher_state_3->GetErrorQueue(),
              ::testing::ElementsAre(ErrorInfo("", kErrorMessage)));
  CancelWatch(watcher_state_1);
  CancelWatch(watcher_state_2);
  CancelWatch(watcher_state_3);
}

TEST_F(GrpcTlsCertificateDistributorTest, WatchErroredCertInfoBySetError) {

  WatcherState* watcher_state_1 = MakeWatcher(kCertName1, std::nullopt);

  WatcherState* watcher_state_2 = MakeWatcher(std::nullopt, kCertName2);

  distributor_.SetError(GRPC_ERROR_CREATE(kErrorMessage));
  CancelWatch(watcher_state_1);
  CancelWatch(watcher_state_2);

  WatcherState* watcher_state_3 = MakeWatcher(kCertName1, kCertName2);
  EXPECT_THAT(watcher_state_3->GetErrorQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_3);

  WatcherState* watcher_state_4 = MakeWatcher(kCertName2, kCertName1);
  EXPECT_THAT(watcher_state_4->GetErrorQueue(), ::testing::ElementsAre());
  CancelWatch(watcher_state_4);
}

TEST_F(GrpcTlsCertificateDistributorTest, SetErrorForCertInCallback) {
  distributor_.SetWatchStatusCallback([this](std::string cert_name,
                                             bool ,
                                             bool ) {
    this->distributor_.SetErrorForCert(
        cert_name, GRPC_ERROR_CREATE(kRootErrorMessage),
        GRPC_ERROR_CREATE(kIdentityErrorMessage));
  });
  auto verify_function = [this](std::string cert_name) {
    WatcherState* watcher_state_1 = MakeWatcher(cert_name, cert_name);

    EXPECT_THAT(watcher_state_1->GetErrorQueue(),
                ::testing::ElementsAre(
                    ErrorInfo(kRootErrorMessage, kIdentityErrorMessage)));
    CancelWatch(watcher_state_1);
  };

  std::vector<std::thread> threads;
  threads.reserve(1000);
  for (int i = 0; i < 1000; ++i) {
    threads.emplace_back(verify_function, std::to_string(i));
  }
  for (auto& th : threads) {
    th.join();
  }
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
