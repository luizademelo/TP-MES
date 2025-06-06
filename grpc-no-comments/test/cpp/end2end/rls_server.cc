
// Copyright 2020 gRPC authors.

#include "test/cpp/end2end/rls_server.h"

#include "absl/log/log.h"
#include "gmock/gmock.h"
#include "src/proto/grpc/lookup/v1/rls.grpc.pb.h"
#include "src/proto/grpc/lookup/v1/rls.pb.h"
#include "test/core/test_util/test_config.h"

using ::grpc::lookup::v1::RouteLookupRequest;
using ::grpc::lookup::v1::RouteLookupResponse;

namespace grpc {
namespace testing {

::grpc::Status RlsServiceImpl::RouteLookup(grpc::ServerContext* context,
                                           const RouteLookupRequest* request,
                                           RouteLookupResponse* response) {
  LOG(INFO) << "RLS: Received request: " << request->DebugString();
  if (context_proc_ != nullptr) {
    context_proc_(context);
  }
  IncreaseRequestCount();
  EXPECT_EQ(request->target_type(), "grpc");

  ResponseData res;
  {
    grpc::internal::MutexLock lock(&mu_);
    auto it = responses_.find(*request);
    if (it == responses_.end()) {
      LOG(INFO) << "RLS: no matching request, returning INTERNAL";
      unmatched_requests_.push_back(*request);
      return Status(StatusCode::INTERNAL, "no response entry");
    }
    res = it->second;
  }

  if (res.response_delay > grpc_core::Duration::Zero()) {
    gpr_sleep_until(
        grpc_timeout_milliseconds_to_deadline(res.response_delay.millis()));
  }
  IncreaseResponseCount();
  *response = res.response;
  LOG(INFO) << "RLS: returning configured response: "
            << response->DebugString();
  return Status::OK;
}

void RlsServiceImpl::SetResponse(RouteLookupRequest request,
                                 RouteLookupResponse response,
                                 grpc_core::Duration response_delay) {
  grpc::internal::MutexLock lock(&mu_);
  responses_[std::move(request)] = {std::move(response), response_delay};
}

void RlsServiceImpl::RemoveResponse(const RouteLookupRequest& request) {
  grpc::internal::MutexLock lock(&mu_);
  responses_.erase(request);
}

std::vector<RouteLookupRequest> RlsServiceImpl::GetUnmatchedRequests() {
  grpc::internal::MutexLock lock(&mu_);
  return std::move(unmatched_requests_);
}

grpc::lookup::v1::RouteLookupRequest BuildRlsRequest(
    std::map<std::string, std::string> key,
    grpc::lookup::v1::RouteLookupRequest::Reason reason,
    const char* stale_header_data) {
  grpc::lookup::v1::RouteLookupRequest request;
  request.set_target_type("grpc");
  request.mutable_key_map()->insert(key.begin(), key.end());
  request.set_reason(reason);
  request.set_stale_header_data(stale_header_data);
  return request;
}

grpc::lookup::v1::RouteLookupResponse BuildRlsResponse(
    std::vector<std::string> targets, const char* header_data) {
  grpc::lookup::v1::RouteLookupResponse response;
  response.mutable_targets()->Add(targets.begin(), targets.end());
  response.set_header_data(header_data);
  return response;
}

}
}
