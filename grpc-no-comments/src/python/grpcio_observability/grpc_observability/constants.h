// Copyright 2023 gRPC authors.

#ifndef GRPC_PYTHON_OBSERVABILITY_CONSTANTS_H
#define GRPC_PYTHON_OBSERVABILITY_CONSTANTS_H

#include <set>
#include <string>

namespace grpc_observability {

const std::string kClientMethod = "grpc.method";
const std::string kClientTarget = "grpc.target";
const std::string kClientStatus = "grpc.status";
const std::string kServerMethod = "grpc.method";
const std::string kServerStatus = "grpc.status";
const std::string kRegisteredMethod = "registerMethod";
const std::string kXEnvoyPeerMetadata = "XEnvoyPeerMetadata";

typedef enum { kMeasurementDouble = 0, kMeasurementInt } MeasurementType;

typedef enum { kSpanData = 0, kMetricData } DataType;

typedef enum {
  kRpcClientApiLatencyMeasureName = 0,
  kRpcClientSentMessagesPerRpcMeasureName,
  kRpcClientSentBytesPerRpcMeasureName,
  kRpcClientReceivedMessagesPerRpcMeasureName,
  kRpcClientReceivedBytesPerRpcMeasureName,
  kRpcClientRoundtripLatencyMeasureName,
  kRpcClientCompletedRpcMeasureName,
  kRpcClientServerLatencyMeasureName,
  kRpcClientStartedRpcsMeasureName,
  kRpcClientRetriesPerCallMeasureName,
  kRpcClientTransparentRetriesPerCallMeasureName,
  kRpcClientRetryDelayPerCallMeasureName,
  kRpcClientTransportLatencyMeasureName,
  kRpcServerSentMessagesPerRpcMeasureName,
  kRpcServerSentBytesPerRpcMeasureName,
  kRpcServerReceivedMessagesPerRpcMeasureName,
  kRpcServerReceivedBytesPerRpcMeasureName,
  kRpcServerServerLatencyMeasureName,
  kRpcServerCompletedRpcMeasureName,
  kRpcServerStartedRpcsMeasureName
} MetricsName;

const std::set<std::string> MetadataExchangeKeyNames = {kXEnvoyPeerMetadata};

}

#endif
