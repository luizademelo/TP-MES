#!/bin/sh
# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd "$(dirname "$0")/../../.."

find . \( \( -name "*.cc" \) -or \( -name "*.h" \) \) \
        -a \( \( -wholename "./src/*" \) \
            -or \( -wholename "./include/*" \) \
            -or \( -wholename "./test/*" \) \) \
        -a -not -wholename "./include/grpcpp/impl/sync.h" \
        -a -not -wholename "./src/core/util/sync.h" \
        -a -not -wholename "./src/core/util/sync_abseil.cc" \
        -a -not -wholename "./test/core/call/call_spine_benchmarks.h" \
        -print0 |\
    xargs -0 grep -n "absl::Mutex" | \
    diff - /dev/null
