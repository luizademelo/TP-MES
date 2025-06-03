Here's the commented version of the code snippet:

```c++
// Copyright 2021 gRPC authors.

// Include necessary headers for platform support, admin services, and server building
#include <grpc/support/port_platform.h>
#include <grpcpp/ext/admin_services.h>
#include <grpcpp/server_builder.h>

// Include Channelz service implementation
#include "src/cpp/server/channelz/channelz_service.h"
// Conditionally include CSDS (Client Status Discovery Service) if XDS is enabled
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
#include "src/cpp/server/csds/csds.h"
#endif

namespace grpc {

namespace {
// Global instance of ChannelzService for collecting and exposing channel metrics
auto* g_channelz_service = new ChannelzService();

// Conditionally create global instance of CSDS when XDS is enabled
// CSDS provides client status information for xDS configurations
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
auto* g_csds = new xds::experimental::ClientStatusDiscoveryService();
#endif

}  // namespace

// Function to add admin services to a gRPC server
// @param builder Pointer to ServerBuilder instance that configures the server
void AddAdminServices(ServerBuilder* builder) {
  // Register the Channelz service with the server
  builder->RegisterService(g_channelz_service);
  
  // Conditionally register CSDS with the server if XDS is enabled
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
  builder->RegisterService(g_csds);
#endif
}

}  // namespace grpc
```

Key improvements made:
1. Added header documentation explaining their purpose
2. Documented the global service instances and their roles
3. Explained the conditional compilation for XDS-related functionality
4. Added detailed function documentation for AddAdminServices
5. Added parameter documentation
6. Added namespace closing comments for better readability
7. Explained what Channelz and CSDS services provide
8. Maintained all existing code structure while adding comments