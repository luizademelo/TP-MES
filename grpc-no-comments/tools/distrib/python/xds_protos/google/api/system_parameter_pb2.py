
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!google/api/system_parameter.proto\x12\ngoogle.api\"B\n\x10SystemParameters\x12.\n\x05rules\x18\x01 \x03(\x0b\x32\x1f.google.api.SystemParameterRule\"X\n\x13SystemParameterRule\x12\x10\n\x08selector\x18\x01 \x01(\t\x12/\n\nparameters\x18\x02 \x03(\x0b\x32\x1b.google.api.SystemParameter\"Q\n\x0fSystemParameter\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0bhttp_header\x18\x02 \x01(\t\x12\x1b\n\x13url_query_parameter\x18\x03 \x01(\tBv\n\x0e\x63om.google.apiB\x14SystemParameterProtoP\x01ZEgoogle.golang.org/genproto/googleapis/api/serviceconfig;serviceconfig\xa2\x02\x04GAPIb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.system_parameter_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\016com.google.apiB\024SystemParameterProtoP\001ZEgoogle.golang.org/genproto/googleapis/api/serviceconfig;serviceconfig\242\002\004GAPI'
  _globals['_SYSTEMPARAMETERS']._serialized_start=49
  _globals['_SYSTEMPARAMETERS']._serialized_end=115
  _globals['_SYSTEMPARAMETERRULE']._serialized_start=117
  _globals['_SYSTEMPARAMETERRULE']._serialized_end=205
  _globals['_SYSTEMPARAMETER']._serialized_start=207
  _globals['_SYSTEMPARAMETER']._serialized_end=288
