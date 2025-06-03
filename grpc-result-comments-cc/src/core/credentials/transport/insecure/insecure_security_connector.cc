Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/insecure/insecure_security_connector.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/local_transport_security.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

// Constant string defining the insecure transport security type
const char kInsecureTransportSecurityType[] = "insecure";

namespace {

// Creates and returns a reference-counted authentication context for insecure connections
// The context includes properties indicating:
// - The transport security type is "insecure"
// - The security level is "none"
RefCountedPtr<grpc_auth_context> MakeAuthContext() {
  auto ctx = MakeRefCounted<grpc_auth_context>(nullptr);
  grpc_auth_context_add_cstring_property(
      ctx.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
      kInsecureTransportSecurityType);
  const char* security_level = tsi_security_level_to_string(TSI_SECURITY_NONE);
  grpc_auth_context_add_property(ctx.get(),
                                 GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME,
                                 security_level, strlen(security_level));
  return ctx;
}

}  // namespace

// Test-only function to create an insecure auth context
RefCountedPtr<grpc_auth_context> TestOnlyMakeInsecureAuthContext() {
  return MakeAuthContext();
}

// Implementation of CheckCallHost for insecure channel security connector
// Always returns OK status since insecure connections don't verify hosts
ArenaPromise<absl::Status> InsecureChannelSecurityConnector::CheckCallHost(
    absl::string_view, grpc_auth_context*) {
  return ImmediateOkStatus();
}

// Adds handshakers for insecure channel security
// Creates a local TSI handshaker and adds it to the handshake manager
void InsecureChannelSecurityConnector::add_handshakers(
    const ChannelArgs& args, grpc_pollset_set* ,
    HandshakeManager* handshake_manager) {
  tsi_handshaker* handshaker = nullptr;

  CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
  handshake_manager->Add(SecurityHandshakerCreate(handshaker, this, args));
}

// Checks peer credentials for insecure channel
// Creates an insecure auth context and immediately invokes the callback with OK status
void InsecureChannelSecurityConnector::check_peer(
    tsi_peer peer, grpc_endpoint* , const ChannelArgs& ,
    RefCountedPtr<grpc_auth_context>* auth_context,
    grpc_closure* on_peer_checked) {
  *auth_context = MakeAuthContext();
  tsi_peer_destruct(&peer);
  ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, absl::OkStatus());
}

// Compares this security connector with another channel security connector
int InsecureChannelSecurityConnector::cmp(
    const grpc_security_connector* other_sc) const {
  return channel_security_connector_cmp(
      static_cast<const grpc_channel_security_connector*>(other_sc));
}

// Adds handshakers for insecure server security
// Creates a local TSI handshaker and adds it to the handshake manager
void InsecureServerSecurityConnector::add_handshakers(
    const ChannelArgs& args, grpc_pollset_set* ,
    HandshakeManager* handshake_manager) {
  tsi_handshaker* handshaker = nullptr;

  CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
  handshake_manager->Add(SecurityHandshakerCreate(handshaker, this, args));
}

// Checks peer credentials for insecure server
// Creates an insecure auth context and immediately invokes the callback with OK status
void InsecureServerSecurityConnector::check_peer(
    tsi_peer peer, grpc_endpoint* , const ChannelArgs& ,
    RefCountedPtr<grpc_auth_context>* auth_context,
    grpc_closure* on_peer_checked) {
  *auth_context = MakeAuthContext();
  tsi_peer_destruct(&peer);
  ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, absl::OkStatus());
}

// Compares this security connector with another server security connector
int InsecureServerSecurityConnector::cmp(
    const grpc_security_connector* other) const {
  return server_security_connector_cmp(
      static_cast<const grpc_server_security_connector*>(other));
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each function and class method
2. The key operations being performed
3. The security implications (or lack thereof) for insecure connections
4. The flow of data and control in critical operations
5. The relationship between different components
6. Special cases like test-only functions

The comments maintain a consistent style and provide enough information for future maintainers to understand the code without being overly verbose.