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

#ifndef NET_GRPC_PHP_GRPC_TIMEVAL_H_
#define NET_GRPC_PHP_GRPC_TIMEVAL_H_

#include "php_grpc.h"

// Class entry for the Timeval class in PHP
extern zend_class_entry *grpc_ce_timeval;

// Macro to define the structure for wrapping gRPC timeval objects in PHP
// Contains a gpr_timespec structure as its member
PHP_GRPC_WRAP_OBJECT_START(wrapped_grpc_timeval)
  gpr_timespec wrapped;  // The actual timespec being wrapped
PHP_GRPC_WRAP_OBJECT_END(wrapped_grpc_timeval)

// Helper function to convert a zend_object to wrapped_grpc_timeval
// Calculates the offset to get the containing structure from the zend_object
static inline wrapped_grpc_timeval
*wrapped_grpc_timeval_from_obj(zend_object *obj) {
  return (wrapped_grpc_timeval*)((char*)(obj) -
                                 XtOffsetOf(wrapped_grpc_timeval, std));
}

// Initializes the Timeval class and registers it with Zend engine
void grpc_init_timeval(TSRMLS_D);

// Cleans up resources used by the Timeval class
void grpc_shutdown_timeval(TSRMLS_D);

// Creates a PHP object wrapping a gpr_timespec structure
// Takes a gpr_timespec and returns a zval (PHP variable container)
zval *grpc_php_wrap_timeval(gpr_timespec wrapped TSRMLS_DC);

#endif  // NET_GRPC_PHP_GRPC_TIMEVAL_H_
```

The comments explain:
1. The copyright and license information
2. The purpose of the header guard
3. The class entry for PHP Timeval class
4. The wrapper structure for gRPC timeval objects
5. The helper function for object conversion
6. The initialization and shutdown functions
7. The wrapper function for creating PHP objects from gpr_timespec
8. The closing header guard

The comments are concise yet informative, explaining both what each part does and why it's important in the context of the gRPC PHP extension.