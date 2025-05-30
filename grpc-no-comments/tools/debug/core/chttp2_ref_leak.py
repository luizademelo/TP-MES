#!/usr/bin/env python3
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import collections
import re
import sys

def new_obj():
    return ["destroy"]

outstanding = collections.defaultdict(new_obj)

for line in sys.stdin:
    m = re.search(
        r"chttp2:(  ref|unref):0x([a-fA-F0-9]+) [^ ]+ ([^[]+) \[(.*)\]", line
    )
    if m:
        if m.group(1) == "  ref":
            outstanding[m.group(2)].append(m.group(3))
        else:
            outstanding[m.group(2)].remove(m.group(3))

for obj, remaining in list(outstanding.items()):
    if remaining:
        print(("LEAKED: %s %r" % (obj, remaining)))
