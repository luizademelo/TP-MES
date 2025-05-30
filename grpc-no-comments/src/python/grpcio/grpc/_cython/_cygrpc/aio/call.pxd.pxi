# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef class _AioCall(GrpcCallWrapper):
    cdef:
        readonly AioChannel _channel
        list _references
        object _deadline
        list _done_callbacks

        object _loop

        bint _is_locally_cancelled

        readonly AioRpcStatus _status
        readonly tuple _initial_metadata
        list _waiters_status
        list _waiters_initial_metadata

        int _send_initial_metadata_flags

    cdef void _create_grpc_call(self, object timeout, bytes method, CallCredentials credentials) except *
    cdef void _set_status(self, AioRpcStatus status) except *
    cdef void _set_initial_metadata(self, tuple initial_metadata) except *
