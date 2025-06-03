Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for security connector functionality
#include "src/core/credentials/transport/security_connector.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/useful.h"

// Constructor for channel security connector
// Initializes with URL scheme, channel credentials, and request metadata credentials
grpc_channel_security_connector::grpc_channel_security_connector(
    absl::string_view url_scheme,
    grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds)
    : grpc_security_connector(url_scheme),
      channel_creds_(std::move(channel_creds)),
      request_metadata_creds_(std::move(request_metadata_creds)) {}

// Compares this channel security connector with another
// First compares channel credentials, then request metadata credentials if needed
int grpc_channel_security_connector::channel_security_connector_cmp(
    const grpc_channel_security_connector* other) const {
  const grpc_channel_security_connector* other_sc =
      static_cast<const grpc_channel_security_connector*>(other);
  CHECK_NE(channel_creds(), nullptr);
  CHECK_NE(other_sc->channel_creds(), nullptr);
  int c = channel_creds()->cmp(other_sc->channel_creds());
  if (c != 0) return c;
  return grpc_core::QsortCompare(request_metadata_creds(),
                                 other_sc->request_metadata_creds());
}

// Returns the type of the channel credentials
grpc_core::UniqueTypeName grpc_channel_security_connector::type() const {
  return channel_creds_->type();
}

// Constructor for server security connector
// Initializes with URL scheme and server credentials
grpc_server_security_connector::grpc_server_security_connector(
    absl::string_view url_scheme,
    grpc_core::RefCountedPtr<grpc_server_credentials> server_creds)
    : grpc_security_connector(url_scheme),
      server_creds_(std::move(server_creds)) {}

// Compares this server security connector with another
// Compares based on server credentials
int grpc_server_security_connector::server_security_connector_cmp(
    const grpc_server_security_connector* other) const {
  const grpc_server_security_connector* other_sc =
      static_cast<const grpc_server_security_connector*>(other);
  CHECK_NE(server_creds(), nullptr);
  CHECK_NE(other_sc->server_creds(), nullptr);
  return grpc_core::QsortCompare(server_creds(), other_sc->server_creds());
}

// Returns the type of the server credentials
grpc_core::UniqueTypeName grpc_server_security_connector::type() const {
  return server_creds_->type();
}

// Destroys a security connector when used as a channel argument
// Unreferences the connector if it's not null
static void connector_arg_destroy(void* p) {
  if (p == nullptr) return;
  static_cast<grpc_security_connector*>(p)->Unref(DEBUG_LOCATION,
                                                  "connector_arg_destroy");
}

// Copies a security connector when used as a channel argument
// References the connector if it's not null
static void* connector_arg_copy(void* p) {
  if (p == nullptr) return nullptr;
  return static_cast<grpc_security_connector*>(p)
      ->Ref(DEBUG_LOCATION, "connector_arg_copy")
      .release();
}

// Compares two security connectors when used as channel arguments
static int connector_cmp(void* a, void* b) {
  return static_cast<grpc_security_connector*>(a)->cmp(
      static_cast<grpc_security_connector*>(b));
}

// Vtable for handling security connectors as channel arguments
static const grpc_arg_pointer_vtable connector_arg_vtable = {
    connector_arg_copy, connector_arg_destroy, connector_cmp};

// Converts a security connector to a channel argument
grpc_arg grpc_security_connector_to_arg(grpc_security_connector* sc) {
  return grpc_channel_arg_pointer_create(
      const_cast<char*>(GRPC_ARG_SECURITY_CONNECTOR), sc,
      &connector_arg_vtable);
}

// Extracts a security connector from a channel argument
// Returns null if argument is not a security connector or has wrong type
grpc_security_connector* grpc_security_connector_from_arg(const grpc_arg* arg) {
  if (strcmp(arg->key, GRPC_ARG_SECURITY_CONNECTOR) != 0) return nullptr;
  if (arg->type != GRPC_ARG_POINTER) {
    LOG(ERROR) << "Invalid type " << arg->type << " for arg "
               << GRPC_ARG_SECURITY_CONNECTOR;
    return nullptr;
  }
  return static_cast<grpc_security_connector*>(arg->value.pointer.p);
}

// Finds a security connector in channel arguments
// Returns the first security connector found, or null if none exists
grpc_security_connector* grpc_security_connector_find_in_args(
    const grpc_channel_args* args) {
  size_t i;
  if (args == nullptr) return nullptr;
  for (i = 0; i < args->num_args; i++) {
    grpc_security_connector* sc =
        grpc_security_connector_from_arg(&args->args[i]);
    if (sc != nullptr) return sc;
  }
  return nullptr;
}
```