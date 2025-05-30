// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_REQUEST_BUFFER_H
#define GRPC_SRC_CORE_CALL_REQUEST_BUFFER_H

#include <utility>

#include "src/core/call/call_spine.h"
#include "src/core/call/message.h"
#include "src/core/call/metadata.h"

namespace grpc_core {

class RequestBuffer {
 public:

  class Reader {
   public:
    explicit Reader(RequestBuffer* buffer) ABSL_LOCKS_EXCLUDED(buffer->mu_)
        : buffer_(buffer) {
      buffer->AddReader(this);
    }
    ~Reader() ABSL_LOCKS_EXCLUDED(buffer_->mu_) { buffer_->RemoveReader(this); }

    Reader(const Reader&) = delete;
    Reader& operator=(const Reader&) = delete;

    GRPC_MUST_USE_RESULT auto PullClientInitialMetadata() {
      return [this]() { return PollPullClientInitialMetadata(); };
    }

    GRPC_MUST_USE_RESULT auto PullMessage() {
      return [this]() { return PollPullMessage(); };
    }

    absl::Status TakeError() { return std::move(error_); }

   private:
    friend class RequestBuffer;

    Poll<ValueOrFailure<ClientMetadataHandle>> PollPullClientInitialMetadata();
    Poll<ValueOrFailure<std::optional<MessageHandle>>> PollPullMessage();

    template <typename T>
    T ClaimObject(T& object) ABSL_EXCLUSIVE_LOCKS_REQUIRED(buffer_->mu_) {
      if (buffer_->winner_ == this) return std::move(object);
      return CopyObject(object);
    }

    ClientMetadataHandle CopyObject(const ClientMetadataHandle& md) {
      return Arena::MakePooled<ClientMetadata>(md->Copy());
    }

    MessageHandle CopyObject(const MessageHandle& msg) {
      return Arena::MakePooled<Message>(msg->payload()->Copy(), msg->flags());
    }

    RequestBuffer* const buffer_;
    bool pulled_client_initial_metadata_ = false;
    size_t message_index_ = 0;
    absl::Status error_;
    Waker pull_waker_;
  };

  RequestBuffer();

  ValueOrFailure<size_t> PushClientInitialMetadata(ClientMetadataHandle md);

  GRPC_MUST_USE_RESULT auto PushMessage(MessageHandle message) {
    return [this, message = std::move(message)]() mutable {
      return PollPushMessage(message);
    };
  }

  StatusFlag FinishSends();

  void Cancel(absl::Status error = absl::CancelledError());

  void Commit(Reader* winner);

  bool committed() const {
    MutexLock lock(&mu_);
    return winner_ != nullptr;
  }

 private:

  struct Buffering {
    Buffering();

    ClientMetadataHandle initial_metadata;

    absl::InlinedVector<MessageHandle, 1> messages;

    size_t buffered = 0;
  };

  struct Buffered {
    Buffered(ClientMetadataHandle md,
             absl::InlinedVector<MessageHandle, 1> msgs)
        : initial_metadata(std::move(md)), messages(std::move(msgs)) {}
    ClientMetadataHandle initial_metadata;
    absl::InlinedVector<MessageHandle, 1> messages;
  };

  struct Streaming {
    MessageHandle message;
    bool end_of_stream = false;
  };

  struct Cancelled {
    explicit Cancelled(absl::Status error) : error(std::move(error)) {}
    absl::Status error;
  };
  using State = std::variant<Buffering, Buffered, Streaming, Cancelled>;

  Poll<ValueOrFailure<size_t>> PollPushMessage(MessageHandle& message);
  Pending PendingPull(Reader* reader) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    reader->pull_waker_ = Activity::current()->MakeOwningWaker();
    return Pending{};
  }
  Pending PendingPush() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    push_waker_ = Activity::current()->MakeOwningWaker();
    return Pending{};
  }
  void MaybeSwitchToStreaming() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    auto& buffering = std::get<Buffering>(state_);
    if (winner_ == nullptr) return;
    if (winner_->message_index_ < buffering.messages.size()) return;
    state_.emplace<Streaming>();
    push_waker_.Wakeup();
  }

  void WakeupAsyncAllPullers() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    WakeupAsyncAllPullersExcept(nullptr);
  }
  void WakeupAsyncAllPullersExcept(Reader* except_reader)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  void AddReader(Reader* reader) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    readers_.insert(reader);
  }

  void RemoveReader(Reader* reader) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    readers_.erase(reader);
  }

  std::string DebugString(Reader* caller) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  mutable Mutex mu_;
  Reader* winner_ ABSL_GUARDED_BY(mu_){nullptr};
  State state_ ABSL_GUARDED_BY(mu_);

  absl::flat_hash_set<Reader*> readers_ ABSL_GUARDED_BY(mu_);
  Waker push_waker_ ABSL_GUARDED_BY(mu_);
};

}

#endif
