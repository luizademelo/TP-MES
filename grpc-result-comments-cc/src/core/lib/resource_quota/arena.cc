Here's the commented version of the code:

```c++
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

// Allocates and returns memory for arena storage with proper alignment
// Adjusts initial_size to ensure it meets minimum requirements
void* ArenaStorage(size_t& initial_size) {
  // Calculate base size including arena overhead and context space
  size_t base_size = Arena::ArenaOverhead() +
                     GPR_ROUND_UP_TO_ALIGNMENT_SIZE(
                         arena_detail::BaseArenaContextTraits::ContextSize());
  // Ensure initial_size is at least base_size and properly aligned
  initial_size =
      std::max(GPR_ROUND_UP_TO_ALIGNMENT_SIZE(initial_size), base_size);
  // Determine alignment - prefer cache line size if it's compatible
  static constexpr size_t alignment =
      (GPR_CACHELINE_SIZE > GPR_MAX_ALIGNMENT &&
       GPR_CACHELINE_SIZE % GPR_MAX_ALIGNMENT == 0)
          ? GPR_CACHELINE_SIZE
          : GPR_MAX_ALIGNMENT;
  // Allocate aligned memory
  return gpr_malloc_aligned(initial_size, alignment);
}

}  // namespace

// Arena destructor - cleans up all allocated resources
Arena::~Arena() {
  // Destroy all contexts
  for (size_t i = 0; i < arena_detail::BaseArenaContextTraits::NumContexts();
       ++i) {
    arena_detail::BaseArenaContextTraits::Destroy(i, contexts()[i]);
  }
  // Clean up managed objects
  DestroyManagedNewObjects();
  // Notify factory about arena destruction
  arena_factory_->FinalizeArena(this);
  // Release allocated memory back to factory's allocator
  arena_factory_->allocator().Release(
      total_allocated_.load(std::memory_order_relaxed));
  // Free all zones in reverse allocation order
  Zone* z = last_zone_;
  while (z) {
    Zone* prev_z = z->prev;
    Destruct(z);
    gpr_free_aligned(z);
    z = prev_z;
  }
}

// Creates a new Arena instance with given initial size and factory
RefCountedPtr<Arena> Arena::Create(size_t initial_size,
                                   RefCountedPtr<ArenaFactory> arena_factory) {
  // Allocate storage for arena
  void* p = ArenaStorage(initial_size);
  // Construct arena in-place using placement new
  return RefCountedPtr<Arena>(
      new (p) Arena(initial_size, std::move(arena_factory)));
}

// Arena constructor
Arena::Arena(size_t initial_size, RefCountedPtr<ArenaFactory> arena_factory)
    : initial_zone_size_(initial_size),
      total_used_(ArenaOverhead() +
                  GPR_ROUND_UP_TO_ALIGNMENT_SIZE(
                      arena_detail::BaseArenaContextTraits::ContextSize())),
      arena_factory_(std::move(arena_factory)) {
  // Initialize all contexts to nullptr
  for (size_t i = 0; i < arena_detail::BaseArenaContextTraits::NumContexts();
       ++i) {
    contexts()[i] = nullptr;
  }
  // Verify initial size is sufficient for context storage
  CHECK_GE(initial_size, arena_detail::BaseArenaContextTraits::ContextSize());
  // Reserve initial memory in allocator
  arena_factory_->allocator().Reserve(initial_size);
}

// Destroys all managed objects created with operator new
void Arena::DestroyManagedNewObjects() {
  ManagedNewObject* p;

  // Atomically exchange head with nullptr to claim ownership of the list
  while ((p = managed_new_head_.exchange(nullptr, std::memory_order_relaxed)) !=
         nullptr) {
    // Iterate through the list and destroy each object
    while (p != nullptr) {
      Destruct(std::exchange(p, p->next));
    }
  }
}

// Destroys the arena and frees its memory
void Arena::Destroy() const {
  // Explicitly call destructor
  this->~Arena();
  // Free memory
  gpr_free_aligned(const_cast<Arena*>(this));
}

// Allocates a new memory zone in the arena
void* Arena::AllocZone(size_t size) {
  // Calculate total allocation size including zone header
  static constexpr size_t zone_base_size =
      GPR_ROUND_UP_TO_ALIGNMENT_SIZE(sizeof(Zone));
  size_t alloc_size = zone_base_size + size;
  // Reserve memory in allocator
  arena_factory_->allocator().Reserve(alloc_size);
  // Track total allocated memory
  total_allocated_.fetch_add(alloc_size, std::memory_order_relaxed);
  // Allocate and construct new zone
  Zone* z = new (gpr_malloc_aligned(alloc_size, GPR_MAX_ALIGNMENT)) Zone();
  // Atomically link the new zone into the list
  auto* prev = last_zone_.load(std::memory_order_relaxed);
  do {
    z->prev = prev;
  } while (!last_zone_.compare_exchange_weak(prev, z, std::memory_order_relaxed,
                                             std::memory_order_relaxed));
  // Return memory after the zone header
  return reinterpret_cast<char*>(z) + zone_base_size;
}

// Links a managed object into the arena's list
void Arena::ManagedNewObject::Link(std::atomic<ManagedNewObject*>* head) {
  // Atomically insert this object at the head of the list
  next = head->load(std::memory_order_relaxed);
  while (!head->compare_exchange_weak(next, this, std::memory_order_acq_rel,
                                      std::memory_order_relaxed)) {
    // Retry if compare_exchange fails
  }
}

// Creates a default memory allocator for simple arena allocator
MemoryAllocator DefaultMemoryAllocatorForSimpleArenaAllocator() {
  return ResourceQuota::Default()->memory_quota()->CreateMemoryAllocator(
      "simple-arena-allocator");
}

// Creates a simple arena factory with given initial size and allocator
RefCountedPtr<ArenaFactory> SimpleArenaAllocator(size_t initial_size,
                                                 MemoryAllocator allocator) {
  // Implementation of simple arena factory
  class Allocator : public ArenaFactory {
   public:
    Allocator(size_t initial_size, MemoryAllocator allocator)
        : ArenaFactory(std::move(allocator)), initial_size_(initial_size) {}

    // Creates a new arena with configured initial size
    RefCountedPtr<Arena> MakeArena() override {
      return Arena::Create(initial_size_, Ref());
    }

    // No-op finalization for simple arena
    void FinalizeArena(Arena*) override {}

   private:
    size_t initial_size_;
  };
  // Create and return an instance of the simple allocator
  return MakeRefCounted<Allocator>(initial_size, std::move(allocator));
}

}  // namespace grpc_core
```