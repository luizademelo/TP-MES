Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_IMPL_CALL_OP_SET_H
#define GRPCPP_IMPL_CALL_OP_SET_H

// Include necessary headers for gRPC core functionality and C++ support
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_hook.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/codegen/intercepted_channel.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/interceptor_common.h>
#include <grpcpp/impl/serialization_traits.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/string_ref.h>

#include <cstring>
#include <map>
#include <memory>

#include "absl/log/absl_check.h"
#include "absl/log/absl_log.h"

namespace grpc {

namespace internal {
class Call;
class CallHook;

// Helper function to convert metadata multimap to gRPC metadata array
inline grpc_metadata* FillMetadataArray(
    const std::multimap<std::string, std::string>& metadata,
    size_t* metadata_count, const std::string& optional_error_details) {
  *metadata_count = metadata.size() + (optional_error_details.empty() ? 0 : 1);
  if (*metadata_count == 0) {
    return nullptr;
  }
  grpc_metadata* metadata_array = static_cast<grpc_metadata*>(
      gpr_malloc((*metadata_count) * sizeof(grpc_metadata)));
  size_t i = 0;
  for (auto iter = metadata.cbegin(); iter != metadata.cend(); ++iter, ++i) {
    metadata_array[i].key = SliceReferencingString(iter->first);
    metadata_array[i].value = SliceReferencingString(iter->second);
  }
  if (!optional_error_details.empty()) {
    metadata_array[i].key = grpc_slice_from_static_buffer(
        kBinaryErrorDetailsKey, sizeof(kBinaryErrorDetailsKey) - 1);
    metadata_array[i].value = SliceReferencingString(optional_error_details);
  }
  return metadata_array;
}
}

// Class representing write options for gRPC calls
class WriteOptions {
 public:
  WriteOptions() : flags_(0), last_message_(false) {}

  inline void Clear() { flags_ = 0; }

  inline uint32_t flags() const { return flags_; }

  // Methods for setting/clearing compression flag
  inline WriteOptions& set_no_compression() {
    SetBit(GRPC_WRITE_NO_COMPRESS);
    return *this;
  }

  inline WriteOptions& clear_no_compression() {
    ClearBit(GRPC_WRITE_NO_COMPRESS);
    return *this;
  }

  inline bool get_no_compression() const {
    return GetBit(GRPC_WRITE_NO_COMPRESS);
  }

  // Methods for setting/clearing buffer hint flag
  inline WriteOptions& set_buffer_hint() {
    SetBit(GRPC_WRITE_BUFFER_HINT);
    return *this;
  }

  inline WriteOptions& clear_buffer_hint() {
    ClearBit(GRPC_WRITE_BUFFER_HINT);
    return *this;
  }

  inline bool get_buffer_hint() const { return GetBit(GRPC_WRITE_BUFFER_HINT); }

  // Methods for setting/clearing corked flag
  inline WriteOptions& set_corked() {
    SetBit(GRPC_WRITE_BUFFER_HINT);
    return *this;
  }

  inline WriteOptions& clear_corked() {
    ClearBit(GRPC_WRITE_BUFFER_HINT);
    return *this;
  }

  inline bool is_corked() const { return GetBit(GRPC_WRITE_BUFFER_HINT); }

  // Methods for setting/clearing last message flag
  inline WriteOptions& set_last_message() {
    last_message_ = true;
    return *this;
  }

  inline WriteOptions& clear_last_message() {
    last_message_ = false;
    return *this;
  }

  bool is_last_message() const { return last_message_; }

  // Methods for setting/clearing write through flag
  inline WriteOptions& set_write_through() {
    SetBit(GRPC_WRITE_THROUGH);
    return *this;
  }

  inline WriteOptions& clear_write_through() {
    ClearBit(GRPC_WRITE_THROUGH);
    return *this;
  }

  inline bool is_write_through() const { return GetBit(GRPC_WRITE_THROUGH); }

 private:
  // Helper methods for bit manipulation
  void SetBit(const uint32_t mask) { flags_ |= mask; }
  void ClearBit(const uint32_t mask) { flags_ &= ~mask; }
  bool GetBit(const uint32_t mask) const { return (flags_ & mask) != 0; }

  uint32_t flags_;
  bool last_message_;
};

namespace internal {

// No-op call operation template
template <int Unused>
class CallNoOp {
 protected:
  void AddOp(grpc_op* , size_t* ) {}
  void FinishOp(bool* ) {}
  void SetInterceptionHookPoint(
      InterceptorBatchMethodsImpl* ) {}
  void SetFinishInterceptionHookPoint(
      InterceptorBatchMethodsImpl* ) {}
  void SetHijackingState(InterceptorBatchMethodsImpl* ) {
  }
};

// Operation for sending initial metadata
class CallOpSendInitialMetadata {
 public:
  CallOpSendInitialMetadata() : send_(false) {
    maybe_compression_level_.is_set = false;
  }

  // Set up initial metadata to be sent
  void SendInitialMetadata(std::multimap<std::string, std::string>* metadata,
                           uint32_t flags) {
    maybe_compression_level_.is_set = false;
    send_ = true;
    flags_ = flags;
    metadata_map_ = metadata;
  }

  // Set compression level for the call
  void set_compression_level(grpc_compression_level level) {
    maybe_compression_level_.is_set = true;
    maybe_compression_level_.level = level;
  }

 protected:
  // Add send initial metadata operation to batch
  void AddOp(grpc_op* ops, size_t* nops) {
    if (!send_ || hijacked_) return;
    grpc_op* op = &ops[(*nops)++];
    op->op = GRPC_OP_SEND_INITIAL_METADATA;
    op->flags = flags_;
    op->reserved = nullptr;
    initial_metadata_ =
        FillMetadataArray(*metadata_map_, &initial_metadata_count_, "");
    op->data.send_initial_metadata.count = initial_metadata_count_;
    op->data.send_initial_metadata.metadata = initial_metadata_;
    op->data.send_initial_metadata.maybe_compression_level.is_set =
        maybe_compression_level_.is_set;
    if (maybe_compression_level_.is_set) {
      op->data.send_initial_metadata.maybe_compression_level.level =
          maybe_compression_level_.level;
    }
  }
  
  // Clean up after operation completes
  void FinishOp(bool* ) {
    if (!send_ || hijacked_) return;
    gpr_free(initial_metadata_);
    send_ = false;
  }

  // Set up interception hook point for this operation
  void SetInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (!send_) return;
    interceptor_methods->AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA);
    interceptor_methods->SetSendInitialMetadata(metadata_map_);
  }

  void SetFinishInterceptionHookPoint(
      InterceptorBatchMethodsImpl* ) {}

  void SetHijackingState(InterceptorBatchMethodsImpl* ) {
    hijacked_ = true;
  }

 private:
  bool hijacked_ = false;
  bool send_;
  uint32_t flags_;
  size_t initial_metadata_count_;
  std::multimap<std::string, std::string>* metadata_map_;
  grpc_metadata* initial_metadata_;
  struct {
    bool is_set;
    grpc_compression_level level;
  } maybe_compression_level_;
};

// Operation for sending messages
class CallOpSendMessage {
 public:
  CallOpSendMessage() : send_buf_() {}

  // Send message with write options
  template <class M>
  GRPC_MUST_USE_RESULT Status SendMessage(const M& message,
                                          WriteOptions options);

  // Send message with default options
  template <class M>
  GRPC_MUST_USE_RESULT Status SendMessage(const M& message);

  // Send message pointer with write options
  template <class M>
  GRPC_MUST_USE_RESULT Status SendMessagePtr(const M* message,
                                             WriteOptions options);

  // Send message pointer with default options
  template <class M>
  GRPC_MUST_USE_RESULT Status SendMessagePtr(const M* message);

 protected:
  // Add send message operation to batch
  void AddOp(grpc_op* ops, size_t* nops) {
    if (msg_ == nullptr && !send_buf_.Valid()) return;
    if (hijacked_) {
      serializer_ = nullptr;
      return;
    }
    if (msg_ != nullptr) {
      ABSL_CHECK(serializer_(msg_).ok());
    }
    serializer_ = nullptr;
    grpc_op* op = &ops[(*nops)++];
    op->op = GRPC_OP_SEND_MESSAGE;
    op->flags = write_options_.flags();
    op->reserved = nullptr;
    op->data.send_message.send_message = send_buf_.c_buffer();

    write_options_.Clear();
  }
  
  // Handle operation completion
  void FinishOp(bool* status) {
    if (msg_ == nullptr && !send_buf_.Valid()) return;
    send_buf_.Clear();
    if (hijacked_ && failed_send_) {
      *status = false;
    } else if (!*status) {
      failed_send_ = true;
    }
  }

  // Set up interception hook point for this operation
  void SetInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (msg_ == nullptr && !send_buf_.Valid()) return;
    interceptor_methods->AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::PRE_SEND_MESSAGE);
    interceptor_methods->SetSendMessage(&send_buf_, &msg_, &failed_send_,
                                        serializer_);
  }

  // Set up post-recv interception hook point
  void SetFinishInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (msg_ != nullptr || send_buf_.Valid()) {
      interceptor_methods->AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::POST_SEND_MESSAGE);
    }
    send_buf_.Clear();
    msg_ = nullptr;

    interceptor_methods->SetSendMessage(nullptr, nullptr, &failed_send_,
                                        nullptr);
  }

  void SetHijackingState(InterceptorBatchMethodsImpl* ) {
    hijacked_ = true;
  }

 private:
  const void* msg_ = nullptr;
  bool hijacked_ = false;
  bool failed_send_ = false;
  ByteBuffer send_buf_;
  WriteOptions write_options_;
  std::function<Status(const void*)> serializer_;
};

// Implementation of SendMessage methods
template <class M>
Status CallOpSendMessage::SendMessage(const M& message, WriteOptions options) {
  write_options_ = options;

  bool own_buf;
  Status result = SerializationTraits<M>::Serialize(
      message, send_buf_.bbuf_ptr(), &own_buf);
  if (!own_buf) {
    send_buf_.Duplicate();
  }
  return result;
}

template <class M>
Status CallOpSendMessage::SendMessage(const M& message) {
  return SendMessage(message, WriteOptions());
}

template <class M>
Status CallOpSendMessage::SendMessagePtr(const M* message,
                                         WriteOptions options) {
  msg_ = message;
  write_options_ = options;

  serializer_ = [this](const void* message) {
    bool own_buf;
    Status result = SerializationTraits<M>::Serialize(
        *static_cast<const M*>(message), send_buf_.bbuf_ptr(), &own_buf);
    if (!own_buf) {
      send_buf_.Duplicate();
    }
    return result;
  };
  return Status();
}

template <class M>
Status CallOpSendMessage::SendMessagePtr(const M* message) {
  return SendMessagePtr(message, WriteOptions());
}

// Operation for receiving messages
template <class R>
class CallOpRecvMessage {
 public:
  void RecvMessage(R* message) { message_ = message; }

  void AllowNoMessage() { allow_not_getting_message_ = true; }

  bool got_message = false;

 protected:
  // Add receive message operation to batch
  void AddOp(grpc_op* ops, size_t* nops) {
    if (message_ == nullptr || hijacked_) return;
    grpc_op* op = &ops[(*nops)++];
    op->op = GRPC_OP_RECV_MESSAGE;
    op->flags = 0;
    op->reserved = nullptr;
    op->data.recv_message.recv_message = recv_buf_.c_buffer_ptr();
  }

  // Handle operation completion
  void FinishOp(bool* status) {
    if (message_ == nullptr) return;
    if (recv_buf_.Valid()) {
      if (*status) {
        got_message = *status =
            SerializationTraits<R>::Deserialize(recv_buf_.bbuf_ptr(), message_)
                .ok();
        recv_buf_.Release();
      } else {
        got_message = false;
        recv_buf_.Clear();
      }
    } else if (hijacked_) {
      if (hijacked_recv_message_failed_) {
        FinishOpRecvMessageFailureHandler(status);
      }
    } else {
      FinishOpRecvMessageFailureHandler(status);
    }
  }

  // Set up interception hook point
  void SetInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (message_ == nullptr) return;
    interceptor_methods->SetRecvMessage(message_,
                                        &hijacked_recv_message_failed_);
  }

  // Set up post-recv interception hook point
  void SetFinishInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (message_ == nullptr) return;
    interceptor_methods->AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::POST_RECV_MESSAGE);
    if (!got_message) interceptor_methods->SetRecvMessage(nullptr, nullptr);
  }
  
  void SetHijackingState(InterceptorBatchMethodsImpl* interceptor_methods) {
    hijacked_ = true;
    if (message_ == nullptr) return;
    interceptor_methods->AddInterceptionHookPoint(
        experimental::InterceptionHookPoints::PRE_RECV_MESSAGE);
    got_message = true;
  }

 private:
  // Helper method for handling receive message failure
  void FinishOpRecvMessageFailureHandler(bool* status) {
    got_message = false;
    if (!allow_not_getting_message_) {
      *status = false;
    }
  }

  R* message_ = nullptr;
  ByteBuffer recv_buf_;
  bool allow_not_getting_message_ = false;
  bool hijacked_ = false;
  bool hijacked_recv_message_failed_ = false;
};

// Abstract base class for deserialization functions
class DeserializeFunc {
 public:
  virtual Status Deserialize(ByteBuffer* buf) = 0;
  virtual ~DeserializeFunc() {}
};

// Template implementation of DeserializeFunc for specific message types
template <class R>
class DeserializeFuncType final : public DeserializeFunc {
 public:
  explicit DeserializeFuncType(R* message) : message_(message) {}
  Status Deserialize(ByteBuffer* buf) override {
    return SerializationTraits<R>::Deserialize(buf->bbuf_ptr(), message_);
  }

  ~DeserializeFuncType() override {}

 private:
  R* message_;
};

// Generic version of message receive operation
class CallOpGenericRecvMessage {
 public:
  template <class R>
  void RecvMessage(R* message) {
    DeserializeFunc* func = new DeserializeFuncType<R>(message);
    deserialize_.reset(func);
    message_ = message;
  }

  void AllowNoMessage() { allow_not_getting_message_ = true; }

  bool got_message = false;

 protected:
  void AddOp(grpc_op* ops, size_t* nops) {
    if (!deserialize_ || hijacked_) return;
    grpc_op* op = &ops[(*nops)++];
    op->op = GRPC_OP_RECV_MESSAGE;
    op->flags = 0;
    op->reserved = nullptr;
    op->data.recv_message.recv_message = recv_buf_.c_buffer_ptr();
  }

  void FinishOp(bool* status) {
    if (!deserialize_) return;
    if (recv_buf_.Valid()) {
      if (*status) {
        got_message = true;
        *status = deserialize_->Deserialize(&recv_buf_).ok();
        recv_buf_.Release();
      } else {
        got_message = false;
        recv_buf_.Clear();
      }
    } else if (hijacked_) {
      if (hijacked_recv_message_failed_) {
        FinishOpRecvMessageFailureHandler(status);
      }
    } else {
      got_message = false;
      if (!allow_not_getting_message_) {
        *status = false;
      }
    }
  }

  void SetInterceptionHookPoint(
      InterceptorBatchMethodsImpl* interceptor_methods) {
    if (!deserialize_) return