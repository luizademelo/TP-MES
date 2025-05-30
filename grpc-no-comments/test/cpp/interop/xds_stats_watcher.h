
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_XDS_STATS_WATCHER_H
#define GRPC_TEST_CPP_INTEROP_XDS_STATS_WATCHER_H

#include <grpcpp/grpcpp.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include "absl/status/status.h"
#include "absl/types/span.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"

namespace grpc {
namespace testing {

class XdsStatsWatcher;

struct AsyncClientCallResult {
  Empty empty_response;
  SimpleResponse simple_response;
  Status status;
  int saved_request_id;
  ClientConfigureRequest::RpcType rpc_type;
};

struct StatsWatchers {

  int global_request_id = 0;

  std::map<int, int> global_request_id_by_type;

  std::set<XdsStatsWatcher*> watchers;

  XdsStatsWatcher* global_watcher;

  std::mutex mu;
};

class XdsStatsWatcher {
 public:
  XdsStatsWatcher(int start_id, int end_id,
                  absl::Span<const std::string> metadata_keys);

  void RpcCompleted(
      const AsyncClientCallResult& call, const std::string& peer,
      const std::multimap<grpc::string_ref, grpc::string_ref>& initial_metadata,
      const std::multimap<grpc::string_ref, grpc::string_ref>&
          trailing_metadata);

  LoadBalancerStatsResponse WaitForRpcStatsResponse(int timeout_sec);

  void GetCurrentRpcStats(LoadBalancerAccumulatedStatsResponse* response,
                          StatsWatchers* stats_watchers);

 private:
  int start_id_;
  int end_id_;
  int rpcs_needed_;
  int no_remote_peer_ = 0;
  std::map<int, int> no_remote_peer_by_type_;

  std::map<std::string, int> rpcs_by_peer_;

  std::map<int, std::map<std::string, int>> rpcs_by_type_;

  LoadBalancerAccumulatedStatsResponse accumulated_stats_;
  std::mutex m_;
  std::condition_variable cv_;
  std::unordered_set<std::string> metadata_keys_;
  bool include_all_metadata_ = false;
  std::map<std::string, LoadBalancerStatsResponse::MetadataByPeer>
      metadata_by_peer_;
};

}
}

#endif
