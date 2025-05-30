// Copyright 2023 The gRPC Authors

#include "test/core/test_util/fuzzing_channel_args.h"

#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "test/core/test_util/fuzzing_channel_args.pb.h"

namespace grpc_core {
namespace testing {

namespace {
using grpc::testing::FuzzingChannelArg;
}

ChannelArgs CreateChannelArgsFromFuzzingConfiguration(
    const grpc::testing::FuzzingChannelArgs& fuzzing_channel_args,
    const FuzzingEnvironment& fuzzing_environment) {
  ChannelArgs channel_args;
  for (const auto& fuzz_arg : fuzzing_channel_args.args()) {
    switch (fuzz_arg.value_case()) {
      case FuzzingChannelArg::kStr:
        channel_args = channel_args.Set(fuzz_arg.key(), fuzz_arg.str());
        break;
      case FuzzingChannelArg::kI:
        channel_args = channel_args.Set(fuzz_arg.key(), fuzz_arg.i());
        break;
      case FuzzingChannelArg::kResourceQuota:
        channel_args =
            channel_args.SetObject(fuzzing_environment.resource_quota);
        break;
      default:

        break;
    }
  }
  return channel_args;
}

}
}
