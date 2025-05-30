# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import logging
import unittest

class TestAllModulesInstalled(unittest.TestCase):
    def test_import_all_modules(self):
        import grpc_admin
        import grpc_channelz
        import grpc_csds
        import grpc_csm_observability
        import grpc_health
        import grpc_observability
        import grpc_reflection
        import grpc_status

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=3)
