
// Copyright 2019 gRPC authors.

#include "test/cpp/microbenchmarks/callback_test_service.h"

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc {
namespace testing {
namespace {

std::string ToString(const grpc::string_ref& r) {
  return std::string(r.data(), r.size());
}

int GetIntValueFromMetadataHelper(
    const char* key,
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    int default_value) {
  if (metadata.find(key) != metadata.end()) {
    std::istringstream iss(ToString(metadata.find(key)->second));
    iss >> default_value;
  }

  return default_value;
}

int GetIntValueFromMetadata(
    const char* key,
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    int default_value) {
  return GetIntValueFromMetadataHelper(key, metadata, default_value);
}
}

ServerUnaryReactor* CallbackStreamingTestService::Echo(
    CallbackServerContext* context, const EchoRequest* ,
    EchoResponse* response) {
  int response_msgs_size = GetIntValueFromMetadata(
      kServerMessageSize, context->client_metadata(), 0);
  if (response_msgs_size > 0) {
    response->set_message(std::string(response_msgs_size, 'a'));
  } else {
    response->set_message("");
  }
  auto* reactor = context->DefaultReactor();
  reactor->Finish(grpc::Status::OK);
  return reactor;
}

ServerBidiReactor<EchoRequest, EchoResponse>*
CallbackStreamingTestService::BidiStream(CallbackServerContext* context) {
  class Reactor : public ServerBidiReactor<EchoRequest, EchoResponse> {
   public:
    explicit Reactor(CallbackServerContext* context) {
      message_size_ = GetIntValueFromMetadata(kServerMessageSize,
                                              context->client_metadata(), 0);
      StartRead(&request_);
    }
    void OnDone() override {
      CHECK(finished_);
      delete this;
    }
    void OnCancel() override {}
    void OnReadDone(bool ok) override {
      if (!ok) {

        Finish(grpc::Status::OK);
        finished_ = true;
        return;
      }
      if (message_size_ > 0) {
        response_.set_message(std::string(message_size_, 'a'));
      } else {
        response_.set_message("");
      }
      StartWrite(&response_);
    }
    void OnWriteDone(bool ok) override {
      if (!ok) {
        LOG(ERROR) << "Server write failed";
        return;
      }
      StartRead(&request_);
    }

   private:
    EchoRequest request_;
    EchoResponse response_;
    int message_size_;
    bool finished_{false};
  };

  return new Reactor(context);
}
}
}
