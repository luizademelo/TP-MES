#!/bin/bash
# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex
set -o pipefail

cd "$(dirname "$0")"

XCODEBUILD_FILTER_OUTPUT_SCRIPT="../../../../../src/objective-c/tests/xcodebuild_filter_output.sh"

XCODEBUILD_FLAGS="
  IPHONEOS_DEPLOYMENT_TARGET=10
  GCC_PREPROCESSOR_DEFINITIONS='DGRPC_IOS_EVENT_ENGINE_CLIENT=0'
"

XCODEBUILD_DESTINATION="platform=iOS Simulator,name=iPhone 11"

time ./build_tests.sh

time xcodebuild \
    -workspace CFStreamTests.xcworkspace \
    -scheme CFStreamTests \
    -destination "${XCODEBUILD_DESTINATION}" \
    test \
    "${XCODEBUILD_FLAGS}" \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"

time xcodebuild \
    -workspace CFStreamTests.xcworkspace \
    -scheme CFStreamTests_Asan \
    -destination "${XCODEBUILD_DESTINATION}" \
    test \
    "${XCODEBUILD_FLAGS}" \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"

time xcodebuild \
    -workspace CFStreamTests.xcworkspace \
    -scheme CFStreamTests_Tsan \
    -destination "${XCODEBUILD_DESTINATION}" \
    test \
    "${XCODEBUILD_FLAGS}" \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"

time xcodebuild \
    -workspace CFStreamTests.xcworkspace \
    -scheme CFStreamTests_Msan \
    -destination "${XCODEBUILD_DESTINATION}" \
    test \
    "${XCODEBUILD_FLAGS}" \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"
