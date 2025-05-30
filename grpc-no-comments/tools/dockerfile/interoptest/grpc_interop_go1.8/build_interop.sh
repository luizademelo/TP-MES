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

git clone --recursive /var/local/jenkins/grpc-go src/google.golang.org/grpc

(cd src/google.golang.org/grpc && make deps && make testdeps)

cp -r /var/local/jenkins/service_account $HOME || true

(cd src/google.golang.org/grpc/interop/client && go install)
(cd src/google.golang.org/grpc/interop/server && go install)
