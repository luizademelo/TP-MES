
// Copyright 2024 gRPC authors.

#ifndef GRPCPP_EXAMPLES_CPP_OTEL_CODELAB_UTIL_H
#define GRPCPP_EXAMPLES_CPP_OTEL_CODELAB_UTIL_H

#include <string>

#include "opentelemetry/sdk/metrics/meter_provider.h"

void AddLatencyView(opentelemetry::sdk::metrics::MeterProvider* provider,
                    const std::string& name, const std::string& unit);

#endif
