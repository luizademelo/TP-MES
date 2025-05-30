// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_PROMISE_TEST_CONTEXT_H
#define GRPC_TEST_CORE_PROMISE_TEST_CONTEXT_H

#include "src/core/lib/promise/context.h"

namespace grpc_core {

template <class T>
using TestContext = promise_detail::Context<T>;

}

#endif
