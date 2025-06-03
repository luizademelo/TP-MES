Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/lib/transport/call_final_info.h"

#include <grpc/support/port_platform.h>

#include <utility>

// Helper function to move 64-bit values between locations
// Adds the value at 'from' to 'to' and then zeroes out 'from'
// @param from: Pointer to source 64-bit value
// @param to: Pointer to destination 64-bit value
static void move64bits(uint64_t* from, uint64_t* to) {
  *to += *from;  // Add source value to destination
  *from = 0;     // Zero out source value
}

// Moves one-way transport statistics from source to destination
// Transfers framing_bytes, data_bytes, and header_bytes between stats structures
// @param from: Source statistics structure
// @param to: Destination statistics structure
void grpc_transport_move_one_way_stats(grpc_transport_one_way_stats* from,
                                       grpc_transport_one_way_stats* to) {
  move64bits(&from->framing_bytes, &to->framing_bytes);
  move64bits(&from->data_bytes, &to->data_bytes);
  move64bits(&from->header_bytes, &to->header_bytes);
}

// Moves complete transport stream statistics from source to destination
// Transfers both incoming and outgoing statistics, and updates latency
// @param from: Source statistics structure
// @param to: Destination statistics structure
void grpc_transport_move_stats(grpc_transport_stream_stats* from,
                               grpc_transport_stream_stats* to) {
  // Move incoming statistics
  grpc_transport_move_one_way_stats(&from->incoming, &to->incoming);
  // Move outgoing statistics
  grpc_transport_move_one_way_stats(&from->outgoing, &to->outgoing);
  // Transfer latency value and reset source to infinite future
  to->latency = std::exchange(from->latency, gpr_inf_future(GPR_TIMESPAN));
}
```

The comments explain:
1. The purpose of each function
2. The parameters and their roles
3. The key operations being performed
4. The side effects (like zeroing out source values)
5. The special handling of latency in the final function

The comments are kept concise while providing all the essential information a maintainer would need to understand the code's behavior.