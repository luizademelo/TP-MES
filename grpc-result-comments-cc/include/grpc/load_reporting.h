Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2017 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_LOAD_REPORTING_H
#define GRPC_LOAD_REPORTING_H

// Include platform-specific support macros and definitions
#include <grpc/support/port_platform.h>

// C++ compatibility: if compiled as C++, use C linkage
#ifdef __cplusplus
extern "C" {
#endif

// Metadata key for load balancing token
// Used to identify the load balancing token in metadata
#define GRPC_LB_TOKEN_MD_KEY "lb-token"

// Metadata key for load balancing cost data
// Used to identify binary-encoded cost metrics in metadata
#define GRPC_LB_COST_MD_KEY "lb-cost-bin"

// End C++ linkage scope if we started it
#ifdef __cplusplus
}
#endif

#endif  // GRPC_LOAD_REPORTING_H
```

Key additions:
1. Added comment explaining the purpose of `port_platform.h` inclusion
2. Explained the C++ compatibility `extern "C"` block
3. Documented both metadata key macros with their purposes
4. Added clear closing comment for the C++ linkage scope
5. Added comment for the header guard closure

The comments now clearly explain:
- The overall purpose of the header file (load reporting definitions)
- The significance of each defined macro
- The cross-language compatibility measures
- The structure of the conditional compilation blocks