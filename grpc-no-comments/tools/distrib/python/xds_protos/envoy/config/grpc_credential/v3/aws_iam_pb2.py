
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n-envoy/config/grpc_credential/v3/aws_iam.proto\x12\x1f\x65nvoy.config.grpc_credential.v3\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x8f\x01\n\x0c\x41wsIamConfig\x12(\n\x0cservice_name\x18\x01 \x01(\tB\x12\x18\x01\xfa\x42\x04r\x02\x10\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12\x1b\n\x06region\x18\x02 \x01(\tB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0:8\x9a\xc5\x88\x1e\x33\n1envoy.config.grpc_credential.v2alpha.AwsIamConfigB\xa0\x01\n-io.envoyproxy.envoy.config.grpc_credential.v3B\x0b\x41wsIamProtoP\x01ZXgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v3;grpc_credentialv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.grpc_credential.v3.aws_iam_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n-io.envoyproxy.envoy.config.grpc_credential.v3B\013AwsIamProtoP\001ZXgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v3;grpc_credentialv3\272\200\310\321\006\002\020\002'
  _AWSIAMCONFIG.fields_by_name['service_name']._options = None
  _AWSIAMCONFIG.fields_by_name['service_name']._serialized_options = b'\030\001\372B\004r\002\020\001\222\307\206\330\004\0033.0'
  _AWSIAMCONFIG.fields_by_name['region']._options = None
  _AWSIAMCONFIG.fields_by_name['region']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _AWSIAMCONFIG._options = None
  _AWSIAMCONFIG._serialized_options = b'\232\305\210\0363\n1envoy.config.grpc_credential.v2alpha.AwsIamConfig'
  _globals['_AWSIAMCONFIG']._serialized_start=211
  _globals['_AWSIAMCONFIG']._serialized_end=354
