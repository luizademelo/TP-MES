# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Bazel rule tests of bazel/python_rules.bzl"""

load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("@rules_python//python:py_info.bzl", "PyInfo")

def _assert_in(env, item, container):
    asserts.true(
        env,
        item in container,
        "Expected " + str(item) + " to be in " + str(container),
    )

def _py_proto_library_provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target = analysistest.target_under_test(env)

    files = [file.short_path for file in target.files.to_list()]
    runfiles = [file.short_path for file in target.default_runfiles.files.to_list()]
    py_info_transitive_sources = [
        file.short_path
        for file in target[PyInfo].transitive_sources.to_list()
    ]

    _assert_in(env, "helloworld_pb2.py", files)
    _assert_in(env, "subdir/hello_dep_pb2.py", files)

    _assert_in(env, "helloworld_pb2.py", runfiles)
    _assert_in(env, "subdir/hello_dep_pb2.py", runfiles)

    _assert_in(env, "helloworld_pb2.py", py_info_transitive_sources)
    _assert_in(env, "subdir/hello_dep_pb2.py", py_info_transitive_sources)

    # TODO: Enable after py_proto_library supports outputting .pyi files.

    return analysistest.end(env)

_py_proto_library_provider_contents_test = analysistest.make(_py_proto_library_provider_contents_test_impl)

def python_rules_test_suite(name):
    _py_proto_library_provider_contents_test(
        name = "py_proto_library_provider_contents_test",
        target_under_test = ":helloworld_py_pb2",
    )

    native.test_suite(
        name = name,
        tests = [
            "py_proto_library_provider_contents_test",
        ],
    )
