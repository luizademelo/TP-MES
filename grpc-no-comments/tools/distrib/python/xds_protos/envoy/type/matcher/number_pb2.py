
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type import range_pb2 as envoy_dot_type_dot_range__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/type/matcher/number.proto\x12\x12\x65nvoy.type.matcher\x1a\x16\x65nvoy/type/range.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"`\n\rDoubleMatcher\x12(\n\x05range\x18\x01 \x01(\x0b\x32\x17.envoy.type.DoubleRangeH\x00\x12\x0f\n\x05\x65xact\x18\x02 \x01(\x01H\x00\x42\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01\x42t\n io.envoyproxy.envoy.type.matcherB\x0bNumberProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.number_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\013NumberProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _DOUBLEMATCHER.oneofs_by_name['match_pattern']._options = None
  _DOUBLEMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _globals['_DOUBLEMATCHER']._serialized_start=135
  _globals['_DOUBLEMATCHER']._serialized_end=231
