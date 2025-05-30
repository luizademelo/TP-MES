// Copyright 2023 gRPC authors.

#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/crash.h"

namespace grpc_core {
namespace {

class TestServerCallTracerFactory : public ServerCallTracerFactory {
 public:
  ServerCallTracer* CreateNewServerCallTracer(
      Arena* , const ChannelArgs& ) override {
    Crash("Not implemented");
  }
};

TEST(ServerCallTracerFactoryTest, GlobalRegistration) {
  TestServerCallTracerFactory factory;
  ServerCallTracerFactory::RegisterGlobal(&factory);
  EXPECT_EQ(ServerCallTracerFactory::Get(ChannelArgs()), &factory);
}

TEST(ServerCallTracerFactoryTest, UsingChannelArgs) {
  TestServerCallTracerFactory factory;
  ChannelArgs args = ChannelArgs().SetObject(&factory);
  EXPECT_EQ(ServerCallTracerFactory::Get(args), &factory);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
