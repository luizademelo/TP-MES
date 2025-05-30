// Copyright 2025 gRPC authors.

#include <grpc/grpc.h>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/server/server.h"

int grpc_server_add_http2_port(grpc_server* server, const char* addr,
                               grpc_server_credentials* creds) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::RefCountedPtr<grpc_server_security_connector> sc;
  grpc_core::Server* core_server = grpc_core::Server::FromC(server);
  grpc_core::ChannelArgs args = core_server->channel_args();
  GRPC_TRACE_LOG(api, INFO) << "grpc_server_add_http2_port(server=" << server
                            << ", addr=" << addr << ", creds=" << creds << ")";
  if (creds == nullptr) {
    LOG(ERROR)
        << "Failed to add port to server: No credentials specified for secure "
           "server port (creds==NULL)";
    return 0;
  }

  if (core_server->config_fetcher() != nullptr) {

    args = args.SetObject(creds->Ref());
  } else {
    sc = creds->create_security_connector(grpc_core::ChannelArgs());
    if (sc == nullptr) {
      LOG(ERROR) << "Unable to create secure server with credentials of type ",
          creds->type().name();
      return 0;
    }
    args = args.SetObject(creds->Ref()).SetObject(sc);
  }
  std::vector<absl::string_view> transport_preferences = absl::StrSplit(
      args.GetString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS).value_or("h2"),
      ',');
  if (transport_preferences.size() != 1) {
    LOG(ERROR) << "Failed to add port to server: "
                  "Only one preferred transport name is currently supported: "
                  "requested='"
               << *args.GetString(GRPC_ARG_PREFERRED_TRANSPORT_PROTOCOLS)
               << "'";
    return 0;
  }
  auto* transport = grpc_core::CoreConfiguration::Get()
                        .endpoint_transport_registry()
                        .GetTransport(transport_preferences[0]);
  if (transport == nullptr) {
    LOG(ERROR) << "Failed to add port to server: unknown protocol '"
               << transport_preferences[0] << "'";
    return 0;
  }
  auto r = transport->AddPort(core_server, addr, args);
  if (!r.ok()) {
    LOG(ERROR) << "Failed to add port to server: " << r.status().message();
    return 0;
  }
  return *r;
}
