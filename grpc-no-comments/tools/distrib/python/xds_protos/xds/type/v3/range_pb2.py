
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x17xds/type/v3/range.proto\x12\x0bxds.type.v3\"(\n\nInt64Range\x12\r\n\x05start\x18\x01 \x01(\x03\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x03\"(\n\nInt32Range\x12\r\n\x05start\x18\x01 \x01(\x05\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x05\")\n\x0b\x44oubleRange\x12\r\n\x05start\x18\x01 \x01(\x01\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x01\x42J\n\x16\x63om.github.xds.type.v3B\nRangeProtoP\x01Z\"github.com/cncf/xds/go/xds/type/v3b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.type.v3.range_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.type.v3B\nRangeProtoP\001Z\"github.com/cncf/xds/go/xds/type/v3'
  _globals['_INT64RANGE']._serialized_start=40
  _globals['_INT64RANGE']._serialized_end=80
  _globals['_INT32RANGE']._serialized_start=82
  _globals['_INT32RANGE']._serialized_end=122
  _globals['_DOUBLERANGE']._serialized_start=124
  _globals['_DOUBLERANGE']._serialized_end=165
