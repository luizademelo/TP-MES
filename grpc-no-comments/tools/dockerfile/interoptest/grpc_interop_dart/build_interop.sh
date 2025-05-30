#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

git config --global --add safe.directory /var/local/jenkins/grpc-dart/.git
mkdir -p /var/local/git
git clone /var/local/jenkins/grpc-dart /var/local/git/grpc-dart

cp -r /var/local/jenkins/service_account $HOME || true

cd /var/local/git/grpc-dart/interop

/usr/lib/dart/bin/dart pub get --verbose || /usr/lib/dart/bin/dart pub get --verbose
