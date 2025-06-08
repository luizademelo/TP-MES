Here's the commented version of the code:

```c++
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
"""Defines an enumeration for classifying RPC methods by their streaming semantics."""

import enum

@enum.unique  # Ensures all enum values are unique
class Cardinality(enum.Enum):
    """
    Enumeration describing the streaming semantics of RPC (Remote Procedure Call) methods.
    
    This class defines four possible combinations of request/response streaming patterns:
    - UNARY_UNARY: Single request followed by single response
    - UNARY_STREAM: Single request followed by stream of responses
    - STREAM_UNARY: Stream of requests followed by single response
    - STREAM_STREAM: Stream of requests followed by stream of responses
    
    These are fundamental patterns in gRPC communication.
    """
    
    # Single request message followed by single response message
    UNARY_UNARY = "request-unary/response-unary"
    
    # Single request message followed by stream of response messages
    UNARY_STREAM = "request-unary/response-streaming"
    
    # Stream of request messages followed by single response message
    STREAM_UNARY = "request-streaming/response-unary"
    
    # Stream of request messages followed by stream of response messages
    STREAM_STREAM = "request-streaming/response-streaming"
```