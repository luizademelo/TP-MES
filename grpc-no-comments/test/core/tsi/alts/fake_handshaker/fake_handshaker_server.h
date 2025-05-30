
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_TSI_ALTS_FAKE_HANDSHAKER_FAKE_HANDSHAKER_SERVER_H
#define GRPC_TEST_CORE_TSI_ALTS_FAKE_HANDSHAKER_FAKE_HANDSHAKER_SERVER_H

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>

namespace grpc {
namespace gcp {

std::unique_ptr<grpc::Service> CreateFakeHandshakerService(
    const std::string& peer_identity);

}
}

#endif
