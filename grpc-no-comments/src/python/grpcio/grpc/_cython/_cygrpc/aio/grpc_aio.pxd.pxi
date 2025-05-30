# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef class _AioState:
    cdef object lock
    cdef int refcount
    cdef object engine
    cdef BaseCompletionQueue cq

cdef grpc_completion_queue *global_completion_queue()

cpdef init_grpc_aio()

cpdef shutdown_grpc_aio()

cdef extern from "src/core/lib/iomgr/timer_manager.h":
  void grpc_timer_manager_set_threading(bint enabled)

cdef extern from "src/core/lib/iomgr/iomgr_internal.h":
  void grpc_set_default_iomgr_platform()
