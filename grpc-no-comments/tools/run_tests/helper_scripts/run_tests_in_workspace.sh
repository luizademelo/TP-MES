#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."
repo_root="$(pwd)"
export repo_root

rm -rf "${WORKSPACE_NAME}"
git clone . "${WORKSPACE_NAME}"

git submodule foreach 'cd "${repo_root}/${WORKSPACE_NAME}" \
    && git submodule update --init --reference ${repo_root}/${name} ${name}'

echo "Running run_tests.py in workspace ${WORKSPACE_NAME}"
python3 "${WORKSPACE_NAME}/tools/run_tests/run_tests.py" "$@"
