// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_SIMPLE_SLICE_BASED_METADATA_H
#define GRPC_SRC_CORE_CALL_SIMPLE_SLICE_BASED_METADATA_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/call/parsed_metadata.h"
#include "src/core/lib/slice/slice.h"

namespace grpc_core {

struct SimpleSliceBasedMetadata {
  using ValueType = Slice;
  using MementoType = Slice;
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn) {
    if (will_keep_past_request_lifetime) {
      return value.TakeUniquelyOwned();
    } else {
      return value.TakeOwned();
    }
  }
  static ValueType MementoToValue(MementoType value) { return value; }
  static Slice Encode(const ValueType& x) { return x.Ref(); }
  static absl::string_view DisplayValue(const ValueType& value) {
    return value.as_string_view();
  }
  static absl::string_view DisplayMemento(const MementoType& value) {
    return value.as_string_view();
  }
};

}

#endif
