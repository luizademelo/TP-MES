// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_DEBUG_TRACE_FLAGS_H
#define GRPC_SRC_CORE_LIB_DEBUG_TRACE_FLAGS_H

#include "src/core/lib/debug/trace_impl.h"

namespace grpc_core {

extern DebugOnlyTraceFlag auth_context_refcount_trace;
extern DebugOnlyTraceFlag call_combiner_trace;
extern DebugOnlyTraceFlag call_refcount_trace;
extern DebugOnlyTraceFlag call_state_trace;
extern DebugOnlyTraceFlag chttp2_server_refcount_trace;
extern DebugOnlyTraceFlag closure_trace;
extern DebugOnlyTraceFlag combiner_trace;
extern DebugOnlyTraceFlag cq_refcount_trace;
extern DebugOnlyTraceFlag error_refcount_trace;
extern DebugOnlyTraceFlag fd_refcount_trace;
extern DebugOnlyTraceFlag fd_trace_trace;
extern DebugOnlyTraceFlag lb_policy_refcount_trace;
extern DebugOnlyTraceFlag party_state_trace;
extern DebugOnlyTraceFlag pending_tags_trace;
extern DebugOnlyTraceFlag http2_ph2_transport_trace;
extern DebugOnlyTraceFlag polling_trace;
extern DebugOnlyTraceFlag polling_api_trace;
extern DebugOnlyTraceFlag promise_primitives_trace;
extern DebugOnlyTraceFlag resolver_refcount_trace;
extern DebugOnlyTraceFlag security_connector_refcount_trace;
extern DebugOnlyTraceFlag slice_refcount_trace;
extern DebugOnlyTraceFlag stream_refcount_trace;
extern DebugOnlyTraceFlag subchannel_refcount_trace;
extern DebugOnlyTraceFlag work_serializer_trace;
extern DebugOnlyTraceFlag ztrace_trace;
extern TraceFlag api_trace;
extern TraceFlag apple_polling_trace;
extern TraceFlag backend_metric_trace;
extern TraceFlag backend_metric_filter_trace;
extern TraceFlag bdp_estimator_trace;
extern TraceFlag call_trace;
extern TraceFlag call_error_trace;
extern TraceFlag cares_address_sorting_trace;
extern TraceFlag cares_resolver_trace;
extern TraceFlag cds_lb_trace;
extern TraceFlag channel_trace;
extern TraceFlag channel_stack_trace;
extern TraceFlag chaotic_good_trace;
extern TraceFlag chttp2_hpack_parser_trace;
extern TraceFlag chttp2_new_stream_trace;
extern TraceFlag client_channel_trace;
extern TraceFlag client_channel_call_trace;
extern TraceFlag client_channel_lb_call_trace;
extern TraceFlag client_idle_filter_trace;
extern TraceFlag compression_trace;
extern TraceFlag connectivity_state_trace;
extern TraceFlag dns_resolver_trace;
extern TraceFlag environment_autodetect_trace;
extern TraceFlag event_engine_trace;
extern TraceFlag event_engine_client_channel_resolver_trace;
extern TraceFlag event_engine_dns_trace;
extern TraceFlag event_engine_endpoint_trace;
extern TraceFlag event_engine_endpoint_data_trace;
extern TraceFlag event_engine_poller_trace;
extern TraceFlag fault_injection_filter_trace;
extern TraceFlag flowctl_trace;
extern TraceFlag fork_trace;
extern TraceFlag fuzzing_ee_timers_trace;
extern TraceFlag fuzzing_ee_writes_trace;
extern TraceFlag glb_trace;
extern TraceFlag grpc_authz_api_trace;
extern TraceFlag handshaker_trace;
extern TraceFlag health_check_client_trace;
extern TraceFlag http_trace;
extern TraceFlag http1_trace;
extern TraceFlag http2_ping_trace;
extern TraceFlag http2_stream_state_trace;
extern TraceFlag http_keepalive_trace;
extern TraceFlag inproc_trace;
extern TraceFlag metadata_query_trace;
extern TraceFlag op_failure_trace;
extern TraceFlag orca_client_trace;
extern TraceFlag outlier_detection_lb_trace;
extern TraceFlag pick_first_trace;
extern TraceFlag plugin_credentials_trace;
extern TraceFlag priority_lb_trace;
extern TraceFlag queue_pluck_trace;
extern TraceFlag resource_quota_trace;
extern TraceFlag retry_trace;
extern TraceFlag ring_hash_lb_trace;
extern TraceFlag rls_lb_trace;
extern TraceFlag round_robin_trace;
extern TraceFlag secure_endpoint_trace;
extern TraceFlag server_channel_trace;
extern TraceFlag stateful_session_filter_trace;
extern TraceFlag subchannel_trace;
extern TraceFlag subchannel_pool_trace;
extern TraceFlag tcp_trace;
extern TraceFlag timer_trace;
extern TraceFlag timer_check_trace;
extern TraceFlag token_fetcher_credentials_trace;
extern TraceFlag tsi_trace;
extern TraceFlag weighted_round_robin_lb_trace;
extern TraceFlag weighted_target_lb_trace;
extern TraceFlag xds_client_trace;
extern TraceFlag xds_client_refcount_trace;
extern TraceFlag xds_cluster_impl_lb_trace;
extern TraceFlag xds_cluster_manager_lb_trace;
extern TraceFlag xds_override_host_lb_trace;
extern TraceFlag xds_resolver_trace;
extern TraceFlag xds_server_config_fetcher_trace;
extern TraceFlag xds_wrr_locality_lb_trace;

}

#endif
