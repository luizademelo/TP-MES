
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.servicecontrol.v1 import http_request_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_http__request__pb2
from google.logging.type import log_severity_pb2 as google_dot_logging_dot_type_dot_log__severity__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,google/api/servicecontrol/v1/log_entry.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a/google/api/servicecontrol/v1/http_request.proto\x1a&google/logging/type/log_severity.proto\x1a\x19google/protobuf/any.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\xe9\x04\n\x08LogEntry\x12\x0c\n\x04name\x18\n \x01(\t\x12-\n\ttimestamp\x18\x0b \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x32\n\x08severity\x18\x0c \x01(\x0e\x32 .google.logging.type.LogSeverity\x12?\n\x0chttp_request\x18\x0e \x01(\x0b\x32).google.api.servicecontrol.v1.HttpRequest\x12\r\n\x05trace\x18\x0f \x01(\t\x12\x11\n\tinsert_id\x18\x04 \x01(\t\x12\x42\n\x06labels\x18\r \x03(\x0b\x32\x32.google.api.servicecontrol.v1.LogEntry.LabelsEntry\x12-\n\rproto_payload\x18\x02 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x12\x16\n\x0ctext_payload\x18\x03 \x01(\tH\x00\x12\x31\n\x0estruct_payload\x18\x06 \x01(\x0b\x32\x17.google.protobuf.StructH\x00\x12\x42\n\toperation\x18\x10 \x01(\x0b\x32/.google.api.servicecontrol.v1.LogEntryOperation\x12M\n\x0fsource_location\x18\x11 \x01(\x0b\x32\x34.google.api.servicecontrol.v1.LogEntrySourceLocation\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x42\t\n\x07payload\"N\n\x11LogEntryOperation\x12\n\n\x02id\x18\x01 \x01(\t\x12\x10\n\x08producer\x18\x02 \x01(\t\x12\r\n\x05\x66irst\x18\x03 \x01(\x08\x12\x0c\n\x04last\x18\x04 \x01(\x08\"F\n\x16LogEntrySourceLocation\x12\x0c\n\x04\x66ile\x18\x01 \x01(\t\x12\x0c\n\x04line\x18\x02 \x01(\x03\x12\x10\n\x08\x66unction\x18\x03 \x01(\tB\xe5\x01\n com.google.api.servicecontrol.v1B\rLogEntryProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.log_entry_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\rLogEntryProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _LOGENTRY_LABELSENTRY._options = None
  _LOGENTRY_LABELSENTRY._serialized_options = b'8\001'
  _globals['_LOGENTRY']._serialized_start=258
  _globals['_LOGENTRY']._serialized_end=875
  _globals['_LOGENTRY_LABELSENTRY']._serialized_start=819
  _globals['_LOGENTRY_LABELSENTRY']._serialized_end=864
  _globals['_LOGENTRYOPERATION']._serialized_start=877
  _globals['_LOGENTRYOPERATION']._serialized_end=955
  _globals['_LOGENTRYSOURCELOCATION']._serialized_start=957
  _globals['_LOGENTRYSOURCELOCATION']._serialized_end=1027
