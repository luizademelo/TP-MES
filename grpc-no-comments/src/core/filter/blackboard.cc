
// Copyright 2024 gRPC authors.

#include "src/core/filter/blackboard.h"

namespace grpc_core {

RefCountedPtr<Blackboard::Entry> Blackboard::Get(UniqueTypeName type,
                                                 const std::string& key) const {
  auto it = map_.find(std::pair(type, key));
  if (it == map_.end()) return nullptr;
  return it->second;
}

void Blackboard::Set(UniqueTypeName type, const std::string& key,
                     RefCountedPtr<Entry> entry) {
  map_[std::pair(type, key)] = std::move(entry);
}

}
