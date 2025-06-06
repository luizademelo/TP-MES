
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import address_pb2 as envoy_dot_api_dot_v2_dot_core_dot_address__pb2
from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/config/trace/v2alpha/xray.proto\x12\x1a\x65nvoy.config.trace.v2alpha\x1a\x1f\x65nvoy/api/v2/core/address.proto\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa5\x01\n\nXRayConfig\x12\x39\n\x0f\x64\x61\x65mon_endpoint\x18\x01 \x01(\x0b\x32 .envoy.api.v2.core.SocketAddress\x12\x1d\n\x0csegment_name\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12=\n\x16sampling_rule_manifest\x18\x03 \x01(\x0b\x32\x1d.envoy.api.v2.core.DataSourceB\x82\x01\n(io.envoyproxy.envoy.config.trace.v2alphaB\tXrayProtoP\x01ZAgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2alpha.xray_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(io.envoyproxy.envoy.config.trace.v2alphaB\tXrayProtoP\001ZAgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2alpha\272\200\310\321\006\002\020\001'
  _XRAYCONFIG.fields_by_name['segment_name']._options = None
  _XRAYCONFIG.fields_by_name['segment_name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_XRAYCONFIG']._serialized_start=189
  _globals['_XRAYCONFIG']._serialized_end=354
