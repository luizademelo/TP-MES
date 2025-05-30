#!/bin/bash
# Copyright 2025 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

tools/bazel \
    build \
    --enable_bzlmod=true \
    --enable_workspace=false \
    --ignore_dev_dependency \
    -- \
    :all \
    -:grpcpp_csm_observability

tools/bazel \
    build \
    --enable_bzlmod=true \
    --enable_workspace=false \
    --ignore_dev_dependency \
    -- \
    //examples/cpp/... \
    -//examples/cpp/csm/...

tools/bazel \
    test \
    --enable_bzlmod=true \
    --enable_workspace=false \
    -- \
    //test/core/config:all \
    //test/cpp/common:all

tools/bazel \
    build \
    --enable_bzlmod=true \
    --enable_workspace=false \
    --ignore_dev_dependency \
    --define=//third_party:grpc_use_openssl=true \
    -- \
    :all \
    -:grpcpp_csm_observability
