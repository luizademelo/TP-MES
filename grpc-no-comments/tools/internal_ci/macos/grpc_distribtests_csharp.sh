#!/bin/bash
# Copyright 2021 The gRPC Authors

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

export PREPARE_BUILD_INSTALL_DEPS_CSHARP=true
source tools/internal_ci/helper_scripts/prepare_build_macos_rc

tools/run_tests/task_runner.py -f artifact macos protoc ${TASK_RUNNER_EXTRA_FILTERS} -j 2 --inner_jobs 4 -x build_artifacts_protoc/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

GRPC_CSHARP_BUILD_SINGLE_PLATFORM_NUGET=1 tools/run_tests/task_runner.py -f package macos csharp nuget -j 2 -x build_packages/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

tools/run_tests/task_runner.py -f distribtest macos csharp ${TASK_RUNNER_EXTRA_FILTERS} -j 4 -x distribtests/sponge_log.xml || FAILED="true"

tools/internal_ci/helper_scripts/store_artifacts_from_moved_src_tree.sh

if [ "$FAILED" != "" ]
then
  exit 1
fi
