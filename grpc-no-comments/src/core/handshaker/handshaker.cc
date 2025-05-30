
// Copyright 2016 gRPC authors.

#include "src/core/handshaker/handshaker.h"

#include <grpc/byte_buffer.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <string>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"

using ::grpc_event_engine::experimental::EventEngine;

namespace grpc_core {

void Handshaker::InvokeOnHandshakeDone(
    HandshakerArgs* args,
    absl::AnyInvocable<void(absl::Status)> on_handshake_done,
    absl::Status status) {
  args->event_engine->Run([on_handshake_done = std::move(on_handshake_done),
                           status = std::move(status)]() mutable {
    ExecCtx exec_ctx;
    on_handshake_done(std::move(status));

    on_handshake_done = nullptr;
  });
}

namespace {

std::string HandshakerArgsString(HandshakerArgs* args) {
  return absl::StrFormat("{endpoint=%p, args=%s, read_buffer.Length()=%" PRIuPTR
                         ", exit_early=%d}",
                         args->endpoint.get(), args->args.ToString(),
                         args->read_buffer.Length(), args->exit_early);
}

}

HandshakeManager::HandshakeManager()
    : RefCounted(GRPC_TRACE_FLAG_ENABLED(handshaker) ? "HandshakeManager"
                                                     : nullptr) {}

void HandshakeManager::Add(RefCountedPtr<Handshaker> handshaker) {
  MutexLock lock(&mu_);
  GRPC_TRACE_LOG(handshaker, INFO)
      << "handshake_manager " << this << ": adding handshaker "
      << std::string(handshaker->name()) << " [" << handshaker.get()
      << "] at index " << handshakers_.size();
  handshakers_.push_back(std::move(handshaker));
}

void HandshakeManager::DoHandshake(
    OrphanablePtr<grpc_endpoint> endpoint, const ChannelArgs& channel_args,
    Timestamp deadline, grpc_tcp_server_acceptor* acceptor,
    absl::AnyInvocable<void(absl::StatusOr<HandshakerArgs*>)>
        on_handshake_done) {

  auto self = Ref();
  MutexLock lock(&mu_);
  CHECK_EQ(index_, 0u);
  on_handshake_done_ = std::move(on_handshake_done);

  args_.endpoint = std::move(endpoint);
  args_.deadline = deadline;
  args_.args = channel_args;
  args_.event_engine = args_.args.GetObject<EventEngine>();
  args_.acceptor = acceptor;
  if (acceptor != nullptr && acceptor->external_connection &&
      acceptor->pending_data != nullptr) {
    grpc_slice_buffer_swap(args_.read_buffer.c_slice_buffer(),
                           &(acceptor->pending_data->data.raw.slice_buffer));
  }

  const Duration time_to_deadline = deadline - Timestamp::Now();
  deadline_timer_handle_ =
      args_.event_engine->RunAfter(time_to_deadline, [self = Ref()]() mutable {
        ExecCtx exec_ctx;
        self->Shutdown(GRPC_ERROR_CREATE("Handshake timed out"));

        self.reset();
      });

  CallNextHandshakerLocked(absl::OkStatus());
}

void HandshakeManager::Shutdown(absl::Status error) {
  MutexLock lock(&mu_);
  if (!is_shutdown_) {
    GRPC_TRACE_LOG(handshaker, INFO)
        << "handshake_manager " << this << ": Shutdown() called: " << error;
    is_shutdown_ = true;

    if (index_ > 0) {
      GRPC_TRACE_LOG(handshaker, INFO)
          << "handshake_manager " << this
          << ": shutting down handshaker at index " << index_ - 1;
      handshakers_[index_ - 1]->Shutdown(std::move(error));
    }
  }
}

void HandshakeManager::CallNextHandshakerLocked(absl::Status error) {
  GRPC_TRACE_LOG(handshaker, INFO)
      << "handshake_manager " << this << ": error=" << error
      << " shutdown=" << is_shutdown_ << " index=" << index_
      << ", args=" << HandshakerArgsString(&args_);
  CHECK(index_ <= handshakers_.size());

  if (!error.ok() || is_shutdown_ || args_.exit_early ||
      index_ == handshakers_.size()) {
    if (error.ok() && is_shutdown_) {
      error = GRPC_ERROR_CREATE("handshaker shutdown");
      args_.endpoint.reset();
    }
    GRPC_TRACE_LOG(handshaker, INFO) << "handshake_manager " << this
                                     << ": handshaking complete -- scheduling "
                                        "on_handshake_done with error="
                                     << error;

    args_.event_engine->Cancel(deadline_timer_handle_);
    is_shutdown_ = true;
    absl::StatusOr<HandshakerArgs*> result(&args_);
    if (!error.ok()) result = std::move(error);
    args_.event_engine->Run([on_handshake_done = std::move(on_handshake_done_),
                             result = std::move(result)]() mutable {
      ExecCtx exec_ctx;
      on_handshake_done(std::move(result));

      on_handshake_done = nullptr;
    });
    return;
  }

  auto handshaker = handshakers_[index_];
  GRPC_TRACE_LOG(handshaker, INFO)
      << "handshake_manager " << this << ": calling handshaker "
      << handshaker->name() << " [" << handshaker.get() << "] at index "
      << index_;
  ++index_;
  handshaker->DoHandshake(&args_, [self = Ref()](absl::Status error) mutable {
    MutexLock lock(&self->mu_);
    self->CallNextHandshakerLocked(std::move(error));
  });
}

}
