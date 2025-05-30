#!/usr/bin/env bash
# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

XDS_V3_OPT="--xds_v3_support" `dirname $0`/grpc_xds_bazel_python_test_in_docker.sh
