// Copyright 2022 gRPC authors.

#ifndef GRPC_EVENT_ENGINE_SLICE_BUFFER_H
#define GRPC_EVENT_ENGINE_SLICE_BUFFER_H

#include <grpc/event_engine/internal/slice_cast.h>
#include <grpc/event_engine/slice.h>
#include <grpc/impl/codegen/slice.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <cstdint>
#include <string>

#include "absl/strings/string_view.h"
#include "absl/utility/utility.h"

namespace grpc_event_engine {
namespace experimental {

class SliceBuffer {
 public:
  SliceBuffer() { grpc_slice_buffer_init(&slice_buffer_); }
  SliceBuffer(const SliceBuffer& other) = delete;
  SliceBuffer(SliceBuffer&& other) noexcept
      : slice_buffer_(other.slice_buffer_) {
    grpc_slice_buffer_init(&slice_buffer_);
    grpc_slice_buffer_swap(&slice_buffer_, &other.slice_buffer_);
  }

  ~SliceBuffer() { grpc_slice_buffer_destroy(&slice_buffer_); }

  SliceBuffer& operator=(const SliceBuffer&) = delete;
  SliceBuffer& operator=(SliceBuffer&& other) noexcept {
    grpc_slice_buffer_swap(&slice_buffer_, &other.slice_buffer_);
    return *this;
  }

  void Swap(SliceBuffer& other) {
    grpc_slice_buffer_swap(&slice_buffer_, &other.slice_buffer_);
  }

  void Append(Slice slice);

  size_t AppendIndexed(Slice slice);

  size_t Count() { return slice_buffer_.count; }

  void RemoveLastNBytes(size_t n) {
    grpc_slice_buffer_trim_end(&slice_buffer_, n, nullptr);
  }

  void MoveFirstNBytesIntoBuffer(size_t n, void* dst) {
    grpc_slice_buffer_move_first_into_buffer(&slice_buffer_, n, dst);
  }

  void MoveLastNBytesIntoSliceBuffer(size_t n, SliceBuffer& other) {
    grpc_slice_buffer_trim_end(&slice_buffer_, n, &other.slice_buffer_);
  }

  void MoveFirstNBytesIntoSliceBuffer(size_t n, SliceBuffer& other) {
    grpc_slice_buffer_move_first(&slice_buffer_, n, &other.slice_buffer_);
  }

  void Clear() { grpc_slice_buffer_reset_and_unref(&slice_buffer_); }

  Slice TakeFirst();

  void Prepend(Slice slice);

  Slice RefSlice(size_t index);

  const Slice& operator[](size_t index) const {
    return internal::SliceCast<Slice>(slice_buffer_.slices[index]);
  }

  Slice& MutableSliceAt(size_t index) const {
    return internal::SliceCast<Slice>(slice_buffer_.slices[index]);
  }

  size_t Length() const { return slice_buffer_.length; }

  grpc_slice_buffer* c_slice_buffer() { return &slice_buffer_; }

  static SliceBuffer TakeCSliceBuffer(grpc_slice_buffer& slice_buffer) {
    return SliceBuffer(&slice_buffer);
  }

 private:

  explicit SliceBuffer(grpc_slice_buffer* slice_buffer) {
    grpc_slice_buffer_init(&slice_buffer_);
    grpc_slice_buffer_swap(&slice_buffer_, slice_buffer);
  }

  grpc_slice_buffer slice_buffer_;
};

}
}

#endif
