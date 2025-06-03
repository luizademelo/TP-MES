Here's the commented version of the code:

```c++
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

/**
 * @class CachingInterceptor
 * @brief A gRPC client interceptor that implements caching for KeyValueStore requests.
 * 
 * This interceptor caches responses from the KeyValueStore service to improve performance
 * by avoiding repeated requests for the same key.
 */
class CachingInterceptor : public grpc::experimental::Interceptor {
 public:
  /**
   * @brief Constructs a new CachingInterceptor.
   * @param info ClientRpcInfo object containing RPC call information
   */
  CachingInterceptor(grpc::experimental::ClientRpcInfo* info) {}

  /**
   * @brief Intercepts gRPC operations at various hook points.
   * @param methods Provides access to various interception hook points and RPC data
   * 
   * This method handles different stages of the RPC call lifecycle:
   * - Initializes the stream and stub for new requests
   * - Checks cache for requested keys
   * - Fetches from server and caches if key not found
   * - Handles response and status operations
   */
  void Intercept(
      ::grpc::experimental::InterceptorBatchMethods* methods) override {
    bool hijack = false;
    
    // Handle PRE_SEND_INITIAL_METADATA hook point
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::
                PRE_SEND_INITIAL_METADATA)) {
      hijack = true;

      // Create new stub and stream for the intercepted channel
      stub_ = keyvaluestore::KeyValueStore::NewStub(
          methods->GetInterceptedChannel());
      stream_ = stub_->GetValues(&context_);
    }
    
    // Handle PRE_SEND_MESSAGE hook point
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)) {
      std::string requested_key;
      const keyvaluestore::Request* req_msg =
          static_cast<const keyvaluestore::Request*>(methods->GetSendMessage());
      
      // Extract the requested key from the message
      if (req_msg != nullptr) {
        requested_key = req_msg->key();
      } else {
        // Fallback for when message isn't directly available
        keyvaluestore::Request req_msg;
        auto* buffer = methods->GetSerializedSendMessage();
        auto copied_buffer = *buffer;
        CHECK(grpc::SerializationTraits<keyvaluestore::Request>::Deserialize(
                  &copied_buffer, &req_msg)
                  .ok());
        requested_key = req_msg.key();
      }

      // Check if key exists in cache
      auto search = cached_map_.find(requested_key);
      if (search != cached_map_.end()) {
        std::cout << requested_key << " found in map" << std::endl;
        response_ = search->second;
      } else {
        std::cout << requested_key << " not found in cache" << std::endl;

        // Key not found in cache - fetch from server
        keyvaluestore::Request req;
        req.set_key(requested_key);
        stream_->Write(req);
        keyvaluestore::Response resp;
        stream_->Read(&resp);
        response_ = resp.value();

        // Cache the new value
        cached_map_.insert({requested_key, response_});
      }
    }
    
    // Handle PRE_SEND_CLOSE hook point
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_SEND_CLOSE)) {
      stream_->WritesDone();
    }
    
    // Handle PRE_RECV_MESSAGE hook point
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)) {
      // Set the response message with cached or fetched value
      keyvaluestore::Response* resp =
          static_cast<keyvaluestore::Response*>(methods->GetRecvMessage());
      resp->set_value(response_);
    }
    
    // Handle PRE_RECV_STATUS hook point
    if (methods->QueryInterceptionHookPoint(
            grpc::experimental::InterceptionHookPoints::PRE_RECV_STATUS)) {
      // Always return OK status since we're handling the RPC internally
      auto* status = methods->GetRecvStatus();
      *status = grpc::Status::OK;
    }

    // Either hijack the call (handle it ourselves) or proceed normally
    if (hijack) {
      methods->Hijack();
    } else {
      methods->Proceed();
    }
  }

 private:
  grpc::ClientContext context_;  // Client context for RPC calls
  std::unique_ptr<keyvaluestore::KeyValueStore::Stub> stub_;  // gRPC stub
  std::unique_ptr<
      grpc::ClientReaderWriter<keyvaluestore::Request, keyvaluestore::Response>>
      stream_;  // Bidirectional stream for key-value operations
  std::map<std::string, std::string> cached_map_;  // Cache storage for key-value pairs
  std::string response_;  // Current response value
};

/**
 * @class CachingInterceptorFactory
 * @brief Factory class for creating CachingInterceptor instances.
 * 
 * Implements the ClientInterceptorFactoryInterface to provide interceptor instances
 * for gRPC client calls.
 */
class CachingInterceptorFactory
    : public grpc::experimental::ClientInterceptorFactoryInterface {
 public:
  /**
   * @brief Creates a new CachingInterceptor instance.
   * @param info ClientRpcInfo object containing RPC call information
   * @return Pointer to new interceptor instance
   */
  grpc::experimental::Interceptor* CreateClientInterceptor(
      grpc::experimental::ClientRpcInfo* info) override {
    return new CachingInterceptor(info);
  }
};
```