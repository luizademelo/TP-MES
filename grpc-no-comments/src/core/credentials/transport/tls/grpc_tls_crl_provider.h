
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CRL_PROVIDER_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CRL_PROVIDER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc_crl_provider.h>
#include <grpc/support/port_platform.h>
#include <openssl/crypto.h>

#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/directory_reader.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {
namespace experimental {

class StaticCrlProvider : public CrlProvider {
 public:

  explicit StaticCrlProvider(
      absl::flat_hash_map<std::string, std::shared_ptr<Crl>> crls)
      : crls_(std::move(crls)) {}
  std::shared_ptr<Crl> GetCrl(const CertificateInfo& certificate_info) override;

 private:
  const absl::flat_hash_map<std::string, std::shared_ptr<Crl>> crls_;
};

class CrlImpl : public Crl {
 public:
  static absl::StatusOr<std::unique_ptr<CrlImpl>> Create(X509_CRL* crl);

  CrlImpl(X509_CRL* crl, absl::string_view issuer)
      : crl_(crl), issuer_(issuer) {}
  ~CrlImpl() override;

  absl::string_view Issuer() override { return issuer_; }

  X509_CRL* crl() const { return crl_; }

 private:
  X509_CRL* crl_;
  const std::string issuer_;
};

class CertificateInfoImpl : public CertificateInfo {
 public:
  explicit CertificateInfoImpl(absl::string_view issuer,
                               absl::string_view authority_key_identifier = "")
      : issuer_(issuer), authority_key_identifier_(authority_key_identifier) {}
  absl::string_view Issuer() const override { return issuer_; }
  absl::string_view AuthorityKeyIdentifier() const override {
    return authority_key_identifier_;
  }

 private:
  const std::string issuer_;
  const std::string authority_key_identifier_;
};

class DirectoryReloaderCrlProvider
    : public CrlProvider,
      public std::enable_shared_from_this<DirectoryReloaderCrlProvider> {
 public:
  DirectoryReloaderCrlProvider(
      std::chrono::seconds duration, std::function<void(absl::Status)> callback,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine,
      std::shared_ptr<DirectoryReader> directory_impl);

  ~DirectoryReloaderCrlProvider() override;
  std::shared_ptr<Crl> GetCrl(const CertificateInfo& certificate_info) override;

  void UpdateAndStartTimer();

 private:

  absl::Status Update();
  Duration refresh_duration_;
  std::function<void(::absl::Status)> reload_error_callback_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  std::shared_ptr<DirectoryReader> crl_directory_;

  Mutex mu_;
  absl::flat_hash_map<::std::string, ::std::shared_ptr<Crl>> crls_
      ABSL_GUARDED_BY(mu_);
  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      refresh_handle_;
};

}
}

#endif