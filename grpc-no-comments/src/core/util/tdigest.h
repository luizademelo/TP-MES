// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TDIGEST_H
#define GRPC_SRC_CORE_UTIL_TDIGEST_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

class TDigest final {
 public:
  TDigest(const TDigest&) = delete;
  TDigest(TDigest&&) = delete;

  TDigest& operator=(const TDigest&) = delete;
  TDigest& operator=(TDigest&&) = delete;

  explicit TDigest(double compression);

  void Reset(double compression);

  void Add(double val, int64_t count);

  void Add(double val) { Add(val, 1); }

  void Merge(const TDigest& that);

  double Quantile(double quantile);

  double Cdf(double val);

  double Min() const { return min_; }

  double Max() const { return max_; }

  double Sum() const { return sum_; }

  int64_t Count() const { return count_; }

  double Compression() const { return compression_; }

  std::string ToString();

  absl::Status FromString(absl::string_view string);

  size_t MemUsageBytes() const;

  void Swap(TDigest& that) {
    std::swap(compression_, that.compression_);
    std::swap(batch_size_, that.batch_size_);
    std::swap(centroids_, that.centroids_);
    std::swap(merged_, that.merged_);
    std::swap(unmerged_, that.unmerged_);
    std::swap(min_, that.min_);
    std::swap(max_, that.max_);
    std::swap(sum_, that.sum_);
    std::swap(count_, that.count_);
  }

 private:

  struct CentroidPod {
    CentroidPod() : CentroidPod(0, 0) {}
    CentroidPod(double mean, int64_t count) : mean(mean), count(count) {}

    double mean;
    int64_t count;

    bool operator<(const CentroidPod& that) const {

      return mean < that.mean || (mean == that.mean && count > that.count);
    }
  };

  void AddUnmergedCentroid(const CentroidPod& centroid);

  void DoMerge();

  double QuantileToCentroid(double quantile) const;

  double CentroidToQuantile(double centroid) const;

  void UpdateStats(double min, double max, double sum, int64_t count) {
    if (count <= 0) return;
    if (min < min_) min_ = min;
    if (max > max_) max_ = max;
    count_ += count;
    sum_ += sum;
  }

  double compression_;

  int64_t batch_size_;

  std::vector<CentroidPod> centroids_;

  int64_t merged_;

  int64_t unmerged_;

  double min_;

  double max_;

  double sum_;

  int64_t count_;
};

}

#endif
