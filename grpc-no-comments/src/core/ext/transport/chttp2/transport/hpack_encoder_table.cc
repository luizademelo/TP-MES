// Copyright 2021 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/hpack_encoder_table.h"

#include <grpc/support/port_platform.h>

#include <algorithm>

#include "absl/log/check.h"

namespace grpc_core {

uint32_t HPackEncoderTable::AllocateIndex(size_t element_size) {
  DCHECK_GE(element_size, 32u);

  uint32_t new_index = tail_remote_index_ + table_elems_ + 1;
  DCHECK(element_size <= MaxEntrySize());

  if (element_size > max_table_size_) {
    while (table_size_ > 0) {
      EvictOne();
    }
    return 0;
  }

  while (table_size_ + element_size > max_table_size_) {
    EvictOne();
  }
  CHECK(table_elems_ < elem_size_.size());
  elem_size_[new_index % elem_size_.size()] =
      static_cast<uint16_t>(element_size);
  table_size_ += element_size;
  table_elems_++;

  return new_index;
}

bool HPackEncoderTable::SetMaxSize(uint32_t max_table_size) {
  if (max_table_size == max_table_size_) {
    return false;
  }
  while (table_size_ > 0 && table_size_ > max_table_size) {
    EvictOne();
  }
  max_table_size_ = max_table_size;
  const size_t max_table_elems =
      hpack_constants::EntriesForBytes(max_table_size);

  if (max_table_elems > elem_size_.size()) {
    Rebuild(static_cast<uint32_t>(
        std::max(max_table_elems, 2 * elem_size_.size())));
  }
  return true;
}

void HPackEncoderTable::EvictOne() {
  tail_remote_index_++;
  CHECK_GT(tail_remote_index_, 0u);
  CHECK_GT(table_elems_, 0u);
  auto removing_size = elem_size_[tail_remote_index_ % elem_size_.size()];
  CHECK(table_size_ >= removing_size);
  table_size_ -= removing_size;
  table_elems_--;
}

void HPackEncoderTable::Rebuild(uint32_t capacity) {
  decltype(elem_size_) new_elem_size(capacity);
  CHECK_LE(table_elems_, capacity);
  for (uint32_t i = 0; i < table_elems_; i++) {
    uint32_t ofs = tail_remote_index_ + i + 1;
    new_elem_size[ofs % capacity] = elem_size_[ofs % elem_size_.size()];
  }
  elem_size_.swap(new_elem_size);
}

}
