
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CHANNELZ_CHANNELZ_H
#define GRPC_SRC_CORE_CHANNELZ_CHANNELZ_H

#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <cstdint>
#include <initializer_list>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_set.h"
#include "absl/container/inlined_vector.h"
#include "absl/strings/string_view.h"
#include "src/core/channelz/channel_trace.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/json/json.h"
#include "src/core/util/per_cpu.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/string.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_CHANNELZ_CHANNEL_NODE \
  "grpc.internal.no_subchannel.channelz_channel_node"

#define GRPC_ARG_CHANNELZ_CONTAINING_BASE_NODE \
  "grpc.internal.no_subchannel.channelz_containing_base_node"

#define GRPC_ARG_CHANNELZ_IS_INTERNAL_CHANNEL \
  "grpc.channelz_is_internal_channel"

#define GRPC_ENABLE_CHANNELZ_DEFAULT true

#define GRPC_MAX_CHANNEL_TRACE_EVENT_MEMORY_PER_NODE_DEFAULT (1024 * 4)

namespace grpc_core {

namespace channelz {

class SocketNode;
class ListenSocketNode;
class DataSource;
class ZTrace;

namespace testing {
class CallCountingHelperPeer;
class SubchannelNodePeer;
}

class BaseNode : public DualRefCounted<BaseNode> {
 public:

  enum class EntityType {
    kTopLevelChannel,
    kInternalChannel,
    kSubchannel,
    kServer,
    kListenSocket,
    kSocket,
    kCall,
  };

  static absl::string_view EntityTypeString(EntityType type) {
    switch (type) {
      case EntityType::kTopLevelChannel:
        return "top_level_channel";
      case EntityType::kInternalChannel:
        return "internal_channel";
      case EntityType::kSubchannel:
        return "subchannel";
      case EntityType::kServer:
        return "server";
      case EntityType::kListenSocket:
        return "listen_socket";
      case EntityType::kSocket:
        return "socket";
      case EntityType::kCall:
        return "call";
    }
    return "unknown";
  }

 protected:
  BaseNode(EntityType type, std::string name);

 public:
  void Orphaned() override;

  bool HasParent(const BaseNode* parent) const {
    MutexLock lock(&parent_mu_);
    return parents_.find(parent) != parents_.end();
  }

  void AddParent(BaseNode* parent) {
    MutexLock lock(&parent_mu_);
    parents_.insert(parent->WeakRef());
  }

  void RemoveParent(BaseNode* parent) {
    MutexLock lock(&parent_mu_);
    parents_.erase(parent);
  }

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_CHANNELZ_CONTAINING_BASE_NODE;
  }
  static int ChannelArgsCompare(const BaseNode* a, const BaseNode* b) {
    return QsortCompare(a, b);
  }

  virtual Json RenderJson() = 0;

  std::string RenderJsonString();

  EntityType type() const { return type_; }
  intptr_t uuid() {
    const intptr_t id = uuid_.load(std::memory_order_relaxed);
    if (id > 0) return id;
    return UuidSlow();
  }
  const std::string& name() const { return name_; }

  void RunZTrace(absl::string_view name, Timestamp deadline,
                 std::map<std::string, std::string> args,
                 std::shared_ptr<grpc_event_engine::experimental::EventEngine>
                     event_engine,
                 absl::AnyInvocable<void(Json output)> callback);
  Json::Object AdditionalInfo();

 protected:
  void PopulateJsonFromDataSources(Json::Object& json);

 private:

  friend class ChannelzRegistry;

  friend class DataSource;
  using ParentSet = absl::flat_hash_set<WeakRefCountedPtr<BaseNode>,
                                        WeakRefCountedPtrHash<BaseNode>,
                                        WeakRefCountedPtrEq<BaseNode>>;

  intptr_t UuidSlow();

  const EntityType type_;
  uint64_t orphaned_index_ = 0;
  std::atomic<intptr_t> uuid_;
  std::string name_;
  Mutex data_sources_mu_;
  absl::InlinedVector<DataSource*, 3> data_sources_
      ABSL_GUARDED_BY(data_sources_mu_);
  BaseNode* prev_;
  BaseNode* next_;
  mutable Mutex parent_mu_;
  ParentSet parents_ ABSL_GUARDED_BY(parent_mu_);
};

class ZTrace {
 public:
  virtual ~ZTrace() = default;
  virtual void Run(Timestamp deadline, std::map<std::string, std::string> args,
                   std::shared_ptr<grpc_event_engine::experimental::EventEngine>
                       event_engine,
                   absl::AnyInvocable<void(Json)>) = 0;
};

class DataSinkImplementation {
 public:
  void AddAdditionalInfo(absl::string_view name, Json::Object additional_info);
  void AddChildObjects(std::vector<RefCountedPtr<BaseNode>> child_objects);
  Json::Object Finalize(bool timed_out);

 private:
  void MergeChildObjectsIntoAdditionalInfo() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  Mutex mu_;
  std::map<std::string, Json::Object> additional_info_ ABSL_GUARDED_BY(mu_);
  std::vector<RefCountedPtr<BaseNode>> child_objects_ ABSL_GUARDED_BY(mu_);
};

class DataSinkCompletionNotification {
 public:
  explicit DataSinkCompletionNotification(absl::AnyInvocable<void()> callback)
      : callback_(std::move(callback)) {}
  ~DataSinkCompletionNotification() { callback_(); }

 private:
  absl::AnyInvocable<void()> callback_;
};

class DataSink {
 public:
  DataSink(std::shared_ptr<DataSinkImplementation> impl,
           std::shared_ptr<DataSinkCompletionNotification> notification)
      : impl_(impl), notification_(std::move(notification)) {}

  void AddAdditionalInfo(absl::string_view name, Json::Object additional_info) {
    auto impl = impl_.lock();
    if (impl == nullptr) return;
    impl->AddAdditionalInfo(name, std::move(additional_info));
  }
  void AddChildObjects(std::vector<RefCountedPtr<BaseNode>> children) {
    auto impl = impl_.lock();
    if (impl == nullptr) return;
    impl->AddChildObjects(std::move(children));
  }

 private:
  std::weak_ptr<DataSinkImplementation> impl_;
  std::shared_ptr<DataSinkCompletionNotification> notification_;
};

class DataSource {
 public:
  explicit DataSource(RefCountedPtr<BaseNode> node);

  virtual void AddData(DataSink) {}

  virtual std::unique_ptr<ZTrace> GetZTrace(absl::string_view ) {
    return nullptr;
  }

 protected:
  ~DataSource();
  RefCountedPtr<BaseNode> channelz_node() { return node_; }

  void ResetDataSource();

 private:
  RefCountedPtr<BaseNode> node_;
};

struct CallCounts {
  int64_t calls_started = 0;
  int64_t calls_succeeded = 0;
  int64_t calls_failed = 0;
  gpr_cycle_counter last_call_started_cycle = 0;

  std::string last_call_started_timestamp() const {
    return gpr_format_timespec(
        gpr_cycle_counter_to_time(last_call_started_cycle));
  }

  void PopulateJson(Json::Object& json) const;
};

class CallCountingHelper final {
 public:
  void RecordCallStarted();
  void RecordCallFailed();
  void RecordCallSucceeded();

  CallCounts GetCallCounts() const {
    return {
        calls_started_.load(std::memory_order_relaxed),
        calls_succeeded_.load(std::memory_order_relaxed),
        calls_failed_.load(std::memory_order_relaxed),
        last_call_started_cycle_.load(std::memory_order_relaxed),
    };
  }

 private:

  friend class testing::CallCountingHelperPeer;

  std::atomic<int64_t> calls_started_{0};
  std::atomic<int64_t> calls_succeeded_{0};
  std::atomic<int64_t> calls_failed_{0};
  std::atomic<gpr_cycle_counter> last_call_started_cycle_{0};
};

class PerCpuCallCountingHelper final {
 public:
  void RecordCallStarted();
  void RecordCallFailed();
  void RecordCallSucceeded();

  CallCounts GetCallCounts() const;

 private:

  friend class testing::CallCountingHelperPeer;

  struct alignas(GPR_CACHELINE_SIZE) PerCpuData {
    std::atomic<int64_t> calls_started{0};
    std::atomic<int64_t> calls_succeeded{0};
    std::atomic<int64_t> calls_failed{0};
    std::atomic<gpr_cycle_counter> last_call_started_cycle{0};
  };
  PerCpu<PerCpuData> per_cpu_data_{PerCpuOptions().SetCpusPerShard(4)};
};

class ChannelNode final : public BaseNode {
 public:
  ChannelNode(std::string target, size_t channel_tracer_max_nodes,
              bool is_internal_channel);

  void Orphaned() override {
    channel_args_ = ChannelArgs();
    BaseNode::Orphaned();
  }

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_CHANNELZ_CHANNEL_NODE;
  }
  static int ChannelArgsCompare(const ChannelNode* a, const ChannelNode* b) {
    return QsortCompare(a, b);
  }

  static const char* GetChannelConnectivityStateChangeString(
      grpc_connectivity_state state);

  Json RenderJson() override;

  void AddTraceEvent(ChannelTrace::Severity severity, const grpc_slice& data) {
    trace_.AddTraceEvent(severity, data);
  }
  void AddTraceEventWithReference(ChannelTrace::Severity severity,
                                  const grpc_slice& data,
                                  RefCountedPtr<BaseNode> referenced_channel) {
    trace_.AddTraceEventWithReference(severity, data,
                                      std::move(referenced_channel));
  }
  void SetChannelArgs(const ChannelArgs& channel_args) {
    channel_args_ = channel_args;
  }
  void RecordCallStarted() { call_counter_.RecordCallStarted(); }
  void RecordCallFailed() { call_counter_.RecordCallFailed(); }
  void RecordCallSucceeded() { call_counter_.RecordCallSucceeded(); }

  void SetConnectivityState(grpc_connectivity_state state);

  const std::string& target() const { return target_; }
  std::optional<std::string> connectivity_state();
  CallCounts GetCallCounts() const { return call_counter_.GetCallCounts(); }
  std::set<intptr_t> child_channels() const;
  std::set<intptr_t> child_subchannels() const;
  const ChannelTrace& trace() const { return trace_; }
  const ChannelArgs& channel_args() const { return channel_args_; }

 private:
  void PopulateChildRefs(Json::Object* json);

  std::string target_;
  CallCountingHelper call_counter_;
  ChannelTrace trace_;

  ChannelArgs channel_args_;

  std::atomic<int> connectivity_state_{0};
};

class SubchannelNode final : public BaseNode {
 public:
  SubchannelNode(std::string target_address, size_t channel_tracer_max_nodes);
  ~SubchannelNode() override;

  void Orphaned() override {
    channel_args_ = ChannelArgs();
    BaseNode::Orphaned();
  }

  void UpdateConnectivityState(grpc_connectivity_state state);

  void SetChildSocket(RefCountedPtr<SocketNode> socket);

  Json RenderJson() override;

  void AddTraceEvent(ChannelTrace::Severity severity, const grpc_slice& data) {
    trace_.AddTraceEvent(severity, data);
  }
  void SetChannelArgs(const ChannelArgs& channel_args) {
    channel_args_ = channel_args;
  }
  void AddTraceEventWithReference(ChannelTrace::Severity severity,
                                  const grpc_slice& data,
                                  RefCountedPtr<BaseNode> referenced_channel) {
    trace_.AddTraceEventWithReference(severity, data,
                                      std::move(referenced_channel));
  }
  void RecordCallStarted() { call_counter_.RecordCallStarted(); }
  void RecordCallFailed() { call_counter_.RecordCallFailed(); }
  void RecordCallSucceeded() { call_counter_.RecordCallSucceeded(); }

  const std::string& target() const { return target_; }
  std::string connectivity_state() const;
  CallCounts GetCallCounts() const { return call_counter_.GetCallCounts(); }
  WeakRefCountedPtr<SocketNode> child_socket() const {
    MutexLock lock(&socket_mu_);
    return child_socket_;
  }
  const ChannelTrace& trace() const { return trace_; }
  const ChannelArgs& channel_args() const { return channel_args_; }

 private:

  friend class testing::SubchannelNodePeer;

  std::atomic<grpc_connectivity_state> connectivity_state_{GRPC_CHANNEL_IDLE};
  mutable Mutex socket_mu_;
  WeakRefCountedPtr<SocketNode> child_socket_ ABSL_GUARDED_BY(socket_mu_);
  std::string target_;
  CallCountingHelper call_counter_;
  ChannelTrace trace_;

  ChannelArgs channel_args_;
};

class ServerNode final : public BaseNode {
 public:
  explicit ServerNode(size_t channel_tracer_max_nodes);

  ~ServerNode() override;

  void Orphaned() override {
    channel_args_ = ChannelArgs();
    BaseNode::Orphaned();
  }

  Json RenderJson() override;

  std::string RenderServerSockets(intptr_t start_socket_id,
                                  intptr_t max_results);

  void AddTraceEvent(ChannelTrace::Severity severity, const grpc_slice& data) {
    trace_.AddTraceEvent(severity, data);
  }
  void AddTraceEventWithReference(ChannelTrace::Severity severity,
                                  const grpc_slice& data,
                                  RefCountedPtr<BaseNode> referenced_channel) {
    trace_.AddTraceEventWithReference(severity, data,
                                      std::move(referenced_channel));
  }
  void SetChannelArgs(const ChannelArgs& channel_args) {
    channel_args_ = channel_args;
  }
  void RecordCallStarted() { call_counter_.RecordCallStarted(); }
  void RecordCallFailed() { call_counter_.RecordCallFailed(); }
  void RecordCallSucceeded() { call_counter_.RecordCallSucceeded(); }

  CallCounts GetCallCounts() const { return call_counter_.GetCallCounts(); }

  std::map<intptr_t, WeakRefCountedPtr<ListenSocketNode>> child_listen_sockets()
      const;
  std::map<intptr_t, WeakRefCountedPtr<SocketNode>> child_sockets() const;

  const ChannelTrace& trace() const { return trace_; }
  const ChannelArgs& channel_args() const { return channel_args_; }

 private:
  PerCpuCallCountingHelper call_counter_;
  ChannelTrace trace_;

  ChannelArgs channel_args_;
};

#define GRPC_ARG_CHANNELZ_SECURITY "grpc.internal.channelz_security"

class SocketNode final : public BaseNode {
 public:
  struct Security : public RefCounted<Security> {
    struct Tls {

      Tls() {}

      enum class NameType { kUnset = 0, kStandardName = 1, kOtherName = 2 };
      NameType type = NameType::kUnset;

      std::string name;
      std::string local_certificate;
      std::string remote_certificate;

      Json RenderJson();
    };
    enum class ModelType { kUnset = 0, kTls = 1, kOther = 2 };
    ModelType type = ModelType::kUnset;
    std::optional<Tls> tls;
    std::optional<Json> other;

    Json RenderJson();

    static absl::string_view ChannelArgName() {
      return GRPC_ARG_CHANNELZ_SECURITY;
    }

    static int ChannelArgsCompare(const Security* a, const Security* b) {
      return QsortCompare(a, b);
    }

    grpc_arg MakeChannelArg() const;

    static RefCountedPtr<Security> GetFromChannelArgs(
        const grpc_channel_args* args);
  };

  SocketNode(std::string local, std::string remote, std::string name,
             RefCountedPtr<Security> security);
  ~SocketNode() override {}

  Json RenderJson() override;

  void RecordStreamStartedFromLocal();
  void RecordStreamStartedFromRemote();
  void RecordStreamSucceeded() {
    streams_succeeded_.fetch_add(1, std::memory_order_relaxed);
  }
  void RecordStreamFailed() {
    streams_failed_.fetch_add(1, std::memory_order_relaxed);
  }
  void RecordMessagesSent(uint32_t num_sent);
  void RecordMessageReceived();
  void RecordKeepaliveSent() {
    keepalives_sent_.fetch_add(1, std::memory_order_relaxed);
  }

  const std::string& remote() { return remote_; }

  int64_t streams_started() const {
    return streams_started_.load(std::memory_order_relaxed);
  }
  int64_t streams_succeeded() const {
    return streams_succeeded_.load(std::memory_order_relaxed);
  }
  int64_t streams_failed() const {
    return streams_failed_.load(std::memory_order_relaxed);
  }
  int64_t messages_sent() const {
    return messages_sent_.load(std::memory_order_relaxed);
  }
  int64_t messages_received() const {
    return messages_received_.load(std::memory_order_relaxed);
  }
  int64_t keepalives_sent() const {
    return keepalives_sent_.load(std::memory_order_relaxed);
  }
  auto last_local_stream_created_timestamp() const {
    return CycleCounterToTimestamp(
        last_local_stream_created_cycle_.load(std::memory_order_relaxed));
  }
  auto last_remote_stream_created_timestamp() const {
    return CycleCounterToTimestamp(
        last_remote_stream_created_cycle_.load(std::memory_order_relaxed));
  }
  auto last_message_sent_timestamp() const {
    return CycleCounterToTimestamp(
        last_message_sent_cycle_.load(std::memory_order_relaxed));
  }
  auto last_message_received_timestamp() const {
    return CycleCounterToTimestamp(
        last_message_received_cycle_.load(std::memory_order_relaxed));
  }
  const std::string& local() const { return local_; }
  const std::string& remote() const { return remote_; }

  RefCountedPtr<Security> security() const { return security_; }

 private:
  std::optional<std::string> CycleCounterToTimestamp(
      gpr_cycle_counter cycle_counter) const {
    return gpr_format_timespec(gpr_cycle_counter_to_time(cycle_counter));
  }

  std::atomic<int64_t> streams_started_{0};
  std::atomic<int64_t> streams_succeeded_{0};
  std::atomic<int64_t> streams_failed_{0};
  std::atomic<int64_t> messages_sent_{0};
  std::atomic<int64_t> messages_received_{0};
  std::atomic<int64_t> keepalives_sent_{0};
  std::atomic<gpr_cycle_counter> last_local_stream_created_cycle_{0};
  std::atomic<gpr_cycle_counter> last_remote_stream_created_cycle_{0};
  std::atomic<gpr_cycle_counter> last_message_sent_cycle_{0};
  std::atomic<gpr_cycle_counter> last_message_received_cycle_{0};
  std::string local_;
  std::string remote_;
  RefCountedPtr<Security> const security_;
};

class ListenSocketNode final : public BaseNode {
 public:
  ListenSocketNode(std::string local_addr, std::string name);
  ~ListenSocketNode() override {}

  Json RenderJson() override;

 private:
  std::string local_addr_;
};

class CallNode final : public BaseNode {
 public:
  explicit CallNode(std::string name)
      : BaseNode(EntityType::kCall, std::move(name)) {}

  Json RenderJson() override;
};

}
}

#endif
