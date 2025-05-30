
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SLICE_PERCENT_ENCODING_H
#define GRPC_SRC_CORE_LIB_SLICE_PERCENT_ENCODING_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/slice/slice.h"

namespace grpc_core {

enum class PercentEncodingType {

  URL,

  Compatible
};

Slice PercentEncodeSlice(Slice slice, PercentEncodingType type);

Slice PermissivePercentDecodeSlice(Slice slice_in);

}

#endif
