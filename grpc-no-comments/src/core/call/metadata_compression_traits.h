// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_METADATA_COMPRESSION_TRAITS_H
#define GRPC_SRC_CORE_CALL_METADATA_COMPRESSION_TRAITS_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

namespace grpc_core {

struct NoCompressionCompressor {};

struct StableValueCompressor {};

template <typename T, T value>
struct KnownValueCompressor {};

struct FrequentKeyWithNoValueCompressionCompressor {};

struct SmallSetOfValuesCompressor {};

template <size_t N>
struct SmallIntegralValuesCompressor {};

struct TimeoutCompressor {};

struct HttpSchemeCompressor {};
struct HttpMethodCompressor {};
struct HttpStatusCompressor {};

}

#endif
