
// Copyright 2015 gRPC authors.

#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

CORE_END2END_TEST(CoreEnd2endTests, ShutdownFinishesTags) {

  auto s = RequestCall(101);
  ShutdownAndDestroyClient();
  ShutdownServerAndNotify(1000);
  Expect(101, false);
  Expect(1000, true);
  Step();
}

}
}
