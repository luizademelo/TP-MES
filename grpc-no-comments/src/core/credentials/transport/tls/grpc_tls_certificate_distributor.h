
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_DISTRIBUTOR_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_DISTRIBUTOR_H

#include <grpc/support/port_platform.h>

#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"

struct grpc_tls_identity_pairs {
  grpc_core::PemKeyCertPairList pem_key_cert_pairs;
};

struct grpc_tls_certificate_distributor
    : public grpc_core::RefCounted<grpc_tls_certificate_distributor> {
 public:

  class TlsCertificatesWatcherInterface {
   public:
    virtual ~TlsCertificatesWatcherInterface() = default;

    virtual void OnCertificatesChanged(
        std::optional<absl::string_view> root_certs,
        std::optional<grpc_core::PemKeyCertPairList> key_cert_pairs) = 0;

    virtual void OnError(grpc_error_handle root_cert_error,
                         grpc_error_handle identity_cert_error) = 0;
  };

  void SetKeyMaterials(
      const std::string& cert_name, std::optional<std::string> pem_root_certs,
      std::optional<grpc_core::PemKeyCertPairList> pem_key_cert_pairs);

  bool HasRootCerts(const std::string& root_cert_name);

  bool HasKeyCertPairs(const std::string& identity_cert_name);

  void SetErrorForCert(const std::string& cert_name,
                       std::optional<grpc_error_handle> root_cert_error,
                       std::optional<grpc_error_handle> identity_cert_error);

  void SetError(grpc_error_handle error);

  void SetWatchStatusCallback(
      std::function<void(std::string, bool, bool)> callback) {
    grpc_core::MutexLock lock(&callback_mu_);
    watch_status_callback_ = std::move(callback);
  };

  void WatchTlsCertificates(
      std::unique_ptr<TlsCertificatesWatcherInterface> watcher,
      std::optional<std::string> root_cert_name,
      std::optional<std::string> identity_cert_name);

  void CancelTlsCertificatesWatch(TlsCertificatesWatcherInterface* watcher);

 private:

  struct WatcherInfo {
    std::unique_ptr<TlsCertificatesWatcherInterface> watcher;
    std::optional<std::string> root_cert_name;
    std::optional<std::string> identity_cert_name;
  };

  struct CertificateInfo {

    std::string pem_root_certs;

    grpc_core::PemKeyCertPairList pem_key_cert_pairs;

    grpc_error_handle root_cert_error;

    grpc_error_handle identity_cert_error;

    std::set<TlsCertificatesWatcherInterface*> root_cert_watchers;

    std::set<TlsCertificatesWatcherInterface*> identity_cert_watchers;

    ~CertificateInfo() {}
    void SetRootError(grpc_error_handle error) { root_cert_error = error; }
    void SetIdentityError(grpc_error_handle error) {
      identity_cert_error = error;
    }
  };

  grpc_core::Mutex mu_;

  grpc_core::Mutex callback_mu_;

  std::map<TlsCertificatesWatcherInterface*, WatcherInfo> watchers_
      ABSL_GUARDED_BY(mu_);

  std::function<void(std::string, bool, bool)> watch_status_callback_
      ABSL_GUARDED_BY(callback_mu_);

  std::map<std::string, CertificateInfo> certificate_info_map_
      ABSL_GUARDED_BY(mu_);
};

#endif
