// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_PARTY_H
#define GRPC_SRC_CORE_LIB_PROMISE_PARTY_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <limits>
#include <string>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/util/check_class_size.h"
#include "src/core/util/construct_destruct.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

namespace party_detail {

static constexpr size_t kMaxParticipants = 16;

}

class Party : public Activity, private Wakeable {
 private:

  class Handle;

  class Participant {
   public:

    virtual bool PollParticipantPromise() = 0;

    virtual void Destroy() = 0;

    virtual Json::Object ToJson() = 0;

    Wakeable* MakeNonOwningWakeable(Party* party);

   protected:
    ~Participant();

   private:
    Handle* handle_ = nullptr;
  };

 public:
  Party(const Party&) = delete;
  Party& operator=(const Party&) = delete;

  static RefCountedPtr<Party> Make(RefCountedPtr<Arena> arena) {
    auto* arena_ptr = arena.get();
    return RefCountedPtr<Party>(arena_ptr->New<Party>(std::move(arena)));
  }

  class WakeupHold {
   public:
    WakeupHold() = default;
    explicit WakeupHold(Party* party)
        : prev_state_(party->state_.load(std::memory_order_relaxed)) {

      if ((prev_state_ & kLocked) == 0 &&
          party->state_.compare_exchange_weak(prev_state_,
                                              (prev_state_ | kLocked) + kOneRef,
                                              std::memory_order_relaxed)) {
        DCHECK_EQ(prev_state_ & ~(kRefMask | kAllocatedMask), 0u)
            << "Party should have contained no wakeups on lock";

        party->LogStateChange("WakeupHold", prev_state_,
                              (prev_state_ | kLocked) + kOneRef);
        party_ = party;
      }
    }
    WakeupHold(const WakeupHold&) = delete;
    WakeupHold& operator=(const WakeupHold&) = delete;
    WakeupHold(WakeupHold&& other) noexcept
        : party_(std::exchange(other.party_, nullptr)),
          prev_state_(other.prev_state_) {}
    WakeupHold& operator=(WakeupHold&& other) noexcept {
      std::swap(party_, other.party_);
      std::swap(prev_state_, other.prev_state_);
      return *this;
    }

    ~WakeupHold() {
      if (party_ == nullptr) return;
      party_->RunLockedAndUnref(party_, prev_state_);
    }

   private:
    Party* party_ = nullptr;
    uint64_t prev_state_;
  };

  class SpawnSerializer final : private Participant {
   public:

    template <class Factory>
    void Spawn(Factory factory) {
      auto empty_completion = [](Empty) {};
      next_.Push(new ParticipantImpl<Factory, decltype(empty_completion)>(
          "SpawnSerializer", std::move(factory), empty_completion));
      party_->WakeupFromState<false>(
          party_->state_.load(std::memory_order_relaxed), wakeup_mask_);
    }

    Json::Object ToJson() override {
      Json::Object obj;
      if (active_ != nullptr) {
        obj["active"] = Json::FromObject(active_->ToJson());
      }
      Json::Array queued;
      next_.ForEach([&](Participant* p) {
        queued.emplace_back(Json::FromObject(p->ToJson()));
      });
      obj["queued"] = Json::FromArray(std::move(queued));
      return obj;
    }

   private:
    friend class Party;
    friend class Arena;

    bool PollParticipantPromise() override;
    void Destroy() override;

    explicit SpawnSerializer(Party* party)
        : next_(party->arena()), party_(party) {}

    ArenaSpsc<Participant*, false> next_;

    Participant* active_ = nullptr;

    WakeupMask wakeup_mask_;

    Party* const party_;
  };

  template <typename Factory, typename OnComplete>
  void Spawn(absl::string_view name, Factory promise_factory,
             OnComplete on_complete);

  template <typename Factory>
  auto SpawnWaitable(absl::string_view name, Factory factory);

  void Orphan() final { Crash("unused"); }

  void ForceImmediateRepoll(WakeupMask mask) final;
  WakeupMask CurrentParticipant() const final {
    DCHECK(currently_polling_ != kNotPolling);
    return 1u << currently_polling_;
  }
  Waker MakeOwningWaker() final;
  Waker MakeNonOwningWaker() final;
  std::string ActivityDebugTag(WakeupMask wakeup_mask) const final;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void IncrementRefCount() {
    const uint64_t prev_state =
        state_.fetch_add(kOneRef, std::memory_order_relaxed);
    LogStateChange("IncrementRefCount", prev_state, prev_state + kOneRef);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Unref() {
    uint64_t prev_state = state_.fetch_sub(kOneRef, std::memory_order_acq_rel);
    LogStateChange("Unref", prev_state, prev_state - kOneRef);
    if ((prev_state & kRefMask) == kOneRef) PartyIsOver();
  }

  RefCountedPtr<Party> Ref() {
    IncrementRefCount();
    return RefCountedPtr<Party>(this);
  }

  template <typename T>
  RefCountedPtr<T> RefAsSubclass() {
    IncrementRefCount();
    return RefCountedPtr<T>(DownCast<T*>(this));
  }

  Arena* arena() { return arena_.get(); }

  SpawnSerializer* MakeSpawnSerializer() {
    auto* const serializer = arena_->New<SpawnSerializer>(this);
    const size_t slot = AddParticipant(serializer);
    DCHECK_NE(slot, std::numeric_limits<size_t>::max());
    serializer->wakeup_mask_ = 1ull << slot;
    return serializer;
  }

  void ToJson(absl::AnyInvocable<void(Json::Object)>);

 protected:
  friend class Arena;

  explicit Party(RefCountedPtr<Arena> arena) : arena_(std::move(arena)) {
    CHECK(arena_->GetContext<grpc_event_engine::experimental::EventEngine>() !=
          nullptr);
  }
  ~Party() override;

  void RunPartyAndUnref(uint64_t prev_state);

  bool RefIfNonZero();

 private:

  template <typename SuppliedFactory, typename OnComplete>
  class ParticipantImpl final : public Participant {
    using Factory = promise_detail::OncePromiseFactory<void, SuppliedFactory>;
    using Promise = typename Factory::Promise;

   public:
    ParticipantImpl(absl::string_view, SuppliedFactory promise_factory,
                    OnComplete on_complete)
        : on_complete_(std::move(on_complete)) {
      Construct(&factory_, std::move(promise_factory));
    }
    ~ParticipantImpl() {
      if (!started_) {
        Destruct(&factory_);
      } else {
        Destruct(&promise_);
      }
    }

    bool PollParticipantPromise() override {
      if (!started_) {
        auto p = factory_.Make();
        Destruct(&factory_);
        Construct(&promise_, std::move(p));
        started_ = true;
      }
      auto p = promise_();
      if (auto* r = p.value_if_ready()) {
        on_complete_(std::move(*r));
        delete this;
        return true;
      }
      return false;
    }

    Json::Object ToJson() override {
      Json::Object obj;
      obj["on_complete"] =
          Json::FromString(std::string(TypeName<OnComplete>()));
      if (!started_) {
        obj["factory"] = Json::FromString(
            std::string(TypeName<typename Factory::UnderlyingFactory>()));
      } else {
        obj["promise"] = PromiseAsJson(promise_);
      }
      return obj;
    }

    void Destroy() override { delete this; }

   private:
    union {
      GPR_NO_UNIQUE_ADDRESS Factory factory_;
      GPR_NO_UNIQUE_ADDRESS Promise promise_;
    };
    GPR_NO_UNIQUE_ADDRESS OnComplete on_complete_;
    bool started_ = false;
  };

  template <typename SuppliedFactory>
  class PromiseParticipantImpl final
      : public RefCounted<PromiseParticipantImpl<SuppliedFactory>,
                          NonPolymorphicRefCount>,
        public Participant {
    using Factory = promise_detail::OncePromiseFactory<void, SuppliedFactory>;
    using Promise = typename Factory::Promise;
    using Result = typename Promise::Result;

   public:
    PromiseParticipantImpl(absl::string_view, SuppliedFactory promise_factory) {
      Construct(&factory_, std::move(promise_factory));
    }

    ~PromiseParticipantImpl() {
      switch (state_.load(std::memory_order_acquire)) {
        case State::kFactory:
          Destruct(&factory_);
          break;
        case State::kPromise:
          Destruct(&promise_);
          break;
        case State::kResult:
          Destruct(&result_);
          break;
      }
    }

    bool PollParticipantPromise() override {
      switch (state_.load(std::memory_order_relaxed)) {
        case State::kFactory: {
          auto p = factory_.Make();
          Destruct(&factory_);
          Construct(&promise_, std::move(p));
          state_.store(State::kPromise, std::memory_order_relaxed);
        }
          [[fallthrough]];
        case State::kPromise: {
          auto p = promise_();
          if (auto* r = p.value_if_ready()) {
            Destruct(&promise_);
            Construct(&result_, std::move(*r));
            state_.store(State::kResult, std::memory_order_release);
            waiter_.Wakeup();
            this->Unref();
            return true;
          }
          return false;
        }
        case State::kResult:
          Crash(
              "unreachable: promises should not be repolled after completion");
      }
    }

    Poll<Result> PollCompletion() {
      switch (state_.load(std::memory_order_acquire)) {
        case State::kFactory:
        case State::kPromise:
          return Pending{};
        case State::kResult:
          return std::move(result_);
      }
    }

    void Destroy() override { this->Unref(); }

    Json::Object ToJson() override {
      Json::Object obj;
      switch (state_.load(std::memory_order_relaxed)) {
        case State::kFactory:
          obj["factory"] = Json::FromString(
              std::string(TypeName<typename Factory::UnderlyingFactory>()));
          break;
        case State::kPromise:
          obj["promise"] = PromiseAsJson(promise_);
          break;
        case State::kResult:
          obj["result"] = Json::FromString(
              std::string(TypeName<typename Promise::Result>()));
          break;
      }
      return obj;
    }

   private:
    enum class State : uint8_t { kFactory, kPromise, kResult };
    union {
      GPR_NO_UNIQUE_ADDRESS Factory factory_;
      GPR_NO_UNIQUE_ADDRESS Promise promise_;
      GPR_NO_UNIQUE_ADDRESS Result result_;
    };
    Waker waiter_{GetContext<Activity>()->MakeOwningWaker()};
    std::atomic<State> state_{State::kFactory};
  };

  static constexpr uint64_t kWakeupMask    = 0x0000'0000'0000'ffff;
  // Bits used to store 16 bits of allocated participant slots.
  static constexpr uint64_t kAllocatedMask = 0x0000'0000'ffff'0000;

  static constexpr uint64_t kLocked        = 0x0000'0008'0000'0000;
  // Bits used to store 24 bits of ref counts
  static constexpr uint64_t kRefMask       = 0xffff'ff00'0000'0000;

  static constexpr size_t kAllocatedShift = 16;

  static constexpr size_t kRefShift = 40;

  static constexpr uint64_t kOneRef = 1ull << kRefShift;

  void CancelRemainingParticipants();

  static void RunLockedAndUnref(Party* party, uint64_t prev_state);

  void PartyIsOver();

  void Wakeup(WakeupMask wakeup_mask) final {
    GRPC_LATENT_SEE_INNER_SCOPE("Party::Wakeup");
    if (Activity::current() == this) {
      wakeup_mask_ |= wakeup_mask;
      Unref();
      return;
    }
    WakeupFromState<true>(state_.load(std::memory_order_relaxed), wakeup_mask);
  }

  template <bool kReffed>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void WakeupFromState(
      uint64_t cur_state, WakeupMask wakeup_mask) {
    GRPC_LATENT_SEE_INNER_SCOPE("Party::WakeupFromState");
    DCHECK_NE(wakeup_mask & kWakeupMask, 0u)
        << "Wakeup mask must be non-zero: " << wakeup_mask;
    while (true) {
      if (cur_state & kLocked) {

        if (kReffed) {
          DCHECK_GT(cur_state & kRefMask, kOneRef);
        } else {
          DCHECK_GE(cur_state & kRefMask, kOneRef);
        }
        const uint64_t new_state =
            (cur_state | wakeup_mask) - (kReffed ? kOneRef : 0);
        if (state_.compare_exchange_weak(cur_state, new_state,
                                         std::memory_order_release)) {
          LogStateChange("Wakeup", cur_state, cur_state | wakeup_mask);
          return;
        }
      } else {

        DCHECK_EQ(cur_state & kWakeupMask, 0u);
        const uint64_t new_state =
            (cur_state | kLocked) + (kReffed ? 0 : kOneRef);
        if (state_.compare_exchange_weak(cur_state, new_state,
                                         std::memory_order_acq_rel)) {
          LogStateChange("WakeupAndRun", cur_state, new_state);
          wakeup_mask_ |= wakeup_mask;
          RunLockedAndUnref(this, cur_state);
          return;
        }
      }
    }
  }

  void WakeupAsync(WakeupMask wakeup_mask) final;
  void Drop(WakeupMask wakeup_mask) final;

  size_t AddParticipant(Participant* participant);
  void MaybeAsyncAddParticipant(Participant* participant);

  static uint64_t NextAllocationMask(uint64_t current_allocation_mask);

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void LogStateChange(
      const char* op, uint64_t prev_state, uint64_t new_state,
      DebugLocation loc = {}) {
    GRPC_TRACE_LOG(party_state, INFO).AtLocation(loc.file(), loc.line())
        << this << " " << op << " "
        << absl::StrFormat("%016" PRIx64 " -> %016" PRIx64, prev_state,
                           new_state);
  }

  Json::Object ToJsonLocked();

  static constexpr uint8_t kNotPolling = 255;

  std::atomic<uint64_t> state_{kOneRef};
  uint8_t currently_polling_ = kNotPolling;
  WakeupMask wakeup_mask_ = 0;

  std::atomic<Participant*> participants_[party_detail::kMaxParticipants] = {};
  RefCountedPtr<Arena> arena_;
};

GRPC_CHECK_CLASS_SIZE(Party, 180);

template <>
struct ContextSubclass<Party> {
  using Base = Activity;
};

template <typename Factory, typename OnComplete>
void Party::Spawn(absl::string_view name, Factory promise_factory,
                  OnComplete on_complete) {
  GRPC_TRACE_LOG(party_state, INFO) << "PARTY[" << this << "]: spawn " << name;
  MaybeAsyncAddParticipant(new ParticipantImpl<Factory, OnComplete>(
      name, std::move(promise_factory), std::move(on_complete)));
}

template <typename Factory>
auto Party::SpawnWaitable(absl::string_view name, Factory promise_factory) {
  GRPC_TRACE_LOG(party_state, INFO) << "PARTY[" << this << "]: spawn " << name;
  auto participant = MakeRefCounted<PromiseParticipantImpl<Factory>>(
      name, std::move(promise_factory));
  Participant* p = participant->Ref().release();
  MaybeAsyncAddParticipant(p);
  return [participant = std::move(participant)]() mutable {
    return participant->PollCompletion();
  };
}

}

#endif
