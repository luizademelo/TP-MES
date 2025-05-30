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

IS_AARCH64_MUSL=""
if [[ "${TASK_RUNNER_EXTRA_FILTERS}" == "aarch64 musllinux_1_1" || "${TASK_RUNNER_EXTRA_FILTERS}" == "presubmit aarch64 musllinux_1_1" ]]; then
  IS_AARCH64_MUSL="True"
fi

if [[ "${IS_AARCH64_MUSL}" == "True" ]]; then
  echo "Skipping prepare_qemu_rc'"
else

  source tools/internal_ci/helper_scripts/prepare_qemu_rc
fi

source tools/internal_ci/helper_scripts/prepare_ccache_rc

tools/run_tests/task_runner.py -f artifact linux python ${TASK_RUNNER_EXTRA_FILTERS} -j 12 -x build_artifacts/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

PACKAGE_TASK_RUNNER_EXTRA_FILTERS="${TASK_RUNNER_EXTRA_FILTERS//presubmit /}"

tools/run_tests/task_runner.py -f package linux python ${PACKAGE_TASK_RUNNER_EXTRA_FILTERS} -x build_packages/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

DISTRIB_TASK_RUNNER_EXTRA_FILTERS="${TASK_RUNNER_EXTRA_FILTERS//musllinux_1_1/alpine}"

tools/run_tests/task_runner.py -f distribtest linux python ${DISTRIB_TASK_RUNNER_EXTRA_FILTERS} -j 12 -x distribtests/sponge_log.xml || FAILED="true"

tools/internal_ci/helper_scripts/check_python_artifacts_size.sh

tools/internal_ci/helper_scripts/store_artifacts_from_moved_src_tree.sh

if [ "$FAILED" != "" ]
then
  exit 1
fi
