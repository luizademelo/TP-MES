# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""
Includes fuzzer rules.

Now that we are at C++17, please prefer grpc_fuzz_test over the
grpc_fuzzer/grpc_proto_fuzzer older rules for new fuzzers - the former is
simpler and better maintained, and we'll eventually replace existing fuzzers
with grpc_fuzz_test.
"""

load("//bazel:grpc_build_system.bzl", "grpc_cc_test")

def grpc_fuzz_test(name, srcs = [], deps = [], shard_count = None, tags = [], data = [], external_deps = []):
    """Instantiates a fuzztest based test.

    This is the preferred method of writing fuzzers.

    Args:
        name: The name of the test.
        srcs: The source files for the test.
        deps: The dependencies of the test.
        shard_count: The shard count.
        tags: The tags for the test.
        data: The data for the test.
        external_deps: External deps.
    """
    grpc_cc_test(
        name = name,
        srcs = srcs,
        tags = tags + [
            "grpc-fuzzer",
            "grpc-fuzztest",
            "no-cache",
            "no_windows",
            "bazel_only",
        ],
        deps = deps,
        uses_polling = False,
        data = data,
        shard_count = shard_count,
        external_deps = external_deps,
    )
