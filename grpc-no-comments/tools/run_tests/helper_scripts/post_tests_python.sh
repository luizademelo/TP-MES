#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

if [ "$CONFIG" != "gcov" ] ; then exit ; fi

cd "$(dirname "$0")/../../../src/python/grpcio_tests/"

coverage combine .
coverage html -i -d ./../../../reports/python
