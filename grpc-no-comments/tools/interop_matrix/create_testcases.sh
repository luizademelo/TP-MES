#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd $(dirname $0)/../..
GRPC_ROOT=$(pwd)
CMDS_SH="${GRPC_ROOT}/interop_client_cmds.sh"
TESTCASES_DIR=${GRPC_ROOT}/tools/interop_matrix/testcases

echo "Create '$LANG' test cases for gRPC release '${RELEASE:=master}'"

function cleanup {
  [ -z "$testcase" ] && testcase=$CMDS_SH
  echo "testcase: $testcase"
  if [ -e $testcase ]; then

    eval docker_image=$(grep -oe '${docker_image:=.*}' $testcase)
    if [ -z "$KEEP_IMAGE" ]; then
      echo "Clean up docker_image $docker_image"
      docker rmi -f $docker_image
    else
      echo "Kept docker_image $docker_image"
    fi
  fi
  [ -e "$CMDS_SH" ] && rm $CMDS_SH
}

function createtests {

if [ $1 == "cxx" ]; then
client_lang="c++"
else
client_lang=$1
fi
echo $client_lang

${GRPC_ROOT}/tools/run_tests/run_interop_tests.py -l $client_lang --use_docker \
  --cloud_to_prod --prod_servers default gateway_v4 --manual_run --custom_credentials_type tls

trap cleanup EXIT

[ -z "$SKIP_TEST" ] && (echo "Running test cases: $CMDS_SH"; sh $CMDS_SH)

mkdir -p $TESTCASES_DIR
testcase=$TESTCASES_DIR/$1__$RELEASE
if [ -e $testcase ]; then
  echo "Updating: $testcase"
  diff $testcase $CMDS_SH || true
fi
mv $CMDS_SH $testcase
chmod a+x $testcase
echo "Test cases created: $testcase"
}

if [ $LANG == "csharp" ]; then
createtests "csharp"
createtests "csharpcoreclr"
else
createtests $LANG
fi
