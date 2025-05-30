
// Copyright 2015 gRPC authors.

#include "test/cpp/util/subprocess.h"

#include <vector>

#include "src/core/util/subprocess.h"

namespace grpc {

static gpr_subprocess* MakeProcess(const std::vector<std::string>& args) {
  std::vector<const char*> vargs;
  for (auto it = args.begin(); it != args.end(); ++it) {
    vargs.push_back(it->c_str());
  }
  return gpr_subprocess_create(vargs.size(), &vargs[0]);
}

SubProcess::SubProcess(const std::vector<std::string>& args)
    : subprocess_(MakeProcess(args)) {}

SubProcess::~SubProcess() { gpr_subprocess_destroy(subprocess_); }

int SubProcess::Join() { return gpr_subprocess_join(subprocess_); }

void SubProcess::Interrupt() { gpr_subprocess_interrupt(subprocess_); }

}
