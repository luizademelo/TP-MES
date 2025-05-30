
// Copyright 2016 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <string>

namespace grpc {
std::string Version() { return GRPC_CPP_VERSION_STRING; }
}
