Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/lib/slice/slice.h"

#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <new>

#include "absl/log/check.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_refcount.h"
#include "src/core/util/memory.h"

// Converts a grpc_slice to a C-style null-terminated string.
// The returned string must be freed using gpr_free().
char* grpc_slice_to_c_string(grpc_slice slice) {
  char* out = static_cast<char*>(gpr_malloc(GRPC_SLICE_LENGTH(slice) + 1));
  memcpy(out, GRPC_SLICE_START_PTR(slice), GRPC_SLICE_LENGTH(slice));
  out[GRPC_SLICE_LENGTH(slice)] = 0;
  return out;
}

// Returns an empty slice (with no reference count).
grpc_slice grpc_empty_slice(void) {
  return grpc_core::slice_detail::EmptySlice();
}

// Creates a new slice that is a copy of the input slice.
// The new slice has its own allocated memory.
grpc_slice grpc_slice_copy(grpc_slice s) {
  grpc_slice out = GRPC_SLICE_MALLOC(GRPC_SLICE_LENGTH(s));
  memcpy(GRPC_SLICE_START_PTR(out), GRPC_SLICE_START_PTR(s),
         GRPC_SLICE_LENGTH(s));
  return out;
}

namespace grpc_core {

// Reference count implementation for slices that need custom destruction.
// Calls user-provided destroy function when reference count reaches zero.
class NewSliceRefcount : public grpc_slice_refcount {
 public:
  NewSliceRefcount(void (*destroy)(void*), void* user_data)
      : grpc_slice_refcount(Destroy),
        user_destroy_(destroy),
        user_data_(user_data) {}
  ~NewSliceRefcount() { user_destroy_(user_data_); }

 private:
  static void Destroy(grpc_slice_refcount* arg) {
    delete static_cast<NewSliceRefcount*>(arg);
  }

  void (*user_destroy_)(void*);
  void* user_data_;
};

}  // namespace grpc_core

// Returns the memory usage of a slice.
// For non-refcounted slices, returns 0.
// For refcounted slices, returns the length of the slice.
size_t grpc_slice_memory_usage(grpc_slice s) {
  if (s.refcount == nullptr ||
      s.refcount == grpc_slice_refcount::NoopRefcount()) {
    return 0;
  } else {
    return s.data.refcounted.length;
  }
}

// Creates a slice from a static buffer (does not copy or take ownership).
grpc_slice grpc_slice_from_static_buffer(const void* s, size_t len) {
  return grpc_core::StaticSlice::FromStaticBuffer(s, len).TakeCSlice();
}

// Creates a slice from a static string (does not copy or take ownership).
grpc_slice grpc_slice_from_static_string(const char* s) {
  return grpc_core::StaticSlice::FromStaticString(s).TakeCSlice();
}

// Creates a new slice with user data and custom destroy function.
// When the slice is destroyed, calls destroy(user_data).
grpc_slice grpc_slice_new_with_user_data(void* p, size_t len,
                                         void (*destroy)(void*),
                                         void* user_data) {
  grpc_slice slice;
  slice.refcount = new grpc_core::NewSliceRefcount(destroy, user_data);
  slice.data.refcounted.bytes = static_cast<uint8_t*>(p);
  slice.data.refcounted.length = len;
  return slice;
}

// Creates a new slice with custom destroy function.
// When the slice is destroyed, calls destroy(p).
grpc_slice grpc_slice_new(void* p, size_t len, void (*destroy)(void*)) {
  return grpc_slice_new_with_user_data(p, len, destroy, p);
}

namespace grpc_core {

// Reference count implementation for slices that need custom destruction
// with length parameter.
class NewWithLenSliceRefcount : public grpc_slice_refcount {
 public:
  NewWithLenSliceRefcount(void (*destroy)(void*, size_t), void* user_data,
                          size_t user_length)
      : grpc_slice_refcount(Destroy),
        user_data_(user_data),
        user_length_(user_length),
        user_destroy_(destroy) {}
  ~NewWithLenSliceRefcount() { user_destroy_(user_data_, user_length_); }

 private:
  static void Destroy(grpc_slice_refcount* arg) {
    delete static_cast<NewWithLenSliceRefcount*>(arg);
  }

  void* user_data_;
  size_t user_length_;
  void (*user_destroy_)(void*, size_t);
};

// Reference count implementation for slices that take ownership of a moved string.
class MovedStringSliceRefCount : public grpc_slice_refcount {
 public:
  explicit MovedStringSliceRefCount(UniquePtr<char>&& str)
      : grpc_slice_refcount(Destroy), str_(std::move(str)) {}

 private:
  static void Destroy(grpc_slice_refcount* arg) {
    delete static_cast<MovedStringSliceRefCount*>(arg);
  }

  UniquePtr<char> str_;
};

// Reference count implementation for slices that take ownership of a moved C++ string.
class MovedCppStringSliceRefCount : public grpc_slice_refcount {
 public:
  explicit MovedCppStringSliceRefCount(std::string&& str)
      : grpc_slice_refcount(Destroy), str_(std::move(str)) {}

  uint8_t* data() {
    return reinterpret_cast<uint8_t*>(const_cast<char*>(str_.data()));
  }

  size_t size() const { return str_.size(); }

 private:
  static void Destroy(grpc_slice_refcount* arg) {
    delete static_cast<MovedCppStringSliceRefCount*>(arg);
  }

  std::string str_;
};

}  // namespace grpc_core

// Creates a new slice with custom destroy function that takes length.
grpc_slice grpc_slice_new_with_len(void* p, size_t len,
                                   void (*destroy)(void*, size_t)) {
  grpc_slice slice;
  slice.refcount = new grpc_core::NewWithLenSliceRefcount(destroy, p, len);
  slice.data.refcounted.bytes = static_cast<uint8_t*>(p);
  slice.data.refcounted.length = len;
  return slice;
}

// Creates a new slice by copying from a buffer.
grpc_slice grpc_slice_from_copied_buffer(const char* source, size_t len) {
  if (len == 0) return grpc_empty_slice();
  grpc_slice out = grpc_slice_malloc(len);
  memcpy(GRPC_SLICE_START_PTR(out), source, len);
  return out;
}

// Creates a new slice by copying from a null-terminated string.
grpc_slice grpc_slice_from_copied_string(const char* source) {
  return grpc_slice_from_copied_buffer(source, strlen(source));
}

// Creates a slice by taking ownership of a buffer (moved).
grpc_slice grpc_slice_from_moved_buffer(grpc_core::UniquePtr<char> p,
                                        size_t len) {
  uint8_t* ptr = reinterpret_cast<uint8_t*>(p.get());
  grpc_slice slice;
  if (len <= sizeof(slice.data.inlined.bytes)) {
    // Small slice - store inline
    slice.refcount = nullptr;
    slice.data.inlined.length = len;
    memcpy(GRPC_SLICE_START_PTR(slice), ptr, len);
  } else {
    // Large slice - use refcount
    slice.refcount = new grpc_core::MovedStringSliceRefCount(std::move(p));
    slice.data.refcounted.bytes = ptr;
    slice.data.refcounted.length = len;
  }
  return slice;
}

// Creates a slice by taking ownership of a null-terminated string (moved).
grpc_slice grpc_slice_from_moved_string(grpc_core::UniquePtr<char> p) {
  const size_t len = strlen(p.get());
  return grpc_slice_from_moved_buffer(std::move(p), len);
}

// Creates a slice by taking ownership of a C++ string (moved).
grpc_slice grpc_slice_from_cpp_string(std::string str) {
  grpc_slice slice;
  if (str.size() <= sizeof(slice.data.inlined.bytes)) {
    // Small string - store inline
    slice.refcount = nullptr;
    slice.data.inlined.length = str.size();
    memcpy(GRPC_SLICE_START_PTR(slice), str.data(), str.size());
  } else {
    // Large string - use refcount
    auto* refcount = new grpc_core::MovedCppStringSliceRefCount(std::move(str));
    slice.data.refcounted.bytes = refcount->data();
    slice.data.refcounted.length = refcount->size();
    slice.refcount = refcount;
  }
  return slice;
}

// Allocates a large slice (not inlined).
grpc_slice grpc_slice_malloc_large(size_t length) {
  grpc_slice slice;
  uint8_t* memory = new uint8_t[sizeof(grpc_slice_refcount) + length];
  slice.refcount = new (memory) grpc_slice_refcount(
      [](grpc_slice_refcount* p) { delete[] reinterpret_cast<uint8_t*>(p); });
  slice.data.refcounted.bytes = memory + sizeof(grpc_slice_refcount);
  slice.data.refcounted.length = length;
  return slice;
}

// Allocates a slice of given length.
// Small slices are stored inline, large slices are heap-allocated.
grpc_slice grpc_slice_malloc(size_t length) {
  if (length <= GRPC_SLICE_INLINED_SIZE) {
    grpc_slice slice;
    slice.refcount = nullptr;
    slice.data.inlined.length = length;
    return slice;
  } else {
    return grpc_slice_malloc_large(length);
  }
}

// Creates a sub-slice without incrementing the reference count.
static grpc_slice sub_no_ref(const grpc_slice& source, size_t begin,
                             size_t end) {
  grpc_slice subset;

  CHECK(end >= begin);

  if (source.refcount != nullptr) {
    // Refcounted slice
    CHECK(source.data.refcounted.length >= end);

    subset.refcount = source.refcount;
    subset.data.refcounted.bytes = source.data.refcounted.bytes + begin;
    subset.data.refcounted.length = end - begin;
  } else {
    // Inlined slice
    CHECK(source.data.inlined.length >= end);
    subset.refcount = nullptr;
    subset.data.inlined.length = static_cast<uint8_t>(end - begin);
    memcpy(subset.data.inlined.bytes, source.data.inlined.bytes + begin,
           end - begin);
  }
  return subset;
}

// Creates a sub-slice without incrementing the reference count.
grpc_slice grpc_slice_sub_no_ref(grpc_slice source, size_t begin, size_t end) {
  return sub_no_ref(source, begin, end);
}

// Creates a sub-slice, possibly incrementing the reference count.
grpc_slice grpc_slice_sub(grpc_slice source, size_t begin, size_t end) {
  grpc_slice subset;

  if (end - begin <= sizeof(subset.data.inlined.bytes)) {
    // Small sub-slice - copy to inline storage
    subset.refcount = nullptr;
    subset.data.inlined.length = static_cast<uint8_t>(end - begin);
    memcpy(subset.data.inlined.bytes, GRPC_SLICE_START_PTR(source) + begin,
           end - begin);
  } else {
    // Large sub-slice - use refcounting
    subset = grpc_slice_sub_no_ref(source, begin, end);

    if (subset.refcount != grpc_slice_refcount::NoopRefcount()) {
      subset.refcount->Ref({});
    }
  }
  return subset;
}

// Splits a slice into head and tail at the specified position.
// The tail may be inlined or refcounted depending on parameters.
template <bool allow_inline>
grpc_slice grpc_slice_split_tail_maybe_ref_impl(grpc_slice* source,
                                                size_t split,
                                                grpc_slice_ref_whom ref_whom) {
  grpc_slice tail;

  if (source->refcount == nullptr) {
    // Inlined source slice
    CHECK(source->data.inlined.length >= split);
    tail.refcount = nullptr;
    tail.data.inlined.length =
        static_cast<uint8_t>(source->data.inlined.length - split);
    memcpy(tail.data.inlined.bytes, source->data.inlined.bytes + split,
           tail.data.inlined.length);
    source->data.inlined.length = static_cast<uint8_t>(split);
  } else if (source->refcount == grpc_slice_refcount::NoopRefcount()) {
    // No-op refcount slice
    tail.refcount = grpc_slice_refcount::NoopRefcount();
    tail.data.refcounted.bytes = source->data.refcounted.bytes + split;
    tail.data.refcounted.length = source->data.refcounted.length - split;
    source->data.refcounted.length = split;
  } else {
    // Regular refcounted slice
    size_t tail_length = source->data.refcounted.length - split;
    CHECK(source->data.refcounted.length >= split);
    if (allow_inline && tail_length < sizeof(tail.data.inlined.bytes) &&
        ref_whom != GRPC_SLICE_REF_TAIL) {
      // Small tail that can be inlined
      tail.refcount = nullptr;
      tail.data.inlined.length = static_cast<uint8_t>(tail_length);
      memcpy(tail.data.inlined.bytes, source->data.refcounted.bytes + split,
             tail_length);
    } else {
      // Large tail that needs refcounting
      switch (ref_whom) {
        case GRPC_SLICE_REF_TAIL:
          tail.refcount = source->refcount;
          source->refcount = grpc_slice_refcount::NoopRefcount();
          break;
        case GRPC_SLICE_REF_HEAD:
          tail.refcount = grpc_slice_refcount::NoopRefcount();
          break;
        case GRPC_SLICE_REF_BOTH:
          tail.refcount = source->refcount;
          if (tail.refcount != grpc_slice_refcount::NoopRefcount()) {
            tail.refcount->Ref({});
          }
          break;
      }
      tail.data.refcounted.bytes = source->data.refcounted.bytes + split;
      tail.data.refcounted.length = tail_length;
    }
    source->data.refcounted.length = split;
  }

  return tail;
}

// Splits a slice into head and tail at the specified position.
// Allows inlining of small tails.
grpc_slice grpc_slice_split_tail_maybe_ref(grpc_slice* source, size_t split,
                                           grpc_slice_ref_whom ref_whom) {
  return grpc_slice_split_tail_maybe_ref_impl<true>(source, split, ref_whom);
}

// Splits a slice into head and tail at the specified position.
// Never inlines the tail.
grpc_slice grpc_slice_split_tail_maybe_ref_no_inline(
    grpc_slice* source, size_t split, grpc_slice_ref_whom ref_whom) {
  return grpc_slice_split_tail_maybe_ref_impl<false>(source, split, ref_whom);
}

// Splits a slice into head and tail at the specified position.
// Maintains references to both parts.
grpc_slice grpc_slice_split_tail(grpc_slice* source, size_t split) {
  return grpc_slice_split_tail_maybe_ref(source, split, GRPC_SLICE_REF_BOTH);
}

// Splits a slice into head and tail at the specified position.
// Maintains references to both parts and never inlines the tail.
grpc_slice grpc_slice_split_tail_no_inline(grpc_slice* source, size_t split) {
  return grpc_slice_split_tail_maybe_ref_no_inline(source, split,
                                                   GRPC_SLICE_REF_BOTH);
}

// Splits a slice into head and tail at the specified position.
template <bool allow_inline>
grpc_slice grpc_slice_split_head_impl(grpc_slice* source, size_t split) {
  grpc_slice head;

  if (source->refcount == nullptr) {
    // Inlined source slice
    CHECK(source->data.inlined.length >= split);

    head.refcount = nullptr;
    head.data.inlined.length = static_cast<uint8_t>(split);
    memcpy(head.data.inlined.bytes, source->data.inlined.bytes, split);
    source->data.inlined.length =
        static_cast<uint8_t>(source->data.inlined.length - split);
    memmove(source->data.inlined.bytes, source->data.inlined.bytes + split,
            source->data.inlined.length);
  } else if (allow_inline && split < sizeof(head.data.inlined.bytes)) {
    // Small head that can be inlined
    CHECK(source->data.refcounted.length >= split);

    head.refcount = nullptr;
    head.data.inlined.length = static_cast<uint8_t>(split);
    memcpy(head.data.inlined.bytes, source->data.refcounted.bytes, split);
    source->data.refcounted.bytes += split;
    source->data.refcounted.length -= split;
  } else {
    // Large head that needs refcounting
    CHECK(source->data.refcounted.length >= split);

    head.refcount = source->refcount;
    if (head.refcount != grpc_slice_refcount::NoopRefcount())