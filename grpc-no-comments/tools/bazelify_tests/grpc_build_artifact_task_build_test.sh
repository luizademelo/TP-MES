#!/bin/bash
# Copyright 2023 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

EXIT_CODE_FILE="$1"
SCRIPT_LOG_FILE="$2"
ARTIFACTS_ARCHIVE="$3"
shift 3

BUILD_ARTIFACT_EXITCODE="$(cat ${EXIT_CODE_FILE})"

echo "Build artifact/package task for '${ARTIFACTS_ARCHIVE}' has finished with exitcode ${BUILD_ARTIFACT_EXITCODE}."

echo "BUILD LOG"
echo "--------------"
cat "${SCRIPT_LOG_FILE}"
echo "--------------"
echo

mkdir -p input_artifacts
pushd input_artifacts >/dev/null
echo "Artifacts that were built by the build artifact/package task:"
echo "--------------"

tar -xopvf ../${ARTIFACTS_ARCHIVE}
echo "--------------"
popd >/dev/null

mkdir -p "${TEST_UNDECLARED_OUTPUTS_DIR}"
cp "${ARTIFACTS_ARCHIVE}" "${TEST_UNDECLARED_OUTPUTS_DIR}" || true

if [ "${BUILD_ARTIFACT_EXITCODE}" -eq "0" ]
then
  echo "SUCCESS: Build artifact/package task for '${ARTIFACTS_ARCHIVE}' ran successfully."
else
  echo "FAIL: Build artifact/package task for '${ARTIFACTS_ARCHIVE}' failed with exitcode ${BUILD_ARTIFACT_EXITCODE}."
  exit 1
fi
