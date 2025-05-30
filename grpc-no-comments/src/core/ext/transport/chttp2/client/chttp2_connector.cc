
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/client/chttp2_connector.h"

#include <grpc/grpc.h>
#include <grpc/grpc_posix.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice_buffer.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <stdint.h>

#include <string>
#include <type_traits>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "src/core/channelz/channelz.h"
#include "src/core/client_channel/client_channel_factory.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/client_channel/connector.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/insecure/insecure_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/handshaker/tcp_connect/tcp_connect_handshaker.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/surface/channel_create.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/transport/endpoint_transport_client_channel_factory.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

#include <fcntl.h>

#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/tcp_client_posix.h"

#endif

namespace grpc_core {

using ::grpc_event_engine::experimental::EventEngine;

namespace {
void NullThenSchedClosure(const DebugLocation& location, grpc_closure** closure,
                          grpc_error_handle error) {
  grpc_closure* c = *closure;
  *closure = nullptr;
  ExecCtx::Run(location, c, error);
}
}

void Chttp2Connector::Connect(const Args& args, Result* result,
                              grpc_closure* notify) {
  {
    MutexLock lock(&mu_);
    CHECK_EQ(notify_, nullptr);
    args_ = args;
    result_ = result;
    notify_ = notify;
    event_engine_ = args_.channel_args.GetObject<EventEngine>();
  }
  absl::StatusOr<std::string> address = grpc_sockaddr_to_uri(args.address);
  if (!address.ok()) {
    grpc_error_handle error = GRPC_ERROR_CREATE(address.status().ToString());
    NullThenSchedClosure(DEBUG_LOCATION, &notify_, error);
    return;
  }
  ChannelArgs channel_args =
      args_.channel_args
          .Set(GRPC_ARG_TCP_HANDSHAKER_RESOLVED_ADDRESS, address.value())
          .Set(GRPC_ARG_TCP_HANDSHAKER_BIND_ENDPOINT_TO_POLLSET, 1);
  handshake_mgr_ = MakeRefCounted<HandshakeManager>();
  CoreConfiguration::Get().handshaker_registry().AddHandshakers(
      HANDSHAKER_CLIENT, channel_args, args_.interested_parties,
      handshake_mgr_.get());
  handshake_mgr_->DoHandshake(
      nullptr, channel_args, args.deadline, nullptr,
      [self = RefAsSubclass<Chttp2Connector>()](
          absl::StatusOr<HandshakerArgs*> result) {
        self->OnHandshakeDone(std::move(result));
      });
}

void Chttp2Connector::Shutdown(grpc_error_handle error) {
  MutexLock lock(&mu_);
  shutdown_ = true;
  if (handshake_mgr_ != nullptr) {

    handshake_mgr_->Shutdown(error);
  }
}

void Chttp2Connector::OnHandshakeDone(absl::StatusOr<HandshakerArgs*> result) {
  MutexLock lock(&mu_);
  if (!result.ok() || shutdown_) {
    if (result.ok()) {
      result = GRPC_ERROR_CREATE("connector shutdown");
    }
    result_->Reset();
    NullThenSchedClosure(DEBUG_LOCATION, &notify_, result.status());
  } else if ((*result)->endpoint != nullptr) {
    result_->transport = grpc_create_chttp2_transport(
        (*result)->args, std::move((*result)->endpoint), true);
    CHECK_NE(result_->transport, nullptr);
    result_->channel_args = std::move((*result)->args);
    Ref().release();
    GRPC_CLOSURE_INIT(&on_receive_settings_, OnReceiveSettings, this,
                      grpc_schedule_on_exec_ctx);
    grpc_chttp2_transport_start_reading(
        result_->transport, (*result)->read_buffer.c_slice_buffer(),
        &on_receive_settings_, args_.interested_parties, nullptr);
    timer_handle_ = event_engine_->RunAfter(
        args_.deadline - Timestamp::Now(),
        [self = RefAsSubclass<Chttp2Connector>()]() mutable {
          ExecCtx exec_ctx;
          self->OnTimeout();

          self.reset();
        });
  } else {

    DCHECK((*result)->exit_early);
    NullThenSchedClosure(DEBUG_LOCATION, &notify_, result.status());
  }
  handshake_mgr_.reset();
}

void Chttp2Connector::OnReceiveSettings(void* arg, grpc_error_handle error) {
  Chttp2Connector* self = static_cast<Chttp2Connector*>(arg);
  {
    MutexLock lock(&self->mu_);
    if (!self->notify_error_.has_value()) {
      if (!error.ok()) {

        self->result_->Reset();
      }
      self->MaybeNotify(error);
      if (self->timer_handle_.has_value()) {
        if (self->event_engine_->Cancel(*self->timer_handle_)) {

          self->MaybeNotify(absl::OkStatus());
        }
        self->timer_handle_.reset();
      }
    } else {

      self->MaybeNotify(absl::OkStatus());
    }
  }
  self->Unref();
}

void Chttp2Connector::OnTimeout() {
  MutexLock lock(&mu_);
  timer_handle_.reset();
  if (!notify_error_.has_value()) {

    result_->Reset();
    MaybeNotify(GRPC_ERROR_CREATE(
        "connection attempt timed out before receiving SETTINGS frame"));
  } else {

    MaybeNotify(absl::OkStatus());
  }
}

void Chttp2Connector::MaybeNotify(grpc_error_handle error) {
  if (notify_error_.has_value()) {
    NullThenSchedClosure(DEBUG_LOCATION, &notify_, notify_error_.value());

    notify_error_.reset();
  } else {
    notify_error_ = error;
  }
}

absl::StatusOr<grpc_channel*> CreateHttp2Channel(std::string target,
                                                 const ChannelArgs& args) {
  auto r = ChannelCreate(
      target,
      args.SetObject(EndpointTransportClientChannelFactory<Chttp2Connector>()),
      GRPC_CLIENT_CHANNEL, nullptr);
  if (r.ok()) {
    return r->release()->c_ptr();
  } else {
    return r.status();
  }
}

}

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD
grpc_channel* grpc_channel_create_from_fd(const char* target, int fd,
                                          grpc_channel_credentials* creds,
                                          const grpc_channel_args* args) {
  grpc_core::ExecCtx exec_ctx;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_channel_create_from_fd(target=" << target << ", fd=" << fd
      << ", creds=" << creds << ", args=" << args << ")";

  if (creds == nullptr ||
      creds->type() != grpc_core::InsecureCredentials::Type()) {
    return grpc_lame_client_channel_create(
        target, GRPC_STATUS_INTERNAL,
        "Failed to create client channel due to invalid creds");
  }
  grpc_core::ChannelArgs final_args =
      grpc_core::CoreConfiguration::Get()
          .channel_args_preconditioning()
          .PreconditionChannelArgs(args)
          .SetIfUnset(GRPC_ARG_DEFAULT_AUTHORITY, "test.authority")
          .SetObject(creds->Ref());

  int flags = fcntl(fd, F_GETFL, 0);
  CHECK_EQ(fcntl(fd, F_SETFL, flags | O_NONBLOCK), 0);
  grpc_core::OrphanablePtr<grpc_endpoint> client(grpc_tcp_create_from_fd(
      grpc_fd_create(fd, "client", true),
      grpc_event_engine::experimental::ChannelArgsEndpointConfig(final_args),
      "fd-client"));
  grpc_core::Transport* transport =
      grpc_create_chttp2_transport(final_args, std::move(client), true);
  CHECK(transport);
  auto channel = grpc_core::ChannelCreate(
      target, final_args, GRPC_CLIENT_DIRECT_CHANNEL, transport);
  if (channel.ok()) {
    grpc_chttp2_transport_start_reading(transport, nullptr, nullptr, nullptr,
                                        nullptr);
    grpc_core::ExecCtx::Get()->Flush();
    return channel->release()->c_ptr();
  } else {
    transport->Orphan();
    return grpc_lame_client_channel_create(
        target, static_cast<grpc_status_code>(channel.status().code()),
        "Failed to create client channel");
  }
}

#else

grpc_channel* grpc_channel_create_from_fd(const char* ,
                                          int ,
                                          grpc_channel_credentials* ,
                                          const grpc_channel_args* ) {
  CHECK(0);
  return nullptr;
}

#endif
