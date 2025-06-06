# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef _check_call_error_no_metadata(c_call_error)

cdef _check_and_raise_call_error_no_metadata(c_call_error)

cdef _check_call_error(c_call_error, metadata)

cdef class _CallState:

  cdef grpc_call *c_call
  cdef set due

  cdef object call_tracer_capsule
  cdef void maybe_save_registered_method(self, bytes method_name) except *
  cdef void maybe_set_client_call_tracer_on_call(self, bytes method_name, bytes target) except *
  cdef void delete_call(self) except *

cdef class _ChannelState:

  cdef bytes target
  cdef object condition
  cdef grpc_channel *c_channel

  cdef object open
  cdef object closed_reason

  cdef dict integrated_call_states
  cdef grpc_completion_queue *c_call_completion_queue

  cdef set segregated_call_states

  cdef set connectivity_due
  cdef grpc_completion_queue *c_connectivity_completion_queue

cdef class IntegratedCall:

  cdef _ChannelState _channel_state
  cdef _CallState _call_state

cdef class SegregatedCall:

  cdef _ChannelState _channel_state
  cdef _CallState _call_state
  cdef grpc_completion_queue *_c_completion_queue

cdef class Channel:

  cdef _ChannelState _state
  cdef dict _registered_call_handles

  cdef tuple _arguments

cdef class CallHandle:

  cdef void *c_call_handle
  cdef object method
