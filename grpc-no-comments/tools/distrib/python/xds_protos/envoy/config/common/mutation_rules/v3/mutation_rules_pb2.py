
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.type.matcher.v3 import regex_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_regex__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n:envoy/config/common/mutation_rules/v3/mutation_rules.proto\x12%envoy.config.common.mutation_rules.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a!envoy/type/matcher/v3/regex.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x9c\x03\n\x13HeaderMutationRules\x12\x35\n\x11\x61llow_all_routing\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12/\n\x0b\x61llow_envoy\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x33\n\x0f\x64isallow_system\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x30\n\x0c\x64isallow_all\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12=\n\x10\x61llow_expression\x18\x05 \x01(\x0b\x32#.envoy.type.matcher.v3.RegexMatcher\x12@\n\x13\x64isallow_expression\x18\x06 \x01(\x0b\x32#.envoy.type.matcher.v3.RegexMatcher\x12\x35\n\x11\x64isallow_is_error\x18\x07 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\"y\n\x0eHeaderMutation\x12\x1d\n\x06remove\x18\x01 \x01(\tB\x0b\xfa\x42\x08r\x06\xc0\x01\x02\xc8\x01\x00H\x00\x12\x39\n\x06\x61ppend\x18\x02 \x01(\x0b\x32\'.envoy.config.core.v3.HeaderValueOptionH\x00\x42\r\n\x06\x61\x63tion\x12\x03\xf8\x42\x01\x42\xb2\x01\n3io.envoyproxy.envoy.config.common.mutation_rules.v3B\x12MutationRulesProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/config/common/mutation_rules/v3;mutation_rulesv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.common.mutation_rules.v3.mutation_rules_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n3io.envoyproxy.envoy.config.common.mutation_rules.v3B\022MutationRulesProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/config/common/mutation_rules/v3;mutation_rulesv3\272\200\310\321\006\002\020\002'
  _HEADERMUTATION.oneofs_by_name['action']._options = None
  _HEADERMUTATION.oneofs_by_name['action']._serialized_options = b'\370B\001'
  _HEADERMUTATION.fields_by_name['remove']._options = None
  _HEADERMUTATION.fields_by_name['remove']._serialized_options = b'\372B\010r\006\300\001\002\310\001\000'
  _globals['_HEADERMUTATIONRULES']._serialized_start=258
  _globals['_HEADERMUTATIONRULES']._serialized_end=670
  _globals['_HEADERMUTATION']._serialized_start=672
  _globals['_HEADERMUTATION']._serialized_end=793
