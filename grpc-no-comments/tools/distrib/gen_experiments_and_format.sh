#!/bin/bash
# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e
cd $(dirname $0)/../..
tools/codegen/core/gen_experiments.py --check --no_dbg_experiments

TEST='' \
    CHANGED_FILES="$(git status --porcelain | awk '{print $2}' | tr '\n' ' ')" \
    tools/distrib/clang_format_code.sh

if [[ $
    CHANGES="$(git diff)"
    if [[ $CHANGES ]]; then
        echo >&2 "ERROR: Experiment code needs to be generated. Please run tools/distrib/gen_experiments_and_format.sh"
        echo >&2 -e "Changes:\n$CHANGES"
        exit 1
    fi
fi
