
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/local/local_credentials.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/credentials/transport/local/local_security_connector.h"

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_local_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* target_name, grpc_core::ChannelArgs* args) {
  return grpc_local_channel_security_connector_create(
      this->Ref(), std::move(request_metadata_creds), *args, target_name);
}

grpc_core::UniqueTypeName grpc_local_credentials::type() const {
  static grpc_core::UniqueTypeName::Factory kFactory("Local");
  return kFactory.Create();
}

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_local_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& ) {
  return grpc_local_server_security_connector_create(this->Ref());
}

grpc_core::UniqueTypeName grpc_local_server_credentials::type() const {
  static grpc_core::UniqueTypeName::Factory kFactory("Local");
  return kFactory.Create();
}

grpc_local_credentials::grpc_local_credentials(
    grpc_local_connect_type connect_type)
    : connect_type_(connect_type) {}

grpc_channel_credentials* grpc_local_credentials_create(
    grpc_local_connect_type connect_type) {
  return new grpc_local_credentials(connect_type);
}

grpc_local_server_credentials::grpc_local_server_credentials(
    grpc_local_connect_type connect_type)
    : connect_type_(connect_type) {}

grpc_server_credentials* grpc_local_server_credentials_create(
    grpc_local_connect_type connect_type) {
  return new grpc_local_server_credentials(connect_type);
}
