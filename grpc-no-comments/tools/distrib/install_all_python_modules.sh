#!/bin/bash
# Copyright 2024 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

BASEDIR=$(dirname "$0")/../..
PACKAGES="grpcio_channelz  grpcio_csds  grpcio_admin grpcio_health_checking  grpcio_reflection  grpcio_status  grpcio_testing grpcio_csm_observability grpcio_tests"

cd "$BASEDIR";

function maybe_run_command () {
  if python3 setup.py --help-commands | grep "$1" &>/dev/null; then
    python3 setup.py "$1";
  fi
}

python3 -m pip install --upgrade "cython==3.1.1";
python3 setup.py install;

pushd tools/distrib/python/grpcio_tools;
  ../make_grpcio_tools.py
  GRPC_PYTHON_BUILD_WITH_CYTHON=1 pip install .
popd;

pushd src/python/grpcio_observability;
  ./make_grpcio_observability.py
  GRPC_PYTHON_BUILD_WITH_CYTHON=1 pip install .
popd;

pushd tools/distrib/python/xds_protos;
  GRPC_PYTHON_BUILD_WITH_CYTHON=1 pip install .
popd;

pushd src/python;
  for PACKAGE in ${PACKAGES}; do
    pushd "${PACKAGE}";
      python3 setup.py clean;
      maybe_run_command preprocess
      maybe_run_command build_package_protos
      python3 -m pip install .;
    popd;
  done
popd;
