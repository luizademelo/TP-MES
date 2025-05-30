#!/bin/bash
# Copyright 2023 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -x

TESTNAME=deprecated

set -uo pipefail; set +e; f=bazel_tools/tools/bash/runfiles/runfiles.bash
source "${RUNFILES_DIR:-/dev/null}/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "${RUNFILES_MANIFEST_FILE:-/dev/null}" | cut -f2- -d' ')" 2>/dev/null || \
  source "$0.runfiles/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.exe.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  { echo>&2 "ERROR: cannot find $f"; exit 1; }; f=; set -e

PROTOC=$(rlocation com_google_protobuf/protoc)
PLUGIN=$(rlocation com_github_grpc_grpc/src/compiler/grpc_csharp_plugin)

DATA_DIR=./test/csharp/codegen/${TESTNAME}

PROTO_OUT=./proto_out
rm -rf ${PROTO_OUT}
mkdir -p ${PROTO_OUT}

$PROTOC \
    --plugin=protoc-gen-grpc="$PLUGIN" \
    --csharp_out=${PROTO_OUT} \
    --grpc_out=${PROTO_OUT} \
    -I ${DATA_DIR}/proto \
    ${DATA_DIR}/proto/depnothing.proto \
    ${DATA_DIR}/proto/depservice.proto \
    ${DATA_DIR}/proto/depmethod.proto

ls -l ./proto_out

nmatches=$(grep -c ObsoleteAttribute ${PROTO_OUT}/DepnothingGrpc.cs || true)
if [ "$nmatches" -ne 0 ]
then
    echo >&2 "Unexpected ObsoleteAttribute in DepnothingGrpc.cs"
    exit 1
fi

nmatches=$(grep -c ObsoleteAttribute ${PROTO_OUT}/DepserviceGrpc.cs || true)
if [ "$nmatches" -eq 0 ]
then
    echo >&2 "Missing ObsoleteAttribute in DepserviceGrpc.cs"
    exit 1
fi

CTX=$(grep -A 2 ObsoleteAttribute ${PROTO_OUT}/DepserviceGrpc.cs || true)

nmatches=$(echo "$CTX" | grep -c "class GreeterServiceLevelDep$" || true)
if [ "$nmatches" -ne 1 ]
then
    echo >&2 "Missing ObsoleteAttribute on class GreeterServiceLevelDep"
    exit 1
fi

nmatches=$(echo "$CTX" | grep -c "class GreeterServiceLevelDepBase$" || true)
if [ "$nmatches" -ne 1 ]
then
    echo >&2 "Missing ObsoleteAttribute on class GreeterServiceLevelDepBase"
    exit 1
fi

nmatches=$(echo "$CTX" | grep -c "class GreeterServiceLevelDepClient" || true)
if [ "$nmatches" -ne 1 ]
then
    echo >&2 "Missing ObsoleteAttribute on class GreeterServiceLevelDepClient"
    exit 1
fi

nmatches=$(grep -c ObsoleteAttribute ${PROTO_OUT}/DepmethodGrpc.cs || true)
if [ "$nmatches" -eq 0 ]
then
    echo >&2 "Missing ObsoleteAttribute in DepmethodGrpc.cs"
    exit 1
fi

nmatches=$(grep -A 2 ObsoleteAttribute ${PROTO_OUT}/DepmethodGrpc.cs | grep -c SayHello || true)
if [ "$nmatches" -ne 5 ]
then
    echo >&2 "Missing ObsoleteAttribute on SayHello method"
    exit 1
fi

echo "Plugin test: ${TESTNAME}: passed."
