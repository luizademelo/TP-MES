
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_CHANNELZ_CHANNEL_TRACE_H
#define GRPC_SRC_CORE_CHANNELZ_CHANNEL_TRACE_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "absl/base/thread_annotations.h"
#include "src/core/util/json/json.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace channelz {

namespace testing {
size_t GetSizeofTraceEvent(void);
}

class BaseNode;

class ChannelTrace {
 public:
  explicit ChannelTrace(size_t max_event_memory);
  ~ChannelTrace();

  enum Severity {
    Unset = 0,
    Info,
    Warning,
    Error
  };

  static const char* SeverityString(ChannelTrace::Severity severity) {
    switch (severity) {
      case ChannelTrace::Severity::Info:
        return "CT_INFO";
      case ChannelTrace::Severity::Warning:
        return "CT_WARNING";
      case ChannelTrace::Severity::Error:
        return "CT_ERROR";
      default:
        GPR_UNREACHABLE_CODE(return "CT_UNKNOWN");
    }
  }

  // NOTE: each ChannelTrace tracks the memory used by its list of trace

  void AddTraceEvent(Severity severity, const grpc_slice& data);

  // NOTE: see the note in the method above.

  void AddTraceEventWithReference(Severity severity, const grpc_slice& data,
                                  RefCountedPtr<BaseNode> referenced_entity);

  Json RenderJson() const;

  void ForEachTraceEvent(
      absl::FunctionRef<void(gpr_timespec, Severity, std::string,
                             RefCountedPtr<BaseNode>)>
          callback) const {
    MutexLock lock(&mu_);
    ForEachTraceEventLocked(callback);
  }
  std::string creation_timestamp() const;
  uint64_t num_events_logged() const {
    MutexLock lock(&mu_);
    return num_events_logged_;
  }

 private:
  friend size_t testing::GetSizeofTraceEvent(void);

  class TraceEvent {
   public:

    TraceEvent(Severity severity, const grpc_slice& data,
               RefCountedPtr<BaseNode> referenced_entity_);

    TraceEvent(Severity severity, const grpc_slice& data);

    ~TraceEvent();

    TraceEvent* next() const { return next_; }
    void set_next(TraceEvent* next) { next_ = next; }

    size_t memory_usage() const { return memory_usage_; }
    gpr_timespec timestamp() const { return timestamp_; }
    Severity severity() const { return severity_; }
    std::string description() const;
    RefCountedPtr<BaseNode> referenced_entity() const;

   private:
    const gpr_timespec timestamp_;
    const Severity severity_;
    const grpc_slice data_;
    const size_t memory_usage_;

    const RefCountedPtr<BaseNode> referenced_entity_;
    TraceEvent* next_ = nullptr;
  };

  void AddTraceEventHelper(TraceEvent* new_trace_event);
  void ForEachTraceEventLocked(
      absl::FunctionRef<void(gpr_timespec, Severity, std::string,
                             RefCountedPtr<BaseNode>)>) const
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  const size_t max_event_memory_;
  const gpr_timespec time_created_;

  mutable Mutex mu_;
  uint64_t num_events_logged_ ABSL_GUARDED_BY(mu_) = 0;
  size_t event_list_memory_usage_ ABSL_GUARDED_BY(mu_) = 0;
  TraceEvent* head_trace_ ABSL_GUARDED_BY(mu_) = nullptr;
  TraceEvent* tail_trace_ ABSL_GUARDED_BY(mu_) = nullptr;
};

}
}

#endif
