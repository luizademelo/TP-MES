#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd $(dirname $0)/../../..

PROTOC=bazel-bin/external/com_google_protobuf/protoc
PLUGIN=protoc-gen-grpc=bazel-bin/src/compiler/grpc_php_plugin

$PROTOC --proto_path=examples/protos \
       --php_out=examples/php/route_guide \
       --grpc_out=generate_server:examples/php/route_guide \
       --plugin=$PLUGIN examples/protos/route_guide.proto
