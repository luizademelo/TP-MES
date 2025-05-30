# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

_BEFORE_IMPORT = tuple(globals())

from grpc import *

_AFTER_IMPORT = tuple(globals())

GRPC_ELEMENTS = tuple(
    element
    for element in _AFTER_IMPORT
    if element not in _BEFORE_IMPORT and element != "_BEFORE_IMPORT"
)
