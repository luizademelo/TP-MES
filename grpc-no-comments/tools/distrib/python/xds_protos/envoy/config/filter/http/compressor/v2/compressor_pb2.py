
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7envoy/config/filter/http/compressor/v2/compressor.proto\x12&envoy.config.filter.http.compressor.v2\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"\xdf\x01\n\nCompressor\x12\x34\n\x0e\x63ontent_length\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12\x14\n\x0c\x63ontent_type\x18\x02 \x03(\t\x12\x1e\n\x16\x64isable_on_etag_header\x18\x03 \x01(\x08\x12%\n\x1dremove_accept_encoding_header\x18\x04 \x01(\x08\x12>\n\x0fruntime_enabled\x18\x05 \x01(\x0b\x32%.envoy.api.v2.core.RuntimeFeatureFlagB\xe0\x01\n4io.envoyproxy.envoy.config.filter.http.compressor.v2B\x0f\x43ompressorProtoP\x01ZZgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/compressor/v2;compressorv2\xf2\x98\xfe\x8f\x05-\x12+envoy.extensions.filters.http.compressor.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.compressor.v2.compressor_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n4io.envoyproxy.envoy.config.filter.http.compressor.v2B\017CompressorProtoP\001ZZgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/compressor/v2;compressorv2\362\230\376\217\005-\022+envoy.extensions.filters.http.compressor.v3\272\200\310\321\006\002\020\001'
  _globals['_COMPRESSOR']._serialized_start=225
  _globals['_COMPRESSOR']._serialized_end=448
