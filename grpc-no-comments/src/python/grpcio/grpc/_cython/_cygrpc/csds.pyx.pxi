# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

def dump_xds_configs():
    cdef grpc_slice client_config_in_slice
    with nogil:
        client_config_in_slice = grpc_dump_xds_configs()
    cdef bytes result = _slice_bytes(client_config_in_slice)
    return result
