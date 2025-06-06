
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.resource.v1 import resource_pb2 as opentelemetry_dot_proto_dot_resource_dot_v1_dot_resource__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nEopentelemetry/proto/metrics/experimental/metrics_config_service.proto\x12(opentelemetry.proto.metrics.experimental\x1a.opentelemetry/proto/resource/v1/resource.proto\"r\n\x13MetricConfigRequest\x12;\n\x08resource\x18\x01 \x01(\x0b\x32).opentelemetry.proto.resource.v1.Resource\x12\x1e\n\x16last_known_fingerprint\x18\x02 \x01(\x0c\"\xe0\x03\n\x14MetricConfigResponse\x12\x13\n\x0b\x66ingerprint\x18\x01 \x01(\x0c\x12Z\n\tschedules\x18\x02 \x03(\x0b\x32G.opentelemetry.proto.metrics.experimental.MetricConfigResponse.Schedule\x12\x1f\n\x17suggested_wait_time_sec\x18\x03 \x01(\x05\x1a\xb5\x02\n\x08Schedule\x12k\n\x12\x65xclusion_patterns\x18\x01 \x03(\x0b\x32O.opentelemetry.proto.metrics.experimental.MetricConfigResponse.Schedule.Pattern\x12k\n\x12inclusion_patterns\x18\x02 \x03(\x0b\x32O.opentelemetry.proto.metrics.experimental.MetricConfigResponse.Schedule.Pattern\x12\x12\n\nperiod_sec\x18\x03 \x01(\x05\x1a;\n\x07Pattern\x12\x10\n\x06\x65quals\x18\x01 \x01(\tH\x00\x12\x15\n\x0bstarts_with\x18\x02 \x01(\tH\x00\x42\x07\n\x05match2\xa1\x01\n\x0cMetricConfig\x12\x90\x01\n\x0fGetMetricConfig\x12=.opentelemetry.proto.metrics.experimental.MetricConfigRequest\x1a>.opentelemetry.proto.metrics.experimental.MetricConfigResponseB\x94\x01\n+io.opentelemetry.proto.metrics.experimentalB\x18MetricConfigServiceProtoP\x01ZIgithub.com/open-telemetry/opentelemetry-proto/gen/go/metrics/experimentalb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.metrics.experimental.metrics_config_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n+io.opentelemetry.proto.metrics.experimentalB\030MetricConfigServiceProtoP\001ZIgithub.com/open-telemetry/opentelemetry-proto/gen/go/metrics/experimental'
  _globals['_METRICCONFIGREQUEST']._serialized_start=163
  _globals['_METRICCONFIGREQUEST']._serialized_end=277
  _globals['_METRICCONFIGRESPONSE']._serialized_start=280
  _globals['_METRICCONFIGRESPONSE']._serialized_end=760
  _globals['_METRICCONFIGRESPONSE_SCHEDULE']._serialized_start=451
  _globals['_METRICCONFIGRESPONSE_SCHEDULE']._serialized_end=760
  _globals['_METRICCONFIGRESPONSE_SCHEDULE_PATTERN']._serialized_start=701
  _globals['_METRICCONFIGRESPONSE_SCHEDULE_PATTERN']._serialized_end=760
  _globals['_METRICCONFIG']._serialized_start=763
  _globals['_METRICCONFIG']._serialized_end=924
