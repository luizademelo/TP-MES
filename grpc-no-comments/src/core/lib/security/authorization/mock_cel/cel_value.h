// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_VALUE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_VALUE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"

namespace grpc_core {
namespace mock_cel {

class CelMap {
 public:
  CelMap() = default;
};

class CelValue {
 public:

  CelValue() : CelValue(nullptr) {}

  static CelValue CreateNull() { return CelValue(nullptr); }

  static CelValue CreateInt64(int64_t ) { return CreateNull(); }

  static CelValue CreateUint64(uint64_t ) { return CreateNull(); }

  static CelValue CreateStringView(absl::string_view ) {
    return CreateNull();
  }

  static CelValue CreateString(const std::string* ) {
    return CreateNull();
  }

  static CelValue CreateMap(const CelMap* ) { return CreateNull(); }

 private:

  template <class T>
  explicit CelValue(T ) {}
};

class ContainerBackedMapImpl : public CelMap {
 public:
  ContainerBackedMapImpl() = default;

  static std::unique_ptr<CelMap> Create(
      absl::Span<std::pair<CelValue, CelValue>> ) {
    return std::make_unique<ContainerBackedMapImpl>();
  }
};

}
}

#endif
