
// Copyright 2018 gRPC authors.

#include "src/cpp/ext/filters/census/measures.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/opencensus.h>

#include "opencensus/stats/stats.h"
#include "src/cpp/ext/filters/census/grpc_plugin.h"

namespace grpc {

using ::opencensus::stats::MeasureDouble;
using ::opencensus::stats::MeasureInt64;

namespace {

constexpr char kUnitBytes[] = "By";
constexpr char kUnitMilliseconds[] = "ms";
constexpr char kCount[] = "1";

}

MeasureDouble RpcClientSentBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientSentBytesPerRpcMeasureName,
      "Total bytes sent across all request messages per RPC", kUnitBytes);
  return measure;
}

MeasureDouble RpcClientReceivedBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientReceivedBytesPerRpcMeasureName,
      "Total bytes received across all response messages per RPC", kUnitBytes);
  return measure;
}

MeasureDouble RpcClientRoundtripLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientRoundtripLatencyMeasureName,
      "Time between first byte of request sent to last byte of response "
      "received, or terminal error",
      kUnitMilliseconds);
  return measure;
}

MeasureDouble RpcClientServerLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientServerLatencyMeasureName,
      "Time between first byte of request received to last byte of response "
      "sent, or terminal error (propagated from the server)",
      kUnitMilliseconds);
  return measure;
}

MeasureInt64 RpcClientSentMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientSentMessagesPerRpcMeasureName,
      "Number of messages sent per RPC", kCount);
  return measure;
}

MeasureInt64 RpcClientReceivedMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientReceivedMessagesPerRpcMeasureName,
      "Number of messages received per RPC", kCount);
  return measure;
}

MeasureInt64 RpcClientStartedRpcs() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcClientStartedRpcsMeasureName,
                             "The total number of client RPCs ever opened, "
                             "including those that have not been completed.",
                             kCount);
  return measure;
}

MeasureDouble RpcClientTransportLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientTransportLatencyMeasureName,
      "Time between first byte of request sent to last byte of response "
      "received on the transport",
      kUnitMilliseconds);
  return measure;
}

MeasureInt64 RpcClientRetriesPerCall() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcClientRetriesPerCallMeasureName,
                             "Number of retry or hedging attempts excluding "
                             "transparent retries made during the client call",
                             kCount);
  return measure;
}

MeasureInt64 RpcClientTransparentRetriesPerCall() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcClientTransparentRetriesPerCallMeasureName,
      "Number of transparent retries made during the client call", kCount);
  return measure;
}

MeasureDouble RpcClientRetryDelayPerCall() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcClientRetryDelayPerCallMeasureName,
      "Total time of delay while there is no active "
      "attempt during the client call",
      kUnitMilliseconds);
  return measure;
}

MeasureDouble RpcServerSentBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerSentBytesPerRpcMeasureName,
      "Total bytes sent across all messages per RPC", kUnitBytes);
  return measure;
}

MeasureDouble RpcServerReceivedBytesPerRpc() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerReceivedBytesPerRpcMeasureName,
      "Total bytes received across all messages per RPC", kUnitBytes);
  return measure;
}

MeasureDouble RpcServerServerLatency() {
  static const auto measure = MeasureDouble::Register(
      experimental::kRpcServerServerLatencyMeasureName,
      "Time between first byte of request received to last byte of response "
      "sent, or terminal error",
      kUnitMilliseconds);
  return measure;
}

MeasureInt64 RpcServerStartedRpcs() {
  static const auto measure =
      MeasureInt64::Register(experimental::kRpcServerStartedRpcsMeasureName,
                             "The total number of server RPCs ever opened, "
                             "including those that have not been completed.",
                             kCount);
  return measure;
}

MeasureInt64 RpcServerSentMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcServerSentMessagesPerRpcMeasureName,
      "Number of messages sent per RPC", kCount);
  return measure;
}

MeasureInt64 RpcServerReceivedMessagesPerRpc() {
  static const auto measure = MeasureInt64::Register(
      experimental::kRpcServerReceivedMessagesPerRpcMeasureName,
      "Number of messages received per RPC", kCount);
  return measure;
}

namespace internal {

MeasureDouble RpcClientApiLatency() {
  static const auto measure = MeasureDouble::Register(
      kRpcClientApiLatencyMeasureName,
      "End-to-end time taken to complete an RPC", kUnitMilliseconds);
  return measure;
}

}

}
