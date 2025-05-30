
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_CHANNEL_ARGUMENTS_H
#define GRPCPP_SUPPORT_CHANNEL_ARGUMENTS_H

#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpcpp/resource_quota.h>
#include <grpcpp/support/config.h>

#include <list>
#include <vector>

namespace grpc {
class ChannelCredentials;
namespace testing {
class ChannelArgumentsTest;
}

class ChannelArguments {
 public:
  ChannelArguments();
  ~ChannelArguments();

  ChannelArguments(const ChannelArguments& other);
  ChannelArguments& operator=(ChannelArguments other) {
    Swap(other);
    return *this;
  }

  void Swap(ChannelArguments& other);

  void SetChannelArgs(grpc_channel_args* channel_args) const;

  void SetSslTargetNameOverride(const std::string& name);

  void SetCompressionAlgorithm(grpc_compression_algorithm algorithm);

  void SetGrpclbFallbackTimeout(int fallback_timeout);

  void SetSocketMutator(grpc_socket_mutator* mutator);

  void SetUserAgentPrefix(const std::string& user_agent_prefix);

  void SetResourceQuota(const grpc::ResourceQuota& resource_quota);

  void SetMaxReceiveMessageSize(int size);
  void SetMaxSendMessageSize(int size);

  void SetLoadBalancingPolicyName(const std::string& lb_policy_name);

  void SetServiceConfigJSON(const std::string& service_config_json);

  void SetInt(const std::string& key, int value);

  void SetPointer(const std::string& key, void* value);

  void SetPointerWithVtable(const std::string& key, void* value,
                            const grpc_arg_pointer_vtable* vtable);

  void SetString(const std::string& key, const std::string& value);

  grpc_channel_args c_channel_args() const {
    grpc_channel_args out;
    out.num_args = args_.size();
    out.args = args_.empty() ? nullptr : const_cast<grpc_arg*>(&args_[0]);
    return out;
  }

 private:
  friend class grpc::ChannelCredentials;
  friend class grpc::testing::ChannelArgumentsTest;

  struct PointerVtableMembers {
    static void* Copy(void* in) { return in; }
    static void Destroy(void* ) {}
    static int Compare(void* a, void* b) {
      if (a < b) return -1;
      if (a > b) return 1;
      return 0;
    }
  };

  std::string GetSslTargetNameOverride() const;

  std::vector<grpc_arg> args_;
  std::list<std::string> strings_;
};

}

#endif
