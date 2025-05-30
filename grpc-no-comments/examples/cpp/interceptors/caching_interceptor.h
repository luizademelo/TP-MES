
/*
 *
 * Copyright 2018 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpcpp/support/client_interceptor.h>

#include <map>

#include "absl/log/check.h"

#ifdef BAZEL_BUILD
#include "examples/protos/keyvaluestore.grpc.pb.h"
#else
#include "keyvaluestore.grpc.pb.h"
#endif

class CachingInterceptor : public grpc::experimental::Interceptor {
 public:
  CachingInterceptor(grpc::experimental::ClientRpcInfo* info) {}

  void Intercept(
      ::grpc::experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::
                PRE_SEND_INITIAL_METADATA)) {

      hijack = true;

      stub_ = keyvaluestore::KeyValueStore::NewStub(
          methods->GetInterceptedChannel());
      stream_ = stub_->GetValues(&context_);
    }
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {

      std::string requested_key;
      const keyvaluestore::Request* req_msg =
          static_cast<const keyvaluestore::Request*>(methods->GetSendMessage());
      if (req_msg != nullptr) {
        requested_key = req_msg->key();
      } else {

        keyvaluestore::Request req_msg;
        auto* buffer = methods->GetSerializedSendMessage();
        auto copied_buffer = *buffer;
        CHECK(grpc::SerializationTraits<keyvaluestore::Request>::Deserialize(
                  &copied_buffer, &req_msg)
                  .ok());
        requested_key = req_msg.key();
      }

      auto search = cached_map_.find(requested_key);
      if (search != cached_map_.end()) {
        std::cout << requested_key << " found in map" << std::endl;
        response_ = search->second;
      } else {
        std::cout << requested_key << " not found in cache" << std::endl;

        keyvaluestore::Request req;
        req.set_key(requested_key);
        stream_->Write(req);
        keyvaluestore::Response resp;
        stream_->Read(&resp);
        response_ = resp.value();

        cached_map_.insert({requested_key, response_});
      }
    }
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {
      stream_->WritesDone();
    }
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {
      keyvaluestore::Response* resp =
          static_cast<keyvaluestore::Response*>(methods->GetRecvMessage());
      resp->set_value(response_);
    }
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      auto* status = methods->GetRecvStatus();
      *status = grpc::Status::OK;
    }

    if (hijack) {

      methods->Hijack();
    } else {

      methods->Proceed();
    }
  }

 private:
  grpc::ClientContext context_;
  std::unique_ptr<keyvaluestore::KeyValueStore::Stub> stub_;
  std::unique_ptr<
      grpc::ClientReaderWriter<keyvaluestore::Request, keyvaluestore::Response>>
      stream_;
  std::map<std::string, std::string> cached_map_;
  std::string response_;
};

class CachingInterceptorFactory
    : public grpc::experimental::ClientInterceptorFactoryInterface {
 public:
  grpc::experimental::Interceptor* CreateClientInterceptor(
      grpc::experimental::ClientRpcInfo* info) override {
    return new CachingInterceptor(info);
  }
};
