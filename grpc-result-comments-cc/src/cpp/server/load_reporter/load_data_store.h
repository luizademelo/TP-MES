Here's the commented version of the code:

```c++
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

// Represents the metric value for a call, tracking both the number of calls
// and the total metric value across those calls.
class CallMetricValue {
 public:
  // Constructs a CallMetricValue with optional initial values.
  explicit CallMetricValue(uint64_t num_calls = 0,
                           double total_metric_value = 0)
      : num_calls_(num_calls), total_metric_value_(total_metric_value) {}

  // Merges another CallMetricValue into this one by summing the counts and values.
  void MergeFrom(CallMetricValue other) {
    num_calls_ += other.num_calls_;
    total_metric_value_ += other.total_metric_value_;
  }

  // Accessors for the metric values
  uint64_t num_calls() const { return num_calls_; }
  double total_metric_value() const { return total_metric_value_; }

 private:
  // Number of calls this metric represents
  uint64_t num_calls_ = 0;
  // Sum of all metric values across the calls
  double total_metric_value_ = 0;
};

// Represents a key for load records, containing load balancing identifiers
// and client information.
class LoadRecordKey {
 public:
  // Constructs a LoadRecordKey with all required fields
  LoadRecordKey(std::string lb_id, std::string lb_tag, std::string user_id,
                std::string client_ip_hex)
      : lb_id_(std::move(lb_id)),
        lb_tag_(std::move(lb_tag)),
        user_id_(std::move(user_id)),
        client_ip_hex_(std::move(client_ip_hex)) {}

  // Alternative constructor that parses client IP and token
  LoadRecordKey(const std::string& client_ip_and_token, std::string user_id);

  // Returns a string representation of the key
  std::string ToString() const {
    return "[lb_id_=" + lb_id_ + ", lb_tag_=" + lb_tag_ +
           ", user_id_=" + user_id_ + ", client_ip_hex_=" + client_ip_hex_ +
           "]";
  }

  // Equality comparison operator
  bool operator==(const LoadRecordKey& other) const {
    return lb_id_ == other.lb_id_ && lb_tag_ == other.lb_tag_ &&
           user_id_ == other.user_id_ && client_ip_hex_ == other.client_ip_hex_;
  }

  // Converts the hex client IP to bytes
  std::string GetClientIpBytes() const;

  // Accessors for the key components
  const std::string& lb_id() const { return lb_id_; }
  const std::string& lb_tag() const { return lb_tag_; }
  const std::string& user_id() const { return user_id_; }
  const std::string& client_ip_hex() const { return client_ip_hex_; }

  // Custom hash implementation for LoadRecordKey to enable use in unordered_map
  struct Hasher {
    // Helper function for combining hashes
    void hash_combine(size_t* seed, const std::string& k) const {
      *seed ^= std::hash<std::string>()(k) + 0x9e3779b9 + (*seed << 6) +
               (*seed >> 2);
    }

    // Computes hash for a LoadRecordKey
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
  std::string lb_id_;          // Load balancer ID
  std::string lb_tag_;         // Load balancer tag
  std::string user_id_;        // User identifier
  std::string client_ip_hex_;  // Client IP address in hexadecimal
};

// Represents the value associated with a load record, containing call statistics
// and metrics.
class LoadRecordValue {
 public:
  // Constructs a LoadRecordValue with optional initial values for call statistics
  explicit LoadRecordValue(uint64_t start_count = 0, uint64_t ok_count = 0,
                           uint64_t error_count = 0, uint64_t bytes_sent = 0,
                           uint64_t bytes_recv = 0, uint64_t latency_ms = 0)
      : start_count_(start_count),
        ok_count_(ok_count),
        error_count_(error_count),
        bytes_sent_(bytes_sent),
        bytes_recv_(bytes_recv),
        latency_ms_(latency_ms) {}

  // Alternative constructor for metric-based initialization
  LoadRecordValue(std::string metric_name, uint64_t num_calls,
                  double total_metric_value);

  // Merges another LoadRecordValue into this one by summing all counts and metrics
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

  // Calculates the delta of calls in progress (started but not completed)
  int64_t GetNumCallsInProgressDelta() const {
    return static_cast<int64_t>(start_count_ - ok_count_ - error_count_);
  }

  // Returns a string representation of the value
  std::string ToString() const {
    return "[start_count_=" + std::to_string(start_count_) +
           ", ok_count_=" + std::to_string(ok_count_) +
           ", error_count_=" + std::to_string(error_count_) +
           ", bytes_sent_=" + std::to_string(bytes_sent_) +
           ", bytes_recv_=" + std::to_string(bytes_recv_) +
           ", latency_ms_=" + std::to_string(latency_ms_) + ", " +
           std::to_string(call_metrics_.size()) + " other call metric(s)]";
  }

  // Inserts a new call metric into the record
  bool InsertCallMetric(const std::string& metric_name,
                        const CallMetricValue& metric_value) {
    return call_metrics_.insert({metric_name, metric_value}).second;
  }

  // Accessors for the value components
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
  uint64_t start_count_ = 0;   // Number of calls started
  uint64_t ok_count_ = 0;      // Number of successful calls
  uint64_t error_count_ = 0;   // Number of failed calls
  uint64_t bytes_sent_ = 0;    // Total bytes sent
  uint64_t bytes_recv_ = 0;    // Total bytes received
  uint64_t latency_ms_ = 0;    // Total latency in milliseconds
  // Map of additional call metrics by name
  std::unordered_map<std::string, CallMetricValue> call_metrics_;
};

// Manages load data for a specific load balancer
class PerBalancerStore {
 public:
  // Type alias for the map storing load records
  using LoadRecordMap =
      std::unordered_map<LoadRecordKey, LoadRecordValue, LoadRecordKey::Hasher>;

  // Constructs a PerBalancerStore with the given load balancer ID and load key
  PerBalancerStore(std::string lb_id, std::string load_key)
      : lb_id_(std::move(lb_id)), load_key_(std::move(load_key)) {}

  // Merges a load record into the store
  void MergeRow(const LoadRecordKey& key, const LoadRecordValue& value);

  // Suspends tracking for this load balancer
  void Suspend();

  // Resumes tracking for this load balancer
  void Resume();

  // Checks if this store is currently suspended
  bool IsSuspended() const { return suspended_; }

  // Checks if the number of calls in progress has changed since last report
  bool IsNumCallsInProgressChangedSinceLastReport() const {
    return num_calls_in_progress_ != last_reported_num_calls_in_progress_;
  }

  // Gets the current number of calls in progress and updates last reported value
  uint64_t GetNumCallsInProgressForReport();

  // Returns a string representation of the store
  std::string ToString() {
    return "[PerBalancerStore lb_id_=" + lb_id_ + " load_key_=" + load_key_ +
           "]";
  }

  // Clears all load records
  void ClearLoadRecordMap() { load_record_map_.clear(); }

  // Accessors for store properties
  const std::string& lb_id() const { return lb_id_; }
  const std::string& load_key() const { return load_key_; }
  const LoadRecordMap& load_record_map() const { return load_record_map_; }

 private:
  std::string lb_id_;          // Load balancer identifier
  std::string load_key_;       // Key used for load reporting
  LoadRecordMap load_record_map_;  // Map of load records
  uint64_t num_calls_in_progress_ = 0;  // Current calls in progress
  uint64_t last_reported_num_calls_in_progress_ = 0;  // Last reported value
  bool suspended_ = false;      // Suspension state
};

// Manages load data stores for each host
class PerHostStore {
 public:
  // Reports that a stream was created for a specific load balancer
  void ReportStreamCreated(const std::string& lb_id,
                           const std::string& load_key);

  // Reports that a stream was closed for a specific load balancer
  void ReportStreamClosed(const std::string& lb_id);

  // Finds the store for a specific load balancer
  PerBalancerStore* FindPerBalancerStore(const std::string& lb_id) const;

  // Gets all stores assigned to a specific load balancer
  const std::set<PerBalancerStore*>* GetAssignedStores(
      const std::string& lb_id) const;

 private:
  // Sets up tracking for a new load balancer ID
  void SetUpForNewLbId(const std::string& lb_id, const std::string& load_key);

  // Assigns an orphaned store to a new receiver
  void AssignOrphanedStore(PerBalancerStore* orphaned_store,
                           const std::string& new_receiver);

  // Maps load keys to the set of receiving load balancer IDs
  std::unordered_map<std::string, std::set<std::string>>
      load_key_to_receiving_lb_ids_;

  // Map of all per-balancer stores by load balancer ID
  std::unordered_map<std::string, std::unique_ptr<PerBalancerStore>>
      per_balancer_stores_;

  // Map of assigned stores by load balancer ID
  std::unordered_map<std::string, std::set<PerBalancerStore*>> assigned_stores_;
};

// Main class for managing all load data across hosts and load balancers
class LoadDataStore {
 public:
  // Finds a specific per-balancer store for a host
  PerBalancerStore* FindPerBalancerStore(const std::string& hostname,
                                         const std::string& lb_id) const;

  // Gets all assigned stores for a host and load balancer
  const std::set<PerBalancerStore*>* GetAssignedStores(const string& hostname,
                                                       const string& lb_id);

  // Merges a load record into the appropriate store
  void MergeRow(const std::string& hostname, const LoadRecordKey& key,
                const LoadRecordValue& value);

  // Checks if a load balancer ID is being tracked as unknown
  bool IsTrackedUnknownBalancerId(const std::string& lb_id) const {
    return unknown_balancer_id_trackers_.find(lb_id) !=
           unknown_balancer_id_trackers_.end();
  }

  // Reports that a stream was created for a host and load balancer
  void ReportStreamCreated(const std::string& hostname,
                           const std::string& lb_id,
                           const std::string& load_key);

  // Reports that a stream was closed for a host and load balancer
  void ReportStreamClosed(const std::string& hostname,
                          const std::string& lb_id);

 private:
  // Map of per-host stores by hostname
  std::unordered_map<std::string, PerHostStore> per_host_stores_;

  // Tracks unknown load balancer IDs and their counts
  std::unordered_map<std::string, uint64_t> unknown_balancer_id_trackers_;
};

}  // namespace load_reporter
}  // namespace grpc

#endif
```