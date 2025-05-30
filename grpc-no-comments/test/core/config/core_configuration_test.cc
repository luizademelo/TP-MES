// Copyright 2021 gRPC authors.

#include "src/core/config/core_configuration.h"

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

#include "gtest/gtest.h"

namespace grpc_core {

namespace {
using ConfigBuilderFunction = std::function<void(CoreConfiguration::Builder*)>;
ConfigBuilderFunction g_mock_builder;
}

void BuildCoreConfiguration(CoreConfiguration::Builder* builder) {
  g_mock_builder(builder);
}

namespace {

void InitConfigWithBuilder(ConfigBuilderFunction fn) {
  CoreConfiguration::Reset();
  g_mock_builder = fn;
  CoreConfiguration::Get();
  g_mock_builder = nullptr;
}

TEST(ConfigTest, NoopConfig) {
  InitConfigWithBuilder([](CoreConfiguration::Builder*) {});
  CoreConfiguration::Get();
}

TEST(ConfigTest, ThreadedInit) {
  CoreConfiguration::Reset();
  g_mock_builder = [](CoreConfiguration::Builder*) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
  std::vector<std::thread> threads;
  threads.reserve(10);
  for (int i = 0; i < 10; i++) {
    threads.push_back(std::thread([]() { CoreConfiguration::Get(); }));
  }
  for (auto& t : threads) {
    t.join();
  }
  g_mock_builder = nullptr;
  CoreConfiguration::Get();
}
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
