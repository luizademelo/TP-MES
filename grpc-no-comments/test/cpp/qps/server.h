
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_SERVER_H
#define GRPC_TEST_CPP_QPS_SERVER_H

#include <grpc/support/cpu.h>
#include <grpcpp/channel.h>
#include <grpcpp/resource_quota.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

#include <vector>

#include "absl/log/log.h"
#include "src/core/ext/transport/chaotic_good/chaotic_good.h"
#include "src/core/transport/endpoint_transport.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/control.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "test/core/end2end/data/ssl_test_data.h"
#include "test/core/test_util/port.h"
#include "test/cpp/qps/usage_timer.h"
#include "test/cpp/util/test_credentials_provider.h"

namespace grpc {
namespace testing {

class Server {
 public:
  explicit Server(const ServerConfig& config)
      : timer_(new UsageTimer), last_reset_poll_count_(0) {
    cores_ = gpr_cpu_num_cores();
    if (config.port()) {
      port_ = config.port();
    } else {
      port_ = grpc_pick_unused_port_or_die();
    }
  }
  virtual ~Server() {}

  ServerStats Mark(bool reset) {
    UsageTimer::Result timer_result;
    int cur_poll_count = GetPollCount();
    int poll_count = cur_poll_count - last_reset_poll_count_;
    if (reset) {
      std::unique_ptr<UsageTimer> timer(new UsageTimer);
      timer.swap(timer_);
      timer_result = timer->Mark();
      last_reset_poll_count_ = cur_poll_count;
    } else {
      timer_result = timer_->Mark();
    }

    ServerStats stats;
    stats.set_time_elapsed(timer_result.wall);
    stats.set_time_system(timer_result.system);
    stats.set_time_user(timer_result.user);
    stats.set_total_cpu_time(timer_result.total_cpu_time);
    stats.set_idle_cpu_time(timer_result.idle_cpu_time);
    stats.set_cq_poll_count(poll_count);
    return stats;
  }

  static bool SetPayload(PayloadType type, int size, Payload* payload) {

    if (type != PayloadType::COMPRESSABLE) {
      return false;
    }
    payload->set_type(type);

    if (payload->body().length() != static_cast<size_t>(size)) {
      std::unique_ptr<char[]> body(new char[size]());
      payload->set_body(body.get(), size);
    }
    return true;
  }

  int port() const { return port_; }
  int cores() const { return cores_; }
  static std::shared_ptr<ServerCredentials> CreateServerCredentials(
      const ServerConfig& config) {
    if (config.has_security_params()) {
      std::string type;
      if (config.security_params().cred_type().empty()) {
        type = kTlsCredentialsType;
      } else {
        type = config.security_params().cred_type();
      }

      return GetCredentialsProvider()->GetServerCredentials(type);
    } else {
      return InsecureServerCredentials();
    }
  }

  virtual int GetPollCount() {

    return 0;
  }

  virtual std::shared_ptr<Channel> InProcessChannel(
      const ChannelArguments& args) = 0;

 protected:
  static void ApplyConfigToBuilder(const ServerConfig& config,
                                   ServerBuilder* builder) {
    if (config.resource_quota_size() > 0) {
      builder->SetResourceQuota(ResourceQuota("AsyncQpsServerTest")
                                    .Resize(config.resource_quota_size()));
    }
    for (const auto& channel_arg : config.channel_args()) {
      switch (channel_arg.value_case()) {
        case ChannelArg::kStrValue:
          builder->AddChannelArgument(channel_arg.name(),
                                      channel_arg.str_value());
          break;
        case ChannelArg::kIntValue:
          builder->AddChannelArgument(channel_arg.name(),
                                      channel_arg.int_value());
          break;
        case ChannelArg::VALUE_NOT_SET:
          LOG(ERROR) << "Channel arg '" << channel_arg.name()
                     << "' does not have a value";
          break;
      }
    }
    switch (config.protocol()) {
      case Protocol::HTTP2:
        break;
      case Protocol::CHAOTIC_GOOD:
        builder->AddChannelArgument(
            GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS,
            std::string(grpc_core::chaotic_good::WireFormatPreferences()));
        break;
      default:
        LOG(FATAL) << "Unknown protocol: " << config.protocol();
    }
  }

 private:
  int port_;
  int cores_;
  std::unique_ptr<UsageTimer> timer_;
  int last_reset_poll_count_;
};

std::unique_ptr<Server> CreateSynchronousServer(const ServerConfig& config);
std::unique_ptr<Server> CreateAsyncServer(const ServerConfig& config);
std::unique_ptr<Server> CreateAsyncGenericServer(const ServerConfig& config);
std::unique_ptr<Server> CreateCallbackServer(const ServerConfig& config);

}
}

#endif
