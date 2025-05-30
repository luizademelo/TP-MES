
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_COMMON_TYPES_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_COMMON_TYPES_H

#include <string>
#include <variant>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/matchers.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

struct CommonTlsContext {
  struct CertificateProviderPluginInstance {
    std::string instance_name;
    std::string certificate_name;

    bool operator==(const CertificateProviderPluginInstance& other) const {
      return instance_name == other.instance_name &&
             certificate_name == other.certificate_name;
    }

    std::string ToString() const;
    bool Empty() const;
  };

  struct CertificateValidationContext {
    struct SystemRootCerts {
      bool operator==(const SystemRootCerts&) const { return true; }
    };
    std::variant<std::monostate, CertificateProviderPluginInstance,
                 SystemRootCerts>
        ca_certs;
    std::vector<StringMatcher> match_subject_alt_names;

    bool operator==(const CertificateValidationContext& other) const {
      return ca_certs == other.ca_certs &&
             match_subject_alt_names == other.match_subject_alt_names;
    }

    std::string ToString() const;
    bool Empty() const;
  };

  CertificateValidationContext certificate_validation_context;
  CertificateProviderPluginInstance tls_certificate_provider_instance;

  bool operator==(const CommonTlsContext& other) const {
    return certificate_validation_context ==
               other.certificate_validation_context &&
           tls_certificate_provider_instance ==
               other.tls_certificate_provider_instance;
  }

  std::string ToString() const;
  bool Empty() const;
};

struct XdsExtension {

  absl::string_view type;

  std::variant<absl::string_view , Json >
      value;

  std::vector<ValidationErrors::ScopedField> validation_fields;
};

}

#endif
