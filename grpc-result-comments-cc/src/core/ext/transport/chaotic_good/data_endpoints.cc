Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chaotic_good/data_endpoints.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>

#include "absl/cleanup/cleanup.h"
#include "src/core/ext/transport/chaotic_good/tcp_frame_header.h"
#include "src/core/ext/transport/chaotic_good/tcp_ztrace_collector.h"
#include "src/core/ext/transport/chaotic_good/transport_context.h"
#include "src/core/lib/event_engine/extensions/channelz.h"
#include "src/core/lib/event_engine/extensions/tcp_trace.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/transport/transport_framing_endpoint_extension.h"
#include "src/core/telemetry/default_tcp_tracer.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/string.h"

namespace grpc_core {
namespace chaotic_good {

namespace data_endpoints_detail {

namespace {
// Tag used to identify security frames in the data stream
const uint64_t kSecurityFramePayloadTag = 0;
}

// SendRate class implementation for tracking and calculating send rates
void SendRate::StartSend(uint64_t current_time, uint64_t send_size) {
  CHECK_NE(current_time, 0u);
  send_start_time_ = current_time;
  send_size_ = send_size;
}

// Completes a send operation and updates the current rate measurement
void SendRate::MaybeCompleteSend(uint64_t current_time) {
  if (send_start_time_ == 0) return;
  if (current_time > send_start_time_) {
    // Calculate instantaneous rate (bytes per nanosecond)
    const double rate = static_cast<double>(send_size_) /
                        static_cast<double>(current_time - send_start_time_);

    // Update current rate with exponential moving average
    if (current_rate_ > 0) {
      current_rate_ = 0.9 * current_rate_ + 0.1 * rate;
    } else {
      current_rate_ = rate;
    }
  }
  send_start_time_ = 0;
}

// Sets the current send rate directly
void SendRate::SetCurrentRate(double bytes_per_nanosecond) {
  CHECK_GE(bytes_per_nanosecond, 0.0);
  current_rate_ = bytes_per_nanosecond;
  last_rate_measurement_ = Timestamp::Now();
}

// Checks if the rate measurement is too old to be considered valid
bool SendRate::IsRateMeasurementStale() const {
  return Timestamp::Now() - last_rate_measurement_ > Duration::Seconds(1);
}

// Calculates load balancing decision based on current rate and pending data
LbDecision SendRate::GetLbDecision(uint64_t current_time, size_t bytes) {
  LbDecision decision;
  decision.bytes = bytes;
  if (send_start_time_ != 0) {
    // If there's an ongoing send, include its information
    decision.current_send = {
        send_size_,
        static_cast<double>(current_time - send_start_time_) * 1e-9,
    };
  }
  decision.current_rate = current_rate_;
  if (current_rate_ <= 0 || IsRateMeasurementStale()) {
    // No valid rate information available
    decision.delivery_time = 0.0;
    return decision;
  }

  // Calculate predicted delivery time
  double start_time = 0.0;
  if (send_start_time_ != 0) {
    // Account for ongoing send operation
    const double send_start_time_relative_to_now =
        current_time > send_start_time_
            ? -static_cast<double>(current_time - send_start_time_)
            : static_cast<double>(send_start_time_ - current_time);
    const double predicted_end_time =
        send_start_time_relative_to_now + current_rate_ * send_size_;
    if (predicted_end_time > start_time) start_time = predicted_end_time;
  }
  decision.delivery_time = (start_time + bytes / current_rate_) * 1e-9;
  return decision;
}

// Adds send rate data to a JSON object for monitoring/debugging
void SendRate::AddData(Json::Object& obj) const {
  if (send_start_time_ != 0) {
    obj["send_start_time"] = Json::FromNumber(send_start_time_);
    obj["send_size"] = Json::FromNumber(send_size_);
  }
  obj["current_rate"] = Json::FromNumber(current_rate_);
  obj["rate_measurement_age"] =
      Json::FromNumber((Timestamp::Now() - last_rate_measurement_).millis());
}

// OutputBuffer class implementation for managing output data buffers
LbDecision OutputBuffer::GetLbDecision(uint64_t current_time, size_t bytes) {
  LbDecision decision =
      send_rate_.GetLbDecision(current_time, pending_.Length() + bytes);
  CHECK(decision.delivery_time.has_value());

  // If there's pending data and the delivery time is too long, mark as unavailable
  if (pending_.Length() != 0) {
    if (*decision.delivery_time <= 0.0 || *decision.delivery_time > 0.3) {
      decision.delivery_time = std::nullopt;
    }
  }
  return decision;
}

void OutputBuffer::MaybeCompleteSend(uint64_t current_time) {
  send_rate_.MaybeCompleteSend(current_time);
}

// Takes pending data and starts a new write operation
NextWrite OutputBuffer::TakePendingAndStartWrite(uint64_t current_time) {
  send_rate_.StartSend(current_time, pending_.Length());
  bool trace = false;
  if (send_rate_.IsRateMeasurementStale()) {
    // Perform rate probe if measurement is stale
    send_rate_.PerformRateProbe();
    trace = true;
  }
  NextWrite next_write;
  next_write.bytes = std::move(pending_);
  next_write.trace = trace;
  pending_.Clear();
  return next_write;
}

// Adds output buffer data to a JSON object for monitoring/debugging
void OutputBuffer::AddData(Json::Object& obj) const {
  obj["have_flush_waker"] = Json::FromBool(!flush_waker_.is_unwakeable());
  obj["pending_bytes"] = Json::FromNumber(pending_.Length());
  send_rate_.AddData(obj);
}

// OutputBuffers class implementation for managing multiple output buffers
void OutputBuffers::WriteSecurityFrame(uint32_t connection_id,
                                       SliceBuffer output_buffer) {
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  MutexLock lock(&mu_);
  auto& buffer = buffers_[connection_id];
  if (!buffer.has_value()) return;
  waker = buffer->TakeWaker();
  SliceBuffer& output = buffer->pending();
  CHECK_LT(output_buffer.Length(), std::numeric_limits<uint32_t>::max());
  const uint32_t payload_length = static_cast<uint32_t>(output_buffer.Length());
  
  // Create and serialize frame header
  TcpDataFrameHeader hdr{kSecurityFramePayloadTag, 0, payload_length};
  auto header_padding = DataConnectionPadding(
      TcpDataFrameHeader::kFrameHeaderSize, encode_alignment_);
  MutableSlice header_slice = MutableSlice::CreateUninitialized(
      TcpDataFrameHeader::kFrameHeaderSize + header_padding);
  hdr.Serialize(header_slice.data());
  
  // Add padding if needed
  if (header_padding > 0) {
    memset(header_slice.data() + TcpDataFrameHeader::kFrameHeaderSize, 0,
           header_padding);
  }
  output.AppendIndexed(Slice(std::move(header_slice)));
  
  // Add payload and padding
  const auto payload_padding =
      DataConnectionPadding(output_buffer.Length(), encode_alignment_);
  output.TakeAndAppend(output_buffer);
  if (payload_padding > 0) {
    auto slice = MutableSlice::CreateUninitialized(payload_padding);
    memset(slice.data(), 0, payload_padding);
    output.AppendIndexed(Slice(std::move(slice)));
  }
  
  // Verify alignment
  CHECK_EQ(output.Length() % encode_alignment_, 0u) << GRPC_DUMP_ARGS(
      output.Length(), encode_alignment_, header_padding, payload_padding);
}

// Polls for write operation on the best available endpoint
Poll<Empty> OutputBuffers::PollWrite(uint64_t payload_tag, uint64_t send_time,
                                     SliceBuffer& output_buffer,
                                     std::shared_ptr<TcpCallTracer>&) {
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  const uint32_t length = output_buffer.Length();
  const size_t write_size =
      TcpDataFrameHeader::kFrameHeaderSize +
      DataConnectionPadding(TcpDataFrameHeader::kFrameHeaderSize,
                            encode_alignment_) +
      length + DataConnectionPadding(length, encode_alignment_);
  CHECK_EQ(write_size % encode_alignment_, 0u)
      << GRPC_DUMP_ARGS(write_size, length, encode_alignment_);
  
  MutexLock lock(&mu_);
  // Find the best endpoint based on load balancing decision
  size_t best_endpoint = std::numeric_limits<size_t>::max();
  double earliest_delivery = std::numeric_limits<double>::max();
  for (size_t i = 0; i < buffers_.size(); ++i) {
    if (!buffers_[i].has_value()) continue;
    auto decision = buffers_[i]->GetLbDecision(send_time, write_size);
    if (!decision.delivery_time.has_value()) continue;
    if (*decision.delivery_time < earliest_delivery) {
      earliest_delivery = *decision.delivery_time;
      best_endpoint = i;
    }
  }
  
  if (best_endpoint == std::numeric_limits<size_t>::max()) {
    // No endpoint available
    GRPC_TRACE_LOG(chaotic_good, INFO)
        << "CHAOTIC_GOOD: No data endpoint ready for " << length
        << " bytes on queue " << this;
    ztrace_collector_->Append(NoEndpointForWriteTrace{length, payload_tag});
    write_waker_ = GetContext<Activity>()->MakeNonOwningWaker();
    return Pending{};
  }
  
  // Create frame header
  TcpDataFrameHeader hdr{payload_tag, send_time, length};
  ztrace_collector_->Append(
      [this, &hdr, send_time, best_endpoint, write_size]() {
        std::vector<std::optional<LbDecision>> lb_decisions;
        mu_.AssertHeld();
        for (size_t i = 0; i < buffers_.size(); ++i) {
          if (!buffers_[i].has_value()) {
            lb_decisions.emplace_back(std::nullopt);
            continue;
          }
          lb_decisions.emplace_back(
              buffers_[i]->GetLbDecision(send_time, write_size));
        }
        return WriteLargeFrameHeaderTrace{hdr, best_endpoint,
                                          std::move(lb_decisions)};
      });
  
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: Queue " << length << " data in " << write_size
      << "b wire bytes onto endpoint " << best_endpoint << " queue " << this;
  
  auto& buffer = buffers_[best_endpoint];
  waker = buffer->TakeWaker();
  SliceBuffer& output = buffer->pending();
  CHECK_EQ(output.Length() % encode_alignment_, 0u)
      << GRPC_DUMP_ARGS(output.Length(), encode_alignment_);
  
  // Add header with padding
  const auto header_padding = DataConnectionPadding(
      TcpDataFrameHeader::kFrameHeaderSize, encode_alignment_);
  MutableSlice header_slice = MutableSlice::CreateUninitialized(
      TcpDataFrameHeader::kFrameHeaderSize + header_padding);
  TcpDataFrameHeader{payload_tag, send_time, length}.Serialize(
      header_slice.data());
  if (header_padding > 0) {
    memset(header_slice.data() + TcpDataFrameHeader::kFrameHeaderSize, 0,
           header_padding);
  }
  output.AppendIndexed(Slice(std::move(header_slice)));
  
  // Add payload with padding
  const auto payload_padding =
      DataConnectionPadding(output_buffer.Length(), encode_alignment_);
  output.TakeAndAppend(output_buffer);
  if (payload_padding > 0) {
    auto slice = MutableSlice::CreateUninitialized(payload_padding);
    memset(slice.data(), 0, payload_padding);
    output.AppendIndexed(Slice(std::move(slice)));
  }
  
  // Verify alignment
  CHECK_EQ(output.Length() % encode_alignment_, 0u) << GRPC_DUMP_ARGS(
      output.Length(), encode_alignment_, header_padding, payload_padding);
  return Empty{};
}

// Polls for next write operation on a specific connection
Poll<NextWrite> OutputBuffers::PollNext(uint32_t connection_id) {
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  MutexLock lock(&mu_);
  const auto current_time = clock_->Now();
  auto& buffer = buffers_[connection_id];
  CHECK(buffer.has_value());
  buffer->MaybeCompleteSend(current_time);
  if (buffer->HavePending()) {
    waker = std::move(write_waker_);
    return buffer->TakePendingAndStartWrite(current_time);
  }
  buffer->SetWaker();
  return Pending{};
}

// Adds a new endpoint to the output buffers
void OutputBuffers::AddEndpoint(uint32_t connection_id) {
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  MutexLock lock(&mu_);
  if (buffers_.size() < connection_id + 1) {
    buffers_.resize(connection_id + 1);
  }
  CHECK(!buffers_[connection_id].has_value()) << GRPC_DUMP_ARGS(connection_id);
  buffers_[connection_id].emplace();
  waker = std::move(write_waker_);
  ready_endpoints_.fetch_add(1, std::memory_order_relaxed);
}

// Updates the send rate for a specific connection
void OutputBuffers::UpdateSendRate(uint32_t connection_id,
                                   double bytes_per_nanosecond) {
  MutexLock lock(&mu_);
  auto& buffer = buffers_[connection_id];
  if (!buffer.has_value()) return;
  buffer->UpdateSendRate(bytes_per_nanosecond);
}

// Adds monitoring data to a channelz sink
void OutputBuffers::AddData(channelz::DataSink sink) {
  Json::Object data;
  MutexLock lock(&mu_);
  data["ready_endpoints"] =
      Json::FromNumber(ready_endpoints_.load(std::memory_order_relaxed));
  data["have_write_waker"] = Json::FromBool(!write_waker_.is_unwakeable());
  Json::Array buffers;
  for (const auto& buffer : buffers_) {
    Json::Object obj;
    if (!buffer.has_value()) {
      obj["write_state"] = Json::FromString("closed");
    } else {
      obj["write_state"] = Json::FromString("open");
      buffer->AddData(obj);
    }
    buffers.emplace_back(Json::FromObject(std::move(obj)));
  }
  data["buffers"] = Json::FromArray(std::move(buffers));
  sink.AddAdditionalInfo("outputBuffers", std::move(data));
}

// InputQueue class implementation for managing input data queues
InputQueue::ReadTicket InputQueue::Read(uint64_t payload_tag) {
  {
    MutexLock lock(&mu_);
    if (read_requested_.Set(payload_tag)) {
      return ReadTicket(Failure{}, nullptr);
    }
  }
  return ReadTicket(payload_tag, Ref());
}

// Polls for read operation completion
Poll<absl::StatusOr<SliceBuffer>> InputQueue::PollRead(uint64_t payload_tag) {
  MutexLock lock(&mu_);
  if (!read_completed_.IsSet(payload_tag)) {
    if (!closed_error_.ok()) return closed_error_;
    read_wakers_.emplace(payload_tag,
                         GetContext<Activity>()->MakeNonOwningWaker());
    return Pending{};
  }
  auto it_buffer = read_buffers_.find(payload_tag);

  CHECK(it_buffer != read_buffers_.end());
  auto buffer = std::move(it_buffer->second);
  read_buffers_.erase(it_buffer);
  read_wakers_.erase(payload_tag);
  return std::move(buffer);
}

// Completes a read operation with the received data
void InputQueue::CompleteRead(uint64_t payload_tag, SliceBuffer buffer) {
  if (payload_tag == 0) return;
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  MutexLock lock(&mu_);
  GRPC_TRACE_LOG(chaotic_good, INFO)
      << "CHAOTIC_GOOD: Complete payload_tag #" << payload_tag;
  if (!closed_error_.ok()) return;
  if (read_completed_.Set(payload_tag)) return;
  read_buffers_.emplace(payload_tag, std::move(buffer));
  auto it = read_wakers_.find(payload_tag);
  if (it != read_wakers_.end()) {
    waker = std::move(it->second);
    read_wakers_.erase(it);
  }
}

// Cancels a pending read operation
void InputQueue::Cancel(uint64_t payload_tag) {
  Waker waker;
  auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
  MutexLock lock(&mu_);
  GRPC_TRACE_LOG(chaotic_good, INFO)
      <<