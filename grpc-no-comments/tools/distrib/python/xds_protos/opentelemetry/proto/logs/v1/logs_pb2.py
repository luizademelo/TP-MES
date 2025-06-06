
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.common.v1 import common_pb2 as opentelemetry_dot_proto_dot_common_dot_v1_dot_common__pb2
from opentelemetry.proto.resource.v1 import resource_pb2 as opentelemetry_dot_proto_dot_resource_dot_v1_dot_resource__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&opentelemetry/proto/logs/v1/logs.proto\x12\x1bopentelemetry.proto.logs.v1\x1a*opentelemetry/proto/common/v1/common.proto\x1a.opentelemetry/proto/resource/v1/resource.proto\"\xbe\x01\n\x0cResourceLogs\x12;\n\x08resource\x18\x01 \x01(\x0b\x32).opentelemetry.proto.resource.v1.Resource\x12]\n\x1cinstrumentation_library_logs\x18\x02 \x03(\x0b\x32\x37.opentelemetry.proto.logs.v1.InstrumentationLibraryLogs\x12\x12\n\nschema_url\x18\x03 \x01(\t\"\xbe\x01\n\x1aInstrumentationLibraryLogs\x12V\n\x17instrumentation_library\x18\x01 \x01(\x0b\x32\x35.opentelemetry.proto.common.v1.InstrumentationLibrary\x12\x34\n\x04logs\x18\x02 \x03(\x0b\x32&.opentelemetry.proto.logs.v1.LogRecord\x12\x12\n\nschema_url\x18\x03 \x01(\t\"\xd6\x02\n\tLogRecord\x12\x16\n\x0etime_unix_nano\x18\x01 \x01(\x06\x12\x44\n\x0fseverity_number\x18\x02 \x01(\x0e\x32+.opentelemetry.proto.logs.v1.SeverityNumber\x12\x15\n\rseverity_text\x18\x03 \x01(\t\x12\x0c\n\x04name\x18\x04 \x01(\t\x12\x35\n\x04\x62ody\x18\x05 \x01(\x0b\x32\'.opentelemetry.proto.common.v1.AnyValue\x12;\n\nattributes\x18\x06 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\x12 \n\x18\x64ropped_attributes_count\x18\x07 \x01(\r\x12\r\n\x05\x66lags\x18\x08 \x01(\x07\x12\x10\n\x08trace_id\x18\t \x01(\x0c\x12\x0f\n\x07span_id\x18\n \x01(\x0c*\xc3\x05\n\x0eSeverityNumber\x12\x1f\n\x1bSEVERITY_NUMBER_UNSPECIFIED\x10\x00\x12\x19\n\x15SEVERITY_NUMBER_TRACE\x10\x01\x12\x1a\n\x16SEVERITY_NUMBER_TRACE2\x10\x02\x12\x1a\n\x16SEVERITY_NUMBER_TRACE3\x10\x03\x12\x1a\n\x16SEVERITY_NUMBER_TRACE4\x10\x04\x12\x19\n\x15SEVERITY_NUMBER_DEBUG\x10\x05\x12\x1a\n\x16SEVERITY_NUMBER_DEBUG2\x10\x06\x12\x1a\n\x16SEVERITY_NUMBER_DEBUG3\x10\x07\x12\x1a\n\x16SEVERITY_NUMBER_DEBUG4\x10\x08\x12\x18\n\x14SEVERITY_NUMBER_INFO\x10\t\x12\x19\n\x15SEVERITY_NUMBER_INFO2\x10\n\x12\x19\n\x15SEVERITY_NUMBER_INFO3\x10\x0b\x12\x19\n\x15SEVERITY_NUMBER_INFO4\x10\x0c\x12\x18\n\x14SEVERITY_NUMBER_WARN\x10\r\x12\x19\n\x15SEVERITY_NUMBER_WARN2\x10\x0e\x12\x19\n\x15SEVERITY_NUMBER_WARN3\x10\x0f\x12\x19\n\x15SEVERITY_NUMBER_WARN4\x10\x10\x12\x19\n\x15SEVERITY_NUMBER_ERROR\x10\x11\x12\x1a\n\x16SEVERITY_NUMBER_ERROR2\x10\x12\x12\x1a\n\x16SEVERITY_NUMBER_ERROR3\x10\x13\x12\x1a\n\x16SEVERITY_NUMBER_ERROR4\x10\x14\x12\x19\n\x15SEVERITY_NUMBER_FATAL\x10\x15\x12\x1a\n\x16SEVERITY_NUMBER_FATAL2\x10\x16\x12\x1a\n\x16SEVERITY_NUMBER_FATAL3\x10\x17\x12\x1a\n\x16SEVERITY_NUMBER_FATAL4\x10\x18*X\n\x0eLogRecordFlags\x12\x1f\n\x1bLOG_RECORD_FLAG_UNSPECIFIED\x10\x00\x12%\n LOG_RECORD_FLAG_TRACE_FLAGS_MASK\x10\xff\x01\x42k\n\x1eio.opentelemetry.proto.logs.v1B\tLogsProtoP\x01Z<github.com/open-telemetry/opentelemetry-proto/gen/go/logs/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.logs.v1.logs_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036io.opentelemetry.proto.logs.v1B\tLogsProtoP\001Z<github.com/open-telemetry/opentelemetry-proto/gen/go/logs/v1'
  _globals['_SEVERITYNUMBER']._serialized_start=895
  _globals['_SEVERITYNUMBER']._serialized_end=1602
  _globals['_LOGRECORDFLAGS']._serialized_start=1604
  _globals['_LOGRECORDFLAGS']._serialized_end=1692
  _globals['_RESOURCELOGS']._serialized_start=164
  _globals['_RESOURCELOGS']._serialized_end=354
  _globals['_INSTRUMENTATIONLIBRARYLOGS']._serialized_start=357
  _globals['_INSTRUMENTATIONLIBRARYLOGS']._serialized_end=547
  _globals['_LOGRECORD']._serialized_start=550
  _globals['_LOGRECORD']._serialized_end=892
