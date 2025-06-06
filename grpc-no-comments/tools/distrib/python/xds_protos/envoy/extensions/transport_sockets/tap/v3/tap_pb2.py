
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.extensions.common.tap.v3 import common_pb2 as envoy_dot_extensions_dot_common_dot_tap_dot_v3_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3envoy/extensions/transport_sockets/tap/v3/tap.proto\x12)envoy.extensions.transport_sockets.tap.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a+envoy/extensions/common/tap/v3/common.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xde\x01\n\x03Tap\x12V\n\rcommon_config\x18\x01 \x01(\x0b\x32\x35.envoy.extensions.common.tap.v3.CommonExtensionConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12I\n\x10transport_socket\x18\x02 \x01(\x0b\x32%.envoy.config.core.v3.TransportSocketB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01:4\x9a\xc5\x88\x1e/\n-envoy.config.transport_socket.tap.v2alpha.TapB\xa5\x01\n7io.envoyproxy.envoy.extensions.transport_sockets.tap.v3B\x08TapProtoP\x01ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tap/v3;tapv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.tap.v3.tap_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.transport_sockets.tap.v3B\010TapProtoP\001ZVgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/tap/v3;tapv3\272\200\310\321\006\002\020\002'
  _TAP.fields_by_name['common_config']._options = None
  _TAP.fields_by_name['common_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _TAP.fields_by_name['transport_socket']._options = None
  _TAP.fields_by_name['transport_socket']._serialized_options = b'\372B\005\212\001\002\020\001'
  _TAP._options = None
  _TAP._serialized_options = b'\232\305\210\036/\n-envoy.config.transport_socket.tap.v2alpha.Tap'
  _globals['_TAP']._serialized_start=268
  _globals['_TAP']._serialized_end=490
