
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import config_source_pb2 as envoy_dot_config_dot_core_dot_v3_dot_config__source__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/config/cluster/v3/filter.proto\x12\x17\x65nvoy.config.cluster.v3\x1a(envoy/config/core/v3/config_source.proto\x1a\x19google/protobuf/any.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xb6\x01\n\x06\x46ilter\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12*\n\x0ctyped_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x45\n\x10\x63onfig_discovery\x18\x03 \x01(\x0b\x32+.envoy.config.core.v3.ExtensionConfigSource:\"\x9a\xc5\x88\x1e\x1d\n\x1b\x65nvoy.api.v2.cluster.FilterB\x88\x01\n%io.envoyproxy.envoy.config.cluster.v3B\x0b\x46ilterProtoP\x01ZHgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/v3;clusterv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.cluster.v3.filter_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.config.cluster.v3B\013FilterProtoP\001ZHgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/v3;clusterv3\272\200\310\321\006\002\020\002'
  _FILTER.fields_by_name['name']._options = None
  _FILTER.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _FILTER._options = None
  _FILTER._serialized_options = b'\232\305\210\036\035\n\033envoy.api.v2.cluster.Filter'
  _globals['_FILTER']._serialized_start=226
  _globals['_FILTER']._serialized_end=408
