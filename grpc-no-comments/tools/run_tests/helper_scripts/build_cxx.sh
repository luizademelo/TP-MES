#!/bin/bash
# Copyright 2022 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."
mkdir -p cmake/install
INSTALL_PATH="$(pwd)/cmake/install"

cd third_party/abseil-cpp
mkdir build
cd build
cmake -DABSL_BUILD_TESTING=OFF -DCMAKE_BUILD_TYPE="${MSBUILD_CONFIG}" -DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}" "$@" ..
make -j"${GRPC_RUN_TESTS_JOBS}" install

cd ../../..
cd third_party/opentelemetry-cpp
mkdir build
cd build
cmake -DWITH_ABSEIL=ON -DBUILD_TESTING=OFF -DWITH_BENCHMARK=OFF -DCMAKE_BUILD_TYPE="${MSBUILD_CONFIG}" -DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}" "$@" ..
make -j"${GRPC_RUN_TESTS_JOBS}" install

cd ../../..
mkdir -p cmake/build
cd cmake/build

if [ "${GRPC_RUNTESTS_ARCHITECTURE}" = "x86" ]; then
cmake -DgRPC_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE="${MSBUILD_CONFIG}" "$@" ../..
else
cmake -DgRPC_BUILD_GRPCPP_OTEL_PLUGIN=ON -DgRPC_ABSL_PROVIDER=package -DgRPC_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE="${MSBUILD_CONFIG}" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}" "$@" ../..
fi

if [[ "$*" =~ "-DgRPC_BUILD_TESTS=OFF" ]]; then

make -j"${GRPC_RUN_TESTS_JOBS}" "grpc++"
else

make -j"${GRPC_RUN_TESTS_JOBS}" "buildtests_${GRPC_RUN_TESTS_CXX_LANGUAGE_SUFFIX}" "tools_${GRPC_RUN_TESTS_CXX_LANGUAGE_SUFFIX}"
fi
