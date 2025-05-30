#! /bin/bash
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

GIT_ROOT="$(dirname "$0")/../../.."
"$GIT_ROOT/tools/distrib/buildifier_format_code.sh" -mode=diff -lint warn
result=$?

if [[ ${result} != 0 ]]; then
    echo "==========BUILDIFIER CHECK FAILED=========="
    echo "Please try using the following script to fix automatically:"
    echo ""
    echo "    tools/distrib/buildifier_format_code_strict.sh"
    echo ""
    exit 1
else
    echo "==========BUILDIFIER CHECK PASSED=========="
fi
