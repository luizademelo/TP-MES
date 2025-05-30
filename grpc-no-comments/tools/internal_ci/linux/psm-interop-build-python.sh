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

psm::lang::build_docker_images() {
  local client_dockerfile="src/python/grpcio_tests/tests_py3_only/interop/Dockerfile.client"
  local server_dockerfile="src/python/grpcio_tests/tests_py3_only/interop/Dockerfile.server"
  psm::build::docker_images_generic "${client_dockerfile}" "${server_dockerfile}"
}
