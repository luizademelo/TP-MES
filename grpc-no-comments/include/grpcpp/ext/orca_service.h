
// Copyright 2022 gRPC authors.

#ifndef GRPCPP_EXT_ORCA_SERVICE_H
#define GRPCPP_EXT_ORCA_SERVICE_H

#include <grpc/event_engine/event_engine.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>

#include <cstdint>
#include <optional>

#include "absl/base/thread_annotations.h"
#include "absl/time/time.h"

namespace grpc {

namespace testing {
class OrcaServiceTest;
}

namespace experimental {

class OrcaService : public Service {
 public:
  struct Options {

    absl::Duration min_report_duration = absl::Seconds(30);

    Options() = default;
    Options& set_min_report_duration(absl::Duration duration) {
      min_report_duration = duration;
      return *this;
    }
  };

  OrcaService(ServerMetricRecorder* const server_metric_recorder,
              Options options);

 private:
  class ReactorHook {
   public:
    virtual ~ReactorHook() = default;
    virtual void OnFinish(grpc::Status status) = 0;
    virtual void OnStartWrite(const ByteBuffer* response) = 0;
  };

  class Reactor;
  friend class testing::OrcaServiceTest;

  Slice GetOrCreateSerializedResponse();

  const ServerMetricRecorder* const server_metric_recorder_;
  const absl::Duration min_report_duration_;
  grpc::internal::Mutex mu_;

  std::optional<Slice> response_slice_ ABSL_GUARDED_BY(mu_);

  std::optional<uint64_t> response_slice_seq_ ABSL_GUARDED_BY(mu_);
};

}
}

#endif
