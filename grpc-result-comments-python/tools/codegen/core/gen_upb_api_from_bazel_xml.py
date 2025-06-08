Here's the commented version of the code:

```python
#!/usr/bin/env python3

# Copyright 2021 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import collections
import os
import re
import shutil
import subprocess
import xml.etree.ElementTree

# Define a named tuple to represent Bazel rules with their attributes
Rule = collections.namedtuple("Rule", "name type srcs deps proto_files")

# Path to the Bazel binary
BAZEL_BIN = "tools/bazel"

def parse_bazel_rule(elem):
    """Parse a Bazel XML rule element into a Rule object.
    
    Args:
        elem: An XML element representing a Bazel rule
        
    Returns:
        A Rule namedtuple containing:
        - name: The rule's name
        - type: The rule's class/type
        - srcs: List of source files
        - deps: List of dependencies
        - proto_files: Empty list (to be populated later)
    """
    srcs = []
    deps = []
    for child in elem:
        # Extract source files
        if child.tag == "list" and child.attrib["name"] == "srcs":
            for tag in child:
                if tag.tag == "label":
                    srcs.append(tag.attrib["value"])
        # Extract dependencies
        if child.tag == "list" and child.attrib["name"] == "deps":
            for tag in child:
                if tag.tag == "label":
                    deps.append(tag.attrib["value"])
        # Handle special case for 'actual' attribute (used in alias rules)
        if child.tag == "label":
            label_name = child.attrib["name"]
            if label_name in ["actual"]:
                actual_name = child.attrib.get("value", None)
                if actual_name:
                    # HACK: since we do a lot of transitive dependency scanning,
                    # we treat 'actual' as a dependency
                    deps.append(actual_name)
    return Rule(elem.attrib["name"], elem.attrib["class"], srcs, deps, [])

def get_transitive_protos(rules, t):
    """Get all transitive .proto files from a given rule.
    
    Args:
        rules: Dictionary of rule names to Rule objects
        t: The starting rule name
        
    Returns:
        List of all .proto files found in the transitive closure
    """
    que = [
        t,
    ]
    visited = set()
    ret = []
    while que:
        name = que.pop(0)
        rule = rules.get(name, None)
        if rule:
            # Add all dependencies to the queue
            for dep in rule.deps:
                if dep not in visited:
                    visited.add(dep)
                    que.append(dep)
            # Collect all .proto files from sources
            for src in rule.srcs:
                if src.endswith(".proto"):
                    ret.append(src)
    return list(set(ret))  # Remove duplicates

def read_upb_bazel_rules():
    """Query Bazel for all UPB-related rules and their dependencies.
    
    Returns:
        List of Rule objects representing UPB proto libraries
    """
    # Query for all UPB rules in the main workspace
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

    # Query for all dependencies of these rules
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

    # Populate proto_files for each UPB rule
    for rule in rules:
        if not rule.type.startswith("upb_"):
            continue
        if len(rule.deps) == 1:
            rule.proto_files.extend(
                get_transitive_protos(dep_rules, rule.deps[0])
            )
    return rules

def build_upb_bazel_rules(rules):
    """Build all UPB rules using Bazel."""
    result = subprocess.check_output(
        [BAZEL_BIN, "build"] + [rule.name for rule in rules]
    )

def get_upb_path(proto_path, ext):
    """Convert a proto path to a UPB-generated file path with given extension.
    
    Args:
        proto_path: Path to the .proto file
        ext: File extension to append
        
    Returns:
        Path with .proto replaced by extension and colons converted to slashes
    """
    return proto_path.replace(":", "/").replace(".proto", ext)

def get_bazel_bin_root_path(elink, file):
    """Get the full path to a file in bazel-bin directory.
    
    Args:
        elink: Tuple representing external link info (prefix, subpath)
        file: Relative file path
        
    Returns:
        Absolute path to the file in bazel-bin directory
    """
    BAZEL_BIN_ROOT = "bazel-bin/"
    # Special handling for protobuf files
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
    # Handle other external dependencies
    if elink[0].startswith("@"):
        result = os.path.join(
            BAZEL_BIN_ROOT,
            "external",
            elink[0].replace("@", "").replace("//", ""),
        )
        if elink[1]:
            result = os.path.join(result, elink[1])
        return os.path.join(result, file)
    # Handle local files
    else:
        return os.path.join(BAZEL_BIN_ROOT, file)

def get_external_link(file):
    """Determine if a file belongs to an external repository.
    
    Args:
        file: The file path to check
        
    Returns:
        Tuple of (external repository prefix, subpath) or ("//", "") for local files
    """
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
    """Copy generated UPB files from bazel-bin to their final destinations.
    
    Args:
        rules: List of Rule objects
        args: Command line arguments
    """
    files = {}
    for rule in rules:
        # Determine file extensions based on rule type
        if rule.type == "upb_c_proto_library":
            extensions = [".upb.h", ".upb_minitable.h", ".upb_minitable.c"]
            output_dir = args.upb_out
        else:
            extensions = [".upbdefs.h", ".upbdefs.c"]
            output_dir = args.upbdefs_out
        # Process each proto file in the rule
        for proto_file in rule.proto_files:
            elink = get_external_link(proto_file)
            prefix_to_strip = elink[0] + elink[1]
            if not proto_file.startswith(prefix_to_strip):
                raise Exception(
                    'Source file "{0}" in does not have the expected prefix'
                    ' "{1}"'.format(proto_file, prefix_to_strip)
                )
            proto_file = proto_file[len(prefix_to_strip) :]
            # Generate source and destination paths for each extension
            for ext in extensions:
                file = get_upb_path(proto_file, ext)
                src = get_bazel_bin_root_path(elink, file)
                dst = os.path.join(output_dir, file)
                files[src] = dst
    # Perform the actual file copies
    for src, dst in files.items():
        if args.verbose:
            print("Copy:")
            print("    {0}".format(src))
            print(" -> {0}".format(dst))
        os.makedirs(os.path.split(dst)[0], exist_ok=True)
        shutil.copyfile(src, dst)

# Set up command line argument parser
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
    """Main function that orchestrates the UPB code generation process."""
    args = parser.parse_args()
    # Read and process Bazel rules
    rules = read_upb_bazel_rules()
    if args.verbose:
        print("Rules:")
        for rule in rules:
            print(
                "  name={0} type={1} proto_files={2}".format(
                    rule.name, rule.type, rule.proto_files
                )
            )
    # If we found any rules, build them and copy the generated files
    if rules:
        build_upb_bazel_rules(rules)
        copy_upb_generated_files(rules, args)

if __name__ == "__main__":
    main()
```