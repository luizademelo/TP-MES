#!/usr/bin/env python2.7
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Change comments style of source files from // to /** */"""

import re
import sys

if len(sys.argv) < 2:
    print("Please provide at least one source file name as argument.")
    sys.exit()

for file_name in sys.argv[1:]:
    print(
        "Modifying format of {file} comments in place...".format(
            file=file_name,
        )
    )

    with open(file_name, "r") as input_file:
        lines = input_file.readlines()

    def peek():
        return lines[0]

    def read_line():
        return lines.pop(0)

    def more_input_available():
        return lines

    output_lines = []

    def write(line):
        output_lines.append(line)

    def flush_output():
        with open(file_name, "w") as output_file:
            for line in output_lines:
                output_file.write(line)

    comment_regex = r"^(\s*)//\s(.*)$"

    def is_comment(line):
        return re.search(comment_regex, line)

    def isnt_comment(line):
        return not is_comment(line)

    def next_line(predicate):
        return more_input_available() and predicate(peek())

    def indentation_of(line):
        match = re.search(comment_regex, line)
        return match.group(1)

    def content(line):
        match = re.search(comment_regex, line)
        return match.group(2)

    def format_as_block(comment_block):
        if len(comment_block) == 0:
            return []

        indent = indentation_of(comment_block[0])

        if len(comment_block) == 1:
            return [indent + "/** " + content(comment_block[0]) + " */\n"]

        block = (
            ["/**"]
            + [" * " + content(line) for line in comment_block]
            + [" */"]
        )
        return [indent + line.rstrip() + "\n" for line in block]

    while more_input_available():
        while next_line(isnt_comment):
            write(read_line())

        comment_block = []

        while next_line(is_comment):
            comment_block.append(read_line())

        for line in format_as_block(comment_block):
            write(line)

    flush_output()
