
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_UNIQUE_TYPE_NAME_H
#define GRPC_SRC_CORE_UTIL_UNIQUE_TYPE_NAME_H

#include <grpc/support/port_platform.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class UniqueTypeName {
 public:

  class Factory {
   public:
    explicit Factory(absl::string_view name) : name_(new std::string(name)) {}

    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    UniqueTypeName Create() const { return UniqueTypeName(*name_); }

   private:
    std::string* name_;
  };

  bool operator==(const UniqueTypeName& other) const {
    return name_.data() == other.name_.data();
  }
  bool operator!=(const UniqueTypeName& other) const {
    return name_.data() != other.name_.data();
  }
  bool operator<(const UniqueTypeName& other) const {
    return name_.data() < other.name_.data();
  }

  template <typename H>
  friend H AbslHashValue(H h, const UniqueTypeName& name) {
    return H::combine(std::move(h),
                      static_cast<const void*>(name.name_.data()));
  }

  int Compare(const UniqueTypeName& other) const {
    return QsortCompare(name_.data(), other.name_.data());
  }

  absl::string_view name() const { return name_; }

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const UniqueTypeName& name) {
    sink.Append(name.name_);
  }

 private:
  explicit UniqueTypeName(absl::string_view name) : name_(name) {}

  absl::string_view name_;
};

template <typename T>
UniqueTypeName UniqueTypeNameFor() {
  static UniqueTypeName::Factory factory(T::TypeName());
  return factory.Create();
}

}

#define GRPC_UNIQUE_TYPE_NAME_HERE(name)                               \
  ([] {                                                                \
    static const ::grpc_core::UniqueTypeName::Factory factory((name)); \
    return factory.Create();                                           \
  }())

#endif
