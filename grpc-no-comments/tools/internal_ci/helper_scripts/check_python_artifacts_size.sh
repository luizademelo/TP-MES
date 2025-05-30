#!/usr/bin/env bash
# Copyright 2024 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

find . -path "*/artifacts/*" -size +80M | egrep '.*' && echo "Found Python artifacts larger than 80 MB." && FAILED="true"

if [ "$FAILED" != "" ]
then
  exit 1
fi
