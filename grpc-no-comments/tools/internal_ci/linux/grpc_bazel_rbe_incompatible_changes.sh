#!/usr/bin/env bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

wget https://github.com/bazelbuild/bazelisk/releases/download/v0.0.7/bazelisk-linux-amd64
chmod u+x bazelisk-linux-amd64

export USE_BAZEL_VERSION=latest

mv bazelisk-linux-amd64 github/grpc/tools/bazel

github/grpc/tools/internal_ci/linux/grpc_bazel_rbe.sh --config=opt --cache_test_results=no
