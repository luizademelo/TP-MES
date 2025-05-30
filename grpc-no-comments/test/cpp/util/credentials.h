// Copyright 2024 The gRPC Authors

#ifndef GRPC_TEST_CPP_UTIL_CREDENTIALS_H
#define GRPC_TEST_CPP_UTIL_CREDENTIALS_H

#include <grpcpp/security/credentials.h>

#include "src/core/credentials/transport/fake/fake_credentials.h"

namespace grpc {
namespace testing {

class FakeTransportSecurityChannelCredentials : public ChannelCredentials {
 public:
  FakeTransportSecurityChannelCredentials()
      : ChannelCredentials(grpc_fake_transport_security_credentials_create()) {}
};

class TestCompositeChannelCredentials : public ChannelCredentials {
 public:
  TestCompositeChannelCredentials(grpc_channel_credentials* channel_creds,
                                  grpc_call_credentials* call_creds)
      : ChannelCredentials(grpc_composite_channel_credentials_create(
            channel_creds, call_creds, nullptr)) {}
};

}
}

#endif
