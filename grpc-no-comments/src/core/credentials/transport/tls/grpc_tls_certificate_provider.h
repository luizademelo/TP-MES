
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_PROVIDER_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_PROVIDER_H

#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <stdint.h>

#include <map>
#include <optional>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

struct grpc_tls_certificate_provider
    : public grpc_core::RefCounted<grpc_tls_certificate_provider> {
 public:
  virtual grpc_core::RefCountedPtr<grpc_tls_certificate_distributor>
  distributor() const = 0;

  int Compare(const grpc_tls_certificate_provider* other) const {
    CHECK_NE(other, nullptr);
    int r = type().Compare(other->type());
    if (r != 0) return r;
    return CompareImpl(other);
  }

  virtual grpc_core::UniqueTypeName type() const = 0;

  static absl::string_view ChannelArgName();
  static int ChannelArgsCompare(const grpc_tls_certificate_provider* a,
                                const grpc_tls_certificate_provider* b) {
    return a->Compare(b);
  }

 private:

  virtual int CompareImpl(const grpc_tls_certificate_provider* other) const = 0;
};

namespace grpc_core {

class StaticDataCertificateProvider final
    : public grpc_tls_certificate_provider {
 public:
  StaticDataCertificateProvider(std::string root_certificate,
                                PemKeyCertPairList pem_key_cert_pairs);

  ~StaticDataCertificateProvider() override;

  RefCountedPtr<grpc_tls_certificate_distributor> distributor() const override {
    return distributor_;
  }

  UniqueTypeName type() const override;

  absl::Status ValidateCredentials() const;

 private:
  struct WatcherInfo {
    bool root_being_watched = false;
    bool identity_being_watched = false;
  };

  int CompareImpl(const grpc_tls_certificate_provider* other) const override {

    return QsortCompare(static_cast<const grpc_tls_certificate_provider*>(this),
                        other);
  }

  RefCountedPtr<grpc_tls_certificate_distributor> distributor_;
  std::string root_certificate_;
  PemKeyCertPairList pem_key_cert_pairs_;

  Mutex mu_;

  std::map<std::string, WatcherInfo> watcher_info_;
};

class FileWatcherCertificateProvider final
    : public grpc_tls_certificate_provider {
 public:
  FileWatcherCertificateProvider(std::string private_key_path,
                                 std::string identity_certificate_path,
                                 std::string root_cert_path,
                                 int64_t refresh_interval_sec);

  ~FileWatcherCertificateProvider() override;

  RefCountedPtr<grpc_tls_certificate_distributor> distributor() const override {
    return distributor_;
  }

  UniqueTypeName type() const override;

  absl::Status ValidateCredentials() const;

  int64_t TestOnlyGetRefreshIntervalSecond() const;

 private:
  struct WatcherInfo {
    bool root_being_watched = false;
    bool identity_being_watched = false;
  };

  int CompareImpl(const grpc_tls_certificate_provider* other) const override {

    return QsortCompare(static_cast<const grpc_tls_certificate_provider*>(this),
                        other);
  }

  void ForceUpdate();

  std::optional<std::string> ReadRootCertificatesFromFile(
      const std::string& root_cert_full_path);

  std::optional<PemKeyCertPairList> ReadIdentityKeyCertPairFromFiles(
      const std::string& private_key_path,
      const std::string& identity_certificate_path);

  std::string private_key_path_;
  std::string identity_certificate_path_;
  std::string root_cert_path_;
  int64_t refresh_interval_sec_ = 0;

  RefCountedPtr<grpc_tls_certificate_distributor> distributor_;
  Thread refresh_thread_;
  gpr_event shutdown_event_;

  mutable Mutex mu_;

  std::string root_certificate_ ABSL_GUARDED_BY(mu_);
  PemKeyCertPairList pem_key_cert_pairs_ ABSL_GUARDED_BY(mu_);

  std::map<std::string, WatcherInfo> watcher_info_ ABSL_GUARDED_BY(mu_);
};

absl::StatusOr<bool> PrivateKeyAndCertificateMatch(
    absl::string_view private_key, absl::string_view cert_chain);

}

#endif
