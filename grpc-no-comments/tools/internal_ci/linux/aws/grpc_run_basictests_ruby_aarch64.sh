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
sudo apt install -y build-essential autoconf libtool pkg-config cmake python python-pip clang
sudo pip install six

sudo apt install -y ruby ruby-dev
sudo gem install bundler
ruby --version

cd grpc

git submodule update --init

tools/run_tests/run_tests.py -l ruby -c opt -t -x run_tests/ruby_linux_aarch64_opt_native/sponge_log.xml --report_suite_name ruby_linux_aarch64_opt_native --report_multi_target
