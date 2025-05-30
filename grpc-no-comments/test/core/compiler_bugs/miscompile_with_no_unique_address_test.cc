// Copyright 2021 gRPC authors.

#include <grpc/support/port_platform.h>

#include <memory>

#include "gtest/gtest.h"

template <int kInit>
class A {
 public:
  ~A() { EXPECT_EQ(a_, kInit); }
  int a_ = kInit;
};
template <class T, int kInit>
class P : A<kInit> {
 public:
  explicit P(T b) : b_(b) {}

  GPR_NO_UNIQUE_ADDRESS T b_;
};

template <int kInit, class T>
void c(T a) {
  P<T, kInit> _(a);
}

TEST(Miscompile, Zero) {
  c<0>([] {});
}

TEST(Miscompile, One) {
  c<1>([] {});
}

TEST(Miscompile, MinusOne) {
  c<-1>([] {});
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
