
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.common.dynamic_forward_proxy.v2alpha import dns_cache_pb2 as envoy_dot_config_dot_common_dot_dynamic__forward__proxy_dot_v2alpha_dot_dns__cache__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@envoy/config/cluster/dynamic_forward_proxy/v2alpha/cluster.proto\x12\x32\x65nvoy.config.cluster.dynamic_forward_proxy.v2alpha\x1a\x41\x65nvoy/config/common/dynamic_forward_proxy/v2alpha/dns_cache.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"v\n\rClusterConfig\x12\x65\n\x10\x64ns_cache_config\x18\x01 \x01(\x0b\x32\x41.envoy.config.common.dynamic_forward_proxy.v2alpha.DnsCacheConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\xef\x01\n@io.envoyproxy.envoy.config.cluster.dynamic_forward_proxy.v2alphaB\x0c\x43lusterProtoP\x01ZYgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/dynamic_forward_proxy/v2alpha\xf2\x98\xfe\x8f\x05\x34\x12\x32\x65nvoy.extensions.clusters.dynamic_forward_proxy.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.cluster.dynamic_forward_proxy.v2alpha.cluster_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.config.cluster.dynamic_forward_proxy.v2alphaB\014ClusterProtoP\001ZYgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/dynamic_forward_proxy/v2alpha\362\230\376\217\0054\0222envoy.extensions.clusters.dynamic_forward_proxy.v3\272\200\310\321\006\002\020\001'
  _CLUSTERCONFIG.fields_by_name['dns_cache_config']._options = None
  _CLUSTERCONFIG.fields_by_name['dns_cache_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_CLUSTERCONFIG']._serialized_start=275
  _globals['_CLUSTERCONFIG']._serialized_end=393
