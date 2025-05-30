
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_DATA_STORE_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_DATA_STORE_H

#include <grpc/support/port_platform.h>
#include <grpcpp/support/config.h>
#include <stddef.h>
#include <stdint.h>

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>

namespace grpc {
namespace load_reporter {

class CallMetricValue {
 public:
  explicit CallMetricValue(uint64_t num_calls = 0,
                           double total_metric_value = 0)
      : num_calls_(num_calls), total_metric_value_(total_metric_value) {}

  void MergeFrom(CallMetricValue other) {
    num_calls_ += other.num_calls_;
    total_metric_value_ += other.total_metric_value_;
  }

  uint64_t num_calls() const { return num_calls_; }
  double total_metric_value() const { return total_metric_value_; }

 private:

  uint64_t num_calls_ = 0;

  double total_metric_value_ = 0;
};

class LoadRecordKey {
 public:
  LoadRecordKey(std::string lb_id, std::string lb_tag, std::string user_id,
                std::string client_ip_hex)
      : lb_id_(std::move(lb_id)),
        lb_tag_(std::move(lb_tag)),
        user_id_(std::move(user_id)),
        client_ip_hex_(std::move(client_ip_hex)) {}

  LoadRecordKey(const std::string& client_ip_and_token, std::string user_id);

  std::string ToString() const {
    return "[lb_id_=" + lb_id_ + ", lb_tag_=" + lb_tag_ +
           ", user_id_=" + user_id_ + ", client_ip_hex_=" + client_ip_hex_ +
           "]";
  }

  bool operator==(const LoadRecordKey& other) const {
    return lb_id_ == other.lb_id_ && lb_tag_ == other.lb_tag_ &&
           user_id_ == other.user_id_ && client_ip_hex_ == other.client_ip_hex_;
  }

  std::string GetClientIpBytes() const;

  const std::string& lb_id() const { return lb_id_; }
  const std::string& lb_tag() const { return lb_tag_; }
  const std::string& user_id() const { return user_id_; }
  const std::string& client_ip_hex() const { return client_ip_hex_; }

  struct Hasher {
    void hash_combine(size_t* seed, const std::string& k) const {
      *seed ^= std::hash<std::string>()(k) + 0x9e3779b9 + (*seed << 6) +
               (*seed >> 2);
    }

    size_t operator()(const LoadRecordKey& k) const {
      size_t h = 0;
      hash_combine(&h, k.lb_id_);
      hash_combine(&h, k.lb_tag_);
      hash_combine(&h, k.user_id_);
      hash_combine(&h, k.client_ip_hex_);
      return h;
    }
  };

 private:
  std::string lb_id_;
  std::string lb_tag_;
  std::string user_id_;
  std::string client_ip_hex_;
};

class LoadRecordValue {
 public:
  explicit LoadRecordValue(uint64_t start_count = 0, uint64_t ok_count = 0,
                           uint64_t error_count = 0, uint64_t bytes_sent = 0,
                           uint64_t bytes_recv = 0, uint64_t latency_ms = 0)
      : start_count_(start_count),
        ok_count_(ok_count),
        error_count_(error_count),
        bytes_sent_(bytes_sent),
        bytes_recv_(bytes_recv),
        latency_ms_(latency_ms) {}

  LoadRecordValue(std::string metric_name, uint64_t num_calls,
                  double total_metric_value);

  void MergeFrom(const LoadRecordValue& other) {
    start_count_ += other.start_count_;
    ok_count_ += other.ok_count_;
    error_count_ += other.error_count_;
    bytes_sent_ += other.bytes_sent_;
    bytes_recv_ += other.bytes_recv_;
    latency_ms_ += other.latency_ms_;
    for (const auto& p : other.call_metrics_) {
      const std::string& key = p.first;
      const CallMetricValue& value = p.second;
      call_metrics_[key].MergeFrom(value);
    }
  }

  int64_t GetNumCallsInProgressDelta() const {
    return static_cast<int64_t>(start_count_ - ok_count_ - error_count_);
  }

  std::string ToString() const {
    return "[start_count_=" + std::to_string(start_count_) +
           ", ok_count_=" + std::to_string(ok_count_) +
           ", error_count_=" + std::to_string(error_count_) +
           ", bytes_sent_=" + std::to_string(bytes_sent_) +
           ", bytes_recv_=" + std::to_string(bytes_recv_) +
           ", latency_ms_=" + std::to_string(latency_ms_) + ", " +
           std::to_string(call_metrics_.size()) + " other call metric(s)]";
  }

  bool InsertCallMetric(const std::string& metric_name,
                        const CallMetricValue& metric_value) {
    return call_metrics_.insert({metric_name, metric_value}).second;
  }

  uint64_t start_count() const { return start_count_; }
  uint64_t ok_count() const { return ok_count_; }
  uint64_t error_count() const { return error_count_; }
  uint64_t bytes_sent() const { return bytes_sent_; }
  uint64_t bytes_recv() const { return bytes_recv_; }
  uint64_t latency_ms() const { return latency_ms_; }
  const std::unordered_map<std::string, CallMetricValue>& call_metrics() const {
    return call_metrics_;
  }

 private:
  uint64_t start_count_ = 0;
  uint64_t ok_count_ = 0;
  uint64_t error_count_ = 0;
  uint64_t bytes_sent_ = 0;
  uint64_t bytes_recv_ = 0;
  uint64_t latency_ms_ = 0;
  std::unordered_map<std::string, CallMetricValue> call_metrics_;
};

class PerBalancerStore {
 public:
  using LoadRecordMap =
      std::unordered_map<LoadRecordKey, LoadRecordValue, LoadRecordKey::Hasher>;

  PerBalancerStore(std::string lb_id, std::string load_key)
      : lb_id_(std::move(lb_id)), load_key_(std::move(load_key)) {}

  void MergeRow(const LoadRecordKey& key, const LoadRecordValue& value);

  void Suspend();

  void Resume();

  bool IsSuspended() const { return suspended_; }

  bool IsNumCallsInProgressChangedSinceLastReport() const {
    return num_calls_in_progress_ != last_reported_num_calls_in_progress_;
  }

  uint64_t GetNumCallsInProgressForReport();

  std::string ToString() {
    return "[PerBalancerStore lb_id_=" + lb_id_ + " load_key_=" + load_key_ +
           "]";
  }

  void ClearLoadRecordMap() { load_record_map_.clear(); }

  const std::string& lb_id() const { return lb_id_; }
  const std::string& load_key() const { return load_key_; }
  const LoadRecordMap& load_record_map() const { return load_record_map_; }

 private:
  std::string lb_id_;

  std::string load_key_;
  LoadRecordMap load_record_map_;
  uint64_t num_calls_in_progress_ = 0;
  uint64_t last_reported_num_calls_in_progress_ = 0;
  bool suspended_ = false;
};

class PerHostStore {
 public:

  void ReportStreamCreated(const std::string& lb_id,
                           const std::string& load_key);

  void ReportStreamClosed(const std::string& lb_id);

  PerBalancerStore* FindPerBalancerStore(const std::string& lb_id) const;

  const std::set<PerBalancerStore*>* GetAssignedStores(
      const std::string& lb_id) const;

 private:

  void SetUpForNewLbId(const std::string& lb_id, const std::string& load_key);

  void AssignOrphanedStore(PerBalancerStore* orphaned_store,
                           const std::string& new_receiver);

  std::unordered_map<std::string, std::set<std::string>>
      load_key_to_receiving_lb_ids_;

  std::unordered_map<std::string, std::unique_ptr<PerBalancerStore>>
      per_balancer_stores_;

  std::unordered_map<std::string, std::set<PerBalancerStore*>> assigned_stores_;
};

// Note: We never remove any store objects from this class, as per the

class LoadDataStore {
 public:

  PerBalancerStore* FindPerBalancerStore(const std::string& hostname,
                                         const std::string& lb_id) const;

  const std::set<PerBalancerStore*>* GetAssignedStores(const string& hostname,
                                                       const string& lb_id);

  void MergeRow(const std::string& hostname, const LoadRecordKey& key,
                const LoadRecordValue& value);

  bool IsTrackedUnknownBalancerId(const std::string& lb_id) const {
    return unknown_balancer_id_trackers_.find(lb_id) !=
           unknown_balancer_id_trackers_.end();
  }

  void ReportStreamCreated(const std::string& hostname,
                           const std::string& lb_id,
                           const std::string& load_key);

  void ReportStreamClosed(const std::string& hostname,
                          const std::string& lb_id);

 private:

  std::unordered_map<std::string, PerHostStore> per_host_stores_;

  std::unordered_map<std::string, uint64_t> unknown_balancer_id_trackers_;
};

}
}

#endif
