Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/util/tdigest.h"

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

namespace grpc_core {

namespace {
// Constants used throughout the TDigest implementation
constexpr double kNan = std::numeric_limits<double>::quiet_NaN();  // NaN constant
constexpr double kMaxCompression = 1e6;  // Maximum allowed compression factor
constexpr double kPi = 3.14159265358979323846;  // Value of π for calculations

// Ensures compression value is within allowed bounds
double BoundedCompression(double compression) {
  static_assert(8 * kMaxCompression < std::numeric_limits<int64_t>::max(),
                "kMaxCompression must be smaller than max_int64/8.");
  return std::min(kMaxCompression, compression);
}

// Calculates the maximum number of centroids based on compression factor
size_t MaxCentroids(double compression) {
  compression = BoundedCompression(compression);
  return 2 * static_cast<size_t>(std::ceil(compression));
}

// Performs linear interpolation between two values with given weights
double LinearInterpolate(double val1, double val2, double weight1,
                         double weight2) {
  DCHECK_GE(weight1, 0);
  DCHECK_GE(weight2, 0);
  DCHECK_GT(weight1 + weight2, 0);
  return (val1 * weight1 + val2 * weight2) / (weight1 + weight2);
}

}  // namespace

// Constructor initializes TDigest with given compression
TDigest::TDigest(double compression) { Reset(compression); }

// Resets the TDigest to initial state with new compression
void TDigest::Reset(double compression) {
  compression_ = BoundedCompression(compression);

  // Calculate batch size based on compression
  batch_size_ = static_cast<int64_t>(4 * MaxCentroids(compression_));
  DCHECK(compression_ == 0.0 || batch_size_ > 0);
  
  // Reserve space for centroids and reset all metrics
  centroids_.reserve(MaxCentroids(compression_) + batch_size_);
  centroids_.clear();
  merged_ = 0;
  unmerged_ = 0;
  min_ = std::numeric_limits<double>::max();
  max_ = std::numeric_limits<double>::lowest();
  sum_ = 0;
  count_ = 0;
}

// Adds a value with given count to the digest
void TDigest::Add(double val, int64_t count) {
  if (count == 0) {
    return;  // Skip if count is zero
  }

  // Update statistics and add new centroid
  UpdateStats(val, val, val * count, count);
  AddUnmergedCentroid(CentroidPod(val, count));
}

// Adds an unmerged centroid to the digest
void TDigest::AddUnmergedCentroid(const CentroidPod& centroid) {
  DCHECK_LT(unmerged_, batch_size_);

  centroids_.push_back(centroid);
  ++unmerged_;
  // Trigger merge if batch size is reached
  if (unmerged_ == batch_size_) {
    DoMerge();
  }
}

// Merges another TDigest into this one
void TDigest::Merge(const TDigest& that) {
  if (compression_ == 0.0) {
    Reset(that.Compression());  // Reset if current compression is zero
  }

  // Update statistics with the other digest's values
  UpdateStats(that.Min(), that.Max(), that.Sum(), that.Count());

  // Add all centroids from the other digest
  for (const auto& centroid : that.centroids_) {
    AddUnmergedCentroid(centroid);
  }
}

// Converts quantile to centroid position using arcsin transformation
double TDigest::QuantileToCentroid(double quantile) const {
  return compression_ * (std::asin(2 * quantile - 1) + kPi / 2) / kPi;
}

// Converts centroid position back to quantile using sin transformation
double TDigest::CentroidToQuantile(double centroid) const {
  centroid = std::min(centroid, compression_);
  return (sin(centroid * kPi / compression_ - kPi / 2) + 1) / 2;
}

// Performs the merge operation on unmerged centroids
void TDigest::DoMerge() {
  if (unmerged_ == 0) {
    return;  // Nothing to merge
  }

  DCHECK(!centroids_.empty());
  // Sort centroids by mean value
  std::sort(centroids_.begin(), centroids_.end());
  unmerged_ += merged_ - 1;
  merged_ = 1;

  const int64_t total_count = count_;

  double q0 = 0;
  double q_limit = total_count * CentroidToQuantile(q0 + 1);

  sum_ = 0;

  // Merge centroids that fall within the same quantile range
  auto last_merged = centroids_.begin();
  auto first_unmerged = last_merged + 1;
  int64_t merged_count = last_merged->count;
  for (; unmerged_ > 0; --unmerged_, ++first_unmerged) {
    if (first_unmerged->count + merged_count <= q_limit) {
      // Merge current centroid with previous
      last_merged->count += first_unmerged->count;
      last_merged->mean +=
          ((first_unmerged->mean - last_merged->mean) * first_unmerged->count) /
          last_merged->count;
      merged_count += first_unmerged->count;
      continue;
    }

    // Move to next quantile range
    q0 = QuantileToCentroid(static_cast<double>(merged_count) / total_count);
    q_limit = total_count * CentroidToQuantile(q0 + 1);
    merged_count += first_unmerged->count;
    sum_ += last_merged->mean * last_merged->count;
    ++merged_;
    ++last_merged;
    *last_merged = *first_unmerged;
  }
  sum_ += last_merged->mean * last_merged->count;

  // Finalize merge operation
  unmerged_ = 0;
  centroids_.resize(merged_);
  if (!centroids_.empty()) {
    min_ = std::min(min_, centroids_.front().mean);
    max_ = std::max(max_, centroids_.back().mean);
  }
  DCHECK_LE(centroids_.size(), MaxCentroids(compression_));
}

// Computes cumulative distribution function for given value
double TDigest::Cdf(double val) {
  DoMerge();  // Ensure all centroids are merged

  if (merged_ == 0) {
    return kNan;  // No data case
  }

  // Boundary cases
  if (val < min_) {
    return 0;
  }
  if (val >= max_) {
    return 1;
  }
  DCHECK_NE(min_, max_);

  // Special case for single centroid
  if (merged_ == 1) {
    return (val - min_) / (min_ - max_);
  }

  // Handle values below first centroid
  if (val < centroids_[0].mean) {
    return LinearInterpolate(
        0.0, static_cast<double>(centroids_[0].count) / count_ / 2.0,
        centroids_[0].mean - val, val - min_);
  }

  // Handle values above last centroid
  if (val >= centroids_.back().mean) {
    return LinearInterpolate(
        1.0 - static_cast<double>(centroids_.back().count) / count_ / 2.0, 1,
        max_ - val, val - centroids_.back().mean);
  }

  // Calculate CDF by accumulating counts
  double accum_count = centroids_[0].count / 2.0;
  for (size_t i = 0; i < centroids_.size(); ++i) {
    if (centroids_[i].mean == val) {
      double prev_accum_count = accum_count;

      // Handle duplicate values
      for (; centroids_[i + 1].mean == val; ++i) {
        accum_count += centroids_[i].count + centroids_[i + 1].count;
      }
      return (prev_accum_count + accum_count) / 2.0 / count_;
    }
    if (centroids_[i].mean <= val && val < centroids_[i + 1].mean) {
      // Interpolate between adjacent centroids
      auto mean1 = centroids_[i].mean;
      auto mean2 = centroids_[i + 1].mean;
      double mean_ratio;

      if (mean2 <= mean1) {
        mean_ratio = 1;
      } else {
        mean_ratio = (val - mean1) / (mean2 - mean1);
      }
      double delta_count =
          (centroids_[i].count + centroids_[i + 1].count) / 2.0;
      return (accum_count + delta_count * mean_ratio) / count_;
    }
    accum_count += (centroids_[i].count + centroids_[i + 1].count) / 2.0;
  }

  LOG(DFATAL) << "Cannot measure CDF for: " << val;
  return kNan;
}

// Computes quantile for given probability
double TDigest::Quantile(double quantile) {
  DCHECK_LE(quantile, 1);
  DCHECK_GE(quantile, 0);

  DoMerge();  // Ensure all centroids are merged

  if (merged_ == 0) {
    return kNan;  // No data case
  }
  if (merged_ == 1) {
    return centroids_[0].mean;  // Single centroid case
  }

  // Calculate target count for the quantile
  const double quantile_count = quantile * count_;
  double prev_count = 0;
  double prev_val = min_;
  double this_count = centroids_[0].count / 2.0;
  double this_val = centroids_[0].mean;

  // Find the range containing the quantile
  for (size_t i = 0; i < centroids_.size(); ++i) {
    if (quantile_count < this_count) {
      break;
    }

    prev_count = this_count;
    prev_val = this_val;

    if (i == centroids_.size() - 1) {
      // Handle last centroid
      this_count = count_;
      this_val = max_;
    } else {
      this_count += (centroids_[i].count + centroids_[i + 1].count) / 2.0;
      this_val = centroids_[i + 1].mean;
    }
  }

  // Interpolate between the found range
  return LinearInterpolate(prev_val, this_val, this_count - quantile_count,
                           quantile_count - prev_count);
}

// Converts TDigest to string representation
std::string TDigest::ToString() {
  std::string str = absl::StrCat(compression_);
  if (count_ <= 1) {
    if (count_ == 0) {
      // Empty digest case
      return absl::StrAppendFormat(&str, "/0/0/0/0");
    }
    // Single value case
    return absl::StrAppendFormat(&str, "/%0.17g", centroids_.front().mean);
  }

  DoMerge();  // Ensure all centroids are merged

  // Add summary statistics
  absl::StrAppendFormat(&str, "/%0.17g/%0.17g/%0.17g/%d", min_, max_, sum_,
                        count_);

  // Add all centroids
  for (auto& centroid : centroids_) {
    absl::StrAppendFormat(&str, "/%0.17g:%d", centroid.mean, centroid.count);
  }
  return str;
}

// Parses TDigest from string representation
absl::Status TDigest::FromString(absl::string_view string) {
  if (string.empty()) {
    Reset(0);  // Empty string case
    return absl::OkStatus();
  }

  // Split string into tokens
  const std::vector<absl::string_view> tokens = absl::StrSplit(string, '/');
  auto iter = tokens.begin();

  if (iter == tokens.end() || iter->empty()) {
    return absl::InvalidArgumentError("No compression/discrete.");
  }

  // Parse compression factor
  double double_val;
  if (!absl::SimpleAtod(iter->substr(0, iter->length()), &double_val) ||
      double_val < 0) {
    return absl::InvalidArgumentError(
        absl::StrCat("Invalid double_val/discrete: ", *iter));
  }

  Reset(double_val);

  if (++iter == tokens.end()) {
    return absl::InvalidArgumentError("Unexpected end of string.");
  }

  // Handle single value case
  if ((iter + 1) == tokens.end()) {
    if (!absl::SimpleAtod(*iter, &double_val)) {
      return absl::InvalidArgumentError(
          absl::StrCat("Invalid single-value: ", *iter));
    }
    Add(double_val, 1);
    return absl::OkStatus();
  }

  // Parse summary statistics
  double min = 0.0, max = 0.0, sum = 0.0;
  int64_t count = 0;
  if (iter == tokens.end() || !absl::SimpleAtod(*iter, &min) ||
      ++iter == tokens.end() || !absl::SimpleAtod(*iter, &max) ||
      ++iter == tokens.end() || !absl::SimpleAtod(*iter, &sum) ||
      ++iter == tokens.end() || !absl::SimpleAtoi(*iter, &count)) {
    return absl::InvalidArgumentError("Invalid min, max, sum, or count.");
  }

  if (++iter == tokens.end()) {
    if (min != 0 || max != 0 || count != 0 || sum != 0) {
      return absl::InvalidArgumentError(
          "Empty t-Digest with non-zero min, max, sum, or count.");
    }
    return absl::OkStatus();
  }

  // Parse and add all centroids
  int64_t int_val = 0;
  for (; iter != tokens.end(); ++iter) {
    const auto pos = iter->find_first_of(':');
    if (pos == absl::string_view::npos ||
        !absl::SimpleAtod(iter->substr(0, pos), &double_val) ||
        !absl::SimpleAtoi(iter->substr(pos + 1), &int_val)) {
      return absl::InvalidArgumentError(
          absl::StrCat("Invalid centroid: ", *iter));
    }
    Add(double_val, int_val);
  }

  DoMerge();
  min_ = min;
  max_ = max;

  if (centroids_.empty()) {
    return absl::OkStatus();
  }

  // Validate parsed values
  DCHECK_LT(std::abs(sum - sum_), 1e-10) << "Invalid sum value.";

  if (count != count_) {
    return absl::InvalidArgumentError("Invalid count value.");
  }

  return absl::OkStatus();
}

// Returns memory usage in bytes
size_t TDigest::MemUsageBytes() const {
  return sizeof(TDigest) + (sizeof(CentroidPod) * centroids_.capacity());
}

}  // namespace grpc_core
```