
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_BACKOFF_H
#define GRPC_SRC_CORE_UTIL_BACKOFF_H

#include "absl/random/random.h"
#include "src/core/util/time.h"

namespace grpc_core {

class BackOff {
 public:
  class Options;

  explicit BackOff(const Options& options);

  Duration NextAttemptDelay();

  void Reset();

  class Options {
   public:
    Options& set_initial_backoff(Duration initial_backoff) {
      initial_backoff_ = initial_backoff;
      return *this;
    }
    Options& set_multiplier(double multiplier) {
      multiplier_ = multiplier;
      return *this;
    }
    Options& set_jitter(double jitter) {
      jitter_ = jitter;
      return *this;
    }
    Options& set_max_backoff(Duration max_backoff) {
      max_backoff_ = max_backoff;
      return *this;
    }

    Duration initial_backoff() const { return initial_backoff_; }

    double multiplier() const { return multiplier_; }

    double jitter() const { return jitter_; }

    Duration max_backoff() const { return max_backoff_; }

   private:
    Duration initial_backoff_;
    double multiplier_;
    double jitter_;
    Duration max_backoff_;
  };

 private:
  const Options options_;
  bool initial_;

  Duration current_backoff_;
};

}
#endif
