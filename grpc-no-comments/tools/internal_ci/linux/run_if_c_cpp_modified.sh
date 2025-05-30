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

cd $(dirname $0)/../../..

AFFECTS_C_CPP=`python3 -c 'import os; \
               import sys; \
               sys.path.insert(0, "tools/run_tests/python_utils"); \
               import filter_pull_request_tests as filter; \
               github_target_branch = os.environ.get("KOKORO_GITHUB_PULL_REQUEST_TARGET_BRANCH"); \
               print(filter.affects_c_cpp("origin/%s" % github_target_branch))'`

if [ $AFFECTS_C_CPP == "False" ] ; then
  echo "This pull request does not affect C/C++. Tests do not need to be run."
else
  $@
fi
