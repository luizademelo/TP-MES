# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Defines an enum for classifying RPC methods by control flow semantics."""

import enum

@enum.unique
class Service(enum.Enum):
    """Describes the control flow style of RPC method implementation."""

    INLINE = "inline"
    EVENT = "event"
