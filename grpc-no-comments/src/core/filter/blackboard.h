
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_FILTER_BLACKBOARD_H
#define GRPC_SRC_CORE_FILTER_BLACKBOARD_H

#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/string_view.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class Blackboard : public RefCounted<Blackboard> {
 public:

  class Entry : public RefCounted<Entry> {};

  template <typename T>
  RefCountedPtr<T> Get(const std::string& key) const {
    return Get(T::Type(), key).template TakeAsSubclass<T>();
  }

  template <typename T>
  void Set(const std::string& key, RefCountedPtr<T> entry) {
    Set(T::Type(), key, std::move(entry));
  }

 private:
  RefCountedPtr<Entry> Get(UniqueTypeName type, const std::string& key) const;
  void Set(UniqueTypeName type, const std::string& key,
           RefCountedPtr<Entry> entry);

  absl::flat_hash_map<std::pair<UniqueTypeName, std::string>,
                      RefCountedPtr<Entry>>
      map_;
};

}

#endif
