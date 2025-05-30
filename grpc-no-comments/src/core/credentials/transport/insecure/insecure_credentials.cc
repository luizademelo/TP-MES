
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/insecure/insecure_credentials.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/credentials/transport/insecure/insecure_security_connector.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

RefCountedPtr<grpc_channel_security_connector>
InsecureCredentials::create_security_connector(
    RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* , ChannelArgs* ) {
  return MakeRefCounted<InsecureChannelSecurityConnector>(
      Ref(), std::move(request_metadata_creds));
}

UniqueTypeName InsecureCredentials::Type() {
  static UniqueTypeName::Factory kFactory("Insecure");
  return kFactory.Create();
}

int InsecureCredentials::cmp_impl(
    const grpc_channel_credentials* ) const {

  return 0;
}

RefCountedPtr<grpc_server_security_connector>
InsecureServerCredentials::create_security_connector(
    const ChannelArgs& ) {
  return MakeRefCounted<InsecureServerSecurityConnector>(Ref());
}

UniqueTypeName InsecureServerCredentials::Type() {
  static auto* kFactory = new UniqueTypeName::Factory("Insecure");
  return kFactory->Create();
}

}

grpc_channel_credentials* grpc_insecure_credentials_create() {

  static auto* creds = new grpc_core::InsecureCredentials();
  return creds->Ref().release();
}

grpc_server_credentials* grpc_insecure_server_credentials_create() {
  return new grpc_core::InsecureServerCredentials();
}
