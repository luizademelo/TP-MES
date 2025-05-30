# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Exceptions for the aio version of the RPC calls."""

cdef class AioRpcStatus(Exception):
    cdef readonly:
        grpc_status_code _code
        str _details

        tuple _trailing_metadata
        str _debug_error_string

    cpdef grpc_status_code code(self)
    cpdef str details(self)
    cpdef tuple trailing_metadata(self)
    cpdef str debug_error_string(self)
    cdef grpc_status_code c_code(self)
