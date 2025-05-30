
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_TEST_SERVER_CONTEXT_TEST_SPOUSE_H
#define GRPCPP_TEST_SERVER_CONTEXT_TEST_SPOUSE_H

#include <grpcpp/server_context.h>

#include <map>

namespace grpc {
namespace testing {

class ServerContextTestSpouse {
 public:
  explicit ServerContextTestSpouse(ServerContext* ctx) : ctx_(ctx) {}

  void AddClientMetadata(const std::string& key, const std::string& value) {
    client_metadata_storage_.insert(
        std::pair<std::string, std::string>(key, value));
    ctx_->client_metadata_.map()->clear();
    for (const auto& item : client_metadata_storage_) {
      ctx_->client_metadata_.map()->insert(
          std::pair<grpc::string_ref, grpc::string_ref>(
              item.first.c_str(),
              grpc::string_ref(item.second.data(), item.second.size())));
    }
  }

  std::multimap<std::string, std::string> GetInitialMetadata() const {
    return ctx_->initial_metadata_;
  }

  std::multimap<std::string, std::string> GetTrailingMetadata() const {
    return ctx_->trailing_metadata_;
  }

 private:
  ServerContext* ctx_;
  std::multimap<std::string, std::string> client_metadata_storage_;
};

}
}

#endif
