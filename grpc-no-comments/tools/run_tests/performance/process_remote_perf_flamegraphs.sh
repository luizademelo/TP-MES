#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

mkdir -p "$OUTPUT_DIR"

PERF_DATA_FILE="${PERF_BASE_NAME}-perf.data"
PERF_SCRIPT_OUTPUT="${PERF_BASE_NAME}-out.perf"

echo "running perf script on $USER_AT_HOST with perf.data"

ssh "$USER_AT_HOST" "cd ~/performance_workspace/grpc && perf script -i $PERF_DATA_FILE | gzip > ${PERF_SCRIPT_OUTPUT}.gz"

scp "$USER_AT_HOST:~/performance_workspace/grpc/$PERF_SCRIPT_OUTPUT.gz" .

gzip -d -f "$PERF_SCRIPT_OUTPUT.gz"

~/FlameGraph/stackcollapse-perf.pl --kernel "$PERF_SCRIPT_OUTPUT" | ~/FlameGraph/flamegraph.pl --color=java --hash > "${OUTPUT_DIR}/${OUTPUT_FILENAME}.svg"
