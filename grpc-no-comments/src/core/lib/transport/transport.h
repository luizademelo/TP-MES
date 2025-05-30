
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_TRANSPORT_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_TRANSPORT_H

#include <grpc/impl/connectivity_state.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <functional>
#include <optional>
#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/call_destination.h"
#include "src/core/call/call_spine.h"
#include "src/core/call/message.h"
#include "src/core/call/metadata.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/latch.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/call_final_info.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport_fwd.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"

#define GRPC_PROTOCOL_VERSION_MAX_MAJOR 2
#define GRPC_PROTOCOL_VERSION_MAX_MINOR 1
#define GRPC_PROTOCOL_VERSION_MIN_MAJOR 2
#define GRPC_PROTOCOL_VERSION_MIN_MINOR 1

#define GRPC_ARG_TRANSPORT "grpc.internal.transport"

#define GRPC_ARG_TRANSPORT_PROTOCOLS "grpc.internal.transport_protocols"

namespace grpc_core {

class ClientInitialMetadataOutstandingToken {
 public:
  static ClientInitialMetadataOutstandingToken Empty() {
    return ClientInitialMetadataOutstandingToken();
  }
  static ClientInitialMetadataOutstandingToken New(
      Arena* arena = GetContext<Arena>()) {
    ClientInitialMetadataOutstandingToken token;
    token.latch_ = arena->New<Latch<bool>>();
    return token;
  }

  ClientInitialMetadataOutstandingToken(
      const ClientInitialMetadataOutstandingToken&) = delete;
  ClientInitialMetadataOutstandingToken& operator=(
      const ClientInitialMetadataOutstandingToken&) = delete;
  ClientInitialMetadataOutstandingToken(
      ClientInitialMetadataOutstandingToken&& other) noexcept
      : latch_(std::exchange(other.latch_, nullptr)) {}
  ClientInitialMetadataOutstandingToken& operator=(
      ClientInitialMetadataOutstandingToken&& other) noexcept {
    latch_ = std::exchange(other.latch_, nullptr);
    return *this;
  }
  ~ClientInitialMetadataOutstandingToken() {
    if (latch_ != nullptr) latch_->Set(false);
  }
  void Complete(bool success) { std::exchange(latch_, nullptr)->Set(success); }

  auto Wait() { return latch_->Wait(); }

 private:
  ClientInitialMetadataOutstandingToken() = default;

  Latch<bool>* latch_ = nullptr;
};

using ClientInitialMetadataOutstandingTokenWaitType =
    decltype(std::declval<ClientInitialMetadataOutstandingToken>().Wait());

struct CallArgs {

  ClientMetadataHandle client_initial_metadata;

  ClientInitialMetadataOutstandingToken client_initial_metadata_outstanding;

  Latch<grpc_polling_entity>* polling_entity;

  PipeSender<ServerMetadataHandle>* server_initial_metadata;

  PipeReceiver<MessageHandle>* client_to_server_messages;

  PipeSender<MessageHandle>* server_to_client_messages;
};

using NextPromiseFactory =
    std::function<ArenaPromise<ServerMetadataHandle>(CallArgs)>;

}

typedef struct grpc_stream grpc_stream;

typedef struct grpc_stream_refcount {
  grpc_core::RefCount refs;
  grpc_closure destroy;
#ifndef NDEBUG
  const char* object_type;
#endif
} grpc_stream_refcount;

#ifndef NDEBUG
void grpc_stream_ref_init(grpc_stream_refcount* refcount, int initial_refs,
                          grpc_iomgr_cb_func cb, void* cb_arg,
                          const char* object_type);
#define GRPC_STREAM_REF_INIT(rc, ir, cb, cb_arg, objtype) \
  grpc_stream_ref_init(rc, ir, cb, cb_arg, objtype)
#else
void grpc_stream_ref_init(grpc_stream_refcount* refcount, int initial_refs,
                          grpc_iomgr_cb_func cb, void* cb_arg);
#define GRPC_STREAM_REF_INIT(rc, ir, cb, cb_arg, objtype) \
  do {                                                    \
    grpc_stream_ref_init(rc, ir, cb, cb_arg);             \
    (void)(objtype);                                      \
  } while (0)
#endif

#ifndef NDEBUG
inline void grpc_stream_ref(grpc_stream_refcount* refcount,
                            const char* reason) {
  GRPC_TRACE_VLOG(stream_refcount, 2)
      << refcount->object_type << " " << refcount << ":"
      << refcount->destroy.cb_arg << " REF " << reason;
  refcount->refs.RefNonZero(DEBUG_LOCATION, reason);
}
#else
inline void grpc_stream_ref(grpc_stream_refcount* refcount) {
  refcount->refs.RefNonZero();
}
#endif

void grpc_stream_destroy(grpc_stream_refcount* refcount);

#ifndef NDEBUG
inline void grpc_stream_unref(grpc_stream_refcount* refcount,
                              const char* reason) {
  GRPC_TRACE_VLOG(stream_refcount, 2)
      << refcount->object_type << " " << refcount << ":"
      << refcount->destroy.cb_arg << " UNREF " << reason;
  if (GPR_UNLIKELY(refcount->refs.Unref(DEBUG_LOCATION, reason))) {
    grpc_stream_destroy(refcount);
  }
}
#else
inline void grpc_stream_unref(grpc_stream_refcount* refcount) {
  if (GPR_UNLIKELY(refcount->refs.Unref())) {
    grpc_stream_destroy(refcount);
  }
}
#endif

grpc_slice grpc_slice_from_stream_owned_buffer(grpc_stream_refcount* refcount,
                                               void* buffer, size_t length);

struct grpc_handler_private_op_data {
  void* extra_arg = nullptr;
  grpc_closure closure;
  grpc_handler_private_op_data() { memset(&closure, 0, sizeof(closure)); }
};

typedef struct grpc_transport_stream_op_batch_payload
    grpc_transport_stream_op_batch_payload;

struct grpc_transport_stream_op_batch {
  grpc_transport_stream_op_batch()
      : send_initial_metadata(false),
        send_trailing_metadata(false),
        send_message(false),
        recv_initial_metadata(false),
        recv_message(false),
        recv_trailing_metadata(false),
        cancel_stream(false),
        is_traced(false) {}

  grpc_closure* on_complete = nullptr;

  grpc_transport_stream_op_batch_payload* payload = nullptr;

  bool send_initial_metadata : 1;

  bool send_trailing_metadata : 1;

  bool send_message : 1;

  bool recv_initial_metadata : 1;

  bool recv_message : 1;

  bool recv_trailing_metadata : 1;

  bool cancel_stream : 1;

  bool is_traced : 1;

  bool HasOp() const {
    return send_initial_metadata || send_trailing_metadata || send_message ||
           recv_initial_metadata || recv_message || recv_trailing_metadata ||
           cancel_stream;
  }

  grpc_handler_private_op_data handler_private;
};

struct grpc_transport_stream_op_batch_payload {
  struct {
    grpc_metadata_batch* send_initial_metadata = nullptr;
  } send_initial_metadata;

  struct {
    grpc_metadata_batch* send_trailing_metadata = nullptr;

    bool* sent = nullptr;
  } send_trailing_metadata;

  struct {

    grpc_core::SliceBuffer* send_message;
    uint32_t flags = 0;

    bool stream_write_closed = false;
  } send_message;

  struct {
    grpc_metadata_batch* recv_initial_metadata = nullptr;

    grpc_closure* recv_initial_metadata_ready = nullptr;

    bool* trailing_metadata_available = nullptr;
  } recv_initial_metadata;

  struct {

    std::optional<grpc_core::SliceBuffer>* recv_message = nullptr;
    uint32_t* flags = nullptr;

    bool* call_failed_before_recv_message = nullptr;

    grpc_closure* recv_message_ready = nullptr;
  } recv_message;

  struct {
    grpc_metadata_batch* recv_trailing_metadata = nullptr;
    grpc_transport_stream_stats* collect_stats = nullptr;

    grpc_closure* recv_trailing_metadata_ready = nullptr;
  } recv_trailing_metadata;

  struct {

    grpc_error_handle cancel_error;

    bool tarpit = false;
  } cancel_stream;
};

typedef struct grpc_transport_op {

  grpc_closure* on_consumed = nullptr;

  grpc_core::OrphanablePtr<grpc_core::ConnectivityStateWatcherInterface>
      start_connectivity_watch;
  grpc_core::ConnectivityStateWatcherInterface* stop_connectivity_watch =
      nullptr;

  grpc_error_handle disconnect_with_error;

  grpc_error_handle goaway_error;
  void (*set_accept_stream_fn)(void* user_data, grpc_core::Transport* transport,
                               const void* server_data) = nullptr;
  void (*set_registered_method_matcher_fn)(
      void* user_data, grpc_core::ServerMetadata* metadata) = nullptr;
  void* set_accept_stream_user_data = nullptr;
  void (*set_make_promise_fn)(void* user_data, grpc_core::Transport* transport,
                              const void* server_data) = nullptr;
  void* set_make_promise_user_data = nullptr;

  grpc_pollset* bind_pollset = nullptr;

  grpc_pollset_set* bind_pollset_set = nullptr;

  struct {

    grpc_closure* on_initiate = nullptr;

    grpc_closure* on_ack = nullptr;
  } send_ping;
  grpc_connectivity_state start_connectivity_watch_state = GRPC_CHANNEL_IDLE;

  bool reset_connect_backoff = false;

  bool set_accept_stream = false;

  bool set_make_promise = false;

  grpc_handler_private_op_data handler_private;
} grpc_transport_op;

grpc_transport_op* grpc_make_transport_op(grpc_closure* on_complete);

grpc_transport_stream_op_batch* grpc_make_transport_stream_op(
    grpc_closure* on_complete);

void grpc_transport_stream_op_batch_finish_with_failure(
    grpc_transport_stream_op_batch* batch, grpc_error_handle error,
    grpc_core::CallCombiner* call_combiner);
void grpc_transport_stream_op_batch_queue_finish_with_failure(
    grpc_transport_stream_op_batch* batch, grpc_error_handle error,
    grpc_core::CallCombinerClosureList* closures);

void grpc_transport_stream_op_batch_finish_with_failure_from_transport(
    grpc_transport_stream_op_batch* batch, grpc_error_handle error);

std::string grpc_transport_stream_op_batch_string(
    grpc_transport_stream_op_batch* op, bool truncate);
std::string grpc_transport_op_string(grpc_transport_op* op);

namespace grpc_core {

class FilterStackTransport;
class ClientTransport;
class ServerTransport;

class Transport : public InternallyRefCounted<Transport> {
 public:
  struct RawPointerChannelArgTag {};
  static absl::string_view ChannelArgName() { return GRPC_ARG_TRANSPORT; }

  using InternallyRefCounted<Transport>::InternallyRefCounted;

  RefCountedPtr<Transport> Ref() {
    return InternallyRefCounted<Transport>::Ref();
  }
  template <typename T>
  RefCountedPtr<T> RefAsSubclass() {
    return InternallyRefCounted<Transport>::RefAsSubclass<T>();
  }

  virtual FilterStackTransport* filter_stack_transport() = 0;
  virtual ClientTransport* client_transport() = 0;
  virtual ServerTransport* server_transport() = 0;

  virtual absl::string_view GetTransportName() const = 0;

  virtual void SetPollset(grpc_stream* stream, grpc_pollset* pollset) = 0;

  virtual void SetPollsetSet(grpc_stream* stream,
                             grpc_pollset_set* pollset_set) = 0;

  void SetPollingEntity(grpc_stream* stream,
                        grpc_polling_entity* pollset_or_pollset_set);

  virtual void PerformOp(grpc_transport_op* op) = 0;

  void StartConnectivityWatch(
      OrphanablePtr<ConnectivityStateWatcherInterface> watcher) {
    grpc_transport_op* op = grpc_make_transport_op(nullptr);
    op->start_connectivity_watch = std::move(watcher);
    PerformOp(op);
  }

  void DisconnectWithError(grpc_error_handle error) {
    CHECK(!error.ok()) << error;
    grpc_transport_op* op = grpc_make_transport_op(nullptr);
    op->disconnect_with_error = error;
    PerformOp(op);
  }

  virtual RefCountedPtr<channelz::SocketNode> GetSocketNode() const = 0;
};

class FilterStackTransport : public Transport {
 public:

  virtual size_t SizeOfStream() const = 0;

  virtual void InitStream(grpc_stream* stream, grpc_stream_refcount* refcount,
                          const void* server_data, Arena* arena) = 0;

  // HACK: inproc does not handle stream op batch callbacks correctly (receive

  virtual bool HackyDisableStreamOpBatchCoalescingInConnectedChannel()
      const = 0;

  virtual void PerformStreamOp(grpc_stream* stream,
                               grpc_transport_stream_op_batch* op) = 0;

  virtual void DestroyStream(grpc_stream* stream,
                             grpc_closure* then_schedule_closure) = 0;

 protected:
  ~FilterStackTransport() override = default;
};

class ClientTransport : public Transport {
 public:
  using Transport::Transport;
  virtual void StartCall(CallHandler call_handler) = 0;

 protected:
  ~ClientTransport() override = default;
};

class ServerTransport : public Transport {
 public:
  using Transport::Transport;

  virtual void SetCallDestination(
      RefCountedPtr<UnstartedCallDestination> unstarted_call_handler) = 0;

 protected:
  ~ServerTransport() override = default;
};

}

namespace grpc_core {

constexpr const char* kKeepaliveThrottlingKey =
    "grpc.internal.keepalive_throttling";
}

#endif
