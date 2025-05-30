#!/usr/bin/env python3

# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys

_TARGET_DIRS = [
    "include/grpc",
    "include/grpc++",
    "src/core",
    "src/cpp",
    "test/core",
    "test/cpp",
]

_INTERESTING_EXTENSIONS = [".c", ".h", ".cc"]

_ROOT = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), "../../.."))
os.chdir(_ROOT)

errors = 0

printed_banner = False
for target_dir in _TARGET_DIRS:
    for root, dirs, filenames in os.walk(target_dir):
        if "README.md" not in filenames:
            if not printed_banner:
                print("Missing README.md")
                print("=================")
                printed_banner = True
            print(root)
            errors += 1
if printed_banner:
    print()
printed_banner = False
for target_dir in _TARGET_DIRS:
    for root, dirs, filenames in os.walk(target_dir):
        for filename in filenames:
            if os.path.splitext(filename)[1] not in _INTERESTING_EXTENSIONS:
                continue
            path = os.path.join(root, filename)
            with open(path) as f:
                contents = f.read()
            if "\\file" not in contents:
                if not printed_banner:
                    print("Missing \\file comment")
                    print("======================")
                    printed_banner = True
                print(path)
                errors += 1

assert errors == 0, "error count = %d" % errors
