
// Copyright 2024 gRPC authors.

#include "src/core/handshaker/endpoint_info/endpoint_info_handshaker.h"

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

namespace {

class EndpointInfoHandshaker : public Handshaker {
 public:
  absl::string_view name() const override { return "endpoint_info"; }

  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override {
    args->args = args->args
                     .Set(GRPC_ARG_ENDPOINT_LOCAL_ADDRESS,
                          grpc_endpoint_get_local_address(args->endpoint.get()))
                     .Set(GRPC_ARG_ENDPOINT_PEER_ADDRESS,
                          grpc_endpoint_get_peer(args->endpoint.get()));
    InvokeOnHandshakeDone(args, std::move(on_handshake_done), absl::OkStatus());
  }

  void Shutdown(grpc_error_handle ) override {}
};

class EndpointInfoHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& ,
                      grpc_pollset_set* ,
                      HandshakeManager* handshake_mgr) override {
    handshake_mgr->Add(MakeRefCounted<EndpointInfoHandshaker>());
  }

  HandshakerPriority Priority() override {

    return HandshakerPriority::kSecurityHandshakers;
  }
};

}

void RegisterEndpointInfoHandshaker(CoreConfiguration::Builder* builder) {
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_CLIENT, std::make_unique<EndpointInfoHandshakerFactory>());
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_SERVER, std::make_unique<EndpointInfoHandshakerFactory>());
}

}
