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

cd $(dirname $0)/../..

REPO_ROOT="$(pwd)"

wget https://github.com/bazelbuild/bazel-toolchains/releases/download/v5.1.2/rbe_configs_gen_windows_amd64.exe

RBE_CONFIGS_GEN_TOOL_PATH="./rbe_configs_gen_windows_amd64.exe"

WINDOWS_RBE_DOCKER_IMAGE=us-docker.pkg.dev/grpc-testing/testing-images-public/rbe_windows2019@sha256:cfef0ae3681d4070f6a93a88afea44d616f5cbdfae36559b9394274e74873bc6

BAZEL_VERSION=7.4.1

CONFIG_OUTPUT_PATH=third_party/toolchains/rbe_windows_vs2022_bazel7

rm -rf "${REPO_ROOT}/${CONFIG_OUTPUT_PATH}"

docker pull ${WINDOWS_RBE_DOCKER_IMAGE}

${RBE_CONFIGS_GEN_TOOL_PATH} \
    --bazel_version="${BAZEL_VERSION}" \
    --toolchain_container="${WINDOWS_RBE_DOCKER_IMAGE}" \
    --output_src_root=. \
    --output_config_path="${CONFIG_OUTPUT_PATH}" \
    --exec_os=windows \
    --target_os=windows \
    --generate_java_configs=false
