
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.trace.v1 import trace_pb2 as opentelemetry_dot_proto_dot_trace_dot_v1_dot_trace__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n:opentelemetry/proto/collector/trace/v1/trace_service.proto\x12&opentelemetry.proto.collector.trace.v1\x1a(opentelemetry/proto/trace/v1/trace.proto\"`\n\x19\x45xportTraceServiceRequest\x12\x43\n\x0eresource_spans\x18\x01 \x03(\x0b\x32+.opentelemetry.proto.trace.v1.ResourceSpans\"\x1c\n\x1a\x45xportTraceServiceResponse2\xa2\x01\n\x0cTraceService\x12\x91\x01\n\x06\x45xport\x12\x41.opentelemetry.proto.collector.trace.v1.ExportTraceServiceRequest\x1a\x42.opentelemetry.proto.collector.trace.v1.ExportTraceServiceResponse\"\x00\x42\x89\x01\n)io.opentelemetry.proto.collector.trace.v1B\x11TraceServiceProtoP\x01ZGgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/trace/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.collector.trace.v1.trace_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n)io.opentelemetry.proto.collector.trace.v1B\021TraceServiceProtoP\001ZGgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/trace/v1'
  _globals['_EXPORTTRACESERVICEREQUEST']._serialized_start=144
  _globals['_EXPORTTRACESERVICEREQUEST']._serialized_end=240
  _globals['_EXPORTTRACESERVICERESPONSE']._serialized_start=242
  _globals['_EXPORTTRACESERVICERESPONSE']._serialized_end=270
  _globals['_TRACESERVICE']._serialized_start=273
  _globals['_TRACESERVICE']._serialized_end=435
