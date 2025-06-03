Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_SUPPORT_PROTO_BUFFER_WRITER_H
#define GRPCPP_SUPPORT_PROTO_BUFFER_WRITER_H

#include <grpc/byte_buffer.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/status.h>

#include <type_traits>

#include "absl/log/absl_check.h"
#include "absl/strings/cord.h"

namespace grpc {

namespace internal {
class ProtoBufferWriterPeer;
}

// Maximum buffer length for ProtoBufferWriter
const int kProtoBufferWriterMaxBufferLength = 1024 * 1024;

// Implementation of ZeroCopyOutputStream that writes to a gRPC ByteBuffer
// This class provides a way to write protocol buffer messages directly to gRPC byte buffers
class ProtoBufferWriter : public grpc::protobuf::io::ZeroCopyOutputStream {
 public:
  // Constructor
  // @param byte_buffer: The target ByteBuffer to write to
  // @param block_size: Preferred size for memory allocation chunks
  // @param total_size: Total expected size of the data to be written
  ProtoBufferWriter(ByteBuffer* byte_buffer, int block_size, int total_size)
      : block_size_(block_size),
        total_size_(total_size),
        byte_count_(0),
        have_backup_(false) {
    ABSL_CHECK(!byte_buffer->Valid());

    // Create a raw byte buffer with no initial slices
    grpc_byte_buffer* bp = grpc_raw_byte_buffer_create(nullptr, 0);
    byte_buffer->set_buffer(bp);
    slice_buffer_ = &bp->data.raw.slice_buffer;
  }

  // Destructor - cleans up any backup slice
  ~ProtoBufferWriter() override {
    if (have_backup_) {
      grpc_slice_unref(backup_slice_);
    }
  }

  // Obtains a buffer into which data can be written
  // @param data: Will be set to point to the buffer
  // @param size: Will be set to the buffer size
  // @return: Always returns true (implementation never fails)
  bool Next(void** data, int* size) override {
    ABSL_CHECK_LT(byte_count_, total_size_);

    // Calculate remaining bytes to write
    size_t remain = static_cast<size_t>(total_size_ - byte_count_);
    if (have_backup_) {
      // Use the backup slice if available
      slice_ = backup_slice_;
      have_backup_ = false;
      if (GRPC_SLICE_LENGTH(slice_) > remain) {
        GRPC_SLICE_SET_LENGTH(slice_, remain);
      }
    } else {
      // Allocate new slice of appropriate size
      size_t allocate_length =
          remain > static_cast<size_t>(block_size_) ? block_size_ : remain;
      slice_ = grpc_slice_malloc(allocate_length > GRPC_SLICE_INLINED_SIZE
                                     ? allocate_length
                                     : GRPC_SLICE_INLINED_SIZE + 1);
    }
    *data = GRPC_SLICE_START_PTR(slice_);

    // Update byte count and add slice to buffer
    ABSL_CHECK(GRPC_SLICE_LENGTH(slice_) <= static_cast<size_t>(INT_MAX));
    byte_count_ += * size = static_cast<int>(GRPC_SLICE_LENGTH(slice_));

    grpc_slice_buffer_add_indexed(slice_buffer_, slice_);
    return true;
  }

  // Backs up 'count' bytes, so the next call to Next() returns data again
  // that was backed up
  // @param count: Number of bytes to back up
  void BackUp(int count) override {
    if (count == 0) return;

    ABSL_CHECK_LE(count, static_cast<int>(GRPC_SLICE_LENGTH(slice_)));
    grpc_slice_buffer_pop(slice_buffer_);
    if (static_cast<size_t>(count) == GRPC_SLICE_LENGTH(slice_)) {
      // If backing up entire slice, keep it as is
      backup_slice_ = slice_;
    } else {
      // Otherwise split the slice and keep the backed up portion
      backup_slice_ =
          grpc_slice_split_tail(&slice_, GRPC_SLICE_LENGTH(slice_) - count);
      grpc_slice_buffer_add(slice_buffer_, slice_);
    }

    have_backup_ = backup_slice_.refcount != nullptr;
    byte_count_ -= count;
  }

  // Returns the total number of bytes written
  int64_t ByteCount() const override { return byte_count_; }

#ifdef GRPC_PROTOBUF_CORD_SUPPORT_ENABLED
  // Writes an absl::Cord to the buffer
  // @param cord: The Cord to write
  // @return: Always returns true (implementation never fails)
  virtual bool WriteCord(const absl::Cord& cord)
#if GOOGLE_PROTOBUF_VERSION >= 4022000
      override
#endif
  {
    grpc_slice_buffer* buffer = slice_buffer();
    size_t cur = 0;
    // Process each chunk in the Cord
    for (absl::string_view chunk : cord.Chunks()) {
      if (chunk.size() < 512) {
        // For small chunks, copy the data
        grpc_slice slice =
            grpc_slice_from_copied_buffer(chunk.data(), chunk.size());
        grpc_slice_buffer_add(buffer, slice);
      } else {
        // For large chunks, use zero-copy approach
        absl::Cord* subcord = new absl::Cord(cord.Subcord(cur, chunk.size()));
        grpc_slice slice = grpc_slice_new_with_user_data(
            const_cast<uint8_t*>(
                reinterpret_cast<const uint8_t*>(chunk.data())),
            chunk.size(), [](void* p) { delete static_cast<absl::Cord*>(p); },
            subcord);
        grpc_slice_buffer_add(buffer, slice);
      }
      cur += chunk.size();
    }
    set_byte_count(ByteCount() + cur);
    return true;
  }
#endif

 protected:
  // Returns the underlying slice buffer
  grpc_slice_buffer* slice_buffer() { return slice_buffer_; }
  // Sets the byte count
  void set_byte_count(int64_t byte_count) { byte_count_ = byte_count; }

 private:
  friend class internal::ProtoBufferWriterPeer;
  const int block_size_;         // Preferred allocation block size
  const int total_size_;         // Total expected size of data
  int64_t byte_count_;           // Total bytes written so far
  grpc_slice_buffer* slice_buffer_;  // The underlying slice buffer
  bool have_backup_;             // Whether we have a backup slice
  grpc_slice backup_slice_;      // Slice holding backed-up data

  grpc_slice slice_;             // Current working slice
};

}  // namespace grpc

#endif  // GRPCPP_SUPPORT_PROTO_BUFFER_WRITER_H
```

The comments explain:
1. The overall purpose of the class (implementing ZeroCopyOutputStream for gRPC ByteBuffers)
2. Each public method's purpose and parameters
3. Key implementation details
4. The role of member variables
5. Special handling for different cases (like small vs large chunks in WriteCord)
6. The relationship with the ProtoBufferWriterPeer friend class

The comments are designed to help future developers understand both the high-level purpose and the implementation details of the code.