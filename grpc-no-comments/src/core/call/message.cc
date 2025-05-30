// Copyright 2024 gRPC authors.

#include "src/core/call/message.h"

#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>

#include "absl/strings/str_cat.h"

namespace grpc_core {

std::string Message::DebugString() const {
  std::string out = absl::StrCat(payload_.Length(), "b");
  auto flags = flags_;
  auto explain = [&flags, &out](uint32_t flag, absl::string_view name) {
    if (flags & flag) {
      flags &= ~flag;
      absl::StrAppend(&out, ":", name);
    }
  };
  explain(GRPC_WRITE_BUFFER_HINT, "write_buffer");
  explain(GRPC_WRITE_NO_COMPRESS, "no_compress");
  explain(GRPC_WRITE_THROUGH, "write_through");
  explain(GRPC_WRITE_INTERNAL_COMPRESS, "compress");
  explain(GRPC_WRITE_INTERNAL_TEST_ONLY_WAS_COMPRESSED, "was_compressed");
  if (flags != 0) {
    absl::StrAppend(&out, ":huh=0x", absl::Hex(flags));
  }
  return out;
}

}
