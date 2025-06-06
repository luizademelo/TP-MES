#!/usr/bin/env python3

# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""
Generate experiment related code artifacts.

Invoke as: tools/codegen/core/gen_experiments.py
Experiment definitions are in src/core/lib/experiments/experiments.yaml
"""

from __future__ import print_function

import argparse
import os
import sys

import experiments_compiler as exp
import yaml

REPO_ROOT = os.path.normpath(
    os.path.join(os.path.dirname(__file__), "../../..")
)
print(REPO_ROOT)
os.chdir(REPO_ROOT)

DEFAULTS = {
    "broken": "false",
    False: "false",
    True: "true",
    "debug": "kDefaultForDebugOnly",
}

PLATFORMS_DEFINE = {
    "windows": "GPR_WINDOWS",
    "ios": "GRPC_CFSTREAM",
    "posix": "",
}

FINAL_RETURN = {
    "broken": "return false;",
    False: "return false;",
    True: "return true;",
    "debug": "\n#ifdef NDEBUG\nreturn false;\n#else\nreturn true;\n#endif\n",
}

FINAL_DEFINE = {
    "broken": None,
    False: None,
    True: "#define %s",
    "debug": "#ifndef NDEBUG\n#define %s\n#endif",
}

BZL_LIST_FOR_DEFAULTS = {
    "broken": None,
    False: "off",
    True: "on",
    "debug": "dbg",
}

def ParseCommandLineArguments(args):
    """Wrapper for argparse command line arguments handling.

    Args:
    args: List of command line arguments.

    Returns:
    Command line arguments namespace built by argparse.ArgumentParser().
    """

    flag_parser = argparse.ArgumentParser()
    flag_parser.add_argument(
        "--check",
        action="store_false",
        help="If specified, disables checking experiment expiry dates",
    )
    flag_parser.add_argument(
        "--no_dbg_experiments",
        action="store_true",
        help="Prohibit 'debug' configurations",
        default=False,
    )
    return flag_parser.parse_args(args)

args = ParseCommandLineArguments(sys.argv[1:])

def _InjectGithubPath(path):
    base, ext = os.path.splitext(path)
    return base + ".github" + ext

def _GenerateExperimentFiles(args, mode):
    if mode == "test":
        _EXPERIMENTS_DEFS = (
            "test/core/experiments/fixtures/test_experiments.yaml"
        )
        _EXPERIMENTS_ROLLOUTS = (
            "test/core/experiments/fixtures/test_experiments_rollout.yaml"
        )
        _EXPERIMENTS_HDR_FILE = "test/core/experiments/fixtures/experiments.h"
        _EXPERIMENTS_SRC_FILE = "test/core/experiments/fixtures/experiments.cc"
        _EXPERIMENTS_BZL_FILE = "bazel/test_experiments.bzl"
    else:
        _EXPERIMENTS_DEFS = "src/core/lib/experiments/experiments.yaml"
        _EXPERIMENTS_ROLLOUTS = "src/core/lib/experiments/rollouts.yaml"
        _EXPERIMENTS_HDR_FILE = "src/core/lib/experiments/experiments.h"
        _EXPERIMENTS_SRC_FILE = "src/core/lib/experiments/experiments.cc"
        _EXPERIMENTS_BZL_FILE = "bazel/experiments.bzl"
        if "/google3/" in REPO_ROOT:
            _EXPERIMENTS_ROLLOUTS = _InjectGithubPath(_EXPERIMENTS_ROLLOUTS)
            _EXPERIMENTS_HDR_FILE = _InjectGithubPath(_EXPERIMENTS_HDR_FILE)
            _EXPERIMENTS_SRC_FILE = _InjectGithubPath(_EXPERIMENTS_SRC_FILE)
            _EXPERIMENTS_BZL_FILE = _InjectGithubPath(_EXPERIMENTS_BZL_FILE)

    with open(_EXPERIMENTS_DEFS) as f:
        attrs = yaml.safe_load(f.read())

    if not exp.AreExperimentsOrdered(attrs):
        print("Experiments are not ordered")
        sys.exit(1)

    with open(_EXPERIMENTS_ROLLOUTS) as f:
        rollouts = yaml.safe_load(f.read())

    if not exp.AreExperimentsOrdered(rollouts):
        print("Rollouts are not ordered")
        sys.exit(1)

    compiler = exp.ExperimentsCompiler(
        DEFAULTS,
        FINAL_RETURN,
        FINAL_DEFINE,
        PLATFORMS_DEFINE,
        BZL_LIST_FOR_DEFAULTS,
    )

    experiment_annotation = "gRPC Experiments: "
    for attr in attrs:
        exp_definition = exp.ExperimentDefinition(attr)
        if not exp_definition.IsValid(args.check):
            sys.exit(1)
        experiment_annotation += exp_definition.name + ":0,"
        if not compiler.AddExperimentDefinition(exp_definition):
            print("Experiment = %s ERROR adding" % exp_definition.name)
            sys.exit(1)

    if len(experiment_annotation) > 2000:
        print("comma-delimited string of experiments is too long")
        sys.exit(1)

    for rollout_attr in rollouts:
        if not compiler.AddRolloutSpecification(rollout_attr):
            print("ERROR adding rollout spec")
            sys.exit(1)

    if mode != "test" and args.no_dbg_experiments:
        print("Ensuring no debug experiments are configured")
        compiler.EnsureNoDebugExperiments()

    print(f"Mode = {mode} Generating experiments headers")
    compiler.GenerateExperimentsHdr(_EXPERIMENTS_HDR_FILE, mode)

    print(f"Mode = {mode} Generating experiments srcs")
    compiler.GenerateExperimentsSrc(
        _EXPERIMENTS_SRC_FILE, _EXPERIMENTS_HDR_FILE, mode
    )

    print("Generating experiments.bzl")
    compiler.GenExperimentsBzl(mode, _EXPERIMENTS_BZL_FILE)
    if mode == "test":
        print("Generating experiments tests")
        compiler.GenTest(
            os.path.join(REPO_ROOT, "test/core/experiments/experiments_test.cc")
        )

_GenerateExperimentFiles(args, "production")
_GenerateExperimentFiles(args, "test")
