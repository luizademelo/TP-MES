#!/usr/bin/env python3

# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import re
import sys

data = sys.stdin.readlines()

errs = []
for line in data:

    if re.search(r"error.cc", line):

        line = line.partition("error.cc:")[-1]
        line = re.sub(r"\d+] ", r"", line)
        line = line.strip().split()
        err = line[0].strip(":")
        if line[1] == "create":
            assert err not in errs
            errs.append(err)
        elif line[0] == "realloc":
            errs.remove(line[1])
            errs.append(line[3])

        elif line[1] == "1" and line[3] == "0":
            assert err in errs
            errs.remove(err)

print(("leaked:", errs))
