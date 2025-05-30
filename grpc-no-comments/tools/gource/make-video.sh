#!/bin/bash
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

dst=$1
shift
$(dirname $0)/gource.sh \
  --disable-progress    \
  --stop-at-end         \
  --output-ppm-stream - \
  $@ |                  \
avconv                  \
  -y                    \
  -r 60                 \
  -f image2pipe         \
  -vcodec ppm           \
  -i -                  \
  -vcodec libx264       \
  $dst
