
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nKenvoy/extensions/filters/network/connection_limit/v3/connection_limit.proto\x12\x34\x65nvoy.extensions.filters.network.connection_limit.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xdc\x01\n\x0f\x43onnectionLimit\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12>\n\x0fmax_connections\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\x07\xfa\x42\x04\x32\x02(\x01\x12(\n\x05\x64\x65lay\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x41\n\x0fruntime_enabled\x18\x04 \x01(\x0b\x32(.envoy.config.core.v3.RuntimeFeatureFlagB\xd4\x01\nBio.envoyproxy.envoy.extensions.filters.network.connection_limit.v3B\x14\x43onnectionLimitProtoP\x01Zngithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/connection_limit/v3;connection_limitv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.connection_limit.v3.connection_limit_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nBio.envoyproxy.envoy.extensions.filters.network.connection_limit.v3B\024ConnectionLimitProtoP\001Zngithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/connection_limit/v3;connection_limitv3\272\200\310\321\006\002\020\002'
  _CONNECTIONLIMIT.fields_by_name['stat_prefix']._options = None
  _CONNECTIONLIMIT.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _CONNECTIONLIMIT.fields_by_name['max_connections']._options = None
  _CONNECTIONLIMIT.fields_by_name['max_connections']._serialized_options = b'\372B\0042\002(\001'
  _globals['_CONNECTIONLIMIT']._serialized_start=287
  _globals['_CONNECTIONLIMIT']._serialized_end=507
