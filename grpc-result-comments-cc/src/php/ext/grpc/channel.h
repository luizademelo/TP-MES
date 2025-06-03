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

#ifndef NET_GRPC_PHP_GRPC_CHANNEL_H_
#define NET_GRPC_PHP_GRPC_CHANNEL_H_

#include "channel_credentials.h"
#include "php_grpc.h"

// Macro to handle hash initialization differences between PHP 8 and earlier versions
#if PHP_MAJOR_VERSION >= 8
#define ZEND_HASH_INIT(hash_table, limit, descriptor, zend_bool) _zend_hash_init(hash_table, limit, descriptor, zend_bool);
#else
#define ZEND_HASH_INIT(hash_table, limit, descriptor, zend_bool) zend_hash_init_ex(hash_table, limit, NULL, descriptor, zend_bool, 0);
#endif

// PHP class entry for gRPC channel
extern zend_class_entry *grpc_ce_channel;

// Structure representing a wrapped gRPC channel with additional metadata
typedef struct _grpc_channel_wrapper {
  grpc_channel *wrapped;                // Core gRPC channel object
  char *key;                            // Unique identifier for the channel
  char *target;                         // Target address for the channel
  char *args_hashstr;                   // Hash string of channel arguments
  char *creds_hashstr;                  // Hash string of channel credentials
  size_t ref_count;                     // Reference count for the channel
  gpr_mu mu;                           // Mutex for thread safety
  grpc_channel_args args;               // Channel configuration arguments
  wrapped_grpc_channel_credentials *creds;  // Channel credentials
} grpc_channel_wrapper;

// Macro to start the wrapper object definition for gRPC channel
PHP_GRPC_WRAP_OBJECT_START(wrapped_grpc_channel)
  grpc_channel_wrapper *wrapper;        // Pointer to the channel wrapper
PHP_GRPC_WRAP_OBJECT_END(wrapped_grpc_channel)

// Utility function to get wrapped_grpc_channel from zend_object
static inline wrapped_grpc_channel
*wrapped_grpc_channel_from_obj(zend_object *obj) {
  return (wrapped_grpc_channel*)((char*)(obj) -
                                 XtOffsetOf(wrapped_grpc_channel, std));
}

// Function to be called during PHP module startup to initialize channel functionality
GRPC_STARTUP_FUNCTION(channel);

// Function to read channel arguments from PHP array into grpc_channel_args structure
int php_grpc_read_args_array(zval *args_array, grpc_channel_args *args
                             TSRMLS_DC);

// Function to generate SHA1 hash string from input string
void generate_sha1_str(char *sha1str, char *str, php_grpc_int len);

// Function to delete an entry from the persistent channel list
void php_grpc_delete_persistent_list_entry(char *key, php_grpc_int key_len
                                           TSRMLS_DC);

// Structure for persistent list entries of channels
typedef struct _channel_persistent_le {
  grpc_channel_wrapper *channel;       // Pointer to the channel wrapper
} channel_persistent_le_t;

// Structure for tracking target connection bounds
typedef struct _target_bound_le {
  int upper_bound;                     // Maximum allowed connections
  int current_count;                   // Current connection count
} target_bound_le_t;

#endif  // NET_GRPC_PHP_GRPC_CHANNEL_H_
```

Key aspects of the comments:
1. Added explanations for each major structure and its fields
2. Documented the purpose of each function
3. Explained the version-specific macro for hash initialization
4. Clarified the role of wrapper objects and conversion functions
5. Maintained the original license header
6. Added clear section comments for different parts of the header
7. Explained the purpose of the persistent list and connection tracking structures

The comments provide a clear understanding of the code's functionality while maintaining readability and staying true to the original implementation.