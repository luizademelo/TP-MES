Here's the commented version of the code:

```c++
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

// Backoff configuration constants for stream reconnection
#define SUBCHANNEL_STREAM_INITIAL_CONNECT_BACKOFF_SECONDS 1
#define SUBCHANNEL_STREAM_RECONNECT_BACKOFF_MULTIPLIER 1.6
#define SUBCHANNEL_STREAM_RECONNECT_MAX_BACKOFF_SECONDS 120
#define SUBCHANNEL_STREAM_RECONNECT_JITTER 0.2

namespace grpc_core {

using ::grpc_event_engine::experimental::EventEngine;

// Constructor for SubchannelStreamClient
// Args:
//   connected_subchannel: The connected subchannel to use for communication
//   interested_parties: Pollset set interested in I/O events
//   event_handler: Handler for call events
//   tracer: Debug tracer string (nullable)
SubchannelStreamClient::SubchannelStreamClient(
    RefCountedPtr<ConnectedSubchannel> connected_subchannel,
    grpc_pollset_set* interested_parties,
    std::unique_ptr<CallEventHandler> event_handler, const char* tracer)
    : InternallyRefCounted<SubchannelStreamClient>(tracer),
      connected_subchannel_(std::move(connected_subchannel)),
      interested_parties_(interested_parties),
      tracer_(tracer),
      // Create memory allocator for call arenas
      call_allocator_(MakeRefCounted<CallArenaAllocator>(
          connected_subchannel_->args()
              .GetObject<ResourceQuota>()
              ->memory_quota()
              ->CreateMemoryAllocator(
                  (tracer != nullptr) ? tracer : "SubchannelStreamClient"),
          1024)),
      event_handler_(std::move(event_handler)),
      // Initialize backoff policy for retries
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

// Destructor - logs destruction if tracer is enabled
SubchannelStreamClient::~SubchannelStreamClient() {
  if (GPR_UNLIKELY(tracer_ != nullptr)) {
    LOG(INFO) << tracer_ << " " << this
              << ": destroying SubchannelStreamClient";
  }
}

// Clean up resources when the client is orphaned
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

// Starts a new call (thread-safe)
void SubchannelStreamClient::StartCall() {
  MutexLock lock(&mu_);
  StartCallLocked();
}

// Starts a new call (must be called with mutex held)
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

// Starts the retry timer (must be called with mutex held)
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

// Callback for when retry timer fires
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

// CallState constructor
SubchannelStreamClient::CallState::CallState(
    RefCountedPtr<SubchannelStreamClient> subchannel_stream_client,
    grpc_pollset_set* interested_parties)
    : subchannel_stream_client_(std::move(subchannel_stream_client)),
      pollent_(grpc_polling_entity_create_from_pollset_set(interested_parties)),
      arena_(subchannel_stream_client_->call_allocator_->MakeArena()) {}

// CallState destructor
SubchannelStreamClient::CallState::~CallState() {
  if (GPR_UNLIKELY(subchannel_stream_client_->tracer_ != nullptr)) {
    LOG(INFO) << subchannel_stream_client_->tracer_ << " "
              << subchannel_stream_client_.get()
              << ": SubchannelStreamClient destroying CallState " << this;
  }

  call_combiner_.SetNotifyOnCancel(nullptr);
}

// Clean up call state when orphaned
void SubchannelStreamClient::CallState::Orphan() {
  call_combiner_.Cancel(absl::CancelledError());
  Cancel();
}

// Starts the call (must be called with mutex held)
void SubchannelStreamClient::CallState::StartCallLocked() {
  // Set up call arguments
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

  // Set up cleanup callback
  GRPC_CLOSURE_INIT(&after_call_stack_destruction_, AfterCallStackDestruction,
                    this, grpc_schedule_on_exec_ctx);
  call_->SetAfterCallStackDestroy(&after_call_stack_destruction_);

  // Handle creation error
  if (!error.ok() || subchannel_stream_client_->event_handler_ == nullptr) {
    LOG(ERROR) << "SubchannelStreamClient " << subchannel_stream_client_.get()
               << " CallState " << this << ": error creating "
               << "stream on subchannel (" << StatusToString(error)
               << "); will retry";
    CallEndedLocked(true);
    return;
  }

  // Set up initial batch
  batch_.payload = &payload_;

  call_->Ref(DEBUG_LOCATION, "on_complete").release();
  batch_.on_complete = GRPC_CLOSURE_INIT(&on_complete_, OnComplete, this,
                                         grpc_schedule_on_exec_ctx);

  // Set up send initial metadata
  send_initial_metadata_.Set(
      HttpPathMetadata(),
      subchannel_stream_client_->event_handler_->GetPathLocked());
  CHECK(error.ok());
  payload_.send_initial_metadata.send_initial_metadata =
      &send_initial_metadata_;
  batch_.send_initial_metadata = true;

  // Set up send message
  send_message_.Append(Slice(
      subchannel_stream_client_->event_handler_->EncodeSendMessageLocked()));
  payload_.send_message.send_message = &send_message_;
  batch_.send_message = true;

  // Set up send trailing metadata
  payload_.send_trailing_metadata.send_trailing_metadata =
      &send_trailing_metadata_;
  batch_.send_trailing_metadata = true;

  // Set up receive initial metadata
  payload_.recv_initial_metadata.recv_initial_metadata =
      &recv_initial_metadata_;
  payload_.recv_initial_metadata.trailing_metadata_available = nullptr;

  call_->Ref(DEBUG_LOCATION, "recv_initial_metadata_ready").release();
  payload_.recv_initial_metadata.recv_initial_metadata_ready =
      GRPC_CLOSURE_INIT(&recv_initial_metadata_ready_, RecvInitialMetadataReady,
                        this, grpc_schedule_on_exec_ctx);
  batch_.recv_initial_metadata = true;

  // Set up receive message
  payload_.recv_message.recv_message = &recv_message_;
  payload_.recv_message.call_failed_before_recv_message = nullptr;

  call_->Ref(DEBUG_LOCATION, "recv_message_ready").release();
  payload_.recv_message.recv_message_ready = GRPC_CLOSURE_INIT(
      &recv_message_ready_, RecvMessageReady, this, grpc_schedule_on_exec_ctx);
  batch_.recv_message = true;

  // Start the batch
  StartBatch(&batch_);

  // Set up receive trailing metadata batch
  recv_trailing_metadata_batch_.payload = &payload_;

  payload_.recv_trailing_metadata.recv_trailing_metadata =
      &recv_trailing_metadata_;
  payload_.recv_trailing_metadata.collect_stats = &collect_stats_;

  payload_.recv_trailing_metadata.recv_trailing_metadata_ready =
      GRPC_CLOSURE_INIT(&recv_trailing_metadata_ready_,
                        RecvTrailingMetadataReady, this,
                        grpc_schedule_on_exec_ctx);
  recv_trailing_metadata_batch_.recv_trailing_metadata = true;

  // Start the receive trailing metadata batch
  StartBatch(&recv_trailing_metadata_batch_);
}

// Starts a batch operation in the call combiner
void SubchannelStreamClient::CallState::StartBatchInCallCombiner(
    void* arg, grpc_error_handle ) {
  auto* batch = static_cast<grpc_transport_stream_op_batch*>(arg);
  auto* call = static_cast<SubchannelCall*>(batch->handler_private.extra_arg);
  call->StartTransportStreamOpBatch(batch);
}

// Starts a batch operation
void SubchannelStreamClient::CallState::StartBatch(
    grpc_transport_stream_op_batch* batch) {
  batch->handler_private.extra_arg = call_;
  GRPC_CLOSURE_INIT(&batch->handler_private.closure, StartBatchInCallCombiner,
                    batch, grpc_schedule_on_exec_ctx);
  GRPC_CALL_COMBINER_START(&call_combiner_, &batch->handler_private.closure,
                           absl::OkStatus(), "start_subchannel_batch");
}

// Callback for after call stack is destroyed
void SubchannelStreamClient::CallState::AfterCallStackDestruction(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  delete self;
}

// Callback for cancel completion
void SubchannelStreamClient::CallState::OnCancelComplete(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "cancel_batch");
  self->call_->Unref(DEBUG_LOCATION, "cancel");
}

// Starts cancel operation
void SubchannelStreamClient::CallState::StartCancel(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  auto* batch = grpc_make_transport_stream_op(
      GRPC_CLOSURE_CREATE(OnCancelComplete, self, grpc_schedule_on_exec_ctx));
  batch->cancel_stream = true;
  batch->payload->cancel_stream.cancel_error = absl::CancelledError();
  self->call_->StartTransportStreamOpBatch(batch);
}

// Cancels the call
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

// Callback for batch completion
void SubchannelStreamClient::CallState::OnComplete(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "on_complete");
  self->send_initial_metadata_.Clear();
  self->send_trailing_metadata_.Clear();
  self->call_->Unref(DEBUG_LOCATION, "on_complete");
}

// Callback for receiving initial metadata
void SubchannelStreamClient::CallState::RecvInitialMetadataReady(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "recv_initial_metadata_ready");
  self->recv_initial_metadata_.Clear();
  self->call_->Unref(DEBUG_LOCATION, "recv_initial_metadata_ready");
}

// Handles received message
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
  // operations have completed

  // Set up next receive message batch
  recv_message_batch_.payload = &payload_;
  payload_.recv_message.recv_message = &recv_message_;
  payload_.recv_message.call_failed_before_recv_message = nullptr;
  payload_.recv_message.recv_message_ready = GRPC_CLOSURE_INIT(
      &recv_message_ready_, RecvMessageReady, this, grpc_schedule_on_exec_ctx);
  recv_message_batch_.recv_message = true;
  StartBatch(&recv_message_batch_);
}

// Callback for receiving message
void SubchannelStreamClient::CallState::RecvMessageReady(
    void* arg, grpc_error_handle ) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_combiner_, "recv_message_ready");
  self->RecvMessageReady();
}

// Callback for receiving trailing metadata
void SubchannelStreamClient::CallState::RecvTrailingMetadataReady(
    void* arg, grpc_error_handle error) {
  auto* self = static_cast<SubchannelStreamClient::CallState*>(arg);
  GRPC_CALL_COMBINER_STOP(&self->call_comb