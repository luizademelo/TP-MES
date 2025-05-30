
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CPP_END2END_XDS_XDS_SERVER_H
#define GRPC_TEST_CPP_END2END_XDS_XDS_SERVER_H

#include <grpcpp/support/status.h>

#include <deque>
#include <optional>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "envoy/config/cluster/v3/cluster.pb.h"
#include "envoy/config/endpoint/v3/endpoint.pb.h"
#include "envoy/config/listener/v3/listener.pb.h"
#include "envoy/config/route/v3/route.pb.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "src/proto/grpc/testing/xds/v3/ads.grpc.pb.h"
#include "src/proto/grpc/testing/xds/v3/discovery.pb.h"
#include "src/proto/grpc/testing/xds/v3/lrs.grpc.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/counted_service.h"

namespace grpc {
namespace testing {

constexpr char kLdsTypeUrl[] =
    "type.googleapis.com/envoy.config.listener.v3.Listener";
constexpr char kRdsTypeUrl[] =
    "type.googleapis.com/envoy.config.route.v3.RouteConfiguration";
constexpr char kCdsTypeUrl[] =
    "type.googleapis.com/envoy.config.cluster.v3.Cluster";
constexpr char kEdsTypeUrl[] =
    "type.googleapis.com/envoy.config.endpoint.v3.ClusterLoadAssignment";

class AdsServiceImpl
    : public CountedService<
          ::envoy::service::discovery::v3::AggregatedDiscoveryService::Service>,
      public std::enable_shared_from_this<AdsServiceImpl> {
 public:
  using DiscoveryRequest = ::envoy::service::discovery::v3::DiscoveryRequest;
  using DiscoveryResponse = ::envoy::service::discovery::v3::DiscoveryResponse;

  struct ResponseState {
    enum State {
      ACKED,
      NACKED,
    };
    State state = ACKED;
    std::string error_message;
  };

  explicit AdsServiceImpl(
      std::function<void(const DiscoveryRequest& request)> check_first_request =
          nullptr,
      std::function<void(absl::StatusCode)> check_nack_status_code = nullptr,
      absl::string_view debug_label = "")
      : check_first_request_(std::move(check_first_request)),
        check_nack_status_code_(std::move(check_nack_status_code)),
        debug_label_(absl::StrFormat(
            "%p%s%s", this, debug_label.empty() ? "" : ":", debug_label)) {}

  void set_wrap_resources(bool wrap_resources) {
    grpc_core::MutexLock lock(&ads_mu_);
    wrap_resources_ = wrap_resources;
  }

  void SetResource(google::protobuf::Any resource, const std::string& type_url,
                   const std::string& name);

  void UnsetResource(const std::string& type_url, const std::string& name);

  void SetLdsResource(const ::envoy::config::listener::v3::Listener& listener) {
    google::protobuf::Any resource;
    resource.PackFrom(listener);
    SetResource(std::move(resource), kLdsTypeUrl, listener.name());
  }

  void SetRdsResource(
      const ::envoy::config::route::v3::RouteConfiguration& route) {
    google::protobuf::Any resource;
    resource.PackFrom(route);
    SetResource(std::move(resource), kRdsTypeUrl, route.name());
  }

  void SetCdsResource(const ::envoy::config::cluster::v3::Cluster& cluster) {
    google::protobuf::Any resource;
    resource.PackFrom(cluster);
    SetResource(std::move(resource), kCdsTypeUrl, cluster.name());
  }

  void SetEdsResource(
      const ::envoy::config::endpoint::v3::ClusterLoadAssignment& assignment) {
    google::protobuf::Any resource;
    resource.PackFrom(assignment);
    SetResource(std::move(resource), kEdsTypeUrl, assignment.cluster_name());
  }

  void IgnoreResourceType(const std::string& type_url) {
    grpc_core::MutexLock lock(&ads_mu_);
    resource_types_to_ignore_.emplace(type_url);
  }

  void SetCheckVersionCallback(
      std::function<void(absl::string_view, int)> check_version_callback) {
    grpc_core::MutexLock lock(&ads_mu_);
    check_version_callback_ = std::move(check_version_callback);
  }

  std::optional<ResponseState> GetResponseState(const std::string& type_url) {
    grpc_core::MutexLock lock(&ads_mu_);
    if (resource_type_response_state_[type_url].empty()) {
      return std::nullopt;
    }
    auto response = resource_type_response_state_[type_url].front();
    resource_type_response_state_[type_url].pop_front();
    return response;
  }
  std::optional<ResponseState> lds_response_state() {
    return GetResponseState(kLdsTypeUrl);
  }
  std::optional<ResponseState> rds_response_state() {
    return GetResponseState(kRdsTypeUrl);
  }
  std::optional<ResponseState> cds_response_state() {
    return GetResponseState(kCdsTypeUrl);
  }
  std::optional<ResponseState> eds_response_state() {
    return GetResponseState(kEdsTypeUrl);
  }

  void Start();

  void Shutdown();

  std::set<std::string> clients() {
    grpc_core::MutexLock lock(&clients_mu_);
    return clients_;
  }

  void ForceADSFailure(Status status) {
    grpc_core::MutexLock lock(&ads_mu_);
    forced_ads_failure_ = std::move(status);
  }

  void ClearADSFailure() {
    grpc_core::MutexLock lock(&ads_mu_);
    forced_ads_failure_ = std::nullopt;
  }

 private:

  using UpdateQueue = std::deque<
      std::pair<std::string , std::string >>;

  struct SubscriptionState {

    UpdateQueue* update_queue;
  };

  using SubscriptionNameMap =
      std::map<std::string , SubscriptionState>;
  using SubscriptionMap =
      std::map<std::string , SubscriptionNameMap>;

  struct SentState {
    int nonce = 0;
    int resource_type_version = 0;
  };

  struct ResourceState {

    std::optional<google::protobuf::Any> resource;

    int resource_type_version = 0;

    std::set<SubscriptionState*> subscriptions;
  };

  using ResourceNameMap =
      std::map<std::string , ResourceState>;

  struct ResourceTypeState {
    int resource_type_version = 0;
    ResourceNameMap resource_name_map;
  };

  using ResourceMap = std::map<std::string , ResourceTypeState>;

  using Stream = ServerReaderWriter<DiscoveryResponse, DiscoveryRequest>;

  Status StreamAggregatedResources(ServerContext* context,
                                   Stream* stream) override {
    LOG(INFO) << "ADS[" << debug_label_
              << "]: StreamAggregatedResources starts";
    {
      grpc_core::MutexLock lock(&ads_mu_);
      if (forced_ads_failure_.has_value()) {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: StreamAggregatedResources forcing early failure "
                     "with status code: "
                  << forced_ads_failure_.value().error_code() << ", message: "
                  << forced_ads_failure_.value().error_message();
        return forced_ads_failure_.value();
      }
    }
    AddClient(context->peer());

    std::shared_ptr<AdsServiceImpl> ads_service_impl = shared_from_this();

    UpdateQueue update_queue;

    SubscriptionMap subscription_map;

    std::map<std::string , SentState> sent_state_map;

    std::deque<DiscoveryRequest> requests;
    bool stream_closed = false;
    std::thread reader(std::bind(&AdsServiceImpl::BlockingRead, this, stream,
                                 &requests, &stream_closed));

    while (true) {

      bool did_work = false;

      std::optional<DiscoveryResponse> response;
      {
        grpc_core::MutexLock lock(&ads_mu_);

        if (stream_closed || ads_done_) break;

        if (!requests.empty()) {
          DiscoveryRequest request = std::move(requests.front());
          requests.pop_front();
          did_work = true;
          LOG(INFO) << "ADS[" << debug_label_ << "]: Received request for type "
                    << request.type_url() << " with content "
                    << request.DebugString();
          SentState& sent_state = sent_state_map[request.type_url()];

          ProcessRequest(request, &update_queue, &subscription_map, &sent_state,
                         &response);
        }
      }
      if (response.has_value()) {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: Sending response: " << response->DebugString();
        stream->Write(response.value());
      }
      response.reset();

      {
        grpc_core::MutexLock lock(&ads_mu_);
        if (!update_queue.empty()) {
          auto [resource_type, resource_name] = std::move(update_queue.front());
          update_queue.pop_front();
          did_work = true;
          SentState& sent_state = sent_state_map[resource_type];
          ProcessUpdate(resource_type, resource_name, &subscription_map,
                        &sent_state, &response);
        }
      }
      if (response.has_value()) {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: Sending update response: " << response->DebugString();
        stream->Write(response.value());
      }
      {
        grpc_core::MutexLock lock(&ads_mu_);
        if (ads_done_) {
          break;
        }
      }

      gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(did_work ? 0 : 10));
    }

    reader.join();

    {
      grpc_core::MutexLock lock(&ads_mu_);
      for (auto& [type_url, subscription_name_map] : subscription_map) {
        for (auto& [resource_name, subscription_state] :
             subscription_name_map) {
          ResourceNameMap& resource_name_map =
              resource_map_[type_url].resource_name_map;
          ResourceState& resource_state = resource_name_map[resource_name];
          resource_state.subscriptions.erase(&subscription_state);
        }
      }
    }
    LOG(INFO) << "ADS[" << debug_label_ << "]: StreamAggregatedResources done";
    RemoveClient(context->peer());
    return Status::OK;
  }

  void ProcessRequest(const DiscoveryRequest& request,
                      UpdateQueue* update_queue,
                      SubscriptionMap* subscription_map, SentState* sent_state,
                      std::optional<DiscoveryResponse>* response)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(ads_mu_) {

    if (request.response_nonce().empty()) {
      int client_resource_type_version = 0;
      if (!request.version_info().empty()) {
        CHECK(absl::SimpleAtoi(request.version_info(),
                               &client_resource_type_version));
      }
      if (check_version_callback_ != nullptr) {
        check_version_callback_(request.type_url(),
                                client_resource_type_version);
      }
    } else {
      int client_nonce;
      CHECK(absl::SimpleAtoi(request.response_nonce(), &client_nonce));

      ResponseState response_state;
      if (!request.has_error_detail()) {
        response_state.state = ResponseState::ACKED;
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: client ACKed resource_type=" << request.type_url()
                  << " version=" << request.version_info();
      } else {
        response_state.state = ResponseState::NACKED;
        if (check_nack_status_code_ != nullptr) {
          check_nack_status_code_(
              static_cast<absl::StatusCode>(request.error_detail().code()));
        }
        response_state.error_message = request.error_detail().message();
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: client NACKed resource_type=" << request.type_url()
                  << " version=" << request.version_info() << ": "
                  << response_state.error_message;
      }
      resource_type_response_state_[request.type_url()].emplace_back(
          std::move(response_state));

      if (client_nonce < sent_state->nonce) return;
    }

    if (resource_types_to_ignore_.find(request.type_url()) !=
        resource_types_to_ignore_.end()) {
      return;
    }

    auto& subscription_name_map = (*subscription_map)[request.type_url()];
    auto& resource_type_state = resource_map_[request.type_url()];
    auto& resource_name_map = resource_type_state.resource_name_map;
    std::set<std::string> resources_in_current_request;
    std::set<std::string> resources_added_to_response;
    for (const std::string& resource_name : request.resource_names()) {
      resources_in_current_request.emplace(resource_name);
      auto& subscription_state = subscription_name_map[resource_name];
      auto& resource_state = resource_name_map[resource_name];

      if (MaybeSubscribe(request.type_url(), resource_name, &subscription_state,
                         &resource_state, update_queue) ||
          ClientNeedsResourceUpdate(resource_type_state, resource_state,
                                    sent_state->resource_type_version)) {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: Sending update for type=" << request.type_url()
                  << " name=" << resource_name;
        resources_added_to_response.emplace(resource_name);
        if (!response->has_value()) response->emplace();
        if (resource_state.resource.has_value()) {
          auto* resource = (*response)->add_resources();
          resource->CopyFrom(resource_state.resource.value());
          if (wrap_resources_) {
            envoy::service::discovery::v3::Resource resource_wrapper;
            *resource_wrapper.mutable_resource() = std::move(*resource);
            resource->PackFrom(resource_wrapper);
          }
        }
      } else {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: client does not need update for type="
                  << request.type_url() << " name=" << resource_name;
      }
    }

    ProcessUnsubscriptions(request.type_url(), resources_in_current_request,
                           &subscription_name_map, &resource_name_map);

    if (!resources_added_to_response.empty()) {
      CompleteBuildingDiscoveryResponse(
          request.type_url(), resource_type_state.resource_type_version,
          subscription_name_map, resources_added_to_response, sent_state,
          &response->value());
    }
  }

  void ProcessUpdate(const std::string& resource_type,
                     const std::string& resource_name,
                     SubscriptionMap* subscription_map, SentState* sent_state,
                     std::optional<DiscoveryResponse>* response)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(ads_mu_) {
    LOG(INFO) << "ADS[" << debug_label_
              << "]: Received update for type=" << resource_type
              << " name=" << resource_name;
    auto& subscription_name_map = (*subscription_map)[resource_type];
    auto& resource_type_state = resource_map_[resource_type];
    auto& resource_name_map = resource_type_state.resource_name_map;
    auto it = subscription_name_map.find(resource_name);
    if (it != subscription_name_map.end()) {
      ResourceState& resource_state = resource_name_map[resource_name];
      if (ClientNeedsResourceUpdate(resource_type_state, resource_state,
                                    sent_state->resource_type_version)) {
        LOG(INFO) << "ADS[" << debug_label_
                  << "]: Sending update for type=" << resource_type
                  << " name=" << resource_name;
        response->emplace();
        if (resource_state.resource.has_value()) {
          auto* resource = (*response)->add_resources();
          resource->CopyFrom(resource_state.resource.value());
        }
        CompleteBuildingDiscoveryResponse(
            resource_type, resource_type_state.resource_type_version,
            subscription_name_map, {resource_name}, sent_state,
            &response->value());
      }
    }
  }

  void BlockingRead(Stream* stream, std::deque<DiscoveryRequest>* requests,
                    bool* stream_closed) {
    DiscoveryRequest request;
    bool seen_first_request = false;
    while (stream->Read(&request)) {
      if (!seen_first_request) {
        if (check_first_request_ != nullptr) {
          check_first_request_(request);
        }
        seen_first_request = true;
      }
      {
        grpc_core::MutexLock lock(&ads_mu_);
        requests->emplace_back(std::move(request));
      }
    }
    LOG(INFO) << "ADS[" << debug_label_ << "]: Null read, stream closed";
    grpc_core::MutexLock lock(&ads_mu_);
    *stream_closed = true;
  }

  void CompleteBuildingDiscoveryResponse(
      const std::string& resource_type, const int version,
      const SubscriptionNameMap& subscription_name_map,
      const std::set<std::string>& resources_added_to_response,
      SentState* sent_state, DiscoveryResponse* response)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(ads_mu_) {
    response->set_type_url(resource_type);
    response->set_version_info(std::to_string(version));
    response->set_nonce(std::to_string(++sent_state->nonce));
    if (resource_type == kLdsTypeUrl || resource_type == kCdsTypeUrl) {

      for (const auto& [resource_name, _] : subscription_name_map) {
        if (resources_added_to_response.find(resource_name) ==
            resources_added_to_response.end()) {
          ResourceNameMap& resource_name_map =
              resource_map_[resource_type].resource_name_map;
          const ResourceState& resource_state =
              resource_name_map[resource_name];
          if (resource_state.resource.has_value()) {
            auto* resource = response->add_resources();
            resource->CopyFrom(resource_state.resource.value());
          }
        }
      }
    }
    sent_state->resource_type_version = version;
  }

  static bool ClientNeedsResourceUpdate(
      const ResourceTypeState& resource_type_state,
      const ResourceState& resource_state, int client_resource_type_version);

  bool MaybeSubscribe(const std::string& resource_type,
                      const std::string& resource_name,
                      SubscriptionState* subscription_state,
                      ResourceState* resource_state, UpdateQueue* update_queue);

  void ProcessUnsubscriptions(
      const std::string& resource_type,
      const std::set<std::string>& resources_in_current_request,
      SubscriptionNameMap* subscription_name_map,
      ResourceNameMap* resource_name_map);

  void AddClient(const std::string& client) {
    grpc_core::MutexLock lock(&clients_mu_);
    clients_.insert(client);
  }

  void RemoveClient(const std::string& client) {
    grpc_core::MutexLock lock(&clients_mu_);
    clients_.erase(client);
  }

  std::function<void(const DiscoveryRequest& request)> check_first_request_;
  std::function<void(absl::StatusCode)> check_nack_status_code_;
  std::string debug_label_;

  grpc_core::CondVar ads_cond_;
  grpc_core::Mutex ads_mu_;
  bool ads_done_ ABSL_GUARDED_BY(ads_mu_) = false;
  std::map<std::string , std::deque<ResponseState>>
      resource_type_response_state_ ABSL_GUARDED_BY(ads_mu_);
  std::set<std::string > resource_types_to_ignore_
      ABSL_GUARDED_BY(ads_mu_);
  std::function<void(absl::string_view, int)> check_version_callback_
      ABSL_GUARDED_BY(ads_mu_);

  ResourceMap resource_map_ ABSL_GUARDED_BY(ads_mu_);
  std::optional<Status> forced_ads_failure_ ABSL_GUARDED_BY(ads_mu_);
  bool wrap_resources_ ABSL_GUARDED_BY(ads_mu_) = false;

  grpc_core::Mutex clients_mu_;
  std::set<std::string> clients_ ABSL_GUARDED_BY(clients_mu_);
};

class LrsServiceImpl
    : public CountedService<
          ::envoy::service::load_stats::v3::LoadReportingService::Service>,
      public std::enable_shared_from_this<LrsServiceImpl> {
 public:
  using LoadStatsRequest = ::envoy::service::load_stats::v3::LoadStatsRequest;
  using LoadStatsResponse = ::envoy::service::load_stats::v3::LoadStatsResponse;

  class ClientStats {
   public:

    struct LocalityStats {
      struct LoadMetric {
        uint64_t num_requests_finished_with_metric = 0;
        double total_metric_value = 0;

        LoadMetric() = default;

        template <typename T>
        explicit LoadMetric(const T& stats)
            : num_requests_finished_with_metric(
                  stats.num_requests_finished_with_metric()),
              total_metric_value(stats.total_metric_value()) {}

        LoadMetric& operator+=(const LoadMetric& other) {
          num_requests_finished_with_metric +=
              other.num_requests_finished_with_metric;
          total_metric_value += other.total_metric_value;
          return *this;
        }
      };

      LocalityStats() {}

      explicit LocalityStats(
          const ::envoy::config::endpoint::v3::UpstreamLocalityStats&
              upstream_locality_stats)
          : total_successful_requests(
                upstream_locality_stats.total_successful_requests()),
            total_requests_in_progress(
                upstream_locality_stats.total_requests_in_progress()),
            total_error_requests(
                upstream_locality_stats.total_error_requests()),
            total_issued_requests(
                upstream_locality_stats.total_issued_requests()),
            cpu_utilization(upstream_locality_stats.cpu_utilization()),
            mem_utilization(upstream_locality_stats.mem_utilization()),
            application_utilization(
                upstream_locality_stats.application_utilization()) {
        for (const auto& s : upstream_locality_stats.load_metric_stats()) {
          load_metrics[s.metric_name()] += LoadMetric(s);
        }
      }

      LocalityStats& operator+=(const LocalityStats& other) {
        total_successful_requests += other.total_successful_requests;
        total_requests_in_progress += other.total_requests_in_progress;
        total_error_requests += other.total_error_requests;
        total_issued_requests += other.total_issued_requests;
        cpu_utilization += other.cpu_utilization;
        mem_utilization += other.mem_utilization;
        application_utilization += other.application_utilization;
        for (const auto& [key, value] : other.load_metrics) {
          load_metrics[key] += value;
        }
        return *this;
      }

      uint64_t total_successful_requests = 0;
      uint64_t total_requests_in_progress = 0;
      uint64_t total_error_requests = 0;
      uint64_t total_issued_requests = 0;
      LoadMetric cpu_utilization;
      LoadMetric mem_utilization;
      LoadMetric application_utilization;
      std::map<std::string, LoadMetric> load_metrics;
    };

    ClientStats() {}

    explicit ClientStats(
        const ::envoy::config::endpoint::v3::ClusterStats& cluster_stats)
        : cluster_name_(cluster_stats.cluster_name()),
          eds_service_name_(cluster_stats.cluster_service_name()),
          total_dropped_requests_(cluster_stats.total_dropped_requests()) {
      for (const auto& input_locality_stats :
           cluster_stats.upstream_locality_stats()) {
        locality_stats_.emplace(input_locality_stats.locality().sub_zone(),
                                LocalityStats(input_locality_stats));
      }
      for (const auto& input_dropped_requests :
           cluster_stats.dropped_requests()) {
        dropped_requests_.emplace(input_dropped_requests.category(),
                                  input_dropped_requests.dropped_count());
      }
    }

    const std::string& cluster_name() const { return cluster_name_; }
    const std::string& eds_service_name() const { return eds_service_name_; }

    const std::map<std::string, LocalityStats>& locality_stats() const {
      return locality_stats_;
    }

    uint64_t total_successful_requests() const;
    uint64_t total_requests_in_progress() const;
    uint64_t total_error_requests() const;
    uint64_t total_issued_requests() const;

    uint64_t total_dropped_requests() const { return total_dropped_requests_; }

    uint64_t dropped_requests(const std::string& category) const;

    ClientStats& operator+=(const ClientStats& other);

   private:
    std::string cluster_name_;
    std::string eds_service_name_;
    std::map<std::string, LocalityStats> locality_stats_;
    uint64_t total_dropped_requests_ = 0;
    std::map<std::string, uint64_t> dropped_requests_;
  };

  LrsServiceImpl(int client_load_reporting_interval_seconds,
                 std::set<std::string> cluster_names,
                 std::function<void()> stream_started_callback = nullptr,
                 std::function<void(const LoadStatsRequest& request)>
                     check_first_request = nullptr,
                 absl::string_view debug_label = "")
      : client_load_reporting_interval_seconds_(
            client_load_reporting_interval_seconds),
        cluster_names_(std::move(cluster_names)),
        stream_started_callback_(std::move(stream_started_callback)),
        check_first_request_(std::move(check_first_request)),
        debug_label_(absl::StrFormat(
            "%p%s%s", this, debug_label.empty() ? "" : ":", debug_label)) {}

  void set_send_all_clusters(bool send_all_clusters) {
    send_all_clusters_ = send_all_clusters;
  }
  void set_cluster_names(const std::set<std::string>& cluster_names) {
    cluster_names_ = cluster_names;
  }

  void Start() ABSL_LOCKS_EXCLUDED(lrs_mu_, load_report_mu_);

  void Shutdown();

  std::vector<ClientStats> WaitForLoadReport(
      absl::Duration timeout = absl::InfiniteDuration());

 private:
  using Stream = ServerReaderWriter<LoadStatsResponse, LoadStatsRequest>;

  Status StreamLoadStats(ServerContext* , Stream* stream) override {
    LOG(INFO) << "LRS[" << debug_label_ << "]: StreamLoadStats starts";
    if (stream_started_callback_ != nullptr) stream_started_callback_();

    std::shared_ptr<LrsServiceImpl> lrs_service_impl = shared_from_this();

    LoadStatsRequest request;
    if (stream->Read(&request)) {
      IncreaseRequestCount();
      if (check_first_request_ != nullptr) check_first_request_(request);

      LoadStatsResponse response;
      if (send_all_clusters_) {
        response.set_send_all_clusters(true);
      } else {
        for (const std::string& cluster_name : cluster_names_) {
          response.add_clusters(cluster_name);
        }
      }
      response.mutable_load_reporting_interval()->set_seconds(
          client_load_reporting_interval_seconds_ *
          grpc_test_slowdown_factor());
      stream->Write(response);
      IncreaseResponseCount();

      request.Clear();
      while (stream->Read(&request)) {
        LOG(INFO) << "LRS[" << debug_label_
                  << "]: received client load report message: "
                  << request.DebugString();
        std::vector<ClientStats> stats;
        for (const auto& cluster_stats : request.cluster_stats()) {
          stats.emplace_back(cluster_stats);
        }
        grpc_core::MutexLock lock(&load_report_mu_);
        result_queue_.emplace_back(std::move(stats));
        if (load_report_cond_ != nullptr) {
          load_report_cond_->Signal();
        }
      }

      grpc_core::MutexLock lock(&lrs_mu_);
      while (!lrs_done_) {
        lrs_cv_.Wait(&lrs_mu_);
      }
    }
    LOG(INFO) << "LRS[" << debug_label_ << "]: StreamLoadStats done";
    return Status::OK;
  }

  const int client_load_reporting_interval_seconds_;
  bool send_all_clusters_ = false;
  std::set<std::string> cluster_names_;
  std::function<void()> stream_started_callback_;
  std::function<void(const LoadStatsRequest& request)> check_first_request_;
  std::string debug_label_;

  grpc_core::CondVar lrs_cv_;
  grpc_core::Mutex lrs_mu_;
  bool lrs_done_ ABSL_GUARDED_BY(lrs_mu_) = false;

  grpc_core::Mutex load_report_mu_;
  grpc_core::CondVar* load_report_cond_ ABSL_GUARDED_BY(load_report_mu_) =
      nullptr;
  std::deque<std::vector<ClientStats>> result_queue_
      ABSL_GUARDED_BY(load_report_mu_);
};

}
}

#endif
