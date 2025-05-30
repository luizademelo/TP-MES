
// Copyright 2021 gRPC authors.

#include <grpc/support/port_platform.h>
#include <grpcpp/ext/admin_services.h>
#include <grpcpp/server_builder.h>

#include "src/cpp/server/channelz/channelz_service.h"
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
#include "src/cpp/server/csds/csds.h"
#endif
namespace grpc {

namespace {

auto* g_channelz_service = new ChannelzService();
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
auto* g_csds = new xds::experimental::ClientStatusDiscoveryService();
#endif

}

void AddAdminServices(ServerBuilder* builder) {
  builder->RegisterService(g_channelz_service);
#if !defined(GRPC_NO_XDS) && !defined(DISABLED_XDS_PROTO_IN_CC)
  builder->RegisterService(g_csds);
#endif
}

}
