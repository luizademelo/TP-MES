
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher import string_pb2 as envoy_dot_type_dot_matcher_dot_string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1d\x65nvoy/type/matcher/path.proto\x12\x12\x65nvoy.type.matcher\x1a\x1f\x65nvoy/type/matcher/string.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"W\n\x0bPathMatcher\x12;\n\x04path\x18\x01 \x01(\x0b\x32!.envoy.type.matcher.StringMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x42\x0b\n\x04rule\x12\x03\xf8\x42\x01\x42r\n io.envoyproxy.envoy.type.matcherB\tPathProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.path_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\tPathProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _PATHMATCHER.oneofs_by_name['rule']._options = None
  _PATHMATCHER.oneofs_by_name['rule']._serialized_options = b'\370B\001'
  _PATHMATCHER.fields_by_name['path']._options = None
  _PATHMATCHER.fields_by_name['path']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_PATHMATCHER']._serialized_start=142
  _globals['_PATHMATCHER']._serialized_end=229
