
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <cinttypes>
#include <memory>
#include <thread>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/byte_buffer_proto_helper.h"
#include "test/cpp/util/string_ref_helper.h"

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;

namespace grpc {
namespace testing {

namespace {

void* tag(int i) { return reinterpret_cast<void*>(i); }
int detag(void* p) { return static_cast<int>(reinterpret_cast<intptr_t>(p)); }

class Verifier {
 public:
  Verifier() {}

  Verifier& Expect(int i, bool expect_ok) {
    expectations_[tag(i)] = expect_ok;
    return *this;
  }

  int Next(CompletionQueue* cq, bool ignore_ok) {
    bool ok;
    void* got_tag;
    EXPECT_TRUE(cq->Next(&got_tag, &ok));
    GotTag(got_tag, ok, ignore_ok);
    return detag(got_tag);
  }

  void Verify(CompletionQueue* cq) {
    CHECK(!expectations_.empty());
    while (!expectations_.empty()) {
      Next(cq, false);
    }
  }

 private:
  void GotTag(void* got_tag, bool ok, bool ignore_ok) {
    auto it = expectations_.find(got_tag);
    if (it != expectations_.end()) {
      if (!ignore_ok) {
        EXPECT_EQ(it->second, ok);
      }
      expectations_.erase(it);
    }
  }

  std::map<void*, bool> expectations_;
};

class RawEnd2EndTest : public ::testing::Test {
 protected:
  RawEnd2EndTest() {}

  void SetUp() override {
    port_ = grpc_pick_unused_port_or_die();
    server_address_ << "localhost:" << port_;
  }

  void TearDown() override {
    server_->Shutdown();
    void* ignored_tag;
    bool ignored_ok;
    cq_->Shutdown();
    while (cq_->Next(&ignored_tag, &ignored_ok)) {
    }
    stub_.reset();
    grpc_recycle_unused_port(port_);
  }

  template <typename ServerType>
  std::unique_ptr<ServerType> BuildAndStartServer() {
    ServerBuilder builder;
    builder.AddListeningPort(server_address_.str(),
                             grpc::InsecureServerCredentials());
    std::unique_ptr<ServerType> service(new ServerType());
    builder.RegisterService(service.get());
    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    return service;
  }

  void ResetStub() {
    ChannelArguments args;
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
        server_address_.str(), grpc::InsecureChannelCredentials());
    stub_ = grpc::testing::EchoTestService::NewStub(channel);
  }

  std::unique_ptr<ServerCompletionQueue> cq_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<Server> server_;
  std::ostringstream server_address_;
  int port_;

  EchoRequest send_request_;
  grpc::ByteBuffer send_request_buffer_;

  EchoRequest recv_request_;
  grpc::ByteBuffer recv_request_buffer_;

  EchoResponse send_response_;
  grpc::ByteBuffer send_response_buffer_;

  EchoResponse recv_response_;
  grpc::ByteBuffer recv_response_buffer_;
  Status recv_status_;

  ClientContext cli_ctx_;
  ServerContext srv_ctx_;
};

TEST_F(RawEnd2EndTest, PureAsyncService) {
  typedef grpc::testing::EchoTestService::AsyncService SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx_);

  send_request_.set_message("hello");
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx_, send_request_, cq_.get()));
  service->RequestEcho(&srv_ctx_, &recv_request_, &response_writer, cq_.get(),
                       cq_.get(), tag(2));
  response_reader->Finish(&recv_response_, &recv_status_, tag(4));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request_.message(), recv_request_.message());
  send_response_.set_message(recv_request_.message());
  response_writer.Finish(send_response_, Status::OK, tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());

  EXPECT_EQ(send_response_.message(), recv_response_.message());
  EXPECT_TRUE(recv_status_.ok());
}

TEST_F(RawEnd2EndTest, RawServerUnary) {
  typedef grpc::testing::EchoTestService::WithRawMethod_Echo<
      grpc::testing::EchoTestService::Service>
      SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();
  grpc::GenericServerAsyncResponseWriter response_writer(&srv_ctx_);

  send_request_.set_message("hello unary");
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx_, send_request_, cq_.get()));
  service->RequestEcho(&srv_ctx_, &recv_request_buffer_, &response_writer,
                       cq_.get(), cq_.get(), tag(2));
  response_reader->Finish(&recv_response_, &recv_status_, tag(4));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_TRUE(ParseFromByteBuffer(&recv_request_buffer_, &recv_request_));
  EXPECT_EQ(send_request_.message(), recv_request_.message());
  send_response_.set_message(recv_request_.message());
  EXPECT_TRUE(
      SerializeToByteBufferInPlace(&send_response_, &send_response_buffer_));
  response_writer.Finish(send_response_buffer_, Status::OK, tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());

  EXPECT_EQ(send_response_.message(), recv_response_.message());
  EXPECT_TRUE(recv_status_.ok());
}

TEST_F(RawEnd2EndTest, RawServerClientStreaming) {
  typedef grpc::testing::EchoTestService::WithRawMethod_RequestStream<
      grpc::testing::EchoTestService::Service>
      SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();

  grpc::GenericServerAsyncReader srv_stream(&srv_ctx_);

  send_request_.set_message("hello client streaming");
  std::unique_ptr<ClientAsyncWriter<EchoRequest>> cli_stream(
      stub_->AsyncRequestStream(&cli_ctx_, &recv_response_, cq_.get(), tag(1)));

  service->RequestRequestStream(&srv_ctx_, &srv_stream, cq_.get(), cq_.get(),
                                tag(2));

  Verifier().Expect(2, true).Expect(1, true).Verify(cq_.get());

  cli_stream->Write(send_request_, tag(3));
  srv_stream.Read(&recv_request_buffer_, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  ParseFromByteBuffer(&recv_request_buffer_, &recv_request_);
  EXPECT_EQ(send_request_.message(), recv_request_.message());

  cli_stream->Write(send_request_, tag(5));
  srv_stream.Read(&recv_request_buffer_, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  ParseFromByteBuffer(&recv_request_buffer_, &recv_request_);
  EXPECT_EQ(send_request_.message(), recv_request_.message());
  cli_stream->WritesDone(tag(7));
  srv_stream.Read(&recv_request_buffer_, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  ParseFromByteBuffer(&recv_request_buffer_, &recv_request_);
  send_response_.set_message(recv_request_.message());
  SerializeToByteBufferInPlace(&send_response_, &send_response_buffer_);
  srv_stream.Finish(send_response_buffer_, Status::OK, tag(9));
  cli_stream->Finish(&recv_status_, tag(10));
  Verifier().Expect(9, true).Expect(10, true).Verify(cq_.get());

  EXPECT_EQ(send_response_.message(), recv_response_.message());
  EXPECT_TRUE(recv_status_.ok());
}

TEST_F(RawEnd2EndTest, RawServerServerStreaming) {
  typedef grpc::testing::EchoTestService::WithRawMethod_ResponseStream<
      grpc::testing::EchoTestService::Service>
      SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();
  grpc::GenericServerAsyncWriter srv_stream(&srv_ctx_);

  send_request_.set_message("hello server streaming");
  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx_, send_request_, cq_.get(), tag(1)));

  service->RequestResponseStream(&srv_ctx_, &recv_request_buffer_, &srv_stream,
                                 cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());
  ParseFromByteBuffer(&recv_request_buffer_, &recv_request_);
  EXPECT_EQ(send_request_.message(), recv_request_.message());

  send_response_.set_message(recv_request_.message());
  SerializeToByteBufferInPlace(&send_response_, &send_response_buffer_);
  srv_stream.Write(send_response_buffer_, tag(3));
  cli_stream->Read(&recv_response_, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_response_.message(), recv_response_.message());

  srv_stream.Write(send_response_buffer_, tag(5));
  cli_stream->Read(&recv_response_, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_response_.message(), recv_response_.message());

  srv_stream.Finish(Status::OK, tag(7));
  cli_stream->Read(&recv_response_, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status_, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status_.ok());
}

TEST_F(RawEnd2EndTest, RawServerBidiStreaming) {
  typedef grpc::testing::EchoTestService::WithRawMethod_BidiStream<
      grpc::testing::EchoTestService::Service>
      SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();

  grpc::GenericServerAsyncReaderWriter srv_stream(&srv_ctx_);

  send_request_.set_message("hello bidi streaming");
  std::unique_ptr<ClientAsyncReaderWriter<EchoRequest, EchoResponse>>
      cli_stream(stub_->AsyncBidiStream(&cli_ctx_, cq_.get(), tag(1)));

  service->RequestBidiStream(&srv_ctx_, &srv_stream, cq_.get(), cq_.get(),
                             tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());

  cli_stream->Write(send_request_, tag(3));
  srv_stream.Read(&recv_request_buffer_, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  ParseFromByteBuffer(&recv_request_buffer_, &recv_request_);
  EXPECT_EQ(send_request_.message(), recv_request_.message());

  send_response_.set_message(recv_request_.message());
  SerializeToByteBufferInPlace(&send_response_, &send_response_buffer_);
  srv_stream.Write(send_response_buffer_, tag(5));
  cli_stream->Read(&recv_response_, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_response_.message(), recv_response_.message());

  cli_stream->WritesDone(tag(7));
  srv_stream.Read(&recv_request_buffer_, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  srv_stream.Finish(Status::OK, tag(9));
  cli_stream->Finish(&recv_status_, tag(10));
  Verifier().Expect(9, true).Expect(10, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status_.ok());
}

TEST_F(RawEnd2EndTest, CompileTest) {
  typedef grpc::testing::EchoTestService::WithRawMethod_Echo<
      grpc::testing::EchoTestService::AsyncService>
      SType;
  ResetStub();
  auto service = BuildAndStartServer<SType>();
}

}
}
}

int main(int argc, char** argv) {

  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
