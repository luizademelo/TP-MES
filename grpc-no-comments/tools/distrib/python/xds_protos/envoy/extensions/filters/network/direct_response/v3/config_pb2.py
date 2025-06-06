
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@envoy/extensions/filters/network/direct_response/v3/config.proto\x12\x33\x65nvoy.extensions.filters.network.direct_response.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"z\n\x06\x43onfig\x12\x32\n\x08response\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSource:<\x9a\xc5\x88\x1e\x37\n5envoy.config.filter.network.direct_response.v2.ConfigB\xc8\x01\nAio.envoyproxy.envoy.extensions.filters.network.direct_response.v3B\x0b\x43onfigProtoP\x01Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/direct_response/v3;direct_responsev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.direct_response.v3.config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nAio.envoyproxy.envoy.extensions.filters.network.direct_response.v3B\013ConfigProtoP\001Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/direct_response/v3;direct_responsev3\272\200\310\321\006\002\020\002'
  _CONFIG._options = None
  _CONFIG._serialized_options = b'\232\305\210\0367\n5envoy.config.filter.network.direct_response.v2.Config'
  _globals['_CONFIG']._serialized_start=220
  _globals['_CONFIG']._serialized_end=342
