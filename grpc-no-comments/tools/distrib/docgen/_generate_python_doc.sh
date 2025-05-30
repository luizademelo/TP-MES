#! /bin/bash
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

HOME="$(mktemp -d)"
export HOME

pip install -r tools/distrib/docgen/requirements.docs.lock
tools/run_tests/run_tests.py -c opt -l python --compiler python3.9 --newline_on_success -j 8 --build_only

source py39/bin/activate
pip install --upgrade Sphinx
python setup.py doc
