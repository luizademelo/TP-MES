Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header includes for fake credentials implementation
#include "src/core/credentials/transport/fake/fake_credentials.h"

// Platform-specific support and standard library includes
#include <grpc/support/port_platform.h>
#include <stdlib.h>

// Standard C++ includes
#include <memory>
#include <utility>

// Abseil string view support
#include "absl/strings/string_view.h"

// gRPC core includes
#include "src/core/call/metadata_batch.h"
#include "src/core/credentials/transport/fake/fake_security_connector.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/util/ref_counted_ptr.h"

// Creates a fake channel security connector using these credentials
// Arguments:
//   call_creds: Call credentials to associate with the connector
//   target: The target name for the channel
//   args: Channel arguments to use for the connector
// Returns:
//   A new fake channel security connector instance
grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_fake_channel_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target, grpc_core::ChannelArgs* args) {
  return grpc_fake_channel_security_connector_create(
      this->Ref(), std::move(call_creds), target, *args);
}

// Returns a unique type name for these fake credentials
// The name is created once and cached for subsequent calls
grpc_core::UniqueTypeName grpc_fake_channel_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Fake");
  return kFactory.Create();
}

// Compares this credentials instance with another
// Arguments:
//   other: The other credentials to compare against
// Returns:
//   Result of comparison (0 if equal, non-zero otherwise)
int grpc_fake_channel_credentials::cmp_impl(
    const grpc_channel_credentials* other) const {
  return grpc_core::QsortCompare(
      static_cast<const grpc_channel_credentials*>(this), other);
}

// Creates a fake server security connector using these credentials
// Arguments:
//   args: Channel arguments (unused in this fake implementation)
// Returns:
//   A new fake server security connector instance
grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_fake_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& ) {
  return grpc_fake_server_security_connector_create(this->Ref());
}

// Returns a unique type name for these fake server credentials
// The name is created once and cached for subsequent calls
grpc_core::UniqueTypeName grpc_fake_server_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Fake");
  return kFactory.Create();
}

// Creates and returns new fake channel credentials
// Returns:
//   A new instance of fake channel credentials
grpc_channel_credentials* grpc_fake_transport_security_credentials_create() {
  return new grpc_fake_channel_credentials();
}

// Creates and returns new fake server credentials
// Returns:
//   A new instance of fake server credentials
grpc_server_credentials*
grpc_fake_transport_security_server_credentials_create() {
  return new grpc_fake_server_credentials();
}

// Creates a channel argument for expected targets in fake security
// Arguments:
//   expected_targets: The expected targets string
// Returns:
//   A channel argument containing the expected targets
grpc_arg grpc_fake_transport_expected_targets_arg(char* expected_targets) {
  return grpc_channel_arg_string_create(
      const_cast<char*>(GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS),
      expected_targets);
}
```

The comments explain:
1. The purpose of each function
2. The parameters they accept
3. What they return
4. Any notable implementation details
5. The role of each type in the fake credentials system

The comments are placed directly above each function they describe and follow a consistent style. They provide enough information for a developer to understand what the code does without having to dive into the implementation details.