Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_SUPPORT_PROTO_BUFFER_READER_H
#define GRPCPP_SUPPORT_PROTO_BUFFER_READER_H

#include <grpc/byte_buffer.h>
#include <grpc/byte_buffer_reader.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/status.h>

#include <type_traits>

#include "absl/log/absl_check.h"
#include "absl/strings/cord.h"

namespace grpc {

// ProtoBufferReader is an implementation of ZeroCopyInputStream that reads
// protocol buffer messages from a gRPC ByteBuffer.
class ProtoBufferReader : public grpc::protobuf::io::ZeroCopyInputStream {
 public:
  // Constructs a ProtoBufferReader from a ByteBuffer.
  // Initializes the internal reader and checks for validity.
  // If initialization fails, sets an INTERNAL error status.
  explicit ProtoBufferReader(ByteBuffer* buffer)
      : byte_count_(0), backup_count_(0), status_() {
    if (!buffer->Valid() ||
        !grpc_byte_buffer_reader_init(&reader_, buffer->c_buffer())) {
      status_ = Status(StatusCode::INTERNAL,
                       "Couldn't initialize byte buffer reader");
    }
  }

  // Destructor that cleans up the byte buffer reader if it was successfully initialized.
  ~ProtoBufferReader() override {
    if (status_.ok()) {
      grpc_byte_buffer_reader_destroy(&reader_);
    }
  }

  // Gets the next chunk of data from the buffer.
  // Returns true if successful, false otherwise.
  // If there's backup data available, returns that first.
  // Otherwise, reads the next slice from the buffer.
  bool Next(const void** data, int* size) override {
    if (!status_.ok()) {
      return false;
    }

    // First return any backed-up data
    if (backup_count_ > 0) {
      *data = GRPC_SLICE_START_PTR(*slice_) + GRPC_SLICE_LENGTH(*slice_) -
              backup_count_;
      ABSL_CHECK_LE(backup_count_, INT_MAX);
      *size = static_cast<int>(backup_count_);
      backup_count_ = 0;
      return true;
    }

    // Get the next slice from the buffer
    if (!grpc_byte_buffer_reader_peek(&reader_, &slice_)) {
      return false;
    }
    *data = GRPC_SLICE_START_PTR(*slice_);

    // Update byte count and return the slice data
    ABSL_CHECK_LE(GRPC_SLICE_LENGTH(*slice_), static_cast<size_t>(INT_MAX));
    byte_count_ += * size = static_cast<int>(GRPC_SLICE_LENGTH(*slice_));
    return true;
  }

  // Returns the current status of the reader.
  Status status() const { return status_; }

  // Backs up by 'count' bytes in the current slice.
  // The backed-up bytes will be returned by the next call to Next().
  void BackUp(int count) override {
    ABSL_CHECK_LE(count, static_cast<int>(GRPC_SLICE_LENGTH(*slice_)));
    backup_count_ = count;
  }

  // Skips over 'count' bytes in the buffer.
  // Returns true if successful, false if there weren't enough bytes to skip.
  bool Skip(int count) override {
    const void* data;
    int size;
    while (Next(&data, &size)) {
      if (size >= count) {
        BackUp(size - count);
        return true;
      }
      count -= size;
    }
    return false;
  }

  // Returns the total number of bytes read so far, minus any backed-up bytes.
  int64_t ByteCount() const override { return byte_count_ - backup_count_; }

#ifdef GRPC_PROTOBUF_CORD_SUPPORT_ENABLED
  // Reads data into an absl::Cord object.
  // Reads up to 'count' bytes or until end of buffer is reached.
  // Returns true if successful, false otherwise.
  virtual bool ReadCord(absl::Cord* cord, int count)
#if GOOGLE_PROTOBUF_VERSION >= 4022000
      override
#endif
  {
    if (!status().ok()) {
      return false;
    }

    // First handle any backed-up data
    if (backup_count() > 0) {
      if (backup_count() <= count) {
        cord->Append(MakeCordFromSlice(grpc_slice_split_tail(
            slice(), GRPC_SLICE_LENGTH(*slice()) - backup_count())));
      } else {
        cord->Append(MakeCordFromSlice(grpc_slice_sub(
            *slice(), GRPC_SLICE_LENGTH(*slice()) - backup_count(),
            GRPC_SLICE_LENGTH(*slice()) - backup_count() + count)));
      }
      int64_t take = (std::min)(backup_count(), static_cast<int64_t>(count));
      set_backup_count(backup_count() - take);

      count -= static_cast<int>(take);
      if (count == 0) {
        return true;
      }
    }

    // Then read from the buffer
    while (count > 0) {
      if (!grpc_byte_buffer_reader_peek(reader(), mutable_slice_ptr())) {
        return false;
      }
      uint64_t slice_length = GRPC_SLICE_LENGTH(*slice());
      set_byte_count(ByteCount() + slice_length);
      if (slice_length <= static_cast<uint64_t>(count)) {
        cord->Append(MakeCordFromSlice(grpc_slice_ref(*slice())));
        count -= static_cast<int>(slice_length);
      } else {
        cord->Append(MakeCordFromSlice(grpc_slice_split_head(slice(), count)));
        set_backup_count(slice_length - count);
        return true;
      }
    }
    ABSL_CHECK_EQ(count, 0);
    return true;
  }
#endif

 protected:
  // Protected accessors for derived classes
  void set_byte_count(int64_t byte_count) { byte_count_ = byte_count; }
  int64_t backup_count() { return backup_count_; }
  void set_backup_count(int64_t backup_count) { backup_count_ = backup_count; }
  grpc_byte_buffer_reader* reader() { return &reader_; }
  grpc_slice* slice() { return slice_; }
  grpc_slice** mutable_slice_ptr() { return &slice_; }

 private:
#ifdef GRPC_PROTOBUF_CORD_SUPPORT_ENABLED
  // Creates an absl::Cord from a grpc_slice.
  // The Cord takes ownership of the slice and will manage its lifetime.
  static absl::Cord MakeCordFromSlice(grpc_slice slice) {
    grpc_slice* slice_for_cord = new grpc_slice;
    *slice_for_cord = slice;
    return absl::MakeCordFromExternal(
        absl::string_view(
            reinterpret_cast<char*>(GRPC_SLICE_START_PTR(*slice_for_cord)),
            GRPC_SLICE_LENGTH(*slice_for_cord)),
        [slice_for_cord](absl::string_view ) {
          grpc_slice_unref(*slice_for_cord);
          delete slice_for_cord;
        });
  }
#endif

  // Total bytes read so far
  int64_t byte_count_;
  // Bytes that have been backed up (will be read again)
  int64_t backup_count_;
  // The underlying gRPC byte buffer reader
  grpc_byte_buffer_reader reader_;
  // Current slice being read
  grpc_slice* slice_;
  // Status of the reader (error if initialization failed)
  Status status_;
};

}  // namespace grpc

#endif  // GRPCPP_SUPPORT_PROTO_BUFFER_READER_H
```