# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""Script to run qps benchmark."""

load("//bazel:grpc_build_system.bzl", "grpc_cc_test")
load("//test/cpp/qps:json_run_localhost_scenarios.bzl", "JSON_RUN_LOCALHOST_SCENARIOS")
load("//test/cpp/qps:qps_json_driver_scenarios.bzl", "QPS_JSON_DRIVER_SCENARIOS")

def add_suffix(name):

    m = len(name) - (87 - len("//test/cpp/qps:"))
    if m >= 0 and m <= 3:
        return name + "_" * (4 - m)
    else:
        return name

def qps_json_driver_batch():
    for scenario in QPS_JSON_DRIVER_SCENARIOS:
        grpc_cc_test(
            name = add_suffix("qps_json_driver_test_%s" % scenario),
            srcs = ["qps_json_driver.cc"],
            args = [
                "--run_inproc",
                "--scenarios_json",
                QPS_JSON_DRIVER_SCENARIOS[scenario],
            ],
            deps = [
                ":benchmark_config",
                ":driver_impl",
                "//:grpc++",
                "//test/cpp/util:test_config",
                "//test/cpp/util:test_util",
            ],
            external_deps = [
                "absl/log:check",
            ],
            tags = [
                "qps_json_driver",
                "no_mac",
                "nomsan",
                "noubsan",
            ],

            flaky = True,
        )

def json_run_localhost_batch():
    for scenario in JSON_RUN_LOCALHOST_SCENARIOS:
        grpc_cc_test(
            name = add_suffix("json_run_localhost_%s" % scenario),
            srcs = ["json_run_localhost.cc"],
            args = [
                "--scenarios_json",
                JSON_RUN_LOCALHOST_SCENARIOS[scenario],
            ],
            data = [
                "//test/cpp/qps:qps_json_driver",
                "//test/cpp/qps:qps_worker",
            ],
            external_deps = [
                "absl/log:check",
            ],
            deps = [
                "//:gpr",
                "//test/core/test_util:grpc_test_util",
                "//test/cpp/util:test_config",
                "//test/cpp/util:test_util",
            ],
            tags = [
                "json_run_localhost",
                "no_windows",
                "no_mac",
                "nomsan",
                "notsan",
                "noubsan",
            ],

            flaky = True,
        )
