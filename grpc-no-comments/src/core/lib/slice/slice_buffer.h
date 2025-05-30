// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SLICE_SLICE_BUFFER_H
#define GRPC_SRC_CORE_LIB_SLICE_SLICE_BUFFER_H

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include <memory>
#include <string>

#include "src/core/lib/slice/slice.h"

void grpc_slice_buffer_copy_first_into_buffer(const grpc_slice_buffer* src,
                                              size_t n, void* dst);

void grpc_slice_buffer_move_first_no_inline(grpc_slice_buffer* src, size_t n,
                                            grpc_slice_buffer* dst);

void grpc_slice_buffer_trim_end_no_inline(grpc_slice_buffer* sb, size_t n,
                                          grpc_slice_buffer* garbage);

namespace grpc_core {

class SliceBuffer {
 public:
  explicit SliceBuffer() { grpc_slice_buffer_init(&slice_buffer_); }
  explicit SliceBuffer(Slice slice) : SliceBuffer() {
    Append(std::move(slice));
  }
  SliceBuffer(const SliceBuffer& other) = delete;
  SliceBuffer(SliceBuffer&& other) noexcept {
    grpc_slice_buffer_init(&slice_buffer_);
    grpc_slice_buffer_swap(&slice_buffer_, &other.slice_buffer_);
  }

  ~SliceBuffer() { grpc_slice_buffer_destroy(&slice_buffer_); }

  SliceBuffer& operator=(const SliceBuffer&) = delete;
  SliceBuffer& operator=(SliceBuffer&& other) noexcept {
    grpc_slice_buffer_swap(&slice_buffer_, &other.slice_buffer_);
    return *this;
  }

  void Append(Slice slice);

  void Append(const SliceBuffer& other);
  void TakeAndAppend(SliceBuffer& other) {
    grpc_slice_buffer_move_into(&other.slice_buffer_, &slice_buffer_);
  }

  size_t AppendIndexed(Slice slice);

  size_t Count() const { return slice_buffer_.count; }

  void CopyToBuffer(uint8_t* dst) {
    grpc_slice_buffer_copy_first_into_buffer(&slice_buffer_,
                                             slice_buffer_.length, dst);
  }

  void RemoveLastNBytes(size_t n) {
    grpc_slice_buffer_trim_end(&slice_buffer_, n, nullptr);
  }

  void RemoveLastNBytesNoInline(size_t n) {
    grpc_slice_buffer_trim_end_no_inline(&slice_buffer_, n, nullptr);
  }

  void MoveFirstNBytesIntoBuffer(size_t n, void* dst) {
    grpc_slice_buffer_move_first_into_buffer(&slice_buffer_, n, dst);
  }

  void CopyFirstNBytesIntoBuffer(size_t n, void* dst) {
    grpc_slice_buffer_copy_first_into_buffer(&slice_buffer_, n, dst);
  }

  void MoveLastNBytesIntoSliceBuffer(size_t n, SliceBuffer& other) {
    grpc_slice_buffer_trim_end(&slice_buffer_, n, &other.slice_buffer_);
  }

  void MoveFirstNBytesIntoSliceBuffer(size_t n, SliceBuffer& other) {
    grpc_slice_buffer_move_first(&slice_buffer_, n, &other.slice_buffer_);
  }

  GRPC_REINITIALIZES void Clear() {
    grpc_slice_buffer_reset_and_unref(&slice_buffer_);
  }

  Slice TakeFirst();

  void Prepend(Slice slice);

  Slice RefSlice(size_t index) const;

  const Slice& operator[](size_t index) const {
    return grpc_event_engine::experimental::internal::SliceCast<Slice>(
        slice_buffer_.slices[index]);
  }

  size_t Length() const { return slice_buffer_.length; }

  void Swap(SliceBuffer* other) {
    grpc_slice_buffer_swap(c_slice_buffer(), other->c_slice_buffer());
  }

  std::string JoinIntoString() const;

  Slice JoinIntoSlice() const;

  SliceBuffer Copy() const {
    SliceBuffer copy;
    for (size_t i = 0; i < Count(); i++) {
      copy.Append(RefSlice(i));
    }
    return copy;
  }

  uint8_t* AddTiny(size_t n) {
    return grpc_slice_buffer_tiny_add(&slice_buffer_, n);
  }

  grpc_slice_buffer* c_slice_buffer() { return &slice_buffer_; }

  const grpc_slice_buffer* c_slice_buffer() const { return &slice_buffer_; }

  const grpc_slice& c_slice_at(size_t index) {
    return slice_buffer_.slices[index];
  }

 private:

  grpc_slice_buffer slice_buffer_;

#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);
#endif
};

}

#endif
