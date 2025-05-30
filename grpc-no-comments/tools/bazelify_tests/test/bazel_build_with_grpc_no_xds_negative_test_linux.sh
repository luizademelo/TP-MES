#!/bin/bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

EXIT_CODE=0
bazel build //test/cpp/end2end/xds:xds_end2end_test --define=grpc_no_xds=true || EXIT_CODE=$?
if [ $EXIT_CODE -eq 0 ]; then
  echo "FAILED: Building xds_end2end_test succeeded even with --define=grpc_no_xds=true"
  exit 1
fi
