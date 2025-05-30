// Copyright 2024 gRPC authors.

#include "src/core/util/down_cast.h"

#include "gtest/gtest.h"

namespace grpc_core {
namespace {

class Base {
 public:
  virtual ~Base() = default;
};

class Derived : public Base {
 public:
  int i = 3;
};

TEST(DownCastTest, DownCast) {
  Derived d;
  Base* b = &d;
  EXPECT_EQ(DownCast<Derived*>(b)->i, 3);
  EXPECT_EQ(DownCast<Derived&>(*b).i, 3);
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
