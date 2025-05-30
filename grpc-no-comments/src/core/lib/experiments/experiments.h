// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EXPERIMENTS_EXPERIMENTS_H
#define GRPC_SRC_CORE_LIB_EXPERIMENTS_EXPERIMENTS_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/experiments/config.h"

namespace grpc_core {

#ifdef GRPC_EXPERIMENTS_ARE_FINAL

#if defined(GRPC_CFSTREAM)
#define GRPC_EXPERIMENT_IS_INCLUDED_CALL_TRACER_IN_TRANSPORT
inline bool IsCallTracerInTransportEnabled() { return true; }
inline bool IsCallv3ClientAuthFilterEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_CHAOTIC_GOOD_FRAMING_LAYER
inline bool IsChaoticGoodFramingLayerEnabled() { return true; }
inline bool IsChttp2BoundWriteSizeEnabled() { return false; }
inline bool IsErrorFlattenEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CLIENT
inline bool IsEventEngineClientEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS
inline bool IsEventEngineDnsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS_NON_CLIENT_CHANNEL
inline bool IsEventEngineDnsNonClientChannelEnabled() { return true; }
inline bool IsEventEngineForkEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_LISTENER
inline bool IsEventEngineListenerEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CALLBACK_CQ
inline bool IsEventEngineCallbackCqEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_FOR_ALL_OTHER_ENDPOINTS
inline bool IsEventEngineForAllOtherEndpointsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_SECURE_ENDPOINT
inline bool IsEventEngineSecureEndpointEnabled() { return true; }
inline bool IsFreeLargeAllocatorEnabled() { return false; }
inline bool IsKeepAlivePingTimerBatchEnabled() { return false; }
inline bool IsLocalConnectorSecureEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_INFLIGHT_PINGS_STRICT_LIMIT
inline bool IsMaxInflightPingsStrictLimitEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_PINGS_WO_DATA_THROTTLE
inline bool IsMaxPingsWoDataThrottleEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MONITORING_EXPERIMENT
inline bool IsMonitoringExperimentEnabled() { return true; }
inline bool IsMultipingEnabled() { return false; }
inline bool IsPollsetAlternativeEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_POSIX_EE_SKIP_GRPC_INIT
inline bool IsPosixEeSkipGrpcInitEnabled() { return true; }
inline bool IsPromiseBasedHttp2ClientTransportEnabled() { return false; }
inline bool IsPromiseBasedHttp2ServerTransportEnabled() { return false; }
inline bool IsPromiseBasedInprocTransportEnabled() { return false; }
inline bool IsRetryInCallv3Enabled() { return false; }
inline bool IsRqFastRejectEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_RST_STREAM_FIX
inline bool IsRstStreamFixEnabled() { return true; }
inline bool IsScheduleCancellationOverWriteEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeReadsEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeWritesEnabled() { return false; }
inline bool IsServerGlobalCallbacksOwnershipEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_SHARD_GLOBAL_CONNECTION_POOL
inline bool IsShardGlobalConnectionPoolEnabled() { return true; }
inline bool IsSleepPromiseExecCtxRemovalEnabled() { return false; }
inline bool IsTcpFrameSizeTuningEnabled() { return false; }
inline bool IsTcpRcvLowatEnabled() { return false; }
inline bool IsTsiFrameProtectorWithoutLocksEnabled() { return false; }
inline bool IsUnconstrainedMaxQuotaBufferSizeEnabled() { return false; }

#elif defined(GPR_WINDOWS)
#define GRPC_EXPERIMENT_IS_INCLUDED_CALL_TRACER_IN_TRANSPORT
inline bool IsCallTracerInTransportEnabled() { return true; }
inline bool IsCallv3ClientAuthFilterEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_CHAOTIC_GOOD_FRAMING_LAYER
inline bool IsChaoticGoodFramingLayerEnabled() { return true; }
inline bool IsChttp2BoundWriteSizeEnabled() { return false; }
inline bool IsErrorFlattenEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CLIENT
inline bool IsEventEngineClientEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS
inline bool IsEventEngineDnsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS_NON_CLIENT_CHANNEL
inline bool IsEventEngineDnsNonClientChannelEnabled() { return true; }
inline bool IsEventEngineForkEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_LISTENER
inline bool IsEventEngineListenerEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CALLBACK_CQ
inline bool IsEventEngineCallbackCqEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_FOR_ALL_OTHER_ENDPOINTS
inline bool IsEventEngineForAllOtherEndpointsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_SECURE_ENDPOINT
inline bool IsEventEngineSecureEndpointEnabled() { return true; }
inline bool IsFreeLargeAllocatorEnabled() { return false; }
inline bool IsKeepAlivePingTimerBatchEnabled() { return false; }
inline bool IsLocalConnectorSecureEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_INFLIGHT_PINGS_STRICT_LIMIT
inline bool IsMaxInflightPingsStrictLimitEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_PINGS_WO_DATA_THROTTLE
inline bool IsMaxPingsWoDataThrottleEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MONITORING_EXPERIMENT
inline bool IsMonitoringExperimentEnabled() { return true; }
inline bool IsMultipingEnabled() { return false; }
inline bool IsPollsetAlternativeEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_POSIX_EE_SKIP_GRPC_INIT
inline bool IsPosixEeSkipGrpcInitEnabled() { return true; }
inline bool IsPromiseBasedHttp2ClientTransportEnabled() { return false; }
inline bool IsPromiseBasedHttp2ServerTransportEnabled() { return false; }
inline bool IsPromiseBasedInprocTransportEnabled() { return false; }
inline bool IsRetryInCallv3Enabled() { return false; }
inline bool IsRqFastRejectEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_RST_STREAM_FIX
inline bool IsRstStreamFixEnabled() { return true; }
inline bool IsScheduleCancellationOverWriteEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeReadsEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeWritesEnabled() { return false; }
inline bool IsServerGlobalCallbacksOwnershipEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_SHARD_GLOBAL_CONNECTION_POOL
inline bool IsShardGlobalConnectionPoolEnabled() { return true; }
inline bool IsSleepPromiseExecCtxRemovalEnabled() { return false; }
inline bool IsTcpFrameSizeTuningEnabled() { return false; }
inline bool IsTcpRcvLowatEnabled() { return false; }
inline bool IsTsiFrameProtectorWithoutLocksEnabled() { return false; }
inline bool IsUnconstrainedMaxQuotaBufferSizeEnabled() { return false; }

#else
#define GRPC_EXPERIMENT_IS_INCLUDED_CALL_TRACER_IN_TRANSPORT
inline bool IsCallTracerInTransportEnabled() { return true; }
inline bool IsCallv3ClientAuthFilterEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_CHAOTIC_GOOD_FRAMING_LAYER
inline bool IsChaoticGoodFramingLayerEnabled() { return true; }
inline bool IsChttp2BoundWriteSizeEnabled() { return false; }
inline bool IsErrorFlattenEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CLIENT
inline bool IsEventEngineClientEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS
inline bool IsEventEngineDnsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS_NON_CLIENT_CHANNEL
inline bool IsEventEngineDnsNonClientChannelEnabled() { return true; }
inline bool IsEventEngineForkEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_LISTENER
inline bool IsEventEngineListenerEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CALLBACK_CQ
inline bool IsEventEngineCallbackCqEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_FOR_ALL_OTHER_ENDPOINTS
inline bool IsEventEngineForAllOtherEndpointsEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_SECURE_ENDPOINT
inline bool IsEventEngineSecureEndpointEnabled() { return true; }
inline bool IsFreeLargeAllocatorEnabled() { return false; }
inline bool IsKeepAlivePingTimerBatchEnabled() { return false; }
inline bool IsLocalConnectorSecureEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_INFLIGHT_PINGS_STRICT_LIMIT
inline bool IsMaxInflightPingsStrictLimitEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_PINGS_WO_DATA_THROTTLE
inline bool IsMaxPingsWoDataThrottleEnabled() { return true; }
#define GRPC_EXPERIMENT_IS_INCLUDED_MONITORING_EXPERIMENT
inline bool IsMonitoringExperimentEnabled() { return true; }
inline bool IsMultipingEnabled() { return false; }
inline bool IsPollsetAlternativeEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_POSIX_EE_SKIP_GRPC_INIT
inline bool IsPosixEeSkipGrpcInitEnabled() { return true; }
inline bool IsPromiseBasedHttp2ClientTransportEnabled() { return false; }
inline bool IsPromiseBasedHttp2ServerTransportEnabled() { return false; }
inline bool IsPromiseBasedInprocTransportEnabled() { return false; }
inline bool IsRetryInCallv3Enabled() { return false; }
inline bool IsRqFastRejectEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_RST_STREAM_FIX
inline bool IsRstStreamFixEnabled() { return true; }
inline bool IsScheduleCancellationOverWriteEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeReadsEnabled() { return false; }
inline bool IsSecureEndpointOffloadLargeWritesEnabled() { return false; }
inline bool IsServerGlobalCallbacksOwnershipEnabled() { return false; }
#define GRPC_EXPERIMENT_IS_INCLUDED_SHARD_GLOBAL_CONNECTION_POOL
inline bool IsShardGlobalConnectionPoolEnabled() { return true; }
inline bool IsSleepPromiseExecCtxRemovalEnabled() { return false; }
inline bool IsTcpFrameSizeTuningEnabled() { return false; }
inline bool IsTcpRcvLowatEnabled() { return false; }
inline bool IsTsiFrameProtectorWithoutLocksEnabled() { return false; }
inline bool IsUnconstrainedMaxQuotaBufferSizeEnabled() { return false; }
#endif

#else
enum ExperimentIds {
  kExperimentIdCallTracerInTransport,
  kExperimentIdCallv3ClientAuthFilter,
  kExperimentIdChaoticGoodFramingLayer,
  kExperimentIdChttp2BoundWriteSize,
  kExperimentIdErrorFlatten,
  kExperimentIdEventEngineClient,
  kExperimentIdEventEngineDns,
  kExperimentIdEventEngineDnsNonClientChannel,
  kExperimentIdEventEngineFork,
  kExperimentIdEventEngineListener,
  kExperimentIdEventEngineCallbackCq,
  kExperimentIdEventEngineForAllOtherEndpoints,
  kExperimentIdEventEngineSecureEndpoint,
  kExperimentIdFreeLargeAllocator,
  kExperimentIdKeepAlivePingTimerBatch,
  kExperimentIdLocalConnectorSecure,
  kExperimentIdMaxInflightPingsStrictLimit,
  kExperimentIdMaxPingsWoDataThrottle,
  kExperimentIdMonitoringExperiment,
  kExperimentIdMultiping,
  kExperimentIdPollsetAlternative,
  kExperimentIdPosixEeSkipGrpcInit,
  kExperimentIdPromiseBasedHttp2ClientTransport,
  kExperimentIdPromiseBasedHttp2ServerTransport,
  kExperimentIdPromiseBasedInprocTransport,
  kExperimentIdRetryInCallv3,
  kExperimentIdRqFastReject,
  kExperimentIdRstStreamFix,
  kExperimentIdScheduleCancellationOverWrite,
  kExperimentIdSecureEndpointOffloadLargeReads,
  kExperimentIdSecureEndpointOffloadLargeWrites,
  kExperimentIdServerGlobalCallbacksOwnership,
  kExperimentIdShardGlobalConnectionPool,
  kExperimentIdSleepPromiseExecCtxRemoval,
  kExperimentIdTcpFrameSizeTuning,
  kExperimentIdTcpRcvLowat,
  kExperimentIdTsiFrameProtectorWithoutLocks,
  kExperimentIdUnconstrainedMaxQuotaBufferSize,
  kNumExperiments
};
#define GRPC_EXPERIMENT_IS_INCLUDED_CALL_TRACER_IN_TRANSPORT
inline bool IsCallTracerInTransportEnabled() {
  return IsExperimentEnabled<kExperimentIdCallTracerInTransport>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_CALLV3_CLIENT_AUTH_FILTER
inline bool IsCallv3ClientAuthFilterEnabled() {
  return IsExperimentEnabled<kExperimentIdCallv3ClientAuthFilter>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_CHAOTIC_GOOD_FRAMING_LAYER
inline bool IsChaoticGoodFramingLayerEnabled() {
  return IsExperimentEnabled<kExperimentIdChaoticGoodFramingLayer>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_CHTTP2_BOUND_WRITE_SIZE
inline bool IsChttp2BoundWriteSizeEnabled() {
  return IsExperimentEnabled<kExperimentIdChttp2BoundWriteSize>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_ERROR_FLATTEN
inline bool IsErrorFlattenEnabled() {
  return IsExperimentEnabled<kExperimentIdErrorFlatten>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CLIENT
inline bool IsEventEngineClientEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineClient>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS
inline bool IsEventEngineDnsEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineDns>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_DNS_NON_CLIENT_CHANNEL
inline bool IsEventEngineDnsNonClientChannelEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineDnsNonClientChannel>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_FORK
inline bool IsEventEngineForkEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineFork>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_LISTENER
inline bool IsEventEngineListenerEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineListener>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_CALLBACK_CQ
inline bool IsEventEngineCallbackCqEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineCallbackCq>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_FOR_ALL_OTHER_ENDPOINTS
inline bool IsEventEngineForAllOtherEndpointsEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineForAllOtherEndpoints>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_EVENT_ENGINE_SECURE_ENDPOINT
inline bool IsEventEngineSecureEndpointEnabled() {
  return IsExperimentEnabled<kExperimentIdEventEngineSecureEndpoint>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_FREE_LARGE_ALLOCATOR
inline bool IsFreeLargeAllocatorEnabled() {
  return IsExperimentEnabled<kExperimentIdFreeLargeAllocator>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_KEEP_ALIVE_PING_TIMER_BATCH
inline bool IsKeepAlivePingTimerBatchEnabled() {
  return IsExperimentEnabled<kExperimentIdKeepAlivePingTimerBatch>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_LOCAL_CONNECTOR_SECURE
inline bool IsLocalConnectorSecureEnabled() {
  return IsExperimentEnabled<kExperimentIdLocalConnectorSecure>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_INFLIGHT_PINGS_STRICT_LIMIT
inline bool IsMaxInflightPingsStrictLimitEnabled() {
  return IsExperimentEnabled<kExperimentIdMaxInflightPingsStrictLimit>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_MAX_PINGS_WO_DATA_THROTTLE
inline bool IsMaxPingsWoDataThrottleEnabled() {
  return IsExperimentEnabled<kExperimentIdMaxPingsWoDataThrottle>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_MONITORING_EXPERIMENT
inline bool IsMonitoringExperimentEnabled() {
  return IsExperimentEnabled<kExperimentIdMonitoringExperiment>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_MULTIPING
inline bool IsMultipingEnabled() {
  return IsExperimentEnabled<kExperimentIdMultiping>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_POLLSET_ALTERNATIVE
inline bool IsPollsetAlternativeEnabled() {
  return IsExperimentEnabled<kExperimentIdPollsetAlternative>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_POSIX_EE_SKIP_GRPC_INIT
inline bool IsPosixEeSkipGrpcInitEnabled() {
  return IsExperimentEnabled<kExperimentIdPosixEeSkipGrpcInit>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_PROMISE_BASED_HTTP2_CLIENT_TRANSPORT
inline bool IsPromiseBasedHttp2ClientTransportEnabled() {
  return IsExperimentEnabled<kExperimentIdPromiseBasedHttp2ClientTransport>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_PROMISE_BASED_HTTP2_SERVER_TRANSPORT
inline bool IsPromiseBasedHttp2ServerTransportEnabled() {
  return IsExperimentEnabled<kExperimentIdPromiseBasedHttp2ServerTransport>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_PROMISE_BASED_INPROC_TRANSPORT
inline bool IsPromiseBasedInprocTransportEnabled() {
  return IsExperimentEnabled<kExperimentIdPromiseBasedInprocTransport>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_RETRY_IN_CALLV3
inline bool IsRetryInCallv3Enabled() {
  return IsExperimentEnabled<kExperimentIdRetryInCallv3>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_RQ_FAST_REJECT
inline bool IsRqFastRejectEnabled() {
  return IsExperimentEnabled<kExperimentIdRqFastReject>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_RST_STREAM_FIX
inline bool IsRstStreamFixEnabled() {
  return IsExperimentEnabled<kExperimentIdRstStreamFix>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SCHEDULE_CANCELLATION_OVER_WRITE
inline bool IsScheduleCancellationOverWriteEnabled() {
  return IsExperimentEnabled<kExperimentIdScheduleCancellationOverWrite>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SECURE_ENDPOINT_OFFLOAD_LARGE_READS
inline bool IsSecureEndpointOffloadLargeReadsEnabled() {
  return IsExperimentEnabled<kExperimentIdSecureEndpointOffloadLargeReads>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SECURE_ENDPOINT_OFFLOAD_LARGE_WRITES
inline bool IsSecureEndpointOffloadLargeWritesEnabled() {
  return IsExperimentEnabled<kExperimentIdSecureEndpointOffloadLargeWrites>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SERVER_GLOBAL_CALLBACKS_OWNERSHIP
inline bool IsServerGlobalCallbacksOwnershipEnabled() {
  return IsExperimentEnabled<kExperimentIdServerGlobalCallbacksOwnership>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SHARD_GLOBAL_CONNECTION_POOL
inline bool IsShardGlobalConnectionPoolEnabled() {
  return IsExperimentEnabled<kExperimentIdShardGlobalConnectionPool>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_SLEEP_PROMISE_EXEC_CTX_REMOVAL
inline bool IsSleepPromiseExecCtxRemovalEnabled() {
  return IsExperimentEnabled<kExperimentIdSleepPromiseExecCtxRemoval>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TCP_FRAME_SIZE_TUNING
inline bool IsTcpFrameSizeTuningEnabled() {
  return IsExperimentEnabled<kExperimentIdTcpFrameSizeTuning>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TCP_RCV_LOWAT
inline bool IsTcpRcvLowatEnabled() {
  return IsExperimentEnabled<kExperimentIdTcpRcvLowat>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_TSI_FRAME_PROTECTOR_WITHOUT_LOCKS
inline bool IsTsiFrameProtectorWithoutLocksEnabled() {
  return IsExperimentEnabled<kExperimentIdTsiFrameProtectorWithoutLocks>();
}
#define GRPC_EXPERIMENT_IS_INCLUDED_UNCONSTRAINED_MAX_QUOTA_BUFFER_SIZE
inline bool IsUnconstrainedMaxQuotaBufferSizeEnabled() {
  return IsExperimentEnabled<kExperimentIdUnconstrainedMaxQuotaBufferSize>();
}

extern const ExperimentMetadata g_experiment_metadata[kNumExperiments];

#endif
}

#endif
