#!/usr/bin/env bash
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

tools/bazel version

python3 tools/run_tests/python_utils/bazel_report_helper.py --report_path bazel_rbe

bazel_rbe/bazel_wrapper \
  --bazelrc=tools/remote_build/linux_kokoro.bazelrc \
  --output_user_root=/tmpfs/bazel \
  test \
  $BAZEL_FLAGS \
  "$@" \
  -- ${BAZEL_TESTS:-//test/...}
