// Copyright 2024 gRPC authors.

#include "absl/container/flat_hash_map.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/no_destruct.h"

namespace grpc_core {

DebugOnlyTraceFlag auth_context_refcount_trace(false, "auth_context_refcount");
DebugOnlyTraceFlag call_combiner_trace(false, "call_combiner");
DebugOnlyTraceFlag call_refcount_trace(false, "call_refcount");
DebugOnlyTraceFlag call_state_trace(false, "call_state");
DebugOnlyTraceFlag chttp2_server_refcount_trace(false,
                                                "chttp2_server_refcount");
DebugOnlyTraceFlag closure_trace(false, "closure");
DebugOnlyTraceFlag combiner_trace(false, "combiner");
DebugOnlyTraceFlag cq_refcount_trace(false, "cq_refcount");
DebugOnlyTraceFlag error_refcount_trace(false, "error_refcount");
DebugOnlyTraceFlag fd_refcount_trace(false, "fd_refcount");
DebugOnlyTraceFlag fd_trace_trace(false, "fd_trace");
DebugOnlyTraceFlag lb_policy_refcount_trace(false, "lb_policy_refcount");
DebugOnlyTraceFlag party_state_trace(false, "party_state");
DebugOnlyTraceFlag pending_tags_trace(false, "pending_tags");
DebugOnlyTraceFlag http2_ph2_transport_trace(false, "http2_ph2_transport");
DebugOnlyTraceFlag polling_trace(false, "polling");
DebugOnlyTraceFlag polling_api_trace(false, "polling_api");
DebugOnlyTraceFlag promise_primitives_trace(false, "promise_primitives");
DebugOnlyTraceFlag resolver_refcount_trace(false, "resolver_refcount");
DebugOnlyTraceFlag security_connector_refcount_trace(
    false, "security_connector_refcount");
DebugOnlyTraceFlag slice_refcount_trace(false, "slice_refcount");
DebugOnlyTraceFlag stream_refcount_trace(false, "stream_refcount");
DebugOnlyTraceFlag subchannel_refcount_trace(false, "subchannel_refcount");
DebugOnlyTraceFlag work_serializer_trace(false, "work_serializer");
DebugOnlyTraceFlag ztrace_trace(false, "ztrace");
TraceFlag api_trace(false, "api");
TraceFlag apple_polling_trace(false, "apple_polling");
TraceFlag backend_metric_trace(false, "backend_metric");
TraceFlag backend_metric_filter_trace(false, "backend_metric_filter");
TraceFlag bdp_estimator_trace(false, "bdp_estimator");
TraceFlag call_trace(false, "call");
TraceFlag call_error_trace(false, "call_error");
TraceFlag cares_address_sorting_trace(false, "cares_address_sorting");
TraceFlag cares_resolver_trace(false, "cares_resolver");
TraceFlag cds_lb_trace(false, "cds_lb");
TraceFlag channel_trace(false, "channel");
TraceFlag channel_stack_trace(false, "channel_stack");
TraceFlag chaotic_good_trace(false, "chaotic_good");
TraceFlag chttp2_hpack_parser_trace(false, "chttp2_hpack_parser");
TraceFlag chttp2_new_stream_trace(false, "chttp2_new_stream");
TraceFlag client_channel_trace(false, "client_channel");
TraceFlag client_channel_call_trace(false, "client_channel_call");
TraceFlag client_channel_lb_call_trace(false, "client_channel_lb_call");
TraceFlag client_idle_filter_trace(false, "client_idle_filter");
TraceFlag compression_trace(false, "compression");
TraceFlag connectivity_state_trace(false, "connectivity_state");
TraceFlag dns_resolver_trace(false, "dns_resolver");
TraceFlag environment_autodetect_trace(false, "environment_autodetect");
TraceFlag event_engine_trace(false, "event_engine");
TraceFlag event_engine_client_channel_resolver_trace(
    false, "event_engine_client_channel_resolver");
TraceFlag event_engine_dns_trace(false, "event_engine_dns");
TraceFlag event_engine_endpoint_trace(false, "event_engine_endpoint");
TraceFlag event_engine_endpoint_data_trace(false, "event_engine_endpoint_data");
TraceFlag event_engine_poller_trace(false, "event_engine_poller");
TraceFlag fault_injection_filter_trace(false, "fault_injection_filter");
TraceFlag flowctl_trace(false, "flowctl");
TraceFlag fork_trace(false, "fork");
TraceFlag fuzzing_ee_timers_trace(false, "fuzzing_ee_timers");
TraceFlag fuzzing_ee_writes_trace(false, "fuzzing_ee_writes");
TraceFlag glb_trace(false, "glb");
TraceFlag grpc_authz_api_trace(false, "grpc_authz_api");
TraceFlag handshaker_trace(false, "handshaker");
TraceFlag health_check_client_trace(false, "health_check_client");
TraceFlag http_trace(false, "http");
TraceFlag http1_trace(false, "http1");
TraceFlag http2_ping_trace(false, "http2_ping");
TraceFlag http2_stream_state_trace(false, "http2_stream_state");
TraceFlag http_keepalive_trace(false, "http_keepalive");
TraceFlag inproc_trace(false, "inproc");
TraceFlag metadata_query_trace(false, "metadata_query");
TraceFlag op_failure_trace(false, "op_failure");
TraceFlag orca_client_trace(false, "orca_client");
TraceFlag outlier_detection_lb_trace(false, "outlier_detection_lb");
TraceFlag pick_first_trace(false, "pick_first");
TraceFlag plugin_credentials_trace(false, "plugin_credentials");
TraceFlag priority_lb_trace(false, "priority_lb");
TraceFlag queue_pluck_trace(false, "queue_pluck");
TraceFlag resource_quota_trace(false, "resource_quota");
TraceFlag retry_trace(false, "retry");
TraceFlag ring_hash_lb_trace(false, "ring_hash_lb");
TraceFlag rls_lb_trace(false, "rls_lb");
TraceFlag round_robin_trace(false, "round_robin");
TraceFlag secure_endpoint_trace(false, "secure_endpoint");
TraceFlag server_channel_trace(false, "server_channel");
TraceFlag stateful_session_filter_trace(false, "stateful_session_filter");
TraceFlag subchannel_trace(false, "subchannel");
TraceFlag subchannel_pool_trace(false, "subchannel_pool");
TraceFlag tcp_trace(false, "tcp");
TraceFlag timer_trace(false, "timer");
TraceFlag timer_check_trace(false, "timer_check");
TraceFlag token_fetcher_credentials_trace(false, "token_fetcher_credentials");
TraceFlag tsi_trace(false, "tsi");
TraceFlag weighted_round_robin_lb_trace(false, "weighted_round_robin_lb");
TraceFlag weighted_target_lb_trace(false, "weighted_target_lb");
TraceFlag xds_client_trace(false, "xds_client");
TraceFlag xds_client_refcount_trace(false, "xds_client_refcount");
TraceFlag xds_cluster_impl_lb_trace(false, "xds_cluster_impl_lb");
TraceFlag xds_cluster_manager_lb_trace(false, "xds_cluster_manager_lb");
TraceFlag xds_override_host_lb_trace(false, "xds_override_host_lb");
TraceFlag xds_resolver_trace(false, "xds_resolver");
TraceFlag xds_server_config_fetcher_trace(false, "xds_server_config_fetcher");
TraceFlag xds_wrr_locality_lb_trace(false, "xds_wrr_locality_lb");

const absl::flat_hash_map<std::string, TraceFlag*>& GetAllTraceFlags() {
  static const NoDestruct<absl::flat_hash_map<std::string, TraceFlag*>> all(
      absl::flat_hash_map<std::string, TraceFlag*>({
          {"api", &api_trace},
          {"apple_polling", &apple_polling_trace},
          {"backend_metric", &backend_metric_trace},
          {"backend_metric_filter", &backend_metric_filter_trace},
          {"bdp_estimator", &bdp_estimator_trace},
          {"call", &call_trace},
          {"call_error", &call_error_trace},
          {"cares_address_sorting", &cares_address_sorting_trace},
          {"cares_resolver", &cares_resolver_trace},
          {"cds_lb", &cds_lb_trace},
          {"channel", &channel_trace},
          {"channel_stack", &channel_stack_trace},
          {"chaotic_good", &chaotic_good_trace},
          {"chttp2_hpack_parser", &chttp2_hpack_parser_trace},
          {"chttp2_new_stream", &chttp2_new_stream_trace},
          {"client_channel", &client_channel_trace},
          {"client_channel_call", &client_channel_call_trace},
          {"client_channel_lb_call", &client_channel_lb_call_trace},
          {"client_idle_filter", &client_idle_filter_trace},
          {"compression", &compression_trace},
          {"connectivity_state", &connectivity_state_trace},
          {"dns_resolver", &dns_resolver_trace},
          {"environment_autodetect", &environment_autodetect_trace},
          {"event_engine", &event_engine_trace},
          {"event_engine_client_channel_resolver",
           &event_engine_client_channel_resolver_trace},
          {"event_engine_dns", &event_engine_dns_trace},
          {"event_engine_endpoint", &event_engine_endpoint_trace},
          {"event_engine_endpoint_data", &event_engine_endpoint_data_trace},
          {"event_engine_poller", &event_engine_poller_trace},
          {"fault_injection_filter", &fault_injection_filter_trace},
          {"flowctl", &flowctl_trace},
          {"fork", &fork_trace},
          {"fuzzing_ee_timers", &fuzzing_ee_timers_trace},
          {"fuzzing_ee_writes", &fuzzing_ee_writes_trace},
          {"glb", &glb_trace},
          {"grpc_authz_api", &grpc_authz_api_trace},
          {"handshaker", &handshaker_trace},
          {"health_check_client", &health_check_client_trace},
          {"http", &http_trace},
          {"http1", &http1_trace},
          {"http2_ping", &http2_ping_trace},
          {"http2_stream_state", &http2_stream_state_trace},
          {"http_keepalive", &http_keepalive_trace},
          {"inproc", &inproc_trace},
          {"metadata_query", &metadata_query_trace},
          {"op_failure", &op_failure_trace},
          {"orca_client", &orca_client_trace},
          {"outlier_detection_lb", &outlier_detection_lb_trace},
          {"pick_first", &pick_first_trace},
          {"plugin_credentials", &plugin_credentials_trace},
          {"priority_lb", &priority_lb_trace},
          {"queue_pluck", &queue_pluck_trace},
          {"resource_quota", &resource_quota_trace},
          {"retry", &retry_trace},
          {"ring_hash_lb", &ring_hash_lb_trace},
          {"rls_lb", &rls_lb_trace},
          {"round_robin", &round_robin_trace},
          {"secure_endpoint", &secure_endpoint_trace},
          {"server_channel", &server_channel_trace},
          {"stateful_session_filter", &stateful_session_filter_trace},
          {"subchannel", &subchannel_trace},
          {"subchannel_pool", &subchannel_pool_trace},
          {"tcp", &tcp_trace},
          {"timer", &timer_trace},
          {"timer_check", &timer_check_trace},
          {"token_fetcher_credentials", &token_fetcher_credentials_trace},
          {"tsi", &tsi_trace},
          {"weighted_round_robin_lb", &weighted_round_robin_lb_trace},
          {"weighted_target_lb", &weighted_target_lb_trace},
          {"xds_client", &xds_client_trace},
          {"xds_client_refcount", &xds_client_refcount_trace},
          {"xds_cluster_impl_lb", &xds_cluster_impl_lb_trace},
          {"xds_cluster_manager_lb", &xds_cluster_manager_lb_trace},
          {"xds_override_host_lb", &xds_override_host_lb_trace},
          {"xds_resolver", &xds_resolver_trace},
          {"xds_server_config_fetcher", &xds_server_config_fetcher_trace},
          {"xds_wrr_locality_lb", &xds_wrr_locality_lb_trace},
#ifndef NDEBUG
          {"auth_context_refcount", &auth_context_refcount_trace},
          {"call_combiner", &call_combiner_trace},
          {"call_refcount", &call_refcount_trace},
          {"call_state", &call_state_trace},
          {"chttp2_server_refcount", &chttp2_server_refcount_trace},
          {"closure", &closure_trace},
          {"combiner", &combiner_trace},
          {"cq_refcount", &cq_refcount_trace},
          {"error_refcount", &error_refcount_trace},
          {"fd_refcount", &fd_refcount_trace},
          {"fd_trace", &fd_trace_trace},
          {"lb_policy_refcount", &lb_policy_refcount_trace},
          {"party_state", &party_state_trace},
          {"pending_tags", &pending_tags_trace},
          {"http2_ph2_transport", &http2_ph2_transport_trace},
          {"polling", &polling_trace},
          {"polling_api", &polling_api_trace},
          {"promise_primitives", &promise_primitives_trace},
          {"resolver_refcount", &resolver_refcount_trace},
          {"security_connector_refcount", &security_connector_refcount_trace},
          {"slice_refcount", &slice_refcount_trace},
          {"stream_refcount", &stream_refcount_trace},
          {"subchannel_refcount", &subchannel_refcount_trace},
          {"work_serializer", &work_serializer_trace},
          {"ztrace", &ztrace_trace},
#endif
      }));
  return *all;
}

}
