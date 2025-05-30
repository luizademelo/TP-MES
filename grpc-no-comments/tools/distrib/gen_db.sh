#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cd $(dirname $0)/../..
REPO_ROOT=$(pwd)

export MANUAL_TARGETS=$(bazel query 'attr("tags", "manual", tests(//test/cpp/...))' | grep -v _on_ios)

tools/distrib/gen_compilation_database.py \
  --include_headers \
  --ignore_system_headers \
  --dedup_targets \
  "//:*" \
  "//src/core/..." \
  "//src/compiler/..." \
  "//test/core/..." \
  "//test/cpp/..." \
  $MANUAL_TARGETS
