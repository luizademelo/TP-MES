Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/lib/promise/party.h"

#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>
#include <limits>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/sync.h"

#ifdef GRPC_MAXIMIZE_THREADYNESS
#include "absl/random/random.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/thd.h"
#endif

namespace grpc_core {

// Attempts to increment the reference count if it's non-zero.
// Returns true if the reference count was successfully incremented,
// false if the reference count was zero.
GRPC_MUST_USE_RESULT bool Party::RefIfNonZero() {
  auto state = state_.load(std::memory_order_relaxed);
  do {
    // Check if reference count is zero
    if ((state & kRefMask) == 0) {
      return false;
    }
  } while (!state_.compare_exchange_weak(state, state + kOneRef,
                                         std::memory_order_acq_rel,
                                         std::memory_order_relaxed));
  LogStateChange("RefIfNonZero", state, state + kOneRef);
  return true;
}

// Handle class manages wakeups for Party participants
class Party::Handle final : public Wakeable {
 public:
  explicit Handle(Party* party) : party_(party) {}

  // Increment reference count
  void Ref() { refs_.fetch_add(1, std::memory_order_relaxed); }

  // Drop the associated activity and release resources
  void DropActivity() ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();
    CHECK_NE(party_, nullptr);
    party_ = nullptr;
    mu_.Unlock();
    Unref();
  }

  // Generic wakeup method that can be used for both sync and async wakeups
  void WakeupGeneric(WakeupMask wakeup_mask,
                     void (Party::*wakeup_method)(WakeupMask))
      ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();

    Party* party = party_;
    if (party != nullptr && party->RefIfNonZero()) {
      mu_.Unlock();
      // Call the specified wakeup method
      (party->*wakeup_method)(wakeup_mask);
    } else {
      // Party is null or couldn't be referenced
      mu_.Unlock();
    }

    Unref();
  }

  // Synchronous wakeup implementation
  void Wakeup(WakeupMask wakeup_mask) override ABSL_LOCKS_EXCLUDED(mu_) {
    WakeupGeneric(wakeup_mask, &Party::Wakeup);
  }

  // Asynchronous wakeup implementation
  void WakeupAsync(WakeupMask wakeup_mask) override ABSL_LOCKS_EXCLUDED(mu_) {
    WakeupGeneric(wakeup_mask, &Party::WakeupAsync);
  }

  // Drop implementation - just decreases reference count
  void Drop(WakeupMask) override { Unref(); }

  // Returns debug tag for the activity
  std::string ActivityDebugTag(WakeupMask) const override {
    MutexLock lock(&mu_);
    return party_ == nullptr ? "<unknown>" : party_->DebugTag();
  }

 private:
  // Decrement reference count and delete if it reaches zero
  void Unref() {
    if (1 == refs_.fetch_sub(1, std::memory_order_acq_rel)) {
      delete this;
    }
  }

  std::atomic<size_t> refs_{2};  // Initialized to 2 (one for Party, one for caller)
  mutable Mutex mu_;             // Protects access to party_
  Party* party_ ABSL_GUARDED_BY(mu_);  // The associated Party
};

// Creates a non-owning wakeable for the party
Wakeable* Party::Participant::MakeNonOwningWakeable(Party* party) {
  if (handle_ == nullptr) {
    handle_ = new Handle(party);
    return handle_;
  }
  handle_->Ref();
  return handle_;
}

// Participant destructor - drops associated activity
Party::Participant::~Participant() {
  if (handle_ != nullptr) {
    handle_->DropActivity();
  }
}

// Polls participant promises in sequence
bool Party::SpawnSerializer::PollParticipantPromise() {
  if (active_ == nullptr) {
    active_ = next_.Pop().value_or(nullptr);
  }
  while (active_ != nullptr) {
    // Poll the current active participant
    if (!active_->PollParticipantPromise()) return false;

    // Move to next participant
    active_ = next_.Pop().value_or(nullptr);
  }

  return false;
}

// Destroys all participants in the serializer
void Party::SpawnSerializer::Destroy() {
  if (active_ != nullptr) {
    active_->Destroy();
  }
  while (auto* p = next_.Pop().value_or(nullptr)) {
    p->Destroy();
  }
  Destruct(this);
}

namespace {

// Converts participant bitmask to JSON representation
Json ParticipantBitmaskToJson(uint64_t mask) {
  Json::Array array;
  for (size_t i = 0; i < party_detail::kMaxParticipants; i++) {
    if (mask & (1u << i)) {
      array.emplace_back(Json::FromNumber(i));
    }
  }
  return Json::FromArray(std::move(array));
}

}

Party::~Party() {}

// Converts Party state to JSON asynchronously
void Party::ToJson(absl::AnyInvocable<void(Json::Object)> f) {
  auto event_engine =
      arena_->GetContext<grpc_event_engine::experimental::EventEngine>();
  CHECK(event_engine != nullptr);
  event_engine->Run([f = std::move(f), self = Ref()]() mutable {
    self->Spawn(
        "get-json",
        [f = std::move(f), self]() mutable {
          return [f = std::move(f), self]() mutable {
            f(self->ToJsonLocked());
            return absl::OkStatus();
          };
        },
        [](absl::Status) {});
  });
}

// Converts Party state to JSON (must be called with lock held)
Json::Object Party::ToJsonLocked() {
  Json::Object obj;
  auto state = state_.load(std::memory_order_relaxed);
  obj["ref_count"] = Json::FromNumber(state >> kRefShift);
  obj["allocated_participants"] =
      ParticipantBitmaskToJson((state & kAllocatedMask) >> kAllocatedShift);
  obj["wakeup_mask"] = ParticipantBitmaskToJson(wakeup_mask_ & kWakeupMask);
  obj["locked"] = Json::FromBool((state & kLocked) != 0);
  obj["local_wakeup_mask"] = ParticipantBitmaskToJson(wakeup_mask_);
  obj["currently_polling"] = Json::FromNumber(currently_polling_);
  Json::Array participants;
  for (size_t i = 0; i < party_detail::kMaxParticipants; i++) {
    if (auto* p = participants_[i].load(std::memory_order_acquire);
        p != nullptr) {
      auto obj = p->ToJson();
      participants.emplace_back(
          Json::FromString(JsonDump(Json::FromObject(std::move(obj)))));
    }
  }
  obj["participants"] = Json::FromArray(std::move(participants));
  return obj;
}

// Cancels all remaining participants
void Party::CancelRemainingParticipants() {
  uint64_t prev_state = state_.load(std::memory_order_relaxed);
  if ((prev_state & kAllocatedMask) == 0) return;
  ScopedActivity activity(this);
  promise_detail::Context<Arena> arena_ctx(arena_.get());
  uint64_t clear_state = 0;
  do {
    // Clear all participants and mark their slots as free
    for (size_t i = 0; i < party_detail::kMaxParticipants; i++) {
      if (auto* p =
              participants_[i].exchange(nullptr, std::memory_order_acquire)) {
        clear_state |= 1ull << i << kAllocatedShift;
        p->Destroy();
      }
    }
    if (clear_state == 0) return;
  } while (!state_.compare_exchange_weak(prev_state, prev_state & ~clear_state,
                                         std::memory_order_acq_rel));
  LogStateChange("CancelRemainingParticipants", prev_state,
                 prev_state & ~clear_state);
}

// Returns debug tag with wakeup mask information
std::string Party::ActivityDebugTag(WakeupMask wakeup_mask) const {
  return absl::StrFormat("%s [parts:%x]", DebugTag(), wakeup_mask);
}

// Creates an owning waker for the current participant
Waker Party::MakeOwningWaker() {
  DCHECK(currently_polling_ != kNotPolling);
  IncrementRefCount();
  return Waker(this, 1u << currently_polling_);
}

// Creates a non-owning waker for the current participant
Waker Party::MakeNonOwningWaker() {
  DCHECK(currently_polling_ != kNotPolling);
  return Waker(participants_[currently_polling_]
                   .load(std::memory_order_relaxed)
                   ->MakeNonOwningWakeable(this),
               1u << currently_polling_);
}

// Forces immediate repoll for the specified mask
void Party::ForceImmediateRepoll(WakeupMask mask) {
  DCHECK(is_current());
  wakeup_mask_ |= mask;
}

// Runs the party with lock held and then unreferences it
void Party::RunLockedAndUnref(Party* party, uint64_t prev_state) {
  GRPC_LATENT_SEE_PARENT_SCOPE("Party::RunLocked");
#ifdef GRPC_MAXIMIZE_THREADYNESS
  // In thread-maximizing mode, run in a new thread
  Thread thd(
      "RunParty",
      [party, prev_state]() {
        ExecCtx exec_ctx;
        party->RunPartyAndUnref(prev_state);
      },
      nullptr, Thread::Options().set_joinable(false));
  thd.Start();
#else
  // In normal mode, use thread-local state to manage execution
  struct RunState;
  static thread_local RunState* g_run_state = nullptr;
  struct PartyWakeup {
    PartyWakeup() : party{nullptr} {}
    PartyWakeup(Party* party, uint64_t prev_state)
        : party{party}, prev_state{prev_state} {}
    Party* party;
    uint64_t prev_state;
  };
  struct RunState {
    explicit RunState(PartyWakeup first) : first{first}, next{} {}
    PartyWakeup first;
    PartyWakeup next;
    GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Run() {
      g_run_state = this;
      do {
        GRPC_LATENT_SEE_INNER_SCOPE("run_one_party");
        first.party->RunPartyAndUnref(first.prev_state);
        first = std::exchange(next, PartyWakeup{});
      } while (first.party != nullptr);
      DCHECK(g_run_state == this);
      g_run_state = nullptr;
    }
  };

  if (GPR_UNLIKELY(g_run_state != nullptr)) {
    // If there's already a run state, try to merge with it
    if (g_run_state->first.party == party) {
      g_run_state->first.prev_state = prev_state;
      party->Unref();
      return;
    }
    if (g_run_state->next.party == party) {
      g_run_state->next.prev_state = prev_state;
      party->Unref();
      return;
    }
    if (g_run_state->next.party != nullptr) {
      // If both slots are full, offload to event engine
      auto wakeup =
          std::exchange(g_run_state->next, PartyWakeup{party, prev_state});
      auto arena = party->arena_.get();
      auto* event_engine =
          arena->GetContext<grpc_event_engine::experimental::EventEngine>();
      CHECK(event_engine != nullptr) << "; " << GRPC_DUMP_ARGS(party, arena);
      event_engine->Run([wakeup]() {
        GRPC_LATENT_SEE_PARENT_SCOPE("Party::RunLocked offload");
        ExecCtx exec_ctx;
        RunState{wakeup}.Run();
      });
      return;
    }
    // Add to next slot if available
    g_run_state->next = PartyWakeup{party, prev_state};
    return;
  }
  // Otherwise create new run state
  RunState{{party, prev_state}}.Run();
#endif
}

// Main party execution logic
void Party::RunPartyAndUnref(uint64_t prev_state) {
  ScopedActivity activity(this);
  promise_detail::Context<Arena> arena_ctx(arena_.get());
  DCHECK_EQ(prev_state & kLocked, 0u)
      << "Party should be unlocked prior to first wakeup";
  DCHECK_GE(prev_state & kRefMask, kOneRef);

  DCHECK_EQ(prev_state & ~(kRefMask | kAllocatedMask), 0u)
      << "Party should have contained no wakeups on lock";
  prev_state |= kLocked;
#if !TARGET_OS_IPHONE
  ScopedTimeCache time_cache;
#endif
  for (;;) {
    uint64_t keep_allocated_mask = kAllocatedMask;

    // Process all wakeups
    while (wakeup_mask_ != 0) {
      auto wakeup_mask = std::exchange(wakeup_mask_, 0);
      while (wakeup_mask != 0) {
        const uint64_t t = LowestOneBit(wakeup_mask);
        const int i = absl::countr_zero(t);
        wakeup_mask ^= t;

        auto* participant = participants_[i].load(std::memory_order_acquire);
        if (GPR_UNLIKELY(participant == nullptr)) {
          GRPC_TRACE_LOG(promise_primitives, INFO)
              << "Party " << this << "                 Run:Wakeup " << i
              << " already complete";
          continue;
        }
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "Party " << this << "                 Run:Wakeup " << i;

        currently_polling_ = i;
        if (participant->PollParticipantPromise()) {
          // Participant is done - clear its slot
          participants_[i].store(nullptr, std::memory_order_relaxed);
          const uint64_t allocated_bit = (1u << i << kAllocatedShift);
          keep_allocated_mask &= ~allocated_bit;
        }
      }
    }
    currently_polling_ = kNotPolling;

    // Try to exit if no more work
    if (state_.compare_exchange_weak(
            prev_state,
            (prev_state & (kRefMask | keep_allocated_mask)) - kOneRef,
            std::memory_order_acq_rel, std::memory_order_acquire)) {
      LogStateChange("Run:End", prev_state,
                     (prev_state & (kRefMask | keep_allocated_mask)) - kOneRef);
      if ((prev_state & kRefMask) == kOneRef) {
        // Last reference - clean up
        PartyIsOver();
      }
      return;
    }

    // Otherwise continue processing
    while (!state_.compare_exchange_weak(
        prev_state, prev_state & (kRefMask | kLocked | keep_allocated_mask))) {
      // Spin until we can update the state
    }
    LogStateChange("Run:Continue", prev_state,
                   prev_state & (kRefMask | kLocked | keep_allocated_mask));
    DCHECK(prev_state & kLocked)
        << "Party should be locked; prev_state=" << prev_state;
    DCHECK_GE(prev_state & kRefMask, kOneRef);

    // Add any new wakeups that came in while we were working
    wakeup_mask_ |= prev_state & kWakeupMask;

    prev_state &= kRefMask | kLocked | keep_allocated_mask;
  }
}

#ifndef GRPC_MAXIMIZE_THREADYNESS
// Returns the next available participant slot (normal mode)
uint64_t Party::NextAllocationMask(uint64_t current_allocation_mask) {
  return LowestOneBit(~current_allocation_mask);
}
#else
// Returns a random available participant slot (thread-maximizing mode)
uint64_t Party::NextAllocationMask(uint64_t current_allocation_mask) {
  CHECK_EQ(current_allocation_mask & ~kWakeupMask, 0);
  if (current_allocation_mask == kWakeupMask) return kWakeupMask + 1;

  size_t unset_bits = 0;
  for (size_t i = 0; i < party_detail::kMaxParticipants; i++) {
    if (current_allocation_mask & (1ull << i)) continue;
    ++unset_bits;
  }
  CHECK_GT(unset_bits, 0);
  absl::BitGen bitgen;
  size_t selected = absl::Uniform<size_t>(bitgen, 0, unset_bits);
  for (size_t i = 0; i < party_detail::kMaxParticipants; i++) {
    if (current_allocation_mask & (1ull << i)) continue;
    if (selected == 0) return 1ull << i;
    --selected;
  }
  LOG(FATAL) << "unreachable";
}
#endif

// Adds a new participant to the party
size_t Party::AddParticipant(Participant* participant) {
  GRPC_LATENT_SEE_INNER_SCOPE("Party::AddParticipant");
  uint64_t state = state_.load(std::memory_order_acquire);
  uint64_t allocated;
  size_t slot;

  uint64_t