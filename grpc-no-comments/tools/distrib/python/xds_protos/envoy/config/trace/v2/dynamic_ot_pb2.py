
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/config/trace/v2/dynamic_ot.proto\x12\x15\x65nvoy.config.trace.v2\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"T\n\x0f\x44ynamicOtConfig\x12\x18\n\x07library\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\'\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x85\x01\n#io.envoyproxy.envoy.config.trace.v2B\x0e\x44ynamicOtProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.dynamic_ot_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\016DynamicOtProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _DYNAMICOTCONFIG.fields_by_name['library']._options = None
  _DYNAMICOTCONFIG.fields_by_name['library']._serialized_options = b'\372B\004r\002 \001'
  _globals['_DYNAMICOTCONFIG']._serialized_start=151
  _globals['_DYNAMICOTCONFIG']._serialized_end=235
