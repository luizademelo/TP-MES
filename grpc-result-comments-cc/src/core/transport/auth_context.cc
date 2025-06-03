Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for auth context functionality
#include "src/core/transport/auth_context.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <algorithm>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/util/ref_counted_ptr.h"

// Releases a reference to an auth context. If the reference count reaches zero,
// the context is destroyed.
void grpc_auth_context_release(grpc_auth_context* context) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_release(context=" << context << ")";
  if (context == nullptr) return;
  context->Unref(DEBUG_LOCATION, "grpc_auth_context_unref");
}

// Static empty iterator used as a default return value
static grpc_auth_property_iterator empty_iterator = {nullptr, 0, nullptr};

// Returns the peer identity property name from the auth context
const char* grpc_auth_context_peer_identity_property_name(
    const grpc_auth_context* ctx) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_peer_identity_property_name(ctx=" << ctx << ")";
  return ctx->peer_identity_property_name();
}

// Sets the peer identity property name in the auth context after verifying
// the property exists. Returns 1 on success, 0 on failure.
int grpc_auth_context_set_peer_identity_property_name(grpc_auth_context* ctx,
                                                      const char* name) {
  grpc_auth_property_iterator it =
      grpc_auth_context_find_properties_by_name(ctx, name);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_set_peer_identity_property_name(ctx=" << ctx
      << ", name=" << name << ")";
  if (prop == nullptr) {
    LOG(ERROR) << "Property name " << (name != nullptr ? name : "NULL")
               << " not found in auth context.";
    return 0;
  }
  ctx->set_peer_identity_property_name(prop->name);
  return 1;
}

// Checks if the peer is authenticated in the given auth context
int grpc_auth_context_peer_is_authenticated(const grpc_auth_context* ctx) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_peer_is_authenticated(ctx=" << ctx << ")";
  return ctx->is_authenticated();
}

// Returns an iterator over all properties in the auth context
grpc_auth_property_iterator grpc_auth_context_property_iterator(
    const grpc_auth_context* ctx) {
  grpc_auth_property_iterator it = empty_iterator;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_property_iterator(ctx=" << ctx << ")";
  if (ctx == nullptr) return it;
  it.ctx = ctx;
  return it;
}

// Advances the property iterator and returns the next property.
// Handles chained auth contexts and property name filtering.
const grpc_auth_property* grpc_auth_property_iterator_next(
    grpc_auth_property_iterator* it) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_property_iterator_next(it=" << it << ")";
  if (it == nullptr || it->ctx == nullptr) return nullptr;
  while (it->index == it->ctx->properties().count) {
    if (it->ctx->chained() == nullptr) return nullptr;
    it->ctx = it->ctx->chained();
    it->index = 0;
  }
  if (it->name == nullptr) {
    return &it->ctx->properties().array[it->index++];
  } else {
    while (it->index < it->ctx->properties().count) {
      const grpc_auth_property* prop =
          &it->ctx->properties().array[it->index++];
      CHECK_NE(prop->name, nullptr);
      if (strcmp(it->name, prop->name) == 0) {
        return prop;
      }
    }

    return grpc_auth_property_iterator_next(it);
  }
}

// Returns an iterator for properties matching the given name
grpc_auth_property_iterator grpc_auth_context_find_properties_by_name(
    const grpc_auth_context* ctx, const char* name) {
  grpc_auth_property_iterator it = empty_iterator;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_find_properties_by_name(ctx=" << ctx
      << ", name=" << name << ")";
  if (ctx == nullptr || name == nullptr) return empty_iterator;
  it.ctx = ctx;
  it.name = name;
  return it;
}

// Returns an iterator for peer identity properties
grpc_auth_property_iterator grpc_auth_context_peer_identity(
    const grpc_auth_context* ctx) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_peer_identity(ctx=" << ctx << ")";
  if (ctx == nullptr) return empty_iterator;
  return grpc_auth_context_find_properties_by_name(
      ctx, ctx->peer_identity_property_name());
}

// Ensures the property array has sufficient capacity, growing it if necessary
void grpc_auth_context::ensure_capacity() {
  if (properties_.count == properties_.capacity) {
    properties_.capacity =
        std::max(properties_.capacity + 8, properties_.capacity * 2);
    properties_.array = static_cast<grpc_auth_property*>(gpr_realloc(
        properties_.array, properties_.capacity * sizeof(grpc_auth_property)));
  }
}

// Adds a property to the auth context with the given name and value
void grpc_auth_context::add_property(const char* name, const char* value,
                                     size_t value_length) {
  ensure_capacity();
  grpc_auth_property* prop = &properties_.array[properties_.count++];
  prop->name = gpr_strdup(name);
  prop->value = static_cast<char*>(gpr_malloc(value_length + 1));
  if (value != nullptr) {
    memcpy(prop->value, value, value_length);
  }
  prop->value[value_length] = '\0';
  prop->value_length = value_length;
}

// Public interface for adding a property to an auth context
void grpc_auth_context_add_property(grpc_auth_context* ctx, const char* name,
                                    const char* value, size_t value_length) {
  GRPC_TRACE_LOG(api, INFO) << absl::StrFormat(
      "grpc_auth_context_add_property(ctx=%p, name=%s, value=%*.*s, "
      "value_length=%lu)",
      ctx, name, (int)value_length, (int)value_length, value,
      (unsigned long)value_length);
  ctx->add_property(name, value, value_length);
}

// Adds a null-terminated string property to the auth context
void grpc_auth_context::add_cstring_property(const char* name,
                                             const char* value) {
  ensure_capacity();
  grpc_auth_property* prop = &properties_.array[properties_.count++];
  prop->name = gpr_strdup(name);
  prop->value = gpr_strdup(value);
  prop->value_length = strlen(value);
}

// Public interface for adding a null-terminated string property
void grpc_auth_context_add_cstring_property(grpc_auth_context* ctx,
                                            const char* name,
                                            const char* value) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_auth_context_add_cstring_property(ctx=" << ctx
      << ", name=" << name << ", value=" << value << ")";
  ctx->add_cstring_property(name, value);
}

// Resets a property by freeing its memory and zeroing its fields
void grpc_auth_property_reset(grpc_auth_property* property) {
  gpr_free(property->name);
  gpr_free(property->value);
  memset(property, 0, sizeof(grpc_auth_property));
}

// Channel argument handling functions for auth context

// Destroys an auth context when used as a channel argument
static void auth_context_pointer_arg_destroy(void* p) {
  if (p != nullptr) {
    static_cast<grpc_auth_context*>(p)->Unref(DEBUG_LOCATION,
                                              "auth_context_pointer_arg");
  }
}

// Copies an auth context when used as a channel argument
static void* auth_context_pointer_arg_copy(void* p) {
  auto* ctx = static_cast<grpc_auth_context*>(p);
  return ctx == nullptr
             ? nullptr
             : ctx->Ref(DEBUG_LOCATION, "auth_context_pointer_arg").release();
}

// Comparison function for auth context channel arguments
static int auth_context_pointer_cmp(void* a, void* b) {
  return grpc_core::QsortCompare(a, b);
}

// Vtable for auth context channel argument operations
static const grpc_arg_pointer_vtable auth_context_pointer_vtable = {
    auth_context_pointer_arg_copy, auth_context_pointer_arg_destroy,
    auth_context_pointer_cmp};

// Creates a channel argument from an auth context
grpc_arg grpc_auth_context_to_arg(grpc_auth_context* c) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_AUTH_CONTEXT_ARG), c,
      &auth_context_pointer_vtable);
}

// Retrieves an auth context from a channel argument
grpc_auth_context* grpc_auth_context_from_arg(const grpc_arg* arg) {
  if (strcmp(arg->key, GRPC_AUTH_CONTEXT_ARG) != 0) return nullptr;
  if (arg->type != GRPC_ARG_POINTER) {
    LOG(ERROR) << "Invalid type " << arg->type << " for arg "
               << GRPC_AUTH_CONTEXT_ARG;
    return nullptr;
  }
  return static_cast<grpc_auth_context*>(arg->value.pointer.p);
}

// Finds an auth context in channel args
grpc_auth_context* grpc_find_auth_context_in_args(
    const grpc_channel_args* args) {
  size_t i;
  if (args == nullptr) return nullptr;
  for (i = 0; i < args->num_args; i++) {
    grpc_auth_context* p = grpc_auth_context_from_arg(&args->args[i]);
    if (p != nullptr) return p;
  }
  return nullptr;
}
```