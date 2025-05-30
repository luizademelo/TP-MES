
// Copyright 2023 gRPC authors.

#include "src/core/util/ref_counted_string.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <new>

namespace grpc_core {

RefCountedPtr<RefCountedString> RefCountedString::Make(absl::string_view src) {
  void* p = gpr_malloc(sizeof(Header) + src.length() + 1);
  return RefCountedPtr<RefCountedString>(new (p) RefCountedString(src));
}

RefCountedString::RefCountedString(absl::string_view src)
    : header_{{}, src.length()} {
  memcpy(payload_, src.data(), header_.length);

  payload_[header_.length] = 0;
}

void RefCountedString::Destroy() { gpr_free(this); }

}
