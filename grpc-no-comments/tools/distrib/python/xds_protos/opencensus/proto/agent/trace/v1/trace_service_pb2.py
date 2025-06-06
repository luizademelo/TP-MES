
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opencensus.proto.agent.common.v1 import common_pb2 as opencensus_dot_proto_dot_agent_dot_common_dot_v1_dot_common__pb2
from opencensus.proto.resource.v1 import resource_pb2 as opencensus_dot_proto_dot_resource_dot_v1_dot_resource__pb2
from opencensus.proto.trace.v1 import trace_pb2 as opencensus_dot_proto_dot_trace_dot_v1_dot_trace__pb2
from opencensus.proto.trace.v1 import trace_config_pb2 as opencensus_dot_proto_dot_trace_dot_v1_dot_trace__config__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3opencensus/proto/agent/trace/v1/trace_service.proto\x12\x1fopencensus.proto.agent.trace.v1\x1a-opencensus/proto/agent/common/v1/common.proto\x1a+opencensus/proto/resource/v1/resource.proto\x1a%opencensus/proto/trace/v1/trace.proto\x1a,opencensus/proto/trace/v1/trace_config.proto\"\x84\x01\n\x14\x43urrentLibraryConfig\x12\x34\n\x04node\x18\x01 \x01(\x0b\x32&.opencensus.proto.agent.common.v1.Node\x12\x36\n\x06\x63onfig\x18\x02 \x01(\x0b\x32&.opencensus.proto.trace.v1.TraceConfig\"\x84\x01\n\x14UpdatedLibraryConfig\x12\x34\n\x04node\x18\x01 \x01(\x0b\x32&.opencensus.proto.agent.common.v1.Node\x12\x36\n\x06\x63onfig\x18\x02 \x01(\x0b\x32&.opencensus.proto.trace.v1.TraceConfig\"\xbb\x01\n\x19\x45xportTraceServiceRequest\x12\x34\n\x04node\x18\x01 \x01(\x0b\x32&.opencensus.proto.agent.common.v1.Node\x12.\n\x05spans\x18\x02 \x03(\x0b\x32\x1f.opencensus.proto.trace.v1.Span\x12\x38\n\x08resource\x18\x03 \x01(\x0b\x32&.opencensus.proto.resource.v1.Resource\"\x1c\n\x1a\x45xportTraceServiceResponse2\x96\x02\n\x0cTraceService\x12|\n\x06\x43onfig\x12\x35.opencensus.proto.agent.trace.v1.CurrentLibraryConfig\x1a\x35.opencensus.proto.agent.trace.v1.UpdatedLibraryConfig\"\x00(\x01\x30\x01\x12\x87\x01\n\x06\x45xport\x12:.opencensus.proto.agent.trace.v1.ExportTraceServiceRequest\x1a;.opencensus.proto.agent.trace.v1.ExportTraceServiceResponse\"\x00(\x01\x30\x01\x42\xa5\x01\n\"io.opencensus.proto.agent.trace.v1B\x11TraceServiceProtoP\x01ZHgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/trace/v1\xea\x02\x1fOpenCensus.Proto.Agent.Trace.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.agent.trace.v1.trace_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.opencensus.proto.agent.trace.v1B\021TraceServiceProtoP\001ZHgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/trace/v1\352\002\037OpenCensus.Proto.Agent.Trace.V1'
  _globals['_CURRENTLIBRARYCONFIG']._serialized_start=266
  _globals['_CURRENTLIBRARYCONFIG']._serialized_end=398
  _globals['_UPDATEDLIBRARYCONFIG']._serialized_start=401
  _globals['_UPDATEDLIBRARYCONFIG']._serialized_end=533
  _globals['_EXPORTTRACESERVICEREQUEST']._serialized_start=536
  _globals['_EXPORTTRACESERVICEREQUEST']._serialized_end=723
  _globals['_EXPORTTRACESERVICERESPONSE']._serialized_start=725
  _globals['_EXPORTTRACESERVICERESPONSE']._serialized_end=753
  _globals['_TRACESERVICE']._serialized_start=756
  _globals['_TRACESERVICE']._serialized_end=1034
