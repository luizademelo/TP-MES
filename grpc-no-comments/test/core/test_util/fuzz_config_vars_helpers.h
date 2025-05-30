// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_FUZZ_CONFIG_VARS_HELPERS_H
#define GRPC_TEST_CORE_TEST_UTIL_FUZZ_CONFIG_VARS_HELPERS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "test/core/test_util/fuzz_config_vars.pb.h"

namespace grpc_core {

std::vector<std::string> ExperimentConfigChoices();
std::vector<std::string> TracerConfigChoices();

inline auto AnyConfigVars() {
  auto optional_string = [](auto x) {
    return ::fuzztest::OneOf(::fuzztest::Just(std::string()), std::move(x));
  };
  return ::fuzztest::Arbitrary<grpc::testing::FuzzConfigVars>()
      .WithStringField("experiments",
                       optional_string(::fuzztest::Map(
                           [](std::vector<std::string> experiments) {
                             return absl::StrJoin(experiments, ",");
                           },
                           ::fuzztest::VectorOf(::fuzztest::ElementOf(
                               ExperimentConfigChoices())))))
      .WithStringField(
          "verbosity",
          optional_string(::fuzztest::ElementOf(
              std::vector<std::string>{"info", "debug", "error", "none"})))
      .WithStringField("trace", optional_string(::fuzztest::Map(
                                    [](std::vector<std::string> traces) {
                                      return absl::StrJoin(traces, ",");
                                    },
                                    ::fuzztest::VectorOf(::fuzztest::ElementOf(
                                        TracerConfigChoices())))))
      .WithStringField("dns_resolver",
                       optional_string(::fuzztest::ElementOf(
                           std::vector<std::string>{"ares", "native"})));
}

}

#endif
