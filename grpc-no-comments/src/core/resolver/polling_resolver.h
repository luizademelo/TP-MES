
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_POLLING_RESOLVER_H
#define GRPC_SRC_CORE_RESOLVER_POLLING_RESOLVER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <optional>
#include <string>

#include "absl/status/status.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/util/backoff.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/time.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

class PollingResolver : public Resolver {
 public:
  PollingResolver(ResolverArgs args, Duration min_time_between_resolutions,
                  BackOff::Options backoff_options, TraceFlag* tracer);
  ~PollingResolver() override;

  void StartLocked() override;
  void RequestReresolutionLocked() override;
  void ResetBackoffLocked() override;
  void ShutdownLocked() override;

 protected:

  virtual OrphanablePtr<Orphanable> StartRequest() = 0;

  void OnRequestComplete(Result result);

  const std::string& authority() const { return authority_; }
  const std::string& name_to_resolve() const { return name_to_resolve_; }
  grpc_pollset_set* interested_parties() const { return interested_parties_; }
  const ChannelArgs& channel_args() const { return channel_args_; }
  WorkSerializer* work_serializer() { return work_serializer_.get(); }

 private:
  void MaybeStartResolvingLocked();
  void StartResolvingLocked();

  void OnRequestCompleteLocked(Result result);
  void GetResultStatus(absl::Status status);

  void ScheduleNextResolutionTimer(Duration delay);
  void OnNextResolutionLocked();
  void MaybeCancelNextResolutionTimer();

  std::string authority_;

  std::string name_to_resolve_;

  ChannelArgs channel_args_;
  std::shared_ptr<WorkSerializer> work_serializer_;
  std::unique_ptr<ResultHandler> result_handler_;
  TraceFlag* tracer_;

  grpc_pollset_set* interested_parties_ = nullptr;

  bool shutdown_ = false;

  OrphanablePtr<Orphanable> request_;

  Duration min_time_between_resolutions_;

  std::optional<Timestamp> last_resolution_timestamp_;

  BackOff backoff_;

  enum class ResultStatusState {
    kNone,
    kResultHealthCallbackPending,
    kReresolutionRequestedWhileCallbackWasPending,
  };
  ResultStatusState result_status_state_ = ResultStatusState::kNone;

  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      next_resolution_timer_handle_;
};

}

#endif
