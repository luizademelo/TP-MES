# Copyright 2025 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set +e
set -x

sudo apt update
sudo apt install -y build-essential autoconf libtool pkg-config cmake python3 python3-pip clang

fail () {
    echo "$(tput setaf 1) $1 $(tput sgr 0)"
    if [[ -n $SERVER_PID ]] ; then
      kill -9 $SERVER_PID || true
    fi
    SERVER_PID=
    exit 1
}

pass () {
    echo "$(tput setaf 2) $1 $(tput sgr 0)"
}

tools/bazel version

export GRPC_TRACE=http

tools/bazel build  //examples/cpp/helloworld:greeter_callback_client

sudo setcap "cap_net_raw=ep" ./bazel-bin/examples/cpp/helloworld/greeter_callback_client
./bazel-bin/examples/cpp/helloworld/greeter_callback_client &> out.log

grep "gRPC Tracers:" out.log
return_code=$?
if [[ $return_code -eq 0 ]]; then
    fail "Able to read env variable with linux capability set"
fi

tools/bazel build  --define GRPC_FORCE_UNSECURE_GETENV=1 //examples/cpp/helloworld:greeter_callback_client

sudo setcap "cap_net_raw=ep" ./bazel-bin/examples/cpp/helloworld/greeter_callback_client
ls -lrt ./bazel-bin/examples/cpp/helloworld/greeter_callback_client
./bazel-bin/examples/cpp/helloworld/greeter_callback_client &> out.log
grep "gRPC Tracers:" out.log
return_code=$?

if [[ ! $return_code -eq 0 ]]; then
    fail "Fail to read env variable with linux capability"
fi

echo "Test completed"
