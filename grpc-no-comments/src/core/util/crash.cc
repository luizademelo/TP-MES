// Copyright 2022 gRPC authors.

#include "src/core/util/crash.h"

#include <grpc/support/port_platform.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

namespace grpc_core {

void Crash(absl::string_view message, SourceLocation location) {
  LOG(ERROR).AtLocation(location.file(), location.line()) << message;
  abort();
}

void CrashWithStdio(absl::string_view message, SourceLocation location) {
  fputs(absl::StrCat(location.file(), ":", location.line(), ": ", message, "\n")
            .c_str(),
        stderr);
  abort();
}

}
