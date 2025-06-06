
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import monitored_resource_pb2 as google_dot_api_dot_monitored__resource__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.logging.type import http_request_pb2 as google_dot_logging_dot_type_dot_http__request__pb2
from google.logging.type import log_severity_pb2 as google_dot_logging_dot_type_dot_log__severity__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!google/logging/v2/log_entry.proto\x12\x11google.logging.v2\x1a\x1fgoogle/api/field_behavior.proto\x1a#google/api/monitored_resource.proto\x1a\x19google/api/resource.proto\x1a&google/logging/type/http_request.proto\x1a&google/logging/type/log_severity.proto\x1a\x19google/protobuf/any.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\x83\x08\n\x08LogEntry\x12\x15\n\x08log_name\x18\x0c \x01(\tB\x03\xe0\x41\x02\x12\x34\n\x08resource\x18\x08 \x01(\x0b\x32\x1d.google.api.MonitoredResourceB\x03\xe0\x41\x02\x12-\n\rproto_payload\x18\x02 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x12\x16\n\x0ctext_payload\x18\x03 \x01(\tH\x00\x12/\n\x0cjson_payload\x18\x06 \x01(\x0b\x32\x17.google.protobuf.StructH\x00\x12\x32\n\ttimestamp\x18\t \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x01\x12:\n\x11receive_timestamp\x18\x18 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x37\n\x08severity\x18\n \x01(\x0e\x32 .google.logging.type.LogSeverityB\x03\xe0\x41\x01\x12\x16\n\tinsert_id\x18\x04 \x01(\tB\x03\xe0\x41\x01\x12;\n\x0chttp_request\x18\x07 \x01(\x0b\x32 .google.logging.type.HttpRequestB\x03\xe0\x41\x01\x12<\n\x06labels\x18\x0b \x03(\x0b\x32\'.google.logging.v2.LogEntry.LabelsEntryB\x03\xe0\x41\x01\x12<\n\toperation\x18\x0f \x01(\x0b\x32$.google.logging.v2.LogEntryOperationB\x03\xe0\x41\x01\x12\x12\n\x05trace\x18\x16 \x01(\tB\x03\xe0\x41\x01\x12\x14\n\x07span_id\x18\x1b \x01(\tB\x03\xe0\x41\x01\x12\x1a\n\rtrace_sampled\x18\x1e \x01(\x08\x42\x03\xe0\x41\x01\x12G\n\x0fsource_location\x18\x17 \x01(\x0b\x32).google.logging.v2.LogEntrySourceLocationB\x03\xe0\x41\x01\x12/\n\x05split\x18# \x01(\x0b\x32\x1b.google.logging.v2.LogSplitB\x03\xe0\x41\x01\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01:\xbd\x01\xea\x41\xb9\x01\n\x1alogging.googleapis.com/Log\x12\x1dprojects/{project}/logs/{log}\x12\'organizations/{organization}/logs/{log}\x12\x1b\x66olders/{folder}/logs/{log}\x12,billingAccounts/{billing_account}/logs/{log}\x1a\x08log_nameB\t\n\x07payload\"b\n\x11LogEntryOperation\x12\x0f\n\x02id\x18\x01 \x01(\tB\x03\xe0\x41\x01\x12\x15\n\x08producer\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x12\n\x05\x66irst\x18\x03 \x01(\x08\x42\x03\xe0\x41\x01\x12\x11\n\x04last\x18\x04 \x01(\x08\x42\x03\xe0\x41\x01\"U\n\x16LogEntrySourceLocation\x12\x11\n\x04\x66ile\x18\x01 \x01(\tB\x03\xe0\x41\x01\x12\x11\n\x04line\x18\x02 \x01(\x03\x42\x03\xe0\x41\x01\x12\x15\n\x08\x66unction\x18\x03 \x01(\tB\x03\xe0\x41\x01\"<\n\x08LogSplit\x12\x0b\n\x03uid\x18\x01 \x01(\t\x12\r\n\x05index\x18\x02 \x01(\x05\x12\x14\n\x0ctotal_splits\x18\x03 \x01(\x05\x42\xb3\x01\n\x15\x63om.google.logging.v2B\rLogEntryProtoP\x01Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\xf8\x01\x01\xaa\x02\x17Google.Cloud.Logging.V2\xca\x02\x17Google\\Cloud\\Logging\\V2\xea\x02\x1aGoogle::Cloud::Logging::V2b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.logging.v2.log_entry_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\025com.google.logging.v2B\rLogEntryProtoP\001Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\370\001\001\252\002\027Google.Cloud.Logging.V2\312\002\027Google\\Cloud\\Logging\\V2\352\002\032Google::Cloud::Logging::V2'
  _LOGENTRY_LABELSENTRY._options = None
  _LOGENTRY_LABELSENTRY._serialized_options = b'8\001'
  _LOGENTRY.fields_by_name['log_name']._options = None
  _LOGENTRY.fields_by_name['log_name']._serialized_options = b'\340A\002'
  _LOGENTRY.fields_by_name['resource']._options = None
  _LOGENTRY.fields_by_name['resource']._serialized_options = b'\340A\002'
  _LOGENTRY.fields_by_name['timestamp']._options = None
  _LOGENTRY.fields_by_name['timestamp']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['receive_timestamp']._options = None
  _LOGENTRY.fields_by_name['receive_timestamp']._serialized_options = b'\340A\003'
  _LOGENTRY.fields_by_name['severity']._options = None
  _LOGENTRY.fields_by_name['severity']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['insert_id']._options = None
  _LOGENTRY.fields_by_name['insert_id']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['http_request']._options = None
  _LOGENTRY.fields_by_name['http_request']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['labels']._options = None
  _LOGENTRY.fields_by_name['labels']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['operation']._options = None
  _LOGENTRY.fields_by_name['operation']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['trace']._options = None
  _LOGENTRY.fields_by_name['trace']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['span_id']._options = None
  _LOGENTRY.fields_by_name['span_id']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['trace_sampled']._options = None
  _LOGENTRY.fields_by_name['trace_sampled']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['source_location']._options = None
  _LOGENTRY.fields_by_name['source_location']._serialized_options = b'\340A\001'
  _LOGENTRY.fields_by_name['split']._options = None
  _LOGENTRY.fields_by_name['split']._serialized_options = b'\340A\001'
  _LOGENTRY._options = None
  _LOGENTRY._serialized_options = b'\352A\271\001\n\032logging.googleapis.com/Log\022\035projects/{project}/logs/{log}\022\'organizations/{organization}/logs/{log}\022\033folders/{folder}/logs/{log}\022,billingAccounts/{billing_account}/logs/{log}\032\010log_name'
  _LOGENTRYOPERATION.fields_by_name['id']._options = None
  _LOGENTRYOPERATION.fields_by_name['id']._serialized_options = b'\340A\001'
  _LOGENTRYOPERATION.fields_by_name['producer']._options = None
  _LOGENTRYOPERATION.fields_by_name['producer']._serialized_options = b'\340A\001'
  _LOGENTRYOPERATION.fields_by_name['first']._options = None
  _LOGENTRYOPERATION.fields_by_name['first']._serialized_options = b'\340A\001'
  _LOGENTRYOPERATION.fields_by_name['last']._options = None
  _LOGENTRYOPERATION.fields_by_name['last']._serialized_options = b'\340A\001'
  _LOGENTRYSOURCELOCATION.fields_by_name['file']._options = None
  _LOGENTRYSOURCELOCATION.fields_by_name['file']._serialized_options = b'\340A\001'
  _LOGENTRYSOURCELOCATION.fields_by_name['line']._options = None
  _LOGENTRYSOURCELOCATION.fields_by_name['line']._serialized_options = b'\340A\001'
  _LOGENTRYSOURCELOCATION.fields_by_name['function']._options = None
  _LOGENTRYSOURCELOCATION.fields_by_name['function']._serialized_options = b'\340A\001'
  _globals['_LOGENTRY']._serialized_start=324
  _globals['_LOGENTRY']._serialized_end=1351
  _globals['_LOGENTRY_LABELSENTRY']._serialized_start=1103
  _globals['_LOGENTRY_LABELSENTRY']._serialized_end=1148
  _globals['_LOGENTRYOPERATION']._serialized_start=1353
  _globals['_LOGENTRYOPERATION']._serialized_end=1451
  _globals['_LOGENTRYSOURCELOCATION']._serialized_start=1453
  _globals['_LOGENTRYSOURCELOCATION']._serialized_end=1538
  _globals['_LOGSPLIT']._serialized_start=1540
  _globals['_LOGSPLIT']._serialized_end=1600
