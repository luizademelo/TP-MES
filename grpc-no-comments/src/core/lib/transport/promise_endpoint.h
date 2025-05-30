// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_PROMISE_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_PROMISE_ENDPOINT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <cstring>
#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/extensions/chaotic_good_extension.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/cancel_callback.h"
#include "src/core/lib/promise/if.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class PromiseEndpoint {
 public:
  using WriteArgs =
      grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs;

  PromiseEndpoint(
      std::unique_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
          endpoint,
      SliceBuffer already_received);
  PromiseEndpoint() = default;
  ~PromiseEndpoint() = default;

  PromiseEndpoint(const PromiseEndpoint&) = delete;
  PromiseEndpoint& operator=(const PromiseEndpoint&) = delete;
  PromiseEndpoint(PromiseEndpoint&&) = default;
  PromiseEndpoint& operator=(PromiseEndpoint&&) = default;

  auto Write(SliceBuffer data, WriteArgs write_args) {
    GRPC_LATENT_SEE_PARENT_SCOPE("GRPC:Write");

    auto prev = write_state_->state.exchange(WriteState::kWriting,
                                             std::memory_order_relaxed);
    CHECK(prev == WriteState::kIdle);
    bool completed;
    if (data.Length() == 0) {
      completed = true;
    } else {

      grpc_slice_buffer_swap(write_state_->buffer.c_slice_buffer(),
                             data.c_slice_buffer());

      write_state_->waker = GetContext<Activity>()->MakeNonOwningWaker();
      completed = endpoint_->Write(
          [write_state = write_state_](absl::Status status) {
            ExecCtx exec_ctx;
            write_state->Complete(std::move(status));
          },
          &write_state_->buffer, std::move(write_args));
      if (completed) write_state_->waker = Waker();
    }
    return If(
        completed,
        [this]() {
          return [write_state = write_state_]() {
            auto prev = write_state->state.exchange(WriteState::kIdle,
                                                    std::memory_order_relaxed);
            CHECK(prev == WriteState::kWriting);
            return absl::OkStatus();
          };
        },
        GRPC_LATENT_SEE_PROMISE(
            "DelayedWrite", ([this]() {
              return [write_state = write_state_]() -> Poll<absl::Status> {

                WriteState::State expected = WriteState::kWritten;
                if (write_state->state.compare_exchange_strong(
                        expected, WriteState::kIdle, std::memory_order_acquire,
                        std::memory_order_relaxed)) {

                  return std::move(write_state->result);
                }

                CHECK(expected == WriteState::kWriting);
                return Pending();
              };
            })));
  }

  auto Read(size_t num_bytes) {
    GRPC_LATENT_SEE_PARENT_SCOPE("GRPC:Read");

    CHECK(!read_state_->complete.load(std::memory_order_relaxed));

    CHECK(read_state_->pending_buffer.Count() == 0u);
    bool complete = true;
    while (read_state_->buffer.Length() < num_bytes) {

      grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs
          read_args;
      read_args.set_read_hint_bytes(
          static_cast<int64_t>(num_bytes - read_state_->buffer.Length()));

      read_state_->waker = GetContext<Activity>()->MakeNonOwningWaker();
      if (endpoint_->Read(
              [read_state = read_state_, num_bytes](absl::Status status) {
                ExecCtx exec_ctx;
                read_state->Complete(std::move(status), num_bytes);
              },
              &read_state_->pending_buffer, std::move(read_args))) {
        read_state_->waker = Waker();
        read_state_->pending_buffer.MoveFirstNBytesIntoSliceBuffer(
            read_state_->pending_buffer.Length(), read_state_->buffer);
        DCHECK(read_state_->pending_buffer.Count() == 0u);
      } else {
        complete = false;
        break;
      }
    }
    return If(
        complete,
        [this, num_bytes]() {
          SliceBuffer ret;
          grpc_slice_buffer_move_first_no_inline(
              read_state_->buffer.c_slice_buffer(), num_bytes,
              ret.c_slice_buffer());
          return [ret = std::move(
                      ret)]() mutable -> Poll<absl::StatusOr<SliceBuffer>> {
            return std::move(ret);
          };
        },
        GRPC_LATENT_SEE_PROMISE(
            "DelayedRead", ([this, num_bytes]() {
              return [read_state = read_state_,
                      num_bytes]() -> Poll<absl::StatusOr<SliceBuffer>> {
                if (!read_state->complete.load(std::memory_order_acquire)) {
                  return Pending();
                }

                if (read_state->result.ok()) {
                  SliceBuffer ret;
                  grpc_slice_buffer_move_first_no_inline(
                      read_state->buffer.c_slice_buffer(), num_bytes,
                      ret.c_slice_buffer());
                  read_state->complete.store(false, std::memory_order_relaxed);
                  return std::move(ret);
                }
                read_state->complete.store(false, std::memory_order_relaxed);
                return std::move(read_state->result);
              };
            })));
  }

  auto ReadSlice(size_t num_bytes) {
    return Map(Read(num_bytes),
               [](absl::StatusOr<SliceBuffer> buffer) -> absl::StatusOr<Slice> {
                 if (!buffer.ok()) return buffer.status();
                 return buffer->JoinIntoSlice();
               });
  }

  auto ReadByte() {
    return Map(ReadSlice(1),
               [](absl::StatusOr<Slice> slice) -> absl::StatusOr<uint8_t> {
                 if (!slice.ok()) return slice.status();
                 return (*slice)[0];
               });
  }

  void EnforceRxMemoryAlignmentAndCoalescing() {
    auto* chaotic_good_ext = grpc_event_engine::experimental::QueryExtension<
        grpc_event_engine::experimental::ChaoticGoodExtension>(endpoint_.get());
    if (chaotic_good_ext != nullptr) {
      chaotic_good_ext->EnforceRxMemoryAlignment();
      chaotic_good_ext->EnableRpcReceiveCoalescing();
    }
  }

  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetPeerAddress() const;
  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetLocalAddress() const;

  std::shared_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
  GetEventEngineEndpoint() const {
    return endpoint_;
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
      endpoint_;

  struct ReadState : public RefCounted<ReadState> {
    std::atomic<bool> complete{false};

    grpc_event_engine::experimental::SliceBuffer buffer;

    grpc_event_engine::experimental::SliceBuffer pending_buffer;

    absl::Status result;
    Waker waker;

    std::weak_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
        endpoint;

    void Complete(absl::Status status, size_t num_bytes_requested);
  };

  struct WriteState : public RefCounted<WriteState> {
    enum State : uint8_t {
      kIdle,
      kWriting,
      kWritten,
    };

    std::atomic<State> state{kIdle};

    grpc_event_engine::experimental::SliceBuffer buffer;

    absl::Status result;
    Waker waker;

    void Complete(absl::Status status) {
      result = std::move(status);
      auto w = std::move(waker);
      auto prev = state.exchange(kWritten, std::memory_order_release);

      CHECK(prev == kWriting);
      w.Wakeup();
    }
  };

  RefCountedPtr<WriteState> write_state_ = MakeRefCounted<WriteState>();
  RefCountedPtr<ReadState> read_state_ = MakeRefCounted<ReadState>();
};

}

#endif
