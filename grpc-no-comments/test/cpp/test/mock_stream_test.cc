
// Copyright 2020 the gRPC authors.

#include <grpcpp/test/mock_stream.h>

#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

TEST(MockStreamTest, Basic) {
  auto cr = std::make_unique<grpc::testing::MockClientReader<EchoResponse>>();
  ASSERT_NE(cr, nullptr);

  auto cw = std::make_unique<grpc::testing::MockClientWriter<EchoResponse>>();
  ASSERT_NE(cw, nullptr);

  auto crw = std::make_unique<
      grpc::testing::MockClientReaderWriter<EchoResponse, EchoResponse>>();
  ASSERT_NE(crw, nullptr);

  auto carr = std::make_unique<
      grpc::testing::MockClientAsyncResponseReader<EchoResponse>>();
  ASSERT_NE(carr, nullptr);

  auto car =
      std::make_unique<grpc::testing::MockClientAsyncReader<EchoResponse>>();
  ASSERT_NE(car, nullptr);

  auto caw =
      std::make_unique<grpc::testing::MockClientAsyncWriter<EchoResponse>>();
  ASSERT_NE(caw, nullptr);

  auto carw = std::make_unique<
      grpc::testing::MockClientAsyncReaderWriter<EchoRequest, EchoResponse>>();
  ASSERT_NE(carw, nullptr);

  auto sr = std::make_unique<grpc::testing::MockServerReader<EchoRequest>>();
  ASSERT_NE(sr, nullptr);

  auto sw = std::make_unique<grpc::testing::MockServerWriter<EchoResponse>>();
  ASSERT_NE(sw, nullptr);

  auto srw = std::make_unique<
      grpc::testing::MockServerReaderWriter<EchoResponse, EchoRequest>>();
  ASSERT_NE(srw, nullptr);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
