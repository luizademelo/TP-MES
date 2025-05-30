
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_INSECURE_INSECURE_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_INSECURE_INSECURE_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

class InsecureCredentials final : public grpc_channel_credentials {
 public:
  RefCountedPtr<grpc_channel_security_connector> create_security_connector(
      RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* , ChannelArgs* ) override;

  static UniqueTypeName Type();

  UniqueTypeName type() const override { return Type(); }

 private:
  int cmp_impl(const grpc_channel_credentials* other) const override;
};

class InsecureServerCredentials final : public grpc_server_credentials {
 public:
  RefCountedPtr<grpc_server_security_connector> create_security_connector(
      const ChannelArgs& ) override;

  static UniqueTypeName Type();

  UniqueTypeName type() const override { return Type(); }
};

}

#endif
