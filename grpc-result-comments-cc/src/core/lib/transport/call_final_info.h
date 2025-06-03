Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_CALL_FINAL_INFO_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_CALL_FINAL_INFO_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <cstdint>

// Structure representing one-way transport statistics (either incoming or outgoing)
// for a gRPC call. Tracks different types of bytes transferred.
struct grpc_transport_one_way_stats {
  uint64_t framing_bytes = 0;  // Bytes used for protocol framing
  uint64_t data_bytes = 0;     // Actual payload/data bytes
  uint64_t header_bytes = 0;   // Bytes used for headers
};

// Structure representing complete transport statistics for a gRPC stream,
// including both incoming and outgoing directions, plus call latency.
struct grpc_transport_stream_stats {
  grpc_transport_one_way_stats incoming;  // Stats for incoming data
  grpc_transport_one_way_stats outgoing;  // Stats for outgoing data
  gpr_timespec latency = gpr_inf_future(GPR_TIMESPAN);  // Total call latency
};

// Moves one-way transport statistics from 'from' to 'to' structure.
// Typically used to aggregate statistics across different transport operations.
void grpc_transport_move_one_way_stats(grpc_transport_one_way_stats* from,
                                       grpc_transport_one_way_stats* to);

// Moves complete transport stream statistics from 'from' to 'to' structure.
// Used to aggregate stream statistics across different transport operations.
void grpc_transport_move_stats(grpc_transport_stream_stats* from,
                               grpc_transport_stream_stats* to);

// Structure representing complete call statistics including both transport
// layer metrics and overall call latency.
struct grpc_call_stats {
  grpc_transport_stream_stats transport_stream_stats;  // Transport-level stats
  gpr_timespec latency;                               // Total call latency
};

// Structure containing final information about a completed gRPC call,
// including statistics, final status code, and optional error information.
struct grpc_call_final_info {
  grpc_call_stats stats;                   // Detailed call statistics
  grpc_status_code final_status = GRPC_STATUS_OK;  // Final call status code
  const char* error_string = nullptr;      // Optional error description
};

#endif
```

The comments provide:
1. Overview of each structure's purpose
2. Explanation of individual fields
3. Clarification of default values
4. Context for the utility functions
5. Relationship between different structures
6. Usage hints where applicable

The comments maintain a consistent style and provide enough detail to understand the code's purpose without being overly verbose.