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

GRPC_MUST_USE_RESULT bool Party::RefIfNonZero() {
  auto state = state_.load(std::memory_order_relaxed);
  do {

    if ((state & kRefMask) == 0) {
      return false;
    }
  } while (!state_.compare_exchange_weak(state, state + kOneRef,
                                         std::memory_order_acq_rel,
                                         std::memory_order_relaxed));
  LogStateChange("RefIfNonZero", state, state + kOneRef);
  return true;
}

class Party::Handle final : public Wakeable {
 public:
  explicit Handle(Party* party) : party_(party) {}

  void Ref() { refs_.fetch_add(1, std::memory_order_relaxed); }

  void DropActivity() ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();
    CHECK_NE(party_, nullptr);
    party_ = nullptr;
    mu_.Unlock();
    Unref();
  }

  void WakeupGeneric(WakeupMask wakeup_mask,
                     void (Party::*wakeup_method)(WakeupMask))
      ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();

    Party* party = party_;
    if (party != nullptr && party->RefIfNonZero()) {
      mu_.Unlock();

      (party->*wakeup_method)(wakeup_mask);
    } else {

      mu_.Unlock();
    }

    Unref();
  }

  void Wakeup(WakeupMask wakeup_mask) override ABSL_LOCKS_EXCLUDED(mu_) {
    WakeupGeneric(wakeup_mask, &Party::Wakeup);
  }

  void WakeupAsync(WakeupMask wakeup_mask) override ABSL_LOCKS_EXCLUDED(mu_) {
    WakeupGeneric(wakeup_mask, &Party::WakeupAsync);
  }

  void Drop(WakeupMask) override { Unref(); }

  std::string ActivityDebugTag(WakeupMask) const override {
    MutexLock lock(&mu_);
    return party_ == nullptr ? "<unknown>" : party_->DebugTag();
  }

 private:

  void Unref() {
    if (1 == refs_.fetch_sub(1, std::memory_order_acq_rel)) {
      delete this;
    }
  }

  std::atomic<size_t> refs_{2};
  mutable Mutex mu_;
  Party* party_ ABSL_GUARDED_BY(mu_);
};

Wakeable* Party::Participant::MakeNonOwningWakeable(Party* party) {
  if (handle_ == nullptr) {
    handle_ = new Handle(party);
    return handle_;
  }
  handle_->Ref();
  return handle_;
}

Party::Participant::~Participant() {
  if (handle_ != nullptr) {
    handle_->DropActivity();
  }
}

bool Party::SpawnSerializer::PollParticipantPromise() {
  if (active_ == nullptr) {
    active_ = next_.Pop().value_or(nullptr);
  }
  while (active_ != nullptr) {

    if (!active_->PollParticipantPromise()) return false;

    active_ = next_.Pop().value_or(nullptr);
  }

  return false;
}

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

void Party::CancelRemainingParticipants() {
  uint64_t prev_state = state_.load(std::memory_order_relaxed);
  if ((prev_state & kAllocatedMask) == 0) return;
  ScopedActivity activity(this);
  promise_detail::Context<Arena> arena_ctx(arena_.get());
  uint64_t clear_state = 0;
  do {
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

std::string Party::ActivityDebugTag(WakeupMask wakeup_mask) const {
  return absl::StrFormat("%s [parts:%x]", DebugTag(), wakeup_mask);
}

Waker Party::MakeOwningWaker() {
  DCHECK(currently_polling_ != kNotPolling);
  IncrementRefCount();
  return Waker(this, 1u << currently_polling_);
}

Waker Party::MakeNonOwningWaker() {
  DCHECK(currently_polling_ != kNotPolling);
  return Waker(participants_[currently_polling_]
                   .load(std::memory_order_relaxed)
                   ->MakeNonOwningWakeable(this),
               1u << currently_polling_);
}

void Party::ForceImmediateRepoll(WakeupMask mask) {
  DCHECK(is_current());
  wakeup_mask_ |= mask;
}

void Party::RunLockedAndUnref(Party* party, uint64_t prev_state) {
  GRPC_LATENT_SEE_PARENT_SCOPE("Party::RunLocked");
#ifdef GRPC_MAXIMIZE_THREADYNESS
  Thread thd(
      "RunParty",
      [party, prev_state]() {
        ExecCtx exec_ctx;
        party->RunPartyAndUnref(prev_state);
      },
      nullptr, Thread::Options().set_joinable(false));
  thd.Start();
#else
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
    g_run_state->next = PartyWakeup{party, prev_state};
    return;
  }
  RunState{{party, prev_state}}.Run();
#endif
}

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
          participants_[i].store(nullptr, std::memory_order_relaxed);
          const uint64_t allocated_bit = (1u << i << kAllocatedShift);
          keep_allocated_mask &= ~allocated_bit;
        }
      }
    }
    currently_polling_ = kNotPolling;

    if (state_.compare_exchange_weak(
            prev_state,
            (prev_state & (kRefMask | keep_allocated_mask)) - kOneRef,
            std::memory_order_acq_rel, std::memory_order_acquire)) {
      LogStateChange("Run:End", prev_state,
                     (prev_state & (kRefMask | keep_allocated_mask)) - kOneRef);
      if ((prev_state & kRefMask) == kOneRef) {

        PartyIsOver();
      }
      return;
    }

    while (!state_.compare_exchange_weak(
        prev_state, prev_state & (kRefMask | kLocked | keep_allocated_mask))) {

    }
    LogStateChange("Run:Continue", prev_state,
                   prev_state & (kRefMask | kLocked | keep_allocated_mask));
    DCHECK(prev_state & kLocked)
        << "Party should be locked; prev_state=" << prev_state;
    DCHECK_GE(prev_state & kRefMask, kOneRef);

    wakeup_mask_ |= prev_state & kWakeupMask;

    prev_state &= kRefMask | kLocked | keep_allocated_mask;
  }
}

#ifndef GRPC_MAXIMIZE_THREADYNESS
uint64_t Party::NextAllocationMask(uint64_t current_allocation_mask) {
  return LowestOneBit(~current_allocation_mask);
}
#else
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

size_t Party::AddParticipant(Participant* participant) {
  GRPC_LATENT_SEE_INNER_SCOPE("Party::AddParticipant");
  uint64_t state = state_.load(std::memory_order_acquire);
  uint64_t allocated;
  size_t slot;

  uint64_t wakeup_mask;
  uint64_t new_state;
  do {
    allocated = (state & kAllocatedMask) >> kAllocatedShift;
    wakeup_mask = NextAllocationMask(allocated);
    if (GPR_UNLIKELY((wakeup_mask & kWakeupMask) == 0)) {
      return std::numeric_limits<size_t>::max();
    }
    DCHECK_NE(wakeup_mask & kWakeupMask, 0u)
        << "No available slots for new participant; allocated=" << allocated
        << " state=" << state << " wakeup_mask=" << wakeup_mask;
    allocated |= wakeup_mask;
    slot = absl::countr_zero(wakeup_mask);

    new_state = (state | (allocated << kAllocatedShift)) + kOneRef;
  } while (!state_.compare_exchange_weak(
      state, new_state, std::memory_order_acq_rel, std::memory_order_acquire));
  LogStateChange("AddParticipantsAndRef", state, new_state);
  GRPC_TRACE_LOG(party_state, INFO)
      << "Party " << this << "                 AddParticipant: " << slot
      << " [participant=" << participant << "]";
  participants_[slot].store(participant, std::memory_order_release);

  WakeupFromState<true>(new_state, wakeup_mask);
  return slot;
}

void Party::MaybeAsyncAddParticipant(Participant* participant) {
  const size_t slot = AddParticipant(participant);
  if (slot != std::numeric_limits<size_t>::max()) return;

  IncrementRefCount();
  VLOG_EVERY_N_SEC(2, 10) << "Delaying addition of participant to party "
                          << this << " because it is full.";
  arena_->GetContext<grpc_event_engine::experimental::EventEngine>()->Run(
      [this, participant]() mutable {
        ExecCtx exec_ctx;
        MaybeAsyncAddParticipant(participant);
        Unref();
      });
}

void Party::WakeupAsync(WakeupMask wakeup_mask) {

  uint64_t prev_state = state_.load(std::memory_order_relaxed);
  LogStateChange("ScheduleWakeup", prev_state,
                 prev_state | (wakeup_mask & kWakeupMask) | kLocked);
  while (true) {
    if ((prev_state & kLocked) == 0) {
      if (state_.compare_exchange_weak(prev_state, prev_state | kLocked,
                                       std::memory_order_acq_rel,
                                       std::memory_order_acquire)) {
        LogStateChange("WakeupAsync", prev_state, prev_state | kLocked);
        wakeup_mask_ |= wakeup_mask;
        arena_->GetContext<grpc_event_engine::experimental::EventEngine>()->Run(
            [this, prev_state]() {
              GRPC_LATENT_SEE_PARENT_SCOPE("Party::WakeupAsync");
              ExecCtx exec_ctx;
              RunLockedAndUnref(this, prev_state);
            });
        return;
      }
    } else {
      if (state_.compare_exchange_weak(
              prev_state, (prev_state | wakeup_mask) - kOneRef,
              std::memory_order_acq_rel, std::memory_order_acquire)) {
        LogStateChange("WakeupAsync", prev_state, prev_state | wakeup_mask);
        return;
      }
    }
  }
}

void Party::Drop(WakeupMask) { Unref(); }

void Party::PartyIsOver() {
  CancelRemainingParticipants();
  auto arena = std::move(arena_);
  this->~Party();
}

}
