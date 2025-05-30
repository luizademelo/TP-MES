// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_EVENT_LOG_H
#define GRPC_SRC_CORE_UTIL_EVENT_LOG_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <atomic>
#include <string>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/util/per_cpu.h"
#include "src/core/util/sync.h"
#include "src/core/util/time_precise.h"

namespace grpc_core {

class EventLog {
 public:
  EventLog() = default;
  ~EventLog();

  EventLog(const EventLog&) = delete;
  EventLog& operator=(const EventLog&) = delete;

  void BeginCollection();
  std::string EndCollectionAndReportCsv(
      absl::Span<const absl::string_view> columns);

  static void Append(absl::string_view event, int64_t delta) {
    EventLog* log = g_instance_.load(std::memory_order_acquire);
    if (log == nullptr) return;
    log->AppendInternal(event, delta);
  }

 private:
  struct Entry {
    gpr_cycle_counter when;
    absl::string_view event;
    int64_t delta;
  };

  struct Fragment {
    Mutex mu;
    std::vector<Entry> entries ABSL_GUARDED_BY(mu);
  };

  void AppendInternal(absl::string_view event, int64_t delta);
  std::vector<Entry> EndCollection(
      absl::Span<const absl::string_view> wanted_events);

  PerCpu<Fragment> fragments_{PerCpuOptions().SetCpusPerShard(2)};
  gpr_cycle_counter collection_begin_;
  static std::atomic<EventLog*> g_instance_;
};

}

#endif
