
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_CONSTANTS_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_CONSTANTS_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

namespace grpc {
namespace load_reporter {

constexpr uint32_t kVersion = 15853;

constexpr uint32_t kFeedbackSampleWindowSeconds = 10;
constexpr uint32_t kFetchAndSampleIntervalSeconds = 1;

constexpr size_t kLbIdLength = 8;
constexpr size_t kIpv4AddressLength = 8;
constexpr size_t kIpv6AddressLength = 32;

constexpr char kInvalidLbId[] = "<INVALID_LBID_238dsb234890rb>";

constexpr char kCallStatusOk[] = "OK";
constexpr char kCallStatusServerError[] = "5XX";
constexpr char kCallStatusClientError[] = "4XX";

constexpr char kTagKeyToken[] = "token";
constexpr char kTagKeyHost[] = "host";
constexpr char kTagKeyUserId[] = "user_id";
constexpr char kTagKeyStatus[] = "status";
constexpr char kTagKeyMetricName[] = "metric_name";

constexpr char kMeasureStartCount[] = "grpc.io/lb/start_count";
constexpr char kMeasureEndCount[] = "grpc.io/lb/end_count";
constexpr char kMeasureEndBytesSent[] = "grpc.io/lb/bytes_sent";
constexpr char kMeasureEndBytesReceived[] = "grpc.io/lb/bytes_received";
constexpr char kMeasureEndLatencyMs[] = "grpc.io/lb/latency_ms";
constexpr char kMeasureOtherCallMetric[] = "grpc.io/lb/other_call_metric";

constexpr char kViewStartCount[] = "grpc.io/lb_view/start_count";
constexpr char kViewEndCount[] = "grpc.io/lb_view/end_count";
constexpr char kViewEndBytesSent[] = "grpc.io/lb_view/bytes_sent";
constexpr char kViewEndBytesReceived[] = "grpc.io/lb_view/bytes_received";
constexpr char kViewEndLatencyMs[] = "grpc.io/lb_view/latency_ms";
constexpr char kViewOtherCallMetricCount[] =
    "grpc.io/lb_view/other_call_metric_count";
constexpr char kViewOtherCallMetricValue[] =
    "grpc.io/lb_view/other_call_metric_value";

}
}

#endif
