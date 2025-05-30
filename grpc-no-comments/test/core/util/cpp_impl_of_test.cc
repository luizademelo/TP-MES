// Copyright 2021 gRPC authors.

#include "src/core/util/cpp_impl_of.h"

#include <memory>

#include "gtest/gtest.h"

typedef struct grpc_foo grpc_foo;

namespace grpc_core {
namespace {
class Foo : public CppImplOf<Foo, grpc_foo> {};
}

TEST(CppImplOfTest, CreateDestroy) { delete Foo::FromC((new Foo())->c_ptr()); }

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
