
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x19\x65nvoy/type/v3/range.proto\x12\renvoy.type.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"F\n\nInt64Range\x12\r\n\x05start\x18\x01 \x01(\x03\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x03:\x1c\x9a\xc5\x88\x1e\x17\n\x15\x65nvoy.type.Int64Range\"F\n\nInt32Range\x12\r\n\x05start\x18\x01 \x01(\x05\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x05:\x1c\x9a\xc5\x88\x1e\x17\n\x15\x65nvoy.type.Int32Range\"H\n\x0b\x44oubleRange\x12\r\n\x05start\x18\x01 \x01(\x01\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x01:\x1d\x9a\xc5\x88\x1e\x18\n\x16\x65nvoy.type.DoubleRangeBp\n\x1bio.envoyproxy.envoy.type.v3B\nRangeProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.v3.range_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033io.envoyproxy.envoy.type.v3B\nRangeProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\272\200\310\321\006\002\020\002'
  _INT64RANGE._options = None
  _INT64RANGE._serialized_options = b'\232\305\210\036\027\n\025envoy.type.Int64Range'
  _INT32RANGE._options = None
  _INT32RANGE._serialized_options = b'\232\305\210\036\027\n\025envoy.type.Int32Range'
  _DOUBLERANGE._options = None
  _DOUBLERANGE._serialized_options = b'\232\305\210\036\030\n\026envoy.type.DoubleRange'
  _globals['_INT64RANGE']._serialized_start=110
  _globals['_INT64RANGE']._serialized_end=180
  _globals['_INT32RANGE']._serialized_start=182
  _globals['_INT32RANGE']._serialized_end=252
  _globals['_DOUBLERANGE']._serialized_start=254
  _globals['_DOUBLERANGE']._serialized_end=326
