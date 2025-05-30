#!/usr/bin/env python3

# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import collections
import os

def to_inc(filename):
    """Given filename, synthesize what should go in an include statement to get that file"""
    if filename.startswith("include/"):
        return "<%s>" % filename[len("include/") :]
    return '"%s"' % filename

def set_pragmas(filename, pragmas):
    """Set the file-level IWYU pragma in filename"""
    lines = []
    saw_first_define = False
    for line in open(filename).read().splitlines():
        if line.startswith("// IWYU pragma: "):
            continue
        lines.append(line)
        if not saw_first_define and line.startswith("#define "):
            saw_first_define = True
            lines.append("")
            for pragma in pragmas:
                lines.append("// IWYU pragma: %s" % pragma)
            lines.append("")
    open(filename, "w").write("\n".join(lines) + "\n")

def set_exports(pub, cg):
    """In file pub, mark the include for cg with IWYU pragma: export"""
    lines = []
    for line in open(pub).read().splitlines():
        if line.startswith("#include %s" % to_inc(cg)):
            lines.append("#include %s  // IWYU pragma: export" % to_inc(cg))
        else:
            lines.append(line)
    open(pub, "w").write("\n".join(lines) + "\n")

CG_ROOTS_GRPC = (
    (r"sync", "grpc/support/sync.h", False),
    (r"atm", "grpc/support/atm.h", False),
    (r"grpc_types", "grpc/grpc.h", True),
    (r"gpr_types", "grpc/grpc.h", True),
    (r"compression_types", "grpc/compression.h", True),
    (r"connectivity_state", "grpc/grpc.h", True),
)

CG_ROOTS_GRPCPP = [
    (r"status_code_enum", "grpcpp/support/status.h", False),
]

def fix_tree(tree, cg_roots):
    """Fix one include tree"""

    reverse_map = collections.defaultdict(list)

    cg_reverse_map = collections.defaultdict(list)
    for root, dirs, files in os.walk(tree):
        root_map = cg_reverse_map if "/impl/codegen" in root else reverse_map
        for filename in files:
            root_map[filename].append(root)

    for filename, paths in cg_reverse_map.items():
        print("****", filename)

        if not filename.endswith(".h"):
            continue
        pragmas = []

        for root, target, friend in cg_roots:
            print(root, target, friend)
            if filename.startswith(root):
                pragmas = ["private, include <%s>" % target]
                if friend:
                    pragmas.append('friend "src/.*"')
                if len(paths) == 1:
                    path = paths[0]
                    if filename.startswith(root + "."):
                        set_exports("include/" + target, path + "/" + filename)
                    if filename.startswith(root + "_"):
                        set_exports(
                            path + "/" + root + ".h", path + "/" + filename
                        )

        if not pragmas and len(paths) == 1:
            path = paths[0]

            if filename in reverse_map:
                proper = reverse_map[filename]

                if len(proper) == 1:

                    cg = path + "/" + filename
                    pub = proper[0] + "/" + filename

                    if ("#include %s" % to_inc(cg)) in open(pub).read():

                        pragmas = ["private, include %s" % to_inc(pub)]

                        set_exports(pub, cg)

        if not pragmas:
            pragmas = ["private"]
        for path in paths:
            set_pragmas(path + "/" + filename, pragmas)

fix_tree("include/grpc", CG_ROOTS_GRPC)
fix_tree("include/grpcpp", CG_ROOTS_GRPCPP)
