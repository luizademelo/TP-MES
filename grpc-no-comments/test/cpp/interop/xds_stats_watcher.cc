// Copyright 2023 gRPC authors.

#include "test/cpp/interop/xds_stats_watcher.h"

#include <map>

#include "absl/algorithm/container.h"
#include "absl/log/check.h"
#include "absl/strings/ascii.h"

namespace grpc {
namespace testing {

namespace {

void AddRpcMetadata(
    LoadBalancerStatsResponse::RpcMetadata* rpc_metadata,
    const std::unordered_set<std::string>& included_keys, bool include_all_keys,
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    LoadBalancerStatsResponse::MetadataType type) {
  for (const auto& key_value : metadata) {
    absl::string_view key(key_value.first.data(), key_value.first.length());
    if (include_all_keys ||
        included_keys.find(absl::AsciiStrToLower(key)) != included_keys.end()) {
      auto entry = rpc_metadata->add_metadata();
      entry->set_key(key);
      entry->set_value(absl::string_view(key_value.second.data(),
                                         key_value.second.length()));
      entry->set_type(type);
    }
  }
}

std::unordered_set<std::string> ToLowerCase(
    absl::Span<const std::string> strings) {
  std::unordered_set<std::string> result;
  for (const auto& str : strings) {
    result.emplace(absl::AsciiStrToLower(str));
  }
  return result;
}

bool HasNonEmptyMetadata(
    const std::map<std::string, LoadBalancerStatsResponse::MetadataByPeer>&
        metadata_by_peer) {
  for (const auto& entry : metadata_by_peer) {
    for (const auto& rpc_metadata : entry.second.rpc_metadata()) {
      if (rpc_metadata.metadata_size() > 0) {
        return true;
      }
    }
  }
  return false;
}

}

XdsStatsWatcher::XdsStatsWatcher(int start_id, int end_id,
                                 absl::Span<const std::string> metadata_keys)
    : start_id_(start_id),
      end_id_(end_id),
      rpcs_needed_(end_id - start_id),
      metadata_keys_(ToLowerCase(metadata_keys)),
      include_all_metadata_(
          absl::c_any_of(metadata_keys, [](absl::string_view key) {
            return absl::StripAsciiWhitespace(key) == "*";
          })) {}

void XdsStatsWatcher::RpcCompleted(
    const AsyncClientCallResult& call, const std::string& peer,
    const std::multimap<grpc::string_ref, grpc::string_ref>& initial_metadata,
    const std::multimap<grpc::string_ref, grpc::string_ref>&
        trailing_metadata) {

  if ((start_id_ == 0 && end_id_ == 0) ||
      (start_id_ <= call.saved_request_id && call.saved_request_id < end_id_)) {
    {
      std::lock_guard<std::mutex> lock(m_);
      if (peer.empty()) {
        no_remote_peer_++;
        ++no_remote_peer_by_type_[call.rpc_type];
      } else {

        rpcs_by_peer_[peer]++;
        rpcs_by_type_[call.rpc_type][peer]++;
        auto* rpc_metadata = metadata_by_peer_[peer].add_rpc_metadata();
        AddRpcMetadata(rpc_metadata, metadata_keys_, include_all_metadata_,
                       initial_metadata, LoadBalancerStatsResponse::INITIAL);
        AddRpcMetadata(rpc_metadata, metadata_keys_, include_all_metadata_,
                       trailing_metadata, LoadBalancerStatsResponse::TRAILING);
      }
      rpcs_needed_--;

      auto& stats_per_method = *accumulated_stats_.mutable_stats_per_method();
      auto& method_stat =
          stats_per_method[ClientConfigureRequest_RpcType_Name(call.rpc_type)];
      auto& result = *method_stat.mutable_result();
      grpc_status_code code =
          static_cast<grpc_status_code>(call.status.error_code());
      auto& num_rpcs = result[code];
      ++num_rpcs;
      auto rpcs_started = method_stat.rpcs_started();
      method_stat.set_rpcs_started(++rpcs_started);
    }
    cv_.notify_one();
  }
}

LoadBalancerStatsResponse XdsStatsWatcher::WaitForRpcStatsResponse(
    int timeout_sec) {
  LoadBalancerStatsResponse response;
  std::unique_lock<std::mutex> lock(m_);
  cv_.wait_for(lock, std::chrono::seconds(timeout_sec),
               [this] { return rpcs_needed_ == 0; });
  response.mutable_rpcs_by_peer()->insert(rpcs_by_peer_.begin(),
                                          rpcs_by_peer_.end());

  if (HasNonEmptyMetadata(metadata_by_peer_)) {
    response.mutable_metadatas_by_peer()->insert(metadata_by_peer_.begin(),
                                                 metadata_by_peer_.end());
  }
  auto& response_rpcs_by_method = *response.mutable_rpcs_by_method();
  for (const auto& rpc_by_type : rpcs_by_type_) {
    std::string method_name;
    if (rpc_by_type.first == ClientConfigureRequest::EMPTY_CALL) {
      method_name = "EmptyCall";
    } else if (rpc_by_type.first == ClientConfigureRequest::UNARY_CALL) {
      method_name = "UnaryCall";
    } else {
      CHECK(0);
    }

    auto& response_rpc_by_method = response_rpcs_by_method[method_name];
    auto& response_rpcs_by_peer =
        *response_rpc_by_method.mutable_rpcs_by_peer();
    for (const auto& rpc_by_peer : rpc_by_type.second) {
      auto& response_rpc_by_peer = response_rpcs_by_peer[rpc_by_peer.first];
      response_rpc_by_peer = rpc_by_peer.second;
    }
  }
  response.set_num_failures(no_remote_peer_ + rpcs_needed_);
  return response;
}

void XdsStatsWatcher::GetCurrentRpcStats(
    LoadBalancerAccumulatedStatsResponse* response,
    StatsWatchers* stats_watchers) {
  std::unique_lock<std::mutex> lock(m_);
  response->CopyFrom(accumulated_stats_);

  auto& response_rpcs_started_by_method =
      *response->mutable_num_rpcs_started_by_method();
  auto& response_rpcs_succeeded_by_method =
      *response->mutable_num_rpcs_succeeded_by_method();
  auto& response_rpcs_failed_by_method =
      *response->mutable_num_rpcs_failed_by_method();

  for (const auto& rpc_by_type : rpcs_by_type_) {
    auto total_succeeded = 0;
    for (const auto& rpc_by_peer : rpc_by_type.second) {
      total_succeeded += rpc_by_peer.second;
    }
    response_rpcs_succeeded_by_method[ClientConfigureRequest_RpcType_Name(
        rpc_by_type.first)] = total_succeeded;
    response_rpcs_started_by_method[ClientConfigureRequest_RpcType_Name(
        rpc_by_type.first)] =
        stats_watchers->global_request_id_by_type[rpc_by_type.first];
    response_rpcs_failed_by_method[ClientConfigureRequest_RpcType_Name(
        rpc_by_type.first)] = no_remote_peer_by_type_[rpc_by_type.first];
  }
}

}
}
