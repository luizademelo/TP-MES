
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2envoy/config/grpc_credential/v2alpha/aws_iam.proto\x12$envoy.config.grpc_credential.v2alpha\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"=\n\x0c\x41wsIamConfig\x12\x1d\n\x0cservice_name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x0e\n\x06region\x18\x02 \x01(\tB\x98\x01\n2io.envoyproxy.envoy.config.grpc_credential.v2alphaB\x0b\x41wsIamProtoP\x01ZKgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.grpc_credential.v2alpha.aws_iam_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n2io.envoyproxy.envoy.config.grpc_credential.v2alphaB\013AwsIamProtoP\001ZKgithub.com/envoyproxy/go-control-plane/envoy/config/grpc_credential/v2alpha\272\200\310\321\006\002\020\001'
  _AWSIAMCONFIG.fields_by_name['service_name']._options = None
  _AWSIAMCONFIG.fields_by_name['service_name']._serialized_options = b'\372B\004r\002 \001'
  _globals['_AWSIAMCONFIG']._serialized_start=148
  _globals['_AWSIAMCONFIG']._serialized_end=209
