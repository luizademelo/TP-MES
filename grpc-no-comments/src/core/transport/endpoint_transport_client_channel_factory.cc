// Copyright 2025 gRPC authors.

#include "src/core/transport/endpoint_transport_client_channel_factory.h"

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"

namespace grpc_core::endpoint_transport_client_channel_factory_detail {

RefCountedPtr<Subchannel> GenericClientChannelFactory::CreateSubchannel(
    const grpc_resolved_address& address, const ChannelArgs& args) {
  absl::StatusOr<ChannelArgs> new_args = GetSecureNamingChannelArgs(args);
  if (!new_args.ok()) {
    LOG(ERROR) << "Failed to create channel args during subchannel creation: "
               << new_args.status() << "; Got args: " << args.ToString();
    return nullptr;
  }
  return Subchannel::Create(MakeConnector(), address, *new_args);
}

absl::StatusOr<ChannelArgs>
GenericClientChannelFactory::GetSecureNamingChannelArgs(ChannelArgs args) {
  auto* channel_credentials = args.GetObject<grpc_channel_credentials>();
  if (channel_credentials == nullptr) {
    return absl::InternalError("channel credentials missing for channel");
  }

  if (args.Contains(GRPC_ARG_SECURITY_CONNECTOR)) {
    return absl::InternalError(
        "security connector already present in channel args.");
  }

  std::optional<std::string> authority =
      args.GetOwnedString(GRPC_ARG_DEFAULT_AUTHORITY);
  if (!authority.has_value()) {
    return absl::InternalError("authority not present in channel args");
  }

  RefCountedPtr<grpc_channel_security_connector> subchannel_security_connector =
      channel_credentials->create_security_connector(
          nullptr, authority->c_str(), &args);
  if (subchannel_security_connector == nullptr) {
    return absl::InternalError(absl::StrFormat(
        "Failed to create subchannel for secure name '%s'", *authority));
  }
  return args.SetObject(std::move(subchannel_security_connector));
}

}
