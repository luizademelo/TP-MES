Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_MEASURES_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_MEASURES_H

// Platform-specific support definitions
#include <grpc/support/port_platform.h>

// OpenCensus stats measurement library
#include "opencensus/stats/stats.h"

namespace grpc {

// Client-side RPC metrics measures (integer values)
::opencensus::stats::MeasureInt64 RpcClientSentMessagesPerRpc();       // Number of messages sent per RPC
::opencensus::stats::MeasureInt64 RpcClientReceivedMessagesPerRpc();   // Number of messages received per RPC
::opencensus::stats::MeasureInt64 RpcClientStartedRpcs();              // Count of RPCs started
::opencensus::stats::MeasureInt64 RpcClientCompletedRpcs();            // Count of RPCs completed
::opencensus::stats::MeasureInt64 RpcClientRetriesPerCall();           // Number of retries per call
::opencensus::stats::MeasureInt64 RpcClientTransparentRetriesPerCall(); // Number of transparent retries per call

// Client-side RPC metrics measures (floating-point values)
::opencensus::stats::MeasureDouble RpcClientSentBytesPerRpc();         // Bytes sent per RPC
::opencensus::stats::MeasureDouble RpcClientReceivedBytesPerRpc();     // Bytes received per RPC
::opencensus::stats::MeasureDouble RpcClientRoundtripLatency();        // Full roundtrip latency
::opencensus::stats::MeasureDouble RpcClientServerLatency();           // Server processing latency
::opencensus::stats::MeasureDouble RpcClientRetryDelayPerCall();       // Retry delay per call
::opencensus::stats::MeasureDouble RpcClientTransportLatency();        // Transport layer latency

// Server-side RPC metrics measures (integer values)
::opencensus::stats::MeasureInt64 RpcServerSentMessagesPerRpc();       // Number of messages sent per RPC
::opencensus::stats::MeasureInt64 RpcServerReceivedMessagesPerRpc();   // Number of messages received per RPC
::opencensus::stats::MeasureInt64 RpcServerStartedRpcs();              // Count of RPCs started
::opencensus::stats::MeasureInt64 RpcServerCompletedRpcs();            // Count of RPCs completed

// Server-side RPC metrics measures (floating-point values)
::opencensus::stats::MeasureDouble RpcServerSentBytesPerRpc();         // Bytes sent per RPC
::opencensus::stats::MeasureDouble RpcServerReceivedBytesPerRpc();     // Bytes received per RPC
::opencensus::stats::MeasureDouble RpcServerServerLatency();           // Server processing latency

namespace internal {
// Internal client-side API latency measurement
::opencensus::stats::MeasureDouble RpcClientApiLatency();              // Client API processing latency
}

} // namespace grpc

#endif // GRPC_SRC_CPP_EXT_FILTERS_CENSUS_MEASURES_H
```

The comments I've added:
1. Explained the purpose of the header guard
2. Noted the purpose of included headers
3. Organized the measures into logical groups (client/server, int64/double)
4. Added brief descriptions of what each measure tracks
5. Marked the internal namespace section
6. Added closing comments for namespaces and header guard

The comments aim to help developers quickly understand:
- What metrics are being collected
- Whether they're client or server side
- The data type of each metric
- The general purpose of each measurement