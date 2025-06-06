
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opencensus.proto.agent.common.v1 import common_pb2 as opencensus_dot_proto_dot_agent_dot_common_dot_v1_dot_common__pb2
from opencensus.proto.metrics.v1 import metrics_pb2 as opencensus_dot_proto_dot_metrics_dot_v1_dot_metrics__pb2
from opencensus.proto.resource.v1 import resource_pb2 as opencensus_dot_proto_dot_resource_dot_v1_dot_resource__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7opencensus/proto/agent/metrics/v1/metrics_service.proto\x12!opencensus.proto.agent.metrics.v1\x1a-opencensus/proto/agent/common/v1/common.proto\x1a)opencensus/proto/metrics/v1/metrics.proto\x1a+opencensus/proto/resource/v1/resource.proto\"\xc3\x01\n\x1b\x45xportMetricsServiceRequest\x12\x34\n\x04node\x18\x01 \x01(\x0b\x32&.opencensus.proto.agent.common.v1.Node\x12\x34\n\x07metrics\x18\x02 \x03(\x0b\x32#.opencensus.proto.metrics.v1.Metric\x12\x38\n\x08resource\x18\x03 \x01(\x0b\x32&.opencensus.proto.resource.v1.Resource\"\x1e\n\x1c\x45xportMetricsServiceResponse2\xa2\x01\n\x0eMetricsService\x12\x8f\x01\n\x06\x45xport\x12>.opencensus.proto.agent.metrics.v1.ExportMetricsServiceRequest\x1a?.opencensus.proto.agent.metrics.v1.ExportMetricsServiceResponse\"\x00(\x01\x30\x01\x42\xad\x01\n$io.opencensus.proto.agent.metrics.v1B\x13MetricsServiceProtoP\x01ZJgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/metrics/v1\xea\x02!OpenCensus.Proto.Agent.Metrics.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.agent.metrics.v1.metrics_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.opencensus.proto.agent.metrics.v1B\023MetricsServiceProtoP\001ZJgithub.com/census-instrumentation/opencensus-proto/gen-go/agent/metrics/v1\352\002!OpenCensus.Proto.Agent.Metrics.V1'
  _globals['_EXPORTMETRICSSERVICEREQUEST']._serialized_start=230
  _globals['_EXPORTMETRICSSERVICEREQUEST']._serialized_end=425
  _globals['_EXPORTMETRICSSERVICERESPONSE']._serialized_start=427
  _globals['_EXPORTMETRICSSERVICERESPONSE']._serialized_end=457
  _globals['_METRICSSERVICE']._serialized_start=460
  _globals['_METRICSSERVICE']._serialized_end=622
