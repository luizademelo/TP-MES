
// Copyright 2023 gRPC authors.

#ifndef GRPCPP_SECURITY_AUDIT_LOGGING_H
#define GRPCPP_SECURITY_AUDIT_LOGGING_H

#include <grpc/grpc_audit_logging.h>
#include <grpcpp/support/string_ref.h>

#include <memory>
#include <string>
#include <utility>

#include "absl/status/statusor.h"

namespace grpc {
namespace experimental {

using grpc_core::experimental::AuditContext;
using grpc_core::experimental::AuditLogger;
using grpc_core::experimental::
    AuditLoggerFactory;
using grpc_core::experimental::
    RegisterAuditLoggerFactory;

}
}

#endif
