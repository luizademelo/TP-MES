Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for HTTP/2 server implementation
#include "src/core/ext/transport/chttp2/server/chttp2_server.h"

// Standard and gRPC library includes
#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/grpc_posix.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/passive_listener.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <string.h>

// STL includes
#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Abseil includes
#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"

// Core gRPC includes
#include "src/core/channelz/channelz.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/insecure/insecure_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/extensions/supports_fd.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/utils.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/iomgr/vsock.h"
#include "src/core/lib/resource_quota/connection_quota.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/server/server.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/match.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/uri.h"

// POSIX-specific includes for file descriptor support
#ifdef GPR_SUPPORT_CHANNELS_FROM_FD
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/tcp_client_posix.h"
#endif

namespace grpc_core {

// Using declarations for EventEngine components
using grpc_event_engine::experimental::ChannelArgsEndpointConfig;
using grpc_event_engine::experimental::EventEngine;
using grpc_event_engine::experimental::EventEngineSupportsFdExtension;
using grpc_event_engine::experimental::QueryExtension;
using http2::Http2ErrorCode;

// URI prefixes for different transport types
const char kUnixUriPrefix[] = "unix:";
const char kUnixAbstractUriPrefix[] = "unix-abstract:";
const char kVSockUriPrefix[] = "vsock:";

namespace {
// Helper function to get connection deadline from channel args
Timestamp GetConnectionDeadline(const ChannelArgs& args) {
  return Timestamp::Now() +
         std::max(
             Duration::Milliseconds(1),
             args.GetDurationFromIntMillis(GRPC_ARG_SERVER_HANDSHAKE_TIMEOUT_MS)
                 .value_or(Duration::Minutes(2)));
}
}

// Alias for TCP server acceptor pointer with custom deleter
using AcceptorPtr = std::unique_ptr<grpc_tcp_server_acceptor, AcceptorDeleter>;

// Implementation of HandshakingState for ActiveConnection
NewChttp2ServerListener::ActiveConnection::HandshakingState::HandshakingState(
    RefCountedPtr<ActiveConnection> connection_ref, grpc_tcp_server* tcp_server,
    grpc_pollset* accepting_pollset, AcceptorPtr acceptor,
    const ChannelArgs& args, OrphanablePtr<grpc_endpoint> endpoint)
    : InternallyRefCounted(
          GRPC_TRACE_FLAG_ENABLED(chttp2_server_refcount)
              ? "NewChttp2ServerListener::ActiveConnection::HandshakingState"
              : nullptr),
      connection_(std::move(connection_ref)),
      tcp_server_(tcp_server),
      accepting_pollset_(accepting_pollset),
      acceptor_(std::move(acceptor)),
      interested_parties_(grpc_pollset_set_create()),
      deadline_(GetConnectionDeadline(args)),
      endpoint_(std::move(endpoint)),
      handshake_mgr_(MakeRefCounted<HandshakeManager>()) {
  // Add accepting pollset to interested parties if it exists
  if (accepting_pollset != nullptr) {
    grpc_pollset_set_add_pollset(interested_parties_, accepting_pollset_);
  }
}

NewChttp2ServerListener::ActiveConnection::HandshakingState::
    ~HandshakingState() {
  // Cleanup pollset and TCP server references
  if (accepting_pollset_ != nullptr) {
    grpc_pollset_set_del_pollset(interested_parties_, accepting_pollset_);
  }
  grpc_pollset_set_destroy(interested_parties_);
  if (tcp_server_ != nullptr) {
    grpc_tcp_server_unref(tcp_server_);
  }
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::Orphan() {
  // Shutdown handshaking when orphaned
  connection_->work_serializer_.Run(
      [this] {
        ShutdownLocked(absl::UnavailableError("Listener stopped serving."));
        Unref();
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::StartLocked(
    const ChannelArgs& channel_args) {
  if (handshake_mgr_ == nullptr) {
    return;
  }
  // Add handshakers and begin handshake process
  CoreConfiguration::Get().handshaker_registry().AddHandshakers(
      HANDSHAKER_SERVER, channel_args, interested_parties_,
      handshake_mgr_.get());
  handshake_mgr_->DoHandshake(
      std::move(endpoint_), channel_args, deadline_, acceptor_.get(),
      [self = Ref()](absl::StatusOr<HandshakerArgs*> result) mutable {
        auto* self_ptr = self.get();
        self_ptr->connection_->work_serializer_.Run(
            [self = std::move(self), result = std::move(result)]() mutable {
              self->OnHandshakeDoneLocked(std::move(result));
            },
            DEBUG_LOCATION);
      });
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::
    ShutdownLocked(absl::Status status) {
  // Shutdown handshake manager with given status
  if (handshake_mgr_ != nullptr) {
    handshake_mgr_->Shutdown(std::move(status));
  }
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::
    OnTimeoutLocked() {
  if (!timer_handle_.has_value()) {
    return;
  }
  // Handle handshake timeout by disconnecting
  timer_handle_.reset();
  auto t = std::get<RefCountedPtr<grpc_chttp2_transport>>(connection_->state_);
  t->DisconnectWithError(GRPC_ERROR_CREATE(
      "Did not receive HTTP/2 settings before handshake timeout"));
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::
    OnReceiveSettings(void* arg, grpc_error_handle /*error*/) {
  // Callback when HTTP/2 settings are received
  HandshakingState* self = static_cast<HandshakingState*>(arg);
  self->connection_->work_serializer_.Run(
      [self] {
        if (self->timer_handle_.has_value()) {
          self->connection_->listener_state_->event_engine()->Cancel(
              *self->timer_handle_);
          self->timer_handle_.reset();
        }
        self->Unref();
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::HandshakingState::
    OnHandshakeDoneLocked(absl::StatusOr<HandshakerArgs*> result) {
  // Handle completion of handshake process
  if (!connection_->shutdown_ && result.ok() &&
      (*result)->endpoint != nullptr) {
    // Create HTTP/2 transport from handshake results
    RefCountedPtr<Transport> transport =
        grpc_create_chttp2_transport((*result)->args,
                                     std::move((*result)->endpoint), false)
            ->Ref();
    grpc_error_handle channel_init_err =
        connection_->listener_state_->server()->SetupTransport(
            transport.get(), accepting_pollset_, (*result)->args);
    if (channel_init_err.ok()) {
      // Success case - setup transport and start reading
      connection_->state_ =
          DownCast<grpc_chttp2_transport*>(transport.get())->Ref();
      Ref().release();
      GRPC_CLOSURE_INIT(&on_receive_settings_, OnReceiveSettings, this,
                        grpc_schedule_on_exec_ctx);
      grpc_closure* on_close = &connection_->on_close_;

      connection_->Ref().release();
      grpc_chttp2_transport_start_reading(
          transport.get(), (*result)->read_buffer.c_slice_buffer(),
          &on_receive_settings_, nullptr, on_close);
      // Set timer for handshake timeout
      timer_handle_ = connection_->listener_state_->event_engine()->RunAfter(
          deadline_ - Timestamp::Now(), [self = Ref()]() mutable {
            ExecCtx exec_ctx;
            auto* self_ptr = self.get();
            self_ptr->connection_->work_serializer_.Run(
                [self = std::move(self)]() { self->OnTimeoutLocked(); },
                DEBUG_LOCATION);
          });
    } else {
      // Error case - log and cleanup
      LOG(ERROR) << "Failed to create channel: "
                 << StatusToString(channel_init_err);
      transport->Orphan();
    }
  }

  // Cleanup handshake manager and notify listener
  handshake_mgr_.reset();
  connection_->listener_state_->OnHandshakeDone(connection_.get());

  // Release connection if transport wasn't successfully created
  if (!std::holds_alternative<RefCountedPtr<grpc_chttp2_transport>>(
          connection_->state_)) {
    connection_->listener_state_->connection_quota()->ReleaseConnections(1);
    connection_->listener_state_->RemoveLogicalConnection(connection_.get());
  }
}

// ActiveConnection implementation
NewChttp2ServerListener::ActiveConnection::ActiveConnection(
    RefCountedPtr<Server::ListenerState> listener_state,
    grpc_tcp_server* tcp_server, grpc_pollset* accepting_pollset,
    AcceptorPtr acceptor, const ChannelArgs& args, MemoryOwner memory_owner,
    OrphanablePtr<grpc_endpoint> endpoint)
    : LogicalConnection(GRPC_TRACE_FLAG_ENABLED(chttp2_server_refcount)
                            ? "NewChttp2ServerListener::ActiveConnection"
                            : nullptr),
      listener_state_(std::move(listener_state)),
      work_serializer_(
          args.GetObjectRef<grpc_event_engine::experimental::EventEngine>()),
      state_(memory_owner.MakeOrphanable<HandshakingState>(
          RefAsSubclass<ActiveConnection>(), tcp_server, accepting_pollset,
          std::move(acceptor), args, std::move(endpoint))) {
  // Initialize close callback
  GRPC_CLOSURE_INIT(&on_close_, ActiveConnection::OnClose, this,
                    grpc_schedule_on_exec_ctx);
}

void NewChttp2ServerListener::ActiveConnection::Orphan() {
  // Shutdown connection when orphaned
  work_serializer_.Run(
      [this]() {
        shutdown_ = true;
        if (std::holds_alternative<OrphanablePtr<HandshakingState>>(state_)) {
          state_ = OrphanablePtr<HandshakingState>(nullptr);
        }
        Unref();
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::SendGoAway() {
  // Send GOAWAY frame to client
  work_serializer_.Run(
      [self = RefAsSubclass<ActiveConnection>()]() mutable {
        self->SendGoAwayImplLocked();
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::DisconnectImmediately() {
  // Immediately disconnect the connection
  work_serializer_.Run(
      [self = RefAsSubclass<ActiveConnection>()]() mutable {
        self->DisconnectImmediatelyImplLocked();
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::Start(const ChannelArgs& args) {
  // Start the connection handshake process
  work_serializer_.Run(
      [self = RefAsSubclass<ActiveConnection>(), args]() mutable {
        if (self->shutdown_) return;
        std::get<OrphanablePtr<HandshakingState>>(self->state_)
            ->StartLocked(args);
      },
      DEBUG_LOCATION);
}

void NewChttp2ServerListener::ActiveConnection::OnClose(
    void* arg, grpc_error_handle /*error*/) {
  // Handle connection close
  ActiveConnection* self = static_cast<ActiveConnection*>(arg);
  self->listener_state_->RemoveLogicalConnection(self);
  self->listener_state_->connection_quota()->ReleaseConnections(1);
  self->Unref();
}

void NewChttp2ServerListener::ActiveConnection::SendGoAwayImplLocked() {
  // Implementation of sending GOAWAY frame
  if (!shutdown_) {
    shutdown_ = true;
    Match(
        state_,
        [](const OrphanablePtr<HandshakingState>& handshaking_state) {
          if (handshaking_state != nullptr) {
            handshaking_state->ShutdownLocked(
                absl::UnavailableError("Connection going away"));
          }
        },
        [](const RefCountedPtr<grpc_chttp2_transport>& transport) {
          if (transport != nullptr) {
            grpc_transport_op* op = grpc_make_transport_op(nullptr);
            op->goaway_error = grpc_error_set_int(
                GRPC_ERROR_CREATE("Server is stopping to serve requests."),
                StatusIntProperty::kHttp2Error,
                static_cast<intptr_t>(Http2ErrorCode::kNoError));
            transport->PerformOp(op);
          }
        });
  }
}

void NewChttp2ServerListener::ActiveConnection::
    DisconnectImmediatelyImplLocked() {
  // Implementation of immediate disconnection
  shutdown_ = true;
  Match(
      state_,
      [](const OrphanablePtr<HandshakingState>& handshaking_state) {
        if (handshaking_state != nullptr) {
          handshaking_state->ShutdownLocked(
              absl::UnavailableError("Connection to be disconnected"));
        }
      },
      [](const RefCountedPtr<grpc_chttp2_transport>& transport) {
        if (transport != nullptr) {
          grpc_transport_op* op = grpc_make_transport_op(nullptr);
          op->disconnect_with_error = GRPC_ERROR_CREATE(
              "Drain grace time expired. Closing connection immediately.");
          transport->PerformOp(op);
        }
      });
}

// NewChttp2ServerListener implementation
grpc_error_handle NewChttp2ServerListener::Create(
    Server* server, const EventEngine::ResolvedAddress& addr,
    const ChannelArgs& args, int* port_num) {
  // Create a new HTTP/2 server listener
  OrphanablePtr<NewChttp2ServerListener> listener =
      MakeOrphanable<NewChttp2ServerListener>(args);

  // Create TCP server
  grpc_error_handle error = grpc_tcp_server_create(
      &listener->tcp_server_shutdown_complete_, ChannelArgsEndpointConfig(args),
      OnAccept, listener.get(), &listener->tcp_server_);
  if (!error.ok()) return error;

  // Handle address resolution
  grpc_resolved_address iomgr_addr =
      grpc_event_engine::experimental::CreateGRPCResolvedAddress(addr);
  if (server->config_fetcher() != nullptr) {
    // Defer port addition if config fetcher is present