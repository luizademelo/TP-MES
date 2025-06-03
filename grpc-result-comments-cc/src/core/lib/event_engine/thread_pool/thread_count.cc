Here's the commented version of the code:

```c++
// Copyright 2023 The gRPC Authors

#include "src/core/lib/event_engine/thread_pool/thread_count.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <cstddef>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

// Blocks the current thread until the thread count reaches the desired value or
// until the operation times out.
// Args:
//   desired_threads: Target number of threads to wait for
//   why: Reason for waiting (used for logging)
//   stuck_timeout: Maximum duration to wait if thread count remains unchanged
// Returns:
//   OkStatus if desired thread count is reached,
//   DeadlineExceededError if timeout occurs
absl::Status LivingThreadCount::BlockUntilThreadCount(
    size_t desired_threads, const char* why,
    grpc_core::Duration stuck_timeout) {
  // Record the start time for timeout calculations
  grpc_core::Timestamp timeout_baseline = grpc_core::Timestamp::Now();
  // Interval for periodic logging while waiting
  constexpr grpc_core::Duration log_rate = grpc_core::Duration::Seconds(5);
  // Track previous thread count to detect stuck conditions
  size_t prev_thread_count = 0;
  
  while (true) {
    // Wait for thread count change or half the logging interval
    auto curr_threads = WaitForCountChange(desired_threads, log_rate / 2);
    
    // Return success if desired thread count is reached
    if (curr_threads == desired_threads) return absl::OkStatus();
    
    auto elapsed = grpc_core::Timestamp::Now() - timeout_baseline;
    
    // Check if thread count is stuck (not changing)
    if (curr_threads == prev_thread_count) {
      // Return timeout error if stuck for longer than allowed duration
      if (elapsed > stuck_timeout) {
        return absl::DeadlineExceededError(absl::StrFormat(
            "Timed out after %f seconds", stuck_timeout.seconds()));
      }
    } else {
      // Reset timeout baseline when thread count changes
      prev_thread_count = curr_threads;
      timeout_baseline = grpc_core::Timestamp::Now();
    }
    
    // Log progress periodically
    GRPC_LOG_EVERY_N_SEC_DELAYED_DEBUG(
        log_rate.seconds(),
        "Waiting for thread pool to idle before %s. (%" PRIdPTR " to %" PRIdPTR
        "). Timing out in %0.f seconds.",
        why, curr_threads, desired_threads,
        (stuck_timeout - elapsed).seconds());
  }
}

// Waits for a change in thread count or until timeout expires
// Args:
//   desired_threads: Target thread count that will exit the wait early
//   timeout: Maximum duration to wait for a change
// Returns:
//   Current thread count when either count changes, reaches desired value,
//   or timeout occurs
size_t LivingThreadCount::WaitForCountChange(size_t desired_threads,
                                             grpc_core::Duration timeout) {
  size_t count;
  // Calculate absolute deadline from relative timeout
  auto deadline = absl::Now() + absl::Milliseconds(timeout.millis());
  
  do {
    // Lock mutex to safely access thread count
    grpc_core::MutexLock lock(&mu_);
    count = CountLocked();
    
    // Exit early if desired thread count is reached
    if (count == desired_threads) break;
    
    // Wait for condition variable signal or deadline
    cv_.WaitWithDeadline(&mu_, deadline);
    
  } while (absl::Now() < deadline);  // Continue until deadline passes
  
  return count;
}

}  // namespace grpc_event_engine::experimental
```