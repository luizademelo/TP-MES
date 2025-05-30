// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_FILTER_LEGACY_CALL_DATA_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_FILTER_LEGACY_CALL_DATA_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <optional>
#include <utility>

#include "absl/container/inlined_vector.h"
#include "absl/functional/any_invocable.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/client_channel/retry_filter.h"
#include "src/core/client_channel/retry_service_config.h"
#include "src/core/client_channel/retry_throttle.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/backoff.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"

namespace grpc_core {

class RetryFilter::LegacyCallData final {
 public:
  static grpc_error_handle Init(grpc_call_element* elem,
                                const grpc_call_element_args* args);
  static void Destroy(grpc_call_element* elem,
                      const grpc_call_final_info* ,
                      grpc_closure* then_schedule_closure);
  static void StartTransportStreamOpBatch(
      grpc_call_element* elem, grpc_transport_stream_op_batch* batch);
  static void SetPollent(grpc_call_element* elem, grpc_polling_entity* pollent);

 private:
  class CallStackDestructionBarrier;

  struct PendingBatch {

    grpc_transport_stream_op_batch* batch = nullptr;

    bool send_ops_cached = false;
  };

  class CallAttempt final : public RefCounted<CallAttempt> {
   public:
    CallAttempt(LegacyCallData* calld, bool is_transparent_retry);
    ~CallAttempt() override;

    bool lb_call_committed() const { return lb_call_committed_; }

    void StartRetriableBatches();

    void FreeCachedSendOpDataAfterCommit();

    void CancelFromSurface(grpc_transport_stream_op_batch* cancel_batch);

   private:

    class BatchData final
        : public RefCounted<BatchData, PolymorphicRefCount, UnrefCallDtor> {
     public:
      BatchData(RefCountedPtr<CallAttempt> call_attempt, int refcount,
                bool set_on_complete);
      ~BatchData() override;

      grpc_transport_stream_op_batch* batch() { return &batch_; }

      void AddRetriableSendInitialMetadataOp();

      void AddRetriableSendMessageOp();

      void AddRetriableSendTrailingMetadataOp();

      void AddRetriableRecvInitialMetadataOp();

      void AddRetriableRecvMessageOp();

      void AddRetriableRecvTrailingMetadataOp();

      void AddCancelStreamOp(grpc_error_handle error);

     private:

      void FreeCachedSendOpDataForCompletedBatch();

      void MaybeAddClosureForRecvInitialMetadataCallback(
          grpc_error_handle error, CallCombinerClosureList* closures);

      static void RecvInitialMetadataReady(void* arg, grpc_error_handle error);

      void MaybeAddClosureForRecvMessageCallback(
          grpc_error_handle error, CallCombinerClosureList* closures);

      static void RecvMessageReady(void* arg, grpc_error_handle error);

      void MaybeAddClosureForRecvTrailingMetadataReady(
          grpc_error_handle error, CallCombinerClosureList* closures);

      void AddClosuresForDeferredCompletionCallbacks(
          CallCombinerClosureList* closures);

      void AddClosuresToFailUnstartedPendingBatches(
          grpc_error_handle error, CallCombinerClosureList* closures);

      void RunClosuresForCompletedCall(grpc_error_handle error);

      static void RecvTrailingMetadataReady(void* arg, grpc_error_handle error);

      void AddClosuresForCompletedPendingBatch(
          grpc_error_handle error, CallCombinerClosureList* closures);

      void AddClosuresForReplayOrPendingSendOps(
          CallCombinerClosureList* closures);

      static void OnComplete(void* arg, grpc_error_handle error);

      static void OnCompleteForCancelOp(void* arg, grpc_error_handle error);

      CallAttempt* call_attempt_;

      grpc_transport_stream_op_batch batch_;

      grpc_closure on_complete_;
    };

    BatchData* CreateBatch(int refcount, bool set_on_complete) {
      return calld_->arena_->New<BatchData>(Ref(DEBUG_LOCATION, "CreateBatch"),
                                            refcount, set_on_complete);
    }

    BatchData* MaybeCreateBatchForReplay();

    void AddClosureForBatch(grpc_transport_stream_op_batch* batch,
                            const char* reason,
                            CallCombinerClosureList* closures);

    void AddBatchForInternalRecvTrailingMetadata(
        CallCombinerClosureList* closures);

    void MaybeAddBatchForCancelOp(grpc_error_handle error,
                                  CallCombinerClosureList* closures);

    void AddBatchesForPendingBatches(CallCombinerClosureList* closures);

    void AddRetriableBatches(CallCombinerClosureList* closures);

    bool PendingBatchContainsUnstartedSendOps(PendingBatch* pending);

    bool HaveSendOpsToReplay();

    void MaybeSwitchToFastPath();

    bool ShouldRetry(std::optional<grpc_status_code> status,
                     std::optional<Duration> server_pushback_ms);

    void Abandon();

    void OnPerAttemptRecvTimer();
    static void OnPerAttemptRecvTimerLocked(void* arg, grpc_error_handle error);
    void MaybeCancelPerAttemptRecvTimer();

    LegacyCallData* calld_;
    OrphanablePtr<ClientChannelFilter::FilterBasedLoadBalancedCall> lb_call_;
    bool lb_call_committed_ = false;

    grpc_closure on_per_attempt_recv_timer_;
    grpc_event_engine::experimental::EventEngine::TaskHandle
        per_attempt_recv_timer_handle_ =
            grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;

    grpc_transport_stream_op_batch_payload batch_payload_;

    grpc_metadata_batch send_initial_metadata_;

    SliceBuffer send_message_;

    grpc_metadata_batch send_trailing_metadata_;

    grpc_metadata_batch recv_initial_metadata_;
    grpc_closure recv_initial_metadata_ready_;
    bool trailing_metadata_available_ = false;

    grpc_closure recv_message_ready_;
    std::optional<SliceBuffer> recv_message_;
    uint32_t recv_message_flags_;

    grpc_metadata_batch recv_trailing_metadata_;
    grpc_transport_stream_stats collect_stats_;
    grpc_closure recv_trailing_metadata_ready_;

    size_t started_send_message_count_ = 0;
    size_t completed_send_message_count_ = 0;
    size_t started_recv_message_count_ = 0;
    size_t completed_recv_message_count_ = 0;
    bool started_send_initial_metadata_ : 1;
    bool completed_send_initial_metadata_ : 1;
    bool started_send_trailing_metadata_ : 1;
    bool completed_send_trailing_metadata_ : 1;
    bool started_recv_initial_metadata_ : 1;
    bool completed_recv_initial_metadata_ : 1;
    bool started_recv_trailing_metadata_ : 1;
    bool completed_recv_trailing_metadata_ : 1;
    bool sent_cancel_stream_ : 1;

    RefCountedPtr<BatchData> recv_initial_metadata_ready_deferred_batch_;
    grpc_error_handle recv_initial_metadata_error_;
    RefCountedPtr<BatchData> recv_message_ready_deferred_batch_;
    grpc_error_handle recv_message_error_;
    struct OnCompleteDeferredBatch {
      OnCompleteDeferredBatch(RefCountedPtr<BatchData> batch,
                              grpc_error_handle error)
          : batch(std::move(batch)), error(error) {}
      RefCountedPtr<BatchData> batch;
      grpc_error_handle error;
    };

    absl::InlinedVector<OnCompleteDeferredBatch, 3>
        on_complete_deferred_batches_;
    RefCountedPtr<BatchData> recv_trailing_metadata_internal_batch_;
    grpc_error_handle recv_trailing_metadata_error_;
    bool seen_recv_trailing_metadata_from_surface_ : 1;
    // NOTE: Do not move this next to the metadata bitfields above. That would

    bool abandoned_ : 1;
  };

  LegacyCallData(RetryFilter* chand, const grpc_call_element_args& args);
  ~LegacyCallData();

  void StartTransportStreamOpBatch(grpc_transport_stream_op_batch* batch);

  static size_t GetBatchIndex(grpc_transport_stream_op_batch* batch);
  PendingBatch* PendingBatchesAdd(grpc_transport_stream_op_batch* batch);
  void PendingBatchClear(PendingBatch* pending);
  void MaybeClearPendingBatch(PendingBatch* pending);
  static void FailPendingBatchInCallCombiner(void* arg,
                                             grpc_error_handle error);

  void PendingBatchesFail(grpc_error_handle error);

  template <typename Predicate>
  PendingBatch* PendingBatchFind(const char* log_message, Predicate predicate);

  void MaybeCacheSendOpsForBatch(PendingBatch* pending);
  void FreeCachedSendInitialMetadata();

  void FreeCachedSendMessage(size_t idx);
  void FreeCachedSendTrailingMetadata();
  void FreeAllCachedSendOpData();

  void RetryCommit(CallAttempt* call_attempt);

  void StartRetryTimer(std::optional<Duration> server_pushback);

  void OnRetryTimer();
  static void OnRetryTimerLocked(void* arg, grpc_error_handle );

  void AddClosureToStartTransparentRetry(CallCombinerClosureList* closures);
  static void StartTransparentRetry(void* arg, grpc_error_handle error);

  OrphanablePtr<ClientChannelFilter::FilterBasedLoadBalancedCall>
  CreateLoadBalancedCall(absl::AnyInvocable<void()> on_commit,
                         bool is_transparent_retry);

  void CreateCallAttempt(bool is_transparent_retry);

  RetryFilter* chand_;
  grpc_polling_entity* pollent_;
  RefCountedPtr<internal::ServerRetryThrottleData> retry_throttle_data_;
  const internal::RetryMethodConfig* retry_policy_ = nullptr;
  BackOff retry_backoff_;

  Timestamp deadline_;
  Arena* arena_;
  grpc_call_stack* owning_call_;
  CallCombiner* call_combiner_;

  grpc_error_handle cancelled_from_surface_;

  RefCountedPtr<CallStackDestructionBarrier> call_stack_destruction_barrier_;

  RefCountedPtr<CallAttempt> call_attempt_;

  OrphanablePtr<ClientChannelFilter::FilterBasedLoadBalancedCall>
      committed_call_;

  size_t bytes_buffered_for_retry_ = 0;
  PendingBatch pending_batches_[MAX_PENDING_BATCHES];
  bool pending_send_initial_metadata_ : 1;
  bool pending_send_message_ : 1;
  bool pending_send_trailing_metadata_ : 1;

  bool retry_committed_ : 1;
  bool retry_codepath_started_ : 1;
  bool sent_transparent_retry_not_seen_by_server_ : 1;
  int num_attempts_completed_ = 0;
  grpc_event_engine::experimental::EventEngine::TaskHandle retry_timer_handle_ =
      grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;
  grpc_closure retry_closure_;

  bool seen_send_initial_metadata_ = false;
  grpc_metadata_batch send_initial_metadata_;

  // Note: We inline the cache for the first 3 send_message ops and use

  struct CachedSendMessage {
    SliceBuffer* slices;
    uint32_t flags;
  };
  absl::InlinedVector<CachedSendMessage, 3> send_messages_;

  bool seen_send_trailing_metadata_ = false;
  grpc_metadata_batch send_trailing_metadata_;
};

}

#endif
