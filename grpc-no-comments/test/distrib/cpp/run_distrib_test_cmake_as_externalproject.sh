#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

apt-get update && apt-get install -y libssl-dev

rm -r third_party/benchmark/* || true
rm -r third_party/bloaty/* || true
rm -r third_party/boringssl-with-bazel/* || true
rm -r third_party/googletest/* || true

GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS=${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS:-4}

cd examples/cpp/helloworld/cmake_externalproject
mkdir -p cmake/build
cd cmake/build
cmake ../..
make "-j${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS}"
