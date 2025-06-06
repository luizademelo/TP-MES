
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import range_pb2 as envoy_dot_type_dot_v3_dot_range__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"envoy/type/matcher/v3/number.proto\x12\x15\x65nvoy.type.matcher.v3\x1a\x19\x65nvoy/type/v3/range.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x8c\x01\n\rDoubleMatcher\x12+\n\x05range\x18\x01 \x01(\x0b\x32\x1a.envoy.type.v3.DoubleRangeH\x00\x12\x0f\n\x05\x65xact\x18\x02 \x01(\x01H\x00:\'\x9a\xc5\x88\x1e\"\n envoy.type.matcher.DoubleMatcherB\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01\x42\x84\x01\n#io.envoyproxy.envoy.type.matcher.v3B\x0bNumberProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.number_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\013NumberProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _DOUBLEMATCHER.oneofs_by_name['match_pattern']._options = None
  _DOUBLEMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _DOUBLEMATCHER._options = None
  _DOUBLEMATCHER._serialized_options = b'\232\305\210\036\"\n envoy.type.matcher.DoubleMatcher'
  _globals['_DOUBLEMATCHER']._serialized_start=180
  _globals['_DOUBLEMATCHER']._serialized_end=320
