
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_INTERARRIVAL_H
#define GRPC_TEST_CPP_QPS_INTERARRIVAL_H

#include <grpcpp/support/config.h>

#include <chrono>
#include <cmath>
#include <random>
#include <vector>

namespace grpc {
namespace testing {

class RandomDistInterface {
 public:
  RandomDistInterface() {}
  virtual ~RandomDistInterface() = 0;

  virtual double transform(double uni) const = 0;
};

inline RandomDistInterface::~RandomDistInterface() {}

class ExpDist final : public RandomDistInterface {
 public:
  explicit ExpDist(double lambda) : lambda_recip_(1.0 / lambda) {}
  ~ExpDist() override {}
  double transform(double uni) const override {
    // Note: Use 1.0-uni above to avoid NaN if uni is 0
    return lambda_recip_ * (-log(1.0 - uni));
  }

 private:
  double lambda_recip_;
};

class InterarrivalTimer {
 public:
  InterarrivalTimer() {}
  void init(const RandomDistInterface& r, int threads, int entries = 1000000) {
    std::random_device devrand;
    std::mt19937_64 generator(devrand());
    std::uniform_real_distribution<double> rando(0, 1);
    for (int i = 0; i < entries; i++) {
      random_table_.push_back(
          static_cast<int64_t>(1e9 * r.transform(rando(generator))));
    }

    for (int i = 0; i < threads; i++) {
      thread_posns_.push_back(random_table_.begin() + (entries * i) / threads);
    }
  }
  virtual ~InterarrivalTimer() {};

  int64_t next(int thread_num) {
    auto ret = *(thread_posns_[thread_num]++);
    if (thread_posns_[thread_num] == random_table_.end()) {
      thread_posns_[thread_num] = random_table_.begin();
    }
    return ret;
  }

 private:
  typedef std::vector<int64_t> time_table;
  std::vector<time_table::const_iterator> thread_posns_;
  time_table random_table_;
};
}
}

#endif
