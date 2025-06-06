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

if [ "$CONFIG" != "gcov" ] ; then exit ; fi

root=$(readlink -f "$(dirname "$0")/../../..")
out=$root/reports/php_ext_coverage
tmp1=$(mktemp)
tmp2=$(mktemp)
cd "$root"
lcov --capture --directory . --output-file "$tmp1"
lcov --extract "$tmp1" "$root/src/php/ext/grpc/*" --output-file "$tmp2"
genhtml "$tmp2" --output-directory "$out"
rm "$tmp2"
rm "$tmp1"
