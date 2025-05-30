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

TESTNAME=basenamespace

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
    --plugin=protoc-gen-grpc-csharp="$PLUGIN" \
    --csharp_out=${PROTO_OUT} \
    --grpc-csharp_out=${PROTO_OUT} \
    --csharp_opt=base_namespace=Example \
    --grpc-csharp_opt=base_namespace=Example \
    -I ${DATA_DIR}/proto \
    ${DATA_DIR}/proto/namespacetest.proto

ls -lR ./proto_out

[ -e ${PROTO_OUT}/V1/CodegenTest/Namespacetest.cs ] || {
    echo >&2 "missing generated output, expecting V1/CodegenTest/Namespacetest.cs"
    exit 1
}

[ -e ${PROTO_OUT}/V1/CodegenTest/NamespacetestGrpc.cs ] || {
    echo >&2 "missing generated output, expecting V1/CodegenTest/NamespacetestGrpc.cs"
    exit 1
}

rm -rf ${PROTO_OUT}
mkdir -p ${PROTO_OUT}

$PROTOC \
    --plugin=protoc-gen-grpc-csharp="$PLUGIN" \
    --csharp_out=${PROTO_OUT} \
    --grpc-csharp_out=${PROTO_OUT} \
    --csharp_opt=base_namespace= \
    --grpc-csharp_opt=base_namespace= \
    -I ${DATA_DIR}/proto \
    ${DATA_DIR}/proto/namespacetest.proto

ls -lR ./proto_out

[ -e ${PROTO_OUT}/Example/V1/CodegenTest/Namespacetest.cs ] || {
    echo >&2 "missing generated output, expecting Example/V1/CodegenTest/Namespacetest.cs"
    exit 1
}

[ -e ${PROTO_OUT}/Example/V1/CodegenTest/NamespacetestGrpc.cs ] || {
    echo >&2 "missing generated output, expecting Example/V1/CodegenTest/NamespacetestGrpc.cs"
    exit 1
}

rm -rf ${PROTO_OUT}
mkdir -p ${PROTO_OUT}

$PROTOC \
    --plugin=protoc-gen-grpc-csharp="$PLUGIN" \
    --csharp_out=${PROTO_OUT} \
    --grpc-csharp_out=${PROTO_OUT} \
    -I ${DATA_DIR}/proto \
    ${DATA_DIR}/proto/namespacetest.proto

ls -lR ./proto_out

[ -e ${PROTO_OUT}/Namespacetest.cs ] || {
    echo >&2 "missing generated output, expecting Namespacetest.cs"
    exit 1
}

[ -e ${PROTO_OUT}/NamespacetestGrpc.cs ] || {
    echo >&2 "missing generated output, expecting NamespacetestGrpc.cs"
    exit 1
}

echo "Plugin test: ${TESTNAME}: passed."
