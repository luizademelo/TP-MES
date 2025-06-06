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
cd $(dirname $0)/../../..
root=$(pwd)
cd src/php/bin
source ./determine_extension_dir.sh

export DYLD_LIBRARY_PATH=$root/libs/$CONFIG
$(which php) $extension_dir -d max_execution_time=300 $(which phpunit) -v --debug \
  --exclude-group persistent_list_bound_tests ../tests/unit_tests

for arg in "$@"
do
  if [[ "$arg" == "--skip-persistent-channel-tests" ]]; then
    SKIP_PERSISTENT_CHANNEL_TESTS=true
  elif [[ "$arg" == "--ignore-valgrind-undef-errors" ]]; then
    VALGRIND_UNDEF_VALUE_ERRORS="--undef-value-errors=no"
  fi
done

if [[ "$SKIP_PERSISTENT_CHANNEL_TESTS" != "true" ]]; then
   $(which php) $extension_dir -d max_execution_time=300 $(which phpunit) -v --debug \
     ../tests/unit_tests/PersistentChannelTests
fi
