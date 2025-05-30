#!/bin/bash
# Copyright 2022 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ev

set -uo pipefail; set +e; f=bazel_tools/tools/bash/runfiles/runfiles.bash
source "${RUNFILES_DIR:-/dev/null}/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "${RUNFILES_MANIFEST_FILE:-/dev/null}" | cut -f2- -d' ')" 2>/dev/null || \
  source "$0.runfiles/$f" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  source "$(grep -sm1 "^$f " "$0.exe.runfiles_manifest" | cut -f2- -d' ')" 2>/dev/null || \
  { echo>&2 "ERROR: cannot find $f"; exit 1; }; f=; set -e

PROTOC=$(rlocation com_google_protobuf/protoc)
PLUGIN=$(rlocation com_github_grpc_grpc/src/compiler/grpc_objective_c_plugin)
WELL_KNOWN_PROTOS_PATH=$(rlocation com_google_protobuf/src)
RUNTIME_IMPORT_PREFIX=prefix/dir/

PROTO_OUT=./proto_out
rm -rf ${PROTO_OUT}
mkdir -p ${PROTO_OUT}

$PROTOC \
    --plugin=protoc-gen-grpc="$PLUGIN" \
    --objc_out=${PROTO_OUT} \
    --grpc_out=grpc_local_import_prefix=$RUNTIME_IMPORT_PREFIX,runtime_import_prefix=$RUNTIME_IMPORT_PREFIX:${PROTO_OUT} \
    -I . \
    -I ${WELL_KNOWN_PROTOS_PATH} \
    src/objective-c/tests/RemoteTestClient/*.proto

[ -e ${PROTO_OUT}/src/objective-c/tests/RemoteTestClient/Test.pbrpc.m ] || {
    echo >&2 "protoc outputs wrong filename."
    exit 1
}

[ "`cat ${PROTO_OUT}/src/objective-c/tests/RemoteTestClient/Test.pbrpc.m |
    egrep '#import "'"${RUNTIME_IMPORT_PREFIX}"'GPBEmpty\.pbobjc\.h'`" ] || {
    echo >&2 "protoc generated import with wrong filename."
    exit 1
}

[ "`cat ${PROTO_OUT}/src/objective-c/tests/RemoteTestClient/Test.pbrpc.m |
    egrep '.*\Messages.pbobjc.h"$' |
    egrep '#import "'"${RUNTIME_IMPORT_PREFIX}"`" ] && {
    echo >&2 "protoc generated import with wrong filename."
    exit 1
}

[ "`cat ${PROTO_OUT}/src/objective-c/tests/RemoteTestClient/Test.pbrpc.h |
    egrep '#import "'"${RUNTIME_IMPORT_PREFIX}"'/ProtoRPC/.*\.h'`"] || {
    echo >&2 "grpc system files should be imported with full paths."
}

[ "`cat ${PROTO_OUT}/src/objective-c/tests/RemoteTestClient/Test.pbrpc.m |
    egrep '#import "'"${RUNTIME_IMPORT_PREFIX}"'/ProtoRPC/.*\.h'`"] || {
    echo >&2 "grpc system files should be imported with full paths."
}

echo "Plugin option tests passed."
