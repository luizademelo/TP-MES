#!/bin/bash

# Copyright 2015 The Bazel Authors. All rights reserved.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -eu

OUTPUT=

function parse_option() {
    local -r opt="$1"
    if [[ "${OUTPUT}" = "1" ]]; then
        OUTPUT=$opt
    elif [[ "$opt" = "-o" ]]; then

        OUTPUT=1
    fi
}

for i in "$@"; do
    if [[ "$i" = @* && -r "${i:1}" ]]; then
        while IFS= read -r opt
        do
            parse_option "$opt"
        done < "${i:1}" || exit 1
    else
        parse_option "$i"
    fi
done

/usr/local/bin/clang-19 "$@"

if [[ "${OUTPUT}" == *.h.processed ]]; then
  echo -n > "${OUTPUT}"
fi
