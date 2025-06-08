Here's the commented version of the code snippet:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Store the current global symbols before importing grpc module
# This helps in identifying what new symbols are added by the import
_BEFORE_IMPORT = tuple(globals())

# Import all symbols from the grpc module
from grpc import *

# Store the global symbols after importing grpc module
_AFTER_IMPORT = tuple(globals())

# Create a tuple of elements that were added by the grpc import:
# 1. Compares before and after import states
# 2. Excludes the '_BEFORE_IMPORT' variable itself from the result
# 3. Results in only the newly imported grpc elements being included
GRPC_ELEMENTS = tuple(
    element
    for element in _AFTER_IMPORT
    if element not in _BEFORE_IMPORT and element != "_BEFORE_IMPORT"
)

```

The comments explain:
1. The purpose of `_BEFORE_IMPORT` and `_AFTER_IMPORT` in tracking global symbol changes
2. The import statement's effect
3. The logic behind `GRPC_ELEMENTS` which identifies newly imported symbols
4. The filtering of internal variables from the result

The comments maintain the original functionality while making the code's intent clearer to future maintainers.