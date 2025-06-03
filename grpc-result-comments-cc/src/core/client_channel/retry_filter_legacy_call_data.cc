Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/client_channel/retry_filter_legacy_call_data.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <memory>
#include <new>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/status_util.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/client_channel/retry_service_config.h"
#include "src/core/client_channel/retry_throttle.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/backoff.h"
#include "src/core/util/construct_destruct.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_core {

using TaskHandle = grpc_event_engine::experimental::EventEngine::TaskHandle;

// CallStackDestructionBarrier ensures that the call stack is not destroyed
// until all LB calls have been destroyed.
class RetryFilter::LegacyCallData::CallStackDestructionBarrier final
    : public RefCounted<CallStackDestructionBarrier, PolymorphicRefCount,
                        UnrefCallDtor> {
 public:
  CallStackDestructionBarrier() {}

  ~CallStackDestructionBarrier() override {
    // Run the on_call_stack_destruction closure when destroyed
    ExecCtx::Run(DEBUG_LOCATION, on_call_stack_destruction_, absl::OkStatus());
  }

  void set_on_call_stack_destruction(grpc_closure* on_call_stack_destruction) {
    on_call_stack_destruction_ = on_call_stack_destruction;
  }

  grpc_closure* MakeLbCallDestructionClosure(
      RetryFilter::LegacyCallData* calld) {
    Ref().release();  // Ref will be released in OnLbCallDestructionComplete
    grpc_closure* on_lb_call_destruction_complete =
        calld->arena_->New<grpc_closure>();
    GRPC_CLOSURE_INIT(on_lb_call_destruction_complete,
                      OnLbCallDestructionComplete, this, nullptr);
    return on_lb_call_destruction_complete;
  }

 private:
  static void OnLbCallDestructionComplete(void* arg,
                                          grpc_error_handle /*error*/) {
    auto* self = static_cast<CallStackDestructionBarrier*>(arg);
    self->Unref();  // Release ref taken in MakeLbCallDestructionClosure
  }

  grpc_closure* on_call_stack_destruction_ = nullptr;
};

// CallAttempt represents a single attempt to make an RPC call, including
// retry attempts.
RetryFilter::LegacyCallData::CallAttempt::CallAttempt(
    RetryFilter::LegacyCallData* calld, bool is_transparent_retry)
    : RefCounted(GRPC_TRACE_FLAG_ENABLED(retry) ? "CallAttempt" : nullptr),
      calld_(calld),
      started_send_initial_metadata_(false),
      completed_send_initial_metadata_(false),
      started_send_trailing_metadata_(false),
      completed_send_trailing_metadata_(false),
      started_recv_initial_metadata_(false),
      completed_recv_initial_metadata_(false),
      started_recv_trailing_metadata_(false),
      completed_recv_trailing_metadata_(false),
      sent_cancel_stream_(false),
      seen_recv_trailing_metadata_from_surface_(false),
      abandoned_(false) {
  // Create the LB call for this attempt
  lb_call_ = calld->CreateLoadBalancedCall(
      [this]() {
        lb_call_committed_ = true;
        if (calld_->retry_committed_) {
          auto* service_config_call_data =
              DownCast<ClientChannelServiceConfigCallData*>(
                  calld_->arena_->GetContext<ServiceConfigCallData>());
          service_config_call_data->Commit();
        }
      },
      is_transparent_retry);
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld << " attempt=" << this
      << ": created attempt, lb_call=" << lb_call_.get();

  // Set up per-attempt recv timeout if configured
  if (calld->retry_policy_ != nullptr &&
      calld->retry_policy_->per_attempt_recv_timeout().has_value()) {
    const Duration per_attempt_recv_timeout =
        *calld->retry_policy_->per_attempt_recv_timeout();
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld->chand_ << " calld=" << calld
        << " attempt=" << this << ": per-attempt timeout in "
        << per_attempt_recv_timeout.millis() << " ms";

    GRPC_CALL_STACK_REF(calld->owning_call_, "OnPerAttemptRecvTimer");
    Ref(DEBUG_LOCATION, "OnPerAttemptRecvTimer").release();
    per_attempt_recv_timer_handle_ = calld_->chand_->event_engine()->RunAfter(
        per_attempt_recv_timeout, [this] {
          ExecCtx exec_ctx;
          OnPerAttemptRecvTimer();
        });
  }
}

RetryFilter::LegacyCallData::CallAttempt::~CallAttempt() {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this << ": destroying call attempt";
}

// Free cached send op data after the call attempt is committed
void RetryFilter::LegacyCallData::CallAttempt::
    FreeCachedSendOpDataAfterCommit() {
  if (completed_send_initial_metadata_) {
    calld_->FreeCachedSendInitialMetadata();
  }
  for (size_t i = 0; i < completed_send_message_count_; ++i) {
    calld_->FreeCachedSendMessage(i);
  }
  if (completed_send_trailing_metadata_) {
    calld_->FreeCachedSendTrailingMetadata();
  }
}

// Check if pending batch contains unstarted send ops
bool RetryFilter::LegacyCallData::CallAttempt::
    PendingBatchContainsUnstartedSendOps(PendingBatch* pending) {
  if (pending->batch->on_complete == nullptr) return false;
  if (pending->batch->send_initial_metadata &&
      !started_send_initial_metadata_) {
    return true;
  }
  if (pending->batch->send_message &&
      started_send_message_count_ < calld_->send_messages_.size()) {
    return true;
  }
  if (pending->batch->send_trailing_metadata &&
      !started_send_trailing_metadata_) {
    return true;
  }
  return false;
}

// Check if there are send ops to replay
bool RetryFilter::LegacyCallData::CallAttempt::HaveSendOpsToReplay() {
  return started_send_message_count_ < calld_->send_messages_.size() ||
         (calld_->seen_send_trailing_metadata_ &&
          !started_send_trailing_metadata_);
}

// Switch to fast path if possible
void RetryFilter::LegacyCallData::CallAttempt::MaybeSwitchToFastPath() {
  if (!calld_->retry_committed_) return;
  if (calld_->committed_call_ != nullptr) return;
  if (per_attempt_recv_timer_handle_ != TaskHandle::kInvalid) return;
  if (HaveSendOpsToReplay()) return;
  if (recv_trailing_metadata_internal_batch_ != nullptr) return;

  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this
      << ": retry state no longer needed; "
         "moving LB call to parent and unreffing the call attempt";
  calld_->committed_call_ = std::move(lb_call_);
  calld_->call_attempt_.reset(DEBUG_LOCATION, "MaybeSwitchToFastPath");
}

// Create a batch for replaying previously completed ops
RetryFilter::LegacyCallData::CallAttempt::BatchData*
RetryFilter::LegacyCallData::CallAttempt::MaybeCreateBatchForReplay() {
  BatchData* replay_batch_data = nullptr;

  // Replay send_initial_metadata if needed
  if (calld_->seen_send_initial_metadata_ && !started_send_initial_metadata_ &&
      !calld_->pending_send_initial_metadata_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_initial_metadata op";
    replay_batch_data = CreateBatch(1, true /* set_on_complete */);
    replay_batch_data->AddRetriableSendInitialMetadataOp();
  }

  // Replay send_message if needed
  if (started_send_message_count_ < calld_->send_messages_.size() &&
      started_send_message_count_ == completed_send_message_count_ &&
      !calld_->pending_send_message_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_message op";
    if (replay_batch_data == nullptr) {
      replay_batch_data = CreateBatch(1, true /* set_on_complete */);
    }
    replay_batch_data->AddRetriableSendMessageOp();
  }

  // Replay send_trailing_metadata if needed
  if (calld_->seen_send_trailing_metadata_ &&
      started_send_message_count_ == calld_->send_messages_.size() &&
      !started_send_trailing_metadata_ &&
      !calld_->pending_send_trailing_metadata_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_trailing_metadata op";
    if (replay_batch_data == nullptr) {
      replay_batch_data = CreateBatch(1, true /* set_on_complete */);
    }
    replay_batch_data->AddRetriableSendTrailingMetadataOp();
  }
  return replay_batch_data;
}

namespace {

// Closure to start a batch in the call combiner
void StartBatchInCallCombiner(void* arg, grpc_error_handle /*error*/) {
  grpc_transport_stream_op_batch* batch =
      static_cast<grpc_transport_stream_op_batch*>(arg);
  auto* lb_call =
      static_cast<ClientChannelFilter::FilterBasedLoadBalancedCall*>(
          batch->handler_private.extra_arg);
  // Note: This will release the call combiner.
  lb_call->StartTransportStreamOpBatch(batch);
}

}  // namespace

// Add a closure for a batch to the closure list
void RetryFilter::LegacyCallData::CallAttempt::AddClosureForBatch(
    grpc_transport_stream_op_batch* batch, const char* reason,
    CallCombinerClosureList* closures) {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this << ": adding batch (" << reason
      << "): " << grpc_transport_stream_op_batch_string(batch, false);
  batch->handler_private.extra_arg = lb_call_.get();
  GRPC_CLOSURE_INIT(&batch->handler_private.closure, StartBatchInCallCombiner,
                    batch, grpc_schedule_on_exec_ctx);
  closures->Add(&batch->handler_private.closure, absl::OkStatus(), reason);
}

// Add a batch for internal recv_trailing_metadata
void RetryFilter::LegacyCallData::CallAttempt::
    AddBatchForInternalRecvTrailingMetadata(CallCombinerClosureList* closures) {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this
      << ": call failed but recv_trailing_metadata not started; "
         "starting it internally";

  BatchData* batch_data = CreateBatch(2, false /* set_on_complete */);
  batch_data->AddRetriableRecvTrailingMetadataOp();
  recv_trailing_metadata_internal_batch_.reset(batch_data);
  AddClosureForBatch(batch_data->batch(),
                     "starting internal recv_trailing_metadata", closures);
}

// Maybe add a batch for cancel op
void RetryFilter::LegacyCallData::CallAttempt::MaybeAddBatchForCancelOp(
    grpc_error_handle error, CallCombinerClosureList* closures) {
  if (sent_cancel_stream_) {
    return;
  }
  sent_cancel_stream_ = true;
  BatchData* cancel_batch_data = CreateBatch(1, true /* set_on_complete */);
  cancel_batch_data->AddCancelStreamOp(error);
  AddClosureForBatch(cancel_batch_data->batch(),
                     "start cancellation batch on call attempt", closures);
}

// Add batches for pending batches
void RetryFilter::LegacyCallData::CallAttempt::AddBatchesForPendingBatches(
    CallCombinerClosureList* closures) {
  for (size_t i = 0; i < GPR_ARRAY_SIZE(calld_->pending_batches_); ++i) {
    PendingBatch* pending = &calld_->pending_batches_[i];
    grpc_transport_stream_op_batch* batch = pending->batch;
    if (batch == nullptr) continue;
    bool has_send_ops = false;

    // Check send_initial_metadata
    if (batch->send_initial_metadata) {
      if (started_send_initial_metadata_) continue;
      has_send_ops = true;
    }
    
    // Check send_message
    if (batch->send_message) {
      if (completed_send_message_count_ < started_send_message_count_ ||
          completed_send_message_count_ ==
              (calld_->send_messages_.size() + !pending->send_ops_cached)) {
        continue;
      }
      has_send_ops = true;
    }

    // Check send_trailing_metadata
    if (batch->send_trailing_metadata) {
      if (started_send_message_count_ + batch->send_message <
              calld_->send_messages_.size() ||
          started_send_trailing_metadata_) {
        continue;
      }
      has_send_ops = true;
    }
    
    // Count callbacks needed
    int num_callbacks = has_send_ops;
    if (batch->recv_initial_metadata) {
      if (started_recv_initial_metadata_) continue;
      ++num_callbacks;
    }
    if (batch->recv_message) {
      if (completed_recv_message_count_ < started_recv_message_count_ ||
          recv_message_ready_deferred_batch_ != nullptr) {
        continue;
      }
      ++num_callbacks;
    }
    if (batch->recv_trailing_metadata) {
      if (started_recv_trailing_metadata_) {
        seen_recv_trailing_metadata_from_surface_ = true;

        if (GPR_UNLIKELY(recv_trailing_metadata_internal_batch_ != nullptr)) {
          if (completed_recv_trailing_metadata_) {
            closures->Add(
                &recv_trailing_metadata_ready_, recv_trailing_metadata_error_,
                "re-executing recv_trailing_metadata_ready to propagate "
                "internally triggered result");
            recv_trailing_metadata_internal_batch_.release();
          } else {
            recv_trailing_metadata_internal_batch_.reset(
                DEBUG_LOCATION,
                "internally started recv_trailing_metadata batch pending and "
                "recv_trailing_metadata started from surface");
          }
          recv_trailing_metadata_error_ = absl::OkStatus();
        }

        if (num_callbacks == 0) continue;
      } else {
        ++num_callbacks;
      }
    }

    // If retry is committed and not a trailing metadata batch, just forward it
    if (calld_->retry_committed_ && !pending->send_ops_cached &&
        (!batch->recv_trailing_metadata || !started_recv_trailing_metadata_)) {
      AddClosureForBatch(
          batch,
          "start non-replayable pending batch on call attempt after commit",
          closures);
      calld_->PendingBatchClear(pending);
      continue;
    }

    // Create batch data for the pending batch
    BatchData* batch_data =
        Create