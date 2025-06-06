
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_GCP_OBSERVABILITY_LOGGING_SINK_H
#define GRPC_SRC_CPP_EXT_GCP_OBSERVABILITY_LOGGING_SINK_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "google/logging/v2/logging.grpc.pb.h"
#include "src/core/ext/filters/logging/logging_sink.h"
#include "src/core/util/sync.h"
#include "src/cpp/ext/gcp/environment_autodetect.h"
#include "src/cpp/ext/gcp/observability_config.h"

namespace grpc {
namespace internal {

class ObservabilityLoggingSink : public grpc_core::LoggingSink {
 public:
  ObservabilityLoggingSink(GcpObservabilityConfig::CloudLogging logging_config,
                           std::string project_id,
                           std::map<std::string, std::string> labels);

  ~ObservabilityLoggingSink() override = default;

  LoggingSink::Config FindMatch(bool is_client, absl::string_view service,
                                absl::string_view method) override;

  void LogEntry(Entry entry) override;

  void FlushAndClose();

 private:
  struct Configuration {
    explicit Configuration(
        const GcpObservabilityConfig::CloudLogging::RpcEventConfiguration&
            rpc_event_config);
    struct ParsedMethod {
      std::string service;
      std::string method;
    };
    std::vector<ParsedMethod> parsed_methods;
    bool exclude = false;
    uint32_t max_metadata_bytes = 0;
    uint32_t max_message_bytes = 0;
  };

  void RegisterEnvironmentResource(
      const EnvironmentAutoDetect::ResourceType* resource);

  void Flush();
  void FlushEntriesHelper(
      google::logging::v2::LoggingServiceV2::StubInterface* stub,
      std::vector<Entry> entries,
      const EnvironmentAutoDetect::ResourceType* resource);

  void MaybeTriggerFlush();
  void MaybeTriggerFlushLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  std::vector<Configuration> client_configs_;
  std::vector<Configuration> server_configs_;
  const std::string project_id_;
  std::string authority_;
  const std::vector<std::pair<std::string, std::string>> labels_;
  grpc_core::Mutex mu_;
  bool registered_env_fetch_notification_ = false;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> ABSL_GUARDED_BY(
      mu_) event_engine_;
  std::unique_ptr<google::logging::v2::LoggingServiceV2::StubInterface> stub_
      ABSL_GUARDED_BY(mu_);
  std::vector<Entry> entries_ ABSL_GUARDED_BY(mu_);
  uint64_t entries_memory_footprint_ ABSL_GUARDED_BY(mu_) = 0;
  const EnvironmentAutoDetect::ResourceType* resource_ ABSL_GUARDED_BY(mu_) =
      nullptr;
  bool flush_triggered_ ABSL_GUARDED_BY(mu_) = false;
  bool flush_in_progress_ ABSL_GUARDED_BY(mu_) = false;
  bool flush_timer_in_progress_ ABSL_GUARDED_BY(mu_) = false;
  bool sink_closed_ ABSL_GUARDED_BY(mu_) = false;
  grpc_core::CondVar sink_flushed_after_close_;
};

void EntryToJsonStructProto(grpc_core::LoggingSink::Entry entry,
                            ::google::protobuf::Struct* json_payload);

}
}

#endif
