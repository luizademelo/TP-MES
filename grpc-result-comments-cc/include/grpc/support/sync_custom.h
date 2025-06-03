Here's the commented version of the code snippet:

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

#ifndef GRPC_SUPPORT_SYNC_CUSTOM_H
#define GRPC_SUPPORT_SYNC_CUSTOM_H

// Include platform-specific portability definitions
#include <grpc/support/port_platform.h>
// Include generic synchronization primitives
#include <grpc/support/sync_generic.h>

// Check if custom synchronization implementation is requested
#ifdef GPR_CUSTOM_SYNC

// Define synchronization types using custom implementations:
// - gpr_mu: Custom mutex type
// - gpr_cv: Custom condition variable type
// - gpr_once: Custom one-time initialization type
typedef GPR_CUSTOM_MU_TYPE gpr_mu;
typedef GPR_CUSTOM_CV_TYPE gpr_cv;
typedef GPR_CUSTOM_ONCE_TYPE gpr_once;

// Define the initializer for one-time initialization using custom implementation
#define GPR_ONCE_INIT GPR_CUSTOM_ONCE_INIT

#endif  // GPR_CUSTOM_SYNC

#endif  // GRPC_SUPPORT_SYNC_CUSTOM_H
```

The comments added explain:
1. The purpose of the included headers
2. The conditional compilation block for custom synchronization
3. Each typedef and what synchronization primitive it represents
4. The one-time initialization macro
5. The closing of conditional and header guards

The comments maintain the original license header and provide clear explanations of the synchronization abstraction layer being defined, which will help future developers understand and maintain this code.