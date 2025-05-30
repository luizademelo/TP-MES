
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_STREAM_CLIENT_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_STREAM_CLIENT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <memory>
#include <optional>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/backoff.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class SubchannelStreamClient final
    : public InternallyRefCounted<SubchannelStreamClient> {
 public:

  class CallEventHandler {
   public:
    virtual ~CallEventHandler() = default;

    virtual Slice GetPathLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;

    virtual void OnCallStartLocked(SubchannelStreamClient* client)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;

    virtual void OnRetryTimerStartLocked(SubchannelStreamClient* client)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;

    virtual grpc_slice EncodeSendMessageLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;

    virtual absl::Status RecvMessageReadyLocked(
        SubchannelStreamClient* client, absl::string_view serialized_message)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;

    virtual void RecvTrailingMetadataReadyLocked(SubchannelStreamClient* client,
                                                 grpc_status_code status)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_) = 0;
  };

  SubchannelStreamClient(
      RefCountedPtr<ConnectedSubchannel> connected_subchannel,
      grpc_pollset_set* interested_parties,
      std::unique_ptr<CallEventHandler> event_handler, const char* tracer);

  ~SubchannelStreamClient() override;

  void Orphan() override;

 private:

  class CallState final : public Orphanable {
   public:
    CallState(RefCountedPtr<SubchannelStreamClient> client,
              grpc_pollset_set* interested_parties);
    ~CallState() override;

    void Orphan() override;

    void StartCallLocked()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&SubchannelStreamClient::mu_);

   private:
    void Cancel();

    void StartBatch(grpc_transport_stream_op_batch* batch);
    static void StartBatchInCallCombiner(void* arg, grpc_error_handle error);

    void CallEndedLocked(bool retry)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&subchannel_stream_client_->mu_);

    void RecvMessageReady();

    static void OnComplete(void* arg, grpc_error_handle error);
    static void RecvInitialMetadataReady(void* arg, grpc_error_handle error);
    static void RecvMessageReady(void* arg, grpc_error_handle error);
    static void RecvTrailingMetadataReady(void* arg, grpc_error_handle error);
    static void StartCancel(void* arg, grpc_error_handle error);
    static void OnCancelComplete(void* arg, grpc_error_handle error);

    static void AfterCallStackDestruction(void* arg, grpc_error_handle error);

    RefCountedPtr<SubchannelStreamClient> subchannel_stream_client_;
    grpc_polling_entity pollent_;

    RefCountedPtr<Arena> arena_;
    CallCombiner call_combiner_;

    SubchannelCall* call_;

    grpc_transport_stream_op_batch_payload payload_;
    grpc_transport_stream_op_batch batch_;
    grpc_transport_stream_op_batch recv_message_batch_;
    grpc_transport_stream_op_batch recv_trailing_metadata_batch_;

    grpc_closure on_complete_;

    grpc_metadata_batch send_initial_metadata_;

    SliceBuffer send_message_;

    grpc_metadata_batch send_trailing_metadata_;

    grpc_metadata_batch recv_initial_metadata_;
    grpc_closure recv_initial_metadata_ready_;

    std::optional<SliceBuffer> recv_message_;
    grpc_closure recv_message_ready_;
    std::atomic<bool> seen_response_{false};

    std::atomic<bool> cancelled_{false};

    grpc_metadata_batch recv_trailing_metadata_;
    grpc_transport_stream_stats collect_stats_;
    grpc_closure recv_trailing_metadata_ready_;

    grpc_closure after_call_stack_destruction_;
  };

  void StartCall();
  void StartCallLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

  void StartRetryTimerLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);
  void OnRetryTimer() ABSL_LOCKS_EXCLUDED(mu_);

  RefCountedPtr<ConnectedSubchannel> connected_subchannel_;
  grpc_pollset_set* interested_parties_;
  const char* tracer_;
  RefCountedPtr<CallArenaAllocator> call_allocator_;

  Mutex mu_;
  std::unique_ptr<CallEventHandler> event_handler_ ABSL_GUARDED_BY(mu_);

  OrphanablePtr<CallState> call_state_ ABSL_GUARDED_BY(mu_);

  BackOff retry_backoff_ ABSL_GUARDED_BY(mu_);
  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      retry_timer_handle_ ABSL_GUARDED_BY(mu_);

  grpc_event_engine::experimental::EventEngine* event_engine_
      ABSL_GUARDED_BY(mu_);
};

}

#endif
