// Copyright 2023 gRPC authors.

#include "test/core/filters/filter_test.h"

#include <grpc/grpc.h>

#include <algorithm>
#include <chrono>
#include <memory>
#include <optional>
#include <queue>

#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/call/call_finalization.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/crash.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"

using grpc_event_engine::experimental::FuzzingEventEngine;

namespace grpc_core {

class FilterTestBase::Call::Impl
    : public std::enable_shared_from_this<FilterTestBase::Call::Impl> {
 public:
  Impl(Call* call, std::shared_ptr<Channel::Impl> channel)
      : call_(call), channel_(std::move(channel)) {}
  ~Impl();

  Arena* arena() const { return arena_.get(); }
  const std::shared_ptr<Channel::Impl>& channel() const { return channel_; }
  CallFinalization* call_finalization() { return &call_finalization_; }

  void Start(ClientMetadataHandle md);
  void ForwardServerInitialMetadata(ServerMetadataHandle md);
  void ForwardMessageClientToServer(MessageHandle msg);
  void ForwardMessageServerToClient(MessageHandle msg);
  void FinishNextFilter(ServerMetadataHandle md);

  void StepLoop();

  grpc_event_engine::experimental::EventEngine* event_engine() {
    return channel_->test->event_engine();
  }

  Events& events() { return channel_->test->events; }

 private:
  bool StepOnce();
  Poll<ServerMetadataHandle> PollNextFilter();
  void ForceWakeup();

  Call* const call_;
  std::shared_ptr<Channel::Impl> const channel_;
  RefCountedPtr<Arena> arena_ = channel_->arena_factory->MakeArena();
  bool run_call_finalization_ = false;
  CallFinalization call_finalization_;
  std::optional<ArenaPromise<ServerMetadataHandle>> promise_;
  Poll<ServerMetadataHandle> poll_next_filter_result_;
  Pipe<ServerMetadataHandle> pipe_server_initial_metadata_{arena_.get()};
  Pipe<MessageHandle> pipe_server_to_client_messages_{arena_.get()};
  Pipe<MessageHandle> pipe_client_to_server_messages_{arena_.get()};
  PipeSender<ServerMetadataHandle>* server_initial_metadata_sender_ = nullptr;
  PipeSender<MessageHandle>* server_to_client_messages_sender_ = nullptr;
  PipeReceiver<MessageHandle>* client_to_server_messages_receiver_ = nullptr;
  std::optional<PipeSender<ServerMetadataHandle>::PushType>
      push_server_initial_metadata_;
  std::optional<PipeReceiverNextType<ServerMetadataHandle>>
      next_server_initial_metadata_;
  std::optional<PipeSender<MessageHandle>::PushType>
      push_server_to_client_messages_;
  std::optional<PipeReceiverNextType<MessageHandle>>
      next_server_to_client_messages_;
  std::optional<PipeSender<MessageHandle>::PushType>
      push_client_to_server_messages_;
  std::optional<PipeReceiverNextType<MessageHandle>>
      next_client_to_server_messages_;
  std::optional<ServerMetadataHandle> forward_server_initial_metadata_;
  std::queue<MessageHandle> forward_client_to_server_messages_;
  std::queue<MessageHandle> forward_server_to_client_messages_;
};

FilterTestBase::Call::Impl::~Impl() {
  if (!run_call_finalization_) {
    call_finalization_.Run(nullptr);
  }
}

void FilterTestBase::Call::Impl::Start(ClientMetadataHandle md) {
  EXPECT_EQ(promise_, std::nullopt);
  promise_ = channel_->filter->MakeCallPromise(
      CallArgs{std::move(md), ClientInitialMetadataOutstandingToken::Empty(),
               nullptr, &pipe_server_initial_metadata_.sender,
               &pipe_client_to_server_messages_.receiver,
               &pipe_server_to_client_messages_.sender},
      [this](CallArgs args) -> ArenaPromise<ServerMetadataHandle> {
        server_initial_metadata_sender_ = args.server_initial_metadata;
        client_to_server_messages_receiver_ = args.client_to_server_messages;
        server_to_client_messages_sender_ = args.server_to_client_messages;
        next_server_initial_metadata_.emplace(
            pipe_server_initial_metadata_.receiver.Next());
        events().Started(call_, *args.client_initial_metadata);
        return [this]() { return PollNextFilter(); };
      });
  EXPECT_NE(promise_, std::nullopt);
  ForceWakeup();
}

Poll<ServerMetadataHandle> FilterTestBase::Call::Impl::PollNextFilter() {
  return std::exchange(poll_next_filter_result_, Pending());
}

void FilterTestBase::Call::Impl::ForwardServerInitialMetadata(
    ServerMetadataHandle md) {
  EXPECT_FALSE(forward_server_initial_metadata_.has_value());
  forward_server_initial_metadata_ = std::move(md);
  ForceWakeup();
}

void FilterTestBase::Call::Impl::ForwardMessageClientToServer(
    MessageHandle msg) {
  forward_client_to_server_messages_.push(std::move(msg));
  ForceWakeup();
}

void FilterTestBase::Call::Impl::ForwardMessageServerToClient(
    MessageHandle msg) {
  forward_server_to_client_messages_.push(std::move(msg));
  ForceWakeup();
}

void FilterTestBase::Call::Impl::FinishNextFilter(ServerMetadataHandle md) {
  poll_next_filter_result_ = std::move(md);
  ForceWakeup();
}

bool FilterTestBase::Call::Impl::StepOnce() {
  if (!promise_.has_value()) return true;

  if (forward_server_initial_metadata_.has_value() &&
      !push_server_initial_metadata_.has_value()) {
    push_server_initial_metadata_.emplace(server_initial_metadata_sender_->Push(
        std::move(*forward_server_initial_metadata_)));
    forward_server_initial_metadata_.reset();
  }

  if (push_server_initial_metadata_.has_value()) {
    auto r = (*push_server_initial_metadata_)();
    if (r.ready()) push_server_initial_metadata_.reset();
  }

  if (next_server_initial_metadata_.has_value()) {
    auto r = (*next_server_initial_metadata_)();
    if (auto* p = r.value_if_ready()) {
      if (p->has_value()) {
        events().ForwardedServerInitialMetadata(call_, *p->value());
      }
      next_server_initial_metadata_.reset();
    }
  }

  if (server_initial_metadata_sender_ != nullptr &&
      !next_server_initial_metadata_.has_value()) {

    if (!next_server_to_client_messages_.has_value()) {
      next_server_to_client_messages_.emplace(
          pipe_server_to_client_messages_.receiver.Next());
    }

    if (push_server_to_client_messages_.has_value()) {
      auto r = (*push_server_to_client_messages_)();
      if (r.ready()) push_server_to_client_messages_.reset();
    }

    {
      auto r = (*next_server_to_client_messages_)();
      if (auto* p = r.value_if_ready()) {
        if (p->has_value()) {
          events().ForwardedMessageServerToClient(call_, *p->value());
        }
        next_server_to_client_messages_.reset();
        GetContext<Activity>()->ForceImmediateRepoll();
      }
    }

    if (!push_server_to_client_messages_.has_value() &&
        !forward_server_to_client_messages_.empty()) {
      push_server_to_client_messages_.emplace(
          server_to_client_messages_sender_->Push(
              std::move(forward_server_to_client_messages_.front())));
      forward_server_to_client_messages_.pop();
      GetContext<Activity>()->ForceImmediateRepoll();
    }
  }

  if (client_to_server_messages_receiver_ != nullptr) {
    if (!next_client_to_server_messages_.has_value()) {
      next_client_to_server_messages_.emplace(
          client_to_server_messages_receiver_->Next());
    }

    if (push_client_to_server_messages_.has_value()) {
      auto r = (*push_client_to_server_messages_)();
      if (r.ready()) push_client_to_server_messages_.reset();
    }

    {
      auto r = (*next_client_to_server_messages_)();
      if (auto* p = r.value_if_ready()) {
        if (p->has_value()) {
          events().ForwardedMessageClientToServer(call_, *p->value());
        }
        next_client_to_server_messages_.reset();
        GetContext<Activity>()->ForceImmediateRepoll();
      }
    }

    if (!push_client_to_server_messages_.has_value() &&
        !forward_client_to_server_messages_.empty()) {
      push_client_to_server_messages_.emplace(
          pipe_client_to_server_messages_.sender.Push(
              std::move(forward_client_to_server_messages_.front())));
      forward_client_to_server_messages_.pop();
      GetContext<Activity>()->ForceImmediateRepoll();
    }
  }

  auto r = (*promise_)();
  if (r.pending()) return false;
  promise_.reset();
  events().Finished(call_, *r.value());
  return true;
}

class FilterTestBase::Call::ScopedContext final
    : public Activity,
      public promise_detail::Context<Arena>,
      public promise_detail::Context<CallFinalization> {
 private:
  class TestWakeable final : public Wakeable {
   public:
    explicit TestWakeable(ScopedContext* ctx)
        : tag_(ctx->DebugTag()), impl_(ctx->impl_) {}
    void Wakeup(WakeupMask) override {
      std::unique_ptr<TestWakeable> self(this);
      auto impl = impl_.lock();
      if (impl == nullptr) return;
      impl->event_engine()->Run([weak_impl = impl_]() {
        auto impl = weak_impl.lock();
        if (impl != nullptr) impl->StepLoop();
      });
    }
    void WakeupAsync(WakeupMask) override { Wakeup(0); }
    void Drop(WakeupMask) override { delete this; }
    std::string ActivityDebugTag(WakeupMask) const override { return tag_; }

   private:
    const std::string tag_;
    const std::weak_ptr<Impl> impl_;
  };

 public:
  explicit ScopedContext(std::shared_ptr<Impl> impl)
      : promise_detail::Context<Arena>(impl->arena()),
        promise_detail::Context<CallFinalization>(impl->call_finalization()),
        impl_(std::move(impl)) {}

  void Orphan() override { Crash("Orphan called on Call::ScopedContext"); }
  void ForceImmediateRepoll(WakeupMask) override { repoll_ = true; }
  Waker MakeOwningWaker() override { return Waker(new TestWakeable(this), 0); }
  Waker MakeNonOwningWaker() override {
    return Waker(new TestWakeable(this), 0);
  }
  std::string DebugTag() const override {
    return absl::StrFormat("FILTER_TEST_CALL[%p]", impl_.get());
  }

  bool repoll() const { return repoll_; }

 private:
  ScopedActivity scoped_activity_{this};
  const std::shared_ptr<Impl> impl_;
  bool repoll_ = false;
};

void FilterTestBase::Call::Impl::StepLoop() {
  for (;;) {
    ScopedContext ctx(shared_from_this());
    if (!StepOnce() && ctx.repoll()) continue;
    return;
  }
}

void FilterTestBase::Call::Impl::ForceWakeup() {
  ScopedContext(shared_from_this()).MakeOwningWaker().Wakeup();
}

FilterTestBase::Call::Call(const Channel& channel)
    : impl_(std::make_unique<Impl>(this, channel.impl_)) {}

FilterTestBase::Call::~Call() { ScopedContext x(std::move(impl_)); }

Arena* FilterTestBase::Call::arena() const { return impl_->arena(); }

ClientMetadataHandle FilterTestBase::Call::NewClientMetadata(
    std::initializer_list<std::pair<absl::string_view, absl::string_view>>
        init) {
  auto md = impl_->arena()->MakePooled<ClientMetadata>();
  for (auto& p : init) {
    auto parsed = ClientMetadata::Parse(
        p.first, Slice::FromCopiedString(p.second), false,
        p.first.length() + p.second.length() + 32,
        [p](absl::string_view, const Slice&) {
          Crash(absl::StrCat("Illegal metadata value: ", p.first, ": ",
                             p.second));
        });
    md->Set(parsed);
  }
  return md;
}

ServerMetadataHandle FilterTestBase::Call::NewServerMetadata(
    std::initializer_list<std::pair<absl::string_view, absl::string_view>>
        init) {
  auto md = impl_->arena()->MakePooled<ClientMetadata>();
  for (auto& p : init) {
    auto parsed = ServerMetadata::Parse(
        p.first, Slice::FromCopiedString(p.second), false,
        p.first.length() + p.second.length() + 32,
        [p](absl::string_view, const Slice&) {
          Crash(absl::StrCat("Illegal metadata value: ", p.first, ": ",
                             p.second));
        });
    md->Set(parsed);
  }
  return md;
}

MessageHandle FilterTestBase::Call::NewMessage(absl::string_view payload,
                                               uint32_t flags) {
  SliceBuffer buffer;
  if (!payload.empty()) buffer.Append(Slice::FromCopiedString(payload));
  return impl_->arena()->MakePooled<Message>(std::move(buffer), flags);
}

void FilterTestBase::Call::Start(ClientMetadataHandle md) {
  ScopedContext ctx(impl_);
  impl_->Start(std::move(md));
}

void FilterTestBase::Call::Cancel() {
  ScopedContext ctx(impl_);
  impl_ = absl::make_unique<Impl>(this, impl_->channel());
}

void FilterTestBase::Call::ForwardServerInitialMetadata(
    ServerMetadataHandle md) {
  impl_->ForwardServerInitialMetadata(std::move(md));
}

void FilterTestBase::Call::ForwardMessageClientToServer(MessageHandle msg) {
  impl_->ForwardMessageClientToServer(std::move(msg));
}

void FilterTestBase::Call::ForwardMessageServerToClient(MessageHandle msg) {
  impl_->ForwardMessageServerToClient(std::move(msg));
}

void FilterTestBase::Call::FinishNextFilter(ServerMetadataHandle md) {
  impl_->FinishNextFilter(std::move(md));
}

FilterTestBase::FilterTestBase() {
  FuzzingEventEngine::Options options;
  options.max_delay_run_after = std::chrono::milliseconds(500);
  options.max_delay_write = std::chrono::milliseconds(50);
  event_engine_ = std::make_shared<FuzzingEventEngine>(
      options, fuzzing_event_engine::Actions());
  grpc_event_engine::experimental::SetDefaultEventEngine(event_engine_);
  grpc_timer_manager_set_start_threaded(false);
  grpc_init();
}

FilterTestBase::~FilterTestBase() {
  grpc_shutdown();
  event_engine_->UnsetGlobalHooks();
  event_engine_.reset();
  grpc_event_engine::experimental::ShutdownDefaultEventEngine();
}

void FilterTestBase::Step() {
  event_engine_->TickUntilIdle();
  ::testing::Mock::VerifyAndClearExpectations(&events);
}

}
