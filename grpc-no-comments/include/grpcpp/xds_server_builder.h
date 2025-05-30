
// Copyright 2020 gRPC authors.

#ifndef GRPCPP_XDS_SERVER_BUILDER_H
#define GRPCPP_XDS_SERVER_BUILDER_H

#include <grpc/support/port_platform.h>
#include <grpcpp/server_builder.h>

namespace grpc {

class XdsServerServingStatusNotifierInterface {
 public:
  struct ServingStatusUpdate {
    grpc::Status status;
  };

  virtual ~XdsServerServingStatusNotifierInterface() = default;

  virtual void OnServingStatusUpdate(std::string uri,
                                     ServingStatusUpdate update) = 0;
};

class XdsServerBuilder : public grpc::ServerBuilder {
 public:
  // NOTE: class experimental_type is not part of the public API of this class

  class experimental_type : public grpc::ServerBuilder::experimental_type {
   public:
    explicit experimental_type(XdsServerBuilder* builder)
        : ServerBuilder::experimental_type(builder), builder_(builder) {}

    void set_drain_grace_time(int drain_grace_time_ms) {
      builder_->drain_grace_time_ms_ = drain_grace_time_ms;
    }

   private:
    XdsServerBuilder* builder_;
  };

  void set_status_notifier(XdsServerServingStatusNotifierInterface* notifier) {
    notifier_ = notifier;
  }

  /// NOTE: The function experimental() is not stable public API. It is a view

  experimental_type experimental() { return experimental_type(this); }

 private:

  ChannelArguments BuildChannelArgs() override;

  static void OnServingStatusUpdate(void* user_data, const char* uri,
                                    grpc_serving_status_update update) {
    if (user_data == nullptr) return;
    XdsServerServingStatusNotifierInterface* notifier =
        static_cast<XdsServerServingStatusNotifierInterface*>(user_data);
    notifier->OnServingStatusUpdate(
        uri, {grpc::Status(static_cast<StatusCode>(update.code),
                           update.error_message)});
  }

  XdsServerServingStatusNotifierInterface* notifier_ = nullptr;
  int drain_grace_time_ms_ = -1;
};

}

#endif
