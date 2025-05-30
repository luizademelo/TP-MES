
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_SECURE_SERVER_CREDENTIALS_H
#define GRPC_SRC_CPP_SERVER_SECURE_SERVER_CREDENTIALS_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>

#include "src/cpp/server/thread_pool_interface.h"

namespace grpc {
class AuthMetadataProcessorAsyncWrapper final {
 public:
  static void Destroy(void* wrapper);

  static void Process(void* wrapper, grpc_auth_context* context,
                      const grpc_metadata* md, size_t num_md,
                      grpc_process_auth_metadata_done_cb cb, void* user_data);

  explicit AuthMetadataProcessorAsyncWrapper(
      const std::shared_ptr<AuthMetadataProcessor>& processor)
      : processor_(processor) {
    if (processor && processor->IsBlocking()) {
      thread_pool_.reset(CreateDefaultThreadPool());
    }
  }

 private:
  void InvokeProcessor(grpc_auth_context* context, const grpc_metadata* md,
                       size_t num_md, grpc_process_auth_metadata_done_cb cb,
                       void* user_data);
  std::unique_ptr<ThreadPoolInterface> thread_pool_;
  std::shared_ptr<AuthMetadataProcessor> processor_;
};

class SecureServerCredentials final : public ServerCredentials {
 public:
  explicit SecureServerCredentials(grpc_server_credentials* creds);

  void SetAuthMetadataProcessor(
      const std::shared_ptr<grpc::AuthMetadataProcessor>& processor) override;

 private:
  std::unique_ptr<grpc::AuthMetadataProcessorAsyncWrapper> processor_;
};

}

#endif
