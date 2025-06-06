// Copyright 2023 gRPC authors.

#include "src/core/lib/event_engine/query_extensions.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/util/crash.h"

namespace grpc_event_engine {
namespace experimental {
namespace {

template <int i>
class TestExtension {
 public:
  TestExtension() = default;
  ~TestExtension() = default;

  static std::string EndpointExtensionName() {
    return "grpc.test.test_extension" + std::to_string(i);
  }

  int GetValue() const { return val_; }

 private:
  int val_ = i;
};

class ExtendedTestEndpoint
    : public ExtendedType<EventEngine::Endpoint, TestExtension<0>,
                          TestExtension<1>, TestExtension<2>> {
 public:
  ExtendedTestEndpoint() = default;
  ~ExtendedTestEndpoint() override = default;
  bool Read(absl::AnyInvocable<void(absl::Status)> ,
            SliceBuffer* , ReadArgs ) override {
    grpc_core::Crash("Not implemented");
  };
  bool Write(absl::AnyInvocable<void(absl::Status)> ,
             SliceBuffer* , WriteArgs ) override {
    grpc_core::Crash("Not implemented");
  }

  const EventEngine::ResolvedAddress& GetPeerAddress() const override {
    grpc_core::Crash("Not implemented");
  }
  const EventEngine::ResolvedAddress& GetLocalAddress() const override {
    grpc_core::Crash("Not implemented");
  };
  std::vector<size_t> AllWriteMetrics() override { return {}; }
  std::optional<absl::string_view> GetMetricName(size_t) override {
    return std::nullopt;
  }
  std::optional<size_t> GetMetricKey(absl::string_view) override {
    return std::nullopt;
  }
};

TEST(QueryExtensionsTest, EndpointSupportsMultipleExtensions) {
  ExtendedTestEndpoint endpoint;
  TestExtension<0>* extension_0 = QueryExtension<TestExtension<0>>(&endpoint);
  TestExtension<1>* extension_1 = QueryExtension<TestExtension<1>>(&endpoint);
  TestExtension<2>* extension_2 = QueryExtension<TestExtension<2>>(&endpoint);

  EXPECT_NE(extension_0, nullptr);
  EXPECT_NE(extension_1, nullptr);
  EXPECT_NE(extension_2, nullptr);

  EXPECT_EQ(extension_0->GetValue(), 0);
  EXPECT_EQ(extension_1->GetValue(), 1);
  EXPECT_EQ(extension_2->GetValue(), 2);
}
}

}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
