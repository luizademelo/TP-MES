
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_BYTE_BUFFER_H
#define GRPCPP_SUPPORT_BYTE_BUFFER_H

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>

#include <vector>

namespace grpc {

class ServerInterface;
class ByteBuffer;
class ServerInterface;

namespace internal {
template <class RequestType, class ResponseType>
class CallbackUnaryHandler;
template <class RequestType, class ResponseType>
class CallbackServerStreamingHandler;
template <class RequestType>
void* UnaryDeserializeHelper(grpc_byte_buffer*, grpc::Status*, RequestType*);
template <class ServiceType, class RequestType, class ResponseType>
class ServerStreamingHandler;
template <grpc::StatusCode code>
class ErrorMethodHandler;
class CallOpSendMessage;
template <class R>
class CallOpRecvMessage;
class CallOpGenericRecvMessage;
class ExternalConnectionAcceptorImpl;
template <class R>
class DeserializeFuncType;
class GrpcByteBufferPeer;

}

class ByteBuffer final {
 public:

  ByteBuffer() : buffer_(nullptr) {}

  ByteBuffer(const Slice* slices, size_t nslices) {

    static_assert(std::is_same<decltype(slices[0].slice_), grpc_slice>::value,
                  "Slice must have same representation as grpc_slice");
    static_assert(sizeof(Slice) == sizeof(grpc_slice),
                  "Slice must have same representation as grpc_slice");

    static_assert(std::is_same<decltype(buffer_), grpc_byte_buffer*>::value,
                  "ByteBuffer must have same representation as "
                  "grpc_byte_buffer*");
    static_assert(sizeof(ByteBuffer) == sizeof(grpc_byte_buffer*),
                  "ByteBuffer must have same representation as "
                  "grpc_byte_buffer*");

    buffer_ = grpc_raw_byte_buffer_create(
        reinterpret_cast<grpc_slice*>(const_cast<Slice*>(slices)), nslices);
  }

  ByteBuffer(const ByteBuffer& buf) : buffer_(nullptr) { operator=(buf); }

  ~ByteBuffer() {
    if (buffer_) {
      grpc_byte_buffer_destroy(buffer_);
    }
  }

  ByteBuffer& operator=(const ByteBuffer& buf) {
    if (this != &buf) {
      Clear();
    }
    if (buf.buffer_) {

      buffer_ = grpc_byte_buffer_copy(buf.buffer_);
    }
    return *this;
  }

  Status TrySingleSlice(Slice* slice) const;

  Status DumpToSingleSlice(Slice* slice) const;

  Status Dump(std::vector<Slice>* slices) const;

  void Clear() {
    if (buffer_) {
      grpc_byte_buffer_destroy(buffer_);
      buffer_ = nullptr;
    }
  }

  void Duplicate() { buffer_ = grpc_byte_buffer_copy(buffer_); }

  void Release() { buffer_ = nullptr; }

  size_t Length() const {
    return buffer_ == nullptr ? 0 : grpc_byte_buffer_length(buffer_);
  }

  void Swap(ByteBuffer* other) {
    grpc_byte_buffer* tmp = other->buffer_;
    other->buffer_ = buffer_;
    buffer_ = tmp;
  }

  bool Valid() const { return (buffer_ != nullptr); }

 private:
  friend class SerializationTraits<ByteBuffer, void>;
  friend class ServerInterface;
  friend class internal::CallOpSendMessage;
  template <class R>
  friend class internal::CallOpRecvMessage;
  friend class internal::CallOpGenericRecvMessage;
  template <class RequestType>
  friend void* internal::UnaryDeserializeHelper(grpc_byte_buffer*,
                                                grpc::Status*, RequestType*);
  template <class ServiceType, class RequestType, class ResponseType>
  friend class internal::ServerStreamingHandler;
  template <class RequestType, class ResponseType>
  friend class internal::CallbackUnaryHandler;
  template <class RequestType, class ResponseType>
  friend class internal::CallbackServerStreamingHandler;
  template <StatusCode code>
  friend class internal::ErrorMethodHandler;
  template <class R>
  friend class internal::DeserializeFuncType;
  friend class ProtoBufferReader;
  friend class ProtoBufferWriter;
  friend class internal::GrpcByteBufferPeer;
  friend class internal::ExternalConnectionAcceptorImpl;

  grpc_byte_buffer* buffer_;

  void set_buffer(grpc_byte_buffer* buf) {
    if (buffer_) {
      Clear();
    }
    buffer_ = buf;
  }

  grpc_byte_buffer* c_buffer() { return buffer_; }
  grpc_byte_buffer** c_buffer_ptr() { return &buffer_; }

  class ByteBufferPointer {
   public:

    ByteBufferPointer(const ByteBuffer* b)
        : bbuf_(const_cast<ByteBuffer*>(b)) {}

    operator ByteBuffer*() { return bbuf_; }

    operator grpc_byte_buffer*() { return bbuf_->buffer_; }

    operator grpc_byte_buffer**() { return &bbuf_->buffer_; }

   private:
    ByteBuffer* bbuf_;
  };
  ByteBufferPointer bbuf_ptr() const { return ByteBufferPointer(this); }
};

template <>
class SerializationTraits<ByteBuffer, void> {
 public:
  static Status Deserialize(ByteBuffer* byte_buffer, ByteBuffer* dest) {
    dest->set_buffer(byte_buffer->buffer_);
    return Status::OK;
  }
  static Status Serialize(const ByteBuffer& source, ByteBuffer* buffer,
                          bool* own_buffer) {
    *buffer = source;
    *own_buffer = true;
    return grpc::Status::OK;
  }
};

}

#endif
