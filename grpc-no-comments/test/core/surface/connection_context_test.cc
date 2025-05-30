
// Copyright 2024 gRPC authors.

#include "src/core/lib/surface/connection_context.h"

#include "gtest/gtest.h"
#include "src/core/util/orphanable.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace {

class Foo {
 public:
  explicit Foo(double value) : value_(value) {}
  double value() const { return value_; }

 private:
  double value_;
};

class Bar {
 public:
  explicit Bar(int value) : value_(value) {}
  int value() const { return value_; }

 private:
  int value_;
};

}

template <>
struct ConnectionContextProperty<Foo> {};

template <>
struct ConnectionContextProperty<Bar> {};

TEST(ConnectionAuthContextTest, SimpleStaticPropertyAdditionContext) {
  OrphanablePtr<ConnectionContext> map = ConnectionContext::Create();
  EXPECT_TRUE(map->EmplaceIfUnset<Foo>(3.0));
  EXPECT_EQ(map->Get<Foo>()->value(), 3.0);
  EXPECT_FALSE(map->EmplaceIfUnset<Foo>(1.0));
  EXPECT_EQ(map->Get<Foo>()->value(), 3.0);
  map->Update<Foo>(2.0);
  EXPECT_EQ(map->Get<Foo>()->value(), 2.0);

  EXPECT_TRUE(map->EmplaceIfUnset<Bar>(1));
  EXPECT_EQ(map->Get<Bar>()->value(), 1);
  EXPECT_FALSE(map->EmplaceIfUnset<Bar>(2));
  EXPECT_EQ(map->Get<Bar>()->value(), 1);
  map->Update<Bar>(1234);
  EXPECT_EQ(map->Get<Bar>()->value(), 1234);
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
