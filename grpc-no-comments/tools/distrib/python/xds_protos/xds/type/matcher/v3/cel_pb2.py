
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.type.v3 import cel_pb2 as xds_dot_type_dot_v3_dot_cel__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1dxds/type/matcher/v3/cel.proto\x12\x13xds.type.matcher.v3\x1a\x1fxds/annotations/v3/status.proto\x1a\x15xds/type/v3/cel.proto\x1a\x17validate/validate.proto\"[\n\nCelMatcher\x12\x38\n\nexpr_match\x18\x01 \x01(\x0b\x32\x1a.xds.type.v3.CelExpressionB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\tB`\n\x1e\x63om.github.xds.type.matcher.v3B\x08\x43\x65lProtoP\x01Z*github.com/cncf/xds/go/xds/type/matcher/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.type.matcher.v3.cel_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.github.xds.type.matcher.v3B\010CelProtoP\001Z*github.com/cncf/xds/go/xds/type/matcher/v3\322\306\244\341\006\002\010\001'
  _CELMATCHER.fields_by_name['expr_match']._options = None
  _CELMATCHER.fields_by_name['expr_match']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_CELMATCHER']._serialized_start=135
  _globals['_CELMATCHER']._serialized_end=226
