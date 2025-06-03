Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/cpp/server/load_reporter/load_data_store.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdio.h>

#include <cstdlib>
#include <iterator>
#include <set>
#include <unordered_map>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/cpp/server/load_reporter/constants.h"

namespace grpc {
namespace load_reporter {

namespace {

// Helper function to erase a value from a set within an unordered_map.
// If the set becomes empty after erasure, removes the key from the map.
// Returns true if the value was found and erased, false otherwise.
template <typename K, typename V>
bool UnorderedMapOfSetEraseKeyValue(std::unordered_map<K, std::set<V>>& map,
                                    const K& key, const V& value) {
  auto it = map.find(key);
  if (it != map.end()) {
    size_t erased = it->second.erase(value);
    if (it->second.empty()) {
      map.erase(it);
    }
    return erased;
  }
  return false;
};

// Helper function to extract and remove a set associated with a key from an unordered_map.
// Returns the extracted set if found, or an empty set otherwise.
template <typename K, typename V>
std::set<V> UnorderedMapOfSetExtract(std::unordered_map<K, std::set<V>>& map,
                                     const K& key) {
  auto it = map.find(key);
  if (it != map.end()) {
    auto set = std::move(it->second);
    map.erase(it);
    return set;
  }
  return {};
};

// Helper function to get a random element from a container.
// The container must not be empty.
template <typename C>
const typename C::value_type* RandomElement(const C& container) {
  CHECK(!container.empty());
  auto it = container.begin();
  std::advance(it, std::rand() % container.size());
  return &(*it);
}

}  // namespace

// Constructs a LoadRecordKey from client IP and token string and user ID.
// The input string is expected to have a specific format:
// - First 2 chars represent IP hex size (0, 4 for IPv4, or 16 for IPv6)
// - Next N chars (based on IP size) represent the IP address in hex
// - Remaining chars represent LB ID and tag
LoadRecordKey::LoadRecordKey(const std::string& client_ip_and_token,
                             std::string user_id)
    : user_id_(std::move(user_id)) {
  CHECK_GE(client_ip_and_token.size(), 2u);
  int ip_hex_size;
  CHECK(sscanf(client_ip_and_token.substr(0, 2).c_str(), "%d", &ip_hex_size) ==
        1);
  CHECK(ip_hex_size == 0 || ip_hex_size == kIpv4AddressLength ||
        ip_hex_size == kIpv6AddressLength);
  size_t cur_pos = 2;
  client_ip_hex_ = client_ip_and_token.substr(cur_pos, ip_hex_size);
  cur_pos += ip_hex_size;
  if (client_ip_and_token.size() - cur_pos < kLbIdLength) {
    lb_id_ = kInvalidLbId;
    lb_tag_ = "";
  } else {
    lb_id_ = client_ip_and_token.substr(cur_pos, kLbIdLength);
    lb_tag_ = client_ip_and_token.substr(cur_pos + kLbIdLength);
  }
}

// Converts the stored hex IP address to bytes in network byte order.
// Returns empty string if conversion fails.
std::string LoadRecordKey::GetClientIpBytes() const {
  if (client_ip_hex_.empty()) {
    return "";
  } else if (client_ip_hex_.size() == kIpv4AddressLength) {
    uint32_t ip_bytes;
    if (sscanf(client_ip_hex_.c_str(), "%x", &ip_bytes) != 1) {
      LOG(ERROR) << "Can't parse client IP (" << client_ip_hex_
                 << ") from a hex string to an integer.";
      return "";
    }
    ip_bytes = grpc_htonl(ip_bytes);
    return std::string(reinterpret_cast<const char*>(&ip_bytes),
                       sizeof(ip_bytes));
  } else if (client_ip_hex_.size() == kIpv6AddressLength) {
    uint32_t ip_bytes[4];
    for (size_t i = 0; i < 4; ++i) {
      if (sscanf(client_ip_hex_.substr(i * 8, (i + 1) * 8).c_str(), "%x",
                 ip_bytes + i) != 1) {
        LOG(ERROR) << "Can't parse client IP part ("
                   << client_ip_hex_.substr(i * 8, (i + 1) * 8)
                   << ") from a hex string to an integer.";
        return "";
      }
      ip_bytes[i] = grpc_htonl(ip_bytes[i]);
    }
    return std::string(reinterpret_cast<const char*>(ip_bytes),
                       sizeof(ip_bytes));
  } else {
    GPR_UNREACHABLE_CODE(return "");
  }
}

// Constructs a LoadRecordValue with a single metric.
LoadRecordValue::LoadRecordValue(std::string metric_name, uint64_t num_calls,
                                 double total_metric_value) {
  call_metrics_.emplace(std::move(metric_name),
                        CallMetricValue(num_calls, total_metric_value));
}

// Merges a load record into this store if not suspended.
// Updates the count of calls in progress.
void PerBalancerStore::MergeRow(const LoadRecordKey& key,
                                const LoadRecordValue& value) {
  if (!suspended_) {
    load_record_map_[key].MergeFrom(value);
    VLOG(2) << "[PerBalancerStore " << this
            << "] Load data merged (Key: " << key.ToString()
            << ", Value: " << value.ToString() << ").";
  } else {
    VLOG(2) << "[PerBalancerStore " << this
            << "] Load data dropped (Key: " << key.ToString()
            << ", Value: " << value.ToString() << ").";
  }

  CHECK(static_cast<int64_t>(num_calls_in_progress_) +
            value.GetNumCallsInProgressDelta() >=
        0);
  num_calls_in_progress_ += value.GetNumCallsInProgressDelta();
}

// Suspends this store, clearing all load records.
void PerBalancerStore::Suspend() {
  suspended_ = true;
  load_record_map_.clear();
  VLOG(2) << "[PerBalancerStore " << this << "] Suspended.";
}

// Resumes this store after suspension.
void PerBalancerStore::Resume() {
  suspended_ = false;
  VLOG(2) << "[PerBalancerStore " << this << "] Resumed.";
}

// Returns the current number of calls in progress and updates last reported value.
uint64_t PerBalancerStore::GetNumCallsInProgressForReport() {
  CHECK(!suspended_);
  last_reported_num_calls_in_progress_ = num_calls_in_progress_;
  return num_calls_in_progress_;
}

// Handles creation of a new load reporting stream for a balancer.
// Sets up tracking for the new LB ID and may reassign orphaned stores.
void PerHostStore::ReportStreamCreated(const std::string& lb_id,
                                       const std::string& load_key) {
  CHECK(lb_id != kInvalidLbId);
  SetUpForNewLbId(lb_id, load_key);

  // If this is the first assigned store, resume and reassign any orphaned stores
  if (assigned_stores_.size() == 1) {
    for (const auto& p : per_balancer_stores_) {
      const std::string& other_lb_id = p.first;
      const std::unique_ptr<PerBalancerStore>& orphaned_store = p.second;
      if (other_lb_id != lb_id) {
        orphaned_store->Resume();
        AssignOrphanedStore(orphaned_store.get(), lb_id);
      }
    }
  }

  // Special case for single balancer - set up invalid LB ID tracking
  if (per_balancer_stores_.size() == 1) {
    SetUpForNewLbId(kInvalidLbId, "");
    ReportStreamClosed(kInvalidLbId);
  }
}

// Handles closure of a load reporting stream for a balancer.
// Cleans up tracking and reassigns any orphaned stores to remaining balancers.
void PerHostStore::ReportStreamClosed(const std::string& lb_id) {
  auto it_store_for_gone_lb = per_balancer_stores_.find(lb_id);
  CHECK(it_store_for_gone_lb != per_balancer_stores_.end());

  // Clean up load key mapping and get orphaned stores
  CHECK(UnorderedMapOfSetEraseKeyValue(load_key_to_receiving_lb_ids_,
                                       it_store_for_gone_lb->second->load_key(),
                                       lb_id));
  std::set<PerBalancerStore*> orphaned_stores =
      UnorderedMapOfSetExtract(assigned_stores_, lb_id);

  // Reassign orphaned stores to new balancers if possible
  for (PerBalancerStore* orphaned_store : orphaned_stores) {
    const std::string* new_receiver = nullptr;
    auto it = load_key_to_receiving_lb_ids_.find(orphaned_store->load_key());
    if (it != load_key_to_receiving_lb_ids_.end()) {
      // Prefer balancers with matching load key
      new_receiver = RandomElement(it->second);
    } else if (!assigned_stores_.empty()) {
      // Fall back to any available balancer
      new_receiver = &(RandomElement(assigned_stores_)->first);
    }
    if (new_receiver != nullptr) {
      AssignOrphanedStore(orphaned_store, *new_receiver);
    } else {
      // No available receivers - suspend the store
      orphaned_store->Suspend();
    }
  }
}

// Finds a PerBalancerStore by LB ID, returns nullptr if not found.
PerBalancerStore* PerHostStore::FindPerBalancerStore(
    const std::string& lb_id) const {
  return per_balancer_stores_.find(lb_id) != per_balancer_stores_.end()
             ? per_balancer_stores_.find(lb_id)->second.get()
             : nullptr;
}

// Gets the set of stores assigned to a balancer, returns nullptr if not found.
const std::set<PerBalancerStore*>* PerHostStore::GetAssignedStores(
    const std::string& lb_id) const {
  auto it = assigned_stores_.find(lb_id);
  if (it == assigned_stores_.end()) return nullptr;
  return &(it->second);
}

// Assigns an orphaned store to a new balancer.
void PerHostStore::AssignOrphanedStore(PerBalancerStore* orphaned_store,
                                       const std::string& new_receiver) {
  auto it = assigned_stores_.find(new_receiver);
  CHECK(it != assigned_stores_.end());
  it->second.insert(orphaned_store);
  LOG(INFO) << "[PerHostStore " << this << "] Re-assigned orphaned store ("
            << orphaned_store << ") with original LB ID of "
            << orphaned_store->lb_id() << " to new receiver " << new_receiver;
}

// Sets up tracking for a new balancer ID with the given load key.
void PerHostStore::SetUpForNewLbId(const std::string& lb_id,
                                   const std::string& load_key) {
  CHECK(per_balancer_stores_.find(lb_id) == per_balancer_stores_.end());
  CHECK(assigned_stores_.find(lb_id) == assigned_stores_.end());
  load_key_to_receiving_lb_ids_[load_key].insert(lb_id);
  std::unique_ptr<PerBalancerStore> per_balancer_store(
      new PerBalancerStore(lb_id, load_key));
  assigned_stores_[lb_id] = {per_balancer_store.get()};
  per_balancer_stores_[lb_id] = std::move(per_balancer_store);
}

// Finds a PerBalancerStore by hostname and LB ID, returns nullptr if not found.
PerBalancerStore* LoadDataStore::FindPerBalancerStore(
    const string& hostname, const string& lb_id) const {
  auto it = per_host_stores_.find(hostname);
  if (it != per_host_stores_.end()) {
    const PerHostStore& per_host_store = it->second;
    return per_host_store.FindPerBalancerStore(lb_id);
  } else {
    return nullptr;
  }
}

// Merges a load record into the appropriate store.
// Handles unknown balancer IDs by tracking their call counts separately.
void LoadDataStore::MergeRow(const std::string& hostname,
                             const LoadRecordKey& key,
                             const LoadRecordValue& value) {
  PerBalancerStore* per_balancer_store =
      FindPerBalancerStore(hostname, key.lb_id());
  if (per_balancer_store != nullptr) {
    per_balancer_store->MergeRow(key, value);
    return;
  }

  // Handle unknown balancer IDs by tracking their call counts
  int64_t in_progress_delta = value.GetNumCallsInProgressDelta();
  if (in_progress_delta != 0) {
    auto it_tracker = unknown_balancer_id_trackers_.find(key.lb_id());
    if (it_tracker == unknown_balancer_id_trackers_.end()) {
      VLOG(2) << "[LoadDataStore " << this
              << "] Start tracking unknown balancer (lb_id_: " << key.lb_id()
              << ").";
      unknown_balancer_id_trackers_.insert(
          {key.lb_id(), static_cast<uint64_t>(in_progress_delta)});
    } else if ((it_tracker->second += in_progress_delta) == 0) {
      unknown_balancer_id_trackers_.erase(it_tracker);
      VLOG(2) << "[LoadDataStore " << this
              << "] Stop tracking unknown balancer (lb_id_: " << key.lb_id()
              << ").";
    }
  }
}

// Gets the stores assigned to a balancer for a specific host.
const std::set<PerBalancerStore*>* LoadDataStore::GetAssignedStores(
    const std::string& hostname, const std::string& lb_id) {
  auto it = per_host_stores_.find(hostname);
  if (it == per_host_stores_.end()) return nullptr;
  return it->second.GetAssignedStores(lb_id);
}

// Handles creation of a new load reporting stream for a host and balancer.
void LoadDataStore::ReportStreamCreated(const std::string& hostname,
                                        const std::string& lb_id,
                                        const std::string& load_key) {
  per_host_stores_[hostname].ReportStreamCreated(lb_id, load_key);
}

// Handles closure of a load reporting stream for a host and balancer.
void LoadDataStore::ReportStreamClosed(const std::string& hostname,
                                       const std::string& lb_id) {
  auto it_per_host_store = per_host_stores_.find(hostname);
  CHECK(it_per_host_store != per_host_stores_.end());
  it_per_host_store->second.ReportStreamClosed(lb_id);
}

}  // namespace load_reporter
}  // namespace grpc
```