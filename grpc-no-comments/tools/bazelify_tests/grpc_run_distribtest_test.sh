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

ARCHIVE_WITH_SUBMODULES="$1"
BUILD_SCRIPT="$2"
shift 2

tar -xopf ${ARCHIVE_WITH_SUBMODULES}
cd grpc

mkdir -p input_artifacts
pushd input_artifacts >/dev/null

for input_artifact_archive in "$@"
do

  archive_extract_dir="$(basename ${input_artifact_archive} .tar.gz)"
  mkdir -p "${archive_extract_dir}"
  pushd "${archive_extract_dir}" >/dev/null
  tar --strip-components=1 -xopf ../../../${input_artifact_archive}
  popd >/dev/null
done
popd >/dev/null

ls -lR input_artifacts

"${BUILD_SCRIPT}"
