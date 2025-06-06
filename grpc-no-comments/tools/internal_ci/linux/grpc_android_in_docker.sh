#!/usr/bin/env bash
# Copyright 2022 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd $(dirname $0)/../../..

REPO_ROOT="$(pwd)"

mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 ../..
make protoc grpc_cpp_plugin -j8
popd

PROTOC=${REPO_ROOT}/cmake/build/third_party/protobuf/protoc
PLUGIN=${REPO_ROOT}/cmake/build/grpc_cpp_plugin

cd "${REPO_ROOT}/src/android/test/interop/"
./gradlew assembleDebug --parallel \
    "-Pprotoc=${PROTOC}" \
    "-Pgrpc_cpp_plugin=${PLUGIN}"
./gradlew assembleDebugAndroidTest \
    "-Pprotoc=${PROTOC}" \
    "-Pgrpc_cpp_plugin=${PLUGIN}"

gcloud firebase test android run \
    --type instrumentation \
    --app app/build/outputs/apk/debug/app-debug.apk \
    --test app/build/outputs/apk/androidTest/debug/app-debug-androidTest.apk \
    --device model=a10,version=29,locale=en,orientation=portrait \
    --device model=oriole,version=32,locale=en,orientation=portrait

cd "${REPO_ROOT}/examples/android/helloworld"
./gradlew build \
    "-Pprotoc=${PROTOC}" \
    "-Pgrpc_cpp_plugin=${PLUGIN}"
