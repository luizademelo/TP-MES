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
cd $(dirname $0)
php -d extension=grpc.so -d max_execution_time=300 \
  route_guide_client.php \
  ../../node/static_codegen/route_guide/route_guide_db.json
