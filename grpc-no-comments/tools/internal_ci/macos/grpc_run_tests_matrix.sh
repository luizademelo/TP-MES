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

source tools/internal_ci/helper_scripts/prepare_build_macos_rc

python3 -m pip install six==1.16.0
tools/run_tests/run_tests_matrix.py $RUN_TESTS_FLAGS || FAILED="true"

ps aux | grep port_server\\.py | awk '{print $2}' | xargs kill -9

if [ "$FAILED" != "" ]
then
  exit 1
fi
