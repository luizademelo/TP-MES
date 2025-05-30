
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_TLS_UTILS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_TLS_UTILS_H

#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <string>
#include <vector>

#include "absl/strings/string_view.h"

namespace grpc_core {

bool VerifySubjectAlternativeName(absl::string_view subject_alternative_name,
                                  const std::string& matcher);

absl::string_view GetAuthPropertyValue(grpc_auth_context* context,
                                       const char* property_name);

std::vector<absl::string_view> GetAuthPropertyArray(grpc_auth_context* context,
                                                    const char* property_name);

}

#endif
