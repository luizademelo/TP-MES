#!/bin/bash
# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cleanup () {
    echo "Trapped SIGTERM. Cleaning up..."
    set -x
    kill -9 $PID1
    kill -9 $PID2
    running=false
    set +x
}

trap cleanup SIGTERM

set -e
cd $(dirname $0)/../../..
root=$(pwd)

tmp_file1=$(mktemp)

tmp_file2=$(mktemp)

set -x

php -d extension=grpc.so -d extension=pthreads.so \
    src/php/tests/interop/xds_client.php $1 $2 $3 $4 $5 $6 \
    --tmp_file1=$tmp_file1 --tmp_file2=$tmp_file2 &
PID1=$!

python3 -u src/php/bin/xds_manager.py \
        --tmp_file1=$tmp_file1 --tmp_file2=$tmp_file2 \
        --bootstrap_path=$GRPC_XDS_BOOTSTRAP &
PID2=$!
set +x

running=true
while $running
do
    sleep 1
done
