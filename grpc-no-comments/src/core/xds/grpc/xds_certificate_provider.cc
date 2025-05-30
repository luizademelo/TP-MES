
// Copyright 2020 gRPC authors.

#include "src/core/xds/grpc/xds_certificate_provider.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <utility>

#include "absl/functional/bind_front.h"
#include "absl/log/check.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/error.h"

namespace grpc_core {

namespace {

class RootCertificatesWatcher final
    : public grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface {
 public:

  explicit RootCertificatesWatcher(
      RefCountedPtr<grpc_tls_certificate_distributor> parent)
      : parent_(std::move(parent)) {}

  void OnCertificatesChanged(std::optional<absl::string_view> root_certs,
                             std::optional<PemKeyCertPairList>
                             ) override {
    if (root_certs.has_value()) {
      parent_->SetKeyMaterials("", std::string(root_certs.value()),
                               std::nullopt);
    }
  }

  void OnError(grpc_error_handle root_cert_error,
               grpc_error_handle ) override {
    if (!root_cert_error.ok()) {
      parent_->SetErrorForCert("", root_cert_error ,
                               std::nullopt);
    }
  }

 private:
  RefCountedPtr<grpc_tls_certificate_distributor> parent_;
};

class IdentityCertificatesWatcher final
    : public grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface {
 public:

  explicit IdentityCertificatesWatcher(
      RefCountedPtr<grpc_tls_certificate_distributor> parent)
      : parent_(std::move(parent)) {}

  void OnCertificatesChanged(
      std::optional<absl::string_view> ,
      std::optional<PemKeyCertPairList> key_cert_pairs) override {
    if (key_cert_pairs.has_value()) {
      parent_->SetKeyMaterials("", std::nullopt, key_cert_pairs);
    }
  }

  void OnError(grpc_error_handle ,
               grpc_error_handle identity_cert_error) override {
    if (!identity_cert_error.ok()) {
      parent_->SetErrorForCert("", std::nullopt,
                               identity_cert_error );
    }
  }

 private:
  RefCountedPtr<grpc_tls_certificate_distributor> parent_;
};

}

XdsCertificateProvider::XdsCertificateProvider(
    RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
    absl::string_view root_cert_name, bool use_system_root_certs,
    RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
    absl::string_view identity_cert_name,
    std::vector<StringMatcher> san_matchers)
    : distributor_(MakeRefCounted<grpc_tls_certificate_distributor>()),
      root_cert_provider_(std::move(root_cert_provider)),
      root_cert_name_(root_cert_name),
      use_system_root_certs_(use_system_root_certs),
      identity_cert_provider_(std::move(identity_cert_provider)),
      identity_cert_name_(identity_cert_name),
      san_matchers_(std::move(san_matchers)),
      require_client_certificate_(false) {
  distributor_->SetWatchStatusCallback(
      absl::bind_front(&XdsCertificateProvider::WatchStatusCallback, this));
}

XdsCertificateProvider::XdsCertificateProvider(
    RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
    absl::string_view root_cert_name,
    RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
    absl::string_view identity_cert_name, bool require_client_certificate)
    : distributor_(MakeRefCounted<grpc_tls_certificate_distributor>()),
      root_cert_provider_(std::move(root_cert_provider)),
      root_cert_name_(root_cert_name),
      identity_cert_provider_(std::move(identity_cert_provider)),
      identity_cert_name_(identity_cert_name),
      require_client_certificate_(require_client_certificate) {
  distributor_->SetWatchStatusCallback(
      absl::bind_front(&XdsCertificateProvider::WatchStatusCallback, this));
}

XdsCertificateProvider::~XdsCertificateProvider() {
  distributor_->SetWatchStatusCallback(nullptr);
}

UniqueTypeName XdsCertificateProvider::type() const {
  static UniqueTypeName::Factory kFactory("Xds");
  return kFactory.Create();
}

void XdsCertificateProvider::WatchStatusCallback(std::string cert_name,
                                                 bool root_being_watched,
                                                 bool identity_being_watched) {
  if (!cert_name.empty()) {
    if (root_being_watched) {
      distributor_->SetErrorForCert(
          cert_name,
          GRPC_ERROR_CREATE(
              "No certificate provider available for root certificates"),
          std::nullopt);
    }
    if (identity_being_watched) {
      distributor_->SetErrorForCert(
          cert_name, std::nullopt,
          GRPC_ERROR_CREATE(
              "No certificate provider available for identity certificates"));
    }
    return;
  }

  if (root_being_watched && root_cert_watcher_ == nullptr) {

    if (root_cert_provider_ == nullptr) {
      distributor_->SetErrorForCert(
          cert_name,
          GRPC_ERROR_CREATE(
              "No certificate provider available for root certificates"),
          std::nullopt);
    } else {
      auto watcher = std::make_unique<RootCertificatesWatcher>(distributor_);
      root_cert_watcher_ = watcher.get();
      root_cert_provider_->distributor()->WatchTlsCertificates(
          std::move(watcher), root_cert_name_, std::nullopt);
    }
  } else if (!root_being_watched && root_cert_watcher_ != nullptr) {

    CHECK(root_cert_provider_ != nullptr);
    root_cert_provider_->distributor()->CancelTlsCertificatesWatch(
        root_cert_watcher_);
    root_cert_watcher_ = nullptr;
  }
  if (identity_being_watched && identity_cert_watcher_ == nullptr) {

    if (identity_cert_provider_ == nullptr) {
      distributor_->SetErrorForCert(
          cert_name, std::nullopt,
          GRPC_ERROR_CREATE(
              "No certificate provider available for identity certificates"));
    } else {
      auto watcher =
          std::make_unique<IdentityCertificatesWatcher>(distributor_);
      identity_cert_watcher_ = watcher.get();
      identity_cert_provider_->distributor()->WatchTlsCertificates(
          std::move(watcher), std::nullopt, identity_cert_name_);
    }
  } else if (!identity_being_watched && identity_cert_watcher_ != nullptr) {
    CHECK(identity_cert_provider_ != nullptr);
    identity_cert_provider_->distributor()->CancelTlsCertificatesWatch(
        identity_cert_watcher_);
    identity_cert_watcher_ = nullptr;
  }
}

}
