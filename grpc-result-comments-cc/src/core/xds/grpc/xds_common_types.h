Here's the commented version of the code:

```c++
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

// Represents common TLS context configuration used in xDS implementations.
// Contains settings for both certificate validation and TLS certificate provision.
struct CommonTlsContext {
  // Represents a certificate provider plugin instance configuration.
  struct CertificateProviderPluginInstance {
    std::string instance_name;       // Name of the certificate provider plugin instance
    std::string certificate_name;    // Name of the certificate to use from the provider

    // Equality comparison operator
    bool operator==(const CertificateProviderPluginInstance& other) const {
      return instance_name == other.instance_name &&
             certificate_name == other.certificate_name;
    }

    // Returns string representation of the instance
    std::string ToString() const;
    // Checks if the instance is empty (unconfigured)
    bool Empty() const;
  };

  // Represents certificate validation context configuration
  struct CertificateValidationContext {
    // Special marker for using system root certificates
    struct SystemRootCerts {
      bool operator==(const SystemRootCerts&) const { return true; }
    };
    
    // CA certificates can be one of:
    // - Unset (monostate)
    // - From a certificate provider plugin
    // - System root certificates
    std::variant<std::monostate, CertificateProviderPluginInstance,
                 SystemRootCerts>
        ca_certs;
    
    // List of subject alternative name matchers for certificate validation
    std::vector<StringMatcher> match_subject_alt_names;

    // Equality comparison operator
    bool operator==(const CertificateValidationContext& other) const {
      return ca_certs == other.ca_certs &&
             match_subject_alt_names == other.match_subject_alt_names;
    }

    // Returns string representation of the context
    std::string ToString() const;
    // Checks if the context is empty (unconfigured)
    bool Empty() const;
  };

  // Configuration for certificate validation
  CertificateValidationContext certificate_validation_context;
  // Configuration for TLS certificate provider
  CertificateProviderPluginInstance tls_certificate_provider_instance;

  // Equality comparison operator
  bool operator==(const CommonTlsContext& other) const {
    return certificate_validation_context ==
               other.certificate_validation_context &&
           tls_certificate_provider_instance ==
               other.tls_certificate_provider_instance;
  }

  // Returns string representation of the TLS context
  std::string ToString() const;
  // Checks if the context is empty (unconfigured)
  bool Empty() const;
};

// Represents an xDS extension configuration
struct XdsExtension {
  // Type of the extension (identifies the extension point)
  absl::string_view type;

  // Extension value can be either:
  // - A string view (for simple string values)
  // - A JSON object (for complex configurations)
  std::variant<absl::string_view, Json> value;

  // Fields used for validation error reporting
  std::vector<ValidationErrors::ScopedField> validation_fields;
};

}

#endif
```

The comments provide:
1. Overview of each struct's purpose
2. Explanation of each member variable
3. Documentation for operators and methods
4. Clarification of variant types and their possible states
5. Context about how these types are used in xDS implementations

The comments are concise yet informative, helping future developers understand both the high-level purpose and implementation details of each component.