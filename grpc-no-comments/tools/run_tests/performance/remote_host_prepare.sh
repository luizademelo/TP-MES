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

cd "$(dirname "$0")/../../.."

ssh "${USER_AT_HOST}" "killall -9 qps_worker dotnet mono node ruby worker || true"

ssh "${USER_AT_HOST}" "ps -e | egrep 'qps_worker|dotnet' | awk '{print \$1}' | xargs kill -9 || true"

ssh "${USER_AT_HOST}" "rm -rf ~/performance_workspace && mkdir -p ~/performance_workspace"

scp ../grpc.tar "${USER_AT_HOST}:~/performance_workspace"

ssh "${USER_AT_HOST}" "tar -xf ~/performance_workspace/grpc.tar -C ~/performance_workspace || tar -xf ~/performance_workspace/grpc.tar -C ~/performance_workspace"

ssh "${USER_AT_HOST}" "~/performance_workspace/grpc/tools/run_tests/performance/kill_workers.sh"

ssh "${USER_AT_HOST}" "cd ~/performance_workspace/grpc/ && python tools/run_tests/start_port_server.py"
