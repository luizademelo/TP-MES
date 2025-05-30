// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_CRASH_H
#define GRPC_SRC_CORE_UTIL_CRASH_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/util/debug_location.h"

namespace grpc_core {

[[noreturn]] void Crash(absl::string_view message,
                        ::grpc_core::SourceLocation location = {});

[[noreturn]] void CrashWithStdio(absl::string_view message,
                                 ::grpc_core::SourceLocation location = {});

}

#endif
