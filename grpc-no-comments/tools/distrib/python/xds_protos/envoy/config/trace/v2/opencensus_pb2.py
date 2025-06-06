
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import grpc_service_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__service__pb2
from opencensus.proto.trace.v1 import trace_config_pb2 as opencensus_dot_proto_dot_trace_dot_v1_dot_trace__config__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/config/trace/v2/opencensus.proto\x12\x15\x65nvoy.config.trace.v2\x1a$envoy/api/v2/core/grpc_service.proto\x1a,opencensus/proto/trace/v1/trace_config.proto\x1a\x1dudpa/annotations/status.proto\"\xd8\x05\n\x10OpenCensusConfig\x12<\n\x0ctrace_config\x18\x01 \x01(\x0b\x32&.opencensus.proto.trace.v1.TraceConfig\x12\x1f\n\x17stdout_exporter_enabled\x18\x02 \x01(\x08\x12$\n\x1cstackdriver_exporter_enabled\x18\x03 \x01(\x08\x12\x1e\n\x16stackdriver_project_id\x18\x04 \x01(\t\x12\x1b\n\x13stackdriver_address\x18\n \x01(\t\x12@\n\x18stackdriver_grpc_service\x18\r \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcService\x12\x1f\n\x17zipkin_exporter_enabled\x18\x05 \x01(\x08\x12\x12\n\nzipkin_url\x18\x06 \x01(\t\x12 \n\x18ocagent_exporter_enabled\x18\x0b \x01(\x08\x12\x17\n\x0focagent_address\x18\x0c \x01(\t\x12<\n\x14ocagent_grpc_service\x18\x0e \x01(\x0b\x32\x1e.envoy.api.v2.core.GrpcService\x12T\n\x16incoming_trace_context\x18\x08 \x03(\x0e\x32\x34.envoy.config.trace.v2.OpenCensusConfig.TraceContext\x12T\n\x16outgoing_trace_context\x18\t \x03(\x0e\x32\x34.envoy.config.trace.v2.OpenCensusConfig.TraceContext\"`\n\x0cTraceContext\x12\x08\n\x04NONE\x10\x00\x12\x11\n\rTRACE_CONTEXT\x10\x01\x12\x12\n\x0eGRPC_TRACE_BIN\x10\x02\x12\x17\n\x13\x43LOUD_TRACE_CONTEXT\x10\x03\x12\x06\n\x02\x42\x33\x10\x04J\x04\x08\x07\x10\x08\x42\x86\x01\n#io.envoyproxy.envoy.config.trace.v2B\x0fOpencensusProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.opencensus_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\017OpencensusProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _globals['_OPENCENSUSCONFIG']._serialized_start=181
  _globals['_OPENCENSUSCONFIG']._serialized_end=909
  _globals['_OPENCENSUSCONFIG_TRACECONTEXT']._serialized_start=807
  _globals['_OPENCENSUSCONFIG_TRACECONTEXT']._serialized_end=903
