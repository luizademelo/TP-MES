// Copyright 2021 gRPC authors.

#ifndef GRPC_TEST_CORE_RESOURCE_QUOTA_CALL_CHECKER_H
#define GRPC_TEST_CORE_RESOURCE_QUOTA_CALL_CHECKER_H

#include <memory>

#include "absl/log/check.h"

namespace grpc_core {
namespace testing {

class CallChecker {
 public:
  explicit CallChecker(bool optional) : optional_(optional) {}
  ~CallChecker() {
    if (!optional_) CHECK(called_);
  }

  void Called() {
    CHECK(!called_);
    called_ = true;
  }

  static std::shared_ptr<CallChecker> Make() {
    return std::make_shared<CallChecker>(false);
  }

  static std::shared_ptr<CallChecker> MakeOptional() {
    return std::make_shared<CallChecker>(true);
  }

 private:
  bool called_ = false;
  const bool optional_ = false;
};

}
}

#endif
