
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_METADATA_MAP_H
#define GRPCPP_IMPL_METADATA_MAP_H

#include <grpc/grpc.h>
#include <grpcpp/support/slice.h>

#include <map>

namespace grpc {

namespace internal {

const char kBinaryErrorDetailsKey[] = "grpc-status-details-bin";

class MetadataMap {
 public:
  MetadataMap() { Setup(); }

  ~MetadataMap() { Destroy(); }

  std::string GetBinaryErrorDetails() {

    if (filled_) {
      auto iter = map_.find(kBinaryErrorDetailsKey);
      if (iter != map_.end()) {
        return std::string(iter->second.begin(), iter->second.length());
      }
    }

    else {
      for (size_t i = 0; i < arr_.count; i++) {
        if (strncmp(reinterpret_cast<const char*>(
                        GRPC_SLICE_START_PTR(arr_.metadata[i].key)),
                    kBinaryErrorDetailsKey,
                    GRPC_SLICE_LENGTH(arr_.metadata[i].key)) == 0) {
          return std::string(reinterpret_cast<const char*>(
                                 GRPC_SLICE_START_PTR(arr_.metadata[i].value)),
                             GRPC_SLICE_LENGTH(arr_.metadata[i].value));
        }
      }
    }
    return std::string();
  }

  std::multimap<grpc::string_ref, grpc::string_ref>* map() {
    FillMap();
    return &map_;
  }
  grpc_metadata_array* arr() { return &arr_; }

  void Reset() {
    filled_ = false;
    map_.clear();
    Destroy();
    Setup();
  }

 private:
  bool filled_ = false;
  grpc_metadata_array arr_;
  std::multimap<grpc::string_ref, grpc::string_ref> map_;

  void Destroy() { grpc_metadata_array_destroy(&arr_); }

  void Setup() { memset(&arr_, 0, sizeof(arr_)); }

  void FillMap() {
    if (filled_) return;
    filled_ = true;
    for (size_t i = 0; i < arr_.count; i++) {

      map_.insert(std::pair<grpc::string_ref, grpc::string_ref>(
          StringRefFromSlice(&arr_.metadata[i].key),
          StringRefFromSlice(&arr_.metadata[i].value)));
    }
  }
};
}

}

#endif
