
// Copyright 2018 gRPC authors.

#include "test/cpp/end2end/interceptors_util.h"

#include "absl/log/check.h"
#include "absl/memory/memory.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {

std::atomic<int> PhonyInterceptor::num_times_run_;
std::atomic<int> PhonyInterceptor::num_times_run_reverse_;
std::atomic<int> PhonyInterceptor::num_times_cancel_;

void MakeCall(const std::shared_ptr<Channel>& channel,
              const StubOptions& options) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel, options);
  ClientContext ctx;
  EchoRequest req;
  req.mutable_param()->set_echo_metadata(true);
  ctx.AddMetadata("testkey", "testvalue");
  req.set_message("Hello");
  EchoResponse resp;
  Status s = stub->Echo(&ctx, req, &resp);
  EXPECT_EQ(s.ok(), true);
  EXPECT_EQ(resp.message(), "Hello");
}

void MakeClientStreamingCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  ClientContext ctx;
  EchoRequest req;
  req.mutable_param()->set_echo_metadata(true);
  ctx.AddMetadata("testkey", "testvalue");
  req.set_message("Hello");
  EchoResponse resp;
  string expected_resp;
  auto writer = stub->RequestStream(&ctx, &resp);
  for (int i = 0; i < kNumStreamingMessages; i++) {
    writer->Write(req);
    expected_resp += "Hello";
  }
  writer->WritesDone();
  Status s = writer->Finish();
  EXPECT_EQ(s.ok(), true);
  EXPECT_EQ(resp.message(), expected_resp);
}

void MakeServerStreamingCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  ClientContext ctx;
  EchoRequest req;
  req.mutable_param()->set_echo_metadata(true);
  ctx.AddMetadata("testkey", "testvalue");
  req.set_message("Hello");
  EchoResponse resp;
  auto reader = stub->ResponseStream(&ctx, req);
  int count = 0;
  while (reader->Read(&resp)) {
    EXPECT_EQ(resp.message(), "Hello");
    count++;
  }
  ASSERT_EQ(count, kNumStreamingMessages);
  Status s = reader->Finish();
  EXPECT_EQ(s.ok(), true);
}

void MakeBidiStreamingCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  ClientContext ctx;
  EchoRequest req;
  EchoResponse resp;
  ctx.AddMetadata("testkey", "testvalue");
  req.mutable_param()->set_echo_metadata(true);
  auto stream = stub->BidiStream(&ctx);
  for (auto i = 0; i < kNumStreamingMessages; i++) {
    req.set_message("Hello" + std::to_string(i));
    stream->Write(req);
    stream->Read(&resp);
    EXPECT_EQ(req.message(), resp.message());
  }
  ASSERT_TRUE(stream->WritesDone());
  Status s = stream->Finish();
  EXPECT_EQ(s.ok(), true);
}

void MakeAsyncCQCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  CompletionQueue cq;
  EchoRequest send_request;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;

  send_request.set_message("Hello");
  cli_ctx.AddMetadata("testkey", "testvalue");
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub->AsyncEcho(&cli_ctx, send_request, &cq));
  response_reader->Finish(&recv_response, &recv_status, tag(1));
  Verifier().Expect(1, true).Verify(&cq);
  EXPECT_EQ(send_request.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

void MakeAsyncCQClientStreamingCall(
    const std::shared_ptr<Channel>& ) {

}

void MakeAsyncCQServerStreamingCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  CompletionQueue cq;
  EchoRequest send_request;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;

  cli_ctx.AddMetadata("testkey", "testvalue");
  send_request.set_message("Hello");
  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub->AsyncResponseStream(&cli_ctx, send_request, &cq, tag(1)));
  Verifier().Expect(1, true).Verify(&cq);

  for (int i = 0; i < kNumStreamingMessages; i++) {
    cli_stream->Read(&recv_response, tag(2));
    Verifier().Expect(2, true).Verify(&cq);
    ASSERT_EQ(recv_response.message(), send_request.message());
  }

  cli_stream->Read(&recv_response, tag(3));
  Verifier().Expect(3, false).Verify(&cq);

  cli_stream->Finish(&recv_status, tag(4));
  Verifier().Expect(4, true).Verify(&cq);
  EXPECT_TRUE(recv_status.ok());
}

void MakeAsyncCQBidiStreamingCall(const std::shared_ptr<Channel>& ) {

}

void MakeCallbackCall(const std::shared_ptr<Channel>& channel) {
  auto stub = grpc::testing::EchoTestService::NewStub(channel);
  ClientContext ctx;
  ctx.set_deadline(grpc_timeout_milliseconds_to_deadline(20000));
  EchoRequest req;
  std::mutex mu;
  std::condition_variable cv;
  bool done = false;
  req.mutable_param()->set_echo_metadata(true);
  ctx.AddMetadata("testkey", "testvalue");
  req.set_message("Hello");
  EchoResponse resp;
  stub->async()->Echo(&ctx, &req, &resp, [&resp, &mu, &done, &cv](Status s) {
    EXPECT_EQ(s.ok(), true);
    EXPECT_EQ(resp.message(), "Hello");
    std::lock_guard<std::mutex> l(mu);
    done = true;
    cv.notify_one();
  });
  std::unique_lock<std::mutex> l(mu);
  while (!done) {
    cv.wait(l);
  }
}

bool CheckMetadata(const std::multimap<grpc::string_ref, grpc::string_ref>& map,
                   const string& key, const string& value) {
  for (const auto& [k, v] : map) {
    if (k.starts_with(key) && v.starts_with(value)) {
      return true;
    }
  }
  return false;
}

bool CheckMetadata(const std::multimap<std::string, std::string>& map,
                   const string& key, const string& value) {
  for (const auto& [k, v] : map) {
    if (k == key && v == value) {
      return true;
    }
  }
  return false;
}

std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
CreatePhonyClientInterceptors() {
  std::vector<std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
      creators;

  creators.reserve(20);
  for (auto i = 0; i < 20; i++) {
    creators.push_back(std::make_unique<PhonyInterceptorFactory>());
  }
  return creators;
}

}
}
