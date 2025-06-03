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

#ifndef NET_GRPC_PHP_GRPC_SERVER_CREDENTIALS_H_
#define NET_GRPC_PHP_GRPC_SERVER_CREDENTIALS_H_

#include "php_grpc.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>

// PHP class entry for gRPC server credentials
extern zend_class_entry *grpc_ce_server_credentials;

// Wrapper structure for gRPC server credentials to be used in PHP
PHP_GRPC_WRAP_OBJECT_START(wrapped_grpc_server_credentials)
  grpc_server_credentials *wrapped;  // Pointer to the actual gRPC server credentials
PHP_GRPC_WRAP_OBJECT_END(wrapped_grpc_server_credentials)

/**
 * Converts a zend_object to a wrapped_grpc_server_credentials structure
 * @param obj The zend_object to convert
 * @return Pointer to the wrapped_grpc_server_credentials structure
 */
static inline wrapped_grpc_server_credentials
*wrapped_grpc_server_credentials_from_obj(zend_object *obj) {
  return (wrapped_grpc_server_credentials*)(
      (char*)(obj) - XtOffsetOf(wrapped_grpc_server_credentials, std));
}

/**
 * Initializes the gRPC server credentials in PHP
 * @param TSRMLS_D Thread-safe resource manager (TSRM) parameter
 */
void grpc_init_server_credentials(TSRMLS_D);

#endif /* NET_GRPC_PHP_GRPC_SERVER_CREDENTIALS_H_ */
```

Key additions:
1. Added description for the PHP class entry variable
2. Documented the wrapper structure purpose and its field
3. Added detailed comments for the conversion function explaining its purpose and parameters
4. Documented the initialization function's purpose and parameter
5. Added proper closing comment for the header guard
6. Maintained all original copyright and licensing information

The comments provide clear explanations of each component's purpose while maintaining the original code structure and functionality.