# Copyright 2019 The gRPC Authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
import logging
import unittest

class TestInit(unittest.TestCase):
    def test_grpc(self):
        import grpc

        channel = grpc.aio.insecure_channel("phony")
        self.assertIsInstance(channel, grpc.aio.Channel)

    def test_grpc_dot_aio(self):
        import grpc.aio

        channel = grpc.aio.insecure_channel("phony")
        self.assertIsInstance(channel, grpc.aio.Channel)

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
