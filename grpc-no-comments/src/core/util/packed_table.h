// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_PACKED_TABLE_H
#define GRPC_SRC_CORE_UTIL_PACKED_TABLE_H

#include <grpc/support/port_platform.h>

#include "src/core/util/sorted_pack.h"
#include "src/core/util/table.h"

namespace grpc_core {

namespace packed_table_detail {
template <typename A, typename B>
struct Cmp {
  static constexpr bool kValue = alignof(A) > alignof(B) ||
                                 (alignof(A) == alignof(B) &&
                                  sizeof(A) > sizeof(B));
};
};

template <typename... T>
using PackedTable =
    typename WithSortedPack<Table, packed_table_detail::Cmp, T...>::Type;

}

#endif
