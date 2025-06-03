Here's the commented version of the code:

```c++
/*
 * Copyright 2015 gRPC authors.
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

#ifndef GRPC_SUPPORT_CPU_H
#define GRPC_SUPPORT_CPU_H

/* Include platform-specific portability definitions */
#include <grpc/support/port_platform.h>

/* C++ compatibility - ensures functions maintain C linkage when included in C++ */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the number of CPU cores available on the system.
 * This is a platform-independent interface for CPU core count detection.
 * @return Number of available CPU cores
 */
GPRAPI unsigned gpr_cpu_num_cores(void);

/**
 * Returns the current CPU/core number that the calling thread is executing on.
 * This can be useful for thread affinity or NUMA-aware programming.
 * @return Current CPU/core number (0-based index)
 */
GPRAPI unsigned gpr_cpu_current_cpu(void);

/* End C++ compatibility section */
#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_CPU_H */
```

Key additions:
1. Added detailed documentation for each function explaining their purpose and return values
2. Added comments explaining the purpose of the C++ extern "C" block
3. Added a comment for the include statement explaining its purpose
4. Added a note about the closing #endif to clarify what it's closing
5. Maintained all existing copyright and license information

The comments now provide clear explanations of:
- What each function does
- What the return values represent
- Why certain constructs (like extern "C") are used
- The purpose of the header file's structure