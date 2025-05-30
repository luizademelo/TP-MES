
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CERTIFICATE_PROVIDER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CERTIFICATE_PROVIDER_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "src/core/util/matchers.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class XdsCertificateProvider final : public grpc_tls_certificate_provider {
 public:

  XdsCertificateProvider(
      RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
      absl::string_view root_cert_name, bool use_system_root_certs,
      RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
      absl::string_view identity_cert_name,
      std::vector<StringMatcher> san_matchers);

  XdsCertificateProvider(
      RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
      absl::string_view root_cert_name,
      RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
      absl::string_view identity_cert_name, bool require_client_certificate);

  ~XdsCertificateProvider() override;

  RefCountedPtr<grpc_tls_certificate_distributor> distributor() const override {
    return distributor_;
  }

  UniqueTypeName type() const override;

  bool ProvidesRootCerts() const { return root_cert_provider_ != nullptr; }
  bool UseSystemRootCerts() const { return use_system_root_certs_; }
  bool ProvidesIdentityCerts() const {
    return identity_cert_provider_ != nullptr;
  }
  bool require_client_certificate() const {
    return require_client_certificate_;
  }
  const std::vector<StringMatcher>& san_matchers() const {
    return san_matchers_;
  }

  static absl::string_view ChannelArgName() {
    return "grpc.internal.xds_certificate_provider";
  }
  static int ChannelArgsCompare(const XdsCertificateProvider* a,
                                const XdsCertificateProvider* b) {
    if (a == nullptr || b == nullptr) return QsortCompare(a, b);
    return a->Compare(b);
  }

 private:
  int CompareImpl(const grpc_tls_certificate_provider* other) const override {

    return QsortCompare(static_cast<const grpc_tls_certificate_provider*>(this),
                        other);
  }

  void WatchStatusCallback(std::string cert_name, bool root_being_watched,
                           bool identity_being_watched);

  RefCountedPtr<grpc_tls_certificate_distributor> distributor_;
  RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider_;
  std::string root_cert_name_;
  bool use_system_root_certs_ = false;
  RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider_;
  std::string identity_cert_name_;
  std::vector<StringMatcher> san_matchers_;
  bool require_client_certificate_ = false;

  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      root_cert_watcher_ = nullptr;
  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      identity_cert_watcher_ = nullptr;
};

}

#endif
