
// Copyright 2015 gRPC authors.

#include <vector>

#include "absl/flags/parse.h"
#include "test/cpp/util/test_config.h"

namespace grpc {
namespace testing {

void InitTest(int* argc, char*** argv, bool remove_flags) {
  std::vector<char*> reduced_argv = absl::ParseCommandLine(*argc, *argv);
  if (remove_flags) {
    *argc = reduced_argv.size();
    for (int i = 0; i < *argc; i++) {
      (*argv)[i] = reduced_argv.at(i);
    }
  }
}

}
}
