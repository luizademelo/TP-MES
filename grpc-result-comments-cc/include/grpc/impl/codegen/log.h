Here's the commented version of the code snippet:

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

#ifndef GRPC_IMPL_CODEGEN_LOG_H
#define GRPC_IMPL_CODEGEN_LOG_H

// Include platform-specific configuration macros and types
#include <grpc/impl/codegen/port_platform.h>

// Include the main logging support header from gRPC support library
// This provides logging macros and utilities used throughout gRPC
#include <grpc/support/log.h>

#endif /* GRPC_IMPL_CODEGEN_LOG_H */
```

Key comments added:
1. Added a brief description of what `port_platform.h` provides
2. Explained the purpose of including `grpc/support/log.h`
3. Added a closing comment to the `#endif` directive to indicate which header it's closing
4. Maintained all original copyright and license information

The comments help future developers understand:
- The purpose of each include
- The relationship between these headers
- That this is a header guard pattern
- Where the logging functionality actually comes from