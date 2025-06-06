
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_LOCAL_LOCAL_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_LOCAL_LOCAL_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

class grpc_local_credentials final : public grpc_channel_credentials {
 public:
  explicit grpc_local_credentials(grpc_local_connect_type connect_type);
  ~grpc_local_credentials() override = default;

  grpc_core::RefCountedPtr<grpc_channel_security_connector>
  create_security_connector(
      grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* target_name, grpc_core::ChannelArgs* args) override;

  grpc_core::UniqueTypeName type() const override;

  grpc_local_connect_type connect_type() const { return connect_type_; }

 private:
  int cmp_impl(const grpc_channel_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_channel_credentials*>(this), other);
  }

  grpc_local_connect_type connect_type_;
};

class grpc_local_server_credentials final : public grpc_server_credentials {
 public:
  explicit grpc_local_server_credentials(grpc_local_connect_type connect_type);
  ~grpc_local_server_credentials() override = default;

  grpc_core::RefCountedPtr<grpc_server_security_connector>
  create_security_connector(const grpc_core::ChannelArgs& ) override;

  grpc_core::UniqueTypeName type() const override;

  grpc_local_connect_type connect_type() const { return connect_type_; }

 private:
  grpc_local_connect_type connect_type_;
};

#endif
