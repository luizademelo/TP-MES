
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import grpc_service_pb2 as envoy_dot_config_dot_core_dot_v3_dot_grpc__service__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/config/trace/v3/service.proto\x12\x15\x65nvoy.config.trace.v3\x1a\'envoy/config/core/v3/grpc_service.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x88\x01\n\x12TraceServiceConfig\x12\x41\n\x0cgrpc_service\x18\x01 \x01(\x0b\x32!.envoy.config.core.v3.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01:/\x9a\xc5\x88\x1e*\n(envoy.config.trace.v2.TraceServiceConfigB\x83\x01\n#io.envoyproxy.envoy.config.trace.v3B\x0cServiceProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v3.service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v3B\014ServiceProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3\272\200\310\321\006\002\020\002'
  _TRACESERVICECONFIG.fields_by_name['grpc_service']._options = None
  _TRACESERVICECONFIG.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _TRACESERVICECONFIG._options = None
  _TRACESERVICECONFIG._serialized_options = b'\232\305\210\036*\n(envoy.config.trace.v2.TraceServiceConfig'
  _globals['_TRACESERVICECONFIG']._serialized_start=195
  _globals['_TRACESERVICECONFIG']._serialized_end=331
