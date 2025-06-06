
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n envoy/type/matcher/v3/path.proto\x12\x15\x65nvoy.type.matcher.v3\x1a\"envoy/type/matcher/v3/string.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x81\x01\n\x0bPathMatcher\x12>\n\x04path\x18\x01 \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.type.matcher.PathMatcherB\x0b\n\x04rule\x12\x03\xf8\x42\x01\x42\x82\x01\n#io.envoyproxy.envoy.type.matcher.v3B\tPathProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.path_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\tPathProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _PATHMATCHER.oneofs_by_name['rule']._options = None
  _PATHMATCHER.oneofs_by_name['rule']._serialized_options = b'\370B\001'
  _PATHMATCHER.fields_by_name['path']._options = None
  _PATHMATCHER.fields_by_name['path']._serialized_options = b'\372B\005\212\001\002\020\001'
  _PATHMATCHER._options = None
  _PATHMATCHER._serialized_options = b'\232\305\210\036 \n\036envoy.type.matcher.PathMatcher'
  _globals['_PATHMATCHER']._serialized_start=187
  _globals['_PATHMATCHER']._serialized_end=316
