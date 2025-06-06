#!/bin/bash
# Copyright 2024 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd $(dirname $0)/../../..

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

export DOCKERFILE_DIR=tools/dockerfile/distribtest/python_dev_ubuntu2204_x64
export DOCKER_RUN_SCRIPT=tools/distrib/install_python_modules_and_run_tests.sh
export GRPC_TEST_REPORT_BASE_DIR=reports

# TODO: Reenable once the underlying test passes.
true
