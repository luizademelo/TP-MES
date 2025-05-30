#!/bin/bash
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd `dirname $0`/../..

pushd third_party/protobuf

version1=$(git describe --tags | cut -f 1 -d'-')
v1=${version1:1}

# Hack: In case we got a 2-part "x.y" version number from the tag,

v1=$(echo "$v1" | sed 's/^\([0-9]*\)\.\([0-9]*\)$/3.\1.\2/')

popd

v2=$(cat src/objective-c/\!ProtoCompiler.podspec | egrep "v = " | cut -f 2 -d"'")

v3=$(cat src/objective-c/\!ProtoCompiler-gRPCPlugin.podspec | egrep 'dependency.*!ProtoCompiler' | cut -f 4 -d"'")

ret=0
if [ "$v1" != "$v2" ]; then
  echo 'Protobuf version in src/objective-c/!ProtoCompiler.podspec does not match protobuf version in third_party/protobuf.'
  ret=1
fi

if [ "$v1" != "$v3" ]; then
  echo 'Protobuf version in src/objective-c/!ProtoCompiler-gRPCPlugin.podspec does not match protobuf version in third_party/protobuf.'
  ret=1
fi

exit $ret
