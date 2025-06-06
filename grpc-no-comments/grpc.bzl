# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""
Bazel macros to declare gRPC libraries automatically generated from proto files.

This file declares two macros:
- objc_proto_library
- objc_grpc_library
"""

def _lower_underscore_to_upper_camel(str):
    humps = []
    for hump in str.split("_"):
        humps.append(hump[0].upper() + hump[1:])
    return "".join(humps)

def _file_to_upper_camel(src):
    elements = src.rpartition("/")
    upper_camel = _lower_underscore_to_upper_camel(elements[-1])
    return "".join(elements[:-1] + [upper_camel])

def _file_with_extension(src, ext):
    elements = src.rpartition("/")
    basename = elements[-1].partition(".")[0]
    return "".join(elements[:-1] + [basename, ext])

def _protoc_invocation(srcs, flags):
    """Returns a CLI command to invoke protoc.

    Uses the given sources and flags. Suitable for use in a genrule.
    """
    protoc_command = "$(location //external:protoc) -I . "
    srcs_params = ""
    for src in srcs:
        srcs_params += " $(location %s)" % (src)
    return protoc_command + flags + srcs_params

def objc_proto_library(name, srcs, visibility = None):
    """Declares an objc_library for the code generated by protoc.

    Uses the given proto sources. This generated code doesn't include proto
    services.

    Args:
      name: The name of the library.
      srcs: A list of .proto file sources.
      visibility: The visibility label to apply to the target.
    """
    h_files = []
    m_files = []
    for src in srcs:
        src = _file_to_upper_camel(src)
        h_files.append(_file_with_extension(src, ".pbobjc.h"))
        m_files.append(_file_with_extension(src, ".pbobjc.m"))

    protoc_flags = "--objc_out=$(GENDIR)"

    native.genrule(
        name = name + "_codegen",
        srcs = srcs + ["//external:protoc"],
        outs = h_files + m_files,
        cmd = _protoc_invocation(srcs, protoc_flags),
    )
    native.objc_library(
        name = name,
        hdrs = h_files,
        includes = ["."],
        non_arc_srcs = m_files,
        deps = ["//external:protobuf_objc"],
        visibility = visibility,
    )

def objc_grpc_library(name, services, other_messages, visibility = None):
    """Declares an objc_library for the code generated by the gRPC ObjC plugin.

    The generated code does not include the services of the files in other_messages.

    Args:
      name: The name of the library.
      services: The .proto files from which to generate the library.
      other_messages: A list of .proto files containing messages needed for the library.
      visibility: The visibility label to apply to the library.
    """
    objc_proto_library(name + "_messages", services + other_messages)

    h_files = []
    m_files = []
    for src in services:
        src = _file_to_upper_camel(src)
        h_files.append(_file_with_extension(src, ".pbrpc.h"))
        m_files.append(_file_with_extension(src, ".pbrpc.m"))

    protoc_flags = ("--grpc_out=$(GENDIR) --plugin=" +
                    "protoc-gen-grpc=$(location //external:grpc_protoc_plugin_objc)")

    native.genrule(
        name = name + "_codegen",
        srcs = services + [
            "//external:grpc_protoc_plugin_objc",
            "//external:protoc",
        ],
        outs = h_files + m_files,
        cmd = _protoc_invocation(services, protoc_flags),
    )
    native.objc_library(
        name = name,
        hdrs = h_files,
        includes = ["."],
        srcs = m_files,
        deps = [
            ":" + name + "_messages",
            "//external:proto_objc_rpc",
        ],
        visibility = visibility,
    )
