
// Copyright 2015 gRPC authors.

#include "test/cpp/util/string_ref_helper.h"

namespace grpc {
namespace testing {

std::string ToString(const grpc::string_ref& r) {
  return std::string(r.data(), r.size());
}

}
}
