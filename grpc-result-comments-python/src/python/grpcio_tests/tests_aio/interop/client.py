Here's the commented version of the code:

```python
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required modules
import argparse  # For parsing command-line arguments
import asyncio  # For asynchronous I/O operations
import logging  # For logging events and debugging
import os  # For operating system dependent functionality
import sys  # For system-specific parameters and functions

# Import gRPC related modules
import grpc
from grpc.experimental import aio  # Asynchronous I/O implementation of gRPC

# Import test client libraries
from tests.interop import client as interop_client_lib  # Interoperability test client
from tests_aio.interop import methods  # Asynchronous I/O test methods

# Initialize logger for this module
_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.DEBUG)  # Set logging level to DEBUG for detailed output

def _create_channel(args):
    """Create and return a gRPC channel based on the provided arguments.
    
    Args:
        args: Command-line arguments containing connection parameters
        
    Returns:
        A secure or insecure gRPC channel based on the provided configuration
    """
    # Construct target address from host and port
    target = f"{args.server_host}:{args.server_port}"

    # Check if secure channel is required (TLS, ALTS, or custom credentials)
    if (
        args.use_tls
        or args.use_alts
        or args.custom_credentials_type is not None
    ):
        # Get secure channel parameters from interop client library
        (
            channel_credentials,
            options,
        ) = interop_client_lib.get_secure_channel_parameters(args)
        # Create and return secure channel
        return aio.secure_channel(target, channel_credentials, options)
    else:
        # Create and return insecure channel
        return aio.insecure_channel(target)

def _test_case_from_arg(test_case_arg):
    """Convert test case argument string to corresponding TestCase enum value.
    
    Args:
        test_case_arg: String representing the test case
        
    Returns:
        Corresponding TestCase enum value
        
    Raises:
        ValueError: If no matching test case is found
    """
    # Iterate through all available test cases
    for test_case in methods.TestCase:
        # Check if argument matches test case value
        if test_case_arg == test_case.value:
            return test_case
    else:
        # Raise error if no matching test case found
        raise ValueError('No test case "%s"!' % test_case_arg)

async def test_interoperability():
    """Main function to execute gRPC interoperability tests.
    
    This function:
    1. Parses command-line arguments
    2. Creates a gRPC channel
    3. Creates a stub for the channel
    4. Determines the test case
    5. Executes the interoperability test
    """
    # Parse command-line arguments
    args = interop_client_lib.parse_interop_client_args(sys.argv)
    # Create appropriate channel (secure/insecure)
    channel = _create_channel(args)
    # Create stub for the channel
    stub = interop_client_lib.create_stub(channel, args)
    # Get test case from arguments
    test_case = _test_case_from_arg(args.test_case)
    # Execute the interoperability test
    await methods.test_interoperability(test_case, stub, args)

if __name__ == "__main__":
    # Configure basic logging settings
    logging.basicConfig(level=logging.DEBUG)
    # Enable asyncio debug mode
    asyncio.get_event_loop().set_debug(True)
    # Run the main test function until completion
    asyncio.get_event_loop().run_until_complete(test_interoperability())
```