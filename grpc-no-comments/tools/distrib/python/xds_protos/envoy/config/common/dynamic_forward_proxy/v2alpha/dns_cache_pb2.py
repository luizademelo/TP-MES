
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2 import cluster_pb2 as envoy_dot_api_dot_v2_dot_cluster__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nAenvoy/config/common/dynamic_forward_proxy/v2alpha/dns_cache.proto\x12\x31\x65nvoy.config.common.dynamic_forward_proxy.v2alpha\x1a\x1a\x65nvoy/api/v2/cluster.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xec\x02\n\x0e\x44nsCacheConfig\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12J\n\x11\x64ns_lookup_family\x18\x02 \x01(\x0e\x32%.envoy.api.v2.Cluster.DnsLookupFamilyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12\x41\n\x10\x64ns_refresh_rate\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\x0c\xfa\x42\t\xaa\x01\x06\x32\x04\x10\xc0\x84=\x12\x35\n\x08host_ttl\x18\x04 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x12\x38\n\tmax_hosts\x18\x05 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02 \x00\x12\x43\n\x18\x64ns_failure_refresh_rate\x18\x06 \x01(\x0b\x32!.envoy.api.v2.Cluster.RefreshRateB\xec\x01\n?io.envoyproxy.envoy.config.common.dynamic_forward_proxy.v2alphaB\rDnsCacheProtoP\x01ZXgithub.com/envoyproxy/go-control-plane/envoy/config/common/dynamic_forward_proxy/v2alpha\xf2\x98\xfe\x8f\x05\x32\x12\x30\x65nvoy.extensions.common.dynamic_forward_proxy.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.common.dynamic_forward_proxy.v2alpha.dns_cache_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.config.common.dynamic_forward_proxy.v2alphaB\rDnsCacheProtoP\001ZXgithub.com/envoyproxy/go-control-plane/envoy/config/common/dynamic_forward_proxy/v2alpha\362\230\376\217\0052\0220envoy.extensions.common.dynamic_forward_proxy.v3\272\200\310\321\006\002\020\001'
  _DNSCACHECONFIG.fields_by_name['name']._options = None
  _DNSCACHECONFIG.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _DNSCACHECONFIG.fields_by_name['dns_lookup_family']._options = None
  _DNSCACHECONFIG.fields_by_name['dns_lookup_family']._serialized_options = b'\372B\005\202\001\002\020\001'
  _DNSCACHECONFIG.fields_by_name['dns_refresh_rate']._options = None
  _DNSCACHECONFIG.fields_by_name['dns_refresh_rate']._serialized_options = b'\372B\t\252\001\0062\004\020\300\204='
  _DNSCACHECONFIG.fields_by_name['host_ttl']._options = None
  _DNSCACHECONFIG.fields_by_name['host_ttl']._serialized_options = b'\372B\005\252\001\002*\000'
  _DNSCACHECONFIG.fields_by_name['max_hosts']._options = None
  _DNSCACHECONFIG.fields_by_name['max_hosts']._serialized_options = b'\372B\004*\002 \000'
  _globals['_DNSCACHECONFIG']._serialized_start=301
  _globals['_DNSCACHECONFIG']._serialized_end=665
