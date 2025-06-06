
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher import number_pb2 as envoy_dot_type_dot_matcher_dot_number__pb2
from envoy.type.matcher import string_pb2 as envoy_dot_type_dot_matcher_dot_string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/type/matcher/value.proto\x12\x12\x65nvoy.type.matcher\x1a\x1f\x65nvoy/type/matcher/number.proto\x1a\x1f\x65nvoy/type/matcher/string.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xcf\x02\n\x0cValueMatcher\x12@\n\nnull_match\x18\x01 \x01(\x0b\x32*.envoy.type.matcher.ValueMatcher.NullMatchH\x00\x12\x39\n\x0c\x64ouble_match\x18\x02 \x01(\x0b\x32!.envoy.type.matcher.DoubleMatcherH\x00\x12\x39\n\x0cstring_match\x18\x03 \x01(\x0b\x32!.envoy.type.matcher.StringMatcherH\x00\x12\x14\n\nbool_match\x18\x04 \x01(\x08H\x00\x12\x17\n\rpresent_match\x18\x05 \x01(\x08H\x00\x12\x35\n\nlist_match\x18\x06 \x01(\x0b\x32\x1f.envoy.type.matcher.ListMatcherH\x00\x1a\x0b\n\tNullMatchB\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01\"W\n\x0bListMatcher\x12\x32\n\x06one_of\x18\x01 \x01(\x0b\x32 .envoy.type.matcher.ValueMatcherH\x00\x42\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01\x42s\n io.envoyproxy.envoy.type.matcherB\nValueProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.value_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\nValueProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _VALUEMATCHER.oneofs_by_name['match_pattern']._options = None
  _VALUEMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _LISTMATCHER.oneofs_by_name['match_pattern']._options = None
  _LISTMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _globals['_VALUEMATCHER']._serialized_start=177
  _globals['_VALUEMATCHER']._serialized_end=512
  _globals['_VALUEMATCHER_NULLMATCH']._serialized_start=479
  _globals['_VALUEMATCHER_NULLMATCH']._serialized_end=490
  _globals['_LISTMATCHER']._serialized_start=514
  _globals['_LISTMATCHER']._serialized_end=601
