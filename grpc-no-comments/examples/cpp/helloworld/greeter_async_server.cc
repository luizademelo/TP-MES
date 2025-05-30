
/*
 *
 * Copyright 2015 gRPC authors.
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

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/check.h"
#include "absl/strings/str_format.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class ServerImpl final {
 public:
  ~ServerImpl() {
    server_->Shutdown();

    cq_->Shutdown();
  }

  void Run(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(&service_);

    cq_ = builder.AddCompletionQueue();

    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    HandleRpcs();
  }

 private:

  class CallData {
   public:

    CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {

      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {

        status_ = PROCESS;

        service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
      } else if (status_ == PROCESS) {

        new CallData(service_, cq_);

        std::string prefix("Hello ");
        reply_.set_message(prefix + request_.name());

        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
      } else {
        CHECK_EQ(status_, FINISH);

        delete this;
      }
    }

   private:

    Greeter::AsyncService* service_;

    ServerCompletionQueue* cq_;

    ServerContext ctx_;

    HelloRequest request_;

    HelloReply reply_;

    ServerAsyncResponseWriter<HelloReply> responder_;

    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
  };

  void HandleRpcs() {

    new CallData(&service_, cq_.get());
    void* tag;
    bool ok;
    while (true) {

      CHECK(cq_->Next(&tag, &ok));
      CHECK(ok);
      static_cast<CallData*>(tag)->Proceed();
    }
  }

  std::unique_ptr<ServerCompletionQueue> cq_;
  Greeter::AsyncService service_;
  std::unique_ptr<Server> server_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  ServerImpl server;
  server.Run(absl::GetFlag(FLAGS_port));

  return 0;
}
