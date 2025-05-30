
// Copyright 2015 gRPC authors.

#include <grpcpp/support/status.h>

#include <memory>

namespace grpc {

const Status& Status::OK = Status();
const Status& Status::CANCELLED = Status(StatusCode::CANCELLED, "");

}
