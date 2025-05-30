# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Reference implementation for status mapping in gRPC Python."""

import grpc

_CODE_TO_GRPC_CODE_MAPPING = {x.value[0]: x for x in grpc.StatusCode}

GRPC_DETAILS_METADATA_KEY = "grpc-status-details-bin"

def code_to_grpc_status_code(code):
    try:
        return _CODE_TO_GRPC_CODE_MAPPING[code]
    except KeyError:
        raise ValueError("Invalid status code %s" % code)
