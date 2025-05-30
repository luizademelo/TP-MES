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

mkdir -p /var/local/git
git clone /var/local/jenkins/grpc /var/local/git/grpc

(cd /var/local/jenkins/grpc/ && git submodule foreach 'cd /var/local/git/grpc \
&& git submodule update --init --reference /var/local/jenkins/grpc/${name} \
${name}')

cp -r /var/local/jenkins/service_account $HOME || true

cd /var/local/git/grpc

mkdir -p /usr/local/share/grpc
cp etc/roots.pem /usr/local/share/grpc/roots.pem

mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 ../..
make interop_client interop_server -j4
make http2_client -j4
