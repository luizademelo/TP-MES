
// Copyright 2023 gRPC authors.

#include "test/cpp/ext/filters/census/library.h"

namespace grpc {
namespace testing {

const ::opencensus::tags::TagKey TEST_TAG_KEY =
    ::opencensus::tags::TagKey::Register("my_key");
const char* TEST_TAG_VALUE = "my_value";
const char* kExpectedTraceIdKey = "expected_trace_id";

ExportedTracesRecorder* traces_recorder_ = new ExportedTracesRecorder();

}
}
