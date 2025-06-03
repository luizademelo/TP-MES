Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers for OpenCensus and gRPC functionality
#include "src/cpp/ext/filters/census/measures.h"
#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>
#include "opencensus/stats/stats.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"

namespace grpc {

// Using declarations for OpenCensus measure types
using ::opencensus::stats::MeasureDouble;
using ::opencensus::stats::MeasureInt64;

namespace {
// Constants for measurement units
constexpr char kUnitBytes[] = "By";          // Bytes unit
constexpr char kUnitMilliseconds[] = "ms";   // Milliseconds unit
constexpr char kCount[] = "1";               // Unitless count
}  // namespace

// Registers and returns a measure for client-side sent bytes per RPC
MeasureDouble RpcClientSentBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientSentBytesPerRpcMeasureName,
      "Total bytes sent across all request messages per RPC", kUnitBytes);
  return measure;
}

// Registers and returns a measure for client-side received bytes per RPC
MeasureDouble RpcClientReceivedBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientReceivedBytesPerRpcMeasureName,
      "Total bytes received across all response messages per RPC", kUnitBytes);
  return measure;
}

// Registers and returns a measure for client-side roundtrip latency
MeasureDouble RpcClientRoundtripLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientRoundtripLatencyMeasureName,
      "Time between first byte of request sent to last byte of response "
      "received, or terminal error",
      kUnitMilliseconds);
  return measure;
}

// Registers and returns a measure for client-side server latency (propagated from server)
MeasureDouble RpcClientServerLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientServerLatencyMeasureName,
      "Time between first byte of request received to last byte of response "
      "sent, or terminal error (propagated from the server)",
      kUnitMilliseconds);
  return measure;
}

// Registers and returns a measure for client-side sent messages count per RPC
MeasureInt64 RpcClientSentMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientSentMessagesPerRpcMeasureName,
      "Number of messages sent per RPC", kCount);
  return measure;
}

// Registers and returns a measure for client-side received messages count per RPC
MeasureInt64 RpcClientReceivedMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientReceivedMessagesPerRpcMeasureName,
      "Number of messages received per RPC", kCount);
  return measure;
}

// Registers and returns a measure for total started client RPCs (including incomplete)
MeasureInt64 RpcClientStartedRpcs() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcClientStartedRpcsMeasureName,
                             "The total number of client RPCs ever opened, "
                             "including those that have not been completed.",
                             kCount);
  return measure;
}

// Registers and returns a measure for client-side transport-level latency
MeasureDouble RpcClientTransportLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientTransportLatencyMeasureName,
      "Time between first byte of request sent to last byte of response "
      "received on the transport",
      kUnitMilliseconds);
  return measure;
}

// Registers and returns a measure for client-side retry attempts per call (excluding transparent retries)
MeasureInt64 RpcClientRetriesPerCall() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcClientRetriesPerCallMeasureName,
                             "Number of retry or hedging attempts excluding "
                             "transparent retries made during the client call",
                             kCount);
  return measure;
}

// Registers and returns a measure for client-side transparent retries per call
MeasureInt64 RpcClientTransparentRetriesPerCall() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientTransparentRetriesPerCallMeasureName,
      "Number of transparent retries made during the client call", kCount);
  return measure;
}

// Registers and returns a measure for client-side total retry delay per call
MeasureDouble RpcClientRetryDelayPerCall() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientRetryDelayPerCallMeasureName,
      "Total time of delay while there is no active "
      "attempt during the client call",
      kUnitMilliseconds);
  return measure;
}

// Registers and returns a measure for server-side sent bytes per RPC
MeasureDouble RpcServerSentBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerSentBytesPerRpcMeasureName,
      "Total bytes sent across all messages per RPC", kUnitBytes);
  return measure;
}

// Registers and returns a measure for server-side received bytes per RPC
MeasureDouble RpcServerReceivedBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerReceivedBytesPerRpcMeasureName,
      "Total bytes received across all messages per RPC", kUnitBytes);
  return measure;
}

// Registers and returns a measure for server-side processing latency
MeasureDouble RpcServerServerLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerServerLatencyMeasureName,
      "Time between first byte of request received to last byte of response "
      "sent, or terminal error",
      kUnitMilliseconds);
  return measure;
}

// Registers and returns a measure for total started server RPCs (including incomplete)
MeasureInt64 RpcServerStartedRpcs() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcServerStartedRpcsMeasureName,
                             "The total number of server RPCs ever opened, "
                             "including those that have not been completed.",
                             kCount);
  return measure;
}

// Registers and returns a measure for server-side sent messages count per RPC
MeasureInt64 RpcServerSentMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcServerSentMessagesPerRpcMeasureName,
      "Number of messages sent per RPC", kCount);
  return measure;
}

// Registers and returns a measure for server-side received messages count per RPC
MeasureInt64 RpcServerReceivedMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcServerReceivedMessagesPerRpcMeasureName,
      "Number of messages received per RPC", kCount);
  return measure;
}

namespace internal {

// Registers and returns a measure for client API latency (internal use)
MeasureDouble RpcClientApiLatency() {
  static const auto measure = MeasureDouble::Register(
      kRpcClientApiLatencyMeasureName,
      "End-to-end time taken to complete an RPC", kUnitMilliseconds);
  return measure;
}

}  // namespace internal
}  // namespace grpc
```