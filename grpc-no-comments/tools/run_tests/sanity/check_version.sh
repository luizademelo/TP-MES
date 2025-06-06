#!/bin/sh

# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

buildfile=BUILD
yamlfile=build_handwritten.yaml
status=0

check_key () {
    key=$1
    build=$(grep "^$key =" < $buildfile | awk -F\" '{print $2}')
    yaml=$(grep "^ *${key}:" < $yamlfile | head -1 | awk '{print $2}')

    if [ "$build" = "" ] ; then
        echo "$key not defined in $buildfile"
        status=1
    fi

    if [ "$yaml" = "" ] ; then
        echo "$key not defined in $yamlfile"
        status=1
    fi

    if [ "$build" != "$yaml" ] ; then
        echo "$key mismatch between $buildfile ($build) and $yamlfile ($yaml)"
        status=1
    fi
}

check_key core_version
check_key version

exit $status
