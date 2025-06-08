Here's the commented version of the code:

```c++
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""A test to ensure that admin services are registered correctly."""

from concurrent.futures import ThreadPoolExecutor
import logging
import sys
import unittest

import grpc
import grpc_admin
from grpc_channelz.v1 import channelz_pb2
from grpc_channelz.v1 import channelz_pb2_grpc
from grpc_csds import csds_pb2
from grpc_csds import csds_pb2_grpc

# Skip this test if running on Python 2.x as ProtoBuf descriptor isn't compatible
@unittest.skipIf(
    sys.version_info[0] < 3, "ProtoBuf descriptor has moved on from Python2"
)
class TestAdmin(unittest.TestCase):
    def setUp(self):
        """Initialize test environment before each test method.
        Creates a gRPC server with admin services, starts it, and establishes a channel.
        """
        # Create a gRPC server with thread pool executor
        self._server = grpc.server(ThreadPoolExecutor())
        # Bind server to an available port on localhost
        port = self._server.add_insecure_port("localhost:0")
        # Add admin services to the server
        grpc_admin.add_admin_servicers(self._server)
        # Start the server
        self._server.start()

        # Create an insecure channel to the server
        self._channel = grpc.insecure_channel("localhost:%s" % port)

    def tearDown(self):
        """Clean up test environment after each test method.
        Closes the channel and stops the server.
        """
        self._channel.close()
        self._server.stop(0)

    def test_has_csds(self):
        """Test that Client Status Discovery Service (CSDS) is registered and responsive.
        Verifies that the CSDS service returns a response with empty config.
        """
        # Create CSDS stub
        stub = csds_pb2_grpc.ClientStatusDiscoveryServiceStub(self._channel)
        # Make RPC call to fetch client status
        resp = stub.FetchClientStatus(csds_pb2.ClientStatusRequest())

        # Verify response contains empty config list
        self.assertEqual(len(resp.config), 0)

    def test_has_channelz(self):
        """Test that Channelz service is registered and responsive.
        Verifies that the Channelz service returns a response with at least one channel.
        """
        # Create Channelz stub
        stub = channelz_pb2_grpc.ChannelzStub(self._channel)
        # Make RPC call to get top channels
        resp = stub.GetTopChannels(channelz_pb2.GetTopChannelsRequest())

        # Verify response contains at least one channel
        self.assertGreater(len(resp.channel), 0)

if __name__ == "__main__":
    # Configure logging and run tests with verbose output
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```

The comments added:
1. Explained the purpose of the Python 2 skip decorator
2. Added detailed docstrings for each test method explaining their purpose
3. Added inline comments for important operations in setUp()
4. Documented the test assertions and their significance
5. Added explanation for the main block execution

The comments maintain a balance between explaining the what and the why, while avoiding redundancy with the code itself. They focus on the higher-level purpose of each section and the important implementation details that might not be immediately obvious.