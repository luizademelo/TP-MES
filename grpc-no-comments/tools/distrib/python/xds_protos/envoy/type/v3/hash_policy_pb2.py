
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/type/v3/hash_policy.proto\x12\renvoy.type.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x93\x02\n\nHashPolicy\x12\x37\n\tsource_ip\x18\x01 \x01(\x0b\x32\".envoy.type.v3.HashPolicy.SourceIpH\x00\x12=\n\x0c\x66ilter_state\x18\x02 \x01(\x0b\x32%.envoy.type.v3.HashPolicy.FilterStateH\x00\x1a\x31\n\x08SourceIp:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.type.HashPolicy.SourceIp\x1a#\n\x0b\x46ilterState\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01:\x1c\x9a\xc5\x88\x1e\x17\n\x15\x65nvoy.type.HashPolicyB\x17\n\x10policy_specifier\x12\x03\xf8\x42\x01\x42u\n\x1bio.envoyproxy.envoy.type.v3B\x0fHashPolicyProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.v3.hash_policy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033io.envoyproxy.envoy.type.v3B\017HashPolicyProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\272\200\310\321\006\002\020\002'
  _HASHPOLICY_SOURCEIP._options = None
  _HASHPOLICY_SOURCEIP._serialized_options = b'\232\305\210\036 \n\036envoy.type.HashPolicy.SourceIp'
  _HASHPOLICY_FILTERSTATE.fields_by_name['key']._options = None
  _HASHPOLICY_FILTERSTATE.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _HASHPOLICY.oneofs_by_name['policy_specifier']._options = None
  _HASHPOLICY.oneofs_by_name['policy_specifier']._serialized_options = b'\370B\001'
  _HASHPOLICY._options = None
  _HASHPOLICY._serialized_options = b'\232\305\210\036\027\n\025envoy.type.HashPolicy'
  _globals['_HASHPOLICY']._serialized_start=142
  _globals['_HASHPOLICY']._serialized_end=417
  _globals['_HASHPOLICY_SOURCEIP']._serialized_start=276
  _globals['_HASHPOLICY_SOURCEIP']._serialized_end=325
  _globals['_HASHPOLICY_FILTERSTATE']._serialized_start=327
  _globals['_HASHPOLICY_FILTERSTATE']._serialized_end=362
