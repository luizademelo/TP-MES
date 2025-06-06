#!/usr/bin/python
# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import re
import sys

def parse_link_map(filename):
    table_tag = {}
    state = "start"

    table_stats_symbol = {}
    table_stats_dead = {}
    section_total_size = 0
    symbol_total_size = 0

    boringssl_size = 0
    core_size = 0
    objc_size = 0
    protobuf_size = 0

    lines = open(filename, encoding="utf-8", errors="ignore").readlines()
    for line in lines:
        line_stripped = line[:-1]
        if "# Object files:" == line_stripped:
            state = "object"
            continue
        elif "# Sections:" == line_stripped:
            state = "section"
            continue
        elif "# Symbols:" == line_stripped:
            state = "symbol"
            continue
        elif "# Dead Stripped Symbols:" == line_stripped:
            state = "dead"
            continue

        if state == "object":
            segs = re.search("(\[ *[0-9]*\]) (.*)", line_stripped)
            table_tag[segs.group(1)] = segs.group(2)

        if state == "section":
            if len(line_stripped) == 0 or line_stripped[0] == "#":
                continue
            segs = re.search("^(.+?)\s+(.+?)\s+.*", line_stripped)
            section_total_size += int(segs.group(2), 16)

        if state == "symbol":
            if len(line_stripped) == 0 or line_stripped[0] == "#":
                continue
            segs = re.search("^.+?\s+(.+?)\s+(\[.+?\]).*", line_stripped)
            if not segs:
                continue
            target = table_tag[segs.group(2)]
            target_stripped = re.search("^(.*?)(\(.+?\))?$", target).group(1)
            size = int(segs.group(1), 16)
            if not target_stripped in table_stats_symbol:
                table_stats_symbol[target_stripped] = 0
            table_stats_symbol[target_stripped] += size
            if "BoringSSL" in target_stripped:
                boringssl_size += size
            elif "libgRPC-Core" in target_stripped:
                core_size += size
            elif (
                "libgRPC-RxLibrary" in target_stripped
                or "libgRPC" in target_stripped
                or "libgRPC-ProtoLibrary" in target_stripped
            ):
                objc_size += size
            elif "libProtobuf" in target_stripped:
                protobuf_size += size

    for target in table_stats_symbol:
        symbol_total_size += table_stats_symbol[target]

    return (
        core_size,
        objc_size,
        boringssl_size,
        protobuf_size,
        symbol_total_size,
    )

def main():
    filename = sys.argv[1]
    (
        core_size,
        objc_size,
        boringssl_size,
        protobuf_size,
        total_size,
    ) = parse_link_map(filename)
    print("Core size:{:,}".format(core_size))
    print("ObjC size:{:,}".format(objc_size))
    print("BoringSSL size:{:,}".format(boringssl_size))
    print("Protobuf size:{:,}\n".format(protobuf_size))
    print("Total size:{:,}".format(total_size))

if __name__ == "__main__":
    main()
