Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/util/event_log.h"

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <atomic>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

// Static instance of EventLog that is globally accessible
std::atomic<EventLog*> EventLog::g_instance_{nullptr};

// Destructor ensures this instance is not the active global instance
EventLog::~EventLog() {
  CHECK(g_instance_.load(std::memory_order_acquire) != this);
}

// Begins event collection by:
// 1. Clearing all existing event fragments
// 2. Recording the start time
// 3. Setting this instance as the global instance
// 4. Logging the start of collection
void EventLog::BeginCollection() {
  for (auto& fragment : fragments_) {
    MutexLock lock(&fragment.mu);
    fragment.entries.clear();
  }
  collection_begin_ = gpr_get_cycle_counter();
  g_instance_.store(this, std::memory_order_release);
  Append("logging", 1);
}

// Ends event collection by:
// 1. Logging the end of collection
// 2. Clearing the global instance
// 3. Gathering all matching events from fragments
// 4. Sorting events chronologically
// Returns a vector of events that match the wanted_events filter
std::vector<EventLog::Entry> EventLog::EndCollection(
    absl::Span<const absl::string_view> wanted_events) {
  Append("logging", -1);
  g_instance_.store(nullptr, std::memory_order_release);
  std::vector<Entry> result;
  for (auto& fragment : fragments_) {
    MutexLock lock(&fragment.mu);
    for (const auto& entry : fragment.entries) {
      if (std::find(wanted_events.begin(), wanted_events.end(), entry.event) !=
          wanted_events.end()) {
        result.push_back(entry);
      }
    }
    fragment.entries.clear();
  }
  std::stable_sort(
      result.begin(), result.end(),
      [](const Entry& a, const Entry& b) { return a.when < b.when; });
  return result;
}

// Internal method to append an event to the current CPU's fragment
// Each event consists of:
// - Timestamp (cycle counter)
// - Event name
// - Delta value (typically +1/-1 for start/end events)
void EventLog::AppendInternal(absl::string_view event, int64_t delta) {
  auto& fragment = fragments_.this_cpu();
  MutexLock lock(&fragment.mu);
  fragment.entries.push_back({gpr_get_cycle_counter(), event, delta});
}

// Ends collection and generates a CSV report with:
// - Header row containing column names
// - Each row represents a point in time with cumulative values
// - Timestamps are relative to collection start
// - Values are accumulated based on event deltas
std::string EventLog::EndCollectionAndReportCsv(
    absl::Span<const absl::string_view> columns) {
  auto events = EndCollection(columns);
  std::vector<int64_t> values(columns.size(), 0);
  std::string result =
      absl::StrCat("timestamp,", absl::StrJoin(columns, ","), "\n");
  for (const auto& entry : events) {
    auto idx = std::find(columns.begin(), columns.end(), entry.event) -
               columns.begin();
    values[idx] += entry.delta;
    absl::StrAppend(&result, entry.when - collection_begin_, ",",
                    absl::StrJoin(values, ","), "\n");
  }
  return result;
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each method and its high-level behavior
2. Key implementation details
3. Important data structures and their usage
4. The flow of data through the system
5. The thread-safety mechanisms (mutexes, atomics)
6. The format of output data (particularly for the CSV generation)

The comments are designed to help future maintainers understand:
- What the code does
- Why it does it that way
- How the different components interact
- The thread-safety considerations
- The data flow through the system