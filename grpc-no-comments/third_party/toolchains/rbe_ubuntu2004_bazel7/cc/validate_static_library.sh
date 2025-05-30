#!/usr/bin/env bash

# Copyright 2023 The Bazel Authors. All rights reserved.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
set -euo pipefail

DUPLICATE_SYMBOLS=$(
  "/usr/bin/nm" -A -g -P  "$1" |
  sed -E -e 's/.*\[([^][]+)\]: (.+) ([A-TX-Z]) [a-f0-9]+ [a-f0-9]+/\1: \3 \2/g' -e t -e d |
  LC_ALL=C sort -k 3 |
  LC_ALL=C uniq -D -f 2 |
  "/usr/bin/c++filt")
if [[ -n "$DUPLICATE_SYMBOLS" ]]; then
  >&2 echo "Duplicate symbols found in $1:"
  >&2 echo "$DUPLICATE_SYMBOLS"
  exit 1
else
  touch "$2"
fi
