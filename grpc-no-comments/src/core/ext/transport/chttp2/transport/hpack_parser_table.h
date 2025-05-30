
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSER_TABLE_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSER_TABLE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "absl/functional/function_ref.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/parsed_metadata.h"
#include "src/core/ext/transport/chttp2/transport/hpack_constants.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parse_result.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/unique_ptr_with_bitset.h"

namespace grpc_core {

class HPackTable {
 public:
  HPackTable() = default;
  ~HPackTable() = default;

  HPackTable(const HPackTable&) = delete;
  HPackTable& operator=(const HPackTable&) = delete;
  HPackTable(HPackTable&&) = default;
  HPackTable& operator=(HPackTable&&) = default;

  void SetMaxBytes(uint32_t max_bytes);
  bool SetCurrentTableSize(uint32_t bytes);
  uint32_t current_table_size() { return current_table_bytes_; }

  struct Memento {
    ParsedMetadata<grpc_metadata_batch> md;

    UniquePtrWithBitset<HpackParseResult, 1> parse_status;
    static const int kUsedBit = 0;
  };

  const Memento* Lookup(uint32_t index) {

    if (index <= hpack_constants::kLastStaticEntry) {
      return &static_mementos_->memento[index - 1];
    } else {
      return LookupDynamic(index);
    }
  }

  GRPC_MUST_USE_RESULT bool Add(Memento md);
  void AddLargerThanCurrentTableSize();

  uint32_t num_entries() const { return entries_.num_entries(); }

  uint32_t test_only_table_size() const { return mem_used_; }

  uint32_t max_bytes() const { return max_bytes_; }
  uint32_t current_table_bytes() const { return current_table_bytes_; }

  std::string TestOnlyDynamicTableAsString() const;

 private:
  struct StaticMementos {
    StaticMementos();
    Memento memento[hpack_constants::kLastStaticEntry];
  };

  class MementoRingBuffer {
   public:
    MementoRingBuffer() {}
    ~MementoRingBuffer();

    MementoRingBuffer(const MementoRingBuffer&) = delete;
    MementoRingBuffer& operator=(const MementoRingBuffer&) = delete;
    MementoRingBuffer(MementoRingBuffer&&) = default;
    MementoRingBuffer& operator=(MementoRingBuffer&&) = default;

    void Rebuild(uint32_t max_entries);

    void Put(Memento m);

    Memento PopOne();

    const Memento* Lookup(uint32_t index);
    const Memento* Peek(uint32_t index) const;

    template <typename F>
    void ForEach(F f) const;

    uint32_t max_entries() const { return max_entries_; }
    uint32_t num_entries() const { return num_entries_; }

   private:

    uint32_t first_entry_ = 0;

    uint32_t num_entries_ = 0;

    uint32_t max_entries_ = hpack_constants::kInitialTableEntries;

    static constexpr uint32_t kNoTimestamp =
        std::numeric_limits<uint32_t>::max();
    uint32_t timestamp_index_ = kNoTimestamp;

    Timestamp timestamp_;

    std::vector<Memento> entries_;
  };

  const Memento* LookupDynamic(uint32_t index) {

    const uint32_t tbl_index = index - (hpack_constants::kLastStaticEntry + 1);
    return entries_.Lookup(tbl_index);
  }

  void EvictOne();

  static const StaticMementos* GetStaticMementos() {
    static const NoDestruct<StaticMementos> static_mementos;
    return static_mementos.get();
  }

  uint32_t mem_used_ = 0;

  uint32_t max_bytes_ = hpack_constants::kInitialTableSize;

  uint32_t current_table_bytes_ = hpack_constants::kInitialTableSize;

  MementoRingBuffer entries_;

  const StaticMementos* static_mementos_ = GetStaticMementos();
};

}

#endif
