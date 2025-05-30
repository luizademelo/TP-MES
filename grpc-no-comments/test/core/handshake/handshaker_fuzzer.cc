// Copyright 2025 gRPC authors.

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "test/core/event_engine/event_engine_test_utils.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"
#include "test/core/handshake/test_handshake.h"
#include "test/core/test_util/fuzzing_channel_args.h"
#include "test/core/test_util/fuzzing_channel_args.pb.h"

namespace grpc_core {
namespace {

auto BaseChannelArgs() { return ChannelArgs(); }

auto AnyChannelArgs() {
  return ::fuzztest::Map(
      [](const grpc::testing::FuzzingChannelArgs& args) {
        testing::FuzzingEnvironment env;
        return testing::CreateChannelArgsFromFuzzingConfiguration(args, env);
      },
      ::fuzztest::Arbitrary<grpc::testing::FuzzingChannelArgs>());
}

void BasicHandshakeSucceeds(const fuzzing_event_engine::Actions& actions) {
  if (!grpc_event_engine::experimental::IsSaneTimerEnvironment()) {
    GTEST_SKIP() << "Needs most EventEngine experiments enabled";
  }
  CHECK_OK(TestHandshake(BaseChannelArgs(), BaseChannelArgs(), actions));
}
FUZZ_TEST(HandshakerFuzzer, BasicHandshakeSucceeds);

TEST(HandshakerFuzzer, BasicHandshakeSucceedsRegression1) {
  BasicHandshakeSucceeds(fuzzing_event_engine::Actions());
}

void RandomChannelArgsDontCauseCrashes(
    const ChannelArgs& client_args, const ChannelArgs& server_args,
    const fuzzing_event_engine::Actions& actions) {
  if (!grpc_event_engine::experimental::IsSaneTimerEnvironment()) {
    GTEST_SKIP() << "Needs most EventEngine experiments enabled";
  }
  std::ignore = TestHandshake(client_args, server_args, actions);
}
FUZZ_TEST(HandshakerFuzzer, RandomChannelArgsDontCauseCrashes)
    .WithDomains(AnyChannelArgs(), AnyChannelArgs(),
                 ::fuzztest::Arbitrary<fuzzing_event_engine::Actions>());

}
}
