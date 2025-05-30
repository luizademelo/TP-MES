# Copyright 2019 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

"""
Reimports constants from the grpc_custom_exec_properties repo.
"""

load("@grpc_custom_exec_properties//:constants.bzl", _LARGE_MACHINE = "LARGE_MACHINE")

LARGE_MACHINE = _LARGE_MACHINE
