# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef void* _copy_pointer(void* pointer)

cdef void _destroy_pointer(void* pointer)

cdef int _compare_pointer(void* first_pointer, void* second_pointer)

cdef grpc_arg_pointer_vtable default_vtable
