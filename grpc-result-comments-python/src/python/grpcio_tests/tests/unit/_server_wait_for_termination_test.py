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

# Import future division behavior for Python 2 compatibility
from __future__ import division

# Import required modules
from concurrent import futures  # For thread pool execution
import datetime  # For time calculations
import threading  # For multi-threading support
import time  # For sleep functionality
import unittest  # For unit testing framework

import grpc  # gRPC library

from tests.unit.framework.common import test_constants  # Test constants

# Define a wait time constant for blocking operations
_WAIT_FOR_BLOCKING = datetime.timedelta(seconds=1)

def _block_on_waiting(server, termination_event, timeout=None):
    """
    Helper function to start a server and block until termination.
    
    Args:
        server: gRPC server instance
        termination_event: threading.Event to signal when termination occurs
        timeout: Optional timeout for server termination wait
    """
    server.start()
    server.wait_for_termination(timeout=timeout)
    termination_event.set()

class ServerWaitForTerminationTest(unittest.TestCase):
    """Test cases for gRPC server termination scenarios."""

    def test_unblock_by_invoking_stop(self):
        """Test that server termination can be triggered by calling stop()."""
        termination_event = threading.Event()
        server = grpc.server(futures.ThreadPoolExecutor())

        # Start a thread that will block waiting for server termination
        wait_thread = threading.Thread(
            target=_block_on_waiting,
            args=(
                server,
                termination_event,
            ),
        )
        wait_thread.daemon = True  # Daemonize thread so it exits with main program
        wait_thread.start()
        
        # Wait briefly to ensure the server is running
        time.sleep(_WAIT_FOR_BLOCKING.total_seconds())

        # Stop the server and verify termination
        server.stop(None)
        termination_event.wait(timeout=test_constants.SHORT_TIMEOUT)
        self.assertTrue(termination_event.is_set())

    def test_unblock_by_del(self):
        """Test that server termination can be triggered by calling __del__()."""
        termination_event = threading.Event()
        server = grpc.server(futures.ThreadPoolExecutor())

        # Start a thread that will block waiting for server termination
        wait_thread = threading.Thread(
            target=_block_on_waiting,
            args=(
                server,
                termination_event,
            ),
        )
        wait_thread.daemon = True
        wait_thread.start()
        
        # Wait briefly to ensure the server is running
        time.sleep(_WAIT_FOR_BLOCKING.total_seconds())

        # Trigger server deletion and verify termination
        server.__del__()
        termination_event.wait(timeout=test_constants.SHORT_TIMEOUT)
        self.assertTrue(termination_event.is_set())

    def test_unblock_by_timeout(self):
        """Test that server wait terminates after specified timeout."""
        termination_event = threading.Event()
        server = grpc.server(futures.ThreadPoolExecutor())

        # Start a thread with a timeout for server termination
        wait_thread = threading.Thread(
            target=_block_on_waiting,
            args=(
                server,
                termination_event,
                test_constants.SHORT_TIMEOUT / 2,  # Set timeout to half of short timeout
            ),
        )
        wait_thread.daemon = True
        wait_thread.start()

        # Verify termination occurs within expected timeframe
        termination_event.wait(timeout=test_constants.SHORT_TIMEOUT)
        self.assertTrue(termination_event.is_set())

if __name__ == "__main__":
    # Run tests with verbose output
    unittest.main(verbosity=2)
```