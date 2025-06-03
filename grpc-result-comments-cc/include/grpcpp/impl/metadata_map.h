Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_METADATA_MAP_H
#define GRPCPP_IMPL_METADATA_MAP_H

#include <grpc/grpc.h>
#include <grpcpp/support/slice.h>

#include <map>

namespace grpc {

namespace internal {

// Key used for binary error details in gRPC metadata
const char kBinaryErrorDetailsKey[] = "grpc-status-details-bin";

// Class for managing gRPC metadata in both array and map formats
class MetadataMap {
 public:
  // Constructor - initializes the metadata array
  MetadataMap() { Setup(); }

  // Destructor - cleans up the metadata array
  ~MetadataMap() { Destroy(); }

  // Retrieves binary error details from metadata
  // Returns: string containing binary error details if found, empty string otherwise
  std::string GetBinaryErrorDetails() {
    // If metadata is already in map format, search there
    if (filled_) {
      auto iter = map_.find(kBinaryErrorDetailsKey);
      if (iter != map_.end()) {
        return std::string(iter->second.begin(), iter->second.length());
      }
    }
    // Otherwise search in the array format
    else {
      for (size_t i = 0; i < arr_.count; i++) {
        // Compare metadata key with binary error details key
        if (strncmp(reinterpret_cast<const char*>(
                        GRPC_SLICE_START_PTR(arr_.metadata[i].key)),
                    kBinaryErrorDetailsKey,
                    GRPC_SLICE_LENGTH(arr_.metadata[i].key)) == 0) {
          // Return the corresponding value if key matches
          return std::string(reinterpret_cast<const char*>(
                                 GRPC_SLICE_START_PTR(arr_.metadata[i].value)),
                             GRPC_SLICE_LENGTH(arr_.metadata[i].value));
        }
      }
    }
    return std::string();
  }

  // Returns a pointer to the metadata map, filling it first if needed
  std::multimap<grpc::string_ref, grpc::string_ref>* map() {
    FillMap();
    return &map_;
  }

  // Returns a pointer to the raw metadata array
  grpc_metadata_array* arr() { return &arr_; }

  // Resets the metadata container to its initial state
  void Reset() {
    filled_ = false;
    map_.clear();
    Destroy();
    Setup();
  }

 private:
  bool filled_ = false;  // Flag indicating if metadata has been converted to map format
  grpc_metadata_array arr_;  // Raw metadata array
  std::multimap<grpc::string_ref, grpc::string_ref> map_;  // Metadata in map format

  // Cleans up the metadata array
  void Destroy() { grpc_metadata_array_destroy(&arr_); }

  // Initializes the metadata array
  void Setup() { memset(&arr_, 0, sizeof(arr_)); }

  // Converts metadata from array format to map format
  void FillMap() {
    if (filled_) return;  // Already converted
    filled_ = true;
    
    // Convert each metadata key-value pair from array to map
    for (size_t i = 0; i < arr_.count; i++) {
      map_.insert(std::pair<grpc::string_ref, grpc::string_ref>(
          StringRefFromSlice(&arr_.metadata[i].key),
          StringRefFromSlice(&arr_.metadata[i].value)));
    }
  }
};

}  // namespace internal

}  // namespace grpc

#endif  // GRPCPP_IMPL_METADATA_MAP_H
```

Key improvements in the comments:
1. Added class-level documentation explaining the purpose of MetadataMap
2. Documented all public methods with their purposes and return values
3. Added comments for private members to explain their roles
4. Explained the conversion process between array and map formats
5. Added clear section comments for different parts of the code
6. Maintained consistency in comment style and detail level
7. Added namespace closing comments for better readability
8. Documented the special binary error details key constant

The comments now provide a comprehensive understanding of the code's functionality while maintaining readability and avoiding redundancy.