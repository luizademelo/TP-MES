
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.metrics.v1 import metrics_pb2 as opentelemetry_dot_proto_dot_metrics_dot_v1_dot_metrics__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n>opentelemetry/proto/collector/metrics/v1/metrics_service.proto\x12(opentelemetry.proto.collector.metrics.v1\x1a,opentelemetry/proto/metrics/v1/metrics.proto\"h\n\x1b\x45xportMetricsServiceRequest\x12I\n\x10resource_metrics\x18\x01 \x03(\x0b\x32/.opentelemetry.proto.metrics.v1.ResourceMetrics\"\x1e\n\x1c\x45xportMetricsServiceResponse2\xac\x01\n\x0eMetricsService\x12\x99\x01\n\x06\x45xport\x12\x45.opentelemetry.proto.collector.metrics.v1.ExportMetricsServiceRequest\x1a\x46.opentelemetry.proto.collector.metrics.v1.ExportMetricsServiceResponse\"\x00\x42\x8f\x01\n+io.opentelemetry.proto.collector.metrics.v1B\x13MetricsServiceProtoP\x01ZIgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/metrics/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.collector.metrics.v1.metrics_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n+io.opentelemetry.proto.collector.metrics.v1B\023MetricsServiceProtoP\001ZIgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/metrics/v1'
  _globals['_EXPORTMETRICSSERVICEREQUEST']._serialized_start=154
  _globals['_EXPORTMETRICSSERVICEREQUEST']._serialized_end=258
  _globals['_EXPORTMETRICSSERVICERESPONSE']._serialized_start=260
  _globals['_EXPORTMETRICSSERVICERESPONSE']._serialized_end=290
  _globals['_METRICSSERVICE']._serialized_start=293
  _globals['_METRICSSERVICE']._serialized_end=465
