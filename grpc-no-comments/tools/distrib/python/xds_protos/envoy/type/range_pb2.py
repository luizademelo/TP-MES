
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x16\x65nvoy/type/range.proto\x12\nenvoy.type\x1a\x1dudpa/annotations/status.proto\"(\n\nInt64Range\x12\r\n\x05start\x18\x01 \x01(\x03\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x03\"(\n\nInt32Range\x12\r\n\x05start\x18\x01 \x01(\x05\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x05\")\n\x0b\x44oubleRange\x12\r\n\x05start\x18\x01 \x01(\x01\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x01\x42\x63\n\x18io.envoyproxy.envoy.typeB\nRangeProtoP\x01Z1github.com/envoyproxy/go-control-plane/envoy/type\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.range_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\030io.envoyproxy.envoy.typeB\nRangeProtoP\001Z1github.com/envoyproxy/go-control-plane/envoy/type\272\200\310\321\006\002\020\001'
  _globals['_INT64RANGE']._serialized_start=69
  _globals['_INT64RANGE']._serialized_end=109
  _globals['_INT32RANGE']._serialized_start=111
  _globals['_INT32RANGE']._serialized_end=151
  _globals['_DOUBLERANGE']._serialized_start=153
  _globals['_DOUBLERANGE']._serialized_end=194
