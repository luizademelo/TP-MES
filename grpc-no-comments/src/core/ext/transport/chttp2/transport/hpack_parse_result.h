// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSE_RESULT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_PARSE_RESULT_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/surface/validate_metadata.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

enum class HpackParseStatus : uint8_t {

  kOk,

  kEof,

  kMovedFrom,

  kFirstStreamError,
  kInvalidMetadata = kFirstStreamError,

  kHardMetadataLimitExceeded,
  kSoftMetadataLimitExceeded,

  kHardMetadataLimitExceededByKey,

  kHardMetadataLimitExceededByValue,
  kMetadataParseError,

  kUnbase64Failed,

  kFirstConnectionError,

  kIncompleteHeaderAtBoundary = kFirstConnectionError,

  kVarintOutOfRange,

  kInvalidHpackIndex,

  kIllegalTableSizeChange,

  kAddBeforeTableSizeUpdated,

  kParseHuffFailed,

  kTooManyDynamicTableSizeChanges,

  kMaliciousVarintEncoding,

  kIllegalHpackOpCode,
};

inline bool IsStreamError(HpackParseStatus status) {
  return status >= HpackParseStatus::kFirstStreamError &&
         status < HpackParseStatus::kFirstConnectionError;
}

inline bool IsConnectionError(HpackParseStatus status) {
  return status >= HpackParseStatus::kFirstConnectionError;
}

inline bool IsEphemeralError(HpackParseStatus status) {
  switch (status) {
    case HpackParseStatus::kSoftMetadataLimitExceeded:
    case HpackParseStatus::kHardMetadataLimitExceeded:
      return true;
    default:
      return false;
  }
}

class HpackParseResult {
 public:
  HpackParseResult() : HpackParseResult{HpackParseStatus::kOk} {}

  bool ok() const {
    return state_ == nullptr || state_->status.get() == HpackParseStatus::kOk;
  }
  bool stream_error() const {
    return state_ != nullptr && IsStreamError(state_->status.get());
  }
  bool connection_error() const {
    return state_ != nullptr && IsConnectionError(state_->status.get());
  }
  bool ephemeral() const {
    return state_ != nullptr && IsEphemeralError(state_->status.get());
  }

  std::unique_ptr<HpackParseResult> PersistentStreamErrorOrNullptr() const {
    if (ok() || connection_error() || ephemeral()) return nullptr;
    return std::make_unique<HpackParseResult>(*this);
  }

  static HpackParseResult FromStatus(HpackParseStatus status) {

    switch (status) {
      case HpackParseStatus::kUnbase64Failed:
      case HpackParseStatus::kParseHuffFailed:
        return HpackParseResult{status};
      default:
        Crash(
            absl::StrCat("Invalid HpackParseStatus for FromStatus: ", status));
    }
  }

  static HpackParseResult FromStatusWithKey(HpackParseStatus status,
                                            absl::string_view key) {
    auto r = FromStatus(status);
    if (r.state_ != nullptr) {
      r.state_->key = std::string(key);
    }
    return r;
  }

  static HpackParseResult MetadataParseError(absl::string_view key) {
    HpackParseResult r{HpackParseStatus::kMetadataParseError};
    r.state_->key = std::string(key);
    return r;
  }

  static HpackParseResult AddBeforeTableSizeUpdated(uint32_t current_size,
                                                    uint32_t max_size) {
    HpackParseResult p{HpackParseStatus::kAddBeforeTableSizeUpdated};
    p.state_->illegal_table_size_change =
        IllegalTableSizeChange{current_size, max_size};
    return p;
  }

  static HpackParseResult MaliciousVarintEncodingError() {
    return HpackParseResult{HpackParseStatus::kMaliciousVarintEncoding};
  }

  static HpackParseResult IllegalHpackOpCode() {
    return HpackParseResult{HpackParseStatus::kIllegalHpackOpCode};
  }

  static HpackParseResult InvalidMetadataError(ValidateMetadataResult result,
                                               absl::string_view key) {
    DCHECK(result != ValidateMetadataResult::kOk);
    HpackParseResult p{HpackParseStatus::kInvalidMetadata};
    p.state_->key = std::string(key);
    p.state_->validate_metadata_result = result;
    return p;
  }

  static HpackParseResult IncompleteHeaderAtBoundaryError() {
    return HpackParseResult{HpackParseStatus::kIncompleteHeaderAtBoundary};
  }

  static HpackParseResult VarintOutOfRangeError(uint32_t value,
                                                uint8_t last_byte) {
    HpackParseResult p{HpackParseStatus::kVarintOutOfRange};
    p.state_->varint_out_of_range = VarintOutOfRange{last_byte, value};
    return p;
  }

  static HpackParseResult InvalidHpackIndexError(uint32_t index) {
    HpackParseResult p{HpackParseStatus::kInvalidHpackIndex};
    p.state_->invalid_hpack_index = index;
    return p;
  }

  static HpackParseResult IllegalTableSizeChangeError(uint32_t new_size,
                                                      uint32_t max_size) {
    HpackParseResult p{HpackParseStatus::kIllegalTableSizeChange};
    p.state_->illegal_table_size_change =
        IllegalTableSizeChange{new_size, max_size};
    return p;
  }

  static HpackParseResult TooManyDynamicTableSizeChangesError() {
    return HpackParseResult{HpackParseStatus::kTooManyDynamicTableSizeChanges};
  }

  static HpackParseResult SoftMetadataLimitExceededError(
      grpc_metadata_batch* metadata, uint32_t frame_length, uint32_t limit) {
    HpackParseResult p{HpackParseStatus::kSoftMetadataLimitExceeded};
    p.state_->metadata_limit_exceeded =
        MetadataLimitExceeded{frame_length, limit, metadata};
    return p;
  }

  static HpackParseResult HardMetadataLimitExceededError(
      grpc_metadata_batch* metadata, uint32_t frame_length, uint32_t limit) {
    HpackParseResult p{HpackParseStatus::kHardMetadataLimitExceeded};
    p.state_->metadata_limit_exceeded =
        MetadataLimitExceeded{frame_length, limit, metadata};
    return p;
  }

  static HpackParseResult HardMetadataLimitExceededByKeyError(
      uint32_t key_length, uint32_t limit) {
    HpackParseResult p{HpackParseStatus::kHardMetadataLimitExceededByKey};
    p.state_->metadata_limit_exceeded_by_atom =
        MetadataLimitExceededByAtom{key_length, limit};
    return p;
  }

  static HpackParseResult HardMetadataLimitExceededByValueError(
      absl::string_view key, uint32_t value_length, uint32_t limit) {
    HpackParseResult p{HpackParseStatus::kHardMetadataLimitExceededByValue};
    p.state_->metadata_limit_exceeded_by_atom =
        MetadataLimitExceededByAtom{value_length, limit};
    p.state_->key = std::string(key);
    return p;
  }

  absl::Status Materialize() const;

 private:
  explicit HpackParseResult(HpackParseStatus status) {

    if (status != HpackParseStatus::kOk) {
      state_ = MakeRefCounted<HpackParseResultState>(status);
    }
  }

  absl::Status BuildMaterialized() const;

  struct VarintOutOfRange {
    uint8_t last_byte;
    uint32_t value;
  };

  struct MetadataLimitExceeded {
    uint32_t frame_length;
    uint32_t limit;
    grpc_metadata_batch* prior;
  };

  struct MetadataLimitExceededByAtom {
    uint32_t atom_length;
    uint32_t limit;
  };

  struct IllegalTableSizeChange {
    uint32_t new_size;
    uint32_t max_size;
  };

  class StatusWrapper {
   public:
    explicit StatusWrapper(HpackParseStatus status) : status_(status) {}

    StatusWrapper(const StatusWrapper&) = default;
    StatusWrapper& operator=(const StatusWrapper&) = default;
    StatusWrapper(StatusWrapper&& other) noexcept
        : status_(std::exchange(other.status_, HpackParseStatus::kMovedFrom)) {}
    StatusWrapper& operator=(StatusWrapper&& other) noexcept {
      status_ = std::exchange(other.status_, HpackParseStatus::kMovedFrom);
      return *this;
    }

    HpackParseStatus get() const { return status_; }

   private:
    HpackParseStatus status_;
  };

  struct HpackParseResultState : public RefCounted<HpackParseResultState> {
    explicit HpackParseResultState(HpackParseStatus incoming_status)
        : status(incoming_status) {}
    StatusWrapper status;
    union {

      ValidateMetadataResult validate_metadata_result;

      VarintOutOfRange varint_out_of_range;

      uint32_t invalid_hpack_index;

      MetadataLimitExceeded metadata_limit_exceeded;

      MetadataLimitExceededByAtom metadata_limit_exceeded_by_atom;

      IllegalTableSizeChange illegal_table_size_change;
    };
    std::string key;
    mutable std::optional<absl::Status> materialized_status;
  };

  RefCountedPtr<HpackParseResultState> state_ = nullptr;
};

}

#endif
