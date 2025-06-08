Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Testing the channel_ready function."""

import asyncio
import gc
import logging
import socket
import time
import unittest

import grpc
from grpc.experimental import aio

from tests.unit.framework.common import get_socket
from tests.unit.framework.common import test_constants
from tests_aio.unit import _common
from tests_aio.unit._test_base import AioTestBase
from tests_aio.unit._test_server import start_test_server

class TestChannelReady(AioTestBase):
    """Test case for verifying channel readiness functionality."""
    
    async def setUp(self):
        """Set up test environment before each test method.
        Creates a channel with a closed socket to simulate initial connection state.
        """
        # Get a socket and its details without listening (connection will initially fail)
        address, self._port, self._socket = get_socket(
            listen=False, sock_options=(socket.SO_REUSEADDR,)
        )
        # Create an insecure channel to the test address
        self._channel = aio.insecure_channel(f"{address}:{self._port}")
        # Close the socket to ensure initial connection failure
        self._socket.close()

    async def tearDown(self):
        """Clean up test environment after each test method.
        Closes the channel to release resources.
        """
        await self._channel.close()

    async def test_channel_ready_success(self):
        """Test successful channel readiness scenario.
        Verifies that channel_ready() completes when server becomes available.
        """
        # Create a task to wait for channel to be ready
        channel_ready_task = self.loop.create_task(
            self._channel.channel_ready()
        )

        # Wait until channel is in transient failure state (expected initial state)
        await _common.block_until_certain_state(
            self._channel, grpc.ChannelConnectivity.TRANSIENT_FAILURE
        )

        try:
            # Start test server on the same port to allow connection
            _, server = await start_test_server(port=self._port)

            # Wait for channel_ready to complete (should succeed now that server is up)
            await channel_ready_task
        finally:
            # Ensure server is stopped regardless of test outcome
            await server.stop(None)

    @unittest.skip(
        "skipping due to flake: https://github.com/grpc/grpc/issues/37949"
    )
    async def test_channel_ready_blocked(self):
        """Test channel readiness timeout scenario.
        Verifies that channel_ready() raises TimeoutError when server is not available.
        Currently skipped due to flakiness issue.
        """
        with self.assertRaises(asyncio.TimeoutError):
            # Attempt to wait for channel readiness with a short timeout
            # Expect this to fail since no server will be started
            await asyncio.wait_for(
                self._channel.channel_ready(), test_constants.SHORT_TIMEOUT
            )

if __name__ == "__main__":
    # Configure logging and run tests with verbose output
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```

Key improvements in the comments:
1. Added class-level docstring explaining the test case purpose
2. Added detailed method docstrings for setup/teardown and test cases
3. Added inline comments explaining key operations and their purpose
4. Documented the skipped test and its reason
5. Explained the main block's functionality
6. Clarified the expected behavior in each test scenario

The comments now provide a clear understanding of:
- What each test is verifying
- The setup/teardown process
- The expected behavior in both success and failure cases
- Why certain tests might be skipped