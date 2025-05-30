// Copyright 2023 gRPC authors.

#include "test/core/test_util/fuzz_config_vars.h"

namespace grpc_core {

ConfigVars::Overrides OverridesFromFuzzConfigVars(
    const grpc::testing::FuzzConfigVars& vars) {
  ConfigVars::Overrides overrides;
  if (vars.has_channelz_max_orphaned_nodes()) {
    overrides.channelz_max_orphaned_nodes = vars.channelz_max_orphaned_nodes();
  }
  if (vars.has_enable_fork_support()) {
    overrides.enable_fork_support = vars.enable_fork_support();
  }
  if (vars.has_dns_resolver()) {
    overrides.dns_resolver = vars.dns_resolver();
  }
  if (vars.has_verbosity()) {
    overrides.verbosity = vars.verbosity();
  }
  if (vars.has_experiments()) {
    overrides.experiments = vars.experiments();
  }
  if (vars.has_trace()) {
    overrides.trace = vars.trace();
  }
  return overrides;
}
void ApplyFuzzConfigVars(const grpc::testing::FuzzConfigVars& vars) {
  ConfigVars::SetOverrides(OverridesFromFuzzConfigVars(vars));
}

}
