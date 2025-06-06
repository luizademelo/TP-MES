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
import re
import sys

IGNORED_FILES = [
    # note: the grpc_core::Server redundant namespace qualification is required

    "src/core/ext/transport/chttp2/server/chttp2_server.h",
    "src/core/server/server.h",

    "src/core/lib/debug/trace_impl.h",
]

def find_closing_mustache(contents, initial_depth):
    """Find the closing mustache for a given number of open mustaches."""
    depth = initial_depth
    start_len = len(contents)
    while contents:

        if contents.startswith('R"'):
            contents = contents[2:]
            offset = contents.find("(")
            assert offset != -1
            prefix = contents[:offset]
            contents = contents[offset:]
            offset = contents.find(f'){prefix}"')
            assert offset != -1
            contents = contents[offset + len(prefix) + 2 :]

        elif contents[0] == '"':
            contents = contents[1:]
            while contents[0] != '"':
                if contents.startswith("\\\\"):
                    contents = contents[2:]
                elif contents.startswith('\\"'):
                    contents = contents[2:]
                else:
                    contents = contents[1:]
            contents = contents[1:]

        elif (
            contents.startswith("'{'")
            or contents.startswith("'\"'")
            or contents.startswith("'}'")
        ):
            contents = contents[3:]

        elif contents.startswith("//"):
            contents = contents[contents.find("\n") :]
        elif contents.startswith("/*"):
            contents = contents[contents.find("*/") + 2 :]

        elif contents[0] == "{":
            contents = contents[1:]
            depth += 1
        elif contents[0] == "}":
            contents = contents[1:]
            depth -= 1
            if depth == 0:
                return start_len - len(contents)

        else:
            contents = contents[1:]
    return None

def is_a_define_statement(match, body):
    """See if the matching line begins with #define"""

    m = re.search(
        r"^#define.*{}$".format(match.group(0)),
        body[: match.end()],
        re.MULTILINE,
    )
    return m is not None

def update_file(contents, namespaces):
    """Scan the contents of a file, and for top-level namespaces in namespaces remove redundant usages."""
    output = ""
    while contents:
        m = re.search(r"namespace ([a-zA-Z0-9_]*) {", contents)
        if not m:
            output += contents
            break
        output += contents[: m.end()]
        contents = contents[m.end() :]
        end = find_closing_mustache(contents, 1)
        if end is None:
            print(
                "Failed to find closing mustache for namespace {}".format(
                    m.group(1)
                )
            )
            print("Remaining text:")
            print(contents)
            sys.exit(1)
        body = contents[:end]
        namespace = m.group(1)
        if namespace in namespaces:
            while body:

                m = re.search(r"\b" + namespace + r"::\b", body)
                if not m:
                    break

                if m.start() >= 2 and body[m.start() - 2 :].startswith("::"):
                    output += body[: m.end()]

                elif is_a_define_statement(m, body):
                    output += body[: m.end()]
                else:
                    output += body[: m.start()]
                body = body[m.end() :]
        output += body
        contents = contents[end:]
    return output

_TEST = """
namespace bar {
    namespace baz {
    }
}
namespace foo {}
namespace foo {
    foo::a;
    ::foo::a;
}
{R"foo({
foo::a;
}foo)"}
"""
_TEST_EXPECTED = """
namespace bar {
    namespace baz {
    }
}
namespace foo {}
namespace foo {
    a;
    ::foo::a;
}
{R"foo({
foo::a;
}foo)"}
"""
output = update_file(_TEST, ["foo"])
if output != _TEST_EXPECTED:
    import difflib

    print("FAILED: self check")
    print(
        "\n".join(
            difflib.ndiff(_TEST_EXPECTED.splitlines(1), output.splitlines(1))
        )
    )
    sys.exit(1)

Config = collections.namedtuple("Config", ["dirs", "namespaces"])

_CONFIGURATION = (Config(["src/core", "test/core"], ["grpc_core"]),)

changed = []

for config in _CONFIGURATION:
    for dir in config.dirs:
        for root, dirs, files in os.walk(dir):
            for file in files:
                if file.endswith(".cc") or file.endswith(".h"):
                    path = os.path.join(root, file)
                    if path in IGNORED_FILES:
                        continue
                    try:
                        with open(path) as f:
                            contents = f.read()
                    except IOError:
                        continue
                    try:
                        updated = update_file(contents, config.namespaces)
                    except:
                        print(f"error checking {file}")
                        raise
                    if updated != contents:
                        changed.append(path)
                        with open(os.path.join(root, file), "w") as f:
                            f.write(updated)

if changed:
    print("The following files were changed:")
    for path in changed:
        print("  " + path)
    sys.exit(1)
