#!/bin/bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

export DOCKERFILE_DIR=tools/dockerfile/test/cxx_debian11_x64

# TODO: is "--security-opt=seccomp=unconfined" actually needed?
export DOCKER_EXTRA_ARGS="--privileged --security-opt=seccomp=unconfined"

tools/docker_runners/run_in_docker.sh bash

# NOTE: Some old distros (e.g. debian 8 "jessie") might have a gdb version
