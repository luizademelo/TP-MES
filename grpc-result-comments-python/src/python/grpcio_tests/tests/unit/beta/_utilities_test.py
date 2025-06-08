Here's the commented version of the code:

```python
# Copyright 2015 gRPC authors.
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

"""Tests of grpc.beta.utilities."""

import threading
import time
import unittest

from grpc.beta import implementations
from grpc.beta import utilities
from grpc.framework.foundation import future

from tests.unit.framework.common import test_constants

class _Callback(object):
    """A helper class for asynchronous callbacks with thread synchronization."""
    
    def __init__(self):
        """Initialize the callback with a condition variable and empty value."""
        self._condition = threading.Condition()
        self._value = None

    def accept_value(self, value):
        """Store the value and notify all waiting threads.
        
        Args:
            value: The value to be stored and passed to waiting threads.
        """
        with self._condition:
            self._value = value
            self._condition.notify_all()

    def block_until_called(self):
        """Block until a value is received and return it.
        
        Returns:
            The value that was passed to accept_value().
        """
        with self._condition:
            while self._value is None:
                self._condition.wait()
            return self._value

@unittest.skip("https://github.com/grpc/grpc/issues/16134")
class ChannelConnectivityTest(unittest.TestCase):
    """Test cases for channel connectivity functionality."""

    def test_lonely_channel_connectivity(self):
        """Test channel connectivity behavior when server is not available.
        
        Verifies that:
        1. The future remains in running state when server is unreachable
        2. The future can be properly cancelled
        3. Callbacks are properly invoked
        """
        # Create channel to non-existent server
        channel = implementations.insecure_channel("localhost", 12345)
        callback = _Callback()

        # Get ready future for channel and set up callback
        ready_future = utilities.channel_ready_future(channel)
        ready_future.add_done_callback(callback.accept_value)
        
        # Verify timeout occurs when trying to connect
        with self.assertRaises(future.TimeoutError):
            ready_future.result(timeout=test_constants.SHORT_TIMEOUT)
        
        # Verify future state before cancellation
        self.assertFalse(ready_future.cancelled())
        self.assertFalse(ready_future.done())
        self.assertTrue(ready_future.running())
        
        # Cancel the future and verify callback was called
        ready_future.cancel()
        value_passed_to_callback = callback.block_until_called()
        self.assertIs(ready_future, value_passed_to_callback)
        
        # Verify future state after cancellation
        self.assertTrue(ready_future.cancelled())
        self.assertTrue(ready_future.done())
        self.assertFalse(ready_future.running())

    def test_immediately_connectable_channel_connectivity(self):
        """Test channel connectivity behavior when server is available.
        
        Verifies that:
        1. The future completes successfully when server is available
        2. The future's state transitions correctly
        3. Cancellation after completion has no effect
        """
        # Create and start test server
        server = implementations.server({})
        port = server.add_insecure_port("[::]:0")
        server.start()
        
        # Create channel to the running server
        channel = implementations.insecure_channel("localhost", port)
        callback = _Callback()

        try:
            # Get ready future for channel and set up callback
            ready_future = utilities.channel_ready_future(channel)
            ready_future.add_done_callback(callback.accept_value)
            
            # Verify connection succeeds
            self.assertIsNone(
                ready_future.result(timeout=test_constants.LONG_TIMEOUT)
            )
            
            # Verify callback was called with the future
            value_passed_to_callback = callback.block_until_called()
            self.assertIs(ready_future, value_passed_to_callback)
            
            # Verify future state after successful completion
            self.assertFalse(ready_future.cancelled())
            self.assertTrue(ready_future.done())
            self.assertFalse(ready_future.running())

            # Verify cancellation after completion has no effect
            ready_future.cancel()
            self.assertFalse(ready_future.cancelled())
            self.assertTrue(ready_future.done())
            self.assertFalse(ready_future.running())
        finally:
            # Clean up
            ready_future.cancel()
            server.stop(0)

if __name__ == "__main__":
    # Run tests with verbose output
    unittest.main(verbosity=2)
```

The comments added:
1. File-level documentation explaining this is a test file for gRPC beta utilities
2. Class-level documentation for `_Callback` helper class
3. Method-level documentation for all methods explaining their purpose and behavior
4. Test class documentation explaining what's being tested
5. Detailed test method documentation explaining the test scenarios and verification points
6. Inline comments explaining key operations and verification steps
7. Clear section comments for logical blocks of code

The comments maintain a consistent style and provide both high-level overview and specific details about the code's functionality.