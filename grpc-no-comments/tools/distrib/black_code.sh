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

ACTION="${1:-}"
[[ $ACTION == '' ]] || [[ $ACTION == '--diff' ]] || [[ $ACTION == '--check' ]]

cd "$(dirname "${0}")/../.."

DIRS=(
    'examples'
    'src'
    'test'
    'tools'
    'setup.py'
)

VIRTUALENV=venv_black_code
python3 -m virtualenv $VIRTUALENV
source $VIRTUALENV/bin/activate

python3 -m pip install black==23.3.0
python3 -m black --config=black.toml $ACTION "${DIRS[@]}"
