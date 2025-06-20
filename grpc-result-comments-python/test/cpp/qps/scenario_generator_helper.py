Here's the commented version of the code:

```python
#!/usr/bin/env python3

# Copyright 2021 The gRPC Authors
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function

import json
import os
import sys

import yaml

# Set up path to import run_tests tools
run_tests_root = os.path.abspath(
    os.path.join(os.path.dirname(sys.argv[0]), "../../../tools/run_tests")
)
sys.path.append(run_tests_root)

import performance.scenario_config as scenario_config

# Copyright notice template to be included in generated files
_COPYRIGHT = """# Copyright 2021 The gRPC Authors
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
"""

def _mutate_scenario(scenario_json):
    """Modifies vanilla benchmark scenario config to make it more suitable for running as a unit test.
    
    Args:
        scenario_json: Original benchmark scenario configuration in JSON format
        
    Returns:
        Modified scenario configuration optimized for unit testing:
        - Reduced warmup and benchmark durations
        - Adjusted outstanding RPCs based on client/server type
        - Limited client channels for streaming scenarios
        - Removes non-protobuf fields
    """
    scenario_json = dict(scenario_json)
    # Set very short durations for unit testing
    scenario_json["warmup_seconds"] = 0
    scenario_json["benchmark_seconds"] = 1
    
    # Reduce outstanding RPCs for synchronous clients/servers
    outstanding_rpcs_divisor = 1
    if (
        scenario_json["client_config"]["client_type"] == "SYNC_CLIENT"
        or scenario_json["server_config"]["server_type"] == "SYNC_SERVER"
    ):
        outstanding_rpcs_divisor = 10
        
    scenario_json["client_config"]["outstanding_rpcs_per_channel"] = max(
        1,
        scenario_json["client_config"]["outstanding_rpcs_per_channel"]
        // outstanding_rpcs_divisor,
    )

    # Limit client channels, especially for streaming scenarios
    max_client_channels = 16
    if scenario_json["client_config"]["rpc_type"] == "STREAMING_FROM_SERVER":
        max_client_channels = 4

    scenario_json["client_config"]["client_channels"] = min(
        max_client_channels, scenario_json["client_config"]["client_channels"]
    )

    return scenario_config.remove_nonproto_fields(scenario_json)

def generate_json_run_localhost_scenarios():
    """Generates test scenarios for localhost runs.
    
    Returns:
        List of modified scenarios that are marked as 'scalable' in their categories
    """
    return [
        _mutate_scenario(scenario_json)
        for scenario_json in scenario_config.CXXLanguage().scenarios()
        if "scalable" in scenario_json.get("CATEGORIES", [])
    ]

def generate_qps_json_driver_scenarios():
    """Generates test scenarios for in-process QPS driver.
    
    Returns:
        List of modified scenarios that are marked as 'inproc' in their categories
    """
    return [
        _mutate_scenario(scenario_json)
        for scenario_json in scenario_config.CXXLanguage().scenarios()
        if "inproc" in scenario_json.get("CATEGORIES", [])
    ]

def generate_scenarios_bzl(json_scenarios, bzl_filename, bzl_variablename):
    """Generate .bzl file that defines a variable with JSON scenario configs.
    
    Args:
        json_scenarios: List of scenario configurations in JSON format
        bzl_filename: Output filename for the generated .bzl file
        bzl_variablename: Name of the variable to define in the .bzl file
    """
    all_scenarios = []
    for scenario in json_scenarios:
        scenario_name = scenario["name"]
        
        # Prepare scenario JSON string with proper escaping
        scenarios_json_arg_str = "\\'%s\\'" % json.dumps(
            {"scenarios": [scenario]}
        )
        all_scenarios.append((scenario_name, scenarios_json_arg_str))

    # Write the generated .bzl file
    with open(bzl_filename, "w") as f:
        f.write(_COPYRIGHT)
        f.write(
            '"""AUTOGENERATED: configuration of benchmark scenarios to be run'
            ' as bazel test"""\n\n'
        )
        f.write("%s = {\n" % bzl_variablename)
        for scenario in all_scenarios:
            f.write("    \"%s\": '%s',\n" % (scenario[0], scenario[1]))
        f.write("}\n")
```