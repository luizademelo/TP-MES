#!/bin/bash
# Copyright 2018 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

echo "KOKORO_RESULTSTORE_URL https://source.cloud.google.com/results/invocations/${KOKORO_BUILD_ID}"
echo "KOKORO_SPONGE_URL http://sponge.corp.google.com/${KOKORO_BUILD_ID}"

ENCODED_KOKORO_JOB_NAME=$(echo "${KOKORO_JOB_NAME}" | sed 's|/|%2F|g')

echo "KOKORO_FUSION_URL http://fusion2.corp.google.com/ci/kokoro/prod:${ENCODED_KOKORO_JOB_NAME}/activity/${KOKORO_BUILD_ID}"

echo "KOKORO_BUILD_NUMBER ${KOKORO_BUILD_NUMBER}"
echo "KOKORO_JOB_NAME ${KOKORO_JOB_NAME}"
echo "KOKORO_GITHUB_COMMIT ${KOKORO_GITHUB_COMMIT}"
