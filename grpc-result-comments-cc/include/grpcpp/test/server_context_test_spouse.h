Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_TEST_SERVER_CONTEXT_TEST_SPOUSE_H
#define GRPCPP_TEST_SERVER_CONTEXT_TEST_SPOUSE_H

#include <grpcpp/server_context.h>  // Main gRPC server context header
#include <map>                     // Standard library map container

namespace grpc {
namespace testing {

// Test utility class that provides controlled access to ServerContext internals
// for testing purposes. This class acts as a "friend" to ServerContext,
// allowing tests to manipulate and inspect normally private members.
class ServerContextTestSpouse {
 public:
  // Constructor takes a pointer to the ServerContext to be tested
  explicit ServerContextTestSpouse(ServerContext* ctx) : ctx_(ctx) {}

  // Adds a key-value pair to the client metadata (headers) in the ServerContext
  // This simulates client sending metadata to the server
  // @param key The metadata key to add
  // @param value The metadata value to add
  void AddClientMetadata(const std::string& key, const std::string& value) {
    // Store the metadata in local storage
    client_metadata_storage_.insert(
        std::pair<std::string, std::string>(key, value));
    
    // Clear existing metadata in the ServerContext
    ctx_->client_metadata_.map()->clear();
    
    // Rebuild the ServerContext metadata from our local storage
    for (const auto& item : client_metadata_storage_) {
      ctx_->client_metadata_.map()->insert(
          std::pair<grpc::string_ref, grpc::string_ref>(
              item.first.c_str(),
              grpc::string_ref(item.second.data(), item.second.size())));
    }
  }

  // Retrieves the initial metadata (headers to be sent to client) from the ServerContext
  // @return A multimap containing all initial metadata key-value pairs
  std::multimap<std::string, std::string> GetInitialMetadata() const {
    return ctx_->initial_metadata_;
  }

  // Retrieves the trailing metadata (trailers to be sent to client) from the ServerContext
  // @return A multimap containing all trailing metadata key-value pairs
  std::multimap<std::string, std::string> GetTrailingMetadata() const {
    return ctx_->trailing_metadata_;
  }

 private:
  ServerContext* ctx_;  // Pointer to the ServerContext being tested
  // Local storage for client metadata to maintain state between operations
  std::multimap<std::string, std::string> client_metadata_storage_;
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPCPP_TEST_SERVER_CONTEXT_TEST_SPOUSE_H
```

The comments explain:
1. The overall purpose of the class (testing utility for ServerContext)
2. Each method's functionality and parameters
3. The internal logic of the AddClientMetadata method
4. The purpose of private member variables
5. Namespace usage and header guard purpose

The comments are designed to help future developers understand:
- Why this class exists (testing purposes)
- How to use its methods
- The internal implementation details
- The relationship between this class and ServerContext