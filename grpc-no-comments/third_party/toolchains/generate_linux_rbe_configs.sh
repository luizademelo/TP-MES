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

TEMP_DIR="$(mktemp -d)"
pushd "${TEMP_DIR}"

git clone https://github.com/bazelbuild/bazel-toolchains.git
cd bazel-toolchains

docker run --rm -v $PWD:/srcdir -w /srcdir golang:1.16 go build -o rbe_configs_gen ./cmd/rbe_configs_gen/rbe_configs_gen.go
popd

RBE_CONFIGS_GEN_TOOL_PATH="${TEMP_DIR}/bazel-toolchains/rbe_configs_gen"

LINUX_RBE_DOCKERFILE_DIR=tools/dockerfile/test/rbe_ubuntu2004

LINUX_RBE_DOCKER_IMAGE=$(cat ${LINUX_RBE_DOCKERFILE_DIR}.current_version)

BAZEL_VERSION=7.4.1

CONFIG_OUTPUT_PATH=third_party/toolchains/rbe_ubuntu2004_bazel7

rm -rf "${REPO_ROOT}/${CONFIG_OUTPUT_PATH}"

${RBE_CONFIGS_GEN_TOOL_PATH} \
    --bazel_version="${BAZEL_VERSION}" \
    --toolchain_container="${LINUX_RBE_DOCKER_IMAGE}" \
    --output_src_root="${REPO_ROOT}" \
    --output_config_path="${CONFIG_OUTPUT_PATH}" \
    --exec_os=linux \
    --target_os=linux \
    --generate_java_configs=false
