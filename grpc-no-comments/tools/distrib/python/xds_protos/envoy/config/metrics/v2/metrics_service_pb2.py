
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import grpc_service_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__service__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n-envoy/config/metrics/v2/metrics_service.proto\x12\x17\x65nvoy.config.metrics.v2\x1a$envoy/api/v2/core/grpc_service.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"V\n\x14MetricsServiceConfig\x12>\n\x0cgrpc_service\x18\x01 \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcServiceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\x90\x01\n%io.envoyproxy.envoy.config.metrics.v2B\x13MetricsServiceProtoP\x01ZHgithub.com/envoyproxy/go-control-plane/envoy/config/metrics/v2;metricsv2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.metrics.v2.metrics_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.config.metrics.v2B\023MetricsServiceProtoP\001ZHgithub.com/envoyproxy/go-control-plane/envoy/config/metrics/v2;metricsv2\272\200\310\321\006\002\020\001'
  _METRICSSERVICECONFIG.fields_by_name['grpc_service']._options = None
  _METRICSSERVICECONFIG.fields_by_name['grpc_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_METRICSSERVICECONFIG']._serialized_start=168
  _globals['_METRICSSERVICECONFIG']._serialized_end=254
