
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/config/trace/v3/dynamic_ot.proto\x12\x15\x65nvoy.config.trace.v3\x1a\x1cgoogle/protobuf/struct.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xa6\x01\n\x0f\x44ynamicOtConfig\x12)\n\x07library\x18\x01 \x01(\tB\x18\x18\x01\xfa\x42\x04r\x02\x10\x01\x92\xc7\x86\xd8\x04\x03\x33.0\xb8\xee\xf2\xd2\x05\x01\x12:\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x11\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\xb8\xee\xf2\xd2\x05\x01:,\x9a\xc5\x88\x1e\'\n%envoy.config.trace.v2.DynamicOtConfigB\xb8\x01\n#io.envoyproxy.envoy.config.trace.v3B\x0e\x44ynamicOtProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3\xf2\x98\xfe\x8f\x05-\x12+envoy.extensions.tracers.dynamic_ot.v4alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v3.dynamic_ot_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v3B\016DynamicOtProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3\362\230\376\217\005-\022+envoy.extensions.tracers.dynamic_ot.v4alpha\272\200\310\321\006\002\020\002'
  _DYNAMICOTCONFIG.fields_by_name['library']._options = None
  _DYNAMICOTCONFIG.fields_by_name['library']._serialized_options = b'\030\001\372B\004r\002\020\001\222\307\206\330\004\0033.0\270\356\362\322\005\001'
  _DYNAMICOTCONFIG.fields_by_name['config']._options = None
  _DYNAMICOTCONFIG.fields_by_name['config']._serialized_options = b'\030\001\222\307\206\330\004\0033.0\270\356\362\322\005\001'
  _DYNAMICOTCONFIG._options = None
  _DYNAMICOTCONFIG._serialized_options = b'\232\305\210\036\'\n%envoy.config.trace.v2.DynamicOtConfig'
  _globals['_DYNAMICOTCONFIG']._serialized_start=256
  _globals['_DYNAMICOTCONFIG']._serialized_end=422
