
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*opentelemetry/proto/common/v1/common.proto\x12\x1dopentelemetry.proto.common.v1\"\x8c\x02\n\x08\x41nyValue\x12\x16\n\x0cstring_value\x18\x01 \x01(\tH\x00\x12\x14\n\nbool_value\x18\x02 \x01(\x08H\x00\x12\x13\n\tint_value\x18\x03 \x01(\x03H\x00\x12\x16\n\x0c\x64ouble_value\x18\x04 \x01(\x01H\x00\x12@\n\x0b\x61rray_value\x18\x05 \x01(\x0b\x32).opentelemetry.proto.common.v1.ArrayValueH\x00\x12\x43\n\x0ckvlist_value\x18\x06 \x01(\x0b\x32+.opentelemetry.proto.common.v1.KeyValueListH\x00\x12\x15\n\x0b\x62ytes_value\x18\x07 \x01(\x0cH\x00\x42\x07\n\x05value\"E\n\nArrayValue\x12\x37\n\x06values\x18\x01 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.AnyValue\"G\n\x0cKeyValueList\x12\x37\n\x06values\x18\x01 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\"O\n\x08KeyValue\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x36\n\x05value\x18\x02 \x01(\x0b\x32\'.opentelemetry.proto.common.v1.AnyValue\"0\n\x0eStringKeyValue\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x18\x01\"7\n\x16InstrumentationLibrary\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0f\n\x07version\x18\x02 \x01(\tBq\n io.opentelemetry.proto.common.v1B\x0b\x43ommonProtoP\x01Z>github.com/open-telemetry/opentelemetry-proto/gen/go/common/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.common.v1.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.opentelemetry.proto.common.v1B\013CommonProtoP\001Z>github.com/open-telemetry/opentelemetry-proto/gen/go/common/v1'
  _STRINGKEYVALUE._options = None
  _STRINGKEYVALUE._serialized_options = b'\030\001'
  _globals['_ANYVALUE']._serialized_start=78
  _globals['_ANYVALUE']._serialized_end=346
  _globals['_ARRAYVALUE']._serialized_start=348
  _globals['_ARRAYVALUE']._serialized_end=417
  _globals['_KEYVALUELIST']._serialized_start=419
  _globals['_KEYVALUELIST']._serialized_end=490
  _globals['_KEYVALUE']._serialized_start=492
  _globals['_KEYVALUE']._serialized_end=571
  _globals['_STRINGKEYVALUE']._serialized_start=573
  _globals['_STRINGKEYVALUE']._serialized_end=621
  _globals['_INSTRUMENTATIONLIBRARY']._serialized_start=623
  _globals['_INSTRUMENTATIONLIBRARY']._serialized_end=678
