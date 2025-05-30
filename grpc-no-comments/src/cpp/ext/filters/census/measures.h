
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_FILTERS_CENSUS_MEASURES_H
#define GRPC_SRC_CPP_EXT_FILTERS_CENSUS_MEASURES_H

#include <grpc/support/port_platform.h>

#include "opencensus/stats/stats.h"

namespace grpc {

::opencensus::stats::MeasureInt64 RpcClientSentMessagesPerRpc();
::opencensus::stats::MeasureDouble RpcClientSentBytesPerRpc();
::opencensus::stats::MeasureInt64 RpcClientReceivedMessagesPerRpc();
::opencensus::stats::MeasureDouble RpcClientReceivedBytesPerRpc();
::opencensus::stats::MeasureDouble RpcClientRoundtripLatency();
::opencensus::stats::MeasureDouble RpcClientServerLatency();
::opencensus::stats::MeasureInt64 RpcClientStartedRpcs();
::opencensus::stats::MeasureInt64 RpcClientCompletedRpcs();
::opencensus::stats::MeasureInt64 RpcClientRetriesPerCall();
::opencensus::stats::MeasureInt64 RpcClientTransparentRetriesPerCall();
::opencensus::stats::MeasureDouble RpcClientRetryDelayPerCall();
::opencensus::stats::MeasureDouble RpcClientTransportLatency();

::opencensus::stats::MeasureInt64 RpcServerSentMessagesPerRpc();
::opencensus::stats::MeasureDouble RpcServerSentBytesPerRpc();
::opencensus::stats::MeasureInt64 RpcServerReceivedMessagesPerRpc();
::opencensus::stats::MeasureDouble RpcServerReceivedBytesPerRpc();
::opencensus::stats::MeasureDouble RpcServerServerLatency();
::opencensus::stats::MeasureInt64 RpcServerStartedRpcs();
::opencensus::stats::MeasureInt64 RpcServerCompletedRpcs();

namespace internal {
::opencensus::stats::MeasureDouble RpcClientApiLatency();
}

}

#endif
