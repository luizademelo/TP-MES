#!/bin/bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

export PYTHON=/opt/python/cp39-cp39/bin/python
export PIP=/opt/python/cp39-cp39/bin/pip
export GRPC_SKIP_PIP_CYTHON_UPGRADE=TRUE
export GRPC_RUN_AUDITWHEEL_REPAIR=TRUE
export GRPC_BUILD_GRPCIO_TOOLS_DEPENDENTS=TRUE

export PATH="/opt/rh/devtoolset-10/root/usr/bin:$PATH"

export GRPC_PYTHON_BUILD_EXT_COMPILER_JOBS=8

mkdir -p artifacts

ARTIFACTS_OUT=artifacts tools/run_tests/artifacts/build_artifact_python.sh
