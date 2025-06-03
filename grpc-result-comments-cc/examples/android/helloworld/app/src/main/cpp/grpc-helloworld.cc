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

#include <atomic>

#include <grpc++/grpc++.h>
#include <jni.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Atomic flag to control server shutdown
std::atomic<bool> stop_server(false);

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::Service {
  // Implementation of the SayHello RPC method
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("Hello ");
    // Set the reply message by combining prefix with the request name
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

// Starts a gRPC server that listens on the specified port
// The server runs until stop_server is set to true or the Java-side task is cancelled
void StartServer(JNIEnv* env, jobject obj, jmethodID is_cancelled_mid,
                 int port) {
  // Format the host:port string for server binding
  const int host_port_buf_size = 1024;
  char host_port[host_port_buf_size];
  snprintf(host_port, host_port_buf_size, "0.0.0.0:%d", port);

  // Create and register the service implementation
  GreeterServiceImpl service;
  ServerBuilder builder;

  // Configure server to listen on the specified port with insecure credentials
  builder.AddListeningPort(host_port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  
  // Server run loop
  while (!stop_server.load()) {
    // Check if the Java-side task has been cancelled
    jboolean is_cancelled = env->CallBooleanMethod(obj, is_cancelled_mid);
    if (is_cancelled == JNI_TRUE) {
      stop_server = true;
    }
  }
}

// Client for the Greeter service
class GreeterClient {
 public:
  // Constructor that takes a channel to the server
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Calls the SayHello RPC method
  std::string SayHello(const std::string& user) {
    // Prepare the request
    HelloRequest request;
    request.set_name(user);

    // Will hold the server's response
    HelloReply reply;
    ClientContext context;

    // Make the RPC call
    Status status = stub_->SayHello(&context, request, &reply);

    // Return the response message or error
    if (status.ok()) {
      return reply.message();
    } else {
      return status.error_message();
    }
  }

 private:
  // The gRPC stub for making RPC calls
  std::unique_ptr<Greeter::Stub> stub_;
};

// JNI function to make a Hello call from Java to C++
extern "C" JNIEXPORT jstring JNICALL
Java_io_grpc_helloworldexample_cpp_HelloworldActivity_sayHello(
    JNIEnv* env, jobject obj_unused, jstring host_raw, jint port_raw,
    jstring message_raw) {
  // Convert Java strings to C++ strings
  const char* host_chars = env->GetStringUTFChars(host_raw, (jboolean*)0);
  std::string host(host_chars, env->GetStringUTFLength(host_raw));

  int port = static_cast<int>(port_raw);

  const char* message_chars = env->GetStringUTFChars(message_raw, (jboolean*)0);
  std::string message(message_chars, env->GetStringUTFLength(message_raw));

  // Format the server address
  const int host_port_buf_size = 1024;
  char host_port[host_port_buf_size];
  snprintf(host_port, host_port_buf_size, "%s:%d", host.c_str(), port);

  // Create client and make RPC call
  GreeterClient greeter(
      grpc::CreateChannel(host_port, grpc::InsecureChannelCredentials()));
  std::string reply = greeter.SayHello(message);

  // Convert response to Java string and return
  return env->NewStringUTF(reply.c_str());
}

// JNI function to start the gRPC server from Java
extern "C" JNIEXPORT void JNICALL
Java_io_grpc_helloworldexample_cpp_HelloworldActivity_startServer(
    JNIEnv* env, jobject obj_this, jint port_raw) {
  int port = static_cast<int>(port_raw);

  // Get the Java method ID for checking cancellation
  jclass cls = env->GetObjectClass(obj_this);
  jmethodID is_cancelled_mid =
      env->GetMethodID(cls, "isRunServerTaskCancelled", "()Z");

  // Reset the server stop flag
  stop_server = false;

  // Start the server
  StartServer(env, obj_this, is_cancelled_mid, port);
}
```