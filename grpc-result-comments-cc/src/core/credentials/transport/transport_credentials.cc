Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for transport credentials functionality
#include "src/core/credentials/transport/transport_credentials.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/useful.h"

// Releases reference to channel credentials
// Args:
//   creds: Pointer to channel credentials to release
void grpc_channel_credentials_release(grpc_channel_credentials* creds) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_channel_credentials_release(creds=" << creds << ")";
  grpc_core::ExecCtx exec_ctx;
  if (creds) creds->Unref();
}

// Releases reference to call credentials
// Args:
//   creds: Pointer to call credentials to release
void grpc_call_credentials_release(grpc_call_credentials* creds) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_call_credentials_release(creds=" << creds << ")";
  grpc_core::ExecCtx exec_ctx;
  if (creds) creds->Unref();
}

// Destroys channel credentials pointer argument
// Args:
//   p: Void pointer to channel credentials to destroy
static void credentials_pointer_arg_destroy(void* p) {
  static_cast<grpc_channel_credentials*>(p)->Unref();
}

// Copies channel credentials pointer argument
// Args:
//   p: Void pointer to channel credentials to copy
// Returns:
//   New reference to copied credentials
static void* credentials_pointer_arg_copy(void* p) {
  return static_cast<grpc_channel_credentials*>(p)->Ref().release();
}

// Compares two channel credentials
// Args:
//   a: First credentials to compare
//   b: Second credentials to compare
// Returns:
//   Comparison result from credentials' cmp method
static int credentials_pointer_cmp(void* a, void* b) {
  return static_cast<const grpc_channel_credentials*>(a)->cmp(
      static_cast<const grpc_channel_credentials*>(b));
}

// Vtable for channel credentials pointer operations
static const grpc_arg_pointer_vtable credentials_pointer_vtable = {
    credentials_pointer_arg_copy, credentials_pointer_arg_destroy,
    credentials_pointer_cmp};

// Converts channel credentials to channel argument
// Args:
//   credentials: Channel credentials to convert
// Returns:
//   grpc_arg containing the credentials
grpc_arg grpc_channel_credentials_to_arg(
    grpc_channel_credentials* credentials) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_ARG_CHANNEL_CREDENTIALS), credentials,
      &credentials_pointer_vtable);
}

// Extracts channel credentials from channel argument
// Args:
//   arg: Channel argument to extract from
// Returns:
//   Extracted credentials or nullptr if invalid
grpc_channel_credentials* grpc_channel_credentials_from_arg(
    const grpc_arg* arg) {
  if (strcmp(arg->key, GRPC_ARG_CHANNEL_CREDENTIALS) != 0) return nullptr;
  if (arg->type != GRPC_ARG_POINTER) {
    LOG(ERROR) << "Invalid type " << arg->type << " for arg "
               << GRPC_ARG_CHANNEL_CREDENTIALS;
    return nullptr;
  }
  return static_cast<grpc_channel_credentials*>(arg->value.pointer.p);
}

// Finds channel credentials in channel arguments
// Args:
//   args: Channel arguments to search
// Returns:
//   First found credentials or nullptr if none found
grpc_channel_credentials* grpc_channel_credentials_find_in_args(
    const grpc_channel_args* args) {
  size_t i;
  if (args == nullptr) return nullptr;
  for (i = 0; i < args->num_args; i++) {
    grpc_channel_credentials* credentials =
        grpc_channel_credentials_from_arg(&args->args[i]);
    if (credentials != nullptr) return credentials;
  }
  return nullptr;
}

// Releases reference to server credentials
// Args:
//   creds: Pointer to server credentials to release
void grpc_server_credentials_release(grpc_server_credentials* creds) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_server_credentials_release(creds=" << creds << ")";
  grpc_core::ExecCtx exec_ctx;
  if (creds) creds->Unref();
}

// Sets auth metadata processor for server credentials
// Args:
//   processor: Auth metadata processor to set
void grpc_server_credentials::set_auth_metadata_processor(
    const grpc_auth_metadata_processor& processor) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_server_credentials_set_auth_metadata_processor(creds=" << this
      << ", processor=grpc_auth_metadata_processor { process: "
      << (void*)(intptr_t)processor.process << ", state: " << processor.state
      << " })";
  DestroyProcessor();
  processor_ = processor;
}

// Sets auth metadata processor for server credentials (C-style wrapper)
// Args:
//   creds: Server credentials to modify
//   processor: Auth metadata processor to set
void grpc_server_credentials_set_auth_metadata_processor(
    grpc_server_credentials* creds, grpc_auth_metadata_processor processor) {
  DCHECK_NE(creds, nullptr);
  creds->set_auth_metadata_processor(processor);
}

// Destroys server credentials pointer argument
// Args:
//   p: Void pointer to server credentials to destroy
static void server_credentials_pointer_arg_destroy(void* p) {
  static_cast<grpc_server_credentials*>(p)->Unref();
}

// Copies server credentials pointer argument
// Args:
//   p: Void pointer to server credentials to copy
// Returns:
//   New reference to copied credentials
static void* server_credentials_pointer_arg_copy(void* p) {
  return static_cast<grpc_server_credentials*>(p)->Ref().release();
}

// Compares two server credentials pointers
// Args:
//   a: First pointer to compare
//   b: Second pointer to compare
// Returns:
//   Result of pointer comparison
static int server_credentials_pointer_cmp(void* a, void* b) {
  return grpc_core::QsortCompare(a, b);
}

// Vtable for server credentials pointer operations
static const grpc_arg_pointer_vtable cred_ptr_vtable = {
    server_credentials_pointer_arg_copy, server_credentials_pointer_arg_destroy,
    server_credentials_pointer_cmp};

// Converts server credentials to channel argument
// Args:
//   c: Server credentials to convert
// Returns:
//   grpc_arg containing the credentials
grpc_arg grpc_server_credentials_to_arg(grpc_server_credentials* c) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_SERVER_CREDENTIALS_ARG), c, &cred_ptr_vtable);
}

// Extracts server credentials from channel argument
// Args:
//   arg: Channel argument to extract from
// Returns:
//   Extracted credentials or nullptr if invalid
grpc_server_credentials* grpc_server_credentials_from_arg(const grpc_arg* arg) {
  if (strcmp(arg->key, GRPC_SERVER_CREDENTIALS_ARG) != 0) return nullptr;
  if (arg->type != GRPC_ARG_POINTER) {
    LOG(ERROR) << "Invalid type " << arg->type << " for arg "
               << GRPC_SERVER_CREDENTIALS_ARG;
    return nullptr;
  }
  return static_cast<grpc_server_credentials*>(arg->value.pointer.p);
}

// Finds server credentials in channel arguments
// Args:
//   args: Channel arguments to search
// Returns:
//   First found credentials or nullptr if none found
grpc_server_credentials* grpc_find_server_credentials_in_args(
    const grpc_channel_args* args) {
  size_t i;
  if (args == nullptr) return nullptr;
  for (i = 0; i < args->num_args; i++) {
    grpc_server_credentials* p =
        grpc_server_credentials_from_arg(&args->args[i]);
    if (p != nullptr) return p;
  }
  return nullptr;
}
```