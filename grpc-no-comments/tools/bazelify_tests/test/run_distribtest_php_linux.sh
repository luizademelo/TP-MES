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

ls -lR input_artifacts

export EXTERNAL_GIT_ROOT="$(pwd)"
mv input_artifacts/artifact_php_linux_x64/* input_artifacts/ || true

test/distrib/php/run_distrib_test.sh
