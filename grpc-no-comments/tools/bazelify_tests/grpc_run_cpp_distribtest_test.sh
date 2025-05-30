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

ARCHIVE_WITH_SUBMODULES="$1"
shift

REPORT_XML_FILE="${XML_OUTPUT_FILE}"

REPORT_SUITE_NAME="$(echo ${TEST_TARGET} | sed 's|^.*[:/]||')"

tar -xopf ${ARCHIVE_WITH_SUBMODULES}
cd grpc

"$@"
