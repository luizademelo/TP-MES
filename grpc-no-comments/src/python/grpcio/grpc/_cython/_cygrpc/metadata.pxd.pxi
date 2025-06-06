# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef void _store_c_metadata(
    metadata, grpc_metadata **c_metadata, size_t *c_count) except *

cdef void _release_c_metadata(grpc_metadata *c_metadata, int count) except *

cdef tuple _metadatum(grpc_slice key_slice, grpc_slice value_slice)

cdef tuple _metadata(grpc_metadata_array *c_metadata_array)
