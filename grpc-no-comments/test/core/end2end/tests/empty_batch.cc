
// Copyright 2015 gRPC authors.

#include <memory>

#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

CORE_END2END_TEST(CoreEnd2endTests, EmptyBatch) {
  auto c = NewClientCall("/service/method").Create();
  c.NewBatch(1);
  Expect(1, true);
  Step();
}

}
