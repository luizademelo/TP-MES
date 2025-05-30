
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_CLIENT_HELPER_H
#define GRPC_TEST_CPP_INTEROP_CLIENT_HELPER_H

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/support/channel_arguments.h>

#include <functional>
#include <memory>
#include <unordered_map>

#include "src/core/lib/surface/call_test_only.h"
#include "src/core/lib/transport/transport.h"

namespace grpc {
namespace testing {

std::string GetServiceAccountJsonKey();

std::string GetOauth2AccessToken();

void UpdateActions(
    std::unordered_map<std::string, std::function<bool()>>* actions);

std::shared_ptr<Channel> CreateChannelForTestCase(
    const std::string& test_case,
    std::vector<
        std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators = {},
    ChannelArguments channel_args = ChannelArguments());

class InteropClientContextInspector {
 public:
  explicit InteropClientContextInspector(const grpc::ClientContext& context)
      : context_(context) {}

  grpc_compression_algorithm GetCallCompressionAlgorithm() const {
    return grpc_call_test_only_get_compression_algorithm(context_.call_);
  }

  bool WasCompressed() const {
    return (grpc_call_test_only_get_message_flags(context_.call_) &
            GRPC_WRITE_INTERNAL_COMPRESS) ||
           (grpc_call_test_only_get_message_flags(context_.call_) &
            GRPC_WRITE_INTERNAL_TEST_ONLY_WAS_COMPRESSED);
  }

 private:
  const grpc::ClientContext& context_;
};

class AdditionalMetadataInterceptor : public experimental::Interceptor {
 public:
  explicit AdditionalMetadataInterceptor(
      std::multimap<std::string, std::string> additional_metadata)
      : additional_metadata_(std::move(additional_metadata)) {}

  void Intercept(experimental::InterceptorBatchMethods* methods) override {
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
      std::multimap<std::string, std::string>* metadata =
          methods->GetSendInitialMetadata();
      for (const auto& entry : additional_metadata_) {
        metadata->insert(entry);
      }
    }
    methods->Proceed();
  }

 private:
  const std::multimap<std::string, std::string> additional_metadata_;
};

class AdditionalMetadataInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  explicit AdditionalMetadataInterceptorFactory(
      std::multimap<std::string, std::string> additional_metadata)
      : additional_metadata_(std::move(additional_metadata)) {}

  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* ) override {
    return new AdditionalMetadataInterceptor(additional_metadata_);
  }

  const std::multimap<std::string, std::string> additional_metadata_;
};

class MetadataAndStatusLoggerInterceptor : public experimental::Interceptor {
 public:
  explicit MetadataAndStatusLoggerInterceptor() {}

  void Intercept(experimental::InterceptorBatchMethods* methods) override;
};

class MetadataAndStatusLoggerInterceptorFactory
    : public experimental::ClientInterceptorFactoryInterface {
 public:
  explicit MetadataAndStatusLoggerInterceptorFactory() {}

  experimental::Interceptor* CreateClientInterceptor(
      experimental::ClientRpcInfo* ) override {
    return new MetadataAndStatusLoggerInterceptor();
  }
};

}
}

#endif
