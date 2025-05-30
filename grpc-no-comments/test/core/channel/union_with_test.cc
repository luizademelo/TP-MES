// Copyright 2023 gRPC authors.

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

using IntOrString = std::variant<int, std::string>;
using VectorOfArgs = std::vector<std::pair<std::string, IntOrString>>;

ChannelArgs ChannelArgsFromVector(VectorOfArgs va) {
  ChannelArgs result;
  for (auto& [key, value] : va) {
    if (std::holds_alternative<int>(value)) {
      result = result.Set(key, std::get<int>(value));
    } else {
      result = result.Set(key, std::get<std::string>(value));
    }
  }
  return result;
}

void UnionWithIsCorrect(VectorOfArgs va, VectorOfArgs vb) {
  auto a = ChannelArgsFromVector(std::move(va));
  auto b = ChannelArgsFromVector(std::move(vb));
  EXPECT_EQ(a.UnionWith(b), a.FuzzingReferenceUnionWith(b));
}
FUZZ_TEST(MyTestSuite, UnionWithIsCorrect);

}
