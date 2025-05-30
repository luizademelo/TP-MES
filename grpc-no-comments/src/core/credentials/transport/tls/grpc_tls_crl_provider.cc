
// Copyright 2023 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_crl_provider.h"

#include <grpc/support/port_platform.h>
#include <limits.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include "absl/container/flat_hash_map.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/types/span.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/directory_reader.h"
#include "src/core/util/load_file.h"

namespace grpc_core {
namespace experimental {

namespace {

absl::StatusOr<std::string> IssuerFromCrl(X509_CRL* crl) {
  if (crl == nullptr) {
    return absl::InvalidArgumentError("crl cannot be null");
  }
  X509_NAME* issuer = X509_CRL_get_issuer(crl);
  if (issuer == nullptr) {
    return absl::InvalidArgumentError("crl cannot have null issuer");
  }
  unsigned char* buf = nullptr;
  int len = i2d_X509_NAME(issuer, &buf);
  if (len < 0 || buf == nullptr) {
    return absl::InvalidArgumentError("crl cannot have null issuer");
  }
  std::string ret(reinterpret_cast<char const*>(buf), len);
  OPENSSL_free(buf);
  return ret;
}

absl::StatusOr<std::shared_ptr<Crl>> ReadCrlFromFile(
    const std::string& crl_path) {
  absl::StatusOr<Slice> crl_slice = LoadFile(crl_path, false);
  if (!crl_slice.ok()) {
    return crl_slice.status();
  }
  absl::StatusOr<std::unique_ptr<Crl>> crl =
      Crl::Parse(crl_slice->as_string_view());
  if (!crl.ok()) {
    return crl.status();
  }
  return crl;
}

}

absl::StatusOr<std::unique_ptr<Crl>> Crl::Parse(absl::string_view crl_string) {
  if (crl_string.size() >= INT_MAX) {
    return absl::InvalidArgumentError("crl_string cannot be of size INT_MAX");
  }
  BIO* crl_bio =
      BIO_new_mem_buf(crl_string.data(), static_cast<int>(crl_string.size()));

  if (crl_bio == nullptr) {
    return absl::InvalidArgumentError(
        "Conversion from crl string to BIO failed.");
  }
  X509_CRL* crl = PEM_read_bio_X509_CRL(crl_bio, nullptr, nullptr, nullptr);
  BIO_free(crl_bio);
  if (crl == nullptr) {
    return absl::InvalidArgumentError(
        "Conversion from PEM string to X509 CRL failed.");
  }
  return CrlImpl::Create(crl);
}

absl::StatusOr<std::unique_ptr<CrlImpl>> CrlImpl::Create(X509_CRL* crl) {
  absl::StatusOr<std::string> issuer = IssuerFromCrl(crl);
  if (!issuer.ok()) {
    return issuer.status();
  }
  return std::make_unique<CrlImpl>(crl, *issuer);
}

CrlImpl::~CrlImpl() { X509_CRL_free(crl_); }

absl::StatusOr<std::shared_ptr<CrlProvider>> CreateStaticCrlProvider(
    absl::Span<const std::string> crls) {
  absl::flat_hash_map<std::string, std::shared_ptr<Crl>> crl_map;
  for (const auto& raw_crl : crls) {
    absl::StatusOr<std::unique_ptr<Crl>> crl = Crl::Parse(raw_crl);
    if (!crl.ok()) {
      return absl::InvalidArgumentError(absl::StrCat(
          "Parsing crl string failed with result ", crl.status().ToString()));
    }
    bool inserted = crl_map.emplace((*crl)->Issuer(), std::move(*crl)).second;
    if (!inserted) {
      LOG(ERROR) << "StaticCrlProvider received multiple CRLs with the same "
                    "issuer. The first one in the span will be used.";
    }
  }
  StaticCrlProvider provider = StaticCrlProvider(std::move(crl_map));
  return std::make_shared<StaticCrlProvider>(std::move(provider));
}

std::shared_ptr<Crl> StaticCrlProvider::GetCrl(
    const CertificateInfo& certificate_info) {
  auto it = crls_.find(certificate_info.Issuer());
  if (it == crls_.end()) {
    return nullptr;
  }
  return it->second;
}

absl::StatusOr<std::shared_ptr<CrlProvider>> CreateDirectoryReloaderCrlProvider(
    absl::string_view directory, std::chrono::seconds refresh_duration,
    std::function<void(absl::Status)> reload_error_callback) {
  if (refresh_duration < std::chrono::seconds(60)) {
    return absl::InvalidArgumentError("Refresh duration minimum is 60 seconds");
  }
  auto provider = std::make_shared<DirectoryReloaderCrlProvider>(
      refresh_duration, reload_error_callback, nullptr,
      MakeDirectoryReader(directory));

  provider->UpdateAndStartTimer();
  return provider;
}

DirectoryReloaderCrlProvider::DirectoryReloaderCrlProvider(
    std::chrono::seconds duration, std::function<void(absl::Status)> callback,
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine,
    std::shared_ptr<DirectoryReader> directory_impl)
    : refresh_duration_(Duration::FromSecondsAsDouble(duration.count())),
      reload_error_callback_(std::move(callback)),
      crl_directory_(std::move(directory_impl)) {

  grpc_init();
  if (event_engine == nullptr) {
    event_engine_ = grpc_event_engine::experimental::GetDefaultEventEngine();
  } else {
    event_engine_ = std::move(event_engine);
  }
}

DirectoryReloaderCrlProvider::~DirectoryReloaderCrlProvider() {
  if (refresh_handle_.has_value()) {
    event_engine_->Cancel(refresh_handle_.value());
  }

  grpc_shutdown();
}

void DirectoryReloaderCrlProvider::UpdateAndStartTimer() {
  absl::Status status = Update();
  if (!status.ok() && reload_error_callback_ != nullptr) {
    reload_error_callback_(status);
  }
  std::weak_ptr<DirectoryReloaderCrlProvider> self = shared_from_this();
  refresh_handle_ =
      event_engine_->RunAfter(refresh_duration_, [self = std::move(self)]() {
        ExecCtx exec_ctx;
        if (std::shared_ptr<DirectoryReloaderCrlProvider> valid_ptr =
                self.lock()) {
          valid_ptr->UpdateAndStartTimer();
        }
      });
}

absl::Status DirectoryReloaderCrlProvider::Update() {
  absl::flat_hash_map<std::string, std::shared_ptr<Crl>> new_crls;
  std::vector<std::string> files_with_errors;
  absl::Status status = crl_directory_->ForEach([&](absl::string_view file) {
    std::string file_path = absl::StrCat(crl_directory_->Name(), "/", file);

    absl::StatusOr<std::shared_ptr<Crl>> crl = ReadCrlFromFile(file_path);
    if (!crl.ok()) {
      files_with_errors.push_back(
          absl::StrCat(file_path, ": ", crl.status().ToString()));
      return;
    }

    std::string issuer((*crl)->Issuer());
    new_crls[std::move(issuer)] = std::move(*crl);
  });
  if (!status.ok()) {
    return status;
  }
  MutexLock lock(&mu_);
  if (!files_with_errors.empty()) {

    for (auto& kv : new_crls) {
      std::shared_ptr<Crl>& crl = kv.second;

      std::string issuer(crl->Issuer());
      crls_[std::move(issuer)] = std::move(crl);
    }
    return absl::UnknownError(absl::StrCat(
        "Errors reading the following files in the CRL directory: [",
        absl::StrJoin(files_with_errors, "; "), "]"));
  } else {
    crls_ = std::move(new_crls);
  }
  return absl::OkStatus();
}

std::shared_ptr<Crl> DirectoryReloaderCrlProvider::GetCrl(
    const CertificateInfo& certificate_info) {
  MutexLock lock(&mu_);
  auto it = crls_.find(certificate_info.Issuer());
  if (it == crls_.end()) {
    return nullptr;
  }
  return it->second;
}

}
}
