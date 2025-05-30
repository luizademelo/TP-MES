// Copyright 2025 gRPC authors.

#ifndef GRPC_TEST_CORE_HANDSHAKE_TEST_HANDSHAKE_H
#define GRPC_TEST_CORE_HANDSHAKE_TEST_HANDSHAKE_H

#include "src/core/lib/channel/channel_args.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"

namespace grpc_core {

absl::StatusOr<std::tuple<ChannelArgs, ChannelArgs>> TestHandshake(
    ChannelArgs client_args, ChannelArgs server_args,
    const fuzzing_event_engine::Actions& actions =
        fuzzing_event_engine::Actions());

}

#endif
