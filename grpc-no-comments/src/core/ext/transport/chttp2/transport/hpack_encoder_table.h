// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_ENCODER_TABLE_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_ENCODER_TABLE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <limits>
#include <vector>

#include "src/core/ext/transport/chttp2/transport/hpack_constants.h"

namespace grpc_core {

class HPackEncoderTable {
 public:
  using EntrySize = uint16_t;

  HPackEncoderTable() : elem_size_(hpack_constants::kInitialTableEntries) {}

  static constexpr size_t MaxEntrySize() {
    return std::numeric_limits<EntrySize>::max();
  }

  uint32_t AllocateIndex(size_t element_size);

  bool SetMaxSize(uint32_t max_table_size);

  uint32_t max_size() const { return max_table_size_; }

  uint32_t test_only_table_size() const { return table_size_; }

  uint32_t test_only_table_elems() const { return table_elems_; }

  uint32_t DynamicIndex(uint32_t index) const {
    return 1 + hpack_constants::kLastStaticEntry + tail_remote_index_ +
           table_elems_ - index;
  }

  bool ConvertibleToDynamicIndex(uint32_t index) const {
    return index > tail_remote_index_;
  }

 private:
  void EvictOne();
  void Rebuild(uint32_t capacity);

  uint32_t tail_remote_index_ = 0;
  uint32_t max_table_size_ = hpack_constants::kInitialTableSize;
  uint32_t table_elems_ = 0;
  uint32_t table_size_ = 0;

  std::vector<EntrySize> elem_size_;
};

}

#endif
