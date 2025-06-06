
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.auth import tls_pb2 as envoy_dot_api_dot_v2_dot_auth_dot_tls__pb2
from envoy.api.v2.cluster import circuit_breaker_pb2 as envoy_dot_api_dot_v2_dot_cluster_dot_circuit__breaker__pb2
from envoy.api.v2.cluster import filter_pb2 as envoy_dot_api_dot_v2_dot_cluster_dot_filter__pb2
from envoy.api.v2.cluster import outlier_detection_pb2 as envoy_dot_api_dot_v2_dot_cluster_dot_outlier__detection__pb2
from envoy.api.v2.core import address_pb2 as envoy_dot_api_dot_v2_dot_core_dot_address__pb2
from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from envoy.api.v2.core import config_source_pb2 as envoy_dot_api_dot_v2_dot_core_dot_config__source__pb2
from envoy.api.v2.core import health_check_pb2 as envoy_dot_api_dot_v2_dot_core_dot_health__check__pb2
from envoy.api.v2.core import protocol_pb2 as envoy_dot_api_dot_v2_dot_core_dot_protocol__pb2
from envoy.api.v2 import endpoint_pb2 as envoy_dot_api_dot_v2_dot_endpoint__pb2
from envoy.type import percent_pb2 as envoy_dot_type_dot_percent__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1a\x65nvoy/api/v2/cluster.proto\x12\x0c\x65nvoy.api.v2\x1a\x1b\x65nvoy/api/v2/auth/tls.proto\x1a*envoy/api/v2/cluster/circuit_breaker.proto\x1a!envoy/api/v2/cluster/filter.proto\x1a,envoy/api/v2/cluster/outlier_detection.proto\x1a\x1f\x65nvoy/api/v2/core/address.proto\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a%envoy/api/v2/core/config_source.proto\x1a$envoy/api/v2/core/health_check.proto\x1a envoy/api/v2/core/protocol.proto\x1a\x1b\x65nvoy/api/v2/endpoint.proto\x1a\x18\x65nvoy/type/percent.proto\x1a\x19google/protobuf/any.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xad.\n\x07\x43luster\x12L\n\x18transport_socket_matches\x18+ \x03(\x0b\x32*.envoy.api.v2.Cluster.TransportSocketMatch\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x15\n\ralt_stat_name\x18\x1c \x01(\t\x12=\n\x04type\x18\x02 \x01(\x0e\x32#.envoy.api.v2.Cluster.DiscoveryTypeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01H\x00\x12?\n\x0c\x63luster_type\x18& \x01(\x0b\x32\'.envoy.api.v2.Cluster.CustomClusterTypeH\x00\x12\x42\n\x12\x65\x64s_cluster_config\x18\x03 \x01(\x0b\x32&.envoy.api.v2.Cluster.EdsClusterConfig\x12<\n\x0f\x63onnect_timeout\x18\x04 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x12G\n!per_connection_buffer_limit_bytes\x18\x05 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12;\n\tlb_policy\x18\x06 \x01(\x0e\x32\x1e.envoy.api.v2.Cluster.LbPolicyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12-\n\x05hosts\x18\x07 \x03(\x0b\x32\x1a.envoy.api.v2.core.AddressB\x02\x18\x01\x12<\n\x0fload_assignment\x18! \x01(\x0b\x32#.envoy.api.v2.ClusterLoadAssignment\x12\x35\n\rhealth_checks\x18\x08 \x03(\x0b\x32\x1e.envoy.api.v2.core.HealthCheck\x12\x41\n\x1bmax_requests_per_connection\x18\t \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12?\n\x10\x63ircuit_breakers\x18\n \x01(\x0b\x32%.envoy.api.v2.cluster.CircuitBreakers\x12\x44\n\x0btls_context\x18\x0b \x01(\x0b\x32%.envoy.api.v2.auth.UpstreamTlsContextB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12V\n\x1eupstream_http_protocol_options\x18. \x01(\x0b\x32..envoy.api.v2.core.UpstreamHttpProtocolOptions\x12L\n\x1c\x63ommon_http_protocol_options\x18\x1d \x01(\x0b\x32&.envoy.api.v2.core.HttpProtocolOptions\x12\x46\n\x15http_protocol_options\x18\r \x01(\x0b\x32\'.envoy.api.v2.core.Http1ProtocolOptions\x12G\n\x16http2_protocol_options\x18\x0e \x01(\x0b\x32\'.envoy.api.v2.core.Http2ProtocolOptions\x12\x61\n\x1a\x65xtension_protocol_options\x18# \x03(\x0b\x32\x33.envoy.api.v2.Cluster.ExtensionProtocolOptionsEntryB\x08\x18\x01\xb8\xee\xf2\xd2\x05\x01\x12\x62\n typed_extension_protocol_options\x18$ \x03(\x0b\x32\x38.envoy.api.v2.Cluster.TypedExtensionProtocolOptionsEntry\x12\x41\n\x10\x64ns_refresh_rate\x18\x10 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0c\xfa\x42\t\xaa\x01\x06*\x04\x10\xc0\x84=\x12\x43\n\x18\x64ns_failure_refresh_rate\x18, \x01(\x0b\x32!.envoy.api.v2.Cluster.RefreshRate\x12\x17\n\x0frespect_dns_ttl\x18\' \x01(\x08\x12J\n\x11\x64ns_lookup_family\x18\x11 \x01(\x0e\x32%.envoy.api.v2.Cluster.DnsLookupFamilyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x31\n\rdns_resolvers\x18\x12 \x03(\x0b\x32\x1a.envoy.api.v2.core.Address\x12\x1f\n\x17use_tcp_for_dns_lookups\x18- \x01(\x08\x12\x41\n\x11outlier_detection\x18\x13 \x01(\x0b\x32&.envoy.api.v2.cluster.OutlierDetection\x12=\n\x10\x63leanup_interval\x18\x14 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x12;\n\x14upstream_bind_config\x18\x15 \x01(\x0b\x32\x1d.envoy.api.v2.core.BindConfig\x12>\n\x10lb_subset_config\x18\x16 \x01(\x0b\x32$.envoy.api.v2.Cluster.LbSubsetConfig\x12\x45\n\x13ring_hash_lb_config\x18\x17 \x01(\x0b\x32&.envoy.api.v2.Cluster.RingHashLbConfigH\x01\x12K\n\x16original_dst_lb_config\x18\" \x01(\x0b\x32).envoy.api.v2.Cluster.OriginalDstLbConfigH\x01\x12M\n\x17least_request_lb_config\x18% \x01(\x0b\x32*.envoy.api.v2.Cluster.LeastRequestLbConfigH\x01\x12>\n\x10\x63ommon_lb_config\x18\x1b \x01(\x0b\x32$.envoy.api.v2.Cluster.CommonLbConfig\x12<\n\x10transport_socket\x18\x18 \x01(\x0b\x32\".envoy.api.v2.core.TransportSocket\x12-\n\x08metadata\x18\x19 \x01(\x0b\x32\x1b.envoy.api.v2.core.Metadata\x12J\n\x12protocol_selection\x18\x1a \x01(\x0e\x32..envoy.api.v2.Cluster.ClusterProtocolSelection\x12L\n\x1bupstream_connection_options\x18\x1e \x01(\x0b\x32\'.envoy.api.v2.UpstreamConnectionOptions\x12\x30\n(close_connections_on_host_health_failure\x18\x1f \x01(\x08\x12P\n!drain_connections_on_host_removal\x18  \x01(\x08\x42%\xf2\x98\xfe\x8f\x05\x1f\n\x1dignore_health_on_host_removal\x12-\n\x07\x66ilters\x18( \x03(\x0b\x32\x1c.envoy.api.v2.cluster.Filter\x12@\n\x15load_balancing_policy\x18) \x01(\x0b\x32!.envoy.api.v2.LoadBalancingPolicy\x12\x33\n\nlrs_server\x18* \x01(\x0b\x32\x1f.envoy.api.v2.core.ConfigSource\x12\x1d\n\x15track_timeout_budgets\x18/ \x01(\x08\x1a\x93\x01\n\x14TransportSocketMatch\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12&\n\x05match\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct\x12<\n\x10transport_socket\x18\x03 \x01(\x0b\x32\".envoy.api.v2.core.TransportSocket\x1aV\n\x11\x43ustomClusterType\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12*\n\x0ctyped_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x1a]\n\x10\x45\x64sClusterConfig\x12\x33\n\neds_config\x18\x01 \x01(\x0b\x32\x1f.envoy.api.v2.core.ConfigSource\x12\x14\n\x0cservice_name\x18\x02 \x01(\t\x1a\xe3\x05\n\x0eLbSubsetConfig\x12^\n\x0f\x66\x61llback_policy\x18\x01 \x01(\x0e\x32;.envoy.api.v2.Cluster.LbSubsetConfig.LbSubsetFallbackPolicyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12/\n\x0e\x64\x65\x66\x61ult_subset\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct\x12O\n\x10subset_selectors\x18\x03 \x03(\x0b\x32\x35.envoy.api.v2.Cluster.LbSubsetConfig.LbSubsetSelector\x12\x1d\n\x15locality_weight_aware\x18\x04 \x01(\x08\x12\x1d\n\x15scale_locality_weight\x18\x05 \x01(\x08\x12\x16\n\x0epanic_mode_any\x18\x06 \x01(\x08\x12\x13\n\x0blist_as_any\x18\x07 \x01(\x08\x1a\xb2\x02\n\x10LbSubsetSelector\x12\x0c\n\x04keys\x18\x01 \x03(\t\x12w\n\x0f\x66\x61llback_policy\x18\x02 \x01(\x0e\x32T.envoy.api.v2.Cluster.LbSubsetConfig.LbSubsetSelector.LbSubsetSelectorFallbackPolicyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x1c\n\x14\x66\x61llback_keys_subset\x18\x03 \x03(\t\"y\n\x1eLbSubsetSelectorFallbackPolicy\x12\x0f\n\x0bNOT_DEFINED\x10\x00\x12\x0f\n\x0bNO_FALLBACK\x10\x01\x12\x10\n\x0c\x41NY_ENDPOINT\x10\x02\x12\x12\n\x0e\x44\x45\x46\x41ULT_SUBSET\x10\x03\x12\x0f\n\x0bKEYS_SUBSET\x10\x04\"O\n\x16LbSubsetFallbackPolicy\x12\x0f\n\x0bNO_FALLBACK\x10\x00\x12\x10\n\x0c\x41NY_ENDPOINT\x10\x01\x12\x12\n\x0e\x44\x45\x46\x41ULT_SUBSET\x10\x02\x1aS\n\x14LeastRequestLbConfig\x12;\n\x0c\x63hoice_count\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(\x02\x1a\xa8\x02\n\x10RingHashLbConfig\x12\x43\n\x11minimum_ring_size\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\n\xfa\x42\x07\x32\x05\x18\x80\x80\x80\x04\x12T\n\rhash_function\x18\x03 \x01(\x0e\x32\x33.envoy.api.v2.Cluster.RingHashLbConfig.HashFunctionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x43\n\x11maximum_ring_size\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\n\xfa\x42\x07\x32\x05\x18\x80\x80\x80\x04\".\n\x0cHashFunction\x12\x0b\n\x07XX_HASH\x10\x00\x12\x11\n\rMURMUR_HASH_2\x10\x01J\x04\x08\x02\x10\x03\x1a.\n\x13OriginalDstLbConfig\x12\x17\n\x0fuse_http_header\x18\x01 \x01(\x08\x1a\x8c\x06\n\x0e\x43ommonLbConfig\x12\x34\n\x17healthy_panic_threshold\x18\x01 \x01(\x0b\x32\x13.envoy.type.Percent\x12V\n\x14zone_aware_lb_config\x18\x02 \x01(\x0b\x32\x36.envoy.api.v2.Cluster.CommonLbConfig.ZoneAwareLbConfigH\x00\x12\x64\n\x1blocality_weighted_lb_config\x18\x03 \x01(\x0b\x32=.envoy.api.v2.Cluster.CommonLbConfig.LocalityWeightedLbConfigH\x00\x12\x36\n\x13update_merge_window\x18\x04 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\'\n\x1fignore_new_hosts_until_first_hc\x18\x05 \x01(\x08\x12,\n$close_connections_on_host_set_change\x18\x06 \x01(\x08\x12\x64\n\x1c\x63onsistent_hashing_lb_config\x18\x07 \x01(\x0b\x32>.envoy.api.v2.Cluster.CommonLbConfig.ConsistentHashingLbConfig\x1a\x98\x01\n\x11ZoneAwareLbConfig\x12,\n\x0frouting_enabled\x18\x01 \x01(\x0b\x32\x13.envoy.type.Percent\x12\x36\n\x10min_cluster_size\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt64Value\x12\x1d\n\x15\x66\x61il_traffic_on_panic\x18\x03 \x01(\x08\x1a\x1a\n\x18LocalityWeightedLbConfig\x1a=\n\x19\x43onsistentHashingLbConfig\x12 \n\x18use_hostname_for_hashing\x18\x01 \x01(\x08\x42\x1b\n\x19locality_config_specifier\x1a\x8e\x01\n\x0bRefreshRate\x12@\n\rbase_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0e\xfa\x42\x0b\xaa\x01\x08\x08\x01*\x04\x10\xc0\x84=\x12=\n\x0cmax_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0c\xfa\x42\t\xaa\x01\x06*\x04\x10\xc0\x84=\x1aX\n\x1d\x45xtensionProtocolOptionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12&\n\x05value\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct:\x02\x38\x01\x1aZ\n\"TypedExtensionProtocolOptionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any:\x02\x38\x01\"W\n\rDiscoveryType\x12\n\n\x06STATIC\x10\x00\x12\x0e\n\nSTRICT_DNS\x10\x01\x12\x0f\n\x0bLOGICAL_DNS\x10\x02\x12\x07\n\x03\x45\x44S\x10\x03\x12\x10\n\x0cORIGINAL_DST\x10\x04\"\xac\x01\n\x08LbPolicy\x12\x0f\n\x0bROUND_ROBIN\x10\x00\x12\x11\n\rLEAST_REQUEST\x10\x01\x12\r\n\tRING_HASH\x10\x02\x12\n\n\x06RANDOM\x10\x03\x12\x1d\n\x0fORIGINAL_DST_LB\x10\x04\x1a\x08\x08\x01\xa8\xf7\xb4\x8b\x02\x01\x12\n\n\x06MAGLEV\x10\x05\x12\x14\n\x10\x43LUSTER_PROVIDED\x10\x06\x12 \n\x1cLOAD_BALANCING_POLICY_CONFIG\x10\x07\"5\n\x0f\x44nsLookupFamily\x12\x08\n\x04\x41UTO\x10\x00\x12\x0b\n\x07V4_ONLY\x10\x01\x12\x0b\n\x07V6_ONLY\x10\x02\"T\n\x18\x43lusterProtocolSelection\x12\x1b\n\x17USE_CONFIGURED_PROTOCOL\x10\x00\x12\x1b\n\x17USE_DOWNSTREAM_PROTOCOL\x10\x01\x42\x18\n\x16\x63luster_discovery_typeB\x0b\n\tlb_configJ\x04\x08\x0c\x10\rJ\x04\x08\x0f\x10\x10\"\xc2\x01\n\x13LoadBalancingPolicy\x12:\n\x08policies\x18\x01 \x03(\x0b\x32(.envoy.api.v2.LoadBalancingPolicy.Policy\x1ao\n\x06Policy\x12\x0c\n\x04name\x18\x01 \x01(\t\x12+\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x02\x18\x01\x12*\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.Any\"H\n\x12UpstreamBindConfig\x12\x32\n\x0esource_address\x18\x01 \x01(\x0b\x32\x1a.envoy.api.v2.core.Address\"S\n\x19UpstreamConnectionOptions\x12\x36\n\rtcp_keepalive\x18\x01 \x01(\x0b\x32\x1f.envoy.api.v2.core.TcpKeepaliveB\x8e\x01\n\x1aio.envoyproxy.envoy.api.v2B\x0c\x43lusterProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/api/v2;apiv2\xf2\x98\xfe\x8f\x05\x19\x12\x17\x65nvoy.config.cluster.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.cluster_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\032io.envoyproxy.envoy.api.v2B\014ClusterProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/api/v2;apiv2\362\230\376\217\005\031\022\027envoy.config.cluster.v3\272\200\310\321\006\002\020\001'
  _CLUSTER_TRANSPORTSOCKETMATCH.fields_by_name['name']._options = None
  _CLUSTER_TRANSPORTSOCKETMATCH.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _CLUSTER_CUSTOMCLUSTERTYPE.fields_by_name['name']._options = None
  _CLUSTER_CUSTOMCLUSTERTYPE.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR.fields_by_name['fallback_policy']._options = None
  _CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR.fields_by_name['fallback_policy']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER_LBSUBSETCONFIG.fields_by_name['fallback_policy']._options = None
  _CLUSTER_LBSUBSETCONFIG.fields_by_name['fallback_policy']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER_LEASTREQUESTLBCONFIG.fields_by_name['choice_count']._options = None
  _CLUSTER_LEASTREQUESTLBCONFIG.fields_by_name['choice_count']._serialized_options = b'\372B\004*\002(\002'
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['minimum_ring_size']._options = None
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['minimum_ring_size']._serialized_options = b'\372B\0072\005\030\200\200\200\004'
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['hash_function']._options = None
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['hash_function']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['maximum_ring_size']._options = None
  _CLUSTER_RINGHASHLBCONFIG.fields_by_name['maximum_ring_size']._serialized_options = b'\372B\0072\005\030\200\200\200\004'
  _CLUSTER_REFRESHRATE.fields_by_name['base_interval']._options = None
  _CLUSTER_REFRESHRATE.fields_by_name['base_interval']._serialized_options = b'\372B\013\252\001\010\010\001*\004\020\300\204='
  _CLUSTER_REFRESHRATE.fields_by_name['max_interval']._options = None
  _CLUSTER_REFRESHRATE.fields_by_name['max_interval']._serialized_options = b'\372B\t\252\001\006*\004\020\300\204='
  _CLUSTER_EXTENSIONPROTOCOLOPTIONSENTRY._options = None
  _CLUSTER_EXTENSIONPROTOCOLOPTIONSENTRY._serialized_options = b'8\001'
  _CLUSTER_TYPEDEXTENSIONPROTOCOLOPTIONSENTRY._options = None
  _CLUSTER_TYPEDEXTENSIONPROTOCOLOPTIONSENTRY._serialized_options = b'8\001'
  _CLUSTER_LBPOLICY.values_by_name["ORIGINAL_DST_LB"]._options = None
  _CLUSTER_LBPOLICY.values_by_name["ORIGINAL_DST_LB"]._serialized_options = b'\010\001\250\367\264\213\002\001'
  _CLUSTER.fields_by_name['name']._options = None
  _CLUSTER.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _CLUSTER.fields_by_name['type']._options = None
  _CLUSTER.fields_by_name['type']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER.fields_by_name['connect_timeout']._options = None
  _CLUSTER.fields_by_name['connect_timeout']._serialized_options = b'\372B\005\252\001\002*\000'
  _CLUSTER.fields_by_name['lb_policy']._options = None
  _CLUSTER.fields_by_name['lb_policy']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER.fields_by_name['hosts']._options = None
  _CLUSTER.fields_by_name['hosts']._serialized_options = b'\030\001'
  _CLUSTER.fields_by_name['tls_context']._options = None
  _CLUSTER.fields_by_name['tls_context']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _CLUSTER.fields_by_name['extension_protocol_options']._options = None
  _CLUSTER.fields_by_name['extension_protocol_options']._serialized_options = b'\030\001\270\356\362\322\005\001'
  _CLUSTER.fields_by_name['dns_refresh_rate']._options = None
  _CLUSTER.fields_by_name['dns_refresh_rate']._serialized_options = b'\372B\t\252\001\006*\004\020\300\204='
  _CLUSTER.fields_by_name['dns_lookup_family']._options = None
  _CLUSTER.fields_by_name['dns_lookup_family']._serialized_options = b'\372B\005\202\001\002\020\001'
  _CLUSTER.fields_by_name['cleanup_interval']._options = None
  _CLUSTER.fields_by_name['cleanup_interval']._serialized_options = b'\372B\005\252\001\002*\000'
  _CLUSTER.fields_by_name['drain_connections_on_host_removal']._options = None
  _CLUSTER.fields_by_name['drain_connections_on_host_removal']._serialized_options = b'\362\230\376\217\005\037\n\035ignore_health_on_host_removal'
  _LOADBALANCINGPOLICY_POLICY.fields_by_name['config']._options = None
  _LOADBALANCINGPOLICY_POLICY.fields_by_name['config']._serialized_options = b'\030\001'
  _globals['_CLUSTER']._serialized_start=674
  _globals['_CLUSTER']._serialized_end=6607
  _globals['_CLUSTER_TRANSPORTSOCKETMATCH']._serialized_start=3537
  _globals['_CLUSTER_TRANSPORTSOCKETMATCH']._serialized_end=3684
  _globals['_CLUSTER_CUSTOMCLUSTERTYPE']._serialized_start=3686
  _globals['_CLUSTER_CUSTOMCLUSTERTYPE']._serialized_end=3772
  _globals['_CLUSTER_EDSCLUSTERCONFIG']._serialized_start=3774
  _globals['_CLUSTER_EDSCLUSTERCONFIG']._serialized_end=3867
  _globals['_CLUSTER_LBSUBSETCONFIG']._serialized_start=3870
  _globals['_CLUSTER_LBSUBSETCONFIG']._serialized_end=4609
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR']._serialized_start=4222
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR']._serialized_end=4528
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR_LBSUBSETSELECTORFALLBACKPOLICY']._serialized_start=4407
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETSELECTOR_LBSUBSETSELECTORFALLBACKPOLICY']._serialized_end=4528
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETFALLBACKPOLICY']._serialized_start=4530
  _globals['_CLUSTER_LBSUBSETCONFIG_LBSUBSETFALLBACKPOLICY']._serialized_end=4609
  _globals['_CLUSTER_LEASTREQUESTLBCONFIG']._serialized_start=4611
  _globals['_CLUSTER_LEASTREQUESTLBCONFIG']._serialized_end=4694
  _globals['_CLUSTER_RINGHASHLBCONFIG']._serialized_start=4697
  _globals['_CLUSTER_RINGHASHLBCONFIG']._serialized_end=4993
  _globals['_CLUSTER_RINGHASHLBCONFIG_HASHFUNCTION']._serialized_start=4941
  _globals['_CLUSTER_RINGHASHLBCONFIG_HASHFUNCTION']._serialized_end=4987
  _globals['_CLUSTER_ORIGINALDSTLBCONFIG']._serialized_start=4995
  _globals['_CLUSTER_ORIGINALDSTLBCONFIG']._serialized_end=5041
  _globals['_CLUSTER_COMMONLBCONFIG']._serialized_start=5044
  _globals['_CLUSTER_COMMONLBCONFIG']._serialized_end=5824
  _globals['_CLUSTER_COMMONLBCONFIG_ZONEAWARELBCONFIG']._serialized_start=5552
  _globals['_CLUSTER_COMMONLBCONFIG_ZONEAWARELBCONFIG']._serialized_end=5704
  _globals['_CLUSTER_COMMONLBCONFIG_LOCALITYWEIGHTEDLBCONFIG']._serialized_start=5706
  _globals['_CLUSTER_COMMONLBCONFIG_LOCALITYWEIGHTEDLBCONFIG']._serialized_end=5732
  _globals['_CLUSTER_COMMONLBCONFIG_CONSISTENTHASHINGLBCONFIG']._serialized_start=5734
  _globals['_CLUSTER_COMMONLBCONFIG_CONSISTENTHASHINGLBCONFIG']._serialized_end=5795
  _globals['_CLUSTER_REFRESHRATE']._serialized_start=5827
  _globals['_CLUSTER_REFRESHRATE']._serialized_end=5969
  _globals['_CLUSTER_EXTENSIONPROTOCOLOPTIONSENTRY']._serialized_start=5971
  _globals['_CLUSTER_EXTENSIONPROTOCOLOPTIONSENTRY']._serialized_end=6059
  _globals['_CLUSTER_TYPEDEXTENSIONPROTOCOLOPTIONSENTRY']._serialized_start=6061
  _globals['_CLUSTER_TYPEDEXTENSIONPROTOCOLOPTIONSENTRY']._serialized_end=6151
  _globals['_CLUSTER_DISCOVERYTYPE']._serialized_start=6153
  _globals['_CLUSTER_DISCOVERYTYPE']._serialized_end=6240
  _globals['_CLUSTER_LBPOLICY']._serialized_start=6243
  _globals['_CLUSTER_LBPOLICY']._serialized_end=6415
  _globals['_CLUSTER_DNSLOOKUPFAMILY']._serialized_start=6417
  _globals['_CLUSTER_DNSLOOKUPFAMILY']._serialized_end=6470
  _globals['_CLUSTER_CLUSTERPROTOCOLSELECTION']._serialized_start=6472
  _globals['_CLUSTER_CLUSTERPROTOCOLSELECTION']._serialized_end=6556
  _globals['_LOADBALANCINGPOLICY']._serialized_start=6610
  _globals['_LOADBALANCINGPOLICY']._serialized_end=6804
  _globals['_LOADBALANCINGPOLICY_POLICY']._serialized_start=6693
  _globals['_LOADBALANCINGPOLICY_POLICY']._serialized_end=6804
  _globals['_UPSTREAMBINDCONFIG']._serialized_start=6806
  _globals['_UPSTREAMBINDCONFIG']._serialized_end=6878
  _globals['_UPSTREAMCONNECTIONOPTIONS']._serialized_start=6880
  _globals['_UPSTREAMCONNECTIONOPTIONS']._serialized_end=6963
