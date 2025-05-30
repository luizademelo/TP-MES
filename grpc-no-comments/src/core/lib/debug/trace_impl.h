// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_DEBUG_TRACE_IMPL_H
#define GRPC_SRC_CORE_LIB_DEBUG_TRACE_IMPL_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <map>
#include <string>

#include "absl/container/flat_hash_map.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"

#ifdef _WIN32
#undef ERROR
#endif

void grpc_tracer_init();
void grpc_tracer_shutdown(void);

namespace grpc_core {
bool ParseTracers(absl::string_view tracers);
class SavedTraceFlags;

class TraceFlag;

namespace testing {
void grpc_tracer_enable_flag(TraceFlag* flag);
}

class TraceFlag {
 public:
  TraceFlag(bool default_enabled, const char* name);

  ~TraceFlag() = default;

  const char* name() const { return name_; }

#define GRPC_USE_TRACERS
#if defined(GRPC_USE_TRACERS) || !defined(NDEBUG)
  bool enabled() { return value_.load(std::memory_order_relaxed); }
#else
  bool enabled() { return false; }
#endif

 private:
  friend void testing::grpc_tracer_enable_flag(TraceFlag* flag);
  friend bool ParseTracers(absl::string_view tracers);
  friend SavedTraceFlags;

  void set_enabled(bool enabled) {
    value_.store(enabled, std::memory_order_relaxed);
  }

  TraceFlag* next_tracer_;
  const char* const name_;
  std::atomic<bool> value_;
};

#define GRPC_TRACE_FLAG_ENABLED_OBJ(obj) GPR_UNLIKELY((obj).enabled())

#define GRPC_TRACE_FLAG_ENABLED(tracer) \
  GPR_UNLIKELY((grpc_core::tracer##_trace).enabled())

#define GRPC_TRACE_LOG(tracer, level) \
  LOG_IF(level, GRPC_TRACE_FLAG_ENABLED(tracer))

#define GRPC_TRACE_DLOG(tracer, level) \
  DLOG_IF(level, GRPC_TRACE_FLAG_ENABLED(tracer))

#define GRPC_TRACE_VLOG(tracer, level) \
  if (GRPC_TRACE_FLAG_ENABLED(tracer)) VLOG(level)

#ifndef NDEBUG
typedef TraceFlag DebugOnlyTraceFlag;
#else
class DebugOnlyTraceFlag {
 public:
  constexpr DebugOnlyTraceFlag(bool , const char* ) {
  }
  constexpr bool enabled() const { return false; }
  constexpr const char* name() const { return "DebugOnlyTraceFlag"; }

 private:
  void set_enabled(bool ) {}
};
#endif

class SavedTraceFlags {
 public:
  SavedTraceFlags();
  void Restore();

 private:
  std::map<std::string, std::pair<bool, TraceFlag*>> values_;
};

const absl::flat_hash_map<std::string, TraceFlag*>& GetAllTraceFlags();

}

#endif
