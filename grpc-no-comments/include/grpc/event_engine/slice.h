// Copyright 2022 gRPC authors.

#ifndef GRPC_EVENT_ENGINE_SLICE_H
#define GRPC_EVENT_ENGINE_SLICE_H

#include <grpc/event_engine/internal/slice_cast.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <cstdint>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"

namespace grpc_event_engine {
namespace experimental {

class Slice;
class MutableSlice;

namespace slice_detail {

static constexpr grpc_slice EmptySlice() { return {nullptr, {}}; }

class BaseSlice {
 public:
  BaseSlice(const BaseSlice&) = delete;
  BaseSlice& operator=(const BaseSlice&) = delete;
  BaseSlice(BaseSlice&& other) = delete;
  BaseSlice& operator=(BaseSlice&& other) = delete;

  const uint8_t* begin() const { return GRPC_SLICE_START_PTR(c_slice()); }
  const uint8_t* end() const { return GRPC_SLICE_END_PTR(c_slice()); }
  const uint8_t* cbegin() const { return GRPC_SLICE_START_PTR(c_slice()); }
  const uint8_t* cend() const { return GRPC_SLICE_END_PTR(c_slice()); }

  const grpc_slice& c_slice() const { return slice_; }

  grpc_slice TakeCSlice() {
    grpc_slice out = slice_;
    slice_ = EmptySlice();
    return out;
  }

  absl::string_view as_string_view() const {
    return absl::string_view(reinterpret_cast<const char*>(data()), size());
  }

  uint8_t operator[](size_t i) const {
    return GRPC_SLICE_START_PTR(c_slice())[i];
  }

  const uint8_t* data() const { return GRPC_SLICE_START_PTR(c_slice()); }

  size_t size() const { return GRPC_SLICE_LENGTH(c_slice()); }
  size_t length() const { return size(); }
  bool empty() const { return size() == 0; }

  bool is_equivalent(const BaseSlice& other) const {
    return grpc_slice_is_equivalent(slice_, other.slice_);
  }

  uint32_t Hash() const;

 protected:
  BaseSlice() : slice_(EmptySlice()) {}
  explicit BaseSlice(const grpc_slice& slice) : slice_(slice) {}
  ~BaseSlice() = default;

  void Swap(BaseSlice* other) { std::swap(slice_, other->slice_); }
  void SetCSlice(const grpc_slice& slice) { slice_ = slice; }

  uint8_t* mutable_data() { return GRPC_SLICE_START_PTR(slice_); }

  grpc_slice* c_slice_ptr() { return &slice_; }

 private:
  grpc_slice slice_;
};

inline bool operator==(const BaseSlice& a, const BaseSlice& b) {
  return grpc_slice_eq(a.c_slice(), b.c_slice()) != 0;
}

inline bool operator!=(const BaseSlice& a, const BaseSlice& b) {
  return grpc_slice_eq(a.c_slice(), b.c_slice()) == 0;
}

inline bool operator==(const BaseSlice& a, absl::string_view b) {
  return a.as_string_view() == b;
}

inline bool operator!=(const BaseSlice& a, absl::string_view b) {
  return a.as_string_view() != b;
}

inline bool operator==(absl::string_view a, const BaseSlice& b) {
  return a == b.as_string_view();
}

inline bool operator!=(absl::string_view a, const BaseSlice& b) {
  return a != b.as_string_view();
}

inline bool operator==(const BaseSlice& a, const grpc_slice& b) {
  return grpc_slice_eq(a.c_slice(), b) != 0;
}

inline bool operator!=(const BaseSlice& a, const grpc_slice& b) {
  return grpc_slice_eq(a.c_slice(), b) == 0;
}

inline bool operator==(const grpc_slice& a, const BaseSlice& b) {
  return grpc_slice_eq(a, b.c_slice()) != 0;
}

inline bool operator!=(const grpc_slice& a, const BaseSlice& b) {
  return grpc_slice_eq(a, b.c_slice()) == 0;
}

template <typename Out>
struct CopyConstructors {
  static Out FromCopiedString(const char* s) {
    return FromCopiedBuffer(s, strlen(s));
  }
  static Out FromCopiedString(absl::string_view s) {
    return FromCopiedBuffer(s.data(), s.size());
  }
  static Out FromCopiedString(std::string s);

  static Out FromCopiedBuffer(const char* p, size_t len) {
    return Out(grpc_slice_from_copied_buffer(p, len));
  }

  static Out FromCopiedBuffer(const uint8_t* p, size_t len) {
    return Out(
        grpc_slice_from_copied_buffer(reinterpret_cast<const char*>(p), len));
  }

  template <typename Buffer>
  static Out FromCopiedBuffer(const Buffer& buffer) {
    return FromCopiedBuffer(reinterpret_cast<const char*>(buffer.data()),
                            buffer.size());
  }
};

}

class GPR_MSVC_EMPTY_BASE_CLASS_WORKAROUND MutableSlice
    : public slice_detail::BaseSlice,
      public slice_detail::CopyConstructors<MutableSlice> {
 public:
  MutableSlice() = default;
  explicit MutableSlice(const grpc_slice& slice);
  ~MutableSlice();

  MutableSlice(const MutableSlice&) = delete;
  MutableSlice& operator=(const MutableSlice&) = delete;
  MutableSlice(MutableSlice&& other) noexcept
      : slice_detail::BaseSlice(other.TakeCSlice()) {}
  MutableSlice& operator=(MutableSlice&& other) noexcept {
    Swap(&other);
    return *this;
  }

  static MutableSlice CreateUninitialized(size_t length) {
    return MutableSlice(grpc_slice_malloc(length));
  }

  MutableSlice TakeSubSlice(size_t pos, size_t n) {
    return MutableSlice(grpc_slice_sub_no_ref(TakeCSlice(), pos, pos + n));
  }

  uint8_t* begin() { return mutable_data(); }
  uint8_t* end() { return mutable_data() + size(); }
  uint8_t* data() { return mutable_data(); }

  uint8_t& operator[](size_t i) { return mutable_data()[i]; }
};

class GPR_MSVC_EMPTY_BASE_CLASS_WORKAROUND Slice
    : public slice_detail::BaseSlice,
      public slice_detail::CopyConstructors<Slice> {
 public:
  Slice() = default;
  ~Slice();
  explicit Slice(const grpc_slice& slice) : slice_detail::BaseSlice(slice) {}
  explicit Slice(slice_detail::BaseSlice&& other)
      : slice_detail::BaseSlice(other.TakeCSlice()) {}

  Slice(const Slice&) = delete;
  Slice& operator=(const Slice&) = delete;
  Slice(Slice&& other) noexcept : slice_detail::BaseSlice(other.TakeCSlice()) {}
  Slice& operator=(Slice&& other) noexcept {
    Swap(&other);
    return *this;
  }

  Slice TakeOwned();

  Slice AsOwned() const;

  MutableSlice TakeMutable();

  Slice TakeSubSlice(size_t pos, size_t n) {
    return Slice(grpc_slice_sub_no_ref(TakeCSlice(), pos, pos + n));
  }

  Slice RefSubSlice(size_t pos, size_t n) const {
    return Slice(grpc_slice_sub(c_slice(), pos, pos + n));
  }

  Slice Split(size_t split) {
    return Slice(grpc_slice_split_tail(c_slice_ptr(), split));
  }

  Slice Ref() const;

  Slice Copy() const { return Slice(grpc_slice_copy(c_slice())); }

  static Slice FromRefcountAndBytes(grpc_slice_refcount* r,
                                    const uint8_t* begin, const uint8_t* end);
};

namespace internal {
template <>
struct SliceCastable<Slice, grpc_slice> {};
template <>
struct SliceCastable<grpc_slice, Slice> {};

template <>
struct SliceCastable<MutableSlice, grpc_slice> {};
template <>
struct SliceCastable<grpc_slice, MutableSlice> {};

template <>
struct SliceCastable<MutableSlice, Slice> {};
template <>
struct SliceCastable<Slice, MutableSlice> {};
}

}
}

#endif
