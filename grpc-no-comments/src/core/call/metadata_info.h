// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_METADATA_INFO_H
#define GRPC_SRC_CORE_CALL_METADATA_INFO_H

#include <grpc/support/port_platform.h>

#include "src/core/call/metadata_batch.h"
#include "src/core/ext/transport/chttp2/transport/hpack_constants.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/telemetry/call_tracer.h"

namespace grpc_core {

#define DEFAULT_MAX_HEADER_LIST_SIZE (16 * 1024)
#define DEFAULT_MAX_HEADER_LIST_SIZE_SOFT_LIMIT (8 * 1024)

inline uint32_t GetSoftLimitFromChannelArgs(const ChannelArgs& args) {
  const int soft_limit = args.GetInt(GRPC_ARG_MAX_METADATA_SIZE).value_or(-1);
  if (soft_limit < 0) {

    return std::max(
        DEFAULT_MAX_HEADER_LIST_SIZE_SOFT_LIMIT,
        static_cast<int>(
            0.8 *
            args.GetInt(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE).value_or(-1)));
  } else {
    return soft_limit;
  }
}

inline uint32_t GetHardLimitFromChannelArgs(const ChannelArgs& args) {
  int hard_limit =
      args.GetInt(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE).value_or(-1);
  if (hard_limit >= 0) {
    return hard_limit;
  } else {

    const int soft_limit = args.GetInt(GRPC_ARG_MAX_METADATA_SIZE).value_or(-1);
    const int value = (soft_limit >= 0 && soft_limit < (INT_MAX / 1.25))
                          ? static_cast<int>(soft_limit * 1.25)
                          : soft_limit;
    return std::max(value, DEFAULT_MAX_HEADER_LIST_SIZE);
  }
}

class MetadataSizesAnnotation
    : public CallTracerAnnotationInterface::Annotation {
 public:
  MetadataSizesAnnotation(grpc_metadata_batch* metadata_buffer,
                          uint64_t soft_limit, uint64_t hard_limit)
      : CallTracerAnnotationInterface::Annotation(
            CallTracerAnnotationInterface::AnnotationType::kMetadataSizes),
        metadata_buffer_(metadata_buffer),
        soft_limit_(soft_limit),
        hard_limit_(hard_limit) {}

  std::string ToString() const override;

 private:
  class MetadataSizeEncoder;
  grpc_metadata_batch* metadata_buffer_;
  uint64_t soft_limit_;
  uint64_t hard_limit_;
};

}

#endif