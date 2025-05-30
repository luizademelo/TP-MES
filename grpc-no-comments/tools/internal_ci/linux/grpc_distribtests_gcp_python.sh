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

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

source tools/internal_ci/helper_scripts/prepare_qemu_rc

source tools/internal_ci/helper_scripts/prepare_ccache_rc

tools/run_tests/task_runner.py -f artifact linux python latest-manylinux ${TASK_RUNNER_EXTRA_FILTERS} -j 12 -x build_artifacts/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true
rm -rf artifacts_from_build_artifacts_step
mv artifacts artifacts_from_build_artifacts_step || true

tools/run_tests/task_runner.py -f package linux python -x build_packages/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

INPUT_ARTIFACTS=$(realpath input_artifacts)

(yes || true) | gcloud components update

test/distrib/gcf/python/run.sh "$INPUT_ARTIFACTS"

tools/internal_ci/helper_scripts/store_artifacts_from_moved_src_tree.sh

if [ "$FAILED" != "" ]
then
  exit 1
fi
