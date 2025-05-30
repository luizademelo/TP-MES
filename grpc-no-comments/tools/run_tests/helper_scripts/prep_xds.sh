#!/bin/bash
# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

trap 'date' DEBUG
set -ex

pushd "${KOKORO_ARTIFACTS_DIR}/github/grpc"

# Note: we don't use venv here because then per-language build files would need

sudo python3 -m pip install --upgrade pip==19.3.1

sudo python3 -m pip install --upgrade grpcio grpcio-tools==1.48.1 google-api-python-client google-auth-httplib2 oauth2client xds-protos

TOOLS_DIR=tools/run_tests
PROTO_SOURCE_DIR=src/proto/grpc/testing
PROTO_DEST_DIR=${TOOLS_DIR}/${PROTO_SOURCE_DIR}
mkdir -p ${PROTO_DEST_DIR}

python3 -m grpc_tools.protoc \
    --proto_path=. \
    --python_out=${TOOLS_DIR} \
    --grpc_python_out=${TOOLS_DIR} \
    ${PROTO_SOURCE_DIR}/test.proto \
    ${PROTO_SOURCE_DIR}/messages.proto \
    ${PROTO_SOURCE_DIR}/empty.proto

HEALTH_PROTO_SOURCE_DIR=src/proto/grpc/health/v1
HEALTH_PROTO_DEST_DIR=${TOOLS_DIR}/${HEALTH_PROTO_SOURCE_DIR}
mkdir -p ${HEALTH_PROTO_DEST_DIR}

python3 -m grpc_tools.protoc \
    --proto_path=. \
    --python_out=${TOOLS_DIR} \
    --grpc_python_out=${TOOLS_DIR} \
    ${HEALTH_PROTO_SOURCE_DIR}/health.proto

popd
