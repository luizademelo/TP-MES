
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher import value_pb2 as envoy_dot_type_dot_matcher_dot_value__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/type/matcher/struct.proto\x12\x12\x65nvoy.type.matcher\x1a\x1e\x65nvoy/type/matcher/value.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc8\x01\n\rStructMatcher\x12\x45\n\x04path\x18\x02 \x03(\x0b\x32-.envoy.type.matcher.StructMatcher.PathSegmentB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x39\n\x05value\x18\x03 \x01(\x0b\x32 .envoy.type.matcher.ValueMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x1a\x35\n\x0bPathSegment\x12\x16\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x42\x0e\n\x07segment\x12\x03\xf8\x42\x01\x42t\n io.envoyproxy.envoy.type.matcherB\x0bStructProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.struct_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\013StructProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _STRUCTMATCHER_PATHSEGMENT.oneofs_by_name['segment']._options = None
  _STRUCTMATCHER_PATHSEGMENT.oneofs_by_name['segment']._serialized_options = b'\370B\001'
  _STRUCTMATCHER_PATHSEGMENT.fields_by_name['key']._options = None
  _STRUCTMATCHER_PATHSEGMENT.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _STRUCTMATCHER.fields_by_name['path']._options = None
  _STRUCTMATCHER.fields_by_name['path']._serialized_options = b'\372B\005\222\001\002\010\001'
  _STRUCTMATCHER.fields_by_name['value']._options = None
  _STRUCTMATCHER.fields_by_name['value']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_STRUCTMATCHER']._serialized_start=144
  _globals['_STRUCTMATCHER']._serialized_end=344
  _globals['_STRUCTMATCHER_PATHSEGMENT']._serialized_start=291
  _globals['_STRUCTMATCHER_PATHSEGMENT']._serialized_end=344
