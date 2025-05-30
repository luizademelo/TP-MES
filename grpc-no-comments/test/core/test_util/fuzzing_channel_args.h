// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_FUZZING_CHANNEL_ARGS_H
#define GRPC_TEST_CORE_TEST_UTIL_FUZZING_CHANNEL_ARGS_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/test_util/fuzzing_channel_args.pb.h"

namespace grpc_core {
namespace testing {

struct FuzzingEnvironment {

  RefCountedPtr<ResourceQuota> resource_quota =
      MakeResourceQuota("fuzzing_quota");
};

ChannelArgs CreateChannelArgsFromFuzzingConfiguration(
    const grpc::testing::FuzzingChannelArgs& fuzzing_channel_args,
    const FuzzingEnvironment& fuzzing_environment);

}
}

#endif
