
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import regex_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_regex__pb2
from xds.core.v3 import extension_pb2 as xds_dot_core_dot_v3_dot_extension__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"envoy/type/matcher/v3/string.proto\x12\x15\x65nvoy.type.matcher.v3\x1a!envoy/type/matcher/v3/regex.proto\x1a\x1bxds/core/v3/extension.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xce\x02\n\rStringMatcher\x12\x0f\n\x05\x65xact\x18\x01 \x01(\tH\x00\x12\x19\n\x06prefix\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x12\x19\n\x06suffix\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x12\x43\n\nsafe_regex\x18\x05 \x01(\x0b\x32#.envoy.type.matcher.v3.RegexMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01H\x00\x12\x1b\n\x08\x63ontains\x18\x07 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00\x12\x33\n\x06\x63ustom\x18\x08 \x01(\x0b\x32!.xds.core.v3.TypedExtensionConfigH\x00\x12\x13\n\x0bignore_case\x18\x06 \x01(\x08:\'\x9a\xc5\x88\x1e\"\n envoy.type.matcher.StringMatcherB\x14\n\rmatch_pattern\x12\x03\xf8\x42\x01J\x04\x08\x04\x10\x05R\x05regex\"\x82\x01\n\x11ListStringMatcher\x12@\n\x08patterns\x18\x01 \x03(\x0b\x32$.envoy.type.matcher.v3.StringMatcherB\x08\xfa\x42\x05\x92\x01\x02\x08\x01:+\x9a\xc5\x88\x1e&\n$envoy.type.matcher.ListStringMatcherB\x84\x01\n#io.envoyproxy.envoy.type.matcher.v3B\x0bStringProtoP\x01ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.matcher.v3.string_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.type.matcher.v3B\013StringProtoP\001ZFgithub.com/envoyproxy/go-control-plane/envoy/type/matcher/v3;matcherv3\272\200\310\321\006\002\020\002'
  _STRINGMATCHER.oneofs_by_name['match_pattern']._options = None
  _STRINGMATCHER.oneofs_by_name['match_pattern']._serialized_options = b'\370B\001'
  _STRINGMATCHER.fields_by_name['prefix']._options = None
  _STRINGMATCHER.fields_by_name['prefix']._serialized_options = b'\372B\004r\002\020\001'
  _STRINGMATCHER.fields_by_name['suffix']._options = None
  _STRINGMATCHER.fields_by_name['suffix']._serialized_options = b'\372B\004r\002\020\001'
  _STRINGMATCHER.fields_by_name['safe_regex']._options = None
  _STRINGMATCHER.fields_by_name['safe_regex']._serialized_options = b'\372B\005\212\001\002\020\001'
  _STRINGMATCHER.fields_by_name['contains']._options = None
  _STRINGMATCHER.fields_by_name['contains']._serialized_options = b'\372B\004r\002\020\001'
  _STRINGMATCHER._options = None
  _STRINGMATCHER._serialized_options = b'\232\305\210\036\"\n envoy.type.matcher.StringMatcher'
  _LISTSTRINGMATCHER.fields_by_name['patterns']._options = None
  _LISTSTRINGMATCHER.fields_by_name['patterns']._serialized_options = b'\372B\005\222\001\002\010\001'
  _LISTSTRINGMATCHER._options = None
  _LISTSTRINGMATCHER._serialized_options = b'\232\305\210\036&\n$envoy.type.matcher.ListStringMatcher'
  _globals['_STRINGMATCHER']._serialized_start=217
  _globals['_STRINGMATCHER']._serialized_end=551
  _globals['_LISTSTRINGMATCHER']._serialized_start=554
  _globals['_LISTSTRINGMATCHER']._serialized_end=684
