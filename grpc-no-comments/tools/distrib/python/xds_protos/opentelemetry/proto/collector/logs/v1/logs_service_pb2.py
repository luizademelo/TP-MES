
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.logs.v1 import logs_pb2 as opentelemetry_dot_proto_dot_logs_dot_v1_dot_logs__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n8opentelemetry/proto/collector/logs/v1/logs_service.proto\x12%opentelemetry.proto.collector.logs.v1\x1a&opentelemetry/proto/logs/v1/logs.proto\"\\\n\x18\x45xportLogsServiceRequest\x12@\n\rresource_logs\x18\x01 \x03(\x0b\x32).opentelemetry.proto.logs.v1.ResourceLogs\"\x1b\n\x19\x45xportLogsServiceResponse2\x9d\x01\n\x0bLogsService\x12\x8d\x01\n\x06\x45xport\x12?.opentelemetry.proto.collector.logs.v1.ExportLogsServiceRequest\x1a@.opentelemetry.proto.collector.logs.v1.ExportLogsServiceResponse\"\x00\x42\x86\x01\n(io.opentelemetry.proto.collector.logs.v1B\x10LogsServiceProtoP\x01ZFgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/logs/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.collector.logs.v1.logs_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(io.opentelemetry.proto.collector.logs.v1B\020LogsServiceProtoP\001ZFgithub.com/open-telemetry/opentelemetry-proto/gen/go/collector/logs/v1'
  _globals['_EXPORTLOGSSERVICEREQUEST']._serialized_start=139
  _globals['_EXPORTLOGSSERVICEREQUEST']._serialized_end=231
  _globals['_EXPORTLOGSSERVICERESPONSE']._serialized_start=233
  _globals['_EXPORTLOGSSERVICERESPONSE']._serialized_end=260
  _globals['_LOGSSERVICE']._serialized_start=263
  _globals['_LOGSSERVICE']._serialized_end=420
