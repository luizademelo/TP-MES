
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/subchannel_stream_client.h"

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdio.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"

#define SUBCHANNEL_STREAM_INITIAL_CONNECT_BACKOFF_SECONDS 1
#define SUBCHANNEL_STREAM_RECONNECT_BACKOFF_MULTIPLIER 1.6
#define SUBCHANNEL_STREAM_RECONNECT_MAX_BACKOFF_SECONDS 120
#define SUBCHANNEL_STREAM_RECONNECT_JITTER 0.2

namespace grpc_core {

using ::grpc_event_engine::experimental::EventEngine;

SubchannelStreamClient::SubchannelStreamClient(
    RefCountedPtr<ConnectedSubchannel> connected_subchannel,
    grpc_pollset_set* interested_parties,
    std::unique_ptr<CallEventHandler> event_handler, const char* tracer)
    : InternallyRefCounted<SubchannelStreamClient>(tracer),
      connected_subchannel_(std::move(connected_subchannel)),
      interested_parties_(interested_parties),
      tracer_(tracer),
      call_allocator_(MakeRefCounted<CallArenaAllocator>(
          connected_subchannel_->args()
              .GetObject<ResourceQuota>()
              ->memory_quota()
              ->CreateMemoryAllocator(
                  (tracer != nullptr) ? tracer : "SubchannelStreamClient"),
          1024)),
      event_handler_(std::move(event_handler)),
      retry_backoff_(
          BackOff::Options()
              .set_initial_backoff(Duration::Seconds(
                  SUBCHANNEL_STREAM_INITIAL_CONNECT_BACKOFF_SECONDS))
              .set_multiplier(SUBCHANNEL_STREAM_RECONNECT_BACKOFF_MULTIPLIER)
              .set_jitter(SUBCHANNEL_STREAM_RECONNECT_JITTER)
              .set_max_backoff(Duration::Seconds(
                  SUBCHANNEL_STREAM_RECONNECT_MAX_BACKOFF_SECONDS))),
      event_engine_(connected_subchannel_->args().GetObject<EventEngine>()) {
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this << ": created SubchannelStreamClient";
  }
  StartCall();
}

SubchannelStreamClient::~SubchannelStreamClient() {
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this
              << ": destroying SubchannelStreamClient";
  }
}

void SubchannelStreamClient::Orphan() {
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this
              << ": SubchannelStreamClient shutting down";
  }
  {
    MutexLock lock(&mu_);
    event_handler_.reset();
    call_state_.reset();
    if (retry_timer_handle_.has_value()) {
      event_engine_->Cancel(*retry_timer_handle_);
      retry_timer_handle_.reset();
    }
  }
  Unref(DEBUG_LOCATION, "orphan");
}

void SubchannelStreamClient::StartCall() {
  MutexLock lock(&mu_);
  StartCallLocked();
}

void SubchannelStreamClient::StartCallLocked() {
  if (event_handler_ == nullptr) return;
  CHECK(call_state_ == nullptr);
  if (event_handler_ != nullptr) {
    event_handler_->OnCallStartLocked(this);
  }
  call_state_ = MakeOrphanable<CallState>(Ref(), interested_parties_);
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this
              << ": SubchannelStreamClient created CallState "
              << call_state_.get();
  }
  call_state_->StartCallLocked();
}

void SubchannelStreamClient::StartRetryTimerLocked() {
  if (event_handler_ != nullptr) {
    event_handler_->OnRetryTimerStartLocked(this);
  }
  const Duration timeout = retry_backoff_.NextAttemptDelay();
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this
              << ": SubchannelStreamClient call lost...";
    if (timeout > Duration::Zero()) {
      LOG(INFO) << tracer_ << " " << this << ": ... will retry in "
                << timeout.millis() << "ms.";
    } else {
      LOG(INFO) << tracer_ << " " << this << ": ... retrying immediately.";
    }
  }
  retry_timer_handle_ = event_engine_->RunAfter(
      timeout, [self = Ref(DEBUG_LOCATION, "retry_timer")]() mutable {
        ExecCtx exec_ctx;
        self->OnRetryTimer();
        self.reset(DEBUG_LOCATION, "retry_timer");
      });
}

void SubchannelStreamClient::OnRetryTimer() {
  MutexLock lock(&mu_);
  if (event_handler_ != nullptr && retry_timer_handle_.has_value() &&
      call_state_ == nullptr) {
    if (GPR_UNLIKELY(tracer_ != nullptr)) {
      LOG(INFO) << tracer_ << " " << this
                << ": SubchannelStreamClient restarting call";
    }
    StartCallLocked();
  }
  retry_timer_handle_.reset();
}

SubchannelStreamClient::CallState::CallState(
    RefCountedPtr<SubchannelStreamClient> subchannel_stream_client,
    grpc_pollset_set* interested_parties)
    : subchannel_stream_client_(std::move(subchannel_stream_client)),
      pollent_(grpc_polling_entity_create_from_pollset_set(interested_parties)),
      arena_(subchannel_stream_client_->call_allocator_->MakeArena()) {}

SubchannelStreamClient::CallState::~CallState() {
  if (GPR_UNLIKELY(subchannel_stream_client_->tracer_ != nullptr)) {
    LOG(INFO) << subchannel_stream_client_->tracer_ << " "
              << subchannel_stream_client_.get()
              << ": SubchannelStreamClient destroying CallState " << this;
  }

  call_combiner_.SetNotifyOnCancel(nullptr);
}

void SubchannelStreamClient::CallState::Orphan() {
  call_combiner_.Cancel(absl::CancelledError());
  Cancel();
}

void SubchannelStreamClient::CallState::StartCallLocked() {
  SubchannelCall::Args args = {
      subchannel_stream_client_->connected_subchannel_,
      &pollent_,
      gpr_get_cycle_counter(),
      Timestamp::InfFuture(),
      arena_.get(),
      &call_combiner_,
  };
  grpc_error_handle error;
  call_ = SubchannelCall::Create(std::move(args), &error).release();

  GRPC_CLOSURE_INIT(&after_call_stack_destruction_, AfterCallStackDestruction,
                    this, grpc_schedule_on_exec_ctx);
  call_->SetAfterCallStackDestroy(&after_call_stack_destruction_);

  if (!error.ok() || subchannel_stream_client_->event_handler_ == nullptr) {
    LOG(ERROR) << "SubchannelStreamClient " << subchannel_stream_client_.get()
               << " CallState " << this << ": error creating "
               << "stream on subchannel (" << StatusToString(error)
               << "); will retry";
    CallEndedLocked(true);
    return;
  }

  batch_.payload = &payload_;

  call_->Ref(DEBUG_LOCATION, "on_complete").release();
  batch_.on_complete = GRPC_CLOSURE_INIT(&on_complete_, OnComplete, this,
                                         grpc_schedule_on_exec_ctx);

  send_initial_metadata_.Set(
      HttpPathMetadata(),
      subchannel_stream_client_->event_handler_->GetPathLocked());
  CHECK(error.ok());
  payload_.send_initial_metadata.send_initial_metadata =
      &send_initial_metadata_;
  batch_.send_initial_metadata = true;

  send_message_.Append(Slice(
      subchannel_stream_client_->event_handler_->EncodeSendMessageLocked()));
  payload_.send_message.send_message = &send_message_;
  batch_.send_message = true;

  payload_.send_trailing_metadata.send_trailing_metadata =
      &send_trailing_metadata_;
  batch_.send_trailing_metadata = true;

  payload_.recv_initial_metadata.recv_initial_metadata =
      &recv_initial_metadata_;
  payload_.recv_initial_metadata.trailing_metadata_available = nullptr;

  call_->Ref(DEBUG_LOCATION, "recv_initial_metadata_ready").release();
  payload_.recv_initial_metadata.recv_initial_metadata_ready =
      GRPC_CLOSURE_INIT(&recv_initial_metadata_ready_, RecvInitialMetadataReady,
                        this, grpc_schedule_on_exec_ctx);
  batch_.recv_initial_metadata = true;

  payload_.recv_message.recv_message = &recv_message_;
  payload_.recv_message.call_failed_before_recv_message = nullptr;

  call_->Ref(DEBUG_LOCATION, "recv_message_ready").release();
  payload_.recv_message.recv_message_ready = GRPC_CLOSURE_INIT(
      &recv_message_ready_, RecvMessageReady, this, grpc_schedule_on_exec_ctx);
  batch_.recv_message = true;

  StartBatch(&batch_);

  recv_trailing_metadata_batch_.payload = &payload_;

  payload_.recv_trailing_metadata.recv_trailing_metadata =
      &recv_trailing_metadata_;
  payload_.recv_trailing_metadata.collect_stats = &collect_stats_;

  payload_.recv_trailing_metadata.recv_trailing_metadata_ready =
      GRPC_CLOSURE_INIT(&recv_trailing_metadata_ready_,
                        RecvTrailingMetadataReady, this,
                        grpc_schedule_on_exec_ctx);
  recv_trailing_metadata_batch_.recv_trailing_metadata = true;

  StartBatch(&recv_trailing_metadata_batch_);
}

void SubchannelStreamClient::CallState::StartBatchInCallCombiner(
    void* arg, grpc_error_handle ) {
  auto* batch = static_cast<grpc_transport_stream_op_batch*>(arg);
  auto* call = static_cast<SubchannelCall*>(batch->handler_private.extra_arg);
  call->StartTransportStreamOpBatch(batch);
}

void SubchannelStreamClient::CallState::StartBatch(
    grpc_transport_stream_op_batch* batch) {
  batch->handler_private.extra_arg = call_;
  GRPC_CLOSURE_INIT(&batch->handler_private.closure, StartBatchInCallCombiner,
                    batch, grpc_schedule_on_exec_ctx);
  GRPC_CALL_COMBINER_START(&call_combiner_, &batch->handler_private.closure,
                           absl::OkStatus(), "start_subchannel_batch");
}

void SubchannelStreamClient::CallState::AfterCallStackDestruction(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  delete self;
}

void SubchannelStreamClient::CallState::OnCancelComplete(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "cancel_batch");
  self->call_->Unref(DEBUG_LOCATION, "cancel");
}

void SubchannelStreamClient::CallState::StartCancel(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  auto* batch = grpc_make_transport_stream_op(
      GRPC_CLOSURE_CREATE(OnCancelComplete, self, grpc_schedule_on_exec_ctx));
  batch->cancel_stream = true;
  batch->payload->cancel_stream.cancel_error = absl::CancelledError();
  self->call_->StartTransportStreamOpBatch(batch);
}

void SubchannelStreamClient::CallState::Cancel() {
  bool expected = false;
  if (cancelled_.compare_exchange_strong(expected, true,
                                         std::memory_order_acq_rel,
                                         std::memory_order_acquire)) {
    call_->Ref(DEBUG_LOCATION, "cancel").release();
    GRPC_CALL_COMBINER_START(
        &call_combiner_,
        GRPC_CLOSURE_CREATE(StartCancel, this, grpc_schedule_on_exec_ctx),
        absl::OkStatus(), "cancel_batch");
  }
}

void SubchannelStreamClient::CallState::OnComplete(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "on_complete");
  self->send_initial_metadata_.Clear();
  self->send_trailing_metadata_.Clear();
  self->call_->Unref(DEBUG_LOCATION, "on_complete");
}

void SubchannelStreamClient::CallState::RecvInitialMetadataReady(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "recv_initial_metadata_ready");
  self->recv_initial_metadata_.Clear();
  self->call_->Unref(DEBUG_LOCATION, "recv_initial_metadata_ready");
}

void SubchannelStreamClient::CallState::RecvMessageReady() {
  if (!recv_message_.has_value()) {
    call_->Unref(DEBUG_LOCATION, "recv_message_ready");
    return;
  }

  {
    MutexLock lock(&subchannel_stream_client_->mu_);
    if (subchannel_stream_client_->event_handler_ != nullptr) {
      absl::Status status =
          subchannel_stream_client_->event_handler_->RecvMessageReadyLocked(
              subchannel_stream_client_.get(), recv_message_->JoinIntoString());
      if (!status.ok()) {
        if (GPR_UNLIKELY(subchannel_stream_client_->tracer_ != nullptr)) {
          LOG(INFO) << subchannel_stream_client_->tracer_ << " "
                    << subchannel_stream_client_.get()
                    << ": SubchannelStreamClient CallState " << this
                    << ": failed to parse response message: " << status;
        }
        Cancel();
      }
    }
  }
  seen_response_.store(true, std::memory_order_release);
  recv_message_.reset();

  // Note: Can't just reuse batch_ here, since we don't know that all

  recv_message_batch_.payload = &payload_;
  payload_.recv_message.recv_message = &recv_message_;
  payload_.recv_message.call_failed_before_recv_message = nullptr;
  payload_.recv_message.recv_message_ready = GRPC_CLOSURE_INIT(
      &recv_message_ready_, RecvMessageReady, this, grpc_schedule_on_exec_ctx);
  recv_message_batch_.recv_message = true;
  StartBatch(&recv_message_batch_);
}

void SubchannelStreamClient::CallState::RecvMessageReady(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "recv_message_ready");
  self->RecvMessageReady();
}

void SubchannelStreamClient::CallState::RecvTrailingMetadataReady(
    void* arg, grpc_error_handle error) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_,
                          "recv_trailing_metadata_ready");

  grpc_status_code status =
      self->recv_trailing_metadata_.get(GrpcStatusMetadata())
          .value_or(GRPC_STATUS_UNKNOWN);
  if (!error.ok()) {
    grpc_error_get_status(error, Timestamp::InfFuture(), &status,
                          nullptr , nullptr ,
                          nullptr );
  }
  if (GPR_UNLIKELY(self->subchannel_stream_client_->tracer_ != nullptr)) {
    LOG(INFO) << self->subchannel_stream_client_->tracer_ << " "
              << self->subchannel_stream_client_.get()
              << ": SubchannelStreamClient CallState " << self
              << ": call failed with status " << status;
  }

  self->recv_trailing_metadata_.Clear();

  // Note: We hold a ref to the SubchannelStreamClient here to ensure

  auto subchannel_stream_client = self->subchannel_stream_client_->Ref();
  MutexLock lock(&self->subchannel_stream_client_->mu_);
  if (self->subchannel_stream_client_->event_handler_ != nullptr) {
    self->subchannel_stream_client_->event_handler_
        ->RecvTrailingMetadataReadyLocked(self->subchannel_stream_client_.get(),
                                          status);
  }

  self->CallEndedLocked(status != GRPC_STATUS_UNIMPLEMENTED);
}

void SubchannelStreamClient::CallState::CallEndedLocked(bool retry) {

  if (this == subchannel_stream_client_->call_state_.get()) {
    subchannel_stream_client_->call_state_.reset();
    if (retry) {
      CHECK(subchannel_stream_client_->event_handler_ != nullptr);
      if (seen_response_.load(std::memory_order_acquire)) {

        subchannel_stream_client_->retry_backoff_.Reset();
        subchannel_stream_client_->StartCallLocked();
      } else {

        subchannel_stream_client_->StartRetryTimerLocked();
      }
    }
  }

  call_->Unref(DEBUG_LOCATION, "call_ended");
}

}
