
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
from envoy.data.tap.v2alpha import wrapper_pb2 as envoy_dot_data_dot_tap_dot_v2alpha_dot_wrapper__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/service/tap/v2alpha/tap.proto\x12\x19\x65nvoy.service.tap.v2alpha\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a$envoy/data/tap/v2alpha/wrapper.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xf6\x01\n\x11StreamTapsRequest\x12K\n\nidentifier\x18\x01 \x01(\x0b\x32\x37.envoy.service.tap.v2alpha.StreamTapsRequest.Identifier\x12\x10\n\x08trace_id\x18\x02 \x01(\x04\x12\x33\n\x05trace\x18\x03 \x01(\x0b\x32$.envoy.data.tap.v2alpha.TraceWrapper\x1aM\n\nIdentifier\x12/\n\x04node\x18\x01 \x01(\x0b\x32\x17.envoy.api.v2.core.NodeB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0e\n\x06tap_id\x18\x02 \x01(\t\"\x14\n\x12StreamTapsResponse2\x7f\n\x0eTapSinkService\x12m\n\nStreamTaps\x12,.envoy.service.tap.v2alpha.StreamTapsRequest\x1a-.envoy.service.tap.v2alpha.StreamTapsResponse\"\x00(\x01\x42\x7f\n\'io.envoyproxy.envoy.service.tap.v2alphaB\x08TapProtoP\x01Z@github.com/envoyproxy/go-control-plane/envoy/service/tap/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.tap.v2alpha.tap_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\'io.envoyproxy.envoy.service.tap.v2alphaB\010TapProtoP\001Z@github.com/envoyproxy/go-control-plane/envoy/service/tap/v2alpha\272\200\310\321\006\002\020\001'
  _STREAMTAPSREQUEST_IDENTIFIER.fields_by_name['node']._options = None
  _STREAMTAPSREQUEST_IDENTIFIER.fields_by_name['node']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_STREAMTAPSREQUEST']._serialized_start=191
  _globals['_STREAMTAPSREQUEST']._serialized_end=437
  _globals['_STREAMTAPSREQUEST_IDENTIFIER']._serialized_start=360
  _globals['_STREAMTAPSREQUEST_IDENTIFIER']._serialized_end=437
  _globals['_STREAMTAPSRESPONSE']._serialized_start=439
  _globals['_STREAMTAPSRESPONSE']._serialized_end=459
  _globals['_TAPSINKSERVICE']._serialized_start=461
  _globals['_TAPSINKSERVICE']._serialized_end=588
