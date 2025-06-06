
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import grpc_service_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__service__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/config/ratelimit/v2/rls.proto\x12\x19\x65nvoy.config.ratelimit.v2\x1a$envoy/api/v2/core/grpc_service.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"d\n\x16RateLimitServiceConfig\x12>\n\x0cgrpc_service\x18\x02 \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01J\x04\x08\x01\x10\x02J\x04\x08\x03\x10\x04\x42\x8b\x01\n\'io.envoyproxy.envoy.config.ratelimit.v2B\x08RlsProtoP\x01ZLgithub.com/envoyproxy/go-control-plane/envoy/config/ratelimit/v2;ratelimitv2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.ratelimit.v2.rls_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\'io.envoyproxy.envoy.config.ratelimit.v2B\010RlsProtoP\001ZLgithub.com/envoyproxy/go-control-plane/envoy/config/ratelimit/v2;ratelimitv2\272\200\310\321\006\002\020\001'
  _RATELIMITSERVICECONFIG.fields_by_name['grpc_service']._options = None
  _RATELIMITSERVICECONFIG.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_RATELIMITSERVICECONFIG']._serialized_start=160
  _globals['_RATELIMITSERVICECONFIG']._serialized_end=260
