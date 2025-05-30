
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_CONFIG_H
#define GRPCPP_SUPPORT_CONFIG_H

#include <string>

#define GRPC_OVERRIDE override
#define GRPC_FINAL final

#ifdef GRPC_CUSTOM_STRING
#warning GRPC_CUSTOM_STRING is no longer supported. Please use std::string.
#endif

namespace grpc {

using std::string;
using std::to_string;

}

#endif
