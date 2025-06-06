
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import grpc_service_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__service__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/config/trace/v2/service.proto\x12\x15\x65nvoy.config.trace.v2\x1a$envoy/api/v2/core/grpc_service.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"T\n\x12TraceServiceConfig\x12>\n\x0cgrpc_service\x18\x01 \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\x83\x01\n#io.envoyproxy.envoy.config.trace.v2B\x0cServiceProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\014ServiceProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _TRACESERVICECONFIG.fields_by_name['grpc_service']._options = None
  _TRACESERVICECONFIG.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_TRACESERVICECONFIG']._serialized_start=156
  _globals['_TRACESERVICECONFIG']._serialized_end=240
