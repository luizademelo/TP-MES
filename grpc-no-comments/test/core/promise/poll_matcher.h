// Copyright 2024 gRPC authors.

#ifndef GRPC_TEST_CORE_PROMISE_POLL_MATCHER_H
#define GRPC_TEST_CORE_PROMISE_POLL_MATCHER_H

#include "gmock/gmock.h"

namespace grpc_core {

MATCHER(IsPending, "") {
  if (arg.ready()) {
    *result_listener << "is ready";
    return false;
  }
  return true;
}

MATCHER(IsReady, "") {
  if (arg.pending()) {
    *result_listener << "is pending";
    return false;
  }
  return true;
}

MATCHER_P(IsReady, value, "") {
  if (arg.pending()) {
    *result_listener << "is pending";
    return false;
  }
  if (arg.value() != value) {
    *result_listener << "is " << ::testing::PrintToString(arg.value());
    return false;
  }
  return true;
}

}

#endif
