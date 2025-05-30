
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_COMPLETION_QUEUE_H
#define GRPCPP_COMPLETION_QUEUE_H

#include <grpc/grpc.h>
#include <grpc/support/atm.h>
#include <grpc/support/time.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/sync.h>
#include <grpcpp/impl/codegen/time.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/status.h>

#include <list>

#include "absl/log/absl_check.h"

struct grpc_completion_queue;

namespace grpc {
template <class R>
class ClientReader;
template <class W>
class ClientWriter;
template <class W, class R>
class ClientReaderWriter;
template <class R>
class ServerReader;
template <class W>
class ServerWriter;
namespace internal {
template <class W, class R>
class ServerReaderWriterBody;

template <class ResponseType>
void UnaryRunHandlerHelper(
    const grpc::internal::MethodHandler::HandlerParameter&, ResponseType*,
    grpc::Status&);
template <class ServiceType, class RequestType, class ResponseType,
          class BaseRequestType, class BaseResponseType>
class RpcMethodHandler;
template <class ServiceType, class RequestType, class ResponseType>
class ClientStreamingHandler;
template <class ServiceType, class RequestType, class ResponseType>
class ServerStreamingHandler;
template <class Streamer, bool WriteNeeded>
class TemplatedBidiStreamingHandler;
template <grpc::StatusCode code>
class ErrorMethodHandler;
}

class Channel;
class ChannelInterface;
class Server;
class ServerBuilder;
class ServerContextBase;
class ServerInterface;

namespace internal {
class CompletionQueueTag;
class RpcMethod;
template <class InputMessage, class OutputMessage>
class BlockingUnaryCallImpl;
template <class Op1, class Op2, class Op3, class Op4, class Op5, class Op6>
class CallOpSet;
}

class CompletionQueue : private grpc::internal::GrpcLibrary {
 public:

  CompletionQueue()
      : CompletionQueue(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_NEXT, GRPC_CQ_DEFAULT_POLLING,
            nullptr}) {}

  explicit CompletionQueue(grpc_completion_queue* take);

  ~CompletionQueue() override { grpc_completion_queue_destroy(cq_); }

  enum NextStatus {
    SHUTDOWN,
    GOT_EVENT,

    TIMEOUT
  };

  bool Next(void** tag, bool* ok) {

    return (AsyncNextInternal(tag, ok, gpr_inf_future(GPR_CLOCK_REALTIME)) ==
            GOT_EVENT);
  }

  template <typename T>
  NextStatus AsyncNext(void** tag, bool* ok, const T& deadline) {
    grpc::TimePoint<T> deadline_tp(deadline);
    return AsyncNextInternal(tag, ok, deadline_tp.raw_time());
  }

  template <typename T, typename F>
  NextStatus DoThenAsyncNext(F&& f, void** tag, bool* ok, const T& deadline) {
    CompletionQueueTLSCache cache = CompletionQueueTLSCache(this);
    f();
    if (cache.Flush(tag, ok)) {
      return GOT_EVENT;
    } else {
      return AsyncNext(tag, ok, deadline);
    }
  }

  void Shutdown();

  grpc_completion_queue* cq() { return cq_; }

 protected:

  explicit CompletionQueue(const grpc_completion_queue_attributes& attributes) {
    cq_ = grpc_completion_queue_create(
        grpc_completion_queue_factory_lookup(&attributes), &attributes,
        nullptr);
    InitialAvalanching();
  }

 private:

  friend class grpc::ServerBuilder;
  friend class grpc::Server;

  template <class R>
  friend class grpc::ClientReader;
  template <class W>
  friend class grpc::ClientWriter;
  template <class W, class R>
  friend class grpc::ClientReaderWriter;
  template <class R>
  friend class grpc::ServerReader;
  template <class W>
  friend class grpc::ServerWriter;
  template <class W, class R>
  friend class grpc::internal::ServerReaderWriterBody;
  template <class ResponseType>
  friend void grpc::internal::UnaryRunHandlerHelper(
      const grpc::internal::MethodHandler::HandlerParameter&, ResponseType*,
      grpc::Status&);
  template <class ServiceType, class RequestType, class ResponseType>
  friend class grpc::internal::ClientStreamingHandler;
  template <class ServiceType, class RequestType, class ResponseType>
  friend class grpc::internal::ServerStreamingHandler;
  template <class Streamer, bool WriteNeeded>
  friend class grpc::internal::TemplatedBidiStreamingHandler;
  template <grpc::StatusCode code>
  friend class grpc::internal::ErrorMethodHandler;
  friend class grpc::ServerContextBase;
  friend class grpc::ServerInterface;
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::BlockingUnaryCallImpl;

  friend class grpc::Channel;

  template <class Op1, class Op2, class Op3, class Op4, class Op5, class Op6>
  friend class grpc::internal::CallOpSet;

  class CompletionQueueTLSCache {
   public:
    explicit CompletionQueueTLSCache(CompletionQueue* cq);
    ~CompletionQueueTLSCache();
    bool Flush(void** tag, bool* ok);

   private:
    CompletionQueue* cq_;
    bool flushed_;
  };

  NextStatus AsyncNextInternal(void** tag, bool* ok, gpr_timespec deadline);

  bool Pluck(grpc::internal::CompletionQueueTag* tag) {
    auto deadline = gpr_inf_future(GPR_CLOCK_REALTIME);
    while (true) {
      auto ev = grpc_completion_queue_pluck(cq_, tag, deadline, nullptr);
      bool ok = ev.success != 0;
      void* ignored = tag;
      if (tag->FinalizeResult(&ignored, &ok)) {
        ABSL_CHECK(ignored == tag);
        return ok;
      }
    }
  }

  /// TODO: sreek - This calls tag->FinalizeResult() even if the cq_ is already

  void TryPluck(grpc::internal::CompletionQueueTag* tag) {
    auto deadline = gpr_time_0(GPR_CLOCK_REALTIME);
    auto ev = grpc_completion_queue_pluck(cq_, tag, deadline, nullptr);
    if (ev.type == GRPC_QUEUE_TIMEOUT) return;
    bool ok = ev.success != 0;
    void* ignored = tag;

    ABSL_CHECK(!tag->FinalizeResult(&ignored, &ok));
  }

  void TryPluck(grpc::internal::CompletionQueueTag* tag,
                gpr_timespec deadline) {
    auto ev = grpc_completion_queue_pluck(cq_, tag, deadline, nullptr);
    if (ev.type == GRPC_QUEUE_TIMEOUT || ev.type == GRPC_QUEUE_SHUTDOWN) {
      return;
    }

    bool ok = ev.success != 0;
    void* ignored = tag;
    ABSL_CHECK(!tag->FinalizeResult(&ignored, &ok));
  }

  void InitialAvalanching() {
    gpr_atm_rel_store(&avalanches_in_flight_, gpr_atm{1});
  }
  void RegisterAvalanching() {
    gpr_atm_no_barrier_fetch_add(&avalanches_in_flight_, gpr_atm{1});
  }
  void CompleteAvalanching() {
    if (gpr_atm_no_barrier_fetch_add(&avalanches_in_flight_, gpr_atm{-1}) ==
        1) {
      grpc_completion_queue_shutdown(cq_);
    }
  }

  void RegisterServer(const grpc::Server* server) {
    (void)server;
#ifndef NDEBUG
    grpc::internal::MutexLock l(&server_list_mutex_);
    server_list_.push_back(server);
#endif
  }
  void UnregisterServer(const grpc::Server* server) {
    (void)server;
#ifndef NDEBUG
    grpc::internal::MutexLock l(&server_list_mutex_);
    server_list_.remove(server);
#endif
  }
  bool ServerListEmpty() const {
#ifndef NDEBUG
    grpc::internal::MutexLock l(&server_list_mutex_);
    return server_list_.empty();
#endif
    return true;
  }

  static CompletionQueue* CallbackAlternativeCQ();
  static void ReleaseCallbackAlternativeCQ(CompletionQueue* cq);

  grpc_completion_queue* cq_;

  gpr_atm avalanches_in_flight_;

  mutable grpc::internal::Mutex server_list_mutex_;
  std::list<const grpc::Server*>
      server_list_ ;
};

class ServerCompletionQueue : public CompletionQueue {
 public:
  bool IsFrequentlyPolled() { return polling_type_ != GRPC_CQ_NON_LISTENING; }

 protected:

  ServerCompletionQueue() : polling_type_(GRPC_CQ_DEFAULT_POLLING) {}

 private:

  ServerCompletionQueue(grpc_cq_completion_type completion_type,
                        grpc_cq_polling_type polling_type,
                        grpc_completion_queue_functor* shutdown_cb)
      : CompletionQueue(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, completion_type, polling_type,
            shutdown_cb}),
        polling_type_(polling_type) {}

  grpc_cq_polling_type polling_type_;
  friend class grpc::ServerBuilder;
  friend class grpc::Server;
};

}

#endif
