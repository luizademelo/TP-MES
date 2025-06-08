Here's the commented version of the code:

```python
#!/usr/bin/env python2.7
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Generates the appropriate build.json data for all the naming tests."""

import collections
import hashlib
import json

import yaml

# Default local DNS server address for testing
_LOCAL_DNS_SERVER_ADDRESS = "127.0.0.1:15353"

def _append_zone_name(name, zone_name):
    """Appends zone name to a given DNS name.
    
    Args:
        name: The base DNS name to extend
        zone_name: The zone name to append
        
    Returns:
        string: The combined name in 'name.zone' format
    """
    return "%s.%s" % (name, zone_name)

def _build_expected_addrs_cmd_arg(expected_addrs):
    """Formats expected addresses into a command-line argument string.
    
    Args:
        expected_addrs: List of address dictionaries containing 'address' 
                       and 'is_balancer' fields
                       
    Returns:
        string: Semicolon-separated list of 'address,is_balancer' pairs
    """
    out = []
    for addr in expected_addrs:
        out.append("%s,%s" % (addr["address"], str(addr["is_balancer"])))
    return ";".join(out)

def _resolver_test_cases(resolver_component_data):
    """Generates test case data from resolver component configuration.
    
    Processes the resolver test cases from YAML data and formats them into
    a dictionary structure suitable for JSON output.
    
    Args:
        resolver_component_data: Dictionary containing resolver test configuration
                                from YAML file
                                
    Returns:
        list: List of test case dictionaries with formatted arguments
    """
    out = []
    for test_case in resolver_component_data["resolver_component_tests"]:
        # Create fully qualified domain name by appending common zone
        target_name = _append_zone_name(
            test_case["record_to_resolve"],
            resolver_component_data["resolver_tests_common_zone_name"],
        )
        out.append(
            {
                "test_title": target_name,
                "arg_names_and_values": [
                    ("target_name", target_name),
                    (
                        "do_ordered_address_comparison",
                        test_case["do_ordered_address_comparison"],
                    ),
                    (
                        "expected_addrs",
                        _build_expected_addrs_cmd_arg(
                            test_case["expected_addrs"]
                        ),
                    ),
                    (
                        "expected_chosen_service_config",
                        (test_case["expected_chosen_service_config"] or ""),
                    ),
                    (
                        "expected_service_config_error",
                        (test_case["expected_service_config_error"] or ""),
                    ),
                    (
                        "expected_lb_policy",
                        (test_case["expected_lb_policy"] or ""),
                    ),
                    ("enable_srv_queries", test_case["enable_srv_queries"]),
                    ("enable_txt_queries", test_case["enable_txt_queries"]),
                    (
                        "inject_broken_nameserver_list",
                        test_case["inject_broken_nameserver_list"],
                    ),
                ],
            }
        )
    return out

def main():
    """Main function that loads YAML test data and generates JSON output.
    
    Reads resolver test configuration from YAML file, processes it through
    _resolver_test_cases(), and outputs the result as YAML format.
    """
    resolver_component_data = ""
    with open("test/cpp/naming/resolver_test_record_groups.yaml") as f:
        resolver_component_data = yaml.safe_load(f)

    # Construct the output JSON structure
    json = {
        "resolver_tests_common_zone_name": resolver_component_data[
            "resolver_tests_common_zone_name"
        ],

        "resolver_component_test_cases": _resolver_test_cases(
            resolver_component_data
        ),
    }

    print(yaml.safe_dump(json))

if __name__ == "__main__":
    main()
```

Key improvements made in the comments:
1. Added module-level docstring explaining the script's purpose
2. Added detailed function docstrings explaining purpose, arguments, and return values
3. Added comments for important constants
4. Added comments explaining complex logic and data transformations
5. Added docstring for the main() function
6. Maintained consistent comment style throughout
7. Added explanations for non-obvious code segments

The comments now provide comprehensive documentation while maintaining readability and avoiding redundancy.