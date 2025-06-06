
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/type/matcher/regex.proto\x12\x12\x65nvoy.type.matcher\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xcf\x01\n\x0cRegexMatcher\x12J\n\ngoogle_re2\x18\x01 \x01(\x0b\x32*.envoy.type.matcher.RegexMatcher.GoogleRE2B\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12\x16\n\x05regex\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x1aG\n\tGoogleRE2\x12:\n\x10max_program_size\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x02\x18\x01\x42\x12\n\x0b\x65ngine_type\x12\x03\xf8\x42\x01\"b\n\x17RegexMatchAndSubstitute\x12\x31\n\x07pattern\x18\x01 \x01(\x0b\x32 .envoy.type.matcher.RegexMatcher\x12\x14\n\x0csubstitution\x18\x02 \x01(\tBs\n io.envoyproxy.envoy.type.matcherB\nRegexProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.regex_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.matcherB\nRegexProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/type/matcher\272\200\310\321\006\002\020\001'
  _REGEXMATCHER_GOOGLERE2.fields_by_name['max_program_size']._options = None
  _REGEXMATCHER_GOOGLERE2.fields_by_name['max_program_size']._serialized_options = b'\030\001'
  _REGEXMATCHER.oneofs_by_name['engine_type']._options = None
  _REGEXMATCHER.oneofs_by_name['engine_type']._serialized_options = b'\370B\001'
  _REGEXMATCHER.fields_by_name['google_re2']._options = None
  _REGEXMATCHER.fields_by_name['google_re2']._serialized_options = b'\372B\005\212\001\002\020\001'
  _REGEXMATCHER.fields_by_name['regex']._options = None
  _REGEXMATCHER.fields_by_name['regex']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_REGEXMATCHER']._serialized_start=143
  _globals['_REGEXMATCHER']._serialized_end=350
  _globals['_REGEXMATCHER_GOOGLERE2']._serialized_start=259
  _globals['_REGEXMATCHER_GOOGLERE2']._serialized_end=330
  _globals['_REGEXMATCHANDSUBSTITUTE']._serialized_start=352
  _globals['_REGEXMATCHANDSUBSTITUTE']._serialized_end=450
