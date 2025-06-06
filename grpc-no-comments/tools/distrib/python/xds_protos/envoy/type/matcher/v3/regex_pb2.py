
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/type/matcher/v3/regex.proto\x12\x15\x65nvoy.type.matcher.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xb4\x02\n\x0cRegexMatcher\x12P\n\ngoogle_re2\x18\x01 \x01(\x0b\x32-.envoy.type.matcher.v3.RegexMatcher.GoogleRE2B\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\x16\n\x05regex\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x1a\x82\x01\n\tGoogleRE2\x12\x43\n\x10max_program_size\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0:0\x9a\xc5\x88\x1e+\n)envoy.type.matcher.RegexMatcher.GoogleRE2:&\x9a\xc5\x88\x1e!\n\x1f\x65nvoy.type.matcher.RegexMatcherB\r\n\x0b\x65ngine_type\"\xaf\x01\n\x17RegexMatchAndSubstitute\x12>\n\x07pattern\x18\x01 \x01(\x0b\x32#.envoy.type.matcher.v3.RegexMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12!\n\x0csubstitution\x18\x02 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00:1\x9a\xc5\x88\x1e,\n*envoy.type.matcher.RegexMatchAndSubstituteB\x83\x01\n#io.envoyproxy.envoy.type.matcher.v3B\nRegexProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.regex_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\nRegexProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _REGEXMATCHER_GOOGLERE2.fields_by_name['max_program_size']._options = None
  _REGEXMATCHER_GOOGLERE2.fields_by_name['max_program_size']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _REGEXMATCHER_GOOGLERE2._options = None
  _REGEXMATCHER_GOOGLERE2._serialized_options = b'\232\305\210\036+\n)envoy.type.matcher.RegexMatcher.GoogleRE2'
  _REGEXMATCHER.fields_by_name['google_re2']._options = None
  _REGEXMATCHER.fields_by_name['google_re2']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _REGEXMATCHER.fields_by_name['regex']._options = None
  _REGEXMATCHER.fields_by_name['regex']._serialized_options = b'\372B\004r\002\020\001'
  _REGEXMATCHER._options = None
  _REGEXMATCHER._serialized_options = b'\232\305\210\036!\n\037envoy.type.matcher.RegexMatcher'
  _REGEXMATCHANDSUBSTITUTE.fields_by_name['pattern']._options = None
  _REGEXMATCHANDSUBSTITUTE.fields_by_name['pattern']._serialized_options = b'\372B\005\212\001\002\020\001'
  _REGEXMATCHANDSUBSTITUTE.fields_by_name['substitution']._options = None
  _REGEXMATCHANDSUBSTITUTE.fields_by_name['substitution']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _REGEXMATCHANDSUBSTITUTE._options = None
  _REGEXMATCHANDSUBSTITUTE._serialized_options = b'\232\305\210\036,\n*envoy.type.matcher.RegexMatchAndSubstitute'
  _globals['_REGEXMATCHER']._serialized_start=221
  _globals['_REGEXMATCHER']._serialized_end=529
  _globals['_REGEXMATCHER_GOOGLERE2']._serialized_start=344
  _globals['_REGEXMATCHER_GOOGLERE2']._serialized_end=474
  _globals['_REGEXMATCHANDSUBSTITUTE']._serialized_start=532
  _globals['_REGEXMATCHANDSUBSTITUTE']._serialized_end=707
