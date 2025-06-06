
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher import regex_pb2 as envoy_dot_type_dot_matcher_dot_regex__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/type/matcher/string.proto\x12\x12\x65nvoy.type.matcher\x1a\x1e\x65nvoy/type/matcher/regex.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xe6\x01\n\rStringMatcher\x12\x0f\n\x05\x65xact\x18\x01 \x01(\tH\x00\x12\x19\n\x06prefix\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x12\x19\n\x06suffix\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x12!\n\x05regex\x18\x04 \x01(\tB\x10\x18\x01\xfa\x42\x05r\x03(\x80\x08\xb8\xee\xf2\xd2\x05\x01H\x00\x12@\n\nsafe_regex\x18\x05 \x01(\x0b\x32 .envoy.type.matcher.RegexMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12\x13\n\x0bignore_case\x18\x06 \x01(\x08\x42\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01\"R\n\x11ListStringMatcher\x12=\n\x08patterns\x18\x01 \x03(\x0b\x32!.envoy.type.matcher.StringMatcherB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x42t\n io.envoyproxy.envoy.type.matcherB\x0bStringProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.string_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\013StringProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _STRINGMATCHER.oneofs_by_name['match_pattern']._options = None
  _STRINGMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _STRINGMATCHER.fields_by_name['prefix']._options = None
  _STRINGMATCHER.fields_by_name['prefix']._serialized_options = b'\372B\004r\002\020\001'
  _STRINGMATCHER.fields_by_name['suffix']._options = None
  _STRINGMATCHER.fields_by_name['suffix']._serialized_options = b'\372B\004r\002\020\001'
  _STRINGMATCHER.fields_by_name['regex']._options = None
  _STRINGMATCHER.fields_by_name['regex']._serialized_options = b'\030\001\372B\005r\003(\200\010\270\356\362\322\005\001'
  _STRINGMATCHER.fields_by_name['safe_regex']._options = None
  _STRINGMATCHER.fields_by_name['safe_regex']._serialized_options = b'\372B\005\212\001\002\020\001'
  _LISTSTRINGMATCHER.fields_by_name['patterns']._options = None
  _LISTSTRINGMATCHER.fields_by_name['patterns']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_STRINGMATCHER']._serialized_start=181
  _globals['_STRINGMATCHER']._serialized_end=411
  _globals['_LISTSTRINGMATCHER']._serialized_start=413
  _globals['_LISTSTRINGMATCHER']._serialized_end=495
