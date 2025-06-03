Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_common_types_parser.h"

#include <grpc/support/json.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <map>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/extensions/transport_sockets/tls/v3/common.upb.h"
#include "envoy/extensions/transport_sockets/tls/v3/tls.upb.h"
#include "envoy/type/matcher/v3/regex.upb.h"
#include "envoy/type/matcher/v3/string.upb.h"
#include "google/protobuf/any.upb.h"
#include "google/protobuf/struct.upb.h"
#include "google/protobuf/struct.upbdefs.h"
#include "google/protobuf/wrappers.upb.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/upb_utils.h"
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"
#include "src/core/xds/xds_client/xds_client.h"
#include "upb/base/status.hpp"
#include "upb/json/encode.h"
#include "upb/mem/arena.h"
#include "xds/type/v3/typed_struct.upb.h"

namespace grpc_core {

// Parses a protocol buffer Duration message into a Duration object
// Validates that seconds and nanos are within acceptable ranges
Duration ParseDuration(const google_protobuf_Duration* proto_duration,
                       ValidationErrors* errors) {
  int64_t seconds = google_protobuf_Duration_seconds(proto_duration);
  if (seconds < 0 || seconds > 315576000000) {
    ValidationErrors::ScopedField field(errors, ".seconds");
    errors->AddError("value must be in the range [0, 315576000000]");
  }
  int32_t nanos = google_protobuf_Duration_nanos(proto_duration);
  if (nanos < 0 || nanos > 999999999) {
    ValidationErrors::ScopedField field(errors, ".nanos");
    errors->AddError("value must be in the range [0, 999999999]");
  }
  return Duration::FromSecondsAndNanoseconds(seconds, nanos);
}

// Parses an XDS address from a protocol buffer message into a resolved address
// Validates the socket address and port, and converts to system address format
std::optional<grpc_resolved_address> ParseXdsAddress(
    const envoy_config_core_v3_Address* address, ValidationErrors* errors) {
  if (address == nullptr) {
    errors->AddError("field not present");
    return std::nullopt;
  }
  ValidationErrors::ScopedField field(errors, ".socket_address");
  const envoy_config_core_v3_SocketAddress* socket_address =
      envoy_config_core_v3_Address_socket_address(address);
  if (socket_address == nullptr) {
    errors->AddError("field not present");
    return std::nullopt;
  }
  std::string address_str = UpbStringToStdString(
      envoy_config_core_v3_SocketAddress_address(socket_address));
  uint32_t port;
  {
    ValidationErrors::ScopedField field(errors, ".port_value");
    port = envoy_config_core_v3_SocketAddress_port_value(socket_address);
    if (GPR_UNLIKELY(port >> 16) != 0) {
      errors->AddError("invalid port");
      return std::nullopt;
    }
  }
  auto addr = StringToSockaddr(address_str, port);
  if (!addr.ok()) {
    errors->AddError(addr.status().message());
    return std::nullopt;
  }
  return *addr;
}

namespace {

// Parses a certificate provider instance from protocol buffer message
// Validates that the instance exists in the bootstrap configuration
CommonTlsContext::CertificateProviderPluginInstance
CertificateProviderInstanceParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance*
        certificate_provider_instance_proto,
    ValidationErrors* errors) {
  CommonTlsContext::CertificateProviderPluginInstance cert_provider;
  cert_provider.instance_name = UpbStringToStdString(
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_instance_name(
          certificate_provider_instance_proto));
  const auto& bootstrap =
      DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap());
  if (bootstrap.certificate_providers().find(cert_provider.instance_name) ==
      bootstrap.certificate_providers().end()) {
    ValidationErrors::ScopedField field(errors, ".instance_name");
    errors->AddError(
        absl::StrCat("unrecognized certificate provider instance name: ",
                     cert_provider.instance_name));
  }
  cert_provider.certificate_name = UpbStringToStdString(
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_certificate_name(
          certificate_provider_instance_proto));
  return cert_provider;
}

// Parses a certificate provider plugin instance from protocol buffer message
// Similar to CertificateProviderInstanceParse but for a different message type
CommonTlsContext::CertificateProviderPluginInstance
CertificateProviderPluginInstanceParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance*
        certificate_provider_plugin_instance_proto,
    ValidationErrors* errors) {
  CommonTlsContext::CertificateProviderPluginInstance cert_provider;
  cert_provider.instance_name = UpbStringToStdString(
      envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_instance_name(
          certificate_provider_plugin_instance_proto));
  const auto& bootstrap =
      DownCast<const GrpcXdsBootstrap&>(context.client->bootstrap());
  if (bootstrap.certificate_providers().find(cert_provider.instance_name) ==
      bootstrap.certificate_providers().end()) {
    ValidationErrors::ScopedField field(errors, ".instance_name");
    errors->AddError(
        absl::StrCat("unrecognized certificate provider instance name: ",
                     cert_provider.instance_name));
  }
  cert_provider.certificate_name = UpbStringToStdString(
      envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_certificate_name(
          certificate_provider_plugin_instance_proto));
  return cert_provider;
}

// Parses a certificate validation context from protocol buffer message
// Handles subject alternative name matchers and certificate provider configuration
CommonTlsContext::CertificateValidationContext
CertificateValidationContextParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext*
        certificate_validation_context_proto,
    ValidationErrors* errors) {
  CommonTlsContext::CertificateValidationContext certificate_validation_context;
  size_t len = 0;
  auto* subject_alt_names_matchers =
      envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_match_subject_alt_names(
          certificate_validation_context_proto, &len);
  for (size_t i = 0; i < len; ++i) {
    ValidationErrors::ScopedField field(
        errors, absl::StrCat(".match_subject_alt_names[", i, "]"));
    StringMatcher::Type type;
    std::string matcher;
    if (envoy_type_matcher_v3_StringMatcher_has_exact(
            subject_alt_names_matchers[i])) {
      type = StringMatcher::Type::kExact;
      matcher = UpbStringToStdString(envoy_type_matcher_v3_StringMatcher_exact(
          subject_alt_names_matchers[i]));
    } else if (envoy_type_matcher_v3_StringMatcher_has_prefix(
                   subject_alt_names_matchers[i])) {
      type = StringMatcher::Type::kPrefix;
      matcher = UpbStringToStdString(envoy_type_matcher_v3_StringMatcher_prefix(
          subject_alt_names_matchers[i]));
    } else if (envoy_type_matcher_v3_StringMatcher_has_suffix(
                   subject_alt_names_matchers[i])) {
      type = StringMatcher::Type::kSuffix;
      matcher = UpbStringToStdString(envoy_type_matcher_v3_StringMatcher_suffix(
          subject_alt_names_matchers[i]));
    } else if (envoy_type_matcher_v3_StringMatcher_has_contains(
                   subject_alt_names_matchers[i])) {
      type = StringMatcher::Type::kContains;
      matcher =
          UpbStringToStdString(envoy_type_matcher_v3_StringMatcher_contains(
              subject_alt_names_matchers[i]));
    } else if (envoy_type_matcher_v3_StringMatcher_has_safe_regex(
                   subject_alt_names_matchers[i])) {
      type = StringMatcher::Type::kSafeRegex;
      auto* regex_matcher = envoy_type_matcher_v3_StringMatcher_safe_regex(
          subject_alt_names_matchers[i]);
      matcher = UpbStringToStdString(
          envoy_type_matcher_v3_RegexMatcher_regex(regex_matcher));
    } else {
      errors->AddError("invalid StringMatcher specified");
      continue;
    }
    bool ignore_case = envoy_type_matcher_v3_StringMatcher_ignore_case(
        subject_alt_names_matchers[i]);
    absl::StatusOr<StringMatcher> string_matcher =
        StringMatcher::Create(type, matcher,
                              !ignore_case);
    if (!string_matcher.ok()) {
      errors->AddError(string_matcher.status().message());
      continue;
    }
    if (type == StringMatcher::Type::kSafeRegex && ignore_case) {
      ValidationErrors::ScopedField field(errors, ".ignore_case");
      errors->AddError("not supported for regex matcher");
      continue;
    }
    certificate_validation_context.match_subject_alt_names.push_back(
        std::move(string_matcher.value()));
  }
  auto* ca_certificate_provider_instance =
      envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_ca_certificate_provider_instance(
          certificate_validation_context_proto);
  if (ca_certificate_provider_instance != nullptr) {
    ValidationErrors::ScopedField field(errors,
                                        ".ca_certificate_provider_instance");
    certificate_validation_context.ca_certs =
        CertificateProviderPluginInstanceParse(
            context, ca_certificate_provider_instance, errors);
  } else {
    auto* system_root_certs =
        envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_system_root_certs(
            certificate_validation_context_proto);
    if (system_root_certs != nullptr) {
      certificate_validation_context.ca_certs =
          CommonTlsContext::CertificateValidationContext::SystemRootCerts();
    }
  }
  // The following features are currently unsupported
  if (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_spki(
          certificate_validation_context_proto, nullptr) != nullptr) {
    ValidationErrors::ScopedField field(errors, ".verify_certificate_spki");
    errors->AddError("feature unsupported");
  }
  if (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_verify_certificate_hash(
          certificate_validation_context_proto, nullptr) != nullptr) {
    ValidationErrors::ScopedField field(errors, ".verify_certificate_hash");
    errors->AddError("feature unsupported");
  }
  if (ParseBoolValue(
          envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_require_signed_certificate_timestamp(
              certificate_validation_context_proto))) {
    ValidationErrors::ScopedField field(
        errors, ".require_signed_certificate_timestamp");
    errors->AddError("feature unsupported");
  }
  if (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_crl(
          certificate_validation_context_proto)) {
    ValidationErrors::ScopedField field(errors, ".crl");
    errors->AddError("feature unsupported");
  }
  if (envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_has_custom_validator_config(
          certificate_validation_context_proto)) {
    ValidationErrors::ScopedField field(errors, ".custom_validator_config");
    errors->AddError("feature unsupported");
  }
  return certificate_validation_context;
}

}  // namespace

// Parses a common TLS context from protocol buffer message
// Handles combined validation contexts and certificate provider configurations
CommonTlsContext CommonTlsContextParse(
    const XdsResourceType::DecodeContext& context,
    const envoy_extensions_transport_sockets_tls_v3_CommonTlsContext*
        common_tls_context_proto,
    ValidationErrors* errors) {
  CommonTlsContext common_tls_context;

  auto* combined_validation_context =
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_combined_validation_context(
          common_tls_context_proto);
  if (combined_validation_context != nullptr) {
    ValidationErrors::ScopedField field(errors, ".combined_validation_context");
    auto* default_validation_context =
        envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_default_validation_context(
            combined_validation_context);
    if (default_validation_context != nullptr) {
      ValidationErrors::ScopedField field(errors,
                                          ".default_validation_context");
      common_tls_context.certificate_validation_context =
          CertificateValidationContextParse(context, default_validation_context,
                                            errors);
    }

    if (!std::holds_alternative<
            CommonTlsContext::CertificateProviderPluginInstance>(
            common_tls_context.certificate_validation_context.ca_certs)) {
      const auto* validation_context_certificate_provider_instance =
          envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_validation_context_certificate_provider_instance(
              combined_validation_context);
      if (validation_context_certificate_provider_instance != nullptr) {
        ValidationErrors::ScopedField field(
            errors, ".validation_context_certificate_provider_instance");
        common_tls_context.certificate_validation_context.ca_certs =
            CertificateProviderInstanceParse(
                context, validation_context_certificate_provider_instance,
                errors);
      }
    }
  } else if (
      auto* validation_context =
          envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_validation_context(
              common_tls_context_proto);
      validation_context != nullptr) {
    ValidationErrors::ScopedField field(errors, ".validation_context");
    common_tls_context.certificate_validation_context =
        CertificateValidationContextParse(context, validation_context, errors);
  } else if (
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_validation_context_sds_secret_config(
          common_tls_context_proto)) {
    ValidationErrors::ScopedField field(
        errors, ".validation_context_sds_secret_config");
    errors->AddError("feature unsupported");
  }
  auto* tls_certificate_provider_instance =
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_provider_instance(
          common_tls_context_proto);
  if (tls_certificate_provider_instance != nullptr) {
    ValidationErrors::ScopedField field(errors,
                                        ".tls_certificate_provider_instance");
    common_tls_context.tls_certificate_provider_instance =
        CertificateProviderPluginInstanceParse(
            context, tls_certificate_provider_instance, errors);
  } else {
    auto* tls_certificate_certificate_provider_instance =
        envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_certificate_provider_instance(
            common_tls_context_proto);
    if (tls_certificate_certificate_provider_instance != nullptr) {
      ValidationErrors::ScopedField field(
          errors, ".tls_certificate_certificate_provider_instance");
      common_tls_context.tls_certificate_provider_instance =
          CertificateProviderInstanceParse(
              context, tls_certificate_certificate_provider_instance, errors);
    } else {
      size_t size;
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificates(
          common_tls_context_proto, &size);
      if (size != 0) {
        ValidationErrors::ScopedField field(errors, ".tls_certificates");
        errors->AddError("feature unsupported");
      }
      envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_tls_certificate_sds_secret_configs(
          common_tls_context_proto, &size);
      if (size != 0) {
        ValidationErrors::ScopedField field(
            errors, ".tls_certificate_sds_secret_configs");
        errors->AddError("feature unsupported");
      }
    }
  }
  // The following features are currently unsupported
  if (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_tls_params(
          common_tls_context_proto)) {
    ValidationErrors::ScopedField field(errors, ".tls_params");
    errors->AddError("feature unsupported");
  }
  if (envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_has_custom_handshaker(
          common_tls_context_proto)) {
    ValidationErrors::ScopedField field(errors, ".custom_handshaker");
    errors->AddError("feature unsupported");