
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_STATS_H
#define GRPC_TEST_CPP_QPS_STATS_H

#include <string>

#include "test/cpp/qps/histogram.h"

namespace grpc {
namespace testing {

template <class T, class F>
double sum(const T& container, F functor) {
  double r = 0;
  for (auto v = container.begin(); v != container.end(); v++) {
    r += functor(*v);
  }
  return r;
}

template <class T, class F>
double average(const T& container, F functor) {
  return sum(container, functor) / container.size();
}

}
}

#endif
