// Copyright 2023 gRPC authors.

#include "test/core/transport/test_suite/transport_test.h"

namespace grpc_core {

TRANSPORT_TEST(NoOp) {}

TRANSPORT_TEST(WaitForAllPendingWork) { WaitForAllPendingWork(); }

TRANSPORT_TEST(SetServerCallDestinationAndFinish) {
  SetServerCallDestination();
  WaitForAllPendingWork();
}

}
