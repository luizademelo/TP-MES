# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Generates and compiles Python gRPC stubs from proto_library rules."""

load("@com_google_protobuf//bazel:py_proto_library.bzl", protobuf_py_proto_library = "py_proto_library")
load("@rules_proto//proto:defs.bzl", "ProtoInfo")
load("@rules_python//python:py_info.bzl", "PyInfo")
load(
    "//bazel:protobuf.bzl",
    "declare_out_files",
    "get_include_directory",
    "get_out_dir",
    "get_plugin_args",
    "get_proto_arguments",
    "get_staged_proto_file",
    "includes_from_deps",
    "is_well_known",
    "protos_from_context",
)

_VIRTUAL_IMPORTS = "/_virtual_imports/"
_GENERATED_PROTO_FORMAT = "{}_pb2.py"
_GENERATED_PROTO_STUB_FORMAT = "{}_pb2.pyi"
_GENERATED_GRPC_PROTO_FORMAT = "{}_pb2_grpc.py"

PyProtoInfo = provider(
    "The Python outputs from the Protobuf compiler.",
    fields = {
        "py_info": "A PyInfo provider for the generated code.",
        "generated_py_srcs": "The direct (not transitive) generated Python source files.",
    },
)

def _merge_pyinfos(pyinfos):
    return PyInfo(
        transitive_sources = depset(transitive = [p.transitive_sources for p in pyinfos]),
        imports = depset(transitive = [p.imports for p in pyinfos]),
    )

def _gen_py_aspect_impl(target, context):

    if is_well_known(str(context.label)):
        return [
            PyProtoInfo(
                py_info = context.attr._protobuf_library[PyInfo],
                generated_py_srcs = [],
            ),
        ]

    protos = []
    for p in target[ProtoInfo].direct_sources:
        protos.append(get_staged_proto_file(target.label, context, p))

    includes = depset(direct = protos, transitive = [target[ProtoInfo].transitive_imports])
    out_files = (declare_out_files(protos, context, _GENERATED_PROTO_FORMAT) +
                 declare_out_files(protos, context, _GENERATED_PROTO_STUB_FORMAT))
    generated_py_srcs = out_files

    tools = [context.executable._protoc]

    out_dir = get_out_dir(protos, context)

    arguments = ([
        "--python_out={}".format(out_dir.path),
        "--pyi_out={}".format(out_dir.path),
    ] + [
        "--proto_path={}".format(get_include_directory(i))
        for i in includes.to_list()
    ] + [
        "--proto_path={}".format(context.genfiles_dir.path),
    ])

    arguments += get_proto_arguments(protos, context.genfiles_dir.path)

    context.actions.run(
        inputs = protos + includes.to_list(),
        tools = tools,
        outputs = out_files,
        executable = context.executable._protoc,
        arguments = arguments,
        mnemonic = "ProtocInvocation",
    )

    imports = []
    if out_dir.import_path:
        imports.append("{}/{}".format(context.workspace_name, out_dir.import_path))

    py_info = PyInfo(transitive_sources = depset(direct = out_files), imports = depset(direct = imports))
    return PyProtoInfo(
        py_info = _merge_pyinfos(
            [
                py_info,
                context.attr._protobuf_library[PyInfo],
            ] + [dep[PyProtoInfo].py_info for dep in context.rule.attr.deps],
        ),
        generated_py_srcs = generated_py_srcs,
    )

_gen_py_aspect = aspect(
    implementation = _gen_py_aspect_impl,
    attr_aspects = ["deps"],
    fragments = ["py"],
    attrs = {
        "_protoc": attr.label(
            default = Label("@com_google_protobuf//:protoc"),
            executable = True,
            cfg = "exec",
        ),
        "_protobuf_library": attr.label(
            default = Label("@com_google_protobuf//:protobuf_python"),
            providers = [PyInfo],
        ),
    },
)

def _generate_py_impl(context):
    if (len(context.attr.deps) != 1):
        fail("Can only compile a single proto at a time.")

    py_sources = []

    if context.label.package != context.attr.deps[0].label.package:
        for py_src in context.attr.deps[0][PyProtoInfo].generated_py_srcs:
            reimport_py_file = context.actions.declare_file(py_src.basename)
            py_sources.append(reimport_py_file)
            import_line = "from %s import *" % py_src.short_path.replace("..", "external").replace("/", ".")[:-len(".py")]
            context.actions.write(reimport_py_file, import_line)

    imports = [context.label.package + "/" + i for i in context.attr.imports]
    py_info = PyInfo(transitive_sources = depset(direct = py_sources), imports = depset(direct = imports))
    out_pyinfo = _merge_pyinfos([py_info, context.attr.deps[0][PyProtoInfo].py_info])

    runfiles = context.runfiles(files = out_pyinfo.transitive_sources.to_list()).merge(context.attr._protobuf_library[DefaultInfo].data_runfiles)
    return [
        DefaultInfo(
            files = out_pyinfo.transitive_sources,
            runfiles = runfiles,
        ),
        out_pyinfo,
    ]

_py_proto_library = rule(
    attrs = {
        "deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [ProtoInfo],
            aspects = [_gen_py_aspect],
        ),
        "_protoc": attr.label(
            default = Label("@com_google_protobuf//:protoc"),
            executable = True,
            cfg = "exec",
        ),
        "_protobuf_library": attr.label(
            default = Label("@com_google_protobuf//:protobuf_python"),
            providers = [PyInfo],
        ),
        "imports": attr.string_list(),
    },
    implementation = _generate_py_impl,
)

def py_proto_library(name, deps, use_protobuf = True, **kwargs):
    """Use `py_proto_library` to generate Python libraries from `.proto` files.

    Args:
      name: The name of the target.
      deps: A single proto_library target.
      use_protobuf: Whether to use protobuf implementation of py_proto_library.
      **kwargs: Additional arguments to be supplied to the invocation of
        py_library.
    """
    if use_protobuf:

        filtered_kwargs = {k: v for k, v in kwargs.items() if k != "imports"}
        protobuf_py_proto_library(name = name, deps = deps, **filtered_kwargs)
    else:
        filtered_kwargs = kwargs
        _py_proto_library(name = name, deps = deps, **filtered_kwargs)

def _generate_pb2_grpc_src_impl(context):
    protos = protos_from_context(context)
    includes = includes_from_deps(context.attr.deps)

    out_files = declare_out_files(protos, context, _GENERATED_GRPC_PROTO_FORMAT)
    plugin_flags = ["grpc_2_0"] + context.attr.strip_prefixes

    arguments = []
    tools = [context.executable._protoc, context.executable._grpc_plugin]
    out_dir = get_out_dir(protos, context)
    if out_dir.import_path:

        out_path = get_include_directory(out_files[0])
    else:
        out_path = out_dir.path
    arguments += get_plugin_args(
        context.executable._grpc_plugin,
        plugin_flags,
        out_path,
        False,
    )

    arguments += [
        "--proto_path={}".format(get_include_directory(i))
        for i in includes
    ]
    arguments.append("--proto_path={}".format(context.genfiles_dir.path))
    arguments += get_proto_arguments(protos, context.genfiles_dir.path)
    context.actions.run(
        inputs = protos + includes,
        tools = tools,
        outputs = out_files,
        executable = context.executable._protoc,
        arguments = arguments,
        mnemonic = "ProtocInvocation",
    )

    imports = []

    if _VIRTUAL_IMPORTS in out_path:
        import_path = out_path

        if out_path.startswith(context.genfiles_dir.path):
            import_path = import_path[len(context.genfiles_dir.path) + 1:]

        import_path = "{}/{}".format(context.workspace_name, import_path)
        imports.append(import_path)

    p = PyInfo(transitive_sources = depset(direct = out_files), imports = depset(direct = imports))
    py_info = _merge_pyinfos(
        [
            p,
            context.attr.grpc_library[PyInfo],
        ] + [dep[PyInfo] for dep in context.attr.py_deps],
    )

    runfiles = context.runfiles(files = out_files, transitive_files = py_info.transitive_sources).merge(context.attr.grpc_library[DefaultInfo].data_runfiles)

    return [
        DefaultInfo(
            files = depset(direct = out_files),
            runfiles = runfiles,
        ),
        py_info,
    ]

_generate_pb2_grpc_src = rule(
    attrs = {
        "deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [ProtoInfo],
        ),
        "py_deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [PyInfo],
        ),
        "strip_prefixes": attr.string_list(),
        "_grpc_plugin": attr.label(
            executable = True,
            cfg = "exec",
            default = Label("//src/compiler:grpc_python_plugin"),
        ),
        "_protoc": attr.label(
            executable = True,
            cfg = "exec",
            default = Label("@com_google_protobuf//:protoc"),
        ),
        "grpc_library": attr.label(
            default = Label("//src/python/grpcio/grpc:grpcio"),
            providers = [PyInfo],
        ),
    },
    implementation = _generate_pb2_grpc_src_impl,
)

def py_grpc_library(
        name,
        srcs,
        deps,
        strip_prefixes = [],
        grpc_library = Label("//src/python/grpcio/grpc:grpcio"),
        **kwargs):
    """Generate python code for gRPC services defined in a protobuf.

    Args:
      name: The name of the target.
      srcs: (List of `labels`) a single proto_library target containing the
        schema of the service.
      deps: (List of `labels`) a single py_proto_library target for the
        proto_library in `srcs`.
      strip_prefixes: (List of `strings`) If provided, this prefix will be
        stripped from the beginning of foo_pb2 modules imported by the
        generated stubs. This is useful in combination with the `imports`
        attribute of the `py_library` rule.
      grpc_library: (`label`) a single `py_library` target representing the
        python gRPC library target to be depended upon. This can be used to
        generate code that depends on `grpcio` from the Python Package Index.
      **kwargs: Additional arguments to be supplied to the invocation of
        py_library.
    """
    if len(srcs) != 1:
        fail("Can only compile a single proto at a time.")

    if len(deps) != 1:
        fail("Deps must have length 1.")

    _generate_pb2_grpc_src(
        name = name,
        deps = srcs,
        py_deps = deps,
        strip_prefixes = strip_prefixes,
        grpc_library = grpc_library,
        **kwargs
    )
