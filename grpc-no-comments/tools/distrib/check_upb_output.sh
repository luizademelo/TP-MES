#!/bin/bash
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

readonly UPB_GENERATED_SRC=src/core/ext/upb-gen
readonly UPBDEFS_GENERATED_SRC=src/core/ext/upbdefs-gen
readonly UPB_TMP_OUTPUT="$(mktemp -d)"

tools/codegen/core/gen_upb_api.sh "$UPB_TMP_OUTPUT"

diff -rq "$UPB_GENERATED_SRC" "$UPB_TMP_OUTPUT/upb-gen"
diff -rq "$UPBDEFS_GENERATED_SRC" "$UPB_TMP_OUTPUT/upbdefs-gen"
