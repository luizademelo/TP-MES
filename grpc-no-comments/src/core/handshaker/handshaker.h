
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_H
#define GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/container/inlined_vector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

struct HandshakerArgs {
  OrphanablePtr<grpc_endpoint> endpoint;
  ChannelArgs args;

  SliceBuffer read_buffer;

  bool exit_early = false;

  grpc_event_engine::experimental::EventEngine* event_engine = nullptr;

  Timestamp deadline;

  grpc_tcp_server_acceptor* acceptor = nullptr;
};

class Handshaker : public RefCounted<Handshaker> {
 public:
  ~Handshaker() override = default;
  virtual absl::string_view name() const = 0;
  virtual void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) = 0;
  virtual void Shutdown(absl::Status error) = 0;

 protected:

  static void InvokeOnHandshakeDone(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done,
      absl::Status status);
};

class HandshakeManager : public RefCounted<HandshakeManager> {
 public:
  HandshakeManager();

  void Add(RefCountedPtr<Handshaker> handshaker) ABSL_LOCKS_EXCLUDED(mu_);

  void DoHandshake(OrphanablePtr<grpc_endpoint> endpoint,
                   const ChannelArgs& channel_args, Timestamp deadline,
                   grpc_tcp_server_acceptor* acceptor,
                   absl::AnyInvocable<void(absl::StatusOr<HandshakerArgs*>)>
                       on_handshake_done) ABSL_LOCKS_EXCLUDED(mu_);

  void Shutdown(absl::Status error) ABSL_LOCKS_EXCLUDED(mu_);

 private:

  void CallNextHandshakerLocked(absl::Status error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  static const size_t kHandshakerListInlineSize = 2;

  Mutex mu_;
  bool is_shutdown_ ABSL_GUARDED_BY(mu_) = false;

  size_t index_ ABSL_GUARDED_BY(mu_) = 0;

  absl::InlinedVector<RefCountedPtr<Handshaker>, kHandshakerListInlineSize>
      handshakers_ ABSL_GUARDED_BY(mu_);

  HandshakerArgs args_ ABSL_GUARDED_BY(mu_);

  absl::AnyInvocable<void(absl::StatusOr<HandshakerArgs*>)> on_handshake_done_
      ABSL_GUARDED_BY(mu_);

  grpc_event_engine::experimental::EventEngine::TaskHandle
      deadline_timer_handle_ ABSL_GUARDED_BY(mu_);
};

}

#endif
