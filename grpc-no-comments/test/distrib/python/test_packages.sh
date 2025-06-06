#!/usr/bin/env bash
# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")"

shopt -s nullglob

echo "Testing Python packages with input artifacts:"
ls "$EXTERNAL_GIT_ROOT"/input_artifacts

if [[ "$1" == "binary" ]]
then
  echo "Testing Python binary distribution"
  ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[-_0-9a-z.]*.whl)
  TOOLS_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*tools[-_0-9a-z.]*.whl)
  OBSERVABILITY_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*observability[-_0-9a-z.]*.whl)
else
  echo "Testing Python source distribution"
  ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[-_0-9a-z.]*.tar.gz)
  TOOLS_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*tools[-_0-9a-z.]*.tar.gz)
  OBSERVABILITY_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*observability[-_0-9a-z.]*.tar.gz)
fi

HEALTH_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*health[_-]*checking[-_0-9a-z.]*.tar.gz)
REFLECTION_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*reflection[-_0-9a-z.]*.tar.gz)
TESTING_ARCHIVES=("$EXTERNAL_GIT_ROOT"/input_artifacts/grpcio[_-]*testing[-_0-9a-z.]*.tar.gz)

VIRTUAL_ENV=$(mktemp -d)
python3 -m virtualenv "$VIRTUAL_ENV"
PYTHON=$VIRTUAL_ENV/bin/python
"$PYTHON" -m pip install --upgrade six pip wheel setuptools

function validate_wheel_hashes() {
  for file in "$@"; do
    "$PYTHON" -m wheel unpack "$file" -d /tmp || return 1
  done
  return 0
}

function at_least_one_installs() {
  for file in "$@"; do
    if "$PYTHON" -m pip install "$file"; then
      return 0
    fi
  done
  return 1
}

if [[ "$1" == "binary" ]]; then
  validate_wheel_hashes "${ARCHIVES[@]}"
  validate_wheel_hashes "${TOOLS_ARCHIVES[@]}"
  validate_wheel_hashes "${OBSERVABILITY_ARCHIVES[@]}"
fi

at_least_one_installs "${ARCHIVES[@]}"
at_least_one_installs "${TOOLS_ARCHIVES[@]}"
at_least_one_installs "${HEALTH_ARCHIVES[@]}"
at_least_one_installs "${REFLECTION_ARCHIVES[@]}"
at_least_one_installs "${TESTING_ARCHIVES[@]}"
at_least_one_installs "${OBSERVABILITY_ARCHIVES[@]}"

"$PYTHON" -m grpc_tools.protoc --help

"$PYTHON" distribtest.py
