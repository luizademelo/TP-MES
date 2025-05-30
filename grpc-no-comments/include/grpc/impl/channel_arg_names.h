// Copyright 2023 gRPC authors.

#ifndef GRPC_IMPL_CHANNEL_ARG_NAMES_H
#define GRPC_IMPL_CHANNEL_ARG_NAMES_H

#define GRPC_ARG_ENABLE_CENSUS "grpc.census"

#define GRPC_ARG_ENABLE_LOAD_REPORTING "grpc.loadreporting"

#define GRPC_ARG_SERVER_CALL_METRIC_RECORDING \
  "grpc.server_call_metric_recording"

#define GRPC_ARG_MINIMAL_STACK "grpc.minimal_stack"

#define GRPC_ARG_MAX_CONCURRENT_STREAMS "grpc.max_concurrent_streams"

#define GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH "grpc.max_receive_message_length"

#define GRPC_ARG_MAX_MESSAGE_LENGTH GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH

#define GRPC_ARG_MAX_SEND_MESSAGE_LENGTH "grpc.max_send_message_length"

#define GRPC_ARG_MAX_CONNECTION_IDLE_MS "grpc.max_connection_idle_ms"

#define GRPC_ARG_MAX_CONNECTION_AGE_MS "grpc.max_connection_age_ms"

#define GRPC_ARG_MAX_CONNECTION_AGE_GRACE_MS "grpc.max_connection_age_grace_ms"

#define GRPC_ARG_CLIENT_IDLE_TIMEOUT_MS "grpc.client_idle_timeout_ms"

#define GRPC_ARG_ENABLE_PER_MESSAGE_COMPRESSION "grpc.per_message_compression"

#define GRPC_ARG_ENABLE_PER_MESSAGE_DECOMPRESSION \
  "grpc.per_message_decompression"

#define GRPC_ARG_HTTP2_INITIAL_SEQUENCE_NUMBER \
  "grpc.http2.initial_sequence_number"

#define GRPC_ARG_HTTP2_STREAM_LOOKAHEAD_BYTES "grpc.http2.lookahead_bytes"

#define GRPC_ARG_HTTP2_HPACK_TABLE_SIZE_DECODER \
  "grpc.http2.hpack_table_size.decoder"

#define GRPC_ARG_HTTP2_HPACK_TABLE_SIZE_ENCODER \
  "grpc.http2.hpack_table_size.encoder"

#define GRPC_ARG_HTTP2_MAX_FRAME_SIZE "grpc.http2.max_frame_size"

#define GRPC_ARG_HTTP2_BDP_PROBE "grpc.http2.bdp_probe"

#define GRPC_ARG_HTTP2_MIN_SENT_PING_INTERVAL_WITHOUT_DATA_MS \
  "grpc.http2.min_time_between_pings_ms"

#define GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS \
  "grpc.http2.min_ping_interval_without_data_ms"

#define GRPC_ARG_SERVER_MAX_UNREQUESTED_TIME_IN_SERVER_SECONDS \
  "grpc.server_max_unrequested_time_in_server"

#define GRPC_ARG_HTTP2_SCHEME "grpc.http2_scheme"

#define GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA \
  "grpc.http2.max_pings_without_data"

#define GRPC_ARG_HTTP2_MAX_PING_STRIKES "grpc.http2.max_ping_strikes"

#define GRPC_ARG_HTTP2_WRITE_BUFFER_SIZE "grpc.http2.write_buffer_size"

#define GRPC_ARG_HTTP2_ENABLE_TRUE_BINARY "grpc.http2.true_binary"

#define GRPC_ARG_EXPERIMENTAL_HTTP2_PREFERRED_CRYPTO_FRAME_SIZE \
  "grpc.experimental.http2.enable_preferred_frame_size"

#define GRPC_ARG_KEEPALIVE_TIME_MS "grpc.keepalive_time_ms"

#define GRPC_ARG_KEEPALIVE_TIMEOUT_MS "grpc.keepalive_timeout_ms"

#define GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS \
  "grpc.keepalive_permit_without_calls"

#define GRPC_ARG_DEFAULT_AUTHORITY "grpc.default_authority"

#define GRPC_ARG_PRIMARY_USER_AGENT_STRING "grpc.primary_user_agent"

#define GRPC_ARG_SECONDARY_USER_AGENT_STRING "grpc.secondary_user_agent"

#define GRPC_ARG_MIN_RECONNECT_BACKOFF_MS "grpc.min_reconnect_backoff_ms"

#define GRPC_ARG_MAX_RECONNECT_BACKOFF_MS "grpc.max_reconnect_backoff_ms"

#define GRPC_ARG_INITIAL_RECONNECT_BACKOFF_MS \
  "grpc.initial_reconnect_backoff_ms"

#define GRPC_ARG_DNS_MIN_TIME_BETWEEN_RESOLUTIONS_MS \
  "grpc.dns_min_time_between_resolutions_ms"

#define GRPC_ARG_SERVER_HANDSHAKE_TIMEOUT_MS "grpc.server_handshake_timeout_ms"

#define GRPC_SSL_TARGET_NAME_OVERRIDE_ARG "grpc.ssl_target_name_override"

#define GRPC_SSL_SESSION_CACHE_ARG "grpc.ssl_session_cache"

#define GRPC_ARG_TSI_MAX_FRAME_SIZE "grpc.tsi.max_frame_size"

#define GRPC_ARG_MAX_METADATA_SIZE "grpc.max_metadata_size"

#define GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE "grpc.absolute_max_metadata_size"

#define GRPC_ARG_ALLOW_REUSEPORT "grpc.so_reuseport"

#define GRPC_ARG_RESOURCE_QUOTA "grpc.resource_quota"

#define GRPC_ARG_EXPAND_WILDCARD_ADDRS "grpc.expand_wildcard_addrs"

#define GRPC_ARG_SERVICE_CONFIG "grpc.service_config"

#define GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION \
  "grpc.service_config_disable_resolution"

#define GRPC_ARG_LB_POLICY_NAME "grpc.lb_policy_name"

#define GRPC_ARG_RING_HASH_LB_RING_SIZE_CAP "grpc.lb.ring_hash.ring_size_cap"

#define GRPC_ARG_SOCKET_MUTATOR "grpc.socket_mutator"

#define GRPC_ARG_SOCKET_FACTORY "grpc.socket_factory"

#define GRPC_ARG_MAX_CHANNEL_TRACE_EVENT_MEMORY_PER_NODE \
  "grpc.max_channel_trace_event_memory_per_node"

#define GRPC_ARG_ENABLE_CHANNELZ "grpc.enable_channelz"

#define GRPC_ARG_TCP_READ_CHUNK_SIZE "grpc.experimental.tcp_read_chunk_size"

#define GRPC_TCP_DEFAULT_READ_SLICE_SIZE 8192

#define GRPC_ARG_TCP_MIN_READ_CHUNK_SIZE \
  "grpc.experimental.tcp_min_read_chunk_size"
#define GRPC_ARG_TCP_MAX_READ_CHUNK_SIZE \
  "grpc.experimental.tcp_max_read_chunk_size"

#define GRPC_ARG_TCP_TX_ZEROCOPY_ENABLED \
  "grpc.experimental.tcp_tx_zerocopy_enabled"

#define GRPC_ARG_TCP_TX_ZEROCOPY_SEND_BYTES_THRESHOLD \
  "grpc.experimental.tcp_tx_zerocopy_send_bytes_threshold"

#define GRPC_ARG_TCP_TX_ZEROCOPY_MAX_SIMULT_SENDS \
  "grpc.experimental.tcp_tx_zerocopy_max_simultaneous_sends"

#define GRPC_ARG_TCP_RECEIVE_BUFFER_SIZE "grpc.tcp_receive_buffer_size"

#define GRPC_ARG_GRPCLB_CALL_TIMEOUT_MS "grpc.grpclb_call_timeout_ms"

#define GRPC_ARG_TEST_ONLY_DO_NOT_USE_IN_PROD_XDS_BOOTSTRAP_CONFIG \
  "grpc.TEST_ONLY_DO_NOT_USE_IN_PROD.xds_bootstrap_config"

#define GRPC_ARG_GRPCLB_FALLBACK_TIMEOUT_MS "grpc.grpclb_fallback_timeout_ms"

#define GRPC_ARG_EXPERIMENTAL_GRPCLB_CHANNEL_ARGS \
  "grpc.experimental.grpclb_channel_args"

#define GRPC_ARG_PRIORITY_FAILOVER_TIMEOUT_MS \
  "grpc.priority_failover_timeout_ms"

#define GRPC_ARG_OPTIMIZATION_TARGET "grpc.optimization_target"

#define GRPC_ARG_ENABLE_RETRIES "grpc.enable_retries"

#define GRPC_ARG_EXPERIMENTAL_ENABLE_HEDGING "grpc.experimental.enable_hedging"

#define GRPC_ARG_PER_RPC_RETRY_BUFFER_SIZE "grpc.per_rpc_retry_buffer_size"

#define GRPC_ARG_MOBILE_LOG_CONTEXT "grpc.mobile_log_context"

#define GRPC_ARG_DISABLE_CLIENT_AUTHORITY_FILTER \
  "grpc.disable_client_authority_filter"

#define GRPC_ARG_ENABLE_HTTP_PROXY "grpc.enable_http_proxy"

#define GRPC_ARG_HTTP_PROXY "grpc.http_proxy"

#define GRPC_ARG_ADDRESS_HTTP_PROXY "grpc.address_http_proxy"

#define GRPC_ARG_ADDRESS_HTTP_PROXY_ENABLED_ADDRESSES \
  "grpc.address_http_proxy_enabled_addresses"

#define GRPC_ARG_SURFACE_USER_AGENT "grpc.surface_user_agent"

#define GRPC_ARG_INHIBIT_HEALTH_CHECKING "grpc.inhibit_health_checking"

#define GRPC_ARG_DNS_ENABLE_SRV_QUERIES "grpc.dns_enable_srv_queries"

#define GRPC_ARG_DNS_ARES_QUERY_TIMEOUT_MS "grpc.dns_ares_query_timeout"

#define GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL "grpc.use_local_subchannel_pool"

#define GRPC_ARG_CHANNEL_POOL_DOMAIN "grpc.channel_pooling_domain"

#define GRPC_ARG_CHANNEL_ID "grpc.channel_id"

#define GRPC_ARG_AUTHORIZATION_POLICY_PROVIDER \
  "grpc.authorization_policy_provider"

#define GRPC_ARG_SERVER_CONFIG_CHANGE_DRAIN_GRACE_TIME_MS \
  "grpc.experimental.server_config_change_drain_grace_time_ms"

#define GRPC_ARG_DSCP "grpc.dscp"

#define GRPC_ARG_HAPPY_EYEBALLS_CONNECTION_ATTEMPT_DELAY_MS \
  "grpc.happy_eyeballs_connection_attempt_delay_ms"

#define GRPC_ARG_EVENT_ENGINE_USE_MEMORY_ALLOCATOR_FACTORY \
  "grpc.event_engine_use_memory_allocator_factory"

#define GRPC_ARG_MAX_ALLOWED_INCOMING_CONNECTIONS \
  "grpc.max_allowed_incoming_connections"

#define GRPC_ARG_EXPERIMENTAL_STATS_PLUGINS "grpc.experimental.stats_plugins"

#define GRPC_ARG_SECURITY_FRAME_ALLOWED "grpc.security_frame_allowed"

#endif
