// Copyright 2023 gRPC authors.

#include "src/core/util/uuid_v4.h"

#include "gtest/gtest.h"

namespace grpc_core {

namespace {

TEST(UUIDv4Test, Basic) {
  EXPECT_EQ(GenerateUUIDv4(0, 0), "00000000-0000-4000-8000-000000000000");
  EXPECT_EQ(GenerateUUIDv4(0x0123456789abcdef, 0x0123456789abcdef),
            "01234567-89ab-4def-8123-456789abcdef");
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
