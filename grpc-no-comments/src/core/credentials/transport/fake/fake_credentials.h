
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_FAKE_FAKE_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_FAKE_FAKE_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/statusor.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS \
  "grpc.fake_security.expected_targets"

class grpc_fake_channel_credentials final : public grpc_channel_credentials {
 public:
  grpc_core::RefCountedPtr<grpc_channel_security_connector>
  create_security_connector(
      grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
      const char* target, grpc_core::ChannelArgs* args) override;

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

 private:
  int cmp_impl(const grpc_channel_credentials* other) const override;
};

class grpc_fake_server_credentials final : public grpc_server_credentials {
 public:
  grpc_core::RefCountedPtr<grpc_server_security_connector>
  create_security_connector(const grpc_core::ChannelArgs& ) override;

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }
};

grpc_channel_credentials* grpc_fake_transport_security_credentials_create(void);

grpc_server_credentials* grpc_fake_transport_security_server_credentials_create(
    void);

grpc_arg grpc_fake_transport_expected_targets_arg(char* expected_targets);

#endif
