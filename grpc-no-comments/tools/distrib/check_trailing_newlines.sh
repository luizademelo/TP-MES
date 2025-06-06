#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cd $(dirname $0)/../..

function find_without_newline() {
  git ls-files |
    sed -En -e '/^third_party/d' -e '/\.(c|cc|proto|rb|py|cs|sh)$/p' |
    while IFS= read -r -d '' f; do
      if [[ ! -z $f ]]; then
        if [[ $(tail -c 1 "$f") != $NEWLINE ]]; then
          echo "Error: file '$f' is missing a trailing newline character."
          if $1; then
            sed -i -e '$a\' $f
            echo 'Fixed!'
          fi
        fi
      fi
    done
}

if [[ $
  FIX=true
else
  FIX=false
fi

ERRORS=$(find_without_newline $FIX)
if [[ "$ERRORS" != '' ]]; then
  echo "$ERRORS"
  if ! $FIX; then
    exit 1
  fi
fi
