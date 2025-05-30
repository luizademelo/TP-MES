#!/usr/bin/env python3

# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), "../.."))
os.chdir(ROOT)

argp = argparse.ArgumentParser(description="include guard checker")
argp.add_argument("-f", "--fix", default=False, action="store_true")
args = argp.parse_args()

errors = 0

CHECK_SUBDIRS = [
    "src/core",
    "src/cpp",
    "test/core",
    "test/cpp",
    "fuzztest",
]

for subdir in CHECK_SUBDIRS:
    for root, dirs, files in os.walk(subdir):
        for f in files:
            if f.endswith(".h") or f.endswith(".cc"):
                fpath = os.path.join(root, f)
                output = open(fpath, "r").readlines()
                changed = False
                for i, line in enumerate(output):
                    m = re.match(r'^#include "([^"]*)"(.*)', line)
                    if not m:
                        continue
                    include = m.group(1)
                    if "/" in include:
                        continue
                    expect_path = os.path.join(root, include)
                    trailing = m.group(2)
                    if not os.path.exists(expect_path):
                        continue
                    changed = True
                    errors += 1
                    output[i] = '#include "{0}"{1}\n'.format(
                        expect_path, trailing
                    )
                    print(
                        "Found naked include '{0}' in {1}".format(
                            include, fpath
                        )
                    )
                if changed and args.fix:
                    open(fpath, "w").writelines(output)

if errors > 0:
    print("{} errors found.".format(errors))
    sys.exit(1)
