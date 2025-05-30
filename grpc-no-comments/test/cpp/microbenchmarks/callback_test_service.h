
// Copyright 2019 gRPC authors.

#ifndef GRPC_TEST_CPP_MICROBENCHMARKS_CALLBACK_TEST_SERVICE_H
#define GRPC_TEST_CPP_MICROBENCHMARKS_CALLBACK_TEST_SERVICE_H

#include <benchmark/benchmark.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <sstream>

#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/cpp/util/string_ref_helper.h"

namespace grpc {
namespace testing {

const char* const kServerMessageSize = "server_message_size";

class CallbackStreamingTestService : public EchoTestService::CallbackService {
 public:
  CallbackStreamingTestService() {}

  ServerUnaryReactor* Echo(CallbackServerContext* context,
                           const EchoRequest* request,
                           EchoResponse* response) override;

  ServerBidiReactor<EchoRequest, EchoResponse>* BidiStream(
      CallbackServerContext* context) override;
};
}
}
#endif
