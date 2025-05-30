
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_END2END_TESTS_CANCEL_TEST_HELPERS_H
#define GRPC_TEST_CORE_END2END_TESTS_CANCEL_TEST_HELPERS_H

#include <grpc/status.h>

#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
class CancellationMode {
 public:
  virtual void Apply(CoreEnd2endTest::Call& call) = 0;
  virtual grpc_status_code ExpectedStatus() = 0;
  virtual ~CancellationMode() = default;
};

class CancelCancellationMode : public CancellationMode {
 public:
  void Apply(CoreEnd2endTest::Call& call) override { call.Cancel(); }
  grpc_status_code ExpectedStatus() override { return GRPC_STATUS_CANCELLED; }
};

class DeadlineCancellationMode : public CancellationMode {
 public:
  void Apply(CoreEnd2endTest::Call&) override {}
  grpc_status_code ExpectedStatus() override {
    return GRPC_STATUS_DEADLINE_EXCEEDED;
  }
};
}

#endif
