#!/bin/sh
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

test "$(bazel query 'somepath("//:grpc_unsecure", "//third_party:libssl")' 2>/dev/null | wc -l)" -eq 0 || exit 1
test "$(bazel query 'somepath("//:grpc++_unsecure", "//third_party:libssl")' 2>/dev/null | wc -l)" -eq 0 || exit 1
test "$(bazel query 'somepath("//:grpc++_codegen_proto", "//third_party:libssl")' 2>/dev/null | wc -l)" -eq 0 || exit 1

test "$(bazel query 'deps("//:grpc")' 2>/dev/null | grep -Ec 'src/cpp|include/grpcpp')" -eq 0 || exit 1

exit 0
