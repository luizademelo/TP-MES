#!/bin/bash
# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

SCHEME=HelloWorld EXAMPLE_PATH=examples/objective-c/helloworld ./build_one_example.sh
SCHEME=RouteGuideClient EXAMPLE_PATH=examples/objective-c/route_guide ./build_one_example.sh
SCHEME=AuthSample EXAMPLE_PATH=examples/objective-c/auth_sample ./build_one_example.sh
