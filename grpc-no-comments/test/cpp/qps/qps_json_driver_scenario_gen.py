#!/usr/bin/env python3

# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(script_dir)

import scenario_generator_helper as gen

gen.generate_scenarios_bzl(
    gen.generate_qps_json_driver_scenarios(),
    os.path.join(script_dir, "qps_json_driver_scenarios.bzl"),
    "QPS_JSON_DRIVER_SCENARIOS",
)
