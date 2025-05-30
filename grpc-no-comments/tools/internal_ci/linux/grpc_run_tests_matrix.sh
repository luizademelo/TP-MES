#!/bin/bash
# Copyright 2017 gRPC authors.

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

source tools/internal_ci/helper_scripts/prepare_ccache_rc

if [ -n "$KOKORO_GITHUB_PULL_REQUEST_NUMBER" ] && [ -n "$RUN_TESTS_FLAGS" ]; then
  export RUN_TESTS_FLAGS="--filter_pr_tests --base_branch origin/$KOKORO_GITHUB_PULL_REQUEST_TARGET_BRANCH $RUN_TESTS_FLAGS"
fi

tools/run_tests/run_tests_matrix.py $RUN_TESTS_FLAGS || FAILED="true"

echo 'Exiting gRPC main test script.'

if [ "$FAILED" != "" ]
then
  exit 1
fi
