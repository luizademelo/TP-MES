// Copyright 2023 gRPC authors.

#ifndef GRPC_PYTHON_OBSERVABILITY_H
#define GRPC_PYTHON_OBSERVABILITY_H

#include <grpc/slice.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "constants.h"
#include "sampler.h"
#include "src/core/lib/channel/channel_stack.h"

namespace grpc_observability {

namespace {
std::atomic<bool> g_python_census_stats_enabled(false);
std::atomic<bool> g_python_census_tracing_enabled(false);
}

void EnablePythonCensusStats(bool enable);
void EnablePythonCensusTracing(bool enable);

bool PythonCensusStatsEnabled();
bool PythonCensusTracingEnabled();

static constexpr size_t kTraceIdSize = 16;
static constexpr size_t kSpanIdSize = 8;

constexpr uint8_t kVersionId = 0;
constexpr uint8_t kTraceIdField = 0;
constexpr uint8_t kSpanIdField = 1;
constexpr uint8_t kTraceOptionsField = 2;

constexpr int kVersionLen = 1;
constexpr int kTraceIdLen = 16;
constexpr int kSpanIdLen = 8;
constexpr int kTraceOptionsLen = 1;

constexpr int kVersionOfs = 0;
constexpr int kTraceIdOfs = 1;
constexpr int kSpanIdOfs = kTraceIdOfs + 1 + kTraceIdLen;
constexpr int kTraceOptionsOfs = kSpanIdOfs + 1 + kSpanIdLen;

static constexpr size_t kSizeTraceID = 16;
static constexpr size_t kSizeSpanID = 8;
static constexpr size_t kSizeTraceOptions = 1;

constexpr int kGrpcTraceBinHeaderLen =
    kVersionLen + 1 + kTraceIdLen + 1 + kSpanIdLen + 1 + kTraceOptionsLen;

struct Tag {
  std::string key;
  std::string value;
};

struct Label {
  Label() {}
  Label(std::string k, std::string v) : key(k), value(v) {}
  std::string key;
  std::string value;
};

union MeasurementValue {
  double value_double;
  int64_t value_int;
};

struct Measurement {
  MetricsName name;
  MeasurementType type;
  MeasurementValue value;
  bool registered_method;
  bool include_exchange_labels;
};

struct Annotation {
  std::string time_stamp;
  std::string description;
};

struct SpanCensusData {
  std::string name;
  std::string start_time;
  std::string end_time;
  std::string trace_id;
  std::string span_id;
  std::string parent_span_id;
  std::string status;
  std::vector<Label> span_labels;
  std::vector<Annotation> span_annotations;
  int64_t child_span_count;
  bool should_sample;
};

class SpanContext final {
 public:
  SpanContext() : is_valid_(false) {}

  SpanContext(const std::string& trace_id, const std::string& span_id,
              bool should_sample)
      : trace_id_(trace_id),
        span_id_(span_id),
        should_sample_(should_sample),
        is_valid_(true) {}

  std::string TraceId() const { return trace_id_; }

  std::string SpanId() const { return span_id_; }

  bool IsSampled() const { return should_sample_; }

  bool IsValid() const { return is_valid_; }

 private:
  std::string trace_id_;
  std::string span_id_;
  bool should_sample_;
  bool is_valid_;
};

class Span final {
 public:
  explicit Span(const std::string& name, const std::string& parent_span_id,
                absl::Time start_time, const SpanContext& context)
      : name_(name),
        parent_span_id_(parent_span_id),
        start_time_(start_time),
        context_(context) {}

  void End() { end_time_ = absl::Now(); }

  void IncreaseChildSpanCount() { ++child_span_count_; }

  static Span StartSpan(absl::string_view name, const Span* parent);

  static Span StartSpan(absl::string_view name,
                        const SpanContext& parent_context);

  static Span StartSpan(absl::string_view name, absl::string_view trace_id);

  static Span BlankSpan() { return StartSpan("", ""); }

  const SpanContext& Context() const { return context_; }

  void SetStatus(absl::string_view status);

  void AddAttribute(absl::string_view key, absl::string_view value);

  void AddAnnotation(absl::string_view description);

  SpanCensusData ToCensusData() const;

 private:
  static bool ShouldSample(const std::string& trace_id) {
    return ProbabilitySampler::Get().ShouldSample(trace_id);
  }

  std::string name_;
  std::string parent_span_id_;
  absl::Time start_time_;
  absl::Time end_time_;
  std::string status_;
  std::vector<Label> span_labels_;
  std::vector<Annotation> span_annotations_;
  SpanContext context_;
  uint64_t child_span_count_ = 0;
};

class PythonCensusContext {
 public:
  PythonCensusContext() : span_(Span::BlankSpan()), labels_({}) {}

  explicit PythonCensusContext(absl::string_view name)
      : span_(Span::StartSpan(name, nullptr)), labels_({}) {}

  PythonCensusContext(absl::string_view name, absl::string_view trace_id)
      : span_(Span::StartSpan(name, trace_id)), labels_({}) {}

  PythonCensusContext(absl::string_view name, const SpanContext& parent_context)
      : span_(Span::StartSpan(name, parent_context)), labels_({}) {}

  PythonCensusContext(absl::string_view name, const Span* parent,
                      const std::vector<Label>& labels)
      : span_(Span::StartSpan(name, parent)), labels_(labels) {}

  PythonCensusContext(absl::string_view name, const Span* parent)
      : span_(Span::StartSpan(name, parent)), labels_({}) {}

  Span& GetSpan() { return span_; }
  std::vector<Label>& Labels() { return labels_; }
  const SpanContext& GetSpanContext() const { return span_.Context(); }

  void AddSpanAttribute(absl::string_view key, absl::string_view attribute) {
    span_.AddAttribute(key, attribute);
  }

  void AddSpanAnnotation(absl::string_view description) {
    span_.AddAnnotation(description);
  }

  void IncreaseChildSpanCount() { span_.IncreaseChildSpanCount(); }

  void EndSpan() { GetSpan().End(); }

 private:
  grpc_observability::Span span_;
  std::vector<Label> labels_;
};

void GenerateClientContext(absl::string_view method, absl::string_view trace_id,
                           absl::string_view parent_span_id,
                           PythonCensusContext* context);

void GenerateServerContext(absl::string_view header, absl::string_view method,
                           PythonCensusContext* context);

inline std::string GetMethod(const char* method) {
  if (std::string(method).empty()) {
    return "";
  }

  return std::string(absl::StripPrefix(method, "/"));
}

inline std::string GetTarget(const char* target) { return std::string(target); }

void ToGrpcTraceBinHeader(const PythonCensusContext& ctx, uint8_t* out);

SpanContext FromGrpcTraceBinHeader(absl::string_view header);

size_t TraceContextSerialize(const PythonCensusContext& context,
                             char* tracing_buf, size_t tracing_buf_size);

size_t StatsContextSerialize(size_t max_tags_len, grpc_slice* tags);

size_t ServerStatsDeserialize(const char* buf, size_t buf_size,
                              uint64_t* server_elapsed_time);

size_t ServerStatsSerialize(uint64_t server_elapsed_time, char* buf,
                            size_t buf_size);

uint64_t GetIncomingDataSize(const grpc_call_final_info* final_info);

uint64_t GetOutgoingDataSize(const grpc_call_final_info* final_info);

}

#endif
