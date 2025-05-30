
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_ARENA_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_ARENA_H

#include <grpc/event_engine/memory_allocator.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <cstddef>
#include <iosfwd>
#include <memory>
#include <utility>

#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/alloc.h"
#include "src/core/util/construct_destruct.h"

namespace grpc_core {

class Arena;

template <typename T>
struct ArenaContextType;

namespace arena_detail {

class BaseArenaContextTraits {
 public:

  static uint16_t NumContexts() {
    return static_cast<uint16_t>(RegisteredTraits().size());
  }

  static size_t ContextSize() { return NumContexts() * sizeof(void*); }

  static void Destroy(uint16_t id, void* ptr) {
    if (ptr == nullptr) return;
    RegisteredTraits()[id](ptr);
  }

 protected:

  static uint16_t MakeId(void (*destroy)(void* ptr)) {
    auto& traits = RegisteredTraits();
    const uint16_t id = static_cast<uint16_t>(traits.size());
    traits.push_back(destroy);
    return id;
  }

 private:
  static std::vector<void (*)(void*)>& RegisteredTraits() {
    static NoDestruct<std::vector<void (*)(void*)>> registered_traits;
    return *registered_traits;
  }
};

template <typename T>
class ArenaContextTraits : public BaseArenaContextTraits {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static uint16_t id() { return id_; }

 private:
  static const uint16_t id_;
};

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void DestroyArenaContext(void* p) {
  ArenaContextType<T>::Destroy(static_cast<T*>(p));
}

template <typename T>
const uint16_t ArenaContextTraits<T>::id_ =
    BaseArenaContextTraits::MakeId(DestroyArenaContext<T>);

template <typename T, typename A, typename B>
struct IfArray {
  using Result = A;
};

template <typename T, typename A, typename B>
struct IfArray<T[], A, B> {
  using Result = B;
};

struct UnrefDestroy {
  void operator()(const Arena* arena) const;
};

}

class ArenaFactory : public RefCounted<ArenaFactory> {
 public:
  virtual RefCountedPtr<Arena> MakeArena() = 0;
  virtual void FinalizeArena(Arena* arena) = 0;

  MemoryAllocator& allocator() { return allocator_; }

 protected:
  explicit ArenaFactory(MemoryAllocator allocator)
      : allocator_(std::move(allocator)) {}

 private:
  MemoryAllocator allocator_;
};

MemoryAllocator DefaultMemoryAllocatorForSimpleArenaAllocator();
RefCountedPtr<ArenaFactory> SimpleArenaAllocator(
    size_t initial_size = 1024,
    MemoryAllocator allocator =
        DefaultMemoryAllocatorForSimpleArenaAllocator());

class Arena final : public RefCounted<Arena, NonPolymorphicRefCount,
                                      arena_detail::UnrefDestroy> {
 public:

  static RefCountedPtr<Arena> Create(size_t initial_size,
                                     RefCountedPtr<ArenaFactory> arena_factory);

  void DestroyManagedNewObjects();

  size_t TotalUsedBytes() const {
    return total_used_.load(std::memory_order_relaxed);
  }

  void* Alloc(size_t size) {
    size = GPR_ROUND_UP_TO_ALIGNMENT_SIZE(size);
    size_t begin = total_used_.fetch_add(size, std::memory_order_relaxed);
    if (begin + size <= initial_zone_size_) {
      return reinterpret_cast<char*>(this) + begin;
    } else {
      return AllocZone(size);
    }
  }

  template <typename T, typename... Args>
  T* New(Args&&... args) {
    T* t = static_cast<T*>(Alloc(sizeof(T)));
    new (t) T(std::forward<Args>(args)...);
    return t;
  }

  template <typename T, typename... Args>
  T* ManagedNew(Args&&... args) {
    auto* p = New<ManagedNewImpl<T>>(std::forward<Args>(args)...);
    p->Link(&managed_new_head_);
    return &p->t;
  }

  template <typename T, typename... Args>
  absl::enable_if_t<std::is_same<typename T::RefCountedUnrefBehaviorType,
                                 UnrefCallDtor>::value,
                    RefCountedPtr<T>>
  MakeRefCounted(Args&&... args) {
    return RefCountedPtr<T>(New<T>(std::forward<Args>(args)...));
  }

  class PooledDeleter {
   public:
    PooledDeleter() = default;
    explicit PooledDeleter(std::nullptr_t) : delete_(false) {}
    template <typename T>
    void operator()(T* p) {

      if (delete_) delete p;
    }

    bool has_freelist() const { return delete_; }

   private:
    bool delete_ = true;
  };

  class ArrayPooledDeleter {
   public:
    ArrayPooledDeleter() = default;
    explicit ArrayPooledDeleter(std::nullptr_t) : delete_(false) {}
    template <typename T>
    void operator()(T* p) {

      if (delete_) delete[] p;
    }

    bool has_freelist() const { return delete_; }

   private:
    bool delete_ = true;
  };

  template <typename T>
  using PoolPtr =
      std::unique_ptr<T, typename arena_detail::IfArray<
                             T, PooledDeleter, ArrayPooledDeleter>::Result>;

  template <typename T, typename... Args>
  static PoolPtr<T> MakePooled(Args&&... args) {
    return PoolPtr<T>(new T(std::forward<Args>(args)...), PooledDeleter());
  }

  template <typename T>
  static PoolPtr<T> MakePooledForOverwrite() {
    return PoolPtr<T>(new T, PooledDeleter());
  }

  template <typename T>
  PoolPtr<T[]> MakePooledArray(size_t n) {
    return PoolPtr<T[]>(new T[n], ArrayPooledDeleter());
  }

  template <typename T, typename... Args>
  T* NewPooled(Args&&... args) {
    return new T(std::forward<Args>(args)...);
  }

  template <typename T>
  void DeletePooled(T* p) {
    delete p;
  }

  template <typename T>
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION T* GetContext() {
    return static_cast<T*>(
        contexts()[arena_detail::ArenaContextTraits<T>::id()]);
  }

  template <typename T>
  void SetContext(T* context) {
    void*& slot = contexts()[arena_detail::ArenaContextTraits<T>::id()];
    if (slot != nullptr) {
      ArenaContextType<T>::Destroy(static_cast<T*>(slot));
    }
    slot = context;
    DCHECK_EQ(GetContext<T>(), context);
  }

  static size_t ArenaOverhead() {
    return GPR_ROUND_UP_TO_ALIGNMENT_SIZE(sizeof(Arena));
  }
  static size_t ArenaZoneOverhead() {
    return GPR_ROUND_UP_TO_ALIGNMENT_SIZE(sizeof(Zone));
  }

 private:
  friend struct arena_detail::UnrefDestroy;

  struct Zone {
    Zone* prev;
  };

  struct ManagedNewObject {
    ManagedNewObject* next = nullptr;
    void Link(std::atomic<ManagedNewObject*>* head);
    virtual ~ManagedNewObject() = default;
  };

  template <typename T>
  struct ManagedNewImpl : public ManagedNewObject {
    T t;
    template <typename... Args>
    explicit ManagedNewImpl(Args&&... args) : t(std::forward<Args>(args)...) {}
  };

  explicit Arena(size_t initial_size,
                 RefCountedPtr<ArenaFactory> arena_factory);

  ~Arena();

  void* AllocZone(size_t size);
  void Destroy() const;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void** contexts() {
    return reinterpret_cast<void**>(this + 1);
  }

  const size_t initial_zone_size_;
  std::atomic<size_t> total_used_;
  std::atomic<size_t> total_allocated_{initial_zone_size_};

  std::atomic<Zone*> last_zone_{nullptr};
  std::atomic<ManagedNewObject*> managed_new_head_{nullptr};
  RefCountedPtr<ArenaFactory> arena_factory_;
};

template <typename T, bool kOptimizeAlignment = true>
class ArenaSpsc {
 public:
  explicit ArenaSpsc(Arena* arena) : arena_(arena) {}

  ~ArenaSpsc() {
    while (Pop().has_value()) {
    }
  }

  ArenaSpsc(const ArenaSpsc&) = delete;
  ArenaSpsc& operator=(const ArenaSpsc&) = delete;

  void Push(T value) {
    Node* n = AllocNode();
    Construct(&n->value, std::move(value));
    n->next.store(nullptr, std::memory_order_relaxed);
    head_->next.store(n, std::memory_order_release);
    head_ = n;
  }

  std::optional<T> Pop() {
    Node* n = tail_.load(std::memory_order_relaxed);
    Node* next = n->next.load(std::memory_order_acquire);
    if (next == nullptr) return std::nullopt;
    T result = std::move(next->value);
    Destruct(&next->value);
    tail_.store(next, std::memory_order_release);
    return result;
  }

  template <typename F>
  void ForEach(F f) {
    Node* tail = tail_.load(std::memory_order_relaxed);
    Node* n = tail->next.load(std::memory_order_acquire);
    while (n != nullptr) {
      f(n->value);
      n = n->next.load(std::memory_order_acquire);
    }
  }

 private:
  struct Node {
    Node() {}
    ~Node() {}
    explicit Node(std::nullptr_t) : next{nullptr} {}
    std::atomic<Node*> next;
    union {
      T value;
    };
  };

  Node* AllocNode() {
    if (first_ != tail_copy_) {
      Node* n = first_;
      first_ = first_->next.load(std::memory_order_relaxed);
      return n;
    }
    tail_copy_ = tail_.load(std::memory_order_acquire);
    if (first_ != tail_copy_) {
      Node* n = first_;
      first_ = first_->next.load(std::memory_order_relaxed);
      return n;
    }
    return arena_->New<Node>();
  }

  Arena* const arena_;
  Node first_node_{nullptr};

  std::atomic<Node*> tail_{&first_node_};

  alignas(kOptimizeAlignment ? GPR_CACHELINE_SIZE
                             : alignof(Node*)) Node* head_{&first_node_};

  Node* first_{&first_node_};

  Node* tail_copy_{&first_node_};
};

template <>
struct ContextType<Arena> {};

namespace arena_detail {
inline void UnrefDestroy::operator()(const Arena* arena) const {
  arena->Destroy();
}
}

namespace promise_detail {

template <typename T>
class Context<T, absl::void_t<decltype(ArenaContextType<T>::Destroy)>> {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static T* get() {
    return GetContext<Arena>()->GetContext<T>();
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static void set(T* value) {
    GetContext<Arena>()->SetContext(value);
  }
};

}

}

#endif
