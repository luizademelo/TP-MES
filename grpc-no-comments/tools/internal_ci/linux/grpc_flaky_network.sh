#!/usr/bin/env bash
# Copyright 2019 gRPC authors.

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

source tools/internal_ci/helper_scripts/prepare_build_linux_rc

export DOCKERFILE_DIR=tools/dockerfile/test/bazel

export EXTRA_DOCKER_ARGS="--cap-add NET_ADMIN"
exec tools/run_tests/dockerize/build_and_run_docker.sh tools/internal_ci/linux/grpc_flaky_network_in_docker.sh
