Here's the commented version of the code:

```c++
/*
 * Copyright 2015-2016 gRPC authors.
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
 */

/**
 * @file census.h
 * @brief Header file for gRPC Census functionality.
 * 
 * This file defines the basic structures and macros needed for Census,
 * gRPC's distributed tracing and stats collection system.
 */

#ifndef GRPC_CENSUS_H
#define GRPC_CENSUS_H

#include <grpc/grpc.h>          // Main gRPC header
#include <grpc/support/port_platform.h>  // Platform-specific configuration

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct census_context
 * @brief Opaque structure representing a Census context.
 *
 * A Census context contains tracing and stats information that is propagated
 * across RPC calls. The actual implementation details are hidden from users.
 */
typedef struct census_context census_context;

#ifdef __cplusplus
}  // extern "C"
#endif

#endif /* GRPC_CENSUS_H */
```

Key additions:
1. Added a file description comment explaining the purpose of the header
2. Added detailed comments for the `census_context` struct
3. Added comments explaining the include files
4. Added comment for the closing `extern "C"` bracket
5. Added comment for the closing header guard
6. Maintained all existing license information

The comments now provide better context about:
- What this header is for (Census functionality)
- What the main components are
- Why certain structures exist
- The purpose of the platform-specific includes
- The C/C++ interoperability handling