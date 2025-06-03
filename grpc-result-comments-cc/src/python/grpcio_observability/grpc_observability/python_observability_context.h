Here's the commented version of the code:

```c++
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

// Anonymous namespace for internal implementation details
namespace {
// Global flags controlling whether Census stats and tracing are enabled
std::atomic<bool> g_python_census_stats_enabled(false);
std::atomic<bool> g_python_census_tracing_enabled(false);
}

// Function declarations for enabling/disabling Census features
void EnablePythonCensusStats(bool enable);
void EnablePythonCensusTracing(bool enable);

// Function declarations for checking Census feature status
bool PythonCensusStatsEnabled();
bool PythonCensusTracingEnabled();

// Constants for trace and span ID sizes
static constexpr size_t kTraceIdSize = 16;  // Size of trace ID in bytes
static constexpr size_t kSpanIdSize = 8;    // Size of span ID in bytes

// Field identifiers for trace context
constexpr uint8_t kVersionId = 0;         // Version field identifier
constexpr uint8_t kTraceIdField = 0;      // Trace ID field identifier
constexpr uint8_t kSpanIdField = 1;       // Span ID field identifier
constexpr uint8_t kTraceOptionsField = 2; // Trace options field identifier

// Length constants for trace context fields
constexpr int kVersionLen = 1;      // Length of version field
constexpr int kTraceIdLen = 16;     // Length of trace ID field
constexpr int kSpanIdLen = 8;       // Length of span ID field
constexpr int kTraceOptionsLen = 1; // Length of trace options field

// Offset constants for trace context fields in binary format
constexpr int kVersionOfs = 0;                         // Version offset
constexpr int kTraceIdOfs = 1;                         // Trace ID offset
constexpr int kSpanIdOfs = kTraceIdOfs + 1 + kTraceIdLen; // Span ID offset
constexpr int kTraceOptionsOfs = kSpanIdOfs + 1 + kSpanIdLen; // Trace options offset

// Size constants for trace components
static constexpr size_t kSizeTraceID = 16;     // Size of trace ID
static constexpr size_t kSizeSpanID = 8;       // Size of span ID
static constexpr size_t kSizeTraceOptions = 1; // Size of trace options

// Total length of gRPC trace binary header
constexpr int kGrpcTraceBinHeaderLen =
    kVersionLen + 1 + kTraceIdLen + 1 + kSpanIdLen + 1 + kTraceOptionsLen;

// Structure representing a key-value tag
struct Tag {
  std::string key;
  std::string value;
};

// Structure representing a key-value label
struct Label {
  Label() {}
  Label(std::string k, std::string v) : key(k), value(v) {}
  std::string key;
  std::string value;
};

// Union for storing measurement values (either double or int64)
union MeasurementValue {
  double value_double;
  int64_t value_int;
};

// Structure representing a measurement with metadata
struct Measurement {
  MetricsName name;                  // Name of the metric
  MeasurementType type;              // Type of measurement
  MeasurementValue value;            // Measurement value
  bool registered_method;           // Whether method is registered
  bool include_exchange_labels;      // Whether to include exchange labels
};

// Structure representing an annotation with timestamp
struct Annotation {
  std::string time_stamp;           // Timestamp of the annotation
  std::string description;          // Description of the annotation
};

// Structure containing all Census data for a span
struct SpanCensusData {
  std::string name;                 // Span name
  std::string start_time;           // Span start time
  std::string end_time;             // Span end time
  std::string trace_id;             // Trace ID
  std::string span_id;              // Span ID
  std::string parent_span_id;       // Parent span ID
  std::string status;               // Span status
  std::vector<Label> span_labels;   // Span labels
  std::vector<Annotation> span_annotations; // Span annotations
  int64_t child_span_count;         // Number of child spans
  bool should_sample;               // Whether span should be sampled
};

// Class representing a span context
class SpanContext final {
 public:
  SpanContext() : is_valid_(false) {}  // Default constructor creates invalid context

  // Constructor with trace ID, span ID, and sampling decision
  SpanContext(const std::string& trace_id, const std::string& span_id,
              bool should_sample)
      : trace_id_(trace_id),
        span_id_(span_id),
        should_sample_(should_sample),
        is_valid_(true) {}

  // Getters for context properties
  std::string TraceId() const { return trace_id_; }
  std::string SpanId() const { return span_id_; }
  bool IsSampled() const { return should_sample_; }
  bool IsValid() const { return is_valid_; }

 private:
  std::string trace_id_;    // Unique trace identifier
  std::string span_id_;     // Unique span identifier
  bool should_sample_;      // Whether this span should be sampled
  bool is_valid_;           // Whether this context is valid
};

// Class representing a span in distributed tracing
class Span final {
 public:
  // Constructor with name, parent span ID, start time, and context
  explicit Span(const std::string& name, const std::string& parent_span_id,
                absl::Time start_time, const SpanContext& context)
      : name_(name),
        parent_span_id_(parent_span_id),
        start_time_(start_time),
        context_(context) {}

  // Marks the end of the span with current time
  void End() { end_time_ = absl::Now(); }

  // Increments child span count
  void IncreaseChildSpanCount() { ++child_span_count_; }

  // Factory methods for creating spans
  static Span StartSpan(absl::string_view name, const Span* parent);
  static Span StartSpan(absl::string_view name,
                        const SpanContext& parent_context);
  static Span StartSpan(absl::string_view name, absl::string_view trace_id);
  static Span BlankSpan() { return StartSpan("", ""); }

  // Getter for span context
  const SpanContext& Context() const { return context_; }

  // Methods for modifying span state
  void SetStatus(absl::string_view status);
  void AddAttribute(absl::string_view key, absl::string_view value);
  void AddAnnotation(absl::string_view description);

  // Converts span data to Census format
  SpanCensusData ToCensusData() const;

 private:
  // Determines if a trace should be sampled based on trace ID
  static bool ShouldSample(const std::string& trace_id) {
    return ProbabilitySampler::Get().ShouldSample(trace_id);
  }

  // Span properties
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

// Class representing a Python Census context containing span and labels
class PythonCensusContext {
 public:
  PythonCensusContext() : span_(Span::BlankSpan()), labels_({}) {}  // Default constructor

  // Constructors with various initialization options
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

  // Getters for context components
  Span& GetSpan() { return span_; }
  std::vector<Label>& Labels() { return labels_; }
  const SpanContext& GetSpanContext() const { return span_.Context(); }

  // Methods for modifying context
  void AddSpanAttribute(absl::string_view key, absl::string_view attribute) {
    span_.AddAttribute(key, attribute);
  }
  void AddSpanAnnotation(absl::string_view description) {
    span_.AddAnnotation(description);
  }
  void IncreaseChildSpanCount() { span_.IncreaseChildSpanCount(); }
  void EndSpan() { GetSpan().End(); }

 private:
  grpc_observability::Span span_;  // The span associated with this context
  std::vector<Label> labels_;      // Labels associated with this context
};

// Functions for generating client and server contexts
void GenerateClientContext(absl::string_view method, absl::string_view trace_id,
                           absl::string_view parent_span_id,
                           PythonCensusContext* context);
void GenerateServerContext(absl::string_view header, absl::string_view method,
                           PythonCensusContext* context);

// Helper functions for processing method and target strings
inline std::string GetMethod(const char* method) {
  if (std::string(method).empty()) {
    return "";
  }
  return std::string(absl::StripPrefix(method, "/"));
}

inline std::string GetTarget(const char* target) { return std::string(target); }

// Functions for trace context serialization/deserialization
void ToGrpcTraceBinHeader(const PythonCensusContext& ctx, uint8_t* out);
SpanContext FromGrpcTraceBinHeader(absl::string_view header);

// Functions for context serialization
size_t TraceContextSerialize(const PythonCensusContext& context,
                             char* tracing_buf, size_t tracing_buf_size);
size_t StatsContextSerialize(size_t max_tags_len, grpc_slice* tags);

// Functions for server stats serialization/deserialization
size_t ServerStatsDeserialize(const char* buf, size_t buf_size,
                              uint64_t* server_elapsed_time);
size_t ServerStatsSerialize(uint64_t server_elapsed_time, char* buf,
                            size_t buf_size);

// Functions for getting data size metrics
uint64_t GetIncomingDataSize(const grpc_call_final_info* final_info);
uint64_t GetOutgoingDataSize(const grpc_call_final_info* final_info);

}

#endif
```