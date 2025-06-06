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
import os.path
import re
import subprocess
import sys

def load(fpath):
    with open(fpath, "r") as f:
        return f.readlines()

def save(fpath, contents):
    with open(fpath, "w") as f:
        f.write(contents)

class QualificationValidator(object):
    def __init__(self):
        self.fully_qualified_re = re.compile(r"([ (<])::(grpc[A-Za-z_:])")
        self.using_re = re.compile(
            r"(using +|using +[A-Za-z_]+ *= *|namespace [A-Za-z_]+ *= *)::"
        )
        self.define_re = re.compile(r"^#define")

    def check(self, fpath, fix):
        fcontents = load(fpath)
        failed = False
        for i, line in enumerate(fcontents):
            if not self.fully_qualified_re.search(line):
                continue

            if self.using_re.search(line):
                continue

            if self.define_re.search(line):
                continue

            if fix:
                fcontents[i] = self.fully_qualified_re.sub(r"\1\2", line)
            else:
                print("Found in %s:%d - %s" % (fpath, i, line.strip()))
                failed = True
        if fix:
            save(fpath, "".join(fcontents))
        return not failed

IGNORED_FILES = [

    "src/cpp/common/core_codegen.cc",

    "src/compiler/cpp_generator.cc",

    "src/core/lib/profiling/timers.h",
    "src/core/util/crash.h",
    "src/core/util/unique_type_name.h",

    "src/core/ext/transport/chttp2/server/chttp2_server.h",
    "src/core/server/server.h",
]

ROOT = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), "../.."))
os.chdir(ROOT)

argp = argparse.ArgumentParser(
    description="c++ namespace full qualification checker"
)
argp.add_argument("-f", "--fix", default=False, action="store_true")
argp.add_argument("--precommit", default=False, action="store_true")
args = argp.parse_args()

grep_filter = r"grep -E '^(include|src|test).*\.(h|cc)$'"
if args.precommit:
    git_command = "git diff --name-only HEAD"
else:
    git_command = "git ls-tree -r --name-only -r HEAD"

FILE_LIST_COMMAND = " | ".join((git_command, grep_filter))

ok = True
filename_list = []
try:
    filename_list = (
        subprocess.check_output(FILE_LIST_COMMAND, shell=True)
        .decode()
        .splitlines()
    )

    filename_list = (f for f in filename_list if os.path.isfile(f))
except subprocess.CalledProcessError:
    sys.exit(0)

validator = QualificationValidator()

for filename in filename_list:

    if (
        filename.endswith(".upb.h")
        or filename.endswith(".upbdefs.h")
        or filename.endswith(".upbdefs.c")
        or filename in IGNORED_FILES
    ):
        continue
    ok = validator.check(filename, args.fix) and ok

sys.exit(0 if ok else 1)
