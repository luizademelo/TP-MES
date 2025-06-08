Here's the commented version of the code:

```c++
#!/usr/bin/env python3
# Copyright 2023 The gRPC Authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import platform
import subprocess
import sys
import time

def test_runner_log(msg):
    """Log a message to stderr with the script filename as prefix.
    
    Args:
        msg: The message to be logged.
    """
    sys.stderr.write("\n%s: %s\n" % (__file__, msg))

def python_args(arg_list):
    """Adjust command arguments for Windows platform if needed.
    
    On Windows, prepend the Python executable path if the first argument
    is a Python script.
    
    Args:
        arg_list: List of command arguments
        
    Returns:
        The adjusted argument list
    """
    if platform.system() == "Windows" and arg_list[0].endswith(".py"):
        return [sys.executable] + arg_list
    return arg_list

def wait_until_dns_server_is_up(args):
    """Wait until DNS server is responsive or timeout after 30 attempts.
    
    Performs health checks by:
    1. Attempting TCP connection to DNS server
    2. If TCP succeeds, making a test DNS query
    3. Checking for expected response in DNS query output
    
    Args:
        args: Command line arguments containing:
            - dns_server_port: Port of DNS server
            - tcp_connect_bin_path: Path to TCP health check utility
            - dns_resolver_bin_path: Path to DNS resolver utility
    
    Exits with code 1 if server doesn't become responsive within timeout.
    """
    for i in range(0, 30):
        test_runner_log(
            "Health check: attempt to connect to DNS server over TCP."
        )
        # Try TCP connection to DNS server
        tcp_connect_subprocess = subprocess.Popen(
            python_args(
                [
                    args.tcp_connect_bin_path,
                    "--server_host",
                    "127.0.0.1",
                    "--server_port",
                    str(args.dns_server_port),
                    "--timeout",
                    str(1),
                ]
            )
        )
        tcp_connect_subprocess.communicate()
        
        # If TCP connection succeeded
        if tcp_connect_subprocess.returncode == 0:
            test_runner_log(
                (
                    "Health check: attempt to make an A-record "
                    "query to DNS server."
                )
            )
            # Try DNS query
            dns_resolver_subprocess = subprocess.Popen(
                python_args(
                    [
                        args.dns_resolver_bin_path,
                        "--qname",
                        "health-check-local-dns-server-is-alive.resolver-tests.grpctestingexp",
                        "--server_host",
                        "127.0.0.1",
                        "--server_port",
                        str(args.dns_server_port),
                    ]
                ),
                stdout=subprocess.PIPE,
            )
            dns_resolver_stdout, _ = dns_resolver_subprocess.communicate(
                str.encode("ascii")
            )
            
            # If DNS query succeeded and contains expected response
            if dns_resolver_subprocess.returncode == 0:
                if "123.123.123.123".encode("ascii") in dns_resolver_stdout:
                    test_runner_log(
                        (
                            "DNS server is up! "
                            "Successfully reached it over UDP and TCP."
                        )
                    )
                return
        time.sleep(1)  # Wait before retrying
        
    # If all attempts failed
    test_runner_log(
        (
            "Failed to reach DNS server over TCP and/or UDP. "
            "Exiting without running tests."
        )
    )
    sys.exit(1)

def main():
    """Main function that parses arguments and checks DNS server availability."""
    argp = argparse.ArgumentParser(description="Make DNS queries for A records")
    argp.add_argument(
        "-p",
        "--dns_server_port",
        default=None,
        type=int,
        help=("Port that local DNS server is listening on."),
    )
    argp.add_argument(
        "--dns_resolver_bin_path",
        default=None,
        type=str,
        help=("Path to the DNS health check utility."),
    )
    argp.add_argument(
        "--tcp_connect_bin_path",
        default=None,
        type=str,
        help=("Path to the TCP health check utility."),
    )
    args = argp.parse_args()
    wait_until_dns_server_is_up(args)

if __name__ == "__main__":
    main()
```