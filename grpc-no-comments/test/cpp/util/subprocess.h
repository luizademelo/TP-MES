
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_SUBPROCESS_H
#define GRPC_TEST_CPP_UTIL_SUBPROCESS_H

#include <initializer_list>
#include <string>
#include <vector>

struct gpr_subprocess;

namespace grpc {

class SubProcess {
 public:
  explicit SubProcess(const std::vector<std::string>& args);
  ~SubProcess();

  int Join();
  void Interrupt();

 private:
  SubProcess(const SubProcess& other);
  SubProcess& operator=(const SubProcess& other);

  gpr_subprocess* const subprocess_;
};

}

#endif
