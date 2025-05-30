// Copyright 2021 gRPC authors.

#include "src/core/call/parsed_metadata.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {
namespace metadata_detail {

std::string MakeDebugString(absl::string_view key, absl::string_view value) {
  return absl::StrCat(key, ": ", value);
}

Slice SliceFromBuffer(const Buffer& buffer) {
  return Slice(CSliceRef(buffer.slice));
}

void DestroySliceValue(const Buffer& value) { CSliceUnref(value.slice); }

void DestroyTrivialMemento(const Buffer&) {}

}
}
