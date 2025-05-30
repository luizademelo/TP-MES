
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_CERTIFICATE_PROVIDER_FACTORY_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_CERTIFICATE_PROVIDER_FACTORY_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class CertificateProviderFactory {
 public:

  class Config : public RefCounted<Config> {
   public:
    ~Config() override = default;

    virtual absl::string_view name() const = 0;

    virtual std::string ToString() const = 0;
  };

  virtual ~CertificateProviderFactory() = default;

  virtual absl::string_view name() const = 0;

  virtual RefCountedPtr<Config> CreateCertificateProviderConfig(
      const Json& config_json, const JsonArgs& args,
      ValidationErrors* errors) = 0;

  virtual RefCountedPtr<grpc_tls_certificate_provider>
  CreateCertificateProvider(RefCountedPtr<Config> config) = 0;
};

}

#endif
