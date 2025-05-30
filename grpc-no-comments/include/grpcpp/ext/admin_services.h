
// Copyright 2021 gRPC authors.

#ifndef GRPCPP_EXT_ADMIN_SERVICES_H
#define GRPCPP_EXT_ADMIN_SERVICES_H

#include <grpcpp/server_builder.h>

namespace grpc {

void AddAdminServices(grpc::ServerBuilder* builder);

}

#endif
