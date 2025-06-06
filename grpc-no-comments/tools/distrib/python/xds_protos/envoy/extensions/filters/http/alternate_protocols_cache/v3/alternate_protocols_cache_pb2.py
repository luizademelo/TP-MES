
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import protocol_pb2 as envoy_dot_config_dot_core_dot_v3_dot_protocol__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nZenvoy/extensions/filters/http/alternate_protocols_cache/v3/alternate_protocols_cache.proto\x12:envoy.extensions.filters.http.alternate_protocols_cache.v3\x1a#envoy/config/core/v3/protocol.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\"|\n\x0c\x46ilterConfig\x12l\n!alternate_protocols_cache_options\x18\x01 \x01(\x0b\x32\x34.envoy.config.core.v3.AlternateProtocolsCacheOptionsB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0B\xf1\x01\nHio.envoyproxy.envoy.extensions.filters.http.alternate_protocols_cache.v3B\x1c\x41lternateProtocolsCacheProtoP\x01Z}github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/alternate_protocols_cache/v3;alternate_protocols_cachev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.alternate_protocols_cache.v3.alternate_protocols_cache_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nHio.envoyproxy.envoy.extensions.filters.http.alternate_protocols_cache.v3B\034AlternateProtocolsCacheProtoP\001Z}github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/alternate_protocols_cache/v3;alternate_protocols_cachev3\272\200\310\321\006\002\020\002'
  _FILTERCONFIG.fields_by_name['alternate_protocols_cache_options']._options = None
  _FILTERCONFIG.fields_by_name['alternate_protocols_cache_options']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _globals['_FILTERCONFIG']._serialized_start=259
  _globals['_FILTERCONFIG']._serialized_end=383
