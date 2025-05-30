#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

export LANG=en_US.UTF-8

TEST_PATH=$(cd "$(dirname $0)" > /dev/null ; pwd)

cd $(dirname $0)/../../..

cd $EXAMPLE_PATH

rm -rf Pods
rm -rf *.xcworkspace
rm -f Podfile.lock

if [ -f Podfile ]; then
  time pod install
fi

set -o pipefail

XCODEBUILD_FILTER_OUTPUT_SCRIPT="${TEST_PATH}/xcodebuild_filter_output.sh"

if [ "$SCHEME" == "gRPC-Package" ]; then
  time xcodebuild \
    build \
    -scheme $SCHEME \
    -destination generic/platform=iOS
    -derivedDataPath Build/Build \
    CODE_SIGN_IDENTITY="" \
    CODE_SIGNING_REQUIRED=NO \
    CODE_SIGNING_ALLOWED=NO \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"
elif [ "$SCHEME" == "tvOS-sample" ]; then
  time xcodebuild \
    build \
    -workspace *.xcworkspace \
    -scheme $SCHEME \
    -destination generic/platform=tvOS \
    -derivedDataPath Build/Build \
    CODE_SIGN_IDENTITY="" \
    CODE_SIGNING_REQUIRED=NO \
    CODE_SIGNING_ALLOWED=NO \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"
else
  time xcodebuild \
    build \
    -workspace *.xcworkspace \
    -scheme $SCHEME \
    -destination generic/platform=iOS \
    -derivedDataPath Build/Build \
    CODE_SIGN_IDENTITY="" \
    CODE_SIGNING_REQUIRED=NO \
    CODE_SIGNING_ALLOWED=NO \
    | "${XCODEBUILD_FILTER_OUTPUT_SCRIPT}"
fi
