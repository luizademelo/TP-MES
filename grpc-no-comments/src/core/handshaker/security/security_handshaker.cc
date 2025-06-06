
// Copyright 2015 gRPC authors.

#include "src/core/handshaker/security/security_handshaker.h"

#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/channelz/channelz.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/handshaker/security/secure_endpoint.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/transport_security_grpc.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"

#define GRPC_INITIAL_HANDSHAKE_BUFFER_SIZE 256

namespace grpc_core {

namespace {

class SecurityHandshaker : public Handshaker {
 public:
  SecurityHandshaker(tsi_handshaker* handshaker,
                     grpc_security_connector* connector,
                     const ChannelArgs& args);
  ~SecurityHandshaker() override;
  absl::string_view name() const override { return "security"; }
  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override;
  void Shutdown(absl::Status error) override;

 private:
  grpc_error_handle DoHandshakerNextLocked(const unsigned char* bytes_received,
                                           size_t bytes_received_size)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  grpc_error_handle OnHandshakeNextDoneLocked(
      tsi_result result, const unsigned char* bytes_to_send,
      size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void HandshakeFailedLocked(absl::Status error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void Finish(absl::Status status);

  void OnHandshakeDataReceivedFromPeerFn(absl::Status error);
  void OnHandshakeDataSentToPeerFn(absl::Status error);
  void OnHandshakeDataReceivedFromPeerFnScheduler(grpc_error_handle error);
  void OnHandshakeDataSentToPeerFnScheduler(grpc_error_handle error);
  static void OnHandshakeNextDoneGrpcWrapper(
      tsi_result result, void* user_data, const unsigned char* bytes_to_send,
      size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result);
  void OnPeerCheckedFn(grpc_error_handle error);
  size_t MoveReadBufferIntoHandshakeBuffer();
  grpc_error_handle CheckPeerLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  tsi_handshaker* handshaker_;
  RefCountedPtr<grpc_security_connector> connector_;

  Mutex mu_;

  bool is_shutdown_ = false;

  HandshakerArgs* args_ = nullptr;
  absl::AnyInvocable<void(absl::Status)> on_handshake_done_;

  size_t handshake_buffer_size_;
  unsigned char* handshake_buffer_;
  SliceBuffer outgoing_;
  RefCountedPtr<grpc_auth_context> auth_context_;
  tsi_handshaker_result* handshaker_result_ = nullptr;
  size_t max_frame_size_ = 0;
  std::string tsi_handshake_error_;
  grpc_closure* on_peer_checked_ ABSL_GUARDED_BY(mu_) = nullptr;
};

SecurityHandshaker::SecurityHandshaker(tsi_handshaker* handshaker,
                                       grpc_security_connector* connector,
                                       const ChannelArgs& args)
    : handshaker_(handshaker),
      connector_(connector->Ref(DEBUG_LOCATION, "handshake")),
      handshake_buffer_size_(GRPC_INITIAL_HANDSHAKE_BUFFER_SIZE),
      handshake_buffer_(
          static_cast<uint8_t*>(gpr_malloc(handshake_buffer_size_))),
      max_frame_size_(
          std::max(0, args.GetInt(GRPC_ARG_TSI_MAX_FRAME_SIZE).value_or(0))) {}

SecurityHandshaker::~SecurityHandshaker() {
  tsi_handshaker_destroy(handshaker_);
  tsi_handshaker_result_destroy(handshaker_result_);
  gpr_free(handshake_buffer_);
  auth_context_.reset(DEBUG_LOCATION, "handshake");
  connector_.reset(DEBUG_LOCATION, "handshake");
}

size_t SecurityHandshaker::MoveReadBufferIntoHandshakeBuffer() {
  size_t bytes_in_read_buffer = args_->read_buffer.Length();
  if (handshake_buffer_size_ < bytes_in_read_buffer) {
    handshake_buffer_ = static_cast<uint8_t*>(
        gpr_realloc(handshake_buffer_, bytes_in_read_buffer));
    handshake_buffer_size_ = bytes_in_read_buffer;
  }
  size_t offset = 0;
  while (args_->read_buffer.Count() > 0) {
    Slice slice = args_->read_buffer.TakeFirst();
    memcpy(handshake_buffer_ + offset, slice.data(), slice.size());
    offset += slice.size();
  }
  return bytes_in_read_buffer;
}

void SecurityHandshaker::HandshakeFailedLocked(absl::Status error) {
  if (error.ok()) {

    error = GRPC_ERROR_CREATE("Handshaker shutdown");
  }
  if (!is_shutdown_) {
    tsi_handshaker_shutdown(handshaker_);

    is_shutdown_ = true;
  }

  Finish(std::move(error));
}

void SecurityHandshaker::Finish(absl::Status status) {
  InvokeOnHandshakeDone(args_, std::move(on_handshake_done_),
                        std::move(status));
}

namespace {

RefCountedPtr<channelz::SocketNode::Security>
MakeChannelzSecurityFromAuthContext(grpc_auth_context* auth_context) {
  RefCountedPtr<channelz::SocketNode::Security> security =
      MakeRefCounted<channelz::SocketNode::Security>();

  security->type = channelz::SocketNode::Security::ModelType::kTls;
  security->tls = std::make_optional<channelz::SocketNode::Security::Tls>();
  grpc_auth_property_iterator it = grpc_auth_context_find_properties_by_name(
      auth_context, GRPC_X509_PEM_CERT_PROPERTY_NAME);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  if (prop != nullptr) {
    security->tls->remote_certificate =
        std::string(prop->value, prop->value_length);
  }
  return security;
}

}

void SecurityHandshaker::OnPeerCheckedFn(grpc_error_handle error) {
  MutexLock lock(&mu_);
  on_peer_checked_ = nullptr;
  if (!error.ok() || is_shutdown_) {
    HandshakeFailedLocked(error);
    return;
  }

  const unsigned char* unused_bytes = nullptr;
  size_t unused_bytes_size = 0;
  tsi_result result = tsi_handshaker_result_get_unused_bytes(
      handshaker_result_, &unused_bytes, &unused_bytes_size);
  if (result != TSI_OK) {
    HandshakeFailedLocked(GRPC_ERROR_CREATE(
        absl::StrCat("TSI handshaker result does not provide unused bytes (",
                     tsi_result_to_string(result), ")")));
    return;
  }

  tsi_frame_protector_type frame_protector_type;
  result = tsi_handshaker_result_get_frame_protector_type(
      handshaker_result_, &frame_protector_type);
  if (result != TSI_OK) {
    HandshakeFailedLocked(GRPC_ERROR_CREATE(
        absl::StrCat("TSI handshaker result does not implement "
                     "get_frame_protector_type (",
                     tsi_result_to_string(result), ")")));
    return;
  }
  tsi_zero_copy_grpc_protector* zero_copy_protector = nullptr;
  tsi_frame_protector* protector = nullptr;
  switch (frame_protector_type) {
    case TSI_FRAME_PROTECTOR_ZERO_COPY:
      [[fallthrough]];
    case TSI_FRAME_PROTECTOR_NORMAL_OR_ZERO_COPY:

      result = tsi_handshaker_result_create_zero_copy_grpc_protector(
          handshaker_result_, max_frame_size_ == 0 ? nullptr : &max_frame_size_,
          &zero_copy_protector);
      if (result != TSI_OK) {
        HandshakeFailedLocked(GRPC_ERROR_CREATE(
            absl::StrCat("Zero-copy frame protector creation failed (",
                         tsi_result_to_string(result), ")")));
        return;
      }
      break;
    case TSI_FRAME_PROTECTOR_NORMAL:

      result = tsi_handshaker_result_create_frame_protector(
          handshaker_result_, max_frame_size_ == 0 ? nullptr : &max_frame_size_,
          &protector);
      if (result != TSI_OK) {
        HandshakeFailedLocked(
            GRPC_ERROR_CREATE(absl::StrCat("Frame protector creation failed (",
                                           tsi_result_to_string(result), ")")));
        return;
      }
      break;
    case TSI_FRAME_PROTECTOR_NONE:
      break;
  }
  bool has_frame_protector =
      zero_copy_protector != nullptr || protector != nullptr;

  if (has_frame_protector) {
    if (unused_bytes_size > 0) {
      grpc_slice slice = grpc_slice_from_copied_buffer(
          reinterpret_cast<const char*>(unused_bytes), unused_bytes_size);
      args_->endpoint = grpc_secure_endpoint_create(
          protector, zero_copy_protector, std::move(args_->endpoint), &slice, 1,
          args_->args);
      CSliceUnref(slice);
    } else {
      args_->endpoint = grpc_secure_endpoint_create(
          protector, zero_copy_protector, std::move(args_->endpoint), nullptr,
          0, args_->args);
    }
  } else if (unused_bytes_size > 0) {

    args_->read_buffer.Append(Slice::FromCopiedBuffer(
        reinterpret_cast<const char*>(unused_bytes), unused_bytes_size));
  }

  tsi_handshaker_result_destroy(handshaker_result_);
  handshaker_result_ = nullptr;
  args_->args = args_->args.SetObject(auth_context_);

  if (has_frame_protector) {
    args_->args = args_->args.SetObject(
        MakeChannelzSecurityFromAuthContext(auth_context_.get()));
  }

  is_shutdown_ = true;

  Finish(absl::OkStatus());
}

grpc_error_handle SecurityHandshaker::CheckPeerLocked() {
  tsi_peer peer;
  tsi_result result =
      tsi_handshaker_result_extract_peer(handshaker_result_, &peer);
  if (result != TSI_OK) {
    return GRPC_ERROR_CREATE(absl::StrCat("Peer extraction failed (",
                                          tsi_result_to_string(result), ")"));
  }
  on_peer_checked_ = NewClosure(
      [self = RefAsSubclass<SecurityHandshaker>()](absl::Status status) {
        self->OnPeerCheckedFn(std::move(status));
      });
  connector_->check_peer(peer, args_->endpoint.get(), args_->args,
                         &auth_context_, on_peer_checked_);
  grpc_auth_property_iterator it = grpc_auth_context_find_properties_by_name(
      auth_context_.get(), GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  if (!prop ||
      !strcmp(tsi_security_level_to_string(TSI_SECURITY_NONE), prop->value)) {
    global_stats().IncrementInsecureConnectionsCreated();
  }
  return absl::OkStatus();
}

grpc_error_handle SecurityHandshaker::OnHandshakeNextDoneLocked(
    tsi_result result, const unsigned char* bytes_to_send,
    size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result) {
  grpc_error_handle error;

  if (is_shutdown_) {
    tsi_handshaker_result_destroy(handshaker_result);
    return GRPC_ERROR_CREATE("Handshaker shutdown");
  }

  if (result == TSI_INCOMPLETE_DATA) {
    CHECK_EQ(bytes_to_send_size, 0u);
    grpc_endpoint_read(
        args_->endpoint.get(), args_->read_buffer.c_slice_buffer(),
        NewClosure([self = RefAsSubclass<SecurityHandshaker>()](
                       absl::Status status) {
          self->OnHandshakeDataReceivedFromPeerFnScheduler(std::move(status));
        }),
        true, 1);
    return error;
  }
  if (result != TSI_OK) {

    return GRPC_ERROR_CREATE(absl::StrCat(
        connector_->type().name(), " handshake failed (",
        tsi_result_to_string(result), ")",
        (tsi_handshake_error_.empty() ? "" : ": "), tsi_handshake_error_));
  }

  if (handshaker_result != nullptr) {
    CHECK_EQ(handshaker_result_, nullptr);
    handshaker_result_ = handshaker_result;
  }
  if (bytes_to_send_size > 0) {

    outgoing_.Clear();
    outgoing_.Append(Slice::FromCopiedBuffer(
        reinterpret_cast<const char*>(bytes_to_send), bytes_to_send_size));
    grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs
        write_args;
    write_args.set_max_frame_size(INT_MAX);
    grpc_endpoint_write(
        args_->endpoint.get(), outgoing_.c_slice_buffer(),
        NewClosure(
            [self = RefAsSubclass<SecurityHandshaker>()](absl::Status status) {
              self->OnHandshakeDataSentToPeerFnScheduler(std::move(status));
            }),
        std::move(write_args));
  } else if (handshaker_result == nullptr) {

    grpc_endpoint_read(
        args_->endpoint.get(), args_->read_buffer.c_slice_buffer(),
        NewClosure([self = RefAsSubclass<SecurityHandshaker>()](
                       absl::Status status) {
          self->OnHandshakeDataReceivedFromPeerFnScheduler(std::move(status));
        }),
        true, 1);
  } else {

    error = CheckPeerLocked();
  }
  return error;
}

void SecurityHandshaker::OnHandshakeNextDoneGrpcWrapper(
    tsi_result result, void* user_data, const unsigned char* bytes_to_send,
    size_t bytes_to_send_size, tsi_handshaker_result* handshaker_result) {
  RefCountedPtr<SecurityHandshaker> h(
      static_cast<SecurityHandshaker*>(user_data));
  MutexLock lock(&h->mu_);
  grpc_error_handle error = h->OnHandshakeNextDoneLocked(
      result, bytes_to_send, bytes_to_send_size, handshaker_result);
  if (!error.ok()) {
    h->HandshakeFailedLocked(std::move(error));
  }
}

grpc_error_handle SecurityHandshaker::DoHandshakerNextLocked(
    const unsigned char* bytes_received, size_t bytes_received_size) {

  const unsigned char* bytes_to_send = nullptr;
  size_t bytes_to_send_size = 0;
  tsi_handshaker_result* hs_result = nullptr;
  auto self = RefAsSubclass<SecurityHandshaker>();
  tsi_result result = tsi_handshaker_next(
      handshaker_, bytes_received, bytes_received_size, &bytes_to_send,
      &bytes_to_send_size, &hs_result, &OnHandshakeNextDoneGrpcWrapper,
      self.get(), &tsi_handshake_error_);
  if (result == TSI_ASYNC) {

    self.release();
    return absl::OkStatus();
  }

  return OnHandshakeNextDoneLocked(result, bytes_to_send, bytes_to_send_size,
                                   hs_result);
}

void SecurityHandshaker::OnHandshakeDataReceivedFromPeerFnScheduler(
    grpc_error_handle error) {
  args_->event_engine->Run([self = RefAsSubclass<SecurityHandshaker>(),
                            error = std::move(error)]() mutable {
    ExecCtx exec_ctx;
    self->OnHandshakeDataReceivedFromPeerFn(std::move(error));

    self.reset();
  });
}

void SecurityHandshaker::OnHandshakeDataReceivedFromPeerFn(absl::Status error) {
  MutexLock lock(&mu_);
  if (!error.ok() || is_shutdown_) {
    HandshakeFailedLocked(
        GRPC_ERROR_CREATE_REFERENCING("Handshake read failed", &error, 1));
    return;
  }

  size_t bytes_received_size = MoveReadBufferIntoHandshakeBuffer();

  error = DoHandshakerNextLocked(handshake_buffer_, bytes_received_size);
  if (!error.ok()) {
    HandshakeFailedLocked(std::move(error));
  }
}

void SecurityHandshaker::OnHandshakeDataSentToPeerFnScheduler(
    grpc_error_handle error) {
  args_->event_engine->Run([self = RefAsSubclass<SecurityHandshaker>(),
                            error = std::move(error)]() mutable {
    ExecCtx exec_ctx;
    self->OnHandshakeDataSentToPeerFn(std::move(error));

    self.reset();
  });
}

void SecurityHandshaker::OnHandshakeDataSentToPeerFn(absl::Status error) {
  MutexLock lock(&mu_);
  if (!error.ok() || is_shutdown_) {
    HandshakeFailedLocked(
        GRPC_ERROR_CREATE_REFERENCING("Handshake write failed", &error, 1));
    return;
  }

  if (handshaker_result_ == nullptr) {
    grpc_endpoint_read(
        args_->endpoint.get(), args_->read_buffer.c_slice_buffer(),
        NewClosure([self = RefAsSubclass<SecurityHandshaker>()](
                       absl::Status status) {
          self->OnHandshakeDataReceivedFromPeerFnScheduler(std::move(status));
        }),
        true, 1);
  } else {
    error = CheckPeerLocked();
    if (!error.ok()) {
      HandshakeFailedLocked(error);
      return;
    }
  }
}

void SecurityHandshaker::Shutdown(grpc_error_handle error) {
  MutexLock lock(&mu_);
  if (!is_shutdown_) {
    is_shutdown_ = true;
    connector_->cancel_check_peer(on_peer_checked_, std::move(error));
    tsi_handshaker_shutdown(handshaker_);
    args_->endpoint.reset();
  }
}

void SecurityHandshaker::DoHandshake(
    HandshakerArgs* args,
    absl::AnyInvocable<void(absl::Status)> on_handshake_done) {
  MutexLock lock(&mu_);
  args_ = args;
  on_handshake_done_ = std::move(on_handshake_done);
  size_t bytes_received_size = MoveReadBufferIntoHandshakeBuffer();
  grpc_error_handle error =
      DoHandshakerNextLocked(handshake_buffer_, bytes_received_size);
  if (!error.ok()) {
    HandshakeFailedLocked(error);
  }
}

class FailHandshaker : public Handshaker {
 public:
  explicit FailHandshaker(absl::Status status) : status_(std::move(status)) {}
  absl::string_view name() const override { return "security_fail"; }
  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override {
    InvokeOnHandshakeDone(args, std::move(on_handshake_done), status_);
  }
  void Shutdown(absl::Status ) override {}

 private:
  ~FailHandshaker() override = default;
  absl::Status status_;
};

class ClientSecurityHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& args,
                      grpc_pollset_set* interested_parties,
                      HandshakeManager* handshake_mgr) override {
    auto* security_connector =
        args.GetObject<grpc_channel_security_connector>();
    if (security_connector) {
      security_connector->add_handshakers(args, interested_parties,
                                          handshake_mgr);
    }
  }
  HandshakerPriority Priority() override {
    return HandshakerPriority::kSecurityHandshakers;
  }
  ~ClientSecurityHandshakerFactory() override = default;
};

class ServerSecurityHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& args,
                      grpc_pollset_set* interested_parties,
                      HandshakeManager* handshake_mgr) override {
    auto* security_connector = args.GetObject<grpc_server_security_connector>();
    if (security_connector) {
      security_connector->add_handshakers(args, interested_parties,
                                          handshake_mgr);
    }
  }
  HandshakerPriority Priority() override {
    return HandshakerPriority::kSecurityHandshakers;
  }
  ~ServerSecurityHandshakerFactory() override = default;
};

}

RefCountedPtr<Handshaker> SecurityHandshakerCreate(
    absl::StatusOr<tsi_handshaker*> handshaker,
    grpc_security_connector* connector, const ChannelArgs& args) {

  if (!handshaker.ok()) {
    return MakeRefCounted<FailHandshaker>(
        absl::Status(handshaker.status().code(),
                     absl::StrCat("Failed to create security handshaker: ",
                                  handshaker.status().message())));
  } else if (*handshaker == nullptr) {

    return MakeRefCounted<FailHandshaker>(
        absl::UnknownError("Failed to create security handshaker."));
  } else {
    return MakeRefCounted<SecurityHandshaker>(*handshaker, connector, args);
  }
}

void SecurityRegisterHandshakerFactories(CoreConfiguration::Builder* builder) {
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_CLIENT, std::make_unique<ClientSecurityHandshakerFactory>());
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_SERVER, std::make_unique<ServerSecurityHandshakerFactory>());
}

}
