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

git clone /var/local/jenkins/grpc-node ~/grpc-node

(cd /var/local/jenkins/grpc-node/ && git submodule foreach 'cd ~/grpc-node \
&& git submodule update --init --recursive --reference /var/local/jenkins/grpc-node/${name} \
${name}')

cp -r /var/local/jenkins/service_account /root/ || true

cd ~/grpc-node

./setup_interop_purejs.sh
