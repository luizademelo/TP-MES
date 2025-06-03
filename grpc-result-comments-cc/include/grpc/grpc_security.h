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

#ifndef GRPC_GRPC_SECURITY_H
#define GRPC_GRPC_SECURITY_H

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque structure representing authentication context
typedef struct grpc_auth_context grpc_auth_context;

// Iterator for authentication properties
typedef struct grpc_auth_property_iterator {
  const grpc_auth_context* ctx;  // Context being iterated
  size_t index;                  // Current position in iteration
  const char* name;              // Property name to filter by (optional)
} grpc_auth_property_iterator;

// Structure representing a single authentication property
typedef struct grpc_auth_property {
  char* name;            // Name of the property
  char* value;           // Value of the property
  size_t value_length;   // Length of the value in bytes
} grpc_auth_property;

// Returns the next property in the iterator or NULL if no more properties
GRPCAPI const grpc_auth_property* grpc_auth_property_iterator_next(
    grpc_auth_property_iterator* it);

// Creates an iterator for all properties in the authentication context
GRPCAPI grpc_auth_property_iterator
grpc_auth_context_property_iterator(const grpc_auth_context* ctx);

// Creates an iterator specifically for peer identity properties
GRPCAPI grpc_auth_property_iterator
grpc_auth_context_peer_identity(const grpc_auth_context* ctx);

// Creates an iterator for properties matching a specific name
GRPCAPI grpc_auth_property_iterator grpc_auth_context_find_properties_by_name(
    const grpc_auth_context* ctx, const char* name);

// Returns the name of the property that represents peer identity
GRPCAPI const char* grpc_auth_context_peer_identity_property_name(
    const grpc_auth_context* ctx);

// Checks if the peer is authenticated (returns 1 if true, 0 otherwise)
GRPCAPI int grpc_auth_context_peer_is_authenticated(
    const grpc_auth_context* ctx);

// Retrieves the authentication context associated with a call
GRPCAPI grpc_auth_context* grpc_call_auth_context(grpc_call* call);

// Releases resources associated with an authentication context
GRPCAPI void grpc_auth_context_release(grpc_auth_context* context);

// Adds a property to the authentication context
GRPCAPI void grpc_auth_context_add_property(grpc_auth_context* ctx,
                                            const char* name, const char* value,
                                            size_t value_length);

// Adds a null-terminated string property to the authentication context
GRPCAPI void grpc_auth_context_add_cstring_property(grpc_auth_context* ctx,
                                                    const char* name,
                                                    const char* value);

// Sets the property name that represents peer identity (returns 1 on success)
GRPCAPI int grpc_auth_context_set_peer_identity_property_name(
    grpc_auth_context* ctx, const char* name);

// Opaque structure representing authorization policy provider
typedef struct grpc_authorization_policy_provider
    grpc_authorization_policy_provider;

// Creates a static authorization policy provider from policy data
GRPCAPI grpc_authorization_policy_provider*
grpc_authorization_policy_provider_static_data_create(
    const char* authz_policy, grpc_status_code* code,
    const char** error_details);

// Creates a file-watcher based authorization policy provider
GRPCAPI grpc_authorization_policy_provider*
grpc_authorization_policy_provider_file_watcher_create(
    const char* authz_policy_path, unsigned int refresh_interval_sec,
    grpc_status_code* code, const char** error_details);

// Releases resources associated with an authorization policy provider
GRPCAPI void grpc_authorization_policy_provider_release(
    grpc_authorization_policy_provider* provider);

#ifdef __cplusplus
}
#endif

#endif  // GRPC_GRPC_SECURITY_H
```

The comments added explain:
1. The purpose of each structure and typedef
2. What each function does
3. The parameters and return values of functions
4. Important details about behavior (like what values indicate success/failure)
5. The relationship between different components (like iterators and contexts)

The comments maintain a consistent style and provide enough information for a developer to understand how to use these security-related components without needing to dive into the implementation details.