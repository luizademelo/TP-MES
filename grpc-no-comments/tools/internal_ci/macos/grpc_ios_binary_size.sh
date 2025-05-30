#!/usr/bin/env bash
# Copyright 2018 gRPC authors.

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

export PREPARE_BUILD_INSTALL_DEPS_OBJC=true
source tools/internal_ci/helper_scripts/prepare_build_macos_rc

if [ "${KOKORO_GITHUB_PULL_REQUEST_TARGET_BRANCH}" != "" ]
then

  DIFF_BASE="origin/${KOKORO_GITHUB_PULL_REQUEST_TARGET_BRANCH}"
else

  DIFF_BASE=""
fi

tools/profiling/ios_bin/binary_size.py \
  --diff_base="${DIFF_BASE}"
