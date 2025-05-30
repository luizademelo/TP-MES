#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

export LANG=en_US.UTF-8

cd "$(dirname "$0")"

hash pod 2>/dev/null || { echo >&2 "Cocoapods needs to be installed."; exit 1; }
hash xcodebuild 2>/dev/null || {
    echo >&2 "XCode command-line tools need to be installed."
    exit 1
}

rm -Rf Pods Podfile.lock Tests.xcworkspace
rm -f RemoteTestClient/*.{h,m}
pod cache clean --all

time pod install --verbose

if [ -d "./Pods/Headers/Public/gRPC-Core/grpc/impl/codegen" ]
then
    echo "grpc/impl/codegen/ has been imported."
    number_of_files=$(find Pods/Headers/Public/gRPC-Core/grpc/impl/codegen -name "*.h" | wc -l)
    echo "The number of files in Pods/Headers/Public/gRPC-Core/grpc/impl/codegen/ is $number_of_files"
else
    echo "Error: grpc/impl/codegen/ hasn't been imported."
fi
