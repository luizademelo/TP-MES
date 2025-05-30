#!/usr/bin/env bash
# Copyright 2023 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

RESULTSTORE_RESULTS_FLAG="--bazelrc=tools/remote_build/include/test_locally_with_resultstore_results.bazelrc"
BAZEL_FLAGS="--test_output=errors --config=python"

python3 tools/run_tests/python_utils/bazel_report_helper.py --report_path python_bazel_tests_fork_support

python_bazel_tests_fork_support/bazel_wrapper ${RESULTSTORE_RESULTS_FLAG} test --config=fork_support --runs_per_test=16 ${BAZEL_FLAGS} //src/python/grpcio_tests/tests/fork:fork_test
