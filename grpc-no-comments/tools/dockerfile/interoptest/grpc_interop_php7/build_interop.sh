#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

mkdir -p /var/local/git
git clone /var/local/jenkins/grpc /var/local/git/grpc

(cd /var/local/jenkins/grpc/ && git submodule foreach 'cd /var/local/git/grpc \
&& git submodule update --init --reference /var/local/jenkins/grpc/${name} \
${name}')

cp -r /var/local/jenkins/service_account $HOME || true

cd /var/local/git/grpc
grpc_root="$(pwd)"

make -j4 shared_c static_c

pushd src/php/ext/grpc
phpize
GRPC_LIB_SUBDIR=libs/opt ./configure --enable-grpc="${grpc_root}"
make -j4
popd

cd src/php

DONE=0
for ((i = 0; i < 5; i++)); do
  php -d extension=ext/grpc/modules/grpc.so /usr/local/bin/composer install && DONE=1 && break
done

if [ "$DONE" != "1" ]
then
  echo "Failed to do composer install"
  exit 1
fi
