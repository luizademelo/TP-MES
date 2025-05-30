
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_CLI_CALL_H
#define GRPC_TEST_CPP_UTIL_CLI_CALL_H

#include <grpcpp/channel.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <map>

namespace grpc {

class ClientContext;

struct CliArgs {
  double timeout = -1;
};

namespace testing {

class CliCall final {
 public:
  typedef std::multimap<std::string, std::string> OutgoingMetadataContainer;
  typedef std::multimap<grpc::string_ref, grpc::string_ref>
      IncomingMetadataContainer;

  CliCall(const std::shared_ptr<grpc::Channel>& channel,
          const std::string& method, const OutgoingMetadataContainer& metadata,
          CliArgs args);
  CliCall(const std::shared_ptr<grpc::Channel>& channel,
          const std::string& method, const OutgoingMetadataContainer& metadata)
      : CliCall(channel, method, metadata, CliArgs{}) {}

  ~CliCall();

  Status Call(const std::string& request, std::string* response,
              IncomingMetadataContainer* server_initial_metadata,
              IncomingMetadataContainer* server_trailing_metadata);

  void Write(const std::string& request);

  void WritesDone();

  bool Read(std::string* response,
            IncomingMetadataContainer* server_initial_metadata);

  void WriteAndWait(const std::string& request);

  void WritesDoneAndWait();

  bool ReadAndMaybeNotifyWrite(
      std::string* response,
      IncomingMetadataContainer* server_initial_metadata);

  Status Finish(IncomingMetadataContainer* server_trailing_metadata);

  std::string peer() const { return ctx_.peer(); }

 private:
  std::unique_ptr<grpc::GenericStub> stub_;
  grpc::ClientContext ctx_;
  std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call_;
  grpc::CompletionQueue cq_;
  gpr_mu write_mu_;
  gpr_cv write_cv_;
  bool write_done_;
};

}
}

#endif
