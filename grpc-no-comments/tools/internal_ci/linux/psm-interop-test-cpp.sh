#!/usr/bin/env bash
# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -eo pipefail

readonly GRPC_LANGUAGE="cpp"
readonly BUILD_SCRIPT_DIR="$(dirname "$0")"

source "${BUILD_SCRIPT_DIR}/psm-interop-install-lib.sh"
psm::lang::source_install_lib
source "${BUILD_SCRIPT_DIR}/psm-interop-build-${GRPC_LANGUAGE}.sh"
psm::run "${PSM_TEST_SUITE}"
