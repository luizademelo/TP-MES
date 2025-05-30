// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_MEMORY_ALLOCATOR_H
#define GRPC_EVENT_ENGINE_MEMORY_ALLOCATOR_H

#include <grpc/event_engine/internal/memory_allocator_impl.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

namespace grpc_event_engine {
namespace experimental {

class MemoryAllocator {
 public:

  explicit MemoryAllocator(
      std::shared_ptr<internal::MemoryAllocatorImpl> allocator)
      : allocator_(std::move(allocator)) {}

  MemoryAllocator() : allocator_(nullptr) {}
  ~MemoryAllocator() {
    if (allocator_ != nullptr) allocator_->Shutdown();
  }

  MemoryAllocator(const MemoryAllocator&) = delete;
  MemoryAllocator& operator=(const MemoryAllocator&) = delete;

  MemoryAllocator(MemoryAllocator&&) = default;
  MemoryAllocator& operator=(MemoryAllocator&&) = default;

  void Reset() {
    auto a = std::move(allocator_);
    if (a != nullptr) a->Shutdown();
  }

  size_t Reserve(MemoryRequest request) { return allocator_->Reserve(request); }

  void Release(size_t n) { return allocator_->Release(n); }

  class Reservation {
   public:
    Reservation() = default;
    Reservation(const Reservation&) = delete;
    Reservation& operator=(const Reservation&) = delete;
    Reservation(Reservation&&) = default;
    Reservation& operator=(Reservation&&) = default;
    ~Reservation() {
      if (allocator_ != nullptr) allocator_->Release(size_);
    }

   private:
    friend class MemoryAllocator;
    Reservation(std::shared_ptr<internal::MemoryAllocatorImpl> allocator,
                size_t size)
        : allocator_(std::move(allocator)), size_(size) {}

    std::shared_ptr<internal::MemoryAllocatorImpl> allocator_;
    size_t size_ = 0;
  };

  Reservation MakeReservation(MemoryRequest request) {
    return Reservation(allocator_, Reserve(request));
  }

  template <typename T, typename... Args>
  typename std::enable_if<std::has_virtual_destructor<T>::value, T*>::type New(
      Args&&... args) {

    class Wrapper final : public T {
     public:
      explicit Wrapper(std::shared_ptr<internal::MemoryAllocatorImpl> allocator,
                       Args&&... args)
          : T(std::forward<Args>(args)...), allocator_(std::move(allocator)) {}
      ~Wrapper() override { allocator_->Release(sizeof(*this)); }

     private:
      const std::shared_ptr<internal::MemoryAllocatorImpl> allocator_;
    };
    Reserve(sizeof(Wrapper));
    return new Wrapper(allocator_, std::forward<Args>(args)...);
  }

  template <typename T, typename... Args>
  std::unique_ptr<T> MakeUnique(Args&&... args) {
    return std::unique_ptr<T>(New<T>(std::forward<Args>(args)...));
  }

  grpc_slice MakeSlice(MemoryRequest request) {
    return allocator_->MakeSlice(request);
  }

  template <typename T>
  class Container {
   public:
    using value_type = T;

    explicit Container(MemoryAllocator* underlying_allocator)
        : underlying_allocator_(underlying_allocator) {}
    template <typename U>
    explicit Container(const Container<U>& other)
        : underlying_allocator_(other.underlying_allocator()) {}

    MemoryAllocator* underlying_allocator() const {
      return underlying_allocator_;
    }

    T* allocate(size_t n) {
      underlying_allocator_->Reserve(n * sizeof(T));
      return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_t n) {
      ::operator delete(p);
      underlying_allocator_->Release(n * sizeof(T));
    }

   private:
    MemoryAllocator* underlying_allocator_;
  };

 protected:

  internal::MemoryAllocatorImpl* get_internal_impl_ptr() {
    return allocator_.get();
  }

  const internal::MemoryAllocatorImpl* get_internal_impl_ptr() const {
    return allocator_.get();
  }

 private:
  std::shared_ptr<internal::MemoryAllocatorImpl> allocator_;
};

template <typename T>
class Vector : public std::vector<T, MemoryAllocator::Container<T>> {
 public:
  explicit Vector(MemoryAllocator* allocator)
      : std::vector<T, MemoryAllocator::Container<T>>(
            MemoryAllocator::Container<T>(allocator)) {}
};

class MemoryAllocatorFactory {
 public:
  virtual ~MemoryAllocatorFactory() = default;

  virtual MemoryAllocator CreateMemoryAllocator(absl::string_view name) = 0;
};

}
}

#endif
