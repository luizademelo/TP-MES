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

#ifndef NET_GRPC_PHP_GRPC_CALL_CREDENTIALS_H_
#define NET_GRPC_PHP_GRPC_CALL_CREDENTIALS_H_

#include "php_grpc.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>

// Class entry for PHP gRPC call credentials
extern zend_class_entry *grpc_ce_call_credentials;

// Wrapper structure for gRPC call credentials to be used in PHP
PHP_GRPC_WRAP_OBJECT_START(wrapped_grpc_call_credentials)
  grpc_call_credentials *wrapped;  // Pointer to the actual gRPC call credentials
PHP_GRPC_WRAP_OBJECT_END(wrapped_grpc_call_credentials)

/**
 * Converts a zend_object to wrapped_grpc_call_credentials by adjusting the pointer
 * to account for the offset of the std member in the structure.
 *
 * @param obj The zend_object to convert
 * @return Pointer to the wrapped_grpc_call_credentials structure
 */
static inline wrapped_grpc_call_credentials
*wrapped_grpc_call_credentials_from_obj(zend_object *obj) {
  return (wrapped_grpc_call_credentials*)(
      (char*)(obj) - XtOffsetOf(wrapped_grpc_call_credentials, std));
}

// Structure to maintain state for credential plugin callbacks
typedef struct plugin_state {
  zend_fcall_info *fci;         // PHP function call information
  zend_fcall_info_cache *fci_cache;  // Cache for PHP function calls
} plugin_state;

/**
 * Callback function for gRPC credential plugins to fetch metadata.
 *
 * @param ptr Plugin state pointer
 * @param context Authentication metadata context
 * @param cb Callback to be invoked with the metadata
 * @param user_data User data to be passed to the callback
 * @param creds_md Array to store synchronous credentials metadata
 * @param num_creds_md Number of metadata entries
 * @param status Status code to return
 * @param error_details Error details if any
 * @return 1 on success, 0 on failure
 */
int plugin_get_metadata(
  void *ptr, grpc_auth_metadata_context context,
  grpc_credentials_plugin_metadata_cb cb, void *user_data,
  grpc_metadata creds_md[GRPC_METADATA_CREDENTIALS_PLUGIN_SYNC_MAX],
  size_t *num_creds_md, grpc_status_code *status,
  const char **error_details);

/**
 * Destroys the state of a credential plugin.
 *
 * @param ptr Plugin state pointer to destroy
 */
void plugin_destroy_state(void *ptr);

/**
 * Initializes gRPC call credentials in PHP.
 *
 * @param TSRMLS_D Thread-safe resource manager macro (for PHP)
 */
void grpc_init_call_credentials(TSRMLS_D);

#endif  // NET_GRPC_PHP_GRPC_CALL_CREDENTIALS_H_
```

The comments provide:
1. File header with licensing information
2. Explanation of the purpose of each major component
3. Documentation for each function including parameters and return values
4. Clarification of complex operations (like the pointer adjustment in wrapped_grpc_call_credentials_from_obj)
5. Context for the plugin state structure and its use
6. Clear indication of the file's purpose as a header file with include guards

The comments are designed to help future developers understand:
- The overall structure of the code
- How the PHP and gRPC components interact
- The purpose of each function and data structure
- Important implementation details