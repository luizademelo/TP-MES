
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_STRING_REF_HELPER_H
#define GRPC_TEST_CPP_UTIL_STRING_REF_HELPER_H

#include <grpcpp/support/string_ref.h>

namespace grpc {
namespace testing {

std::string ToString(const grpc::string_ref& r);

}
}

#endif
