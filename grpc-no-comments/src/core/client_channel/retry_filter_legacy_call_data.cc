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

class RetryFilter::LegacyCallData::CallStackDestructionBarrier final
    : public RefCounted<CallStackDestructionBarrier, PolymorphicRefCount,
                        UnrefCallDtor> {
 public:
  CallStackDestructionBarrier() {}

  ~CallStackDestructionBarrier() override {

    ExecCtx::Run(DEBUG_LOCATION, on_call_stack_destruction_, absl::OkStatus());
  }

  void set_on_call_stack_destruction(grpc_closure* on_call_stack_destruction) {
    on_call_stack_destruction_ = on_call_stack_destruction;
  }

  grpc_closure* MakeLbCallDestructionClosure(
      RetryFilter::LegacyCallData* calld) {
    Ref().release();
    grpc_closure* on_lb_call_destruction_complete =
        calld->arena_->New<grpc_closure>();
    GRPC_CLOSURE_INIT(on_lb_call_destruction_complete,
                      OnLbCallDestructionComplete, this, nullptr);
    return on_lb_call_destruction_complete;
  }

 private:
  static void OnLbCallDestructionComplete(void* arg,
                                          grpc_error_handle ) {
    auto* self = static_cast<CallStackDestructionBarrier*>(arg);
    self->Unref();
  }

  grpc_closure* on_call_stack_destruction_ = nullptr;
};

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

bool RetryFilter::LegacyCallData::CallAttempt::HaveSendOpsToReplay() {

  return started_send_message_count_ < calld_->send_messages_.size() ||
         (calld_->seen_send_trailing_metadata_ &&
          !started_send_trailing_metadata_);
}

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

RetryFilter::LegacyCallData::CallAttempt::BatchData*
RetryFilter::LegacyCallData::CallAttempt::MaybeCreateBatchForReplay() {
  BatchData* replay_batch_data = nullptr;

  if (calld_->seen_send_initial_metadata_ && !started_send_initial_metadata_ &&
      !calld_->pending_send_initial_metadata_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_initial_metadata op";
    replay_batch_data = CreateBatch(1, true );
    replay_batch_data->AddRetriableSendInitialMetadataOp();
  }

  if (started_send_message_count_ < calld_->send_messages_.size() &&
      started_send_message_count_ == completed_send_message_count_ &&
      !calld_->pending_send_message_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_message op";
    if (replay_batch_data == nullptr) {
      replay_batch_data = CreateBatch(1, true );
    }
    replay_batch_data->AddRetriableSendMessageOp();
  }

  if (calld_->seen_send_trailing_metadata_ &&
      started_send_message_count_ == calld_->send_messages_.size() &&
      !started_send_trailing_metadata_ &&
      !calld_->pending_send_trailing_metadata_) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << calld_->chand_
                                << " calld=" << calld_ << " attempt=" << this
                                << ": replaying previously completed "
                                   "send_trailing_metadata op";
    if (replay_batch_data == nullptr) {
      replay_batch_data = CreateBatch(1, true );
    }
    replay_batch_data->AddRetriableSendTrailingMetadataOp();
  }
  return replay_batch_data;
}

namespace {

void StartBatchInCallCombiner(void* arg, grpc_error_handle ) {
  grpc_transport_stream_op_batch* batch =
      static_cast<grpc_transport_stream_op_batch*>(arg);
  auto* lb_call =
      static_cast<ClientChannelFilter::FilterBasedLoadBalancedCall*>(
          batch->handler_private.extra_arg);
  // Note: This will release the call combiner.
  lb_call->StartTransportStreamOpBatch(batch);
}

}

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

void RetryFilter::LegacyCallData::CallAttempt::
    AddBatchForInternalRecvTrailingMetadata(CallCombinerClosureList* closures) {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this
      << ": call failed but recv_trailing_metadata not started; "
         "starting it internally";

  BatchData* batch_data = CreateBatch(2, false );
  batch_data->AddRetriableRecvTrailingMetadataOp();
  recv_trailing_metadata_internal_batch_.reset(batch_data);
  AddClosureForBatch(batch_data->batch(),
                     "starting internal recv_trailing_metadata", closures);
}

void RetryFilter::LegacyCallData::CallAttempt::MaybeAddBatchForCancelOp(
    grpc_error_handle error, CallCombinerClosureList* closures) {
  if (sent_cancel_stream_) {
    return;
  }
  sent_cancel_stream_ = true;
  BatchData* cancel_batch_data = CreateBatch(1, true);
  cancel_batch_data->AddCancelStreamOp(error);
  AddClosureForBatch(cancel_batch_data->batch(),
                     "start cancellation batch on call attempt", closures);
}

void RetryFilter::LegacyCallData::CallAttempt::AddBatchesForPendingBatches(
    CallCombinerClosureList* closures) {
  for (size_t i = 0; i < GPR_ARRAY_SIZE(calld_->pending_batches_); ++i) {
    PendingBatch* pending = &calld_->pending_batches_[i];
    grpc_transport_stream_op_batch* batch = pending->batch;
    if (batch == nullptr) continue;
    bool has_send_ops = false;

    if (batch->send_initial_metadata) {
      if (started_send_initial_metadata_) continue;
      has_send_ops = true;
    }
    if (batch->send_message) {

      if (completed_send_message_count_ < started_send_message_count_ ||
          completed_send_message_count_ ==
              (calld_->send_messages_.size() + !pending->send_ops_cached)) {
        continue;
      }
      has_send_ops = true;
    }

    if (batch->send_trailing_metadata) {
      if (started_send_message_count_ + batch->send_message <
              calld_->send_messages_.size() ||
          started_send_trailing_metadata_) {
        continue;
      }
      has_send_ops = true;
    }
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

    if (calld_->retry_committed_ && !pending->send_ops_cached &&
        (!batch->recv_trailing_metadata || !started_recv_trailing_metadata_)) {
      AddClosureForBatch(
          batch,
          "start non-replayable pending batch on call attempt after commit",
          closures);
      calld_->PendingBatchClear(pending);
      continue;
    }

    BatchData* batch_data =
        CreateBatch(num_callbacks, has_send_ops );

    calld_->MaybeCacheSendOpsForBatch(pending);

    if (batch->send_initial_metadata) {
      batch_data->AddRetriableSendInitialMetadataOp();
    }

    if (batch->send_message) {
      batch_data->AddRetriableSendMessageOp();
    }

    if (batch->send_trailing_metadata) {
      batch_data->AddRetriableSendTrailingMetadataOp();
    }

    if (batch->recv_initial_metadata) {
      batch_data->AddRetriableRecvInitialMetadataOp();
    }

    if (batch->recv_message) {
      batch_data->AddRetriableRecvMessageOp();
    }

    if (batch->recv_trailing_metadata && !started_recv_trailing_metadata_) {
      batch_data->AddRetriableRecvTrailingMetadataOp();
    }
    AddClosureForBatch(batch_data->batch(),
                       "start replayable pending batch on call attempt",
                       closures);
  }
}

void RetryFilter::LegacyCallData::CallAttempt::AddRetriableBatches(
    CallCombinerClosureList* closures) {

  BatchData* replay_batch_data = MaybeCreateBatchForReplay();
  if (replay_batch_data != nullptr) {
    AddClosureForBatch(replay_batch_data->batch(),
                       "start replay batch on call attempt", closures);
  }

  AddBatchesForPendingBatches(closures);
}

void RetryFilter::LegacyCallData::CallAttempt::StartRetriableBatches() {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this << ": constructing retriable batches";

  CallCombinerClosureList closures;
  AddRetriableBatches(&closures);
  // Note: This will yield the call combiner.

  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld_->chand_ << " calld=" << calld_
      << " attempt=" << this << ": starting " << closures.size()
      << " retriable batches on lb_call=" << lb_call_.get();
  closures.RunClosures(calld_->call_combiner_);
}

void RetryFilter::LegacyCallData::CallAttempt::CancelFromSurface(
    grpc_transport_stream_op_batch* cancel_batch) {
  MaybeCancelPerAttemptRecvTimer();
  Abandon();

  lb_call_->StartTransportStreamOpBatch(cancel_batch);
}

bool RetryFilter::LegacyCallData::CallAttempt::ShouldRetry(
    std::optional<grpc_status_code> status,
    std::optional<Duration> server_pushback) {

  if (calld_->retry_policy_ == nullptr) return false;

  if (status.has_value()) {
    if (GPR_LIKELY(*status == GRPC_STATUS_OK)) {
      if (calld_->retry_throttle_data_ != nullptr) {
        calld_->retry_throttle_data_->RecordSuccess();
      }
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld_->chand_ << " calld=" << calld_
          << " attempt=" << this << ": call succeeded";
      return false;
    }

    if (!calld_->retry_policy_->retryable_status_codes().Contains(*status)) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld_->chand_ << " calld=" << calld_
          << " attempt=" << this << ": status "
          << grpc_status_code_to_string(*status)
          << " not configured as retryable";
      return false;
    }
  }

  if (calld_->retry_throttle_data_ != nullptr &&
      !calld_->retry_throttle_data_->RecordFailure()) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld_->chand_ << " calld=" << calld_
        << " attempt=" << this << ": retries throttled";
    return false;
  }

  if (calld_->retry_committed_) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld_->chand_ << " calld=" << calld_
        << " attempt=" << this << ": retries already committed";
    return false;
  }

  ++calld_->num_attempts_completed_;
  if (calld_->num_attempts_completed_ >=
      calld_->retry_policy_->max_attempts()) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld_->chand_ << " calld=" << calld_
        << " attempt=" << this << ": exceeded "
        << calld_->retry_policy_->max_attempts() << " retry attempts";
    return false;
  }

  if (server_pushback.has_value()) {
    if (*server_pushback < Duration::Zero()) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld_->chand_ << " calld=" << calld_
          << " attempt=" << this << ": not retrying due to server push-back";
      return false;
    } else {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld_->chand_ << " calld=" << calld_
          << " attempt=" << this << ": server push-back: retry in "
          << server_pushback->millis() << " ms";
    }
  }

  return true;
}

void RetryFilter::LegacyCallData::CallAttempt::Abandon() {
  abandoned_ = true;

  if (started_recv_trailing_metadata_ &&
      !seen_recv_trailing_metadata_from_surface_) {
    recv_trailing_metadata_internal_batch_.reset(
        DEBUG_LOCATION,
        "unref internal recv_trailing_metadata_ready batch; attempt abandoned");
  }
  recv_trailing_metadata_error_ = absl::OkStatus();
  recv_initial_metadata_ready_deferred_batch_.reset(
      DEBUG_LOCATION,
      "unref deferred recv_initial_metadata_ready batch; attempt abandoned");
  recv_initial_metadata_error_ = absl::OkStatus();
  recv_message_ready_deferred_batch_.reset(
      DEBUG_LOCATION,
      "unref deferred recv_message_ready batch; attempt abandoned");
  recv_message_error_ = absl::OkStatus();
  for (auto& on_complete_deferred_batch : on_complete_deferred_batches_) {
    on_complete_deferred_batch.batch.reset(
        DEBUG_LOCATION, "unref deferred on_complete batch; attempt abandoned");
  }
  on_complete_deferred_batches_.clear();
}

void RetryFilter::LegacyCallData::CallAttempt::OnPerAttemptRecvTimer() {
  GRPC_CLOSURE_INIT(&on_per_attempt_recv_timer_, OnPerAttemptRecvTimerLocked,
                    this, nullptr);
  GRPC_CALL_COMBINER_START(calld_->call_combiner_, &on_per_attempt_recv_timer_,
                           absl::OkStatus(), "per-attempt timer fired");
}

void RetryFilter::LegacyCallData::CallAttempt::OnPerAttemptRecvTimerLocked(
    void* arg, grpc_error_handle error) {
  auto* call_attempt = static_cast<CallAttempt*>(arg);
  auto* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt
      << ": perAttemptRecvTimeout timer fired: error=" << StatusToString(error)
      << ", per_attempt_recv_timer_handle_ is valid ="
      << (call_attempt->per_attempt_recv_timer_handle_ != TaskHandle::kInvalid);
  CallCombinerClosureList closures;
  if (call_attempt->per_attempt_recv_timer_handle_ != TaskHandle::kInvalid) {
    call_attempt->per_attempt_recv_timer_handle_ = TaskHandle::kInvalid;

    call_attempt->MaybeAddBatchForCancelOp(
        grpc_error_set_int(
            GRPC_ERROR_CREATE("retry perAttemptRecvTimeout exceeded"),
            StatusIntProperty::kRpcStatus, GRPC_STATUS_CANCELLED),
        &closures);

    if (call_attempt->ShouldRetry(std::nullopt,
                                  std::nullopt)) {

      call_attempt->Abandon();

      calld->StartRetryTimer(std::nullopt);
    } else {

      calld->RetryCommit(call_attempt);

      call_attempt->MaybeSwitchToFastPath();
    }
  }
  closures.RunClosures(calld->call_combiner_);
  call_attempt->Unref(DEBUG_LOCATION, "OnPerAttemptRecvTimer");
  GRPC_CALL_STACK_UNREF(calld->owning_call_, "OnPerAttemptRecvTimer");
}

void RetryFilter::LegacyCallData::CallAttempt::
    MaybeCancelPerAttemptRecvTimer() {
  if (per_attempt_recv_timer_handle_ != TaskHandle::kInvalid) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld_->chand_ << " calld=" << calld_
        << " attempt=" << this << ": cancelling perAttemptRecvTimeout timer";
    if (calld_->chand_->event_engine()->Cancel(
            per_attempt_recv_timer_handle_)) {
      Unref(DEBUG_LOCATION, "OnPerAttemptRecvTimer");
      GRPC_CALL_STACK_UNREF(calld_->owning_call_, "OnPerAttemptRecvTimer");
    }
    per_attempt_recv_timer_handle_ = TaskHandle::kInvalid;
  }
}

RetryFilter::LegacyCallData::CallAttempt::BatchData::BatchData(
    RefCountedPtr<CallAttempt> attempt, int refcount, bool set_on_complete)
    : RefCounted(GRPC_TRACE_FLAG_ENABLED(retry) ? "BatchData" : nullptr,
                 refcount),
      call_attempt_(attempt.release()) {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << call_attempt_->calld_->chand_
      << " calld=" << call_attempt_->calld_ << " attempt=" << call_attempt_
      << ": creating batch " << this;

  GRPC_CALL_STACK_REF(call_attempt_->calld_->owning_call_, "Retry BatchData");
  batch_.payload = &call_attempt_->batch_payload_;
  if (set_on_complete) {
    GRPC_CLOSURE_INIT(&on_complete_, OnComplete, this, nullptr);
    batch_.on_complete = &on_complete_;
  }
}

RetryFilter::LegacyCallData::CallAttempt::BatchData::~BatchData() {
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << call_attempt_->calld_->chand_
      << " calld=" << call_attempt_->calld_ << " attempt=" << call_attempt_
      << ": destroying batch " << this;
  CallAttempt* call_attempt = std::exchange(call_attempt_, nullptr);
  grpc_call_stack* owning_call = call_attempt->calld_->owning_call_;
  call_attempt->Unref(DEBUG_LOCATION, "~BatchData");
  GRPC_CALL_STACK_UNREF(owning_call, "Retry BatchData");
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    FreeCachedSendOpDataForCompletedBatch() {
  auto* calld = call_attempt_->calld_;

  if (batch_.send_initial_metadata) {
    calld->FreeCachedSendInitialMetadata();
  }
  if (batch_.send_message) {
    calld->FreeCachedSendMessage(call_attempt_->completed_send_message_count_ -
                                 1);
  }
  if (batch_.send_trailing_metadata) {
    calld->FreeCachedSendTrailingMetadata();
  }
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    MaybeAddClosureForRecvInitialMetadataCallback(
        grpc_error_handle error, CallCombinerClosureList* closures) {

  PendingBatch* pending = call_attempt_->calld_->PendingBatchFind(
      "invoking recv_initial_metadata_ready for",
      [](grpc_transport_stream_op_batch* batch) {
        return batch->recv_initial_metadata &&
               batch->payload->recv_initial_metadata
                       .recv_initial_metadata_ready != nullptr;
      });
  if (pending == nullptr) {
    return;
  }

  *pending->batch->payload->recv_initial_metadata.recv_initial_metadata =
      std::move(call_attempt_->recv_initial_metadata_);

  *pending->batch->payload->recv_initial_metadata.trailing_metadata_available =
      call_attempt_->trailing_metadata_available_;

  // Note: Need to do this before invoking the callback, since invoking

  grpc_closure* recv_initial_metadata_ready =
      pending->batch->payload->recv_initial_metadata
          .recv_initial_metadata_ready;
  pending->batch->payload->recv_initial_metadata.recv_initial_metadata_ready =
      nullptr;
  call_attempt_->calld_->MaybeClearPendingBatch(pending);

  closures->Add(recv_initial_metadata_ready, error,
                "recv_initial_metadata_ready for pending batch");
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    RecvInitialMetadataReady(void* arg, grpc_error_handle error) {
  RefCountedPtr<BatchData> batch_data(static_cast<BatchData*>(arg));
  CallAttempt* call_attempt = batch_data->call_attempt_;
  RetryFilter::LegacyCallData* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt << " batch_data=" << batch_data.get()
      << ": got recv_initial_metadata_ready, error=" << StatusToString(error);
  call_attempt->completed_recv_initial_metadata_ = true;

  if (call_attempt->abandoned_) {
    GRPC_CALL_COMBINER_STOP(
        calld->call_combiner_,
        "recv_initial_metadata_ready for abandoned attempt");
    return;
  }

  call_attempt->MaybeCancelPerAttemptRecvTimer();

  if (!calld->retry_committed_) {

    if (GPR_UNLIKELY(
            (call_attempt->trailing_metadata_available_ || !error.ok()) &&
            !call_attempt->completed_recv_trailing_metadata_)) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld->chand_ << " calld=" << calld
          << " attempt=" << call_attempt
          << ": deferring recv_initial_metadata_ready (Trailers-Only)";
      call_attempt->recv_initial_metadata_ready_deferred_batch_ =
          std::move(batch_data);
      call_attempt->recv_initial_metadata_error_ = error;
      CallCombinerClosureList closures;
      if (!error.ok()) {
        call_attempt->MaybeAddBatchForCancelOp(error, &closures);
      }
      if (!call_attempt->started_recv_trailing_metadata_) {

        call_attempt->AddBatchForInternalRecvTrailingMetadata(&closures);
      }
      closures.RunClosures(calld->call_combiner_);
      return;
    }

    calld->RetryCommit(call_attempt);

    call_attempt->MaybeSwitchToFastPath();
  }

  CallCombinerClosureList closures;
  batch_data->MaybeAddClosureForRecvInitialMetadataCallback(error, &closures);
  closures.RunClosures(calld->call_combiner_);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    MaybeAddClosureForRecvMessageCallback(grpc_error_handle error,
                                          CallCombinerClosureList* closures) {

  PendingBatch* pending = call_attempt_->calld_->PendingBatchFind(
      "invoking recv_message_ready for",
      [](grpc_transport_stream_op_batch* batch) {
        return batch->recv_message &&
               batch->payload->recv_message.recv_message_ready != nullptr;
      });
  if (pending == nullptr) {
    return;
  }

  *pending->batch->payload->recv_message.recv_message =
      std::move(call_attempt_->recv_message_);
  *pending->batch->payload->recv_message.flags =
      call_attempt_->recv_message_flags_;

  // Note: Need to do this before invoking the callback, since invoking

  grpc_closure* recv_message_ready =
      pending->batch->payload->recv_message.recv_message_ready;
  pending->batch->payload->recv_message.recv_message_ready = nullptr;
  call_attempt_->calld_->MaybeClearPendingBatch(pending);

  closures->Add(recv_message_ready, error,
                "recv_message_ready for pending batch");
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::RecvMessageReady(
    void* arg, grpc_error_handle error) {
  RefCountedPtr<BatchData> batch_data(static_cast<BatchData*>(arg));
  CallAttempt* call_attempt = batch_data->call_attempt_;
  RetryFilter::LegacyCallData* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt << " batch_data=" << batch_data.get()
      << ": got recv_message_ready, error=" << StatusToString(error);
  ++call_attempt->completed_recv_message_count_;

  if (call_attempt->abandoned_) {

    call_attempt->recv_message_.reset();
    GRPC_CALL_COMBINER_STOP(calld->call_combiner_,
                            "recv_message_ready for abandoned attempt");
    return;
  }

  call_attempt->MaybeCancelPerAttemptRecvTimer();

  if (!calld->retry_committed_) {

    if (GPR_UNLIKELY(
            (!call_attempt->recv_message_.has_value() || !error.ok()) &&
            !call_attempt->completed_recv_trailing_metadata_)) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << calld->chand_ << " calld=" << calld
          << " attempt=" << call_attempt
          << ": deferring recv_message_ready (nullptr message and "
             "recv_trailing_metadata pending)";
      call_attempt->recv_message_ready_deferred_batch_ = std::move(batch_data);
      call_attempt->recv_message_error_ = error;
      CallCombinerClosureList closures;
      if (!error.ok()) {
        call_attempt->MaybeAddBatchForCancelOp(error, &closures);
      }
      if (!call_attempt->started_recv_trailing_metadata_) {

        call_attempt->AddBatchForInternalRecvTrailingMetadata(&closures);
      }
      closures.RunClosures(calld->call_combiner_);
      return;
    }

    calld->RetryCommit(call_attempt);

    call_attempt->MaybeSwitchToFastPath();
  }

  CallCombinerClosureList closures;
  batch_data->MaybeAddClosureForRecvMessageCallback(error, &closures);
  closures.RunClosures(calld->call_combiner_);
}

namespace {

void GetCallStatus(
    Timestamp deadline, grpc_metadata_batch* md_batch, grpc_error_handle error,
    grpc_status_code* status, std::optional<Duration>* server_pushback,
    bool* is_lb_drop,
    std::optional<GrpcStreamNetworkState::ValueType>* stream_network_state) {
  if (!error.ok()) {
    grpc_error_get_status(error, deadline, status, nullptr, nullptr, nullptr);
    intptr_t value = 0;
    if (grpc_error_get_int(error, StatusIntProperty::kLbPolicyDrop, &value) &&
        value != 0) {
      *is_lb_drop = true;
    }
  } else {
    *status = *md_batch->get(GrpcStatusMetadata());
  }
  *server_pushback = md_batch->get(GrpcRetryPushbackMsMetadata());
  *stream_network_state = md_batch->get(GrpcStreamNetworkState());
}

}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    MaybeAddClosureForRecvTrailingMetadataReady(
        grpc_error_handle error, CallCombinerClosureList* closures) {
  auto* calld = call_attempt_->calld_;

  PendingBatch* pending = calld->PendingBatchFind(
      "invoking recv_trailing_metadata_ready for",
      [](grpc_transport_stream_op_batch* batch) {
        return batch->recv_trailing_metadata &&
               batch->payload->recv_trailing_metadata
                       .recv_trailing_metadata_ready != nullptr;
      });

  if (pending == nullptr) {
    call_attempt_->recv_trailing_metadata_error_ = error;
    return;
  }

  grpc_transport_move_stats(
      &call_attempt_->collect_stats_,
      pending->batch->payload->recv_trailing_metadata.collect_stats);

  *pending->batch->payload->recv_trailing_metadata.recv_trailing_metadata =
      std::move(call_attempt_->recv_trailing_metadata_);

  closures->Add(pending->batch->payload->recv_trailing_metadata
                    .recv_trailing_metadata_ready,
                error, "recv_trailing_metadata_ready for pending batch");

  pending->batch->payload->recv_trailing_metadata.recv_trailing_metadata_ready =
      nullptr;
  calld->MaybeClearPendingBatch(pending);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddClosuresForDeferredCompletionCallbacks(
        CallCombinerClosureList* closures) {

  if (GPR_UNLIKELY(call_attempt_->recv_initial_metadata_ready_deferred_batch_ !=
                   nullptr)) {
    MaybeAddClosureForRecvInitialMetadataCallback(
        call_attempt_->recv_initial_metadata_error_, closures);
    call_attempt_->recv_initial_metadata_ready_deferred_batch_.reset(
        DEBUG_LOCATION, "resuming deferred recv_initial_metadata_ready");
    call_attempt_->recv_initial_metadata_error_ = absl::OkStatus();
  }

  if (GPR_UNLIKELY(call_attempt_->recv_message_ready_deferred_batch_ !=
                   nullptr)) {
    MaybeAddClosureForRecvMessageCallback(call_attempt_->recv_message_error_,
                                          closures);
    call_attempt_->recv_message_ready_deferred_batch_.reset(
        DEBUG_LOCATION, "resuming deferred recv_message_ready");
    call_attempt_->recv_message_error_ = absl::OkStatus();
  }

  for (auto& on_complete_deferred_batch :
       call_attempt_->on_complete_deferred_batches_) {
    closures->Add(&on_complete_deferred_batch.batch->on_complete_,
                  on_complete_deferred_batch.error, "resuming on_complete");
    on_complete_deferred_batch.batch.release();
  }
  call_attempt_->on_complete_deferred_batches_.clear();
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddClosuresToFailUnstartedPendingBatches(
        grpc_error_handle error, CallCombinerClosureList* closures) {
  auto* calld = call_attempt_->calld_;
  for (size_t i = 0; i < GPR_ARRAY_SIZE(calld->pending_batches_); ++i) {
    PendingBatch* pending = &calld->pending_batches_[i];
    if (pending->batch == nullptr) continue;
    if (call_attempt_->PendingBatchContainsUnstartedSendOps(pending)) {
      closures->Add(pending->batch->on_complete, error,
                    "failing on_complete for pending batch");
      pending->batch->on_complete = nullptr;
      calld->MaybeClearPendingBatch(pending);
    }
  }
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    RunClosuresForCompletedCall(grpc_error_handle error) {

  CallCombinerClosureList closures;

  MaybeAddClosureForRecvTrailingMetadataReady(error, &closures);

  AddClosuresForDeferredCompletionCallbacks(&closures);

  AddClosuresToFailUnstartedPendingBatches(error, &closures);

  // Note: This will release the call combiner.
  closures.RunClosures(call_attempt_->calld_->call_combiner_);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    RecvTrailingMetadataReady(void* arg, grpc_error_handle error) {
  RefCountedPtr<BatchData> batch_data(static_cast<BatchData*>(arg));
  CallAttempt* call_attempt = batch_data->call_attempt_;
  RetryFilter::LegacyCallData* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt << " batch_data=" << batch_data.get()
      << ": got recv_trailing_metadata_ready, error=" << StatusToString(error);
  call_attempt->completed_recv_trailing_metadata_ = true;

  if (call_attempt->abandoned_) {
    GRPC_CALL_COMBINER_STOP(
        calld->call_combiner_,
        "recv_trailing_metadata_ready for abandoned attempt");
    return;
  }

  call_attempt->MaybeCancelPerAttemptRecvTimer();

  grpc_status_code status = GRPC_STATUS_OK;
  std::optional<Duration> server_pushback;
  bool is_lb_drop = false;
  std::optional<GrpcStreamNetworkState::ValueType> stream_network_state;
  grpc_metadata_batch* md_batch =
      batch_data->batch_.payload->recv_trailing_metadata.recv_trailing_metadata;
  GetCallStatus(calld->deadline_, md_batch, error, &status, &server_pushback,
                &is_lb_drop, &stream_network_state);
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt
      << ": call finished, status=" << grpc_status_code_to_string(status)
      << " server_pushback="
      << (server_pushback.has_value() ? server_pushback->ToString() : "N/A")
      << " is_lb_drop=" << is_lb_drop << " stream_network_state="
      << (stream_network_state.has_value() ? absl::StrCat(*stream_network_state)
                                           : "N/A");

  if (!is_lb_drop) {
    enum { kNoRetry, kTransparentRetry, kConfigurableRetry } retry = kNoRetry;

    if (stream_network_state.has_value() && !calld->retry_committed_) {

      if (*stream_network_state == GrpcStreamNetworkState::kNotSentOnWire) {
        retry = kTransparentRetry;
      } else if (*stream_network_state ==
                     GrpcStreamNetworkState::kNotSeenByServer &&
                 !calld->sent_transparent_retry_not_seen_by_server_) {
        calld->sent_transparent_retry_not_seen_by_server_ = true;
        retry = kTransparentRetry;
      }
    }

    if (retry == kNoRetry &&
        call_attempt->ShouldRetry(status, server_pushback)) {
      retry = kConfigurableRetry;
    }

    if (retry != kNoRetry) {
      CallCombinerClosureList closures;

      call_attempt->MaybeAddBatchForCancelOp(
          error.ok() ? grpc_error_set_int(
                           GRPC_ERROR_CREATE("call attempt failed"),
                           StatusIntProperty::kRpcStatus, GRPC_STATUS_CANCELLED)
                     : error,
          &closures);

      if (retry == kTransparentRetry) {
        calld->AddClosureToStartTransparentRetry(&closures);
      } else {
        calld->StartRetryTimer(server_pushback);
      }

      call_attempt->Abandon();

      closures.RunClosures(calld->call_combiner_);
      return;
    }
  }

  calld->RetryCommit(call_attempt);

  call_attempt->MaybeSwitchToFastPath();

  batch_data->RunClosuresForCompletedCall(error);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddClosuresForCompletedPendingBatch(grpc_error_handle error,
                                        CallCombinerClosureList* closures) {
  auto* calld = call_attempt_->calld_;
  PendingBatch* pending = calld->PendingBatchFind(
      "completed", [this](grpc_transport_stream_op_batch* batch) {

        return batch->on_complete != nullptr &&
               batch_.send_initial_metadata == batch->send_initial_metadata &&
               batch_.send_message == batch->send_message &&
               batch_.send_trailing_metadata == batch->send_trailing_metadata;
      });

  if (pending == nullptr) {
    return;
  }

  if (batch_.send_message) {
    pending->batch->payload->send_message.stream_write_closed =
        batch_.payload->send_message.stream_write_closed;
  }

  closures->Add(pending->batch->on_complete, error,
                "on_complete for pending batch");
  pending->batch->on_complete = nullptr;
  calld->MaybeClearPendingBatch(pending);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddClosuresForReplayOrPendingSendOps(CallCombinerClosureList* closures) {
  auto* calld = call_attempt_->calld_;
  bool have_pending_send_ops = call_attempt_->HaveSendOpsToReplay();

  if (!have_pending_send_ops) {
    for (size_t i = 0; i < GPR_ARRAY_SIZE(calld->pending_batches_); ++i) {
      PendingBatch* pending = &calld->pending_batches_[i];
      grpc_transport_stream_op_batch* batch = pending->batch;
      if (batch == nullptr || pending->send_ops_cached) continue;
      if (batch->send_message || batch->send_trailing_metadata) {
        have_pending_send_ops = true;
        break;
      }
    }
  }
  if (have_pending_send_ops) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld->chand_ << " calld=" << calld
        << " attempt=" << call_attempt_
        << ": starting next batch for pending send op(s)";
    call_attempt_->AddRetriableBatches(closures);
  }
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::OnComplete(
    void* arg, grpc_error_handle error) {
  RefCountedPtr<BatchData> batch_data(static_cast<BatchData*>(arg));
  CallAttempt* call_attempt = batch_data->call_attempt_;
  RetryFilter::LegacyCallData* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt << " batch_data=" << batch_data.get()
      << ": got on_complete, error=" << StatusToString(error) << ", batch="
      << grpc_transport_stream_op_batch_string(&batch_data->batch_, false);

  if (call_attempt->abandoned_) {
    GRPC_CALL_COMBINER_STOP(calld->call_combiner_,
                            "on_complete for abandoned attempt");
    return;
  }

  if (GPR_UNLIKELY(!calld->retry_committed_ && !error.ok() &&
                   !call_attempt->completed_recv_trailing_metadata_)) {
    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << calld->chand_ << " calld=" << calld
        << " attempt=" << call_attempt << ": deferring on_complete";
    call_attempt->on_complete_deferred_batches_.emplace_back(
        std::move(batch_data), error);
    CallCombinerClosureList closures;
    call_attempt->MaybeAddBatchForCancelOp(error, &closures);
    if (!call_attempt->started_recv_trailing_metadata_) {

      call_attempt->AddBatchForInternalRecvTrailingMetadata(&closures);
    }
    closures.RunClosures(calld->call_combiner_);
    return;
  }

  if (batch_data->batch_.send_initial_metadata) {
    call_attempt->completed_send_initial_metadata_ = true;
  }
  if (batch_data->batch_.send_message) {
    ++call_attempt->completed_send_message_count_;
    call_attempt->send_message_.Clear();
  }
  if (batch_data->batch_.send_trailing_metadata) {
    call_attempt->completed_send_trailing_metadata_ = true;
  }

  if (calld->retry_committed_) {
    batch_data->FreeCachedSendOpDataForCompletedBatch();
  }

  CallCombinerClosureList closures;

  batch_data->AddClosuresForCompletedPendingBatch(error, &closures);

  if (!call_attempt->completed_recv_trailing_metadata_) {
    batch_data->AddClosuresForReplayOrPendingSendOps(&closures);
  }

  call_attempt->MaybeSwitchToFastPath();

  // Note: This yields the call combiner.
  closures.RunClosures(calld->call_combiner_);
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::OnCompleteForCancelOp(
    void* arg, grpc_error_handle error) {
  RefCountedPtr<BatchData> batch_data(static_cast<BatchData*>(arg));
  CallAttempt* call_attempt = batch_data->call_attempt_;
  RetryFilter::LegacyCallData* calld = call_attempt->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt << " batch_data=" << batch_data.get()
      << ": got on_complete for cancel_stream batch, error="
      << StatusToString(error) << ", batch="
      << grpc_transport_stream_op_batch_string(&batch_data->batch_, false);
  GRPC_CALL_COMBINER_STOP(
      calld->call_combiner_,
      "on_complete for internally generated cancel_stream op");
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableSendInitialMetadataOp() {
  auto* calld = call_attempt_->calld_;

  call_attempt_->send_initial_metadata_ = calld->send_initial_metadata_.Copy();
  if (GPR_UNLIKELY(calld->num_attempts_completed_ > 0)) {
    call_attempt_->send_initial_metadata_.Set(GrpcPreviousRpcAttemptsMetadata(),
                                              calld->num_attempts_completed_);
  } else {
    call_attempt_->send_initial_metadata_.Remove(
        GrpcPreviousRpcAttemptsMetadata());
  }
  call_attempt_->started_send_initial_metadata_ = true;
  batch_.send_initial_metadata = true;
  batch_.payload->send_initial_metadata.send_initial_metadata =
      &call_attempt_->send_initial_metadata_;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableSendMessageOp() {
  auto* calld = call_attempt_->calld_;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << calld->chand_ << " calld=" << calld
      << " attempt=" << call_attempt_ << ": starting calld->send_messages["
      << call_attempt_->started_send_message_count_ << "]";
  CachedSendMessage cache =
      calld->send_messages_[call_attempt_->started_send_message_count_];
  ++call_attempt_->started_send_message_count_;
  batch_.send_message = true;
  call_attempt_->send_message_ = cache.slices->Copy();
  batch_.payload->send_message.send_message = &call_attempt_->send_message_;
  batch_.payload->send_message.flags = cache.flags;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableSendTrailingMetadataOp() {
  auto* calld = call_attempt_->calld_;

  call_attempt_->send_trailing_metadata_ =
      calld->send_trailing_metadata_.Copy();
  call_attempt_->started_send_trailing_metadata_ = true;
  batch_.send_trailing_metadata = true;
  batch_.payload->send_trailing_metadata.send_trailing_metadata =
      &call_attempt_->send_trailing_metadata_;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableRecvInitialMetadataOp() {
  call_attempt_->started_recv_initial_metadata_ = true;
  batch_.recv_initial_metadata = true;
  call_attempt_->recv_initial_metadata_.Clear();
  batch_.payload->recv_initial_metadata.recv_initial_metadata =
      &call_attempt_->recv_initial_metadata_;
  batch_.payload->recv_initial_metadata.trailing_metadata_available =
      &call_attempt_->trailing_metadata_available_;
  GRPC_CLOSURE_INIT(&call_attempt_->recv_initial_metadata_ready_,
                    RecvInitialMetadataReady, this, grpc_schedule_on_exec_ctx);
  batch_.payload->recv_initial_metadata.recv_initial_metadata_ready =
      &call_attempt_->recv_initial_metadata_ready_;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableRecvMessageOp() {
  ++call_attempt_->started_recv_message_count_;
  batch_.recv_message = true;
  batch_.payload->recv_message.recv_message = &call_attempt_->recv_message_;
  batch_.payload->recv_message.flags = &call_attempt_->recv_message_flags_;
  batch_.payload->recv_message.call_failed_before_recv_message = nullptr;
  GRPC_CLOSURE_INIT(&call_attempt_->recv_message_ready_, RecvMessageReady, this,
                    grpc_schedule_on_exec_ctx);
  batch_.payload->recv_message.recv_message_ready =
      &call_attempt_->recv_message_ready_;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::
    AddRetriableRecvTrailingMetadataOp() {
  call_attempt_->started_recv_trailing_metadata_ = true;
  batch_.recv_trailing_metadata = true;
  call_attempt_->recv_trailing_metadata_.Clear();
  batch_.payload->recv_trailing_metadata.recv_trailing_metadata =
      &call_attempt_->recv_trailing_metadata_;
  batch_.payload->recv_trailing_metadata.collect_stats =
      &call_attempt_->collect_stats_;
  GRPC_CLOSURE_INIT(&call_attempt_->recv_trailing_metadata_ready_,
                    RecvTrailingMetadataReady, this, grpc_schedule_on_exec_ctx);
  batch_.payload->recv_trailing_metadata.recv_trailing_metadata_ready =
      &call_attempt_->recv_trailing_metadata_ready_;
}

void RetryFilter::LegacyCallData::CallAttempt::BatchData::AddCancelStreamOp(
    grpc_error_handle error) {
  batch_.cancel_stream = true;
  batch_.payload->cancel_stream.cancel_error = error;

  GRPC_CLOSURE_INIT(&on_complete_, OnCompleteForCancelOp, this, nullptr);
}

grpc_error_handle RetryFilter::LegacyCallData::Init(
    grpc_call_element* elem, const grpc_call_element_args* args) {
  auto* chand = static_cast<RetryFilter*>(elem->channel_data);
  new (elem->call_data) RetryFilter::LegacyCallData(chand, *args);
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << chand << " calld=" << elem->call_data << ": created call";
  return absl::OkStatus();
}

void RetryFilter::LegacyCallData::Destroy(
    grpc_call_element* elem, const grpc_call_final_info* ,
    grpc_closure* then_schedule_closure) {
  auto* calld = static_cast<RetryFilter::LegacyCallData*>(elem->call_data);

  RefCountedPtr<CallStackDestructionBarrier> call_stack_destruction_barrier =
      std::move(calld->call_stack_destruction_barrier_);
  calld->~LegacyCallData();

  call_stack_destruction_barrier->set_on_call_stack_destruction(
      then_schedule_closure);
}

void RetryFilter::LegacyCallData::StartTransportStreamOpBatch(
    grpc_call_element* elem, grpc_transport_stream_op_batch* batch) {
  auto* calld = static_cast<RetryFilter::LegacyCallData*>(elem->call_data);
  calld->StartTransportStreamOpBatch(batch);
}

void RetryFilter::LegacyCallData::SetPollent(grpc_call_element* elem,
                                             grpc_polling_entity* pollent) {
  auto* calld = static_cast<RetryFilter::LegacyCallData*>(elem->call_data);
  calld->pollent_ = pollent;
}

RetryFilter::LegacyCallData::LegacyCallData(RetryFilter* chand,
                                            const grpc_call_element_args& args)
    : chand_(chand),
      retry_throttle_data_(chand->retry_throttle_data()),
      retry_policy_(chand->GetRetryPolicy(args.arena)),
      retry_backoff_(
          BackOff::Options()
              .set_initial_backoff(retry_policy_ == nullptr
                                       ? Duration::Zero()
                                       : retry_policy_->initial_backoff())
              .set_multiplier(retry_policy_ == nullptr
                                  ? 0
                                  : retry_policy_->backoff_multiplier())
              .set_jitter(RetryFilter::BackoffJitter())
              .set_max_backoff(retry_policy_ == nullptr
                                   ? Duration::Zero()
                                   : retry_policy_->max_backoff())),
      deadline_(args.deadline),
      arena_(args.arena),
      owning_call_(args.call_stack),
      call_combiner_(args.call_combiner),
      call_stack_destruction_barrier_(
          arena_->New<CallStackDestructionBarrier>()),
      pending_send_initial_metadata_(false),
      pending_send_message_(false),
      pending_send_trailing_metadata_(false),
      retry_committed_(false),
      retry_codepath_started_(false),
      sent_transparent_retry_not_seen_by_server_(false) {}

RetryFilter::LegacyCallData::~LegacyCallData() {
  FreeAllCachedSendOpData();

  for (size_t i = 0; i < GPR_ARRAY_SIZE(pending_batches_); ++i) {
    CHECK_EQ(pending_batches_[i].batch, nullptr);
  }
}

void RetryFilter::LegacyCallData::StartTransportStreamOpBatch(
    grpc_transport_stream_op_batch* batch) {
  if (GRPC_TRACE_FLAG_ENABLED(retry) && !GRPC_TRACE_FLAG_ENABLED(channel)) {
    LOG(INFO) << "chand=" << chand_ << " calld=" << this
              << ": batch started from surface: "
              << grpc_transport_stream_op_batch_string(batch, false);
  }

  if (committed_call_ != nullptr) {
    // Note: This will release the call combiner.
    committed_call_->StartTransportStreamOpBatch(batch);
    return;
  }

  if (!cancelled_from_surface_.ok()) {
    // Note: This will release the call combiner.
    grpc_transport_stream_op_batch_finish_with_failure(
        batch, cancelled_from_surface_, call_combiner_);
    return;
  }

  if (GPR_UNLIKELY(batch->cancel_stream)) {

    cancelled_from_surface_ = batch->payload->cancel_stream.cancel_error;
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                                << ": cancelled from surface: "
                                << StatusToString(cancelled_from_surface_);

    PendingBatchesFail(cancelled_from_surface_);

    if (call_attempt_ != nullptr) {
      RetryCommit(call_attempt_.get());

      // Note: This will release the call combiner.
      call_attempt_->CancelFromSurface(batch);
      return;
    }

    if (retry_timer_handle_ != TaskHandle::kInvalid) {
      GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                                  << ": cancelling retry timer";
      if (chand_->event_engine()->Cancel(retry_timer_handle_)) {
        GRPC_CALL_STACK_UNREF(owning_call_, "OnRetryTimer");
      }
      retry_timer_handle_ = TaskHandle::kInvalid;
      FreeAllCachedSendOpData();
    }

    // Note: This will release the call combiner.
    grpc_transport_stream_op_batch_finish_with_failure(
        batch, cancelled_from_surface_, call_combiner_);
    return;
  }

  PendingBatch* pending = PendingBatchesAdd(batch);

  if (retry_timer_handle_ != TaskHandle::kInvalid) {
    GRPC_CALL_COMBINER_STOP(call_combiner_,
                            "added pending batch while retry timer pending");
    return;
  }

  if (call_attempt_ == nullptr) {

    if (!retry_codepath_started_ && retry_committed_ &&
        (retry_policy_ == nullptr ||
         !retry_policy_->per_attempt_recv_timeout().has_value())) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << chand_ << " calld=" << this
          << ": retry committed before first attempt; creating LB call";
      PendingBatchClear(pending);
      auto* service_config_call_data =
          DownCast<ClientChannelServiceConfigCallData*>(
              arena_->GetContext<ServiceConfigCallData>());
      committed_call_ = CreateLoadBalancedCall(
          [service_config_call_data]() { service_config_call_data->Commit(); },
          false);
      committed_call_->StartTransportStreamOpBatch(batch);
      return;
    }

    GRPC_TRACE_LOG(retry, INFO)
        << "chand=" << chand_ << " calld=" << this << ": creating call attempt";
    retry_codepath_started_ = true;
    CreateCallAttempt(false);
    return;
  }

  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << chand_ << " calld=" << this
      << ": starting batch on attempt=" << call_attempt_.get();
  call_attempt_->StartRetriableBatches();
}

OrphanablePtr<ClientChannelFilter::FilterBasedLoadBalancedCall>
RetryFilter::LegacyCallData::CreateLoadBalancedCall(
    absl::AnyInvocable<void()> on_commit, bool is_transparent_retry) {
  grpc_call_element_args args = {owning_call_,     nullptr,
                                 0, deadline_,
                                 arena_,           call_combiner_};
  return chand_->client_channel()->CreateLoadBalancedCall(
      args, pollent_,

      call_stack_destruction_barrier_->MakeLbCallDestructionClosure(this),
      std::move(on_commit), is_transparent_retry);
}

void RetryFilter::LegacyCallData::CreateCallAttempt(bool is_transparent_retry) {
  call_attempt_ = MakeRefCounted<CallAttempt>(this, is_transparent_retry);
  call_attempt_->StartRetriableBatches();
}

void RetryFilter::LegacyCallData::MaybeCacheSendOpsForBatch(
    PendingBatch* pending) {
  if (pending->send_ops_cached) return;
  pending->send_ops_cached = true;
  grpc_transport_stream_op_batch* batch = pending->batch;

  if (batch->send_initial_metadata) {
    seen_send_initial_metadata_ = true;
    grpc_metadata_batch* send_initial_metadata =
        batch->payload->send_initial_metadata.send_initial_metadata;
    send_initial_metadata_ = send_initial_metadata->Copy();
  }

  if (batch->send_message) {
    SliceBuffer* cache = arena_->New<SliceBuffer>(std::move(
        *std::exchange(batch->payload->send_message.send_message, nullptr)));
    send_messages_.push_back({cache, batch->payload->send_message.flags});
  }

  if (batch->send_trailing_metadata) {
    seen_send_trailing_metadata_ = true;
    grpc_metadata_batch* send_trailing_metadata =
        batch->payload->send_trailing_metadata.send_trailing_metadata;
    send_trailing_metadata_ = send_trailing_metadata->Copy();
  }
}

void RetryFilter::LegacyCallData::FreeCachedSendInitialMetadata() {
  GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                              << ": destroying send_initial_metadata";
  send_initial_metadata_.Clear();
}

void RetryFilter::LegacyCallData::FreeCachedSendMessage(size_t idx) {
  if (send_messages_[idx].slices != nullptr) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                                << ": destroying send_messages[" << idx << "]";
    Destruct(std::exchange(send_messages_[idx].slices, nullptr));
  }
}

void RetryFilter::LegacyCallData::FreeCachedSendTrailingMetadata() {
  GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                              << ": destroying send_trailing_metadata";
  send_trailing_metadata_.Clear();
}

void RetryFilter::LegacyCallData::FreeAllCachedSendOpData() {
  if (seen_send_initial_metadata_) {
    FreeCachedSendInitialMetadata();
  }
  for (size_t i = 0; i < send_messages_.size(); ++i) {
    FreeCachedSendMessage(i);
  }
  if (seen_send_trailing_metadata_) {
    FreeCachedSendTrailingMetadata();
  }
}

size_t RetryFilter::LegacyCallData::GetBatchIndex(
    grpc_transport_stream_op_batch* batch) {
  if (batch->send_initial_metadata) return 0;
  if (batch->send_message) return 1;
  if (batch->send_trailing_metadata) return 2;
  if (batch->recv_initial_metadata) return 3;
  if (batch->recv_message) return 4;
  if (batch->recv_trailing_metadata) return 5;
  GPR_UNREACHABLE_CODE(return (size_t)-1);
}

RetryFilter::LegacyCallData::PendingBatch*
RetryFilter::LegacyCallData::PendingBatchesAdd(
    grpc_transport_stream_op_batch* batch) {
  const size_t idx = GetBatchIndex(batch);
  GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                              << ": adding pending batch at index " << idx;
  PendingBatch* pending = &pending_batches_[idx];
  CHECK_EQ(pending->batch, nullptr);
  pending->batch = batch;
  pending->send_ops_cached = false;

  // Note: We don't check the size of trailing metadata here, because

  if (batch->send_initial_metadata) {
    pending_send_initial_metadata_ = true;
    bytes_buffered_for_retry_ += batch->payload->send_initial_metadata
                                     .send_initial_metadata->TransportSize();
  }
  if (batch->send_message) {
    pending_send_message_ = true;
    bytes_buffered_for_retry_ +=
        batch->payload->send_message.send_message->Length();
  }
  if (batch->send_trailing_metadata) {
    pending_send_trailing_metadata_ = true;
  }

  if (GPR_UNLIKELY(bytes_buffered_for_retry_ >
                   chand_->per_rpc_retry_buffer_size())) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                                << ": exceeded retry buffer size, committing";
    RetryCommit(call_attempt_.get());
  }
  return pending;
}

void RetryFilter::LegacyCallData::PendingBatchClear(PendingBatch* pending) {
  if (pending->batch->send_initial_metadata) {
    pending_send_initial_metadata_ = false;
  }
  if (pending->batch->send_message) {
    pending_send_message_ = false;
  }
  if (pending->batch->send_trailing_metadata) {
    pending_send_trailing_metadata_ = false;
  }
  pending->batch = nullptr;
}

void RetryFilter::LegacyCallData::MaybeClearPendingBatch(
    PendingBatch* pending) {
  grpc_transport_stream_op_batch* batch = pending->batch;

  if (batch->on_complete == nullptr &&
      (!batch->recv_initial_metadata ||
       batch->payload->recv_initial_metadata.recv_initial_metadata_ready ==
           nullptr) &&
      (!batch->recv_message ||
       batch->payload->recv_message.recv_message_ready == nullptr) &&
      (!batch->recv_trailing_metadata ||
       batch->payload->recv_trailing_metadata.recv_trailing_metadata_ready ==
           nullptr)) {
    GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                                << ": clearing pending batch";
    PendingBatchClear(pending);
  }
}

void RetryFilter::LegacyCallData::FailPendingBatchInCallCombiner(
    void* arg, grpc_error_handle error) {
  grpc_transport_stream_op_batch* batch =
      static_cast<grpc_transport_stream_op_batch*>(arg);
  RetryFilter::LegacyCallData* call = static_cast<RetryFilter::LegacyCallData*>(
      batch->handler_private.extra_arg);
  // Note: This will release the call combiner.
  grpc_transport_stream_op_batch_finish_with_failure(batch, error,
                                                     call->call_combiner_);
}

void RetryFilter::LegacyCallData::PendingBatchesFail(grpc_error_handle error) {
  CHECK(!error.ok());
  if (GRPC_TRACE_FLAG_ENABLED(retry)) {
    size_t num_batches = 0;
    for (size_t i = 0; i < GPR_ARRAY_SIZE(pending_batches_); ++i) {
      if (pending_batches_[i].batch != nullptr) ++num_batches;
    }
    LOG(INFO) << "chand=" << chand_ << " calld=" << this << ": failing "
              << num_batches << " pending batches: " << StatusToString(error);
  }
  CallCombinerClosureList closures;
  for (size_t i = 0; i < GPR_ARRAY_SIZE(pending_batches_); ++i) {
    PendingBatch* pending = &pending_batches_[i];
    grpc_transport_stream_op_batch* batch = pending->batch;
    if (batch != nullptr) {
      batch->handler_private.extra_arg = this;
      GRPC_CLOSURE_INIT(&batch->handler_private.closure,
                        FailPendingBatchInCallCombiner, batch,
                        grpc_schedule_on_exec_ctx);
      closures.Add(&batch->handler_private.closure, error,
                   "PendingBatchesFail");
      PendingBatchClear(pending);
    }
  }
  closures.RunClosuresWithoutYielding(call_combiner_);
}

template <typename Predicate>
RetryFilter::LegacyCallData::PendingBatch*
RetryFilter::LegacyCallData::PendingBatchFind(const char* log_message,
                                              Predicate predicate) {
  for (size_t i = 0; i < GPR_ARRAY_SIZE(pending_batches_); ++i) {
    PendingBatch* pending = &pending_batches_[i];
    grpc_transport_stream_op_batch* batch = pending->batch;
    if (batch != nullptr && predicate(batch)) {
      GRPC_TRACE_LOG(retry, INFO)
          << "chand=" << chand_ << " calld=" << this << ": " << log_message
          << " pending batch at index " << i;
      return pending;
    }
  }
  return nullptr;
}

void RetryFilter::LegacyCallData::RetryCommit(CallAttempt* call_attempt) {
  if (retry_committed_) return;
  retry_committed_ = true;
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << chand_ << " calld=" << this << ": committing retries";
  if (call_attempt != nullptr) {

    // Note: If call_attempt is null, this is happening before the first

    if (call_attempt->lb_call_committed()) {
      auto* service_config_call_data =
          DownCast<ClientChannelServiceConfigCallData*>(
              arena_->GetContext<ServiceConfigCallData>());
      service_config_call_data->Commit();
    }

    call_attempt->FreeCachedSendOpDataAfterCommit();
  }
}

void RetryFilter::LegacyCallData::StartRetryTimer(
    std::optional<Duration> server_pushback) {

  call_attempt_.reset(DEBUG_LOCATION, "StartRetryTimer");

  Duration next_attempt_timeout;
  if (server_pushback.has_value()) {
    CHECK(*server_pushback >= Duration::Zero());
    next_attempt_timeout = *server_pushback;
    retry_backoff_.Reset();
  } else {
    next_attempt_timeout = retry_backoff_.NextAttemptDelay();
  }
  GRPC_TRACE_LOG(retry, INFO)
      << "chand=" << chand_ << " calld=" << this << ": retrying failed call in "
      << next_attempt_timeout.millis() << " ms";

  GRPC_CALL_STACK_REF(owning_call_, "OnRetryTimer");
  retry_timer_handle_ =
      chand_->event_engine()->RunAfter(next_attempt_timeout, [this] {
        ExecCtx exec_ctx;
        OnRetryTimer();
      });
}

void RetryFilter::LegacyCallData::OnRetryTimer() {
  GRPC_CLOSURE_INIT(&retry_closure_, OnRetryTimerLocked, this, nullptr);
  GRPC_CALL_COMBINER_START(call_combiner_, &retry_closure_, absl::OkStatus(),
                           "retry timer fired");
}

void RetryFilter::LegacyCallData::OnRetryTimerLocked(
    void* arg, grpc_error_handle ) {
  auto* calld = static_cast<RetryFilter::LegacyCallData*>(arg);
  if (calld->retry_timer_handle_ != TaskHandle::kInvalid) {
    calld->retry_timer_handle_ = TaskHandle::kInvalid;
    calld->CreateCallAttempt(false);
  }
  GRPC_CALL_STACK_UNREF(calld->owning_call_, "OnRetryTimer");
}

void RetryFilter::LegacyCallData::AddClosureToStartTransparentRetry(
    CallCombinerClosureList* closures) {
  GRPC_TRACE_LOG(retry, INFO) << "chand=" << chand_ << " calld=" << this
                              << ": scheduling transparent retry";
  GRPC_CALL_STACK_REF(owning_call_, "OnRetryTimer");
  GRPC_CLOSURE_INIT(&retry_closure_, StartTransparentRetry, this, nullptr);
  closures->Add(&retry_closure_, absl::OkStatus(), "start transparent retry");
}

void RetryFilter::LegacyCallData::StartTransparentRetry(
    void* arg, grpc_error_handle ) {
  auto* calld = static_cast<RetryFilter::LegacyCallData*>(arg);
  if (calld->cancelled_from_surface_.ok()) {
    calld->CreateCallAttempt(true);
  } else {
    GRPC_CALL_COMBINER_STOP(calld->call_combiner_,
                            "call cancelled before transparent retry");
  }
  GRPC_CALL_STACK_UNREF(calld->owning_call_, "OnRetryTimer");
}

}
