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

curl -sSL -o dotnet-install.sh https://dot.net/v1/dotnet-install.sh
chmod u+x dotnet-install.sh

./dotnet-install.sh --channel 3.1
./dotnet-install.sh --channel 6.0
export PATH="$HOME/.dotnet:$PATH"

export NUGET_XMLDOC_MODE=skip
export DOTNET_SKIP_FIRST_TIME_EXPERIENCE=true
export DOTNET_CLI_TELEMETRY_OPTOUT=true

dotnet --list-sdks

cd grpc

git submodule update --init

tools/run_tests/run_tests.py -l csharp -c opt --compiler coreclr -t -x run_tests/csharp_linux_aarch64_opt_native/sponge_log.xml --report_suite_name csharp_linux_aarch64_opt_native --report_multi_target
