
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_IMPL_INTERCEPTOR_COMMON_H
#define GRPCPP_IMPL_INTERCEPTOR_COMMON_H

#include <grpc/impl/grpc_types.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/intercepted_channel.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/server_interceptor.h>

#include <array>
#include <functional>

#include "absl/log/absl_check.h"

namespace grpc {
namespace internal {

class InterceptorBatchMethodsImpl
    : public experimental::InterceptorBatchMethods {
 public:
  InterceptorBatchMethodsImpl() {
    for (auto i = static_cast<experimental::InterceptionHookPoints>(0);
         i < experimental::InterceptionHookPoints::NUM_INTERCEPTION_HOOKS;
         i = static_cast<experimental::InterceptionHookPoints>(
             static_cast<size_t>(i) + 1)) {
      hooks_[static_cast<size_t>(i)] = false;
    }
  }

  ~InterceptorBatchMethodsImpl() override {}

  bool QueryInterceptionHookPoint(
      experimental::InterceptionHookPoints type) override {
    return hooks_[static_cast<size_t>(type)];
  }

  void Proceed() override {
    if (call_->client_rpc_info() != nullptr) {
      return ProceedClient();
    }
    ABSL_CHECK_NE(call_->server_rpc_info(), nullptr);
    ProceedServer();
  }

  void Hijack() override {

    ABSL_CHECK(!reverse_ && ops_ != nullptr &&
               call_->client_rpc_info() != nullptr);

    ABSL_CHECK(!ran_hijacking_interceptor_);
    auto* rpc_info = call_->client_rpc_info();
    rpc_info->hijacked_ = true;
    rpc_info->hijacked_interceptor_ = current_interceptor_index_;
    ClearHookPoints();
    ops_->SetHijackingState();
    ran_hijacking_interceptor_ = true;
    rpc_info->RunInterceptor(this, current_interceptor_index_);
  }

  void AddInterceptionHookPoint(experimental::InterceptionHookPoints type) {
    hooks_[static_cast<size_t>(type)] = true;
  }

  ByteBuffer* GetSerializedSendMessage() override {
    ABSL_CHECK_NE(orig_send_message_, nullptr);
    if (*orig_send_message_ != nullptr) {
      ABSL_CHECK(serializer_(*orig_send_message_).ok());
      *orig_send_message_ = nullptr;
    }
    return send_message_;
  }

  const void* GetSendMessage() override {
    ABSL_CHECK_NE(orig_send_message_, nullptr);
    return *orig_send_message_;
  }

  void ModifySendMessage(const void* message) override {
    ABSL_CHECK_NE(orig_send_message_, nullptr);
    *orig_send_message_ = message;
  }

  bool GetSendMessageStatus() override { return !*fail_send_message_; }

  std::multimap<std::string, std::string>* GetSendInitialMetadata() override {
    return send_initial_metadata_;
  }

  Status GetSendStatus() override {
    return Status(static_cast<StatusCode>(*code_), *error_message_,
                  *error_details_);
  }

  void ModifySendStatus(const Status& status) override {
    *code_ = static_cast<grpc_status_code>(status.error_code());
    *error_details_ = status.error_details();
    *error_message_ = status.error_message();
  }

  std::multimap<std::string, std::string>* GetSendTrailingMetadata() override {
    return send_trailing_metadata_;
  }

  void* GetRecvMessage() override { return recv_message_; }

  std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvInitialMetadata()
      override {
    return recv_initial_metadata_->map();
  }

  Status* GetRecvStatus() override { return recv_status_; }

  void FailHijackedSendMessage() override {
    ABSL_CHECK(hooks_[static_cast<size_t>(
        experimental::InterceptionHookPoints::PRE_SEND_MESSAGE)]);
    *fail_send_message_ = true;
  }

  std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvTrailingMetadata()
      override {
    return recv_trailing_metadata_->map();
  }

  void SetSendMessage(ByteBuffer* buf, const void** msg,
                      bool* fail_send_message,
                      std::function<Status(const void*)> serializer) {
    send_message_ = buf;
    orig_send_message_ = msg;
    fail_send_message_ = fail_send_message;
    serializer_ = serializer;
  }

  void SetSendInitialMetadata(
      std::multimap<std::string, std::string>* metadata) {
    send_initial_metadata_ = metadata;
  }

  void SetSendStatus(grpc_status_code* code, std::string* error_details,
                     std::string* error_message) {
    code_ = code;
    error_details_ = error_details;
    error_message_ = error_message;
  }

  void SetSendTrailingMetadata(
      std::multimap<std::string, std::string>* metadata) {
    send_trailing_metadata_ = metadata;
  }

  void SetRecvMessage(void* message, bool* hijacked_recv_message_failed) {
    recv_message_ = message;
    hijacked_recv_message_failed_ = hijacked_recv_message_failed;
  }

  void SetRecvInitialMetadata(MetadataMap* map) {
    recv_initial_metadata_ = map;
  }

  void SetRecvStatus(Status* status) { recv_status_ = status; }

  void SetRecvTrailingMetadata(MetadataMap* map) {
    recv_trailing_metadata_ = map;
  }

  std::unique_ptr<ChannelInterface> GetInterceptedChannel() override {
    auto* info = call_->client_rpc_info();
    if (info == nullptr) {
      return std::unique_ptr<ChannelInterface>(nullptr);
    }

    return std::unique_ptr<ChannelInterface>(new InterceptedChannel(
        info->channel(), current_interceptor_index_ + 1));
  }

  void FailHijackedRecvMessage() override {
    ABSL_CHECK(hooks_[static_cast<size_t>(
        experimental::InterceptionHookPoints::PRE_RECV_MESSAGE)]);
    *hijacked_recv_message_failed_ = true;
  }

  void ClearState() {
    reverse_ = false;
    ran_hijacking_interceptor_ = false;
    ClearHookPoints();
  }

  void SetReverse() {
    reverse_ = true;
    ran_hijacking_interceptor_ = false;
    ClearHookPoints();
  }

  void SetCall(Call* call) { call_ = call; }

  void SetCallOpSetInterface(CallOpSetInterface* ops) { ops_ = ops; }

  bool InterceptorsListEmpty() {
    auto* client_rpc_info = call_->client_rpc_info();
    if (client_rpc_info != nullptr) {
      return client_rpc_info->interceptors_.empty();
    }

    auto* server_rpc_info = call_->server_rpc_info();
    return server_rpc_info == nullptr || server_rpc_info->interceptors_.empty();
  }

  bool RunInterceptors() {
    ABSL_CHECK(ops_);
    auto* client_rpc_info = call_->client_rpc_info();
    if (client_rpc_info != nullptr) {
      if (client_rpc_info->interceptors_.empty()) {
        return true;
      } else {
        RunClientInterceptors();
        return false;
      }
    }

    auto* server_rpc_info = call_->server_rpc_info();
    if (server_rpc_info == nullptr || server_rpc_info->interceptors_.empty()) {
      return true;
    }
    RunServerInterceptors();
    return false;
  }

  bool RunInterceptors(std::function<void(void)> f) {

    ABSL_CHECK_EQ(reverse_, true);
    ABSL_CHECK_EQ(call_->client_rpc_info(), nullptr);
    auto* server_rpc_info = call_->server_rpc_info();
    if (server_rpc_info == nullptr || server_rpc_info->interceptors_.empty()) {
      return true;
    }
    callback_ = std::move(f);
    RunServerInterceptors();
    return false;
  }

 private:
  void RunClientInterceptors() {
    auto* rpc_info = call_->client_rpc_info();
    if (!reverse_) {
      current_interceptor_index_ = 0;
    } else {
      if (rpc_info->hijacked_) {
        current_interceptor_index_ = rpc_info->hijacked_interceptor_;
      } else {
        current_interceptor_index_ = rpc_info->interceptors_.size() - 1;
      }
    }
    rpc_info->RunInterceptor(this, current_interceptor_index_);
  }

  void RunServerInterceptors() {
    auto* rpc_info = call_->server_rpc_info();
    if (!reverse_) {
      current_interceptor_index_ = 0;
    } else {
      current_interceptor_index_ = rpc_info->interceptors_.size() - 1;
    }
    rpc_info->RunInterceptor(this, current_interceptor_index_);
  }

  void ProceedClient() {
    auto* rpc_info = call_->client_rpc_info();
    if (rpc_info->hijacked_ && !reverse_ &&
        current_interceptor_index_ == rpc_info->hijacked_interceptor_ &&
        !ran_hijacking_interceptor_) {

      ClearHookPoints();
      ops_->SetHijackingState();
      ran_hijacking_interceptor_ = true;
      rpc_info->RunInterceptor(this, current_interceptor_index_);
      return;
    }
    if (!reverse_) {
      current_interceptor_index_++;

      if (current_interceptor_index_ < rpc_info->interceptors_.size()) {
        if (rpc_info->hijacked_ &&
            current_interceptor_index_ > rpc_info->hijacked_interceptor_) {

          ops_->ContinueFillOpsAfterInterception();
        } else {
          rpc_info->RunInterceptor(this, current_interceptor_index_);
        }
      } else {

        ops_->ContinueFillOpsAfterInterception();
      }
    } else {

      if (current_interceptor_index_ > 0) {

        current_interceptor_index_--;
        rpc_info->RunInterceptor(this, current_interceptor_index_);
      } else {

        ops_->ContinueFinalizeResultAfterInterception();
      }
    }
  }

  void ProceedServer() {
    auto* rpc_info = call_->server_rpc_info();
    if (!reverse_) {
      current_interceptor_index_++;
      if (current_interceptor_index_ < rpc_info->interceptors_.size()) {
        return rpc_info->RunInterceptor(this, current_interceptor_index_);
      } else if (ops_) {
        return ops_->ContinueFillOpsAfterInterception();
      }
    } else {

      if (current_interceptor_index_ > 0) {

        current_interceptor_index_--;
        return rpc_info->RunInterceptor(this, current_interceptor_index_);
      } else if (ops_) {
        return ops_->ContinueFinalizeResultAfterInterception();
      }
    }
    ABSL_CHECK(callback_);
    callback_();
  }

  void ClearHookPoints() {
    for (auto i = static_cast<experimental::InterceptionHookPoints>(0);
         i < experimental::InterceptionHookPoints::NUM_INTERCEPTION_HOOKS;
         i = static_cast<experimental::InterceptionHookPoints>(
             static_cast<size_t>(i) + 1)) {
      hooks_[static_cast<size_t>(i)] = false;
    }
  }

  std::array<bool,
             static_cast<size_t>(
                 experimental::InterceptionHookPoints::NUM_INTERCEPTION_HOOKS)>
      hooks_;

  size_t current_interceptor_index_ = 0;
  bool reverse_ = false;
  bool ran_hijacking_interceptor_ = false;
  Call* call_ = nullptr;

  CallOpSetInterface* ops_ = nullptr;
  std::function<void(void)> callback_;

  ByteBuffer* send_message_ = nullptr;
  bool* fail_send_message_ = nullptr;
  const void** orig_send_message_ = nullptr;
  std::function<Status(const void*)> serializer_;

  std::multimap<std::string, std::string>* send_initial_metadata_;

  grpc_status_code* code_ = nullptr;
  std::string* error_details_ = nullptr;
  std::string* error_message_ = nullptr;

  std::multimap<std::string, std::string>* send_trailing_metadata_ = nullptr;

  void* recv_message_ = nullptr;
  bool* hijacked_recv_message_failed_ = nullptr;

  MetadataMap* recv_initial_metadata_ = nullptr;

  Status* recv_status_ = nullptr;

  MetadataMap* recv_trailing_metadata_ = nullptr;
};

class CancelInterceptorBatchMethods
    : public experimental::InterceptorBatchMethods {
 public:
  bool QueryInterceptionHookPoint(
      experimental::InterceptionHookPoints type) override {
    return type == experimental::InterceptionHookPoints::PRE_SEND_CANCEL;
  }

  void Proceed() override {

  }

  void Hijack() override {

    ABSL_CHECK(false) << "It is illegal to call Hijack on a method which has a "
                         "Cancel notification";
  }

  ByteBuffer* GetSerializedSendMessage() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetSendMessage on a method which "
           "has a Cancel notification";
    return nullptr;
  }

  bool GetSendMessageStatus() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetSendMessageStatus on a method which "
           "has a Cancel notification";
    return false;
  }

  const void* GetSendMessage() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetOriginalSendMessage on a method which "
           "has a Cancel notification";
    return nullptr;
  }

  void ModifySendMessage(const void* ) override {
    ABSL_CHECK(false)
        << "It is illegal to call ModifySendMessage on a method which "
           "has a Cancel notification";
  }

  std::multimap<std::string, std::string>* GetSendInitialMetadata() override {
    ABSL_CHECK(false) << "It is illegal to call GetSendInitialMetadata on a "
                         "method which has a Cancel notification";
    return nullptr;
  }

  Status GetSendStatus() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetSendStatus on a method which "
           "has a Cancel notification";
    return Status();
  }

  void ModifySendStatus(const Status& ) override {
    ABSL_CHECK(false) << "It is illegal to call ModifySendStatus on a method "
                         "which has a Cancel notification";
  }

  std::multimap<std::string, std::string>* GetSendTrailingMetadata() override {
    ABSL_CHECK(false) << "It is illegal to call GetSendTrailingMetadata on a "
                         "method which has a Cancel notification";
    return nullptr;
  }

  void* GetRecvMessage() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetRecvMessage on a method which "
           "has a Cancel notification";
    return nullptr;
  }

  std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvInitialMetadata()
      override {
    ABSL_CHECK(false) << "It is illegal to call GetRecvInitialMetadata on a "
                         "method which has a Cancel notification";
    return nullptr;
  }

  Status* GetRecvStatus() override {
    ABSL_CHECK(false)
        << "It is illegal to call GetRecvStatus on a method which "
           "has a Cancel notification";
    return nullptr;
  }

  std::multimap<grpc::string_ref, grpc::string_ref>* GetRecvTrailingMetadata()
      override {
    ABSL_CHECK(false) << "It is illegal to call GetRecvTrailingMetadata on a "
                         "method which has a Cancel notification";
    return nullptr;
  }

  std::unique_ptr<ChannelInterface> GetInterceptedChannel() override {
    ABSL_CHECK(false) << "It is illegal to call GetInterceptedChannel on a "
                         "method which has a Cancel notification";
    return std::unique_ptr<ChannelInterface>(nullptr);
  }

  void FailHijackedRecvMessage() override {
    ABSL_CHECK(false) << "It is illegal to call FailHijackedRecvMessage on a "
                         "method which has a Cancel notification";
  }

  void FailHijackedSendMessage() override {
    ABSL_CHECK(false) << "It is illegal to call FailHijackedSendMessage on a "
                         "method which has a Cancel notification";
  }
};
}
}

#endif
