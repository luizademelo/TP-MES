#!/bin/bash
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e
command -v php-cs-fixer > /dev/null || {
  echo "Cannot find php-cs-fixer. Exiting..."
  exit 1
}
cd $(dirname $0)/..
php-cs-fixer fix lib/Grpc || true
php-cs-fixer fix tests/generated_code || true
php-cs-fixer fix tests/interop || true
php-cs-fixer fix tests/unit_tests || true
