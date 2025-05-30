#!/usr/bin/env python3
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import collections
import os
import subprocess
from typing import Any, Dict, Iterable, List, Optional
import xml.etree.ElementTree as ET

import build_cleaner

BuildMetadata = Dict[str, Any]
BuildDict = Dict[str, BuildMetadata]
BuildYaml = Dict[str, Any]

BuildMetadata = Dict[str, Any]
BuildDict = Dict[str, BuildMetadata]
BuildYaml = Dict[str, Any]

class ExternalProtoLibrary:
    """ExternalProtoLibrary is the struct about an external proto library.

    Fields:
    - destination(int): The relative path of this proto library should be.
        Preferably, it should match the submodule path.
    - proto_prefix(str): The prefix to remove in order to insure the proto import
        is correct. For more info, see description of
        https://github.com/grpc/grpc/pull/25272.
    - urls(List[str]): Following 3 fields should be filled by build metadata from
        Bazel.
    - hash(str): The hash of the downloaded archive
    - strip_prefix(str): The path to be stripped from the extracted directory, see
        http_archive in Bazel.
    """

    def __init__(
        self, destination, proto_prefix, urls=None, hash="", strip_prefix=""
    ):
        self.destination = destination
        self.proto_prefix = proto_prefix
        if urls is None:
            self.urls = []
        else:
            self.urls = urls
        self.hash = hash
        self.strip_prefix = strip_prefix

EXTERNAL_PROTO_LIBRARIES = {
    "envoy_api": ExternalProtoLibrary(
        destination="third_party/envoy-api",
        proto_prefix="third_party/envoy-api/",
    ),
    "com_google_googleapis": ExternalProtoLibrary(
        destination="third_party/googleapis",
        proto_prefix="third_party/googleapis/",
    ),
    "com_github_cncf_xds": ExternalProtoLibrary(
        destination="third_party/xds", proto_prefix="third_party/xds/"
    ),
    "com_envoyproxy_protoc_gen_validate": ExternalProtoLibrary(
        destination="third_party/protoc-gen-validate",
        proto_prefix="third_party/protoc-gen-validate/",
    ),
    "opencensus_proto": ExternalProtoLibrary(
        destination="third_party/opencensus-proto/src",
        proto_prefix="third_party/opencensus-proto/src/",
    ),
}

EXTERNAL_SOURCE_PREFIXES = {

    "@utf8_range//": "third_party/utf8_range",
    "@com_googlesource_code_re2//": "third_party/re2",
    "@com_google_googletest//": "third_party/googletest",
    "@@googletest//": "third_party/googletest",
    "@com_google_protobuf//upb": "third_party/upb/upb",
    "@com_google_protobuf//third_party/utf8_range": "third_party/utf8_range",
    "@zlib//": "third_party/zlib",
}

def _bazel_query_xml_tree(query: str) -> ET.Element:
    """Get xml output of bazel query invocation, parsed as XML tree"""
    output = subprocess.check_output(
        ["tools/bazel", "query", "--noimplicit_deps", "--output", "xml", query]
    )
    return ET.fromstring(output)

def _rule_dict_from_xml_node(rule_xml_node):
    """Converts XML node representing a rule (obtained from "bazel query --output xml") to a dictionary that contains all the metadata we will need."""
    rule_name = rule_xml_node.attrib.get("name")
    result = {
        "class": rule_xml_node.attrib.get("class"),
        "name": rule_name,
        "srcs": [],
        "hdrs": [],
        "textual_hdrs": [],
        "deps": [],
        "data": [],
        "tags": [],
        "args": [],
        "generator_function": None,
        "size": None,
        "flaky": False,
        "actual": None,
    }
    for child in rule_xml_node:

        if child.tag == "list":
            list_name = child.attrib["name"]
            if list_name in [
                "srcs",
                "hdrs",
                "textual_hdrs",
                "deps",
                "data",
                "tags",
                "args",
            ]:
                result[list_name] += [item.attrib["value"] for item in child]
        if child.tag == "string":
            string_name = child.attrib["name"]
            if string_name in ["generator_function", "size"]:
                result[string_name] = child.attrib["value"]
        if child.tag == "boolean":
            bool_name = child.attrib["name"]
            if bool_name in ["flaky"]:
                result[bool_name] = child.attrib["value"] == "true"
        if child.tag == "label":

            label_name = child.attrib["name"]
            if label_name in ["actual"]:
                actual_name = child.attrib.get("value", None)
                if actual_name:
                    result["actual"] = actual_name
                    # HACK: since we do a lot of transitive dependency scanning,

                    result["deps"].append(actual_name)
                elif rule_name == "//third_party:libssl":

                    result["deps"].append("@boringssl//:ssl")
                elif rule_name == "//third_party:libcrypto":

                    result["deps"].append("@boringssl//:crypto")

    return result

def _extract_rules_from_bazel_xml(xml_tree):
    """Extract bazel rules from an XML tree node obtained from "bazel query --output xml" command."""
    result = {}
    for child in xml_tree:
        if child.tag == "rule":
            rule_dict = _rule_dict_from_xml_node(child)
            rule_clazz = rule_dict["class"]
            rule_name = rule_dict["name"]
            if rule_clazz in [
                "cc_library",
                "cc_binary",
                "cc_test",
                "cc_proto_library",
                "cc_proto_gen_validate",
                "proto_library",
                "upb_c_proto_library",
                "upb_proto_reflection_library",
                "alias",
                "bind",
                "genrule",
            ]:
                if rule_name in result:
                    raise Exception("Rule %s already present" % rule_name)
                result[rule_name] = rule_dict
    return result

def _get_bazel_label(target_name: str) -> str:
    if target_name.startswith("@"):
        return target_name
    if ":" in target_name:
        return "//%s" % target_name
    else:
        return "//:%s" % target_name

def _try_extract_source_file_path(label: str) -> str:
    """Gets relative path to source file from bazel deps listing"""
    if label.startswith("@"):

        for lib_name, prefix in EXTERNAL_SOURCE_PREFIXES.items():
            if label.startswith(lib_name):
                return (
                    label.replace("%s" % lib_name, prefix)
                    .replace(":", "/")
                    .replace("//", "/")
                )

        for lib_name, external_proto_lib in EXTERNAL_PROTO_LIBRARIES.items():
            if label.startswith("@" + lib_name + "//"):
                return label.replace(
                    "@%s//" % lib_name,
                    external_proto_lib.proto_prefix,
                ).replace(":", "/")

        return None
    else:
        if label.startswith("//"):
            label = label[len("//") :]

        if label.startswith(":"):
            label = label[len(":") :]

        return label.replace(":", "/")

def _has_header_suffix(label: str) -> bool:
    """Returns True if the label has a suffix that looks like a C/C++ include file"""
    return (
        label.endswith(".h")
        or label.endswith(".h")
        or label.endswith(".hpp")
        or label.endswith(".inc")
    )

def _extract_public_headers(bazel_rule: BuildMetadata) -> List[str]:
    """Gets list of public headers from a bazel rule"""
    result = []
    for dep in bazel_rule["hdrs"]:
        if dep.startswith("//:include/") and _has_header_suffix(dep):
            source_file_maybe = _try_extract_source_file_path(dep)
            if source_file_maybe:
                result.append(source_file_maybe)
    return list(sorted(result))

def _extract_nonpublic_headers(bazel_rule: BuildMetadata) -> List[str]:
    """Gets list of non-public headers from a bazel rule"""
    result = []
    for dep in list(
        bazel_rule["hdrs"] + bazel_rule["textual_hdrs"] + bazel_rule["srcs"]
    ):
        if not dep.startswith("//:include/") and _has_header_suffix(dep):
            source_file_maybe = _try_extract_source_file_path(dep)
            if source_file_maybe:
                result.append(source_file_maybe)
    return list(sorted(result))

def _extract_sources(bazel_rule: BuildMetadata) -> List[str]:
    """Gets list of source files from a bazel rule"""
    result = []
    for src in bazel_rule["srcs"]:

        if src.startswith("@com_google_protobuf//") and src.endswith(".proto"):
            continue
        if src.endswith(".cc") or src.endswith(".c") or src.endswith(".proto"):
            source_file_maybe = _try_extract_source_file_path(src)
            if source_file_maybe:
                result.append(source_file_maybe)
    return list(sorted(result))

def _extract_deps(
    bazel_rule: BuildMetadata, bazel_rules: BuildDict
) -> List[str]:
    """Gets list of deps from from a bazel rule"""
    deps = set(bazel_rule["deps"])
    for src in bazel_rule["srcs"]:
        if (
            not src.endswith(".cc")
            and not src.endswith(".c")
            and not src.endswith(".proto")
        ):
            if src in bazel_rules:

                deps.add(src)
    return list(sorted(list(deps)))

def _create_target_from_bazel_rule(
    target_name: str, bazel_rules: BuildDict
) -> BuildMetadata:
    """Create build.yaml-like target definition from bazel metadata"""
    bazel_rule = bazel_rules[_get_bazel_label(target_name)]

    result = {
        "name": target_name,
        "_PUBLIC_HEADERS_BAZEL": _extract_public_headers(bazel_rule),
        "_HEADERS_BAZEL": _extract_nonpublic_headers(bazel_rule),
        "_SRC_BAZEL": _extract_sources(bazel_rule),
        "_DEPS_BAZEL": _extract_deps(bazel_rule, bazel_rules),
        "public_headers": bazel_rule["_COLLAPSED_PUBLIC_HEADERS"],
        "headers": bazel_rule["_COLLAPSED_HEADERS"],
        "src": bazel_rule["_COLLAPSED_SRCS"],
        "deps": bazel_rule["_COLLAPSED_DEPS"],
    }
    return result

def _external_dep_name_from_bazel_dependency(bazel_dep: str) -> Optional[str]:
    """Returns name of dependency if external bazel dependency is provided or None"""
    if bazel_dep.startswith("@com_google_absl//"):

        prefixlen = len("@com_google_absl//")
        return bazel_dep[prefixlen:]
    elif bazel_dep == "@com_github_google_benchmark//:benchmark":
        return "benchmark"
    elif bazel_dep == "@boringssl//:ssl":
        return "libssl"
    elif bazel_dep == "@com_github_cares_cares//:ares":
        return "cares"
    elif (
        bazel_dep == "@com_google_protobuf//:protobuf"
        or bazel_dep == "@com_google_protobuf//:protobuf_headers"
    ):
        return "protobuf"
    elif bazel_dep == "@com_google_protobuf//:protoc_lib":
        return "protoc"
    elif bazel_dep == "@io_opentelemetry_cpp//api:api":
        return "opentelemetry-cpp::api"
    elif bazel_dep == "@io_opentelemetry_cpp//sdk/src/metrics:metrics":
        return "opentelemetry-cpp::metrics"
    elif bazel_dep == "@io_opentelemetry_cpp//sdk/src/trace:trace":
        return "opentelemetry-cpp::trace"
    elif (
        bazel_dep
        == "@io_opentelemetry_cpp//exporters/memory:in_memory_span_exporter"
    ):
        return "opentelemetry-cpp::in_memory_span_exporter"
    else:

        return None

def _compute_transitive_metadata(
    rule_name: str, bazel_rules: Any, bazel_label_to_dep_name: Dict[str, str]
) -> None:
    """Computes the final build metadata for Bazel target with rule_name.

    The dependencies that will appear on the deps list are:

    * Public build targets including binaries and tests;
    * External targets, like absl, re2.

    All other intermediate dependencies will be merged, which means their
    source file, headers, etc. will be collected into one build target. This
    step of processing will greatly reduce the complexity of the generated
    build specifications for other build systems, like CMake, Make, setuptools.

    The final build metadata are:
    * _TRANSITIVE_DEPS: all the transitive dependencies including intermediate
                        targets;
    * _COLLAPSED_DEPS:  dependencies that fits our requirement above, and it
                        will remove duplicated items and produce the shortest
                        possible dependency list in alphabetical order;
    * _COLLAPSED_SRCS:  the merged source files;
    * _COLLAPSED_PUBLIC_HEADERS: the merged public headers;
    * _COLLAPSED_HEADERS: the merged non-public headers;
    * _EXCLUDE_DEPS: intermediate targets to exclude when performing collapsing
      of sources and dependencies.

    For the collapsed_deps, the algorithm improved cases like:

    The result in the past:
        end2end_tests -> [grpc_test_util, grpc, gpr, address_sorting, upb]
        grpc_test_util -> [grpc, gpr, address_sorting, upb, ...]
        grpc -> [gpr, address_sorting, upb, ...]

    The result of the algorithm:
        end2end_tests -> [grpc_test_util]
        grpc_test_util -> [grpc]
        grpc -> [gpr, address_sorting, upb, ...]
    """
    bazel_rule = bazel_rules[rule_name]
    direct_deps = _extract_deps(bazel_rule, bazel_rules)
    transitive_deps = set()
    collapsed_deps = set()
    exclude_deps = set()
    collapsed_srcs = set(_extract_sources(bazel_rule))
    collapsed_public_headers = set(_extract_public_headers(bazel_rule))
    collapsed_headers = set(_extract_nonpublic_headers(bazel_rule))

    for dep in direct_deps:
        external_dep_name_maybe = _external_dep_name_from_bazel_dependency(dep)

        if dep in bazel_rules:

            if external_dep_name_maybe is None:
                if "_PROCESSING_DONE" not in bazel_rules[dep]:

                    _compute_transitive_metadata(
                        dep, bazel_rules, bazel_label_to_dep_name
                    )
                transitive_deps.update(
                    bazel_rules[dep].get("_TRANSITIVE_DEPS", [])
                )
                collapsed_deps.update(
                    collapsed_deps, bazel_rules[dep].get("_COLLAPSED_DEPS", [])
                )
                exclude_deps.update(bazel_rules[dep].get("_EXCLUDE_DEPS", []))

        if dep in bazel_label_to_dep_name:
            transitive_deps.update([bazel_label_to_dep_name[dep]])
            collapsed_deps.update(
                collapsed_deps, [bazel_label_to_dep_name[dep]]
            )

            exclude_deps.update(bazel_rules[dep]["_TRANSITIVE_DEPS"])
            continue

        if external_dep_name_maybe is not None:
            transitive_deps.update([external_dep_name_maybe])
            collapsed_deps.update(collapsed_deps, [external_dep_name_maybe])
            continue

    transitive_deps.update(direct_deps)

    transitive_public_deps = set(
        [x for x in transitive_deps if x in bazel_label_to_dep_name]
    )

    collapsed_deps = set([x for x in collapsed_deps if x not in exclude_deps])

    for dep in transitive_deps:
        if dep not in exclude_deps and dep not in transitive_public_deps:
            if dep in bazel_rules:
                collapsed_srcs.update(_extract_sources(bazel_rules[dep]))
                collapsed_public_headers.update(
                    _extract_public_headers(bazel_rules[dep])
                )
                collapsed_headers.update(
                    _extract_nonpublic_headers(bazel_rules[dep])
                )

    bazel_rule["_PROCESSING_DONE"] = True

    bazel_rule["_TRANSITIVE_DEPS"] = list(sorted(transitive_deps))
    bazel_rule["_COLLAPSED_DEPS"] = list(sorted(collapsed_deps))
    bazel_rule["_COLLAPSED_SRCS"] = list(sorted(collapsed_srcs))
    bazel_rule["_COLLAPSED_PUBLIC_HEADERS"] = list(
        sorted(collapsed_public_headers)
    )
    bazel_rule["_COLLAPSED_HEADERS"] = list(sorted(collapsed_headers))
    bazel_rule["_EXCLUDE_DEPS"] = list(sorted(exclude_deps))

def _populate_transitive_metadata(
    bazel_rules: Any, public_dep_names: Iterable[str]
) -> None:
    """Add 'transitive_deps' field for each of the rules"""

    bazel_label_to_dep_name = {}
    for dep_name in public_dep_names:
        bazel_label_to_dep_name[_get_bazel_label(dep_name)] = dep_name

    for rule_name in bazel_rules:
        if "_PROCESSING_DONE" not in bazel_rules[rule_name]:
            _compute_transitive_metadata(
                rule_name, bazel_rules, bazel_label_to_dep_name
            )

def update_test_metadata_with_transitive_metadata(
    all_extra_metadata: BuildDict, bazel_rules: BuildDict
) -> None:
    """Patches test build metadata with transitive metadata."""
    for lib_name, lib_dict in list(all_extra_metadata.items()):

        if (
            lib_dict.get("build") != "test"
            and lib_dict.get("build") != "plugin_test"
        ) or lib_dict.get("_TYPE") != "target":
            continue

        bazel_rule = bazel_rules[_get_bazel_label(lib_name)]

        if "//third_party:benchmark" in bazel_rule["_TRANSITIVE_DEPS"]:
            lib_dict["benchmark"] = True
            lib_dict["defaults"] = "benchmark"

        if "//third_party:gtest" in bazel_rule["_TRANSITIVE_DEPS"]:

            lib_dict["gtest"] = True
            # TODO: this might be incorrect categorization of the test...
            lib_dict["language"] = "c++"

def _get_transitive_protos(bazel_rules, t):
    que = [
        t,
    ]
    visited = set()
    ret = []
    while que:
        name = que.pop(0)
        rule = bazel_rules.get(name, None)
        if rule:
            for dep in rule["deps"]:
                if dep not in visited:
                    visited.add(dep)
                    que.append(dep)
            for src in rule["srcs"]:
                if src.endswith(".proto"):
                    ret.append(src)
    return list(set(ret))

def _expand_upb_proto_library_rules(bazel_rules):

    GEN_UPB_ROOT = "//:src/core/ext/upb-gen/"
    GEN_UPBDEFS_ROOT = "//:src/core/ext/upbdefs-gen/"
    EXTERNAL_LINKS = [
        ("@com_google_protobuf//", "src/"),
        ("@com_google_googleapis//", ""),
        ("@com_github_cncf_xds//", ""),
        ("@com_envoyproxy_protoc_gen_validate//", ""),
        ("@envoy_api//", ""),
        ("@opencensus_proto//", ""),
    ]
    for name, bazel_rule in bazel_rules.items():
        gen_func = bazel_rule.get("generator_function", None)
        if gen_func in (
            "grpc_upb_proto_library",
            "grpc_upb_proto_reflection_library",
        ):

            deps = bazel_rule["deps"]
            if len(deps) != 1:
                raise Exception(
                    'upb rule "{0}" should have 1 proto dependency but has'
                    ' "{1}"'.format(name, deps)
                )

            bazel_rule["deps"] = [
                "@com_google_protobuf//upb:descriptor_upb_proto",
                "@com_google_protobuf//upb:generated_code_support",
            ]

            protos = _get_transitive_protos(bazel_rules, deps[0])
            if len(protos) == 0:
                raise Exception(
                    'upb rule "{0}" should have at least one proto file.'.format(
                        name
                    )
                )
            srcs = []
            hdrs = []
            for proto_src in protos:
                for external_link in EXTERNAL_LINKS:
                    if proto_src.startswith(external_link[0]):
                        prefix_to_strip = external_link[0] + external_link[1]
                        if not proto_src.startswith(prefix_to_strip):
                            raise Exception(
                                'Source file "{0}" in upb rule {1} does not'
                                ' have the expected prefix "{2}"'.format(
                                    proto_src, name, prefix_to_strip
                                )
                            )
                        proto_src = proto_src[len(prefix_to_strip) :]
                        break
                if proto_src.startswith("@"):
                    raise Exception('"{0}" is unknown workspace.'.format(name))
                proto_src_file = _try_extract_source_file_path(proto_src)
                if not proto_src_file:
                    raise Exception(
                        'Failed to get source file for "{0}" in upb rule "{1}".'.format(
                            proto_src, name
                        )
                    )

                extensions = (

                    [".upb.h", ".upb_minitable.h", ".upb_minitable.c"]
                    if gen_func == "grpc_upb_proto_library"
                    else [".upbdefs.h", ".upbdefs.c"]
                )
                root = (
                    GEN_UPB_ROOT
                    if gen_func == "grpc_upb_proto_library"
                    else GEN_UPBDEFS_ROOT
                )
                for ext in extensions:
                    srcs.append(root + proto_src_file.replace(".proto", ext))
                    hdrs.append(root + proto_src_file.replace(".proto", ext))
            bazel_rule["srcs"] = srcs
            bazel_rule["hdrs"] = hdrs

def _patch_grpc_proto_library_rules(bazel_rules):
    for name, bazel_rule in bazel_rules.items():
        generator_func = bazel_rule.get("generator_function", None)
        if name.startswith("//") and (
            generator_func == "grpc_proto_library"
            or bazel_rule["class"] == "cc_proto_library"
        ):

            bazel_rule["deps"].append("//third_party:protobuf")

def _patch_descriptor_upb_proto_library(bazel_rules):

    bazel_rule = bazel_rules.get(
        "@com_google_protobuf//upb:descriptor_upb_proto", None
    )
    if bazel_rule:
        bazel_rule["srcs"].append(
            ":src/core/ext/upb-gen/google/protobuf/descriptor.upb_minitable.c"
        )
        bazel_rule["hdrs"].append(
            ":src/core/ext/upb-gen/google/protobuf/descriptor.upb.h"
        )

def _generate_build_metadata(
    build_extra_metadata: BuildDict, bazel_rules: BuildDict
) -> BuildDict:
    """Generate build metadata in build.yaml-like format bazel build metadata and build.yaml-specific "extra metadata"."""
    lib_names = list(build_extra_metadata.keys())
    result = {}

    for lib_name in lib_names:
        lib_dict = _create_target_from_bazel_rule(lib_name, bazel_rules)

        lib_dict.update(build_extra_metadata.get(lib_name, {}))

        result[lib_name] = lib_dict

    for lib_name in lib_names:
        to_name = build_extra_metadata.get(lib_name, {}).get("_RENAME", None)
        if to_name:

            if to_name in result:
                raise Exception(
                    "Cannot rename target "
                    + str(lib_name)
                    + ", "
                    + str(to_name)
                    + " already exists."
                )
            lib_dict = result.pop(lib_name)
            lib_dict["name"] = to_name
            result[to_name] = lib_dict

            for lib_dict_to_update in list(result.values()):
                lib_dict_to_update["deps"] = list(
                    [
                        to_name if dep == lib_name else dep
                        for dep in lib_dict_to_update["deps"]
                    ]
                )

    return result

def _convert_to_build_yaml_like(lib_dict: BuildMetadata) -> BuildYaml:
    lib_names = [
        lib_name
        for lib_name in list(lib_dict.keys())
        if lib_dict[lib_name].get("_TYPE", "library") == "library"
    ]
    target_names = [
        lib_name
        for lib_name in list(lib_dict.keys())
        if lib_dict[lib_name].get("_TYPE", "library") == "target"
    ]
    test_names = [
        lib_name
        for lib_name in list(lib_dict.keys())
        if lib_dict[lib_name].get("_TYPE", "library") == "test"
        or lib_dict[lib_name].get("_TYPE", "library") == "plugin_test"
    ]

    lib_list = [lib_dict[lib_name] for lib_name in lib_names]
    target_list = [lib_dict[lib_name] for lib_name in target_names]
    test_list = [lib_dict[lib_name] for lib_name in test_names]

    for lib in lib_list:
        for field_to_remove in [
            k for k in list(lib.keys()) if k.startswith("_")
        ]:
            lib.pop(field_to_remove, None)
    for target in target_list:
        for field_to_remove in [
            k for k in list(target.keys()) if k.startswith("_")
        ]:
            target.pop(field_to_remove, None)
        target.pop(
            "public_headers", None
        )
    for test in test_list:
        for field_to_remove in [
            k for k in list(test.keys()) if k.startswith("_")
        ]:
            test.pop(field_to_remove, None)
        test.pop(
            "public_headers", None
        )

    build_yaml_like = {
        "libs": lib_list,
        "filegroups": [],
        "targets": target_list,
        "tests": test_list,
    }
    return build_yaml_like

def _extract_cc_tests(bazel_rules: BuildDict) -> List[str]:
    """Gets list of cc_test tests from bazel rules"""
    result = []
    for bazel_rule in list(bazel_rules.values()):
        if bazel_rule["class"] == "cc_test":
            test_name = bazel_rule["name"]
            if test_name.startswith("//"):
                prefixlen = len("//")
                result.append(test_name[prefixlen:])
    return list(sorted(result))

def _exclude_unwanted_cc_tests(tests: List[str]) -> List[str]:
    """Filters out bazel tests that we don't want to run with other build systems or we cannot build them reasonably"""

    tests = [test for test in tests if not test.startswith("test/cpp/qps:")]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/microbenchmarks:")
    ]
    tests = [
        test
        for test in tests
        if not test.startswith("test/core/promise/benchmark:")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/ext/filters/census:")
        and not test.startswith(
            "test/core/server:xds_channel_stack_modifier_test"
        )
        and not test.startswith("test/cpp/ext/gcp:")
        and not test.startswith("test/cpp/ext/filters/logging:")
        and not test.startswith("test/cpp/interop:observability_interop")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/ext/csm:")
        and not test.startswith("test/cpp/interop:xds_interop")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith(
            "test/cpp/end2end:server_load_reporting_end2end_test"
        )
    ]
    tests = [
        test
        for test in tests
        if not test.startswith(
            "test/cpp/server/load_reporter:lb_load_reporter_test"
        )
    ]

    tests = [
        test
        for test in tests
        if not test.startswith(
            "test/cpp/naming:resolver_component_tests_runner_invoker"
        )
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/end2end:time_change_test")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/end2end:client_crash_test")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/end2end:server_crash_test")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/core/tsi:ssl_session_cache_test")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/cpp/util:channelz_sampler_test")
    ]

    tests = [
        test
        for test in tests
        if not test.startswith("test/core/transport/chaotic_good")
    ]

    tests = [test for test in tests if not test.endswith("_fuzzer")]
    tests = [test for test in tests if "_fuzzer_" not in test]

    return tests

def _generate_build_extra_metadata_for_tests(
    tests: List[str], bazel_rules: BuildDict
) -> BuildDict:
    """For given tests, generate the "extra metadata" that we need for our "build.yaml"-like output. The extra metadata is generated from the bazel rule metadata by using a bunch of heuristics."""
    test_metadata = {}
    for test in tests:
        test_dict = {"build": "test", "_TYPE": "target"}

        bazel_rule = bazel_rules[_get_bazel_label(test)]

        bazel_tags = bazel_rule["tags"]
        if "manual" in bazel_tags:

            test_dict["run"] = False

        if bazel_rule["flaky"]:

            test_dict["run"] = False

        if "no_uses_polling" in bazel_tags:
            test_dict["uses_polling"] = False

        if "grpc_fuzzer" == bazel_rule["generator_function"]:

            print(("skipping fuzzer " + test))
            continue

        if "bazel_only" in bazel_tags:
            continue

        if test.startswith("test/cpp/ext/otel"):
            test_dict["build"] = "plugin_test"
            test_dict["plugin_option"] = "gRPC_BUILD_GRPCPP_OTEL_PLUGIN"

        known_platform_tags = set(["no_windows", "no_mac"])
        if set(bazel_tags).intersection(known_platform_tags):
            platforms = []

            platforms.append("linux")
            platforms.append(
                "posix"
            )
            if "no_mac" not in bazel_tags:
                platforms.append("mac")
            if "no_windows" not in bazel_tags:
                platforms.append("windows")
            test_dict["platforms"] = platforms

        cmdline_args = bazel_rule["args"]
        if cmdline_args:
            test_dict["args"] = list(cmdline_args)

        if test.startswith("test/cpp"):
            test_dict["language"] = "c++"

        elif test.startswith("test/core"):
            test_dict["language"] = "c"
        else:
            raise Exception("wrong test" + test)

        simple_test_name = os.path.basename(_try_extract_source_file_path(test))
        test_dict["_RENAME"] = simple_test_name

        test_metadata[test] = test_dict

    tests_by_simple_name = {}
    for test_name, test_dict in list(test_metadata.items()):
        simple_test_name = test_dict["_RENAME"]
        if simple_test_name not in tests_by_simple_name:
            tests_by_simple_name[simple_test_name] = []
        tests_by_simple_name[simple_test_name].append(test_name)

    for collision_list in list(tests_by_simple_name.values()):
        if len(collision_list) > 1:
            for test_name in collision_list:
                long_name = test_name.replace("/", "_").replace(":", "_")
                print(
                    'short name of "%s" collides with another test, renaming'
                    " to %s" % (test_name, long_name)
                )
                test_metadata[test_name]["_RENAME"] = long_name
    return test_metadata

def _parse_http_archives(xml_tree: ET.Element) -> "List[ExternalProtoLibrary]":
    """Parse Bazel http_archive rule into ExternalProtoLibrary objects."""
    result = []
    for xml_http_archive in xml_tree:
        if (
            xml_http_archive.tag != "rule"
            or xml_http_archive.attrib["class"] != "http_archive"
        ):
            continue

        http_archive = dict()
        for xml_node in xml_http_archive:
            if xml_node.attrib["name"] == "name":
                http_archive["name"] = xml_node.attrib["value"]
            if xml_node.attrib["name"] == "urls":
                http_archive["urls"] = []
                for url_node in xml_node:
                    http_archive["urls"].append(url_node.attrib["value"])
            if xml_node.attrib["name"] == "url":
                http_archive["urls"] = [xml_node.attrib["value"]]
            if xml_node.attrib["name"] == "sha256":
                http_archive["hash"] = xml_node.attrib["value"]
            if xml_node.attrib["name"] == "strip_prefix":
                http_archive["strip_prefix"] = xml_node.attrib["value"]
        if http_archive["name"] not in EXTERNAL_PROTO_LIBRARIES:

            continue
        lib = EXTERNAL_PROTO_LIBRARIES[http_archive["name"]]
        lib.urls = http_archive["urls"]
        lib.hash = http_archive["hash"]
        lib.strip_prefix = http_archive["strip_prefix"]
        result.append(lib)
    return result

def _generate_external_proto_libraries() -> List[Dict[str, Any]]:
    """Generates the build metadata for external proto libraries"""
    xml_tree = _bazel_query_xml_tree("kind(http_archive, //external:*)")
    libraries = _parse_http_archives(xml_tree)
    libraries.sort(key=lambda x: x.destination)
    return list(map(lambda x: x.__dict__, libraries))

def _detect_and_print_issues(build_yaml_like: BuildYaml) -> None:
    """Try detecting some unusual situations and warn about them."""
    for tgt in build_yaml_like["targets"]:
        if tgt["build"] == "test":
            for src in tgt["src"]:
                if src.startswith("src/") and not src.endswith(".proto"):
                    print(
                        (
                            'source file from under "src/" tree used in test '
                            + tgt["name"]
                            + ": "
                            + src
                        )
                    )

_BUILD_EXTRA_METADATA = {
    "third_party/address_sorting:address_sorting": {
        "language": "c",
        "build": "all",
        "_RENAME": "address_sorting",
    },
    "@com_google_protobuf//upb:base": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_base_lib",
    },
    "@com_google_protobuf//upb/hash:hash": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_hash_lib",
    },
    "@com_google_protobuf//upb:mem": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_mem_lib",
    },
    "@com_google_protobuf//upb/lex:lex": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_lex_lib",
    },
    "@com_google_protobuf//upb:message": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_message_lib",
    },
    "@com_google_protobuf//upb/json:json": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_json_lib",
    },
    "@com_google_protobuf//upb/mini_descriptor:mini_descriptor": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_mini_descriptor_lib",
    },
    "@com_google_protobuf//upb/mini_table:mini_table": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_mini_table_lib",
    },
    "@com_google_protobuf//upb/reflection:reflection": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_reflection_lib",
    },
    "@com_google_protobuf//upb/text:text": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_textformat_lib",
    },
    "@com_google_protobuf//upb/wire:wire": {
        "language": "c",
        "build": "all",
        "_RENAME": "upb_wire_lib",
    },
    "@com_google_protobuf//third_party/utf8_range:utf8_range": {
        "language": "c",
        "build": "all",

        "_RENAME": "utf8_range_lib",
    },
    "@com_googlesource_code_re2//:re2": {
        "language": "c",
        "build": "all",
        "_RENAME": "re2",
    },
    "@com_google_googletest//:gtest": {
        "language": "c",
        "build": "private",
        "_RENAME": "gtest",
    },
    "@zlib//:zlib": {
        "language": "c",
        "zlib": True,
        "build": "private",
        "defaults": "zlib",
        "_RENAME": "z",
    },
    "gpr": {
        "language": "c",
        "build": "all",
    },
    "grpc": {
        "language": "c",
        "build": "all",
        "baselib": True,
        "generate_plugin_registry": True,
    },
    "grpc++": {
        "language": "c++",
        "build": "all",
        "baselib": True,
    },
    "grpc++_alts": {"language": "c++", "build": "all", "baselib": True},
    "grpc++_error_details": {"language": "c++", "build": "all"},
    "grpc++_reflection": {"language": "c++", "build": "all"},
    "grpc_authorization_provider": {"language": "c++", "build": "all"},
    "grpc++_unsecure": {
        "language": "c++",
        "build": "all",
        "baselib": True,
    },
    "grpc_unsecure": {
        "language": "c",
        "build": "all",
        "baselib": True,
        "generate_plugin_registry": True,
    },
    "grpcpp_channelz": {"language": "c++", "build": "all"},
    "grpcpp_otel_plugin": {
        "language": "c++",
        "build": "plugin",
    },
    "grpc++_test": {
        "language": "c++",
        "build": "private",
    },
    "src/compiler:grpc_plugin_support": {
        "language": "c++",
        "build": "protoc",
        "_RENAME": "grpc_plugin_support",
    },
    "src/compiler:grpc_cpp_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_cpp_plugin",
    },
    "src/compiler:grpc_csharp_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_csharp_plugin",
    },
    "src/compiler:grpc_node_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_node_plugin",
    },
    "src/compiler:grpc_objective_c_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_objective_c_plugin",
    },
    "src/compiler:grpc_php_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_php_plugin",
    },
    "src/compiler:grpc_python_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_python_plugin",
    },
    "src/compiler:grpc_ruby_plugin": {
        "language": "c++",
        "build": "protoc",
        "_TYPE": "target",
        "_RENAME": "grpc_ruby_plugin",
    },

    "test/core/test_util:grpc_test_util": {
        "language": "c",
        "build": "private",
        "_RENAME": "grpc_test_util",
    },
    "test/core/test_util:grpc_test_util_unsecure": {
        "language": "c",
        "build": "private",
        "_RENAME": "grpc_test_util_unsecure",
    },

    "test/cpp/util:test_config": {
        "language": "c++",
        "build": "private",
        "_RENAME": "grpc++_test_config",
    },
    "test/cpp/util:test_util": {
        "language": "c++",
        "build": "private",
        "_RENAME": "grpc++_test_util",
    },

    "test/cpp/microbenchmarks:helpers": {
        "language": "c++",
        "build": "test",
        "defaults": "benchmark",
        "_RENAME": "benchmark_helpers",
    },
    "test/cpp/interop:interop_client": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "interop_client",
    },
    "test/cpp/interop:interop_server": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "interop_server",
    },

    "test/cpp/interop:http2_client": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "http2_client",
    },
    "test/cpp/qps:qps_json_driver": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "qps_json_driver",
    },
    "test/cpp/qps:qps_worker": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "qps_worker",
    },
    "test/cpp/util:grpc_cli": {
        "language": "c++",
        "build": "test",
        "run": False,
        "_TYPE": "target",
        "_RENAME": "grpc_cli",
    },

}

_BAZEL_DEPS_QUERIES = [
    'deps("//test/...")',
    'deps("//:all")',
    'deps("//src/compiler/...")',

    'kind(alias, "//third_party:*")',

    'deps(kind("^proto_library", @envoy_api//envoy/...))',

    'deps("@com_google_protobuf//upb:generated_code_support")',
]

bazel_rules = {}
for query in _BAZEL_DEPS_QUERIES:
    bazel_rules.update(
        _extract_rules_from_bazel_xml(_bazel_query_xml_tree(query))
    )

_expand_upb_proto_library_rules(bazel_rules)

_patch_grpc_proto_library_rules(bazel_rules)

_patch_descriptor_upb_proto_library(bazel_rules)

tests = _exclude_unwanted_cc_tests(_extract_cc_tests(bazel_rules))

all_extra_metadata = {}
all_extra_metadata.update(
    _generate_build_extra_metadata_for_tests(tests, bazel_rules)
)
all_extra_metadata.update(_BUILD_EXTRA_METADATA)

_populate_transitive_metadata(bazel_rules, list(all_extra_metadata.keys()))

update_test_metadata_with_transitive_metadata(all_extra_metadata, bazel_rules)

all_targets_dict = _generate_build_metadata(all_extra_metadata, bazel_rules)

build_yaml_like = _convert_to_build_yaml_like(all_targets_dict)

build_yaml_like[
    "external_proto_libraries"
] = _generate_external_proto_libraries()

_detect_and_print_issues(build_yaml_like)

build_yaml_string = build_cleaner.cleaned_build_yaml_dict_as_string(
    build_yaml_like
)
with open("build_autogenerated.yaml", "w") as file:
    file.write(build_yaml_string)
