
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_OUTLIER_DETECTION_OUTLIER_DETECTION_H
#define GRPC_SRC_CORE_LOAD_BALANCING_OUTLIER_DETECTION_OUTLIER_DETECTION_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <optional>

#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

struct OutlierDetectionConfig {
  Duration interval = Duration::Seconds(10);
  Duration base_ejection_time = Duration::Milliseconds(30000);
  Duration max_ejection_time = Duration::Milliseconds(30000);
  uint32_t max_ejection_percent = 10;
  struct SuccessRateEjection {
    uint32_t stdev_factor = 1900;
    uint32_t enforcement_percentage = 100;
    uint32_t minimum_hosts = 5;
    uint32_t request_volume = 100;

    SuccessRateEjection() {}

    bool operator==(const SuccessRateEjection& other) const {
      return stdev_factor == other.stdev_factor &&
             enforcement_percentage == other.enforcement_percentage &&
             minimum_hosts == other.minimum_hosts &&
             request_volume == other.request_volume;
    }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors);
  };
  struct FailurePercentageEjection {
    uint32_t threshold = 85;
    uint32_t enforcement_percentage = 100;
    uint32_t minimum_hosts = 5;
    uint32_t request_volume = 50;

    FailurePercentageEjection() {}

    bool operator==(const FailurePercentageEjection& other) const {
      return threshold == other.threshold &&
             enforcement_percentage == other.enforcement_percentage &&
             minimum_hosts == other.minimum_hosts &&
             request_volume == other.request_volume;
    }

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors);
  };
  std::optional<SuccessRateEjection> success_rate_ejection;
  std::optional<FailurePercentageEjection> failure_percentage_ejection;

  bool operator==(const OutlierDetectionConfig& other) const {
    return interval == other.interval &&
           base_ejection_time == other.base_ejection_time &&
           max_ejection_time == other.max_ejection_time &&
           max_ejection_percent == other.max_ejection_percent &&
           success_rate_ejection == other.success_rate_ejection &&
           failure_percentage_ejection == other.failure_percentage_ejection;
  }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);
};

}

#endif
