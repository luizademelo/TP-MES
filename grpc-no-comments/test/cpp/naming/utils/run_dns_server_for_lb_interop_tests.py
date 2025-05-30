#!/usr/bin/env python3
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import os
import signal
import subprocess
import sys
import tempfile
import time

import yaml

argp = argparse.ArgumentParser(
    description="Runs a DNS server for LB interop tests"
)
argp.add_argument(
    "-l",
    "--grpclb_ips",
    default=None,
    type=str,
    help="Comma-separated list of IP addresses of balancers",
)
argp.add_argument(
    "-f",
    "--fallback_ips",
    default=None,
    type=str,
    help="Comma-separated list of IP addresses of fallback servers",
)
argp.add_argument(
    "-c",
    "--cause_no_error_no_data_for_balancer_a_record",
    default=False,
    action="store_const",
    const=True,
    help=(
        "Used for testing the case in which the grpclb "
        "balancer A record lookup results in a DNS NOERROR response "
        "but with no ANSWER section i.e. no addresses"
    ),
)
args = argp.parse_args()

balancer_records = []
grpclb_ips = args.grpclb_ips.split(",")
if grpclb_ips[0]:
    for ip in grpclb_ips:
        balancer_records.append(
            {
                "TTL": "2100",
                "data": ip,
                "type": "A",
            }
        )
fallback_records = []
fallback_ips = args.fallback_ips.split(",")
if fallback_ips[0]:
    for ip in fallback_ips:
        fallback_records.append(
            {
                "TTL": "2100",
                "data": ip,
                "type": "A",
            }
        )
records_config_yaml = {
    "resolver_tests_common_zone_name": "test.google.fr.",
    "resolver_component_tests": [
        {
            "records": {
                "_grpclb._tcp.server": [
                    {
                        "TTL": "2100",
                        "data": "0 0 12000 balancer",
                        "type": "SRV",
                    },
                ],
                "balancer": balancer_records,
                "server": fallback_records,
            }
        }
    ],
}
if args.cause_no_error_no_data_for_balancer_a_record:
    balancer_records = records_config_yaml["resolver_component_tests"][0][
        "records"
    ]["balancer"]
    assert not balancer_records

    balancer_records.append(
        {
            "TTL": "2100",
            "data": "arbitrary string that wont actually be resolved",
            "type": "TXT",
        }
    )

records_config_path = tempfile.mktemp()
with open(records_config_path, "w") as records_config_generated:
    records_config_generated.write(yaml.dump(records_config_yaml))

with open(records_config_path, "r") as records_config_generated:
    sys.stderr.write("===== DNS server records config: =====\n")
    sys.stderr.write(records_config_generated.read())
    sys.stderr.write("======================================\n")

subprocess.check_output(
    [
        "/var/local/git/grpc/test/cpp/naming/utils/dns_server.py",
        "--port=53",
        "--records_config_path",
        records_config_path,
        "--add_a_record=metadata.google.internal:169.254.169.254",
    ]
)
