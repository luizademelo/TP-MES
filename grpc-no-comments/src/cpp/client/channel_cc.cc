
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/slice.h>

#include <atomic>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/iomgr.h"

namespace grpc {

Channel::Channel(
    const std::string& host, grpc_channel* channel,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators)
    : host_(host), c_channel_(channel) {
  interceptor_creators_ = std::move(interceptor_creators);
}

Channel::~Channel() {
  grpc_channel_destroy(c_channel_);
  CompletionQueue* callback_cq = callback_cq_.load(std::memory_order_relaxed);
  if (callback_cq != nullptr) {
    if (grpc_iomgr_run_in_background()) {

      callback_cq->Shutdown();
    } else {
      CompletionQueue::ReleaseCallbackAlternativeCQ(callback_cq);
    }
  }
}

namespace {

inline grpc_slice SliceFromArray(const char* arr, size_t len) {
  return grpc_slice_from_copied_buffer(arr, len);
}

std::string GetChannelInfoField(grpc_channel* channel,
                                grpc_channel_info* channel_info,
                                char*** channel_info_field) {
  char* value = nullptr;
  memset(channel_info, 0, sizeof(*channel_info));
  *channel_info_field = &value;
  grpc_channel_get_info(channel, channel_info);
  if (value == nullptr) return "";
  std::string result = value;
  gpr_free(value);
  return result;
}

}

std::string Channel::GetLoadBalancingPolicyName() const {
  grpc_channel_info channel_info;
  return GetChannelInfoField(c_channel_, &channel_info,
                             &channel_info.lb_policy_name);
}

std::string Channel::GetServiceConfigJSON() const {
  grpc_channel_info channel_info;
  return GetChannelInfoField(c_channel_, &channel_info,
                             &channel_info.service_config_json);
}

namespace experimental {

void ChannelResetConnectionBackoff(Channel* channel) {
  grpc_channel_reset_connect_backoff(channel->c_channel_);
}

}

grpc::internal::Call Channel::CreateCallInternal(
    const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
    grpc::CompletionQueue* cq, size_t interceptor_pos) {
  const bool kRegistered = method.channel_tag() && context->authority().empty();
  grpc_call* c_call = nullptr;
  if (kRegistered) {
    c_call = grpc_channel_create_registered_call(
        c_channel_, context->propagate_from_call_,
        context->propagation_options_.c_bitmask(), cq->cq(),
        method.channel_tag(), context->raw_deadline(), nullptr);
  } else {
    const ::std::string* host_str = nullptr;
    if (!context->authority_.empty()) {
      host_str = &context->authority_;
    } else if (!host_.empty()) {
      host_str = &host_;
    }
    grpc_slice method_slice =
        SliceFromArray(method.name(), strlen(method.name()));
    grpc_slice host_slice;
    if (host_str != nullptr) {
      host_slice = grpc::SliceFromCopiedString(*host_str);
    }
    c_call = grpc_channel_create_call(
        c_channel_, context->propagate_from_call_,
        context->propagation_options_.c_bitmask(), cq->cq(), method_slice,
        host_str == nullptr ? nullptr : &host_slice, context->raw_deadline(),
        nullptr);
    grpc_slice_unref(method_slice);
    if (host_str != nullptr) {
      grpc_slice_unref(host_slice);
    }
  }
  grpc_census_call_set_context(c_call, context->census_context());

  auto* info = context->set_client_rpc_info(
      method.name(), method.suffix_for_stats(), method.method_type(), this,
      interceptor_creators_, interceptor_pos);
  context->set_call(c_call, shared_from_this());

  return grpc::internal::Call(c_call, this, cq, info);
}

grpc::internal::Call Channel::CreateCall(
    const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
    CompletionQueue* cq) {
  return CreateCallInternal(method, context, cq, 0);
}

void Channel::PerformOpsOnCall(grpc::internal::CallOpSetInterface* ops,
                               grpc::internal::Call* call) {
  ops->FillOps(
      call);
}

void* Channel::RegisterMethod(const char* method) {
  return grpc_channel_register_call(
      c_channel_, method, host_.empty() ? nullptr : host_.c_str(), nullptr);
}

grpc_connectivity_state Channel::GetState(bool try_to_connect) {
  return grpc_channel_check_connectivity_state(c_channel_, try_to_connect);
}

namespace {

class TagSaver final : public grpc::internal::CompletionQueueTag {
 public:
  explicit TagSaver(void* tag) : tag_(tag) {}
  ~TagSaver() override {}
  bool FinalizeResult(void** tag, bool* ) override {
    *tag = tag_;
    delete this;
    return true;
  }

 private:
  void* tag_;
};

}

void Channel::NotifyOnStateChangeImpl(grpc_connectivity_state last_observed,
                                      gpr_timespec deadline,
                                      grpc::CompletionQueue* cq, void* tag) {
  TagSaver* tag_saver = new TagSaver(tag);
  grpc_channel_watch_connectivity_state(c_channel_, last_observed, deadline,
                                        cq->cq(), tag_saver);
}

bool Channel::WaitForStateChangeImpl(grpc_connectivity_state last_observed,
                                     gpr_timespec deadline) {
  grpc::CompletionQueue cq;
  bool ok = false;
  void* tag = nullptr;
  NotifyOnStateChangeImpl(last_observed, deadline, &cq, nullptr);
  cq.Next(&tag, &ok);
  CHECK_EQ(tag, nullptr);
  return ok;
}

namespace {
class ShutdownCallback : public grpc_completion_queue_functor {
 public:
  ShutdownCallback() {
    functor_run = &ShutdownCallback::Run;

    inlineable = true;
  }

  void TakeCQ(grpc::CompletionQueue* cq) { cq_ = cq; }

  static void Run(grpc_completion_queue_functor* cb, int) {
    auto* callback = static_cast<ShutdownCallback*>(cb);
    delete callback->cq_;
    delete callback;
  }

 private:
  grpc::CompletionQueue* cq_ = nullptr;
};
}

::grpc::CompletionQueue* Channel::CallbackCQ() {

  CompletionQueue* callback_cq = callback_cq_.load(std::memory_order_acquire);
  if (callback_cq != nullptr) {
    return callback_cq;
  }

  grpc::internal::MutexLock l(&mu_);
  callback_cq = callback_cq_.load(std::memory_order_relaxed);
  if (callback_cq == nullptr) {
    if (grpc_iomgr_run_in_background()) {

      auto* shutdown_callback = new ShutdownCallback;
      callback_cq = new grpc::CompletionQueue(grpc_completion_queue_attributes{
          GRPC_CQ_CURRENT_VERSION, GRPC_CQ_CALLBACK, GRPC_CQ_DEFAULT_POLLING,
          shutdown_callback});

      shutdown_callback->TakeCQ(callback_cq);
    } else {

      callback_cq = CompletionQueue::CallbackAlternativeCQ();
    }
    callback_cq_.store(callback_cq, std::memory_order_release);
  }
  return callback_cq;
}

}
