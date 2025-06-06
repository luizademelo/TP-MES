#!/bin/sh
# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -e

cd "$(dirname "$0")/../../.."

grep -PIirn \
    '((\b|_)(black[\ -]?hat|black[\ -]?list|black[\ -]?listed|black[\ -]?listing|dummy|grand[\ -]?father\ clause|grand[\ -]?fathered|hang|hung|man[\ -]?power|man[\ -]?hours|master(?!/)|slave|white[\ -]?hat|white[\ -]?list|white[\ -]?listed|white[\ -]?listing)(\b|_))' \
    examples \
    include \
    src/abseil-cpp \
    src/compiler \
    src/core \
    src/cpp \
    test | \
    diff - /dev/null
