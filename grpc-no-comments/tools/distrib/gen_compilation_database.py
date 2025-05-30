#!/usr/bin/env python3

# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import glob
import json
import logging
import os
from pathlib import Path
import re
import shlex
import subprocess

RE_INCLUDE_SYSTEM = re.compile("\s*-I\s+/usr/[^ ]+")

def generateCompilationDatabase(args):

    bazel_options = shlex.split(os.environ.get("BAZEL_BUILD_OPTIONS", "")) + [
        "--config=compdb",
        "--remote_download_outputs=all",
    ]

    subprocess.check_call(
        ["bazel", "build"]
        + bazel_options
        + [
            "--aspects=@bazel_compdb//:aspects.bzl%compilation_database_aspect",
            "--output_groups=compdb_files,header_files",
        ]
        + args.bazel_targets
    )

    execroot = (
        subprocess.check_output(
            ["bazel", "info", "execution_root"] + bazel_options
        )
        .decode()
        .strip()
    )

    compdb = []
    for compdb_file in Path(execroot).glob("**/*.compile_commands.json"):
        compdb.extend(
            json.loads(
                compdb_file.read_text().replace("__EXEC_ROOT__", execroot)
            )
        )

    if args.dedup_targets:
        compdb_map = {target["file"]: target for target in compdb}
        compdb = list(compdb_map.values())

    return compdb

def isHeader(filename):
    for ext in (".h", ".hh", ".hpp", ".hxx"):
        if filename.endswith(ext):
            return True
    return False

def isCompileTarget(target, args):
    filename = target["file"]
    if not args.include_headers and isHeader(filename):
        return False
    if not args.include_genfiles:
        if filename.startswith("bazel-out/"):
            return False
    if not args.include_external:
        if filename.startswith("external/"):
            return False
    return True

def modifyCompileCommand(target, args):
    cc, options = target["command"].split(" ", 1)

    options = options.replace("-std=c++0x ", "")
    options = options.replace("-std=c++14 ", "")

    options += " -DNDEBUG"

    if args.vscode:

        options = options.replace("-iquote ", "-I ")

    if args.ignore_system_headers:

        options = RE_INCLUDE_SYSTEM.sub("", options)

    if isHeader(target["file"]):
        options += " -Wno-pragma-once-outside-header -Wno-unused-const-variable"
        options += " -Wno-unused-function"
        if not target["file"].startswith("external/"):

            options = "-x c++ -std=c++17 -fexceptions " + options

    target["command"] = " ".join([cc, options])
    return target

def fixCompilationDatabase(args, db):
    db = [
        modifyCompileCommand(target, args)
        for target in db
        if isCompileTarget(target, args)
    ]

    with open("compile_commands.json", "w") as db_file:
        json.dump(db, db_file, indent=2)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate JSON compilation database"
    )
    parser.add_argument("--include_external", action="store_true")
    parser.add_argument("--include_genfiles", action="store_true")
    parser.add_argument("--include_headers", action="store_true")
    parser.add_argument("--vscode", action="store_true")
    parser.add_argument("--ignore_system_headers", action="store_true")
    parser.add_argument("--dedup_targets", action="store_true")
    parser.add_argument("bazel_targets", nargs="*", default=["//..."])
    args = parser.parse_args()
    fixCompilationDatabase(args, generateCompilationDatabase(args))
