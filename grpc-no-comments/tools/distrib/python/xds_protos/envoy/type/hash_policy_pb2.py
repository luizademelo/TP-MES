
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1c\x65nvoy/type/hash_policy.proto\x12\nenvoy.type\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"g\n\nHashPolicy\x12\x34\n\tsource_ip\x18\x01 \x01(\x0b\x32\x1f.envoy.type.HashPolicy.SourceIpH\x00\x1a\n\n\x08SourceIpB\x17\n\x10policy_specifier\x12\x03\xf8\x42\x01\x42h\n\x18io.envoyproxy.envoy.typeB\x0fHashPolicyProtoP\x01Z1github.com/envoyproxy/go-control-plane/envoy/type\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.hash_policy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\030io.envoyproxy.envoy.typeB\017HashPolicyProtoP\001Z1github.com/envoyproxy/go-control-plane/envoy/type\272\200\310\321\006\002\020\001'
  _HASHPOLICY.oneofs_by_name['policy_specifier']._options = None
  _HASHPOLICY.oneofs_by_name['policy_specifier']._serialized_options = b'\370B\001'
  _globals['_HASHPOLICY']._serialized_start=100
  _globals['_HASHPOLICY']._serialized_end=203
  _globals['_HASHPOLICY_SOURCEIP']._serialized_start=168
  _globals['_HASHPOLICY_SOURCEIP']._serialized_end=178
