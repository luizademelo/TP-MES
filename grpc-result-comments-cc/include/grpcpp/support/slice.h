Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SLICE_H
#define GRPCPP_SUPPORT_SLICE_H

#include <grpc/slice.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

namespace grpc {

// A wrapper class for grpc_slice that provides RAII semantics and convenience methods
// for working with gRPC slice objects. Slices represent reference-counted buffers.
class Slice final {
 public:
  // Default constructor creates an empty slice
  Slice() : slice_(grpc_empty_slice()) {}

  // Destructor decreases reference count (or frees memory if refcount reaches 0)
  ~Slice() { grpc_slice_unref(slice_); }

  // Enum to indicate reference count should be incremented when constructing from raw slice
  enum AddRef { ADD_REF };

  // Construct from raw grpc_slice with reference count increment
  Slice(grpc_slice slice, AddRef) : slice_(grpc_slice_ref(slice)) {}

  // Enum to indicate slice should take ownership without incrementing reference count
  enum StealRef { STEAL_REF };

  // Construct from raw grpc_slice taking ownership (no reference count increment)
  Slice(grpc_slice slice, StealRef) : slice_(slice) {}

  // Construct an uninitialized slice of given length
  explicit Slice(size_t len) : slice_(grpc_slice_malloc(len)) {}

  // Construct from a buffer by copying the data
  Slice(const void* buf, size_t len)
      : slice_(grpc_slice_from_copied_buffer(reinterpret_cast<const char*>(buf),
                                             len)) {}

  // Construct from std::string by copying the data
  Slice(const std::string& str)
      : slice_(grpc_slice_from_copied_buffer(str.c_str(), str.length())) {}

  // Enum to indicate the slice should reference static (non-owned) memory
  enum StaticSlice { STATIC_SLICE };

  // Construct slice referencing static buffer (no copying or ownership taken)
  Slice(const void* buf, size_t len, StaticSlice)
      : slice_(grpc_slice_from_static_buffer(reinterpret_cast<const char*>(buf),
                                             len)) {}

  // Copy constructor increments reference count
  Slice(const Slice& other) : slice_(grpc_slice_ref(other.slice_)) {}

  // Move constructor transfers ownership without reference count changes
  Slice(Slice&& other) noexcept : slice_(other.slice_) {
    other.slice_ = grpc_empty_slice();
  }

  // Assignment operator using copy-and-swap idiom
  Slice& operator=(Slice other) {
    std::swap(slice_, other.slice_);
    return *this;
  }

  // Construct slice with custom destructor for user-managed buffer
  Slice(void* buf, size_t len, void (*destroy)(void*), void* user_data)
      : slice_(grpc_slice_new_with_user_data(buf, len, destroy, user_data)) {}

  // Construct slice with custom destructor (simplified version)
  Slice(void* buf, size_t len, void (*destroy)(void*))
      : Slice(buf, len, destroy, buf) {}

  // Construct slice with custom destructor that also receives length
  Slice(void* buf, size_t len, void (*destroy)(void*, size_t))
      : slice_(grpc_slice_new_with_len(buf, len, destroy)) {}

  // Returns the length of the slice data
  size_t size() const { return GRPC_SLICE_LENGTH(slice_); }

  // Returns pointer to beginning of slice data
  const uint8_t* begin() const { return GRPC_SLICE_START_PTR(slice_); }

  // Returns pointer to end of slice data
  const uint8_t* end() const { return GRPC_SLICE_END_PTR(slice_); }

  // Returns a sub-slice of the current slice
  Slice sub(size_t begin, size_t end) const {
    return Slice(grpc_slice_sub(slice_, begin, end), STEAL_REF);
  }

  // Returns a raw grpc_slice with incremented reference count
  grpc_slice c_slice() const { return grpc_slice_ref(slice_); }

 private:
  friend class ByteBuffer;  // Allow ByteBuffer to access private slice_ member

  grpc_slice slice_;  // The underlying grpc_slice object
};

// Converts a grpc_slice to a string_ref (non-owning string view)
inline grpc::string_ref StringRefFromSlice(const grpc_slice* slice) {
  return grpc::string_ref(
      reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(*slice)),
      GRPC_SLICE_LENGTH(*slice));
}

// Converts a grpc_slice to a new std::string (copies the data)
inline std::string StringFromCopiedSlice(grpc_slice slice) {
  return std::string(reinterpret_cast<char*>(GRPC_SLICE_START_PTR(slice)),
                     GRPC_SLICE_LENGTH(slice));
}

// Creates a slice that references a string's data without copying (static buffer)
inline grpc_slice SliceReferencingString(const std::string& str) {
  return grpc_slice_from_static_buffer(str.data(), str.length());
}

// Creates a slice by copying a string's data
inline grpc_slice SliceFromCopiedString(const std::string& str) {
  return grpc_slice_from_copied_buffer(str.data(), str.length());
}

}  // namespace grpc

#endif  // GRPCPP_SUPPORT_SLICE_H
```