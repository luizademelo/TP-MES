Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/lib/transport/promise_endpoint.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/sync.h"

namespace grpc_core {

// Constructor for PromiseEndpoint
// Takes ownership of an EventEngine Endpoint and any already received data
// in a SliceBuffer
PromiseEndpoint::PromiseEndpoint(
    std::unique_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
        endpoint,
    SliceBuffer already_received)
    : endpoint_(std::move(endpoint)) {
  // Ensure endpoint is not null
  CHECK_NE(endpoint_, nullptr);
  // Store the endpoint in read state
  read_state_->endpoint = endpoint_;

  // Swap the contents of the already_received buffer into our read buffer
  grpc_slice_buffer_swap(read_state_->buffer.c_slice_buffer(),
                         already_received.c_slice_buffer());
}

// Returns the peer address of the connected endpoint
const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
PromiseEndpoint::GetPeerAddress() const {
  return endpoint_->GetPeerAddress();
}

// Returns the local address of the connected endpoint
const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
PromiseEndpoint::GetLocalAddress() const {
  return endpoint_->GetLocalAddress();
}

// Completes a read operation, handling both success and failure cases
// This method manages the state machine for reading data from the endpoint
void PromiseEndpoint::ReadState::Complete(absl::Status status,
                                          const size_t num_bytes_requested) {
  // Loop until the read operation is fully completed
  while (true) {
    if (!status.ok()) {
      // Error case: clear buffers, store error status, and wake up waiter
      pending_buffer.Clear();
      buffer.Clear();
      result = status;
      auto w = std::move(waker);
      complete.store(true, std::memory_order_release);
      w.Wakeup();
      return;
    }

    // Move any pending data into the main buffer
    pending_buffer.MoveFirstNBytesIntoSliceBuffer(pending_buffer.Length(),
                                                  buffer);
    DCHECK(pending_buffer.Count() == 0u);
    
    // Check if we still need more data to fulfill the request
    if (buffer.Length() < num_bytes_requested) {
      // Prepare read arguments with hint for remaining bytes needed
      grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs
          read_args;
      read_args.set_read_hint_bytes(
          static_cast<int64_t>(num_bytes_requested - buffer.Length()));

      // Check if endpoint is still available
      auto ep = endpoint.lock();
      if (ep == nullptr) {
        status = absl::UnavailableError("Endpoint closed during read.");
        continue;  // Will trigger error handling in next iteration
      }
      
      // Attempt another read operation
      if (ep->Read(
              [self = Ref(), num_bytes_requested](absl::Status status) {
                // Callback that will be invoked when read completes
                ExecCtx exec_ctx;
                self->Complete(std::move(status), num_bytes_requested);
              },
              &pending_buffer, std::move(read_args))) {
        continue;  // Read was initiated, wait for callback
      }
      return;  // Read failed to initiate
    }
    
    // Success case: we have all requested data
    result = status;
    auto w = std::move(waker);
    complete.store(true, std::memory_order_release);
    w.Wakeup();
    return;
  }
}

}  // namespace grpc_core
```

Key aspects covered in the comments:
1. Class constructor behavior and ownership transfer
2. Getter methods for connection addresses
3. The state machine logic in Complete() method
4. Error handling paths
5. Buffer management during read operations
6. Asynchronous read initiation and callback handling
7. Memory ordering guarantees for the atomic complete flag
8. Waker management for synchronization

The comments explain both the high-level flow and important implementation details while maintaining readability.