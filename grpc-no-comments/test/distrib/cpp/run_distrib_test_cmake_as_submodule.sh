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

GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS=${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS:-4}

cd examples/cpp/helloworld
mkdir -p cmake/build
cd cmake/build
cmake \
  -DCMAKE_CXX_STANDARD=17 \
  -DGRPC_AS_SUBMODULE=ON \
  -Dprotobuf_INSTALL=OFF \
  -Dutf8_range_ENABLE_INSTALL=OFF \
  ../..
make "-j${GRPC_CPP_DISTRIBTEST_BUILD_COMPILER_JOBS}"
