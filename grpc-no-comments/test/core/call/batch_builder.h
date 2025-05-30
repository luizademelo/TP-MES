// Copyright 2024 gRPC authors.

#ifndef GRPC_TEST_CORE_CALL_BATCH_BUILDER_H
#define GRPC_TEST_CORE_CALL_BATCH_BUILDER_H

#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/lib/slice/slice.h"
#include "test/core/end2end/cq_verifier.h"

namespace grpc_core {

using ByteBufferUniquePtr =
    std::unique_ptr<grpc_byte_buffer, void (*)(grpc_byte_buffer*)>;
ByteBufferUniquePtr ByteBufferFromSlice(Slice slice);

std::optional<std::string> FindInMetadataArray(const grpc_metadata_array& md,
                                               absl::string_view key);

class IncomingMetadata final : public CqVerifier::SuccessfulStateString {
 public:
  IncomingMetadata() = default;
  ~IncomingMetadata() {
    if (metadata_ != nullptr) grpc_metadata_array_destroy(metadata_.get());
  }

  std::optional<std::string> Get(absl::string_view key) const;

  grpc_op MakeOp();

  std::string GetSuccessfulStateString() override;

 private:
  std::unique_ptr<grpc_metadata_array> metadata_ =
      std::make_unique<grpc_metadata_array>(grpc_metadata_array{0, 0, nullptr});
};

class IncomingMessage final : public CqVerifier::SuccessfulStateString {
 public:
  IncomingMessage() = default;
  IncomingMessage(const IncomingMessage&) = delete;
  IncomingMessage& operator=(const IncomingMessage&) = delete;
  ~IncomingMessage() {
    if (payload_ != nullptr) grpc_byte_buffer_destroy(payload_);
  }

  std::string payload() const;

  bool is_end_of_stream() const { return payload_ == nullptr; }

  grpc_byte_buffer_type byte_buffer_type() const { return payload_->type; }

  grpc_compression_algorithm compression() const {
    return payload_->data.raw.compression;
  }
  std::string GetSuccessfulStateString() override;

  grpc_op MakeOp();

  grpc_byte_buffer** raw_payload_ptr() { return &payload_; }

 private:
  grpc_byte_buffer* payload_ = nullptr;
};

class IncomingStatusOnClient final : public CqVerifier::SuccessfulStateString {
 public:
  IncomingStatusOnClient() = default;
  IncomingStatusOnClient(const IncomingStatusOnClient&) = delete;
  IncomingStatusOnClient& operator=(const IncomingStatusOnClient&) = delete;
  IncomingStatusOnClient(IncomingStatusOnClient&& other) noexcept = default;
  IncomingStatusOnClient& operator=(IncomingStatusOnClient&& other) noexcept =
      default;
  ~IncomingStatusOnClient() {
    if (data_ != nullptr) {
      grpc_metadata_array_destroy(&data_->trailing_metadata);
      gpr_free(const_cast<char*>(data_->error_string));
    }
  }

  grpc_status_code status() const { return data_->status; }

  std::string message() const {
    return std::string(data_->status_details.as_string_view());
  }

  std::string error_string() const {
    return data_->error_string == nullptr ? "" : data_->error_string;
  }

  std::optional<std::string> GetTrailingMetadata(absl::string_view key) const;

  std::string GetSuccessfulStateString() override;

  grpc_op MakeOp();

 private:
  struct Data {
    grpc_metadata_array trailing_metadata{0, 0, nullptr};
    grpc_status_code status;
    Slice status_details;
    const char* error_string = nullptr;
  };
  std::unique_ptr<Data> data_ = std::make_unique<Data>();
};

class IncomingCloseOnServer final : public CqVerifier::SuccessfulStateString {
 public:
  IncomingCloseOnServer() = default;
  IncomingCloseOnServer(const IncomingCloseOnServer&) = delete;
  IncomingCloseOnServer& operator=(const IncomingCloseOnServer&) = delete;

  bool was_cancelled() const { return cancelled_ != 0; }

  grpc_op MakeOp();

  std::string GetSuccessfulStateString() override {
    return absl::StrCat("close_on_server: cancelled=", cancelled_);
  }

 private:
  int cancelled_;
};

class BatchBuilder {
 public:
  BatchBuilder(grpc_call* call, CqVerifier* cq_verifier, int tag)
      : call_(call), tag_(tag), cq_verifier_(cq_verifier) {
    cq_verifier_->ClearSuccessfulStateStrings(CqVerifier::tag(tag_));
  }
  ~BatchBuilder();

  BatchBuilder(const BatchBuilder&) = delete;
  BatchBuilder& operator=(const BatchBuilder&) = delete;
  BatchBuilder(BatchBuilder&&) noexcept = default;

  BatchBuilder& SendInitialMetadata(
      std::initializer_list<std::pair<absl::string_view, absl::string_view>> md,
      uint32_t flags = 0,
      std::optional<grpc_compression_level> compression_level = std::nullopt);

  BatchBuilder& SendMessage(Slice payload, uint32_t flags = 0);
  BatchBuilder& SendMessage(absl::string_view payload, uint32_t flags = 0) {
    return SendMessage(Slice::FromCopiedString(payload), flags);
  }

  BatchBuilder& SendCloseFromClient();

  BatchBuilder& SendStatusFromServer(
      grpc_status_code status, absl::string_view message,
      std::initializer_list<std::pair<absl::string_view, absl::string_view>>
          md);

  BatchBuilder& RecvInitialMetadata(IncomingMetadata& md) {
    cq_verifier_->AddSuccessfulStateString(CqVerifier::tag(tag_), &md);
    ops_.emplace_back(md.MakeOp());
    return *this;
  }

  BatchBuilder& RecvMessage(IncomingMessage& msg) {
    cq_verifier_->AddSuccessfulStateString(CqVerifier::tag(tag_), &msg);
    ops_.emplace_back(msg.MakeOp());
    return *this;
  }

  BatchBuilder& RecvStatusOnClient(IncomingStatusOnClient& status) {
    cq_verifier_->AddSuccessfulStateString(CqVerifier::tag(tag_), &status);
    ops_.emplace_back(status.MakeOp());
    return *this;
  }

  BatchBuilder& RecvCloseOnServer(IncomingCloseOnServer& close) {
    cq_verifier_->AddSuccessfulStateString(CqVerifier::tag(tag_), &close);
    ops_.emplace_back(close.MakeOp());
    return *this;
  }

 private:

  class Thing {
   public:
    virtual ~Thing() = default;
  };
  template <typename T>
  class SpecificThing final : public Thing {
   public:
    template <typename... Args>
    explicit SpecificThing(Args&&... args) : t_(std::forward<Args>(args)...) {}
    SpecificThing() = default;

    T& get() { return t_; }

   private:
    T t_;
  };

  template <typename T, typename... Args>
  T& Make(Args&&... args) {
    things_.emplace_back(new SpecificThing<T>(std::forward<Args>(args)...));
    return static_cast<SpecificThing<T>*>(things_.back().get())->get();
  }

  grpc_call* call_;
  const int tag_;
  std::vector<grpc_op> ops_;
  std::vector<std::unique_ptr<Thing>> things_;
  CqVerifier* const cq_verifier_;
};

}

#endif
