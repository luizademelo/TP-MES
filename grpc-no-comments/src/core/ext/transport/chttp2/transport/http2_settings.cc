
// Copyright 2017 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_settings.h"

#include <grpc/support/port_platform.h>

#include "absl/strings/str_cat.h"
#include "src/core/ext/transport/chttp2/transport/frame.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/util/useful.h"

using grpc_core::http2::Http2ErrorCode;

namespace grpc_core {

void Http2Settings::Diff(
    bool is_first_send, const Http2Settings& old,
    absl::FunctionRef<void(uint16_t key, uint32_t value)> cb) const {
  if (header_table_size_ != old.header_table_size_) {
    cb(kHeaderTableSizeWireId, header_table_size_);
  }
  if (enable_push_ != old.enable_push_) {
    cb(kEnablePushWireId, enable_push_);
  }
  if (max_concurrent_streams_ != old.max_concurrent_streams_) {
    cb(kMaxConcurrentStreamsWireId, max_concurrent_streams_);
  }
  if (is_first_send || initial_window_size_ != old.initial_window_size_) {
    cb(kInitialWindowSizeWireId, initial_window_size_);
  }
  if (max_frame_size_ != old.max_frame_size_) {
    cb(kMaxFrameSizeWireId, max_frame_size_);
  }
  if (max_header_list_size_ != old.max_header_list_size_) {
    cb(kMaxHeaderListSizeWireId, max_header_list_size_);
  }
  if (allow_true_binary_metadata_ != old.allow_true_binary_metadata_) {
    cb(kGrpcAllowTrueBinaryMetadataWireId, allow_true_binary_metadata_);
  }
  if (preferred_receive_crypto_message_size_ !=
      old.preferred_receive_crypto_message_size_) {
    cb(kGrpcPreferredReceiveCryptoFrameSizeWireId,
       preferred_receive_crypto_message_size_);
  }
  if (allow_security_frame_ != old.allow_security_frame_) {
    cb(kGrpcAllowSecurityFrameWireId, allow_security_frame_);
  }
}

std::string Http2Settings::WireIdToName(uint16_t wire_id) {
  switch (wire_id) {
    case kHeaderTableSizeWireId:
      return std::string(header_table_size_name());
    case kEnablePushWireId:
      return std::string(enable_push_name());
    case kMaxConcurrentStreamsWireId:
      return std::string(max_concurrent_streams_name());
    case kInitialWindowSizeWireId:
      return std::string(initial_window_size_name());
    case kMaxFrameSizeWireId:
      return std::string(max_frame_size_name());
    case kMaxHeaderListSizeWireId:
      return std::string(max_header_list_size_name());
    case kGrpcAllowTrueBinaryMetadataWireId:
      return std::string(allow_true_binary_metadata_name());
    case kGrpcPreferredReceiveCryptoFrameSizeWireId:
      return std::string(preferred_receive_crypto_message_size_name());
    case kGrpcAllowSecurityFrameWireId:
      return std::string(allow_security_frame_name());
    default:
      return absl::StrCat("UNKNOWN (", wire_id, ")");
  }
}

Http2ErrorCode Http2Settings::Apply(uint16_t key, uint32_t value) {
  switch (key) {
    case kHeaderTableSizeWireId:
      header_table_size_ = value;
      break;
    case kEnablePushWireId:
      if (value > 1) return Http2ErrorCode::kProtocolError;
      enable_push_ = value != 0;
      break;
    case kMaxConcurrentStreamsWireId:
      max_concurrent_streams_ = value;
      break;
    case kInitialWindowSizeWireId:
      if (value > max_initial_window_size()) {
        return Http2ErrorCode::kFlowControlError;
      }
      initial_window_size_ = value;
      break;
    case kMaxFrameSizeWireId:
      if (value < min_max_frame_size() || value > max_max_frame_size()) {
        return Http2ErrorCode::kProtocolError;
      }
      max_frame_size_ = value;
      break;
    case kMaxHeaderListSizeWireId:
      max_header_list_size_ = std::min(value, 16777216u);
      break;
    case kGrpcAllowTrueBinaryMetadataWireId:
      if (value > 1) return Http2ErrorCode::kProtocolError;
      allow_true_binary_metadata_ = value != 0;
      break;
    case kGrpcPreferredReceiveCryptoFrameSizeWireId:
      preferred_receive_crypto_message_size_ =
          Clamp(value, min_preferred_receive_crypto_message_size(),
                max_preferred_receive_crypto_message_size());
      break;
    case kGrpcAllowSecurityFrameWireId:
      if (value > 1) return Http2ErrorCode::kProtocolError;
      allow_security_frame_ = value != 0;
      break;
  }
  return Http2ErrorCode::kNoError;
}

std::optional<Http2SettingsFrame> Http2SettingsManager::MaybeSendUpdate() {
  switch (update_state_) {
    case UpdateState::kSending:
      return std::nullopt;
    case UpdateState::kIdle:
      if (local_ == sent_) return std::nullopt;
      break;
    case UpdateState::kFirst:
      break;
  }
  Http2SettingsFrame frame;
  local_.Diff(update_state_ == UpdateState::kFirst, sent_,
              [&frame](uint16_t key, uint32_t value) {
                frame.settings.emplace_back(key, value);
              });
  sent_ = local_;
  update_state_ = UpdateState::kSending;
  return frame;
}

bool Http2SettingsManager::AckLastSend() {
  if (update_state_ != UpdateState::kSending) return false;
  update_state_ = UpdateState::kIdle;
  acked_ = sent_;
  return true;
}

}
