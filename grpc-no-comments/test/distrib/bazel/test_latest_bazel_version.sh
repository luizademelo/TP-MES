#!/usr/bin/env bash
# Copyright 2021 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")"

GITHUB_URL="https://github.com"
REPO="bazelbuild/bazel"

VERSION=$(curl -v "${GITHUB_URL}/${REPO}/releases/latest" 2>/dev/stdout | \
  grep "location:" | \
  grep -o "[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*")

./test_single_bazel_version.sh "$VERSION"
