
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.service.tap.v2alpha import common_pb2 as envoy_dot_service_dot_tap_dot_v2alpha_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1d\x65nvoy/admin/v2alpha/tap.proto\x12\x13\x65nvoy.admin.v2alpha\x1a&envoy/service/tap/v2alpha/common.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"l\n\nTapRequest\x12\x1a\n\tconfig_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x42\n\ntap_config\x18\x02 \x01(\x0b\x32$.envoy.service.tap.v2alpha.TapConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42s\n!io.envoyproxy.envoy.admin.v2alphaB\x08TapProtoP\x01Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v2alpha.tap_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.envoyproxy.envoy.admin.v2alphaB\010TapProtoP\001Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\272\200\310\321\006\002\020\001'
  _TAPREQUEST.fields_by_name['config_id']._options = None
  _TAPREQUEST.fields_by_name['config_id']._serialized_options = b'\372B\004r\002 \001'
  _TAPREQUEST.fields_by_name['tap_config']._options = None
  _TAPREQUEST.fields_by_name['tap_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_TAPREQUEST']._serialized_start=150
  _globals['_TAPREQUEST']._serialized_end=258
