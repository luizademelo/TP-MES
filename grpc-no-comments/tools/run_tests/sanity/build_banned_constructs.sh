#!/bin/sh
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd "$(dirname "$0")/../../.."

regex='^licenses\(.*#'
for dir in bazel examples src test tools; do
  for file in BUILD BUILD.bazel; do
    git grep -EIrn "$regex" "$dir/**$file" | diff - /dev/null
  done
done
