
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_LOAD_REPORTING_REGISTERED_OPENCENSUS_OBJECTS_H
#define GRPC_SRC_CORE_EXT_FILTERS_LOAD_REPORTING_REGISTERED_OPENCENSUS_OBJECTS_H

#include <grpc/support/port_platform.h>

#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "src/cpp/server/load_reporter/constants.h"

namespace grpc {
namespace load_reporter {

inline ::opencensus::stats::MeasureInt64 MeasureStartCount() {
  static const ::opencensus::stats::MeasureInt64 measure =
      ::opencensus::stats::MeasureInt64::Register(
          kMeasureStartCount, kMeasureStartCount, kMeasureStartCount);
  return measure;
}

inline ::opencensus::stats::MeasureInt64 MeasureEndCount() {
  static const ::opencensus::stats::MeasureInt64 measure =
      ::opencensus::stats::MeasureInt64::Register(
          kMeasureEndCount, kMeasureEndCount, kMeasureEndCount);
  return measure;
}

inline ::opencensus::stats::MeasureInt64 MeasureEndBytesSent() {
  static const ::opencensus::stats::MeasureInt64 measure =
      ::opencensus::stats::MeasureInt64::Register(
          kMeasureEndBytesSent, kMeasureEndBytesSent, kMeasureEndBytesSent);
  return measure;
}

inline ::opencensus::stats::MeasureInt64 MeasureEndBytesReceived() {
  static const ::opencensus::stats::MeasureInt64 measure =
      ::opencensus::stats::MeasureInt64::Register(kMeasureEndBytesReceived,
                                                  kMeasureEndBytesReceived,
                                                  kMeasureEndBytesReceived);
  return measure;
}

inline ::opencensus::stats::MeasureInt64 MeasureEndLatencyMs() {
  static const ::opencensus::stats::MeasureInt64 measure =
      ::opencensus::stats::MeasureInt64::Register(
          kMeasureEndLatencyMs, kMeasureEndLatencyMs, kMeasureEndLatencyMs);
  return measure;
}

inline ::opencensus::stats::MeasureDouble MeasureOtherCallMetric() {
  static const ::opencensus::stats::MeasureDouble measure =
      ::opencensus::stats::MeasureDouble::Register(kMeasureOtherCallMetric,
                                                   kMeasureOtherCallMetric,
                                                   kMeasureOtherCallMetric);
  return measure;
}

inline ::opencensus::tags::TagKey TagKeyToken() {
  static const ::opencensus::tags::TagKey token =
      opencensus::tags::TagKey::Register(kTagKeyToken);
  return token;
}

inline ::opencensus::tags::TagKey TagKeyHost() {
  static const ::opencensus::tags::TagKey token =
      opencensus::tags::TagKey::Register(kTagKeyHost);
  return token;
}

inline ::opencensus::tags::TagKey TagKeyUserId() {
  static const ::opencensus::tags::TagKey token =
      opencensus::tags::TagKey::Register(kTagKeyUserId);
  return token;
}

inline ::opencensus::tags::TagKey TagKeyStatus() {
  static const ::opencensus::tags::TagKey token =
      opencensus::tags::TagKey::Register(kTagKeyStatus);
  return token;
}

inline ::opencensus::tags::TagKey TagKeyMetricName() {
  static const ::opencensus::tags::TagKey token =
      opencensus::tags::TagKey::Register(kTagKeyMetricName);
  return token;
}

}
}

#endif
