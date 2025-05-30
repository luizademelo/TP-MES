
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_CHANNELZ_CHANNELZ_REGISTRY_H
#define GRPC_SRC_CORE_CHANNELZ_CHANNELZ_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <cstdint>
#include <map>
#include <string>

#include "absl/container/btree_map.h"
#include "absl/functional/function_ref.h"
#include "src/core/channelz/channelz.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace channelz {

class ChannelzRegistry final {
 public:
  static void Register(BaseNode* node) {
    return Default()->InternalRegister(node);
  }
  static void Unregister(BaseNode* node) {
    Default()->InternalUnregister(node);
  }
  static WeakRefCountedPtr<BaseNode> Get(intptr_t uuid) {
    return Default()->InternalGet(uuid);
  }
  static intptr_t NumberNode(BaseNode* node) {
    return Default()->InternalNumberNode(node);
  }

  static WeakRefCountedPtr<SubchannelNode> GetSubchannel(intptr_t uuid) {
    return Default()
        ->InternalGetTyped<SubchannelNode, BaseNode::EntityType::kSubchannel>(
            uuid);
  }

  static WeakRefCountedPtr<ChannelNode> GetChannel(intptr_t uuid) {
    auto node = Default()->InternalGet(uuid);
    if (node == nullptr) return nullptr;
    if (node->type() == BaseNode::EntityType::kTopLevelChannel) {
      return node->WeakRefAsSubclass<ChannelNode>();
    }
    if (node->type() == BaseNode::EntityType::kInternalChannel) {
      return node->WeakRefAsSubclass<ChannelNode>();
    }
    return nullptr;
  }

  static WeakRefCountedPtr<ServerNode> GetServer(intptr_t uuid) {
    return Default()
        ->InternalGetTyped<ServerNode, BaseNode::EntityType::kServer>(uuid);
  }

  static WeakRefCountedPtr<SocketNode> GetSocket(intptr_t uuid) {
    return Default()
        ->InternalGetTyped<SocketNode, BaseNode::EntityType::kSocket>(uuid);
  }

  static auto GetTopChannels(intptr_t start_channel_id) {
    return Default()
        ->InternalGetObjects<ChannelNode,
                             BaseNode::EntityType::kTopLevelChannel>(
            start_channel_id);
  }

  static std::string GetTopChannelsJson(intptr_t start_channel_id);
  static std::string GetServersJson(intptr_t start_server_id);

  static auto GetServers(intptr_t start_server_id) {
    return Default()
        ->InternalGetObjects<ServerNode, BaseNode::EntityType::kServer>(
            start_server_id);
  }

  static std::tuple<std::vector<WeakRefCountedPtr<BaseNode>>, bool>
  GetChildrenOfType(intptr_t start_node, const BaseNode* parent,
                    BaseNode::EntityType type, size_t max_results) {
    return Default()->InternalGetChildrenOfType(start_node, parent, type,
                                                max_results);
  }

  static void LogAllEntities() { Default()->InternalLogAllEntities(); }

  static std::vector<WeakRefCountedPtr<BaseNode>> GetAllEntities() {
    return Default()->InternalGetAllEntities();
  }

  static void TestOnlyReset();

 private:
  ChannelzRegistry() { LoadConfig(); }

  void LoadConfig();

  template <typename F>
  static auto CollectReferences(F fn) {
    return [fn = std::move(fn)](BaseNode* n) {
      auto node = n->RefIfNonZero();
      if (node == nullptr) return true;
      return fn(std::move(node));
    };
  }

  struct NodeList {
    BaseNode* head = nullptr;
    BaseNode* tail = nullptr;
    size_t count = 0;
    bool Holds(BaseNode* node) const;
    void AddToHead(BaseNode* node);
    void Remove(BaseNode* node);
  };

  struct alignas(GPR_CACHELINE_SIZE) NodeShard {
    Mutex mu;

    NodeList nursery ABSL_GUARDED_BY(mu);

    NodeList numbered ABSL_GUARDED_BY(mu);

    NodeList orphaned ABSL_GUARDED_BY(mu);

    NodeList orphaned_numbered ABSL_GUARDED_BY(mu);
    uint64_t next_orphan_index ABSL_GUARDED_BY(mu) = 1;
    size_t TotalOrphaned() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu) {
      return orphaned.count + orphaned_numbered.count;
    }
  };

  static ChannelzRegistry* Default();

  void InternalRegister(BaseNode* node);

  void InternalUnregister(BaseNode* node);

  intptr_t InternalNumberNode(BaseNode* node);

  WeakRefCountedPtr<BaseNode> InternalGet(intptr_t uuid);

  std::tuple<std::vector<WeakRefCountedPtr<BaseNode>>, bool> QueryNodes(
      intptr_t start_node,
      absl::FunctionRef<bool(const BaseNode*)> discriminator,
      size_t max_results);

  std::tuple<std::vector<WeakRefCountedPtr<BaseNode>>, bool>
  InternalGetChildrenOfType(intptr_t start_node, const BaseNode* parent,
                            BaseNode::EntityType type, size_t max_results) {
    return QueryNodes(
        start_node,
        [type, parent](const BaseNode* n) {
          return n->type() == type && n->HasParent(parent);
        },
        max_results);
  }

  template <typename T, BaseNode::EntityType entity_type>
  WeakRefCountedPtr<T> InternalGetTyped(intptr_t uuid) {
    WeakRefCountedPtr<BaseNode> node = InternalGet(uuid);
    if (node == nullptr || node->type() != entity_type) {
      return nullptr;
    }
    return node->WeakRefAsSubclass<T>();
  }

  template <typename T, BaseNode::EntityType entity_type>
  std::tuple<std::vector<WeakRefCountedPtr<T>>, bool> InternalGetObjects(
      intptr_t start_id) {
    const int kPaginationLimit = 100;
    std::vector<WeakRefCountedPtr<T>> top_level_channels;
    const auto [nodes, end] = QueryNodes(
        start_id,
        [](const BaseNode* node) { return node->type() == entity_type; },
        kPaginationLimit);
    for (const auto& p : nodes) {
      top_level_channels.emplace_back(p->template WeakRefAsSubclass<T>());
    }
    return std::tuple(std::move(top_level_channels), end);
  }

  void InternalLogAllEntities();
  std::vector<WeakRefCountedPtr<BaseNode>> InternalGetAllEntities();

  static constexpr size_t kNodeShards = 63;
  size_t NodeShardIndex(BaseNode* node) {
    return absl::HashOf(node) % kNodeShards;
  }

  int64_t uuid_generator_{1};
  std::vector<NodeShard> node_shards_{kNodeShards};
  Mutex index_mu_;
  absl::btree_map<intptr_t, BaseNode*> index_ ABSL_GUARDED_BY(index_mu_);
  size_t max_orphaned_per_shard_;
};

std::string StripAdditionalInfoFromJson(absl::string_view json);

}
}

#endif
