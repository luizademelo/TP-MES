
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_FILE_WATCHER_CERTIFICATE_PROVIDER_FACTORY_H
#define GRPC_SRC_CORE_XDS_GRPC_FILE_WATCHER_CERTIFICATE_PROVIDER_FACTORY_H

#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/certificate_provider_factory.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class FileWatcherCertificateProviderFactory final
    : public CertificateProviderFactory {
 public:
  class Config final : public CertificateProviderFactory::Config {
   public:
    absl::string_view name() const override;

    std::string ToString() const override;

    const std::string& identity_cert_file() const {
      return identity_cert_file_;
    }

    const std::string& private_key_file() const { return private_key_file_; }

    const std::string& root_cert_file() const { return root_cert_file_; }

    Duration refresh_interval() const { return refresh_interval_; }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs& args);
    void JsonPostLoad(const Json& json, const JsonArgs& args,
                      ValidationErrors* errors);

   private:
    std::string identity_cert_file_;
    std::string private_key_file_;
    std::string root_cert_file_;
    Duration refresh_interval_ = Duration::Minutes(10);
  };

  absl::string_view name() const override;

  RefCountedPtr<CertificateProviderFactory::Config>
  CreateCertificateProviderConfig(const Json& config_json, const JsonArgs& args,
                                  ValidationErrors* errors) override;

  RefCountedPtr<grpc_tls_certificate_provider> CreateCertificateProvider(
      RefCountedPtr<CertificateProviderFactory::Config> config) override;
};

}

#endif
