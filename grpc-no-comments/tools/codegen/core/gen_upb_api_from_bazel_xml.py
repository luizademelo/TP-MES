#!/usr/bin/env python3

# Copyright 2021 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import collections
import os
import re
import shutil
import subprocess
import xml.etree.ElementTree

Rule = collections.namedtuple("Rule", "name type srcs deps proto_files")

BAZEL_BIN = "tools/bazel"

def parse_bazel_rule(elem):
    """Returns a rule from bazel XML rule."""
    srcs = []
    deps = []
    for child in elem:
        if child.tag == "list" and child.attrib["name"] == "srcs":
            for tag in child:
                if tag.tag == "label":
                    srcs.append(tag.attrib["value"])
        if child.tag == "list" and child.attrib["name"] == "deps":
            for tag in child:
                if tag.tag == "label":
                    deps.append(tag.attrib["value"])
        if child.tag == "label":

            label_name = child.attrib["name"]
            if label_name in ["actual"]:
                actual_name = child.attrib.get("value", None)
                if actual_name:
                    # HACK: since we do a lot of transitive dependency scanning,

                    deps.append(actual_name)
    return Rule(elem.attrib["name"], elem.attrib["class"], srcs, deps, [])

def get_transitive_protos(rules, t):
    que = [
        t,
    ]
    visited = set()
    ret = []
    while que:
        name = que.pop(0)
        rule = rules.get(name, None)
        if rule:
            for dep in rule.deps:
                if dep not in visited:
                    visited.add(dep)
                    que.append(dep)
            for src in rule.srcs:
                if src.endswith(".proto"):
                    ret.append(src)
    return list(set(ret))

def read_upb_bazel_rules():
    """Runs bazel query on given package file and returns all upb rules."""

    result = subprocess.check_output(
        [BAZEL_BIN, "query", "--output", "xml", "--noimplicit_deps", "//:all"]
    )
    root = xml.etree.ElementTree.fromstring(result)
    rules = [
        parse_bazel_rule(elem)
        for elem in root
        if elem.tag == "rule"
        and elem.attrib["class"]
        in [
            "upb_c_proto_library",
            "upb_proto_reflection_library",
        ]
    ]

    all_deps = [dep for rule in rules for dep in rule.deps]
    result = subprocess.check_output(
        [
            BAZEL_BIN,
            "query",
            "--output",
            "xml",
            "--noimplicit_deps",
            " union ".join("deps({0})".format(d) for d in all_deps),
        ]
    )
    root = xml.etree.ElementTree.fromstring(result)
    dep_rules = {}
    for dep_rule in (
        parse_bazel_rule(elem) for elem in root if elem.tag == "rule"
    ):
        dep_rules[dep_rule.name] = dep_rule

    for rule in rules:
        if not rule.type.startswith("upb_"):
            continue
        if len(rule.deps) == 1:
            rule.proto_files.extend(
                get_transitive_protos(dep_rules, rule.deps[0])
            )
    return rules

def build_upb_bazel_rules(rules):
    result = subprocess.check_output(
        [BAZEL_BIN, "build"] + [rule.name for rule in rules]
    )

def get_upb_path(proto_path, ext):
    return proto_path.replace(":", "/").replace(".proto", ext)

def get_bazel_bin_root_path(elink, file):
    BAZEL_BIN_ROOT = "bazel-bin/"
    if elink[0] == "@com_google_protobuf//":
        name = re.search("google/protobuf/([a-z_]*)\.", file).group(1)
        result = os.path.join(
            BAZEL_BIN_ROOT,
            "external",
            elink[0].replace("@", "").replace("//", ""),
            "src",
            "google",
            "protobuf",
            "_virtual_imports",
            "%s_proto" % name,
        )
        return os.path.join(result, file)
    if elink[0].startswith("@"):

        result = os.path.join(
            BAZEL_BIN_ROOT,
            "external",
            elink[0].replace("@", "").replace("//", ""),
        )
        if elink[1]:
            result = os.path.join(result, elink[1])
        return os.path.join(result, file)
    else:

        return os.path.join(BAZEL_BIN_ROOT, file)

def get_external_link(file):
    EXTERNAL_LINKS = [
        ("@com_google_protobuf//", "src/"),
        ("@com_google_googleapis//", ""),
        ("@com_github_cncf_xds//", ""),
        ("@com_envoyproxy_protoc_gen_validate//", ""),
        ("@envoy_api//", ""),
        ("@opencensus_proto//", ""),
    ]
    for external_link in EXTERNAL_LINKS:
        if file.startswith(external_link[0]):
            return external_link
    return ("//", "")

def copy_upb_generated_files(rules, args):
    files = {}
    for rule in rules:
        if rule.type == "upb_c_proto_library":

            extensions = [".upb.h", ".upb_minitable.h", ".upb_minitable.c"]
            output_dir = args.upb_out
        else:
            extensions = [".upbdefs.h", ".upbdefs.c"]
            output_dir = args.upbdefs_out
        for proto_file in rule.proto_files:
            elink = get_external_link(proto_file)
            prefix_to_strip = elink[0] + elink[1]
            if not proto_file.startswith(prefix_to_strip):
                raise Exception(
                    'Source file "{0}" in does not have the expected prefix'
                    ' "{1}"'.format(proto_file, prefix_to_strip)
                )
            proto_file = proto_file[len(prefix_to_strip) :]
            for ext in extensions:
                file = get_upb_path(proto_file, ext)
                src = get_bazel_bin_root_path(elink, file)
                dst = os.path.join(output_dir, file)
                files[src] = dst
    for src, dst in files.items():
        if args.verbose:
            print("Copy:")
            print("    {0}".format(src))
            print(" -> {0}".format(dst))
        os.makedirs(os.path.split(dst)[0], exist_ok=True)
        shutil.copyfile(src, dst)

parser = argparse.ArgumentParser(description="UPB code-gen from bazel")
parser.add_argument("--verbose", default=False, action="store_true")
parser.add_argument(
    "--upb_out",
    default="src/core/ext/upb-gen",
    help="Output directory for upb targets",
)
parser.add_argument(
    "--upbdefs_out",
    default="src/core/ext/upbdefs-gen",
    help="Output directory for upbdefs targets",
)

def main():
    args = parser.parse_args()
    rules = read_upb_bazel_rules()
    if args.verbose:
        print("Rules:")
        for rule in rules:
            print(
                "  name={0} type={1} proto_files={2}".format(
                    rule.name, rule.type, rule.proto_files
                )
            )
    if rules:
        build_upb_bazel_rules(rules)
        copy_upb_generated_files(rules, args)

if __name__ == "__main__":
    main()
