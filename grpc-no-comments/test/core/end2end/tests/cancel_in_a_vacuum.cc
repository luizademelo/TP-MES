
// Copyright 2015 gRPC authors.

#include <memory>

#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {

CORE_END2END_TEST(CoreEnd2endTests, CancelInAVacuum) {
  NewClientCall("/service/method").Create().Cancel();
}

CORE_END2END_TEST(CoreDeadlineTests, DeadlineInAVacuum) {
  NewClientCall("/service/method").Create();
}

}
