
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.matcher.v3 import value_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_value__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nCenvoy/extensions/matching/input_matchers/metadata/v3/metadata.proto\x12\x34\x65nvoy.extensions.matching.input_matchers.metadata.v3\x1a!envoy/type/matcher/v3/value.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"X\n\x08Metadata\x12<\n\x05value\x18\x01 \x01(\x0b\x32#.envoy.type.matcher.v3.ValueMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0e\n\x06invert\x18\x04 \x01(\x08\x42\xc5\x01\nBio.envoyproxy.envoy.extensions.matching.input_matchers.metadata.v3B\rMetadataProtoP\x01Zfgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/metadata/v3;metadatav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.matching.input_matchers.metadata.v3.metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nBio.envoyproxy.envoy.extensions.matching.input_matchers.metadata.v3B\rMetadataProtoP\001Zfgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/metadata/v3;metadatav3\272\200\310\321\006\002\020\002'
  _METADATA.fields_by_name['value']._options = None
  _METADATA.fields_by_name['value']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_METADATA']._serialized_start=216
  _globals['_METADATA']._serialized_end=304
