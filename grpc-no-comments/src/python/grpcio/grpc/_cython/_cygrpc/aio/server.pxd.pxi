# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef class _HandlerCallDetails:
    cdef readonly str method
    cdef readonly tuple invocation_metadata

cdef class RPCState(GrpcCallWrapper):
    cdef grpc_call_details details
    cdef grpc_metadata_array request_metadata
    cdef AioServer server

    cdef bint client_closed
    cdef object abort_exception
    cdef bint metadata_sent
    cdef bint status_sent
    cdef grpc_status_code status_code
    cdef object py_status_code
    cdef str status_details
    cdef tuple trailing_metadata
    cdef object compression_algorithm
    cdef bint disable_next_compression
    cdef object callbacks

    cdef bytes method(self)
    cdef tuple invocation_metadata(self)
    cdef void raise_for_termination(self) except *
    cdef int get_write_flag(self)
    cdef Operation create_send_initial_metadata_op_if_not_sent(self)

cdef class _ServicerContext:
    cdef RPCState _rpc_state
    cdef object _loop
    cdef object _request_deserializer
    cdef object _response_serializer

cdef class _SyncServicerContext:
    cdef _ServicerContext _context
    cdef list _callbacks
    cdef object _loop

cdef class _MessageReceiver:
    cdef _ServicerContext _servicer_context
    cdef object _agen

cdef enum AioServerStatus:
    AIO_SERVER_STATUS_UNKNOWN
    AIO_SERVER_STATUS_READY
    AIO_SERVER_STATUS_RUNNING
    AIO_SERVER_STATUS_STOPPED
    AIO_SERVER_STATUS_STOPPING

cdef class _ConcurrentRpcLimiter:
    cdef int _maximum_concurrent_rpcs
    cdef int _active_rpcs
    cdef bint limiter_concurrency_exceeded

cdef class AioServer:
    cdef Server _server
    cdef list _generic_handlers
    cdef AioServerStatus _status
    cdef object _loop
    cdef object _serving_task
    cdef object _shutdown_lock
    cdef object _shutdown_completed
    cdef CallbackWrapper _shutdown_callback_wrapper
    cdef object _crash_exception
    cdef tuple _interceptors
    cdef object _thread_pool
    cdef _ConcurrentRpcLimiter _limiter

    cdef thread_pool(self)
