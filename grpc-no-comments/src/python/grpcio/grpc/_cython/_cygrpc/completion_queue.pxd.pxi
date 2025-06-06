# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef int g_interrupt_check_period_ms

cdef grpc_event _next(grpc_completion_queue *c_completion_queue, deadline) except *

cdef _interpret_event(grpc_event c_event)

cdef class _LatentEventArg:
  cdef grpc_completion_queue *c_completion_queue
  cdef object deadline

cdef class CompletionQueue:

  cdef grpc_completion_queue *c_completion_queue
  cdef bint is_shutting_down
  cdef bint is_shutdown

  cdef _interpret_event(self, grpc_event c_event)
