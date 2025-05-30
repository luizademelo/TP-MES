// Copyright 2023 The gRPC Authors

#ifndef GRPC_IMPL_CALL_H
#define GRPC_IMPL_CALL_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"

void grpc_call_run_in_event_engine(const grpc_call* call,
                                   absl::AnyInvocable<void()> cb);

#endif
