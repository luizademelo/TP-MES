
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$google/api/expr/v1beta1/source.proto\x12\x17google.api.expr.v1beta1\"\xad\x01\n\nSourceInfo\x12\x10\n\x08location\x18\x02 \x01(\t\x12\x14\n\x0cline_offsets\x18\x03 \x03(\x05\x12\x45\n\tpositions\x18\x04 \x03(\x0b\x32\x32.google.api.expr.v1beta1.SourceInfo.PositionsEntry\x1a\x30\n\x0ePositionsEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12\r\n\x05value\x18\x02 \x01(\x05:\x02\x38\x01\"P\n\x0eSourcePosition\x12\x10\n\x08location\x18\x01 \x01(\t\x12\x0e\n\x06offset\x18\x02 \x01(\x05\x12\x0c\n\x04line\x18\x03 \x01(\x05\x12\x0e\n\x06\x63olumn\x18\x04 \x01(\x05\x42l\n\x1b\x63om.google.api.expr.v1beta1B\x0bSourceProtoP\x01Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1beta1.source_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033com.google.api.expr.v1beta1B\013SourceProtoP\001Z;google.golang.org/genproto/googleapis/api/expr/v1beta1;expr\370\001\001'
  _SOURCEINFO_POSITIONSENTRY._options = None
  _SOURCEINFO_POSITIONSENTRY._serialized_options = b'8\001'
  _globals['_SOURCEINFO']._serialized_start=66
  _globals['_SOURCEINFO']._serialized_end=239
  _globals['_SOURCEINFO_POSITIONSENTRY']._serialized_start=191
  _globals['_SOURCEINFO_POSITIONSENTRY']._serialized_end=239
  _globals['_SOURCEPOSITION']._serialized_start=241
  _globals['_SOURCEPOSITION']._serialized_end=321
