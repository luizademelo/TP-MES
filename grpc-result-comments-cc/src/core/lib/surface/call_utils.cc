Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

// Core gRPC headers and standard library includes
#include "src/core/lib/surface/call_utils.h"

#include <grpc/byte_buffer.h>
#include <grpc/compression.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/call.h>
#include <grpc/impl/propagation_bits.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

// Abseil and other utility headers
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/status_util.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/status_flag.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/lib/surface/validate_metadata.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/match.h"

namespace grpc_core {

// Publishes metadata from grpc_metadata_batch to grpc_metadata_array
// If the array doesn't have enough capacity, it's reallocated with additional space
// is_client indicates whether this is client-side metadata
void PublishMetadataArray(grpc_metadata_batch* md, grpc_metadata_array* array,
                          bool is_client) {
  const auto md_count = md->count();
  if (md_count > array->capacity) {
    // Increase capacity by either the needed amount or 1.5x current capacity
    array->capacity =
        std::max(array->capacity + md->count(), array->capacity * 3 / 2);
    array->metadata = static_cast<grpc_metadata*>(
        gpr_realloc(array->metadata, sizeof(grpc_metadata) * array->capacity));
  }
  // Use encoder to transfer metadata from batch to array
  PublishToAppEncoder encoder(array, md, is_client);
  md->Encode(&encoder);
}

// Converts C-style grpc_metadata array to grpc_metadata_batch format
// Skips "content-length" metadata and logs any append errors
void CToMetadata(grpc_metadata* metadata, size_t count,
                 grpc_metadata_batch* b) {
  for (size_t i = 0; i < count; i++) {
    grpc_metadata* md = &metadata[i];
    auto key = StringViewFromSlice(md->key);

    if (key == "content-length") continue;
    b->Append(key, Slice(CSliceRef(md->value)),
              [md](absl::string_view error, const Slice& value) {
                VLOG(2) << "Append error: key=" << StringViewFromSlice(md->key)
                        << " error=" << error
                        << " value=" << value.as_string_view();
              });
  }
}

// Returns string representation of gRPC operation type
const char* GrpcOpTypeName(grpc_op_type op) {
  switch (op) {
    case GRPC_OP_SEND_INITIAL_METADATA:
      return "SendInitialMetadata";
    case GRPC_OP_SEND_MESSAGE:
      return "SendMessage";
    case GRPC_OP_SEND_STATUS_FROM_SERVER:
      return "SendStatusFromServer";
    case GRPC_OP_SEND_CLOSE_FROM_CLIENT:
      return "SendCloseFromClient";
    case GRPC_OP_RECV_MESSAGE:
      return "RecvMessage";
    case GRPC_OP_RECV_CLOSE_ON_SERVER:
      return "RecvCloseOnServer";
    case GRPC_OP_RECV_INITIAL_METADATA:
      return "RecvInitialMetadata";
    case GRPC_OP_RECV_STATUS_ON_CLIENT:
      return "RecvStatusOnClient";
  }
  Crash("Unreachable");
}

// Asynchronous operation to wait for completion queue operation to finish
// Handles both closure and non-closure completion notifications
Poll<Empty> WaitForCqEndOp::operator()() {
  GRPC_TRACE_LOG(promise_primitives, INFO)
      << Activity::current()->DebugTag() << "WaitForCqEndOp[" << this << "] "
      << StateString(state_);
  if (auto* n = std::get_if<NotStarted>(&state_)) {
    if (n->is_closure) {
      // Directly execute closure if that's the notification mechanism
      ExecCtx::Run(DEBUG_LOCATION, static_cast<grpc_closure*>(n->tag),
                   std::move(n->error));
      return Empty{};
    } else {
      // For non-closure notifications, initiate completion queue operation
      auto not_started = std::move(*n);
      auto& started =
          state_.emplace<Started>(GetContext<Activity>()->MakeOwningWaker());
      grpc_cq_end_op(
          not_started.cq, not_started.tag, std::move(not_started.error),
          [](void* p, grpc_cq_completion*) {
            auto started = static_cast<Started*>(p);
            auto wakeup = std::move(started->waker);
            started->done.store(true, std::memory_order_release);
            wakeup.Wakeup();
          },
          &started, &started.completion);
    }
  }
  auto& started = std::get<Started>(state_);
  if (started.done.load(std::memory_order_acquire)) {
    return Empty{};
  } else {
    return Pending{};
  }
}

// Returns string representation of the operation state for debugging
std::string WaitForCqEndOp::StateString(const State& state) {
  return Match(
      state,
      [](const NotStarted& x) {
        return absl::StrFormat(
            "NotStarted{is_closure=%s, tag=%p, error=%s, cq=%p}",
            x.is_closure ? "true" : "false", x.tag, x.error.ToString(), x.cq);
      },
      [](const Started& x) {
        return absl::StrFormat(
            "Started{completion=%p, done=%s}", &x.completion,
            x.done.load(std::memory_order_relaxed) ? "true" : "false");
      },
      [](const Invalid&) -> std::string { return "Invalid{}"; });
}

// Creates a human-readable error string from server trailing metadata
// Includes status code, message, and any context annotations
std::string MakeErrorString(const ServerMetadata* trailing_metadata) {
  std::string out = absl::StrCat(
      trailing_metadata->get(GrpcStatusFromWire()).value_or(false)
          ? "Error received from peer"
          : "Error generated by client",
      " grpc_status: ",
      grpc_status_code_to_string(trailing_metadata->get(GrpcStatusMetadata())
                                     .value_or(GRPC_STATUS_UNKNOWN)));
  if (const Slice* message =
          trailing_metadata->get_pointer(GrpcMessageMetadata())) {
    absl::StrAppend(&out, "\ngrpc_message: ", message->as_string_view());
  }
  if (auto annotations = trailing_metadata->get_pointer(GrpcStatusContext())) {
    absl::StrAppend(&out, "\nStatus Context:");
    for (const std::string& annotation : *annotations) {
      absl::StrAppend(&out, "\n  ", annotation);
    }
  }
  return out;
}

// Validates metadata array:
// - Checks count doesn't exceed INT_MAX
// - Validates each metadata key and value
// - Checks binary header constraints and value length
bool ValidateMetadata(size_t count, grpc_metadata* metadata) {
  if (count > INT_MAX) {
    return false;
  }
  for (size_t i = 0; i < count; i++) {
    grpc_metadata* md = &metadata[i];
    if (!GRPC_LOG_IF_ERROR("validate_metadata",
                           grpc_validate_header_key_is_legal(md->key))) {
      return false;
    } else if (!grpc_is_binary_header_internal(md->key) &&
               !GRPC_LOG_IF_ERROR(
                   "validate_metadata",
                   grpc_validate_header_nonbin_value_is_legal(md->value))) {
      return false;
    } else if (GRPC_SLICE_LENGTH(md->value) >= UINT32_MAX) {
      return false;
    }
  }
  return true;
}

// Immediately completes an operation on a completion queue
// Handles both closure and non-closure completion mechanisms
void EndOpImmediately(grpc_completion_queue* cq, void* notify_tag,
                      bool is_notify_tag_closure) {
  if (!is_notify_tag_closure) {
    CHECK(grpc_cq_begin_op(cq, notify_tag));
    grpc_cq_end_op(
        cq, notify_tag, absl::OkStatus(),
        [](void*, grpc_cq_completion* completion) { gpr_free(completion); },
        nullptr,
        static_cast<grpc_cq_completion*>(
            gpr_malloc(sizeof(grpc_cq_completion))));
  } else {
    Closure::Run(DEBUG_LOCATION, static_cast<grpc_closure*>(notify_tag),
                 absl::OkStatus());
  }
}

}  // namespace grpc_core
```