
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_MOCK_ENDPOINT_H
#define GRPC_TEST_CORE_TEST_UTIL_MOCK_ENDPOINT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>

#include <memory>

#include "src/core/lib/iomgr/endpoint.h"

namespace grpc_event_engine {
namespace experimental {

class MockEndpointController
    : public std::enable_shared_from_this<MockEndpointController> {
 public:

  static std::shared_ptr<MockEndpointController> Create(
      std::shared_ptr<EventEngine> engine);

  ~MockEndpointController();

  void TriggerReadEvent(Slice read_data);
  void NoMoreReads();
  void Read(absl::AnyInvocable<void(absl::Status)> on_read,
            SliceBuffer* buffer);

  grpc_endpoint* TakeCEndpoint();

  EventEngine* engine() { return engine_.get(); }

 private:
  explicit MockEndpointController(std::shared_ptr<EventEngine> engine);

  std::shared_ptr<EventEngine> engine_;
  grpc_core::Mutex mu_;
  bool reads_done_ ABSL_GUARDED_BY(mu_) = false;
  SliceBuffer read_buffer_ ABSL_GUARDED_BY(mu_);
  absl::AnyInvocable<void(absl::Status)> on_read_ ABSL_GUARDED_BY(mu_);
  SliceBuffer* on_read_slice_buffer_ ABSL_GUARDED_BY(mu_) = nullptr;
  grpc_endpoint* mock_grpc_endpoint_;
};

class MockEndpoint : public EventEngine::Endpoint {
 public:
  MockEndpoint();
  ~MockEndpoint() override = default;

  void SetController(std::shared_ptr<MockEndpointController> endpoint_control) {
    endpoint_control_ = std::move(endpoint_control);
  }

  bool Read(absl::AnyInvocable<void(absl::Status)> on_read, SliceBuffer* buffer,
            ReadArgs args) override;
  bool Write(absl::AnyInvocable<void(absl::Status)> on_writable,
             SliceBuffer* data, WriteArgs args) override;
  const EventEngine::ResolvedAddress& GetPeerAddress() const override;
  const EventEngine::ResolvedAddress& GetLocalAddress() const override;

  std::vector<size_t> AllWriteMetrics() override { return {}; }

  std::optional<absl::string_view> GetMetricName(size_t) override {
    return std::nullopt;
  }
  std::optional<size_t> GetMetricKey(absl::string_view) override {
    return std::nullopt;
  }

 private:
  std::shared_ptr<MockEndpointController> endpoint_control_;
  EventEngine::ResolvedAddress peer_addr_;
  EventEngine::ResolvedAddress local_addr_;
};

}
}

#endif
