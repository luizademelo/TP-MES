#!/usr/bin/env python3

# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import ast
import os
import re
import subprocess
import sys

os.chdir(os.path.join(os.path.dirname(sys.argv[0]), "../../.."))

git_hash_pattern = re.compile("[0-9a-f]{40}")

git_submodules = (
    subprocess.check_output("git submodule", shell=True)
    .decode()
    .strip()
    .split("\n")
)
git_submodule_hashes = {
    re.search(git_hash_pattern, s).group() for s in git_submodules
}

_BAZEL_SKYLIB_DEP_NAME = "bazel_skylib"
_BAZEL_TOOLCHAINS_DEP_NAME = "bazel_toolchains"
_BAZEL_COMPDB_DEP_NAME = "bazel_compdb"

_GRPC_DEP_NAMES = [
    "platforms",
    "boringssl",
    "zlib",
    "com_google_protobuf",
    "com_google_googletest",
    "rules_cc",
    "com_github_google_benchmark",
    "com_github_cares_cares",
    "com_google_absl",
    "com_google_fuzztest",
    "io_opencensus_cpp",
    "io_opentelemetry_cpp",
    "envoy_api",
    _BAZEL_SKYLIB_DEP_NAME,
    _BAZEL_TOOLCHAINS_DEP_NAME,
    _BAZEL_COMPDB_DEP_NAME,
    "bazel_features",
    "rules_proto",
    "io_bazel_rules_go",
    "build_bazel_rules_apple",
    "build_bazel_apple_support",
    "com_googlesource_code_re2",
    "bazel_gazelle",
    "opencensus_proto",
    "com_envoyproxy_protoc_gen_validate",
    "com_google_googleapis",
    "com_google_libprotobuf_mutator",
    "com_github_cncf_xds",
    "google_cloud_cpp",
    "rules_shell",
    "rules_java",
    "yaml-cpp",
]

_GRPC_BAZEL_ONLY_DEPS = [
    "platforms",
    "rules_cc",
    "com_google_absl",
    "com_google_fuzztest",
    "io_opencensus_cpp",
    _BAZEL_SKYLIB_DEP_NAME,
    _BAZEL_TOOLCHAINS_DEP_NAME,
    _BAZEL_COMPDB_DEP_NAME,
    "bazel_features",
    "rules_proto",
    "io_bazel_rules_go",
    "build_bazel_rules_apple",
    "build_bazel_apple_support",
    "com_googlesource_code_re2",
    "bazel_gazelle",
    "opencensus_proto",
    "com_envoyproxy_protoc_gen_validate",
    "com_google_googleapis",
    "com_google_libprotobuf_mutator",
    "google_cloud_cpp",
    "rules_shell",
    "rules_java",
    "yaml-cpp",
]

class BazelEvalState(object):
    def __init__(self, names_and_urls, overridden_name=None):
        self.names_and_urls = names_and_urls
        self.overridden_name = overridden_name

    def http_archive(self, **args):
        self.archive(**args)

    def new_http_archive(self, **args):
        self.archive(**args)

    def bind(self, **args):
        pass

    def existing_rules(self):
        if self.overridden_name:
            return [self.overridden_name]
        return []

    def archive(self, **args):
        assert self.names_and_urls.get(args["name"]) is None
        if args["name"] in _GRPC_BAZEL_ONLY_DEPS:
            self.names_and_urls[args["name"]] = "dont care"
            return
        url = args.get("url", None)
        if not url:

            url = " ".join(args["urls"])
        self.names_and_urls[args["name"]] = url

    def git_repository(self, **args):
        assert self.names_and_urls.get(args["name"]) is None
        if args["name"] in _GRPC_BAZEL_ONLY_DEPS:
            self.names_and_urls[args["name"]] = "dont care"
            return
        self.names_and_urls[args["name"]] = args["remote"]

    def grpc_python_deps(self):
        pass

with open(os.path.join("bazel", "grpc_deps.bzl"), "r") as f:
    names_and_urls = {}
    eval_state = BazelEvalState(names_and_urls)
    bazel_file = f.read()

bazel_file = re.sub(
    r"^grpc_repo_deps_ext.*$", "", bazel_file, flags=re.MULTILINE
)

bazel_file += "\ngrpc_deps()\n"
bazel_file += "\ngrpc_test_only_deps()\n"
build_rules = {
    "native": eval_state,
    "http_archive": lambda **args: eval_state.http_archive(**args),
    "load": lambda a, b: None,
    "git_repository": lambda **args: eval_state.git_repository(**args),
    "grpc_python_deps": lambda: None,
    "Label": lambda a: None,
    "repository_rule": lambda **args: lambda name: None,
}
exec((bazel_file), build_rules)
grpc_dep_names_set = set(_GRPC_DEP_NAMES)
names_set = set(names_and_urls.keys())
if grpc_dep_names_set != names_set:
    print("Differences detected between GRPC_DEP_NAMES and grpc_deps.bzl")
    print("- GRPC_DEP_NAMES only:", grpc_dep_names_set - names_set)
    print("- grpc_deps.bzl only:", names_set - grpc_dep_names_set)
    sys.exit(1)

names_without_bazel_only_deps = list(names_and_urls.keys())
for dep_name in _GRPC_BAZEL_ONLY_DEPS:
    names_without_bazel_only_deps.remove(dep_name)
archive_urls = [names_and_urls[name] for name in names_without_bazel_only_deps]
for url in archive_urls:
    if re.search(git_hash_pattern, url) is None:
        print("Cannot find the hash value from url", url)
        sys.exit(1)
workspace_git_hashes = {
    re.search(git_hash_pattern, url).group() for url in archive_urls
}
if len(workspace_git_hashes) == 0:
    print("(Likely) parse error, did not find any bazel git dependencies.")
    sys.exit(1)

if len(workspace_git_hashes - git_submodule_hashes) > 0:
    print(
        "Found discrepancies between git submodules and Bazel WORKSPACE"
        " dependencies"
    )
    print(("workspace_git_hashes: %s" % workspace_git_hashes))
    print(("git_submodule_hashes: %s" % git_submodule_hashes))
    print(
        "workspace_git_hashes - git_submodule_hashes: %s"
        % (workspace_git_hashes - git_submodule_hashes)
    )
    sys.exit(1)

for name in _GRPC_DEP_NAMES:
    names_and_urls_with_overridden_name = {}
    state = BazelEvalState(
        names_and_urls_with_overridden_name, overridden_name=name
    )
    rules = {
        "native": state,
        "http_archive": lambda **args: state.http_archive(**args),
        "load": lambda a, b: None,
        "git_repository": lambda **args: state.git_repository(**args),
        "grpc_python_deps": lambda *args, **kwargs: None,
        "Label": lambda a: None,
        "repository_rule": lambda **args: lambda name: None,
    }
    exec((bazel_file), rules)
    assert name not in list(names_and_urls_with_overridden_name.keys())

sys.exit(0)
