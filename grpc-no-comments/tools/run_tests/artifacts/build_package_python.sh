#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -eux

cd "$(dirname "$0")/../../.."

mkdir -p artifacts/

find "${EXTERNAL_GIT_ROOT}"/input_artifacts/ \
    -maxdepth 1 \
    -type d \
    -name "${ARTIFACT_PREFIX}*" \
    -not -name "${EXCLUDE_PATTERN}" \
    -print0 \
        | xargs -0 -I% find % -type f -maxdepth 1 -exec cp -v {} ./artifacts \;

# TODO: all the artifact builder configurations generate a grpcio-VERSION.tar.gz
