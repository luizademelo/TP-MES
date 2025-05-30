
// Copyright 2016 gRPC authors.

#include "src/core/credentials/transport/fake/fake_credentials.h"

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/credentials/transport/fake/fake_security_connector.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/util/ref_counted_ptr.h"

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_fake_channel_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target, grpc_core::ChannelArgs* args) {
  return grpc_fake_channel_security_connector_create(
      this->Ref(), std::move(call_creds), target, *args);
}

grpc_core::UniqueTypeName grpc_fake_channel_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Fake");
  return kFactory.Create();
}

int grpc_fake_channel_credentials::cmp_impl(
    const grpc_channel_credentials* other) const {

  return grpc_core::QsortCompare(
      static_cast<const grpc_channel_credentials*>(this), other);
}

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_fake_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& ) {
  return grpc_fake_server_security_connector_create(this->Ref());
}

grpc_core::UniqueTypeName grpc_fake_server_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Fake");
  return kFactory.Create();
}

grpc_channel_credentials* grpc_fake_transport_security_credentials_create() {
  return new grpc_fake_channel_credentials();
}

grpc_server_credentials*
grpc_fake_transport_security_server_credentials_create() {
  return new grpc_fake_server_credentials();
}

grpc_arg grpc_fake_transport_expected_targets_arg(char* expected_targets) {
  return grpc_channel_arg_string_create(
      const_cast<char*>(GRPC_ARG_FAKE_SECURITY_EXPECTED_TARGETS),
      expected_targets);
}
