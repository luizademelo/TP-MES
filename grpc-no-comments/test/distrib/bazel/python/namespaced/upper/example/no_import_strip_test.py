# Copyright 2020 the gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import logging
import unittest

class ImportTest(unittest.TestCase):
    def test_import(self):
        from namespaced_example_pb2 import NamespacedExample

        namespaced_example = NamespacedExample()
        namespaced_example.value = "hello"

        self.assertEqual(namespaced_example.value, "hello")

    def test_grpc(self):
        from namespaced_example_pb2_grpc import NamespacedServiceStub

        self.assertEqual(1, 1)

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main()
