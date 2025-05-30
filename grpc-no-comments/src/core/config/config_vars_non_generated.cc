// Copyright 2022 gRPC authors.

#include <grpc/support/port_platform.h>

#include <atomic>
#include <string>

#include "src/core/config/config_vars.h"

namespace grpc_core {

std::atomic<ConfigVars*> ConfigVars::config_vars_{nullptr};

const ConfigVars& ConfigVars::Load() {

  auto vars = new ConfigVars({});
  ConfigVars* expected = nullptr;
  if (!config_vars_.compare_exchange_strong(expected, vars,
                                            std::memory_order_acq_rel,
                                            std::memory_order_acquire)) {
    delete vars;
    return *expected;
  }
  return *vars;
}

void ConfigVars::Reset() {
  delete config_vars_.exchange(nullptr, std::memory_order_acq_rel);
}

void ConfigVars::SetOverrides(const Overrides& overrides) {
  delete config_vars_.exchange(new ConfigVars(overrides),
                               std::memory_order_acq_rel);
}

}
