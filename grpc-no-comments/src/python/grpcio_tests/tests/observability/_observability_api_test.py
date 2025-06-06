# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Test of gRPC Python Observability's application-layer API."""

import logging
import unittest

from tests.observability import _from_csm_observability_import_star
from tests.observability import _from_observability_import_star

class AllTest(unittest.TestCase):
    def testBaseOtel(self):
        expected_observability_code_elements = ("OpenTelemetryPlugin",)

        self.assertCountEqual(
            expected_observability_code_elements,
            _from_observability_import_star.GRPC_OBSERVABILITY_ELEMENTS,
        )

    def testCSMOtel(self):
        expected_csm_observability_code_elements = ("CsmOpenTelemetryPlugin",)

        self.assertCountEqual(
            expected_csm_observability_code_elements,
            _from_csm_observability_import_star.GRPC_CSM_OBSERVABILITY_ELEMENTS,
        )

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
