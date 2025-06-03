Here's the commented version of the code:

```c++
/*
 *
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
 *
 */

#ifndef GRPC_PHP_GRPC_COMPLETION_QUEUE_H_
#define GRPC_PHP_GRPC_COMPLETION_QUEUE_H_

// Include PHP main header file
#include <php.h>
// Include gRPC core header
#include <grpc/grpc.h>

// Compatibility macro for PHP 8+ (Thread Safe Resource Manager macros were removed in PHP 8)
#if PHP_MAJOR_VERSION >= 8
#define TSRMLS_D
#endif

// Global completion queue pointer for gRPC operations
extern grpc_completion_queue *completion_queue;

/**
 * Initializes the gRPC completion queue.
 * This function should be called during PHP module initialization.
 * @param TSRMLS_D - Thread Safe Resource Manager macro (empty in PHP 8+)
 */
void grpc_php_init_completion_queue(TSRMLS_D);

/**
 * Shuts down and cleans up the gRPC completion queue.
 * This function should be called during PHP module shutdown.
 * @param TSRMLS_D - Thread Safe Resource Manager macro (empty in PHP 8+)
 */
void grpc_php_shutdown_completion_queue(TSRMLS_D);

#endif /* GRPC_PHP_GRPC_COMPLETION_QUEUE_H_ */
```

Key additions:
1. Added explanation of the PHP version compatibility macro
2. Documented the purpose of the global completion queue variable
3. Added detailed comments for both function declarations
4. Added closing comment for the #endif directive
5. Explained the TSRMLS_D parameter which relates to PHP's thread safety system
6. Added general comments about included headers

The comments provide context about:
- The purpose of each component
- When functions should be called
- Compatibility considerations
- The role of global variables
- Relationships between components