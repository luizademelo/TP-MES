
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SLICE_H
#define GRPCPP_SUPPORT_SLICE_H

#include <grpc/slice.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/string_ref.h>

namespace grpc {

class Slice final {
 public:

  Slice() : slice_(grpc_empty_slice()) {}

  ~Slice() { grpc_slice_unref(slice_); }

  enum AddRef { ADD_REF };

  Slice(grpc_slice slice, AddRef) : slice_(grpc_slice_ref(slice)) {}

  enum StealRef { STEAL_REF };

  Slice(grpc_slice slice, StealRef) : slice_(slice) {}

  explicit Slice(size_t len) : slice_(grpc_slice_malloc(len)) {}

  Slice(const void* buf, size_t len)
      : slice_(grpc_slice_from_copied_buffer(reinterpret_cast<const char*>(buf),
                                             len)) {}

  Slice(const std::string& str)
      : slice_(grpc_slice_from_copied_buffer(str.c_str(), str.length())) {}

  enum StaticSlice { STATIC_SLICE };

  Slice(const void* buf, size_t len, StaticSlice)
      : slice_(grpc_slice_from_static_buffer(reinterpret_cast<const char*>(buf),
                                             len)) {}

  Slice(const Slice& other) : slice_(grpc_slice_ref(other.slice_)) {}

  Slice(Slice&& other) noexcept : slice_(other.slice_) {
    other.slice_ = grpc_empty_slice();
  }

  Slice& operator=(Slice other) {
    std::swap(slice_, other.slice_);
    return *this;
  }

  Slice(void* buf, size_t len, void (*destroy)(void*), void* user_data)
      : slice_(grpc_slice_new_with_user_data(buf, len, destroy, user_data)) {}

  Slice(void* buf, size_t len, void (*destroy)(void*))
      : Slice(buf, len, destroy, buf) {}

  Slice(void* buf, size_t len, void (*destroy)(void*, size_t))
      : slice_(grpc_slice_new_with_len(buf, len, destroy)) {}

  size_t size() const { return GRPC_SLICE_LENGTH(slice_); }

  const uint8_t* begin() const { return GRPC_SLICE_START_PTR(slice_); }

  const uint8_t* end() const { return GRPC_SLICE_END_PTR(slice_); }

  Slice sub(size_t begin, size_t end) const {
    return Slice(grpc_slice_sub(slice_, begin, end), STEAL_REF);
  }

  grpc_slice c_slice() const { return grpc_slice_ref(slice_); }

 private:
  friend class ByteBuffer;

  grpc_slice slice_;
};

inline grpc::string_ref StringRefFromSlice(const grpc_slice* slice) {
  return grpc::string_ref(
      reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(*slice)),
      GRPC_SLICE_LENGTH(*slice));
}

inline std::string StringFromCopiedSlice(grpc_slice slice) {
  return std::string(reinterpret_cast<char*>(GRPC_SLICE_START_PTR(slice)),
                     GRPC_SLICE_LENGTH(slice));
}

inline grpc_slice SliceReferencingString(const std::string& str) {
  return grpc_slice_from_static_buffer(str.data(), str.length());
}

inline grpc_slice SliceFromCopiedString(const std::string& str) {
  return grpc_slice_from_copied_buffer(str.data(), str.length());
}

}

#endif
