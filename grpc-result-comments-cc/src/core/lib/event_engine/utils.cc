Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/utils.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/internal/write_event.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/extensions/blocking_dns.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/util/notification.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

// Converts two uintptr_t values into a formatted hexadecimal string representation
// Output format: "{hex_value_a,hex_value_b}" where each value is 16-digit zero-padded
std::string HandleToStringInternal(uintptr_t a, uintptr_t b) {
  return absl::StrCat("{", absl::Hex(a, absl::kZeroPad16), ",",
                      absl::Hex(b, absl::kZeroPad16), "}");
}

// Converts a duration delta into a Timestamp relative to the current time
// Ensures the duration is at least 1 millisecond and adds an additional millisecond
// to prevent immediate expiration. Uses nanoseconds precision with rounding up.
grpc_core::Timestamp ToTimestamp(grpc_core::Timestamp now,
                                 EventEngine::Duration delta) {
  return now +
         std::max(grpc_core::Duration::Milliseconds(1),
                  grpc_core::Duration::NanosecondsRoundUp(delta.count())) +
         grpc_core::Duration::Milliseconds(1);
}

// Performs a blocking DNS hostname lookup
// First tries to use a blocking resolver if supported, otherwise falls back to
// an asynchronous lookup with a notification-based wait mechanism.
// Parameters:
//   dns_resolver - DNS resolver instance to use
//   name - hostname to resolve
//   default_port - default port to use if not specified in the hostname
// Returns:
//   StatusOr containing either the resolved addresses or an error status
absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
LookupHostnameBlocking(EventEngine::DNSResolver* dns_resolver,
                       absl::string_view name, absl::string_view default_port) {
  // Check if the resolver supports blocking operations
  auto* blocking_resolver =
      QueryExtension<ResolverSupportsBlockingLookups>(dns_resolver);
  if (blocking_resolver != nullptr) {
    return blocking_resolver->LookupHostnameBlocking(name, default_port);
  }

  // Fallback to async lookup with blocking wait
  absl::StatusOr<std::vector<EventEngine::ResolvedAddress>> results;
  grpc_core::Notification done;
  dns_resolver->LookupHostname(
      [&](absl::StatusOr<std::vector<EventEngine::ResolvedAddress>> addresses) {
        results = std::move(addresses);
        done.Notify();
      },
      name, default_port);
  done.WaitForNotification();
  return results;
}

// Converts a WriteEvent enum value to its string representation
// Parameters:
//   event - The WriteEvent enum value to convert
// Returns:
//   String representation of the event
// Note:
//   Will log FATAL and return "UNKNOWN" if an invalid event is provided
absl::string_view WriteEventToString(
    grpc_event_engine::experimental::internal::WriteEvent event) {
  switch (event) {
    case grpc_event_engine::experimental::internal::WriteEvent::kSendMsg:
      return "SENDMSG";
    case grpc_event_engine::experimental::internal::WriteEvent::kScheduled:
      return "SCHEDULED";
    case grpc_event_engine::experimental::internal::WriteEvent::kSent:
      return "SENT";
    case grpc_event_engine::experimental::internal::WriteEvent::kAcked:
      return "ACKED";
    case grpc_event_engine::experimental::internal::WriteEvent::kClosed:
      return "CLOSED";
    case grpc_event_engine::experimental::internal::WriteEvent::kCount:
      break;  // This case is intentionally left empty as it's likely a count/sentinel value
  }
  LOG(FATAL) << "WriteEventToString called with " << static_cast<int>(event);
  return "UNKNOWN";
}

}  // namespace grpc_event_engine::experimental
```

The comments added:
1. Explain the purpose and behavior of each function
2. Document parameters and return values
3. Note important implementation details
4. Clarify special cases and edge conditions
5. Maintain consistency with the existing code style
6. Provide context for maintenance developers

The comments are concise yet informative, helping future developers understand the code's intent without being overly verbose.