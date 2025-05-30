
// Copyright 2022 gRPC authors.

#include "src/core/handshaker/tcp_connect/tcp_connect_handshaker.h"

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/uri.h"

namespace grpc_core {

namespace {

class TCPConnectHandshaker : public Handshaker {
 public:
  explicit TCPConnectHandshaker(grpc_pollset_set* pollset_set);
  absl::string_view name() const override { return "tcp_connect"; }
  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override;
  void Shutdown(absl::Status error) override;

 private:
  ~TCPConnectHandshaker() override;
  void FinishLocked(absl::Status error) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  static void Connected(void* arg, grpc_error_handle error);

  Mutex mu_;
  bool shutdown_ ABSL_GUARDED_BY(mu_) = false;

  grpc_endpoint* endpoint_to_destroy_ ABSL_GUARDED_BY(mu_) = nullptr;
  absl::AnyInvocable<void(absl::Status)> on_handshake_done_
      ABSL_GUARDED_BY(mu_);
  grpc_pollset_set* interested_parties_ = nullptr;
  grpc_polling_entity pollent_;
  HandshakerArgs* args_ = nullptr;
  bool bind_endpoint_to_pollset_ = false;
  grpc_resolved_address addr_;
  grpc_closure connected_;
};

TCPConnectHandshaker::TCPConnectHandshaker(grpc_pollset_set* pollset_set)
    : interested_parties_(grpc_pollset_set_create()),
      pollent_(grpc_polling_entity_create_from_pollset_set(pollset_set)) {

  if (interested_parties_ != nullptr) {
    grpc_polling_entity_add_to_pollset_set(&pollent_, interested_parties_);
  }
  GRPC_CLOSURE_INIT(&connected_, Connected, this, grpc_schedule_on_exec_ctx);
}

void TCPConnectHandshaker::Shutdown(absl::Status ) {

  MutexLock lock(&mu_);
  if (!shutdown_) {
    shutdown_ = true;

    if (on_handshake_done_ != nullptr) {

      FinishLocked(GRPC_ERROR_CREATE("tcp handshaker shutdown"));
    }
  }
}

void TCPConnectHandshaker::DoHandshake(
    HandshakerArgs* args,
    absl::AnyInvocable<void(absl::Status)> on_handshake_done) {
  {
    MutexLock lock(&mu_);
    on_handshake_done_ = std::move(on_handshake_done);
  }
  CHECK_EQ(args->endpoint.get(), nullptr);
  args_ = args;
  absl::string_view resolved_address_text =
      args->args.GetString(GRPC_ARG_TCP_HANDSHAKER_RESOLVED_ADDRESS).value();
  absl::StatusOr<URI> uri = URI::Parse(resolved_address_text);
  if (!uri.ok() || !grpc_parse_uri(*uri, &addr_)) {
    MutexLock lock(&mu_);
    FinishLocked(GRPC_ERROR_CREATE(absl::StrCat(
        "Resolved address in invalid format: ", resolved_address_text)));
    return;
  }
  bind_endpoint_to_pollset_ =
      args->args.GetBool(GRPC_ARG_TCP_HANDSHAKER_BIND_ENDPOINT_TO_POLLSET)
          .value_or(false);

  args->args = args->args.Remove(GRPC_ARG_TCP_HANDSHAKER_RESOLVED_ADDRESS)
                   .Remove(GRPC_ARG_TCP_HANDSHAKER_BIND_ENDPOINT_TO_POLLSET);

  Ref().release();

  grpc_tcp_client_connect(
      &connected_, &endpoint_to_destroy_, interested_parties_,
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(args->args),
      &addr_, args->deadline);
}

void TCPConnectHandshaker::Connected(void* arg, grpc_error_handle error) {
  RefCountedPtr<TCPConnectHandshaker> self(
      static_cast<TCPConnectHandshaker*>(arg));
  {
    MutexLock lock(&self->mu_);
    if (!error.ok() || self->shutdown_) {
      if (error.ok()) {
        error = GRPC_ERROR_CREATE("tcp handshaker shutdown");
      }
      if (self->endpoint_to_destroy_ != nullptr) {
        grpc_endpoint_destroy(self->endpoint_to_destroy_);
        self->endpoint_to_destroy_ = nullptr;
      }
      if (!self->shutdown_) {
        self->shutdown_ = true;
        self->FinishLocked(std::move(error));
      } else {

      }
      return;
    }
    CHECK_NE(self->endpoint_to_destroy_, nullptr);
    self->args_->endpoint.reset(self->endpoint_to_destroy_);
    self->endpoint_to_destroy_ = nullptr;
    if (self->bind_endpoint_to_pollset_) {
      grpc_endpoint_add_to_pollset_set(self->args_->endpoint.get(),
                                       self->interested_parties_);
    }
    self->FinishLocked(absl::OkStatus());
  }
}

TCPConnectHandshaker::~TCPConnectHandshaker() {
  if (endpoint_to_destroy_ != nullptr) {
    grpc_endpoint_destroy(endpoint_to_destroy_);
  }
  grpc_pollset_set_destroy(interested_parties_);
}

void TCPConnectHandshaker::FinishLocked(absl::Status error) {
  if (interested_parties_ != nullptr) {
    grpc_polling_entity_del_from_pollset_set(&pollent_, interested_parties_);
  }
  InvokeOnHandshakeDone(args_, std::move(on_handshake_done_), std::move(error));
}

class TCPConnectHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& ,
                      grpc_pollset_set* interested_parties,
                      HandshakeManager* handshake_mgr) override {
    handshake_mgr->Add(
        MakeRefCounted<TCPConnectHandshaker>(interested_parties));
  }
  HandshakerPriority Priority() override {
    return HandshakerPriority::kTCPConnectHandshakers;
  }
  ~TCPConnectHandshakerFactory() override = default;
};

}

void RegisterTCPConnectHandshaker(CoreConfiguration::Builder* builder) {
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_CLIENT, std::make_unique<TCPConnectHandshakerFactory>());
}

}
