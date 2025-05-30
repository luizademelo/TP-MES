
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_INTEROP_CLIENT_H
#define GRPC_TEST_CPP_INTEROP_INTEROP_CLIENT_H

#include <grpc/grpc.h>
#include <grpcpp/channel.h>

#include <cstdint>
#include <memory>

#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/cpp/interop/backend_metrics_lb_policy.h"

namespace grpc {
namespace testing {

typedef std::function<void(const InteropClientContextInspector&,
                           const SimpleRequest*, const SimpleResponse*)>
    CheckerFn;

typedef std::function<std::shared_ptr<Channel>(ChannelArguments)>
    ChannelCreationFunc;

class InteropClient {
 public:

  explicit InteropClient(ChannelCreationFunc channel_creation_func,
                         bool new_stub_every_test_case,
                         bool do_not_abort_on_transient_failures);
  ~InteropClient() {}

  void Reset(const std::shared_ptr<Channel>& channel);

  bool DoEmpty();
  bool DoLargeUnary();
  bool DoServerCompressedUnary();
  bool DoClientCompressedUnary();
  bool DoPingPong();
  bool DoHalfDuplex();
  bool DoRequestStreaming();
  bool DoResponseStreaming();
  bool DoServerCompressedStreaming();
  bool DoClientCompressedStreaming();
  bool DoResponseStreamingWithSlowConsumer();
  bool DoCancelAfterBegin();
  bool DoCancelAfterFirstResponse();
  bool DoTimeoutOnSleepingServer();
  bool DoEmptyStream();
  bool DoStatusWithMessage();

  bool DoSpecialStatusMessage();
  bool DoCustomMetadata();
  bool DoUnimplementedMethod();
  bool DoUnimplementedService();

  bool DoPickFirstUnary();
  bool DoOrcaPerRpc();
  bool DoOrcaOob();

  bool DoChannelSoakTest(const std::string& server_uri, int32_t soak_iterations,
                         int32_t max_failures,
                         int64_t max_acceptable_per_iteration_latency_ms,
                         int32_t soak_min_time_ms_between_rpcs,
                         int32_t overall_timeout_seconds, int32_t request_size,
                         int32_t response_size);
  bool DoRpcSoakTest(const std::string& server_uri, int32_t soak_iterations,
                     int32_t max_failures,
                     int64_t max_acceptable_per_iteration_latency_ms,
                     int32_t soak_min_time_ms_between_rpcs,
                     int32_t overall_timeout_seconds, int32_t request_size,
                     int32_t response_size);
  bool DoLongLivedChannelTest(int32_t soak_iterations,
                              int32_t iteration_interval);

  bool DoJwtTokenCreds(const std::string& username);
  bool DoComputeEngineCreds(const std::string& default_service_account,
                            const std::string& oauth_scope);

  bool DoOauth2AuthToken(const std::string& username,
                         const std::string& oauth_scope);

  bool DoPerRpcCreds(const std::string& json_key);

  bool DoGoogleDefaultCredentials(const std::string& default_service_account);

 private:
  class ServiceStub {
   public:
    typedef std::function<std::shared_ptr<Channel>()> ChannelCreationFunc;

    ServiceStub(ChannelCreationFunc channel_creation_func,
                bool new_stub_every_call);

    TestService::Stub* Get();
    UnimplementedService::Stub* GetUnimplementedServiceStub();

    void ResetChannel();

   private:
    ChannelCreationFunc channel_creation_func_;
    std::unique_ptr<TestService::Stub> stub_;
    std::unique_ptr<UnimplementedService::Stub> unimplemented_service_stub_;
    std::shared_ptr<Channel> channel_;
    bool new_stub_every_call_;

  };

  bool PerformLargeUnary(SimpleRequest* request, SimpleResponse* response);

  bool PerformLargeUnary(SimpleRequest* request, SimpleResponse* response,
                         const CheckerFn& custom_checks_fn);
  bool AssertStatusOk(const Status& s,
                      const std::string& optional_debug_string);
  bool AssertStatusCode(const Status& s, StatusCode expected_code,
                        const std::string& optional_debug_string);
  bool TransientFailureOrAbort();

  std::tuple<bool, int32_t, std::string, std::string>
  PerformOneSoakTestIteration(
      const bool reset_channel,
      const int32_t max_acceptable_per_iteration_latency_ms,
      const int32_t request_size, const int32_t response_size);

  void PerformSoakTest(const std::string& server_uri,
                       const bool reset_channel_per_iteration,
                       const int32_t soak_iterations,
                       const int32_t max_failures,
                       const int32_t max_acceptable_per_iteration_latency_ms,
                       const int32_t min_time_ms_between_rpcs,
                       const int32_t overall_timeout_seconds,
                       const int32_t request_size, const int32_t response_size);

  ServiceStub serviceStub_;

  bool do_not_abort_on_transient_failures_;

  LoadReportTracker load_report_tracker_;
};

}
}

#endif
