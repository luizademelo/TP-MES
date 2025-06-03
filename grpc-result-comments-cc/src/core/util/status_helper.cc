Here's the commented version of the code:

```c++
// Copyright 2021 the gRPC authors.

#include "src/core/util/status_helper.h"

#include <grpc/status.h>
#include <string.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/strings/cord.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/time/clock.h"
#include "google/protobuf/any.upb.h"
#include "google/rpc/status.upb.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/slice/percent_encoding.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/status_conversion.h"
#include "src/core/util/time.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"

namespace grpc_core {

namespace {

// Constants for status property type URLs
#define TYPE_URL_PREFIX "type.googleapis.com/grpc.status."
#define TYPE_INT_TAG "int."
#define TYPE_STR_TAG "str."
#define TYPE_TIME_TAG "time."
#define TYPE_CHILDREN_TAG "children"
#define TYPE_URL(name) (TYPE_URL_PREFIX name)
const absl::string_view kTypeUrlPrefix = TYPE_URL_PREFIX;
const absl::string_view kTypeIntTag = TYPE_INT_TAG;
const absl::string_view kTypeStrTag = TYPE_STR_TAG;
const absl::string_view kTypeTimeTag = TYPE_TIME_TAG;
const absl::string_view kTypeChildrenTag = TYPE_CHILDREN_TAG;
const absl::string_view kChildrenPropertyUrl = TYPE_URL(TYPE_CHILDREN_TAG);

// Returns the type URL for a given integer status property
const char* GetStatusIntPropertyUrl(StatusIntProperty key) {
  switch (key) {
    case StatusIntProperty::kStreamId:
      return TYPE_URL(TYPE_INT_TAG "stream_id");
    case StatusIntProperty::kRpcStatus:
      return TYPE_URL(TYPE_INT_TAG "grpc_status");
    case StatusIntProperty::kHttp2Error:
      return TYPE_URL(TYPE_INT_TAG "http2_error");
    case StatusIntProperty::ChannelConnectivityState:
      return TYPE_URL(TYPE_INT_TAG "channel_connectivity_state");
    case StatusIntProperty::kLbPolicyDrop:
      return TYPE_URL(TYPE_INT_TAG "lb_policy_drop");
  }
  GPR_UNREACHABLE_CODE(return "unknown");
}

// Returns the type URL for a given string status property
const char* GetStatusStrPropertyUrl(StatusStrProperty key) {
  switch (key) {
    case StatusStrProperty::kGrpcMessage:
      return TYPE_URL(TYPE_STR_TAG "grpc_message");
  }
  GPR_UNREACHABLE_CODE(return "unknown");
}

// Encodes a 32-bit unsigned integer into a byte array (little-endian)
void EncodeUInt32ToBytes(uint32_t v, char* buf) {
  buf[0] = v & 0xFF;
  buf[1] = (v >> 8) & 0xFF;
  buf[2] = (v >> 16) & 0xFF;
  buf[3] = (v >> 24) & 0xFF;
}

// Decodes a 32-bit unsigned integer from a byte array (little-endian)
uint32_t DecodeUInt32FromBytes(const char* buf) {
  const unsigned char* ubuf = reinterpret_cast<const unsigned char*>(buf);
  return ubuf[0] | (static_cast<uint32_t>(ubuf[1]) << 8) |
         (static_cast<uint32_t>(ubuf[2]) << 16) |
         (static_cast<uint32_t>(ubuf[3]) << 24);
}

// Parses a sequence of child statuses from a Cord containing serialized protos
std::vector<absl::Status> ParseChildren(absl::Cord children) {
  std::vector<absl::Status> result;
  upb::Arena arena;

  absl::string_view buf = children.Flatten();
  size_t cur = 0;
  while (buf.size() - cur >= sizeof(uint32_t)) {
    // Read message size prefix
    size_t msg_size = DecodeUInt32FromBytes(buf.data() + cur);
    cur += sizeof(uint32_t);
    CHECK(buf.size() - cur >= msg_size);
    // Parse the status proto message
    google_rpc_Status* msg =
        google_rpc_Status_parse(buf.data() + cur, msg_size, arena.ptr());
    cur += msg_size;
    result.push_back(internal::StatusFromProto(msg));
  }
  return result;
}

}  // namespace

// Creates a new status with optional child statuses
absl::Status StatusCreate(absl::StatusCode code, absl::string_view msg,
                          const DebugLocation& ,
                          std::vector<absl::Status> children) {
  absl::Status s(code, msg);
  for (const absl::Status& child : children) {
    if (!child.ok()) {
      StatusAddChild(&s, child);
    }
  }
  return s;
}

namespace {

// Creates a new status with the same payloads as the original but different code
absl::Status ReplaceStatusCode(const absl::Status& status,
                               absl::StatusCode code) {
  absl::Status new_status(code, status.message());
  status.ForEachPayload(
      [&](absl::string_view type_url, const absl::Cord& payload) {
        new_status.SetPayload(type_url, payload);
      });
  return new_status;
}

}  // namespace

// Sets an integer property on a status
void StatusSetInt(absl::Status* status, StatusIntProperty key, intptr_t value) {
  if (IsErrorFlattenEnabled() && key == StatusIntProperty::kRpcStatus) {
    // Special handling for RPC status codes when flattening is enabled
    *status = ReplaceStatusCode(*status, static_cast<absl::StatusCode>(value));
    return;
  }
  status->SetPayload(GetStatusIntPropertyUrl(key),
                     absl::Cord(std::to_string(value)));
}

// Gets an integer property from a status
std::optional<intptr_t> StatusGetInt(const absl::Status& status,
                                     StatusIntProperty key) {
  if (IsErrorFlattenEnabled() && key == StatusIntProperty::kRpcStatus) {
    return static_cast<intptr_t>(status.code());
  }
  auto p = status.GetPayload(GetStatusIntPropertyUrl(key));
  if (p.has_value()) {
    auto sv = p->TryFlat();
    intptr_t value;
    if (sv.has_value()) {
      if (absl::SimpleAtoi(*sv, &value)) {
        return value;
      }
    } else {
      if (absl::SimpleAtoi(std::string(*p), &value)) {
        return value;
      }
    }
  }
  return {};
}

namespace {

// Creates a new status with the same payloads as the original but different message
absl::Status ReplaceStatusMessage(const absl::Status& status,
                                  absl::string_view message) {
  absl::Status new_status(status.code(), message);
  status.ForEachPayload(
      [&](absl::string_view type_url, const absl::Cord& payload) {
        new_status.SetPayload(type_url, payload);
      });
  return new_status;
}

}  // namespace

// Sets a string property on a status
void StatusSetStr(absl::Status* status, StatusStrProperty key,
                  absl::string_view value) {
  if (IsErrorFlattenEnabled() && key == StatusStrProperty::kGrpcMessage) {
    if (!status->ok()) {
      *status = ReplaceStatusMessage(
          *status, status->message().empty()
                       ? value
                       : absl::StrCat(value, " (", status->message(), ")"));
    }
    return;
  }
  status->SetPayload(GetStatusStrPropertyUrl(key), absl::Cord(value));
}

// Gets a string property from a status
std::optional<std::string> StatusGetStr(const absl::Status& status,
                                        StatusStrProperty key) {
  if (IsErrorFlattenEnabled() && key == StatusStrProperty::kGrpcMessage) {
    return std::string(status.message());
  }
  auto p = status.GetPayload(GetStatusStrPropertyUrl(key));
  if (p.has_value()) {
    return std::string(*p);
  }
  return {};
}

// Adds a child status to a parent status
void StatusAddChild(absl::Status* status, absl::Status child) {
  if (IsErrorFlattenEnabled()) {
    // When flattening is enabled, merge child status into parent
    if (child.ok()) return;

    if (status->ok()) {
      *status = std::move(child);
      return;
    }

    // Combine status codes and messages
    absl::Status new_status(
        status->code() == absl::StatusCode::kUnknown ? child.code()
                                                     : status->code(),
        absl::StrCat(status->message(), " (", child.message(), ")"));

    // Copy payloads from both statuses
    status->ForEachPayload(
        [&](absl::string_view type_url, const absl::Cord& payload) {
          new_status.SetPayload(type_url, payload);
        });
    child.ForEachPayload(
        [&](absl::string_view type_url, const absl::Cord& payload) {
          // Only set payload if it doesn't already exist
          if (!new_status.GetPayload(type_url).has_value()) {
            new_status.SetPayload(type_url, payload);
          }
        });
    *status = std::move(new_status);
    return;
  }

  // When flattening is disabled, serialize child status as a proto
  upb::Arena arena;
  google_rpc_Status* msg = internal::StatusToProto(child, arena.ptr());
  size_t buf_len = 0;
  char* buf = google_rpc_Status_serialize(msg, arena.ptr(), &buf_len);

  // Append serialized child to existing children (if any)
  auto old_children = status->GetPayload(kChildrenPropertyUrl);
  absl::Cord children;
  if (old_children.has_value()) {
    children = *old_children;
  }
  char head_buf[sizeof(uint32_t)];
  EncodeUInt32ToBytes(buf_len, head_buf);
  children.Append(absl::string_view(head_buf, sizeof(uint32_t)));
  children.Append(absl::string_view(buf, buf_len));
  status->SetPayload(kChildrenPropertyUrl, std::move(children));
}

// Gets all child statuses from a status
std::vector<absl::Status> StatusGetChildren(absl::Status status) {
  auto children = status.GetPayload(kChildrenPropertyUrl);
  return children.has_value() ? ParseChildren(*children)
                              : std::vector<absl::Status>();
}

// Converts a status to a human-readable string representation
std::string StatusToString(const absl::Status& status) {
  if (status.ok()) {
    return "OK";
  }
  std::string head;
  absl::StrAppend(&head, absl::StatusCodeToString(status.code()));
  if (!status.message().empty()) {
    absl::StrAppend(&head, ":", status.message());
  }
  std::vector<std::string> kvs;
  std::optional<absl::Cord> children;
  
  // Process all payloads
  status.ForEachPayload([&](absl::string_view type_url,
                            const absl::Cord& payload) {
    if (absl::StartsWith(type_url, kTypeUrlPrefix)) {
      type_url.remove_prefix(kTypeUrlPrefix.size());
      if (type_url == kTypeChildrenTag) {
        children = payload;
        return;
      }
      absl::string_view payload_view;
      std::string payload_storage;
      if (payload.TryFlat().has_value()) {
        payload_view = payload.TryFlat().value();
      } else {
        payload_storage = std::string(payload);
        payload_view = payload_storage;
      }
      // Handle different types of payloads
      if (absl::StartsWith(type_url, kTypeIntTag)) {
        type_url.remove_prefix(kTypeIntTag.size());
        kvs.push_back(absl::StrCat(type_url, ":", payload_view));
      } else if (absl::StartsWith(type_url, kTypeStrTag)) {
        type_url.remove_prefix(kTypeStrTag.size());
        kvs.push_back(absl::StrCat(type_url, ":\"",
                                   absl::CHexEscape(payload_view), "\""));
      } else if (absl::StartsWith(type_url, kTypeTimeTag)) {
        type_url.remove_prefix(kTypeTimeTag.size());
        absl::Time t;
        if (absl::ParseTime(absl::RFC3339_full, payload_view, &t, nullptr)) {
          kvs.push_back(
              absl::StrCat(type_url, ":\"", absl::FormatTime(t), "\""));
        } else {
          kvs.push_back(absl::StrCat(type_url, ":\"",
                                     absl::CHexEscape(payload_view), "\""));
        }
      } else {
        kvs.push_back(absl::StrCat(type_url, ":\"",
                                   absl::CHexEscape(payload_view), "\""));
      }
    } else {
      // Handle non-standard payloads
      auto payload_view = payload.TryFlat();
      std::string payload_str = absl::CHexEscape(
          payload_view.has_value() ? *payload_view : std::string(payload));
      kvs.push_back(absl::StrCat(type_url, ":\"", payload_str, "\""));
    }
  });
  
  // Process child statuses if any
  if (children.has_value()) {
    std::vector<absl::Status> children_status = ParseChildren(*children);
    std::vector<std::string> children_text;
    children_text.reserve(children_status.size());
    for (const absl::Status& child_status : children_status) {
      children_text.push_back(StatusToString(child_status));
    }
    kvs.push_back(
        absl::StrCat("children:[", absl::StrJoin(children_text, ", "), "]"));
  }
  return kvs.empty() ? head
                     : absl::StrCat(head, " {", absl::StrJoin(kvs, ", "), "}");
}

// Adds a prefix to a status message
absl::Status AddMessagePrefix(absl::string_view prefix,
                              const absl::Status& status) {
  return ReplaceStatusMessage(status,
                              absl::StrCat(prefix, ": ", status.message()));
}

namespace internal {

// Converts an absl::Status to a google.rpc.Status proto message
google_rpc_Status* StatusToProto(const absl::Status& status, upb_Arena* arena) {
  google_rpc_Status* msg = google_rpc_Status_new(arena);
  google_rpc_Status_set_code(msg, static_cast<int32_t>(status.code()));

  // Percent-encode the status message
  Slice message_percent_slice =
      PercentEncodeSlice(Slice::FromExternalString(status.message()),
                         PercentEncodingType::Compatible);
  char* message_percent = reinterpret_cast<char*>(
      upb_Arena_Malloc(arena, message_percent_slice.length()));
  if (!message_percent_slice.empty()) {
    memcpy(message_percent, message_percent_slice.data(),
           message_percent_slice.length());
  }
  google_rpc_Status_set_message(
      msg, upb_StringView_FromDataAndSize(message_percent,
                                          message_percent_slice.length()));
  
  // Convert all payloads to proto Any messages
  status.ForEachPayload([&](absl::string_view type_url,
                            const absl::Cord& payload) {
    google_protobuf_Any* any = google_rpc_Status_add_details(msg, arena);
    char* type_url_buf =
        reinterpret_cast<char*>(upb_Arena_Malloc(arena, type_url.size()));
    memcpy(type_url_buf, type_url.data(), type_url.size());
    google_protobuf_Any_set_type_url(
        any, upb_StringView_FromDataAndSize(type_url_buf, type_url.size()));
    auto v_view = payload.TryFlat();
    if (v_view.has_value()) {
      google_protobuf_Any_set_value(
          any, upb_StringView_FromDataAndSize(v_view->data(), v_view->size()));
    } else {
      // For non-flat payloads, copy all chunks
      char* buf =
          reinterpret_cast<char*>(upb_Arena_Malloc(arena, payload.size()));
      char* cur = buf;
      for (absl::string_view chunk : payload.Chunks()) {
        memcpy(cur, chunk.data(), chunk.size());
        cur += chunk.size();
      }
      google_protobuf_Any_set_value(
          any, upb_StringView_FromDataAndSize(buf, payload.size()));
    }
  });
  return msg;
}

// Converts a google.rpc.Status proto message to an absl::Status
absl::Status StatusFromProto(google_rpc_Status* msg) {
  int32_t code = google_rpc_Status_code(msg);
  upb_StringView message_percent_upb = google_rpc_Status_message(msg);
  Slice message_percent_slice = Slice::FromExternalString(
      absl::string_view(message_percent_upb.data, message_percent_upb.size));
  // Percent-decode the message
  Slice message_slice =
      PermissivePercentDecodeSlice(std::move(message_percent_slice));
  absl::Status status(
      static_cast<absl::StatusCode>(code),
      absl::string_view(reinterpret_cast<const char*>(message_slice.data()),
                        message_slice.size()));
  
  // Convert all Any messages to payloads
  size_t detail_len;
  const google_protobuf_Any* const* details =
      google_rpc_Status_details(msg, &detail_len);
  for (size_t i = 0; i < detail_len; i++) {
    upb_StringView type