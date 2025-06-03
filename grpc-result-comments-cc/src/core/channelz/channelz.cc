Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/channelz/channelz.h"

#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <string>
#include <tuple>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/strip.h"
#include "src/core/channelz/channelz_registry.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/notification.h"
#include "src/core/util/string.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace channelz {

// DataSinkImplementation class methods

// Adds additional information to the data sink with a given name
void DataSinkImplementation::AddAdditionalInfo(absl::string_view name,
                                               Json::Object additional_info) {
  MutexLock lock(&mu_);
  additional_info_.emplace(std::string(name), std::move(additional_info));
}

// Adds child objects to the data sink
void DataSinkImplementation::AddChildObjects(
    std::vector<RefCountedPtr<BaseNode>> child_objects) {
  MutexLock lock(&mu_);
  for (auto& node : child_objects) {
    child_objects_.push_back(std::move(node));
  }
}

// Finalizes the data collection, optionally marking if it timed out
Json::Object DataSinkImplementation::Finalize(bool timed_out) {
  if (timed_out) {
    AddAdditionalInfo("channelzState", {{"timedOut", Json::FromBool(true)}});
  }
  MutexLock lock(&mu_);
  MergeChildObjectsIntoAdditionalInfo();
  Json::Object out;
  for (auto& [name, additional_info] : additional_info_) {
    out[name] = Json::FromObject(std::move(additional_info));
  }
  return out;
}

// Merges child objects into additional info for final JSON output
void DataSinkImplementation::MergeChildObjectsIntoAdditionalInfo() {
  if (child_objects_.empty()) return;
  Json::Object subobjects;
  std::map<BaseNode::EntityType, std::set<int64_t>> child_objects_by_type;
  for (auto& node : child_objects_) {
    child_objects_by_type[node->type()].insert(node->uuid());
  }
  for (const auto& [type, child_objects] : child_objects_by_type) {
    std::string key;
    switch (type) {
      case BaseNode::EntityType::kTopLevelChannel:
      case BaseNode::EntityType::kSubchannel:
      case BaseNode::EntityType::kListenSocket:
      case BaseNode::EntityType::kServer:
      case BaseNode::EntityType::kInternalChannel: {
        LOG(ERROR) << "Nodes of type " << BaseNode::EntityTypeString(type)
                   << " not supported for child object collection in DataSink";
        continue;
      }
      case BaseNode::EntityType::kSocket:
        key = "subSockets";
        break;
      case BaseNode::EntityType::kCall:
        key = "calls";
        break;
    }
    Json::Array uuids;
    uuids.reserve(child_objects.size());
    for (int64_t uuid : child_objects) {
      uuids.push_back(Json::FromNumber(uuid));
    }
    subobjects[key] = Json::FromArray(std::move(uuids));
  }
  additional_info_.emplace("childObjects", std::move(subobjects));
}

// BaseNode class methods

// Constructor for BaseNode, registers itself with ChannelzRegistry
BaseNode::BaseNode(EntityType type, std::string name)
    : type_(type), uuid_(-1), name_(std::move(name)) {
  ChannelzRegistry::Register(this);
}

// Called when node is orphaned, unregisters from ChannelzRegistry
void BaseNode::Orphaned() { ChannelzRegistry::Unregister(this); }

// Gets UUID for the node (slow path)
intptr_t BaseNode::UuidSlow() { return ChannelzRegistry::NumberNode(this); }

// Renders node as JSON string
std::string BaseNode::RenderJsonString() {
  Json json = RenderJson();
  return JsonDump(json);
}

// Populates JSON object with data from data sources
void BaseNode::PopulateJsonFromDataSources(Json::Object& json) {
  auto info = AdditionalInfo();
  if (info.empty()) return;
  json["additionalInfo"] = Json::FromObject(std::move(info));
}

// Collects additional information from data sources
Json::Object BaseNode::AdditionalInfo() {
  auto done = std::make_shared<Notification>();
  auto sink_impl = std::make_shared<DataSinkImplementation>();
  {
    MutexLock lock(&data_sources_mu_);
    auto done_notifier = std::make_shared<DataSinkCompletionNotification>(
        [done]() { done->Notify(); });
    for (DataSource* data_source : data_sources_) {
      data_source->AddData(DataSink(sink_impl, done_notifier));
    }
  }
  bool completed =
      done->WaitForNotificationWithTimeout(absl::Milliseconds(100));
  return sink_impl->Finalize(!completed);
}

// Runs a ztrace operation
void BaseNode::RunZTrace(
    absl::string_view name, Timestamp deadline,
    std::map<std::string, std::string> args,
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine,
    absl::AnyInvocable<void(Json)> callback) {

  deadline = std::min(deadline, Timestamp::Now() + Duration::Minutes(10));
  auto fail = [&callback, event_engine](absl::Status status) {
    event_engine->Run(
        [callback = std::move(callback), status = std::move(status)]() mutable {
          Json::Object object;
          object["status"] = Json::FromString(status.ToString());
          callback(Json::FromObject(std::move(object)));
        });
  };
  std::unique_ptr<ZTrace> ztrace;
  {
    MutexLock lock(&data_sources_mu_);
    for (auto* data_source : data_sources_) {
      if (auto found_ztrace = data_source->GetZTrace(name);
          found_ztrace != nullptr) {
        if (ztrace == nullptr) {
          ztrace = std::move(found_ztrace);
        } else {
          fail(absl::InternalError(
              absl::StrCat("Ambiguous ztrace handler: ", name)));
          return;
        }
      }
    }
  }
  if (ztrace == nullptr) {
    fail(absl::NotFoundError(absl::StrCat("ztrace not found: ", name)));
    return;
  }
  ztrace->Run(deadline, std::move(args), event_engine, std::move(callback));
}

// DataSource class methods

// Constructor for DataSource, registers with parent node
DataSource::DataSource(RefCountedPtr<BaseNode> node) : node_(std::move(node)) {
  if (node_ == nullptr) return;
  MutexLock lock(&node_->data_sources_mu_);
  node_->data_sources_.push_back(this);
}

// Destructor for DataSource, ensures ResetDataSource was called
DataSource::~DataSource() {
  DCHECK(node_ == nullptr) << "DataSource must be ResetDataSource()'d in the "
                              "most derived class before destruction";
}

// Unregisters data source from parent node
void DataSource::ResetDataSource() {
  RefCountedPtr<BaseNode> node = std::move(node_);
  if (node == nullptr) return;
  MutexLock lock(&node->data_sources_mu_);
  node->data_sources_.erase(
      std::remove(node->data_sources_.begin(), node->data_sources_.end(), this),
      node->data_sources_.end());
}

// CallCountingHelper class methods

// Records that a call has started
void CallCountingHelper::RecordCallStarted() {
  calls_started_.fetch_add(1, std::memory_order_relaxed);
  last_call_started_cycle_.store(gpr_get_cycle_counter(),
                                 std::memory_order_relaxed);
}

// Records that a call has failed
void CallCountingHelper::RecordCallFailed() {
  calls_failed_.fetch_add(1, std::memory_order_relaxed);
}

// Records that a call has succeeded
void CallCountingHelper::RecordCallSucceeded() {
  calls_succeeded_.fetch_add(1, std::memory_order_relaxed);
}

// Populates JSON with call count statistics
void CallCounts::PopulateJson(Json::Object& json) const {
  if (calls_started != 0) {
    json["callsStarted"] = Json::FromString(absl::StrCat(calls_started));
    json["lastCallStartedTimestamp"] =
        Json::FromString(last_call_started_timestamp());
  }
  if (calls_succeeded != 0) {
    json["callsSucceeded"] = Json::FromString(absl::StrCat(calls_succeeded));
  }
  if (calls_failed != 0) {
    json["callsFailed"] = Json::FromString(absl::StrCat(calls_failed));
  }
}

// PerCpuCallCountingHelper class methods

// Records that a call has started (per-CPU version)
void PerCpuCallCountingHelper::RecordCallStarted() {
  auto& data = per_cpu_data_.this_cpu();
  data.calls_started.fetch_add(1, std::memory_order_relaxed);
  data.last_call_started_cycle.store(gpr_get_cycle_counter(),
                                     std::memory_order_relaxed);
}

// Records that a call has failed (per-CPU version)
void PerCpuCallCountingHelper::RecordCallFailed() {
  per_cpu_data_.this_cpu().calls_failed.fetch_add(1, std::memory_order_relaxed);
}

// Records that a call has succeeded (per-CPU version)
void PerCpuCallCountingHelper::RecordCallSucceeded() {
  per_cpu_data_.this_cpu().calls_succeeded.fetch_add(1,
                                                     std::memory_order_relaxed);
}

// Gets aggregated call counts across all CPUs
CallCounts PerCpuCallCountingHelper::GetCallCounts() const {
  CallCounts call_counts;
  for (const auto& cpu : per_cpu_data_) {
    call_counts.calls_started +=
        cpu.calls_started.load(std::memory_order_relaxed);
    call_counts.calls_succeeded +=
        cpu.calls_succeeded.load(std::memory_order_relaxed);
    call_counts.calls_failed +=
        cpu.calls_failed.load(std::memory_order_relaxed);
    call_counts.last_call_started_cycle =
        std::max(call_counts.last_call_started_cycle,
                 cpu.last_call_started_cycle.load(std::memory_order_relaxed));
  }
  return call_counts;
}

// ChannelNode class methods

// Constructor for ChannelNode
ChannelNode::ChannelNode(std::string target, size_t channel_tracer_max_nodes,
                         bool is_internal_channel)
    : BaseNode(is_internal_channel ? EntityType::kInternalChannel
                                   : EntityType::kTopLevelChannel,
               target),
      target_(std::move(target)),
      trace_(channel_tracer_max_nodes) {}

// Returns string representation of connectivity state change
const char* ChannelNode::GetChannelConnectivityStateChangeString(
    grpc_connectivity_state state) {
  switch (state) {
    case GRPC_CHANNEL_IDLE:
      return "Channel state change to IDLE";
    case GRPC_CHANNEL_CONNECTING:
      return "Channel state change to CONNECTING";
    case GRPC_CHANNEL_READY:
      return "Channel state change to READY";
    case GRPC_CHANNEL_TRANSIENT_FAILURE:
      return "Channel state change to TRANSIENT_FAILURE";
    case GRPC_CHANNEL_SHUTDOWN:
      return "Channel state change to SHUTDOWN";
  }
  GPR_UNREACHABLE_CODE(return "UNKNOWN");
}

namespace {

// Helper function to get child IDs of a specific type
std::set<intptr_t> ChildIdSet(const BaseNode* parent,
                              BaseNode::EntityType type) {
  std::set<intptr_t> ids;
  auto [children, _] = ChannelzRegistry::GetChildrenOfType(
      0, parent, type, std::numeric_limits<size_t>::max());
  for (const auto& node : children) {
    ids.insert(node->uuid());
  }
  return ids;
}

}

// Gets set of child channel IDs
std::set<intptr_t> ChannelNode::child_channels() const {
  return ChildIdSet(this, BaseNode::EntityType::kInternalChannel);
}

// Gets set of child subchannel IDs
std::set<intptr_t> ChannelNode::child_subchannels() const {
  return ChildIdSet(this, BaseNode::EntityType::kSubchannel);
}

// Gets current connectivity state if available
std::optional<std::string> ChannelNode::connectivity_state() {
  int state_field = connectivity_state_.load(std::memory_order_relaxed);
  if ((state_field & 1) != 0) {
    grpc_connectivity_state state =
        static_cast<grpc_connectivity_state>(state_field >> 1);
    return ConnectivityStateName(state);
  }
  return std::nullopt;
}

// Renders channel node as JSON
Json ChannelNode::RenderJson() {
  Json::Object data = {
      {"target", Json::FromString(target_)},
  };
  if (auto cs = connectivity_state(); cs.has_value()) {
    data["state"] = Json::FromObject({
        {"state", Json::FromString(cs.value())},
    });
  }

  Json trace_json = trace_.RenderJson();
  if (trace_json.type() != Json::Type::kNull) {
    data["trace"] = std::move(trace_json);
  }

  call_counter_.GetCallCounts().PopulateJson(data);

  Json::Object json = {
      {"ref", Json::FromObject({
                  {"channelId", Json::FromString(absl::StrCat(uuid()))},
              })},
      {"data", Json::FromObject(std::move(data))},
  };

  PopulateChildRefs(&json);
  PopulateJsonFromDataSources(json);
  return Json::FromObject(std::move(json));
}

// Populates child references in JSON object
void ChannelNode::PopulateChildRefs(Json::Object* json) {
  auto child_subchannels = this->child_subchannels();
  auto child_channels = this->child_channels();
  if (!child_subchannels.empty()) {
    Json::Array array;
    for (intptr_t subchannel_uuid : child_subchannels) {
      array.emplace_back(Json::FromObject({
          {"subchannelId", Json::FromString(absl::StrCat(subchannel_uuid))},
      }));
    }
    (*json)["subchannelRef"] = Json::FromArray(std::move(array));
  }
  if (!child_channels.empty()) {
    Json::Array array;
    for (intptr_t channel_uuid : child_channels) {
      array.emplace_back(Json::FromObject({
          {"channelId", Json::FromString(absl::StrCat(channel_uuid))},
      }));
    }
    (*json)["channelRef"] = Json::FromArray(std::move(array));
  }
}

// Sets the connectivity state of the channel
void ChannelNode::SetConnectivityState(grpc_connectivity_state state) {
  int state_field = (state << 1) + 1;
  connectivity_state_.store(state_field, std::memory_order_relaxed);
}

// SubchannelNode class methods

// Constructor for SubchannelNode
SubchannelNode::SubchannelNode(std::string target_address,
                               size_t channel_tracer_max_nodes)
    : BaseNode(EntityType::kSubchannel, target_address),
      target_(std::move(target_address)),
      trace_(channel_tracer_max_nodes) {}

SubchannelNode::~SubchannelNode() {}

// Updates the connectivity state of the subchannel
void SubchannelNode::UpdateConnectivityState(grpc_connectivity_state state) {
  connectivity_state_.store(state, std::memory_order_relaxed);
}

// Sets the child socket of the subchannel
void SubchannelNode::SetChildSocket(RefCountedPtr<SocketNode> socket) {
  MutexLock lock(&socket_mu_);
  child_socket_ =
      socket == nullptr ? nullptr : socket->WeakRefAsSubclass<SocketNode>();
}

// Gets the connectivity state as a string
std::string SubchannelNode::connectivity_state() const {
  grpc_connectivity_state state =
      connectivity_state_.load(std::memory_order_relaxed);
  return ConnectivityStateName(state);
}

// Renders subchannel node as JSON
Json SubchannelNode::RenderJson() {
  Json::Object data = {
      {"state", Json::FromObject({
                    {"state", Json::FromString(connectivity_state())},
                })},
      {"target", Json::FromString(target_)},
  };

  Json trace_json = trace_.RenderJson();
  if (trace_json.type() != Json::Type::kNull) {
    data["trace"] = std::move(trace_json);
  }

  call_counter_.GetCallCounts().PopulateJson(data);

  Json::Object object{
      {"ref", Json::FromObject({
                  {"subchannelId", Json::FromString(absl::StrCat(uuid()))},
              })},
      {"data", Json::FromObject(std::move(data))},
  };

  WeakRefCountedPtr<SocketNode> child_socket;
  {
    MutexLock lock(&socket_mu_);
    child_socket = child_socket_;
  }
  if (child_socket != nullptr && child