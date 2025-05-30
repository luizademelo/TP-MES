// Copyright 2025 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_POSTMORTEM_H
#define GRPC_TEST_CORE_TEST_UTIL_POSTMORTEM_H

namespace grpc_core {

class PostMortem {
 public:

  ~PostMortem();

  static void Emit();
};

}

#endif
