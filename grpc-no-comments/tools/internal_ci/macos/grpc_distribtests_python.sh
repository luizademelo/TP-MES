#!/bin/bash
# Copyright 2022 The gRPC Authors

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

export PREPARE_BUILD_INSTALL_DEPS_PYTHON=true
source tools/internal_ci/helper_scripts/prepare_build_macos_rc

python3.9 -m pip install -U 'cython==3.1.1' setuptools==65.4.1 six==1.16.0 wheel --user
python3.10 -m pip install -U 'cython==3.1.1' setuptools==65.4.1 six==1.16.0 wheel --user
python3.11 -m pip install -U 'cython==3.1.1' setuptools==65.4.1 six==1.16.0 wheel --user
python3.12 -m pip install -U 'cython==3.1.1' setuptools==65.4.1 six==1.16.0 wheel --user --break-system-packages
python3.13 -m pip install -U 'cython==3.1.1' setuptools==65.4.1 six==1.16.0 wheel --user --break-system-packages

tools/run_tests/task_runner.py -f artifact macos python ${TASK_RUNNER_EXTRA_FILTERS} -j 2 -x build_artifacts/sponge_log.xml || FAILED="true"

rm -rf input_artifacts
mkdir -p input_artifacts
cp -r artifacts/* input_artifacts/ || true

cp -r input_artifacts/python_*/* artifacts/ || true

tools/internal_ci/helper_scripts/check_python_artifacts_size.sh

tools/internal_ci/helper_scripts/store_artifacts_from_moved_src_tree.sh

if [ "$FAILED" != "" ]
then
  exit 1
fi
