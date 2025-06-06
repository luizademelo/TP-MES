#!/bin/bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

source $(dirname $0)/../../../tools/internal_ci/helper_scripts/move_src_tree_and_respawn_itself_rc

cd $(dirname $0)/../../..

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

echo "The grpc_portability_build_only job on linux has been deprecated and is now a no-op."
echo "The portability tests in 'build_only' mode are running as bazelified tests under tools/bazelify_tests."
echo "Note that the grpc_portability job still runs on master (but not on PRs)."
