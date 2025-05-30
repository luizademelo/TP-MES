#!/usr/bin/env bash
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

sudo apt update
sudo apt install -y build-essential autoconf libtool pkg-config cmake python3 python3-pip clang

python3 --version

cd grpc

python3 tools/run_tests/start_port_server.py

tools/bazel build --config=opt //test/...
