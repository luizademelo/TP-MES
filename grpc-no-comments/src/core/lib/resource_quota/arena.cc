
// Copyright 2017 gRPC authors.

#include "src/core/lib/resource_quota/arena.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <new>

#include "absl/log/log.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/alloc.h"
namespace grpc_core {

namespace {

void* ArenaStorage(size_t& initial_size) {
  size_t base_size = Arena::ArenaOverhead() +
                     GPR_ROUND_UP_TO_ALIGNMENT_SIZE(
                         arena_detail::BaseArenaContextTraits::ContextSize());
  initial_size =
      std::max(GPR_ROUND_UP_TO_ALIGNMENT_SIZE(initial_size), base_size);
  static constexpr size_t alignment =
      (GPR_CACHELINE_SIZE > GPR_MAX_ALIGNMENT &&
       GPR_CACHELINE_SIZE % GPR_MAX_ALIGNMENT == 0)
          ? GPR_CACHELINE_SIZE
          : GPR_MAX_ALIGNMENT;
  return gpr_malloc_aligned(initial_size, alignment);
}

}

Arena::~Arena() {
  for (size_t i = 0; i < arena_detail::BaseArenaContextTraits::NumContexts();
       ++i) {
    arena_detail::BaseArenaContextTraits::Destroy(i, contexts()[i]);
  }
  DestroyManagedNewObjects();
  arena_factory_->FinalizeArena(this);
  arena_factory_->allocator().Release(
      total_allocated_.load(std::memory_order_relaxed));
  Zone* z = last_zone_;
  while (z) {
    Zone* prev_z = z->prev;
    Destruct(z);
    gpr_free_aligned(z);
    z = prev_z;
  }
}

RefCountedPtr<Arena> Arena::Create(size_t initial_size,
                                   RefCountedPtr<ArenaFactory> arena_factory) {
  void* p = ArenaStorage(initial_size);
  return RefCountedPtr<Arena>(
      new (p) Arena(initial_size, std::move(arena_factory)));
}

Arena::Arena(size_t initial_size, RefCountedPtr<ArenaFactory> arena_factory)
    : initial_zone_size_(initial_size),
      total_used_(ArenaOverhead() +
                  GPR_ROUND_UP_TO_ALIGNMENT_SIZE(
                      arena_detail::BaseArenaContextTraits::ContextSize())),
      arena_factory_(std::move(arena_factory)) {
  for (size_t i = 0; i < arena_detail::BaseArenaContextTraits::NumContexts();
       ++i) {
    contexts()[i] = nullptr;
  }
  CHECK_GE(initial_size, arena_detail::BaseArenaContextTraits::ContextSize());
  arena_factory_->allocator().Reserve(initial_size);
}

void Arena::DestroyManagedNewObjects() {
  ManagedNewObject* p;

  while ((p = managed_new_head_.exchange(nullptr, std::memory_order_relaxed)) !=
         nullptr) {

    while (p != nullptr) {
      Destruct(std::exchange(p, p->next));
    }
  }
}

void Arena::Destroy() const {
  this->~Arena();
  gpr_free_aligned(const_cast<Arena*>(this));
}

void* Arena::AllocZone(size_t size) {

  static constexpr size_t zone_base_size =
      GPR_ROUND_UP_TO_ALIGNMENT_SIZE(sizeof(Zone));
  size_t alloc_size = zone_base_size + size;
  arena_factory_->allocator().Reserve(alloc_size);
  total_allocated_.fetch_add(alloc_size, std::memory_order_relaxed);
  Zone* z = new (gpr_malloc_aligned(alloc_size, GPR_MAX_ALIGNMENT)) Zone();
  auto* prev = last_zone_.load(std::memory_order_relaxed);
  do {
    z->prev = prev;
  } while (!last_zone_.compare_exchange_weak(prev, z, std::memory_order_relaxed,
                                             std::memory_order_relaxed));
  return reinterpret_cast<char*>(z) + zone_base_size;
}

void Arena::ManagedNewObject::Link(std::atomic<ManagedNewObject*>* head) {
  next = head->load(std::memory_order_relaxed);
  while (!head->compare_exchange_weak(next, this, std::memory_order_acq_rel,
                                      std::memory_order_relaxed)) {
  }
}

MemoryAllocator DefaultMemoryAllocatorForSimpleArenaAllocator() {
  return ResourceQuota::Default()->memory_quota()->CreateMemoryAllocator(
      "simple-arena-allocator");
}

RefCountedPtr<ArenaFactory> SimpleArenaAllocator(size_t initial_size,
                                                 MemoryAllocator allocator) {
  class Allocator : public ArenaFactory {
   public:
    Allocator(size_t initial_size, MemoryAllocator allocator)
        : ArenaFactory(std::move(allocator)), initial_size_(initial_size) {}

    RefCountedPtr<Arena> MakeArena() override {
      return Arena::Create(initial_size_, Ref());
    }

    void FinalizeArena(Arena*) override {

    }

   private:
    size_t initial_size_;
  };
  return MakeRefCounted<Allocator>(initial_size, std::move(allocator));
}

}
