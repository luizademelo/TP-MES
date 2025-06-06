
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.common.mutation_rules.v3 import mutation_rules_pb2 as envoy_dot_config_dot_common_dot_mutation__rules_dot_v3_dot_mutation__rules__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nTenvoy/extensions/http/early_header_mutation/header_mutation/v3/header_mutation.proto\x12>envoy.extensions.http.early_header_mutation.header_mutation.v3\x1a:envoy/config/common/mutation_rules/v3/mutation_rules.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"d\n\x0eHeaderMutation\x12R\n\tmutations\x18\x01 \x03(\x0b\x32\x35.envoy.config.common.mutation_rules.v3.HeaderMutationB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x42\xe6\x01\nLio.envoyproxy.envoy.extensions.http.early_header_mutation.header_mutation.v3B\x13HeaderMutationProtoP\x01Zwgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/early_header_mutation/header_mutation/v3;header_mutationv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.early_header_mutation.header_mutation.v3.header_mutation_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nLio.envoyproxy.envoy.extensions.http.early_header_mutation.header_mutation.v3B\023HeaderMutationProtoP\001Zwgithub.com/envoyproxy/go-control-plane/envoy/extensions/http/early_header_mutation/header_mutation/v3;header_mutationv3\272\200\310\321\006\002\020\002'
  _HEADERMUTATION.fields_by_name['mutations']._options = None
  _HEADERMUTATION.fields_by_name['mutations']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_HEADERMUTATION']._serialized_start=268
  _globals['_HEADERMUTATION']._serialized_end=368
