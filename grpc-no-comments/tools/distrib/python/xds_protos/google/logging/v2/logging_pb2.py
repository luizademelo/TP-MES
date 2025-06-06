
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import monitored_resource_pb2 as google_dot_api_dot_monitored__resource__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.logging.v2 import log_entry_pb2 as google_dot_logging_dot_v2_dot_log__entry__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1fgoogle/logging/v2/logging.proto\x12\x11google.logging.v2\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a#google/api/monitored_resource.proto\x1a\x19google/api/resource.proto\x1a!google/logging/v2/log_entry.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x17google/rpc/status.proto\"H\n\x10\x44\x65leteLogRequest\x12\x34\n\x08log_name\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\n\x1alogging.googleapis.com/Log\"\xe6\x02\n\x16WriteLogEntriesRequest\x12\x34\n\x08log_name\x18\x01 \x01(\tB\"\xe0\x41\x01\xfa\x41\x1c\n\x1alogging.googleapis.com/Log\x12\x34\n\x08resource\x18\x02 \x01(\x0b\x32\x1d.google.api.MonitoredResourceB\x03\xe0\x41\x01\x12J\n\x06labels\x18\x03 \x03(\x0b\x32\x35.google.logging.v2.WriteLogEntriesRequest.LabelsEntryB\x03\xe0\x41\x01\x12\x31\n\x07\x65ntries\x18\x04 \x03(\x0b\x32\x1b.google.logging.v2.LogEntryB\x03\xe0\x41\x02\x12\x1c\n\x0fpartial_success\x18\x05 \x01(\x08\x42\x03\xe0\x41\x01\x12\x14\n\x07\x64ry_run\x18\x06 \x01(\x08\x42\x03\xe0\x41\x01\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\x19\n\x17WriteLogEntriesResponse\"\xc8\x01\n\x1cWriteLogEntriesPartialErrors\x12]\n\x10log_entry_errors\x18\x01 \x03(\x0b\x32\x43.google.logging.v2.WriteLogEntriesPartialErrors.LogEntryErrorsEntry\x1aI\n\x13LogEntryErrorsEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12!\n\x05value\x18\x02 \x01(\x0b\x32\x12.google.rpc.Status:\x02\x38\x01\"\xb0\x01\n\x15ListLogEntriesRequest\x12:\n\x0eresource_names\x18\x08 \x03(\tB\"\xe0\x41\x02\xfa\x41\x1c\x12\x1alogging.googleapis.com/Log\x12\x13\n\x06\x66ilter\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x15\n\x08order_by\x18\x03 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x04 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x05 \x01(\tB\x03\xe0\x41\x01\"_\n\x16ListLogEntriesResponse\x12,\n\x07\x65ntries\x18\x01 \x03(\x0b\x32\x1b.google.logging.v2.LogEntry\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"Z\n\'ListMonitoredResourceDescriptorsRequest\x12\x16\n\tpage_size\x18\x01 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\"\x8a\x01\n(ListMonitoredResourceDescriptorsResponse\x12\x45\n\x14resource_descriptors\x18\x01 \x03(\x0b\x32\'.google.api.MonitoredResourceDescriptor\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"\xb2\x01\n\x0fListLogsRequest\x12\x32\n\x06parent\x18\x01 \x01(\tB\"\xe0\x41\x02\xfa\x41\x1c\x12\x1alogging.googleapis.com/Log\x12:\n\x0eresource_names\x18\x08 \x03(\tB\"\xe0\x41\x01\xfa\x41\x1c\x12\x1alogging.googleapis.com/Log\x12\x16\n\tpage_size\x18\x02 \x01(\x05\x42\x03\xe0\x41\x01\x12\x17\n\npage_token\x18\x03 \x01(\tB\x03\xe0\x41\x01\">\n\x10ListLogsResponse\x12\x11\n\tlog_names\x18\x03 \x03(\t\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"\x80\x01\n\x15TailLogEntriesRequest\x12\x1b\n\x0eresource_names\x18\x01 \x03(\tB\x03\xe0\x41\x02\x12\x13\n\x06\x66ilter\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x35\n\rbuffer_window\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\x03\xe0\x41\x01\"\xdf\x02\n\x16TailLogEntriesResponse\x12,\n\x07\x65ntries\x18\x01 \x03(\x0b\x32\x1b.google.logging.v2.LogEntry\x12S\n\x10suppression_info\x18\x02 \x03(\x0b\x32\x39.google.logging.v2.TailLogEntriesResponse.SuppressionInfo\x1a\xc1\x01\n\x0fSuppressionInfo\x12P\n\x06reason\x18\x01 \x01(\x0e\x32@.google.logging.v2.TailLogEntriesResponse.SuppressionInfo.Reason\x12\x18\n\x10suppressed_count\x18\x02 \x01(\x05\"B\n\x06Reason\x12\x16\n\x12REASON_UNSPECIFIED\x10\x00\x12\x0e\n\nRATE_LIMIT\x10\x01\x12\x10\n\x0cNOT_CONSUMED\x10\x02\x32\xe9\r\n\x10LoggingServiceV2\x12\x93\x02\n\tDeleteLog\x12#.google.logging.v2.DeleteLogRequest\x1a\x16.google.protobuf.Empty\"\xc8\x01\xda\x41\x08log_name\x82\xd3\xe4\x93\x02\xb6\x01* /v2/{log_name=projects/*/logs/*}Z\x1b*\x19/v2/{log_name=*/*/logs/*}Z\'*%/v2/{log_name=organizations/*/logs/*}Z!*\x1f/v2/{log_name=folders/*/logs/*}Z)*\'/v2/{log_name=billingAccounts/*/logs/*}\x12\xa9\x01\n\x0fWriteLogEntries\x12).google.logging.v2.WriteLogEntriesRequest\x1a*.google.logging.v2.WriteLogEntriesResponse\"?\xda\x41 log_name,resource,labels,entries\x82\xd3\xe4\x93\x02\x16\"\x11/v2/entries:write:\x01*\x12\xa3\x01\n\x0eListLogEntries\x12(.google.logging.v2.ListLogEntriesRequest\x1a).google.logging.v2.ListLogEntriesResponse\"<\xda\x41\x1eresource_names,filter,order_by\x82\xd3\xe4\x93\x02\x15\"\x10/v2/entries:list:\x01*\x12\xc5\x01\n ListMonitoredResourceDescriptors\x12:.google.logging.v2.ListMonitoredResourceDescriptorsRequest\x1a;.google.logging.v2.ListMonitoredResourceDescriptorsResponse\"(\x82\xd3\xe4\x93\x02\"\x12 /v2/monitoredResourceDescriptors\x12\x8b\x04\n\x08ListLogs\x12\".google.logging.v2.ListLogsRequest\x1a#.google.logging.v2.ListLogsResponse\"\xb5\x03\xda\x41\x06parent\x82\xd3\xe4\x93\x02\xa5\x03\x12\x15/v2/{parent=*/*}/logsZ\x1e\x12\x1c/v2/{parent=projects/*}/logsZ#\x12!/v2/{parent=organizations/*}/logsZ\x1d\x12\x1b/v2/{parent=folders/*}/logsZ%\x12#/v2/{parent=billingAccounts/*}/logsZ<\x12:/v2/{parent=projects/*/locations/*/buckets/*/views/*}/logsZA\x12?/v2/{parent=organizations/*/locations/*/buckets/*/views/*}/logsZ;\x12\x39/v2/{parent=folders/*/locations/*/buckets/*/views/*}/logsZC\x12\x41/v2/{parent=billingAccounts/*/locations/*/buckets/*/views/*}/logs\x12\x86\x01\n\x0eTailLogEntries\x12(.google.logging.v2.TailLogEntriesRequest\x1a).google.logging.v2.TailLogEntriesResponse\"\x1b\x82\xd3\xe4\x93\x02\x15\"\x10/v2/entries:tail:\x01*(\x01\x30\x01\x1a\x8d\x02\xca\x41\x16logging.googleapis.com\xd2\x41\xf0\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.read,https://www.googleapis.com/auth/logging.writeB\xb2\x01\n\x15\x63om.google.logging.v2B\x0cLoggingProtoP\x01Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\xf8\x01\x01\xaa\x02\x17Google.Cloud.Logging.V2\xca\x02\x17Google\\Cloud\\Logging\\V2\xea\x02\x1aGoogle::Cloud::Logging::V2b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.logging.v2.logging_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\025com.google.logging.v2B\014LoggingProtoP\001Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\370\001\001\252\002\027Google.Cloud.Logging.V2\312\002\027Google\\Cloud\\Logging\\V2\352\002\032Google::Cloud::Logging::V2'
  _DELETELOGREQUEST.fields_by_name['log_name']._options = None
  _DELETELOGREQUEST.fields_by_name['log_name']._serialized_options = b'\340A\002\372A\034\n\032logging.googleapis.com/Log'
  _WRITELOGENTRIESREQUEST_LABELSENTRY._options = None
  _WRITELOGENTRIESREQUEST_LABELSENTRY._serialized_options = b'8\001'
  _WRITELOGENTRIESREQUEST.fields_by_name['log_name']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['log_name']._serialized_options = b'\340A\001\372A\034\n\032logging.googleapis.com/Log'
  _WRITELOGENTRIESREQUEST.fields_by_name['resource']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['resource']._serialized_options = b'\340A\001'
  _WRITELOGENTRIESREQUEST.fields_by_name['labels']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['labels']._serialized_options = b'\340A\001'
  _WRITELOGENTRIESREQUEST.fields_by_name['entries']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['entries']._serialized_options = b'\340A\002'
  _WRITELOGENTRIESREQUEST.fields_by_name['partial_success']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['partial_success']._serialized_options = b'\340A\001'
  _WRITELOGENTRIESREQUEST.fields_by_name['dry_run']._options = None
  _WRITELOGENTRIESREQUEST.fields_by_name['dry_run']._serialized_options = b'\340A\001'
  _WRITELOGENTRIESPARTIALERRORS_LOGENTRYERRORSENTRY._options = None
  _WRITELOGENTRIESPARTIALERRORS_LOGENTRYERRORSENTRY._serialized_options = b'8\001'
  _LISTLOGENTRIESREQUEST.fields_by_name['resource_names']._options = None
  _LISTLOGENTRIESREQUEST.fields_by_name['resource_names']._serialized_options = b'\340A\002\372A\034\022\032logging.googleapis.com/Log'
  _LISTLOGENTRIESREQUEST.fields_by_name['filter']._options = None
  _LISTLOGENTRIESREQUEST.fields_by_name['filter']._serialized_options = b'\340A\001'
  _LISTLOGENTRIESREQUEST.fields_by_name['order_by']._options = None
  _LISTLOGENTRIESREQUEST.fields_by_name['order_by']._serialized_options = b'\340A\001'
  _LISTLOGENTRIESREQUEST.fields_by_name['page_size']._options = None
  _LISTLOGENTRIESREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTLOGENTRIESREQUEST.fields_by_name['page_token']._options = None
  _LISTLOGENTRIESREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTMONITOREDRESOURCEDESCRIPTORSREQUEST.fields_by_name['page_size']._options = None
  _LISTMONITOREDRESOURCEDESCRIPTORSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTMONITOREDRESOURCEDESCRIPTORSREQUEST.fields_by_name['page_token']._options = None
  _LISTMONITOREDRESOURCEDESCRIPTORSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTLOGSREQUEST.fields_by_name['parent']._options = None
  _LISTLOGSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\034\022\032logging.googleapis.com/Log'
  _LISTLOGSREQUEST.fields_by_name['resource_names']._options = None
  _LISTLOGSREQUEST.fields_by_name['resource_names']._serialized_options = b'\340A\001\372A\034\022\032logging.googleapis.com/Log'
  _LISTLOGSREQUEST.fields_by_name['page_size']._options = None
  _LISTLOGSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _LISTLOGSREQUEST.fields_by_name['page_token']._options = None
  _LISTLOGSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _TAILLOGENTRIESREQUEST.fields_by_name['resource_names']._options = None
  _TAILLOGENTRIESREQUEST.fields_by_name['resource_names']._serialized_options = b'\340A\002'
  _TAILLOGENTRIESREQUEST.fields_by_name['filter']._options = None
  _TAILLOGENTRIESREQUEST.fields_by_name['filter']._serialized_options = b'\340A\001'
  _TAILLOGENTRIESREQUEST.fields_by_name['buffer_window']._options = None
  _TAILLOGENTRIESREQUEST.fields_by_name['buffer_window']._serialized_options = b'\340A\001'
  _LOGGINGSERVICEV2._options = None
  _LOGGINGSERVICEV2._serialized_options = b'\312A\026logging.googleapis.com\322A\360\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.read,https://www.googleapis.com/auth/logging.write'
  _LOGGINGSERVICEV2.methods_by_name['DeleteLog']._options = None
  _LOGGINGSERVICEV2.methods_by_name['DeleteLog']._serialized_options = b'\332A\010log_name\202\323\344\223\002\266\001* /v2/{log_name=projects/*/logs/*}Z\033*\031/v2/{log_name=*/*/logs/*}Z\'*%/v2/{log_name=organizations/*/logs/*}Z!*\037/v2/{log_name=folders/*/logs/*}Z)*\'/v2/{log_name=billingAccounts/*/logs/*}'
  _LOGGINGSERVICEV2.methods_by_name['WriteLogEntries']._options = None
  _LOGGINGSERVICEV2.methods_by_name['WriteLogEntries']._serialized_options = b'\332A log_name,resource,labels,entries\202\323\344\223\002\026\"\021/v2/entries:write:\001*'
  _LOGGINGSERVICEV2.methods_by_name['ListLogEntries']._options = None
  _LOGGINGSERVICEV2.methods_by_name['ListLogEntries']._serialized_options = b'\332A\036resource_names,filter,order_by\202\323\344\223\002\025\"\020/v2/entries:list:\001*'
  _LOGGINGSERVICEV2.methods_by_name['ListMonitoredResourceDescriptors']._options = None
  _LOGGINGSERVICEV2.methods_by_name['ListMonitoredResourceDescriptors']._serialized_options = b'\202\323\344\223\002\"\022 /v2/monitoredResourceDescriptors'
  _LOGGINGSERVICEV2.methods_by_name['ListLogs']._options = None
  _LOGGINGSERVICEV2.methods_by_name['ListLogs']._serialized_options = b'\332A\006parent\202\323\344\223\002\245\003\022\025/v2/{parent=*/*}/logsZ\036\022\034/v2/{parent=projects/*}/logsZ#\022!/v2/{parent=organizations/*}/logsZ\035\022\033/v2/{parent=folders/*}/logsZ%\022#/v2/{parent=billingAccounts/*}/logsZ<\022:/v2/{parent=projects/*/locations/*/buckets/*/views/*}/logsZA\022?/v2/{parent=organizations/*/locations/*/buckets/*/views/*}/logsZ;\0229/v2/{parent=folders/*/locations/*/buckets/*/views/*}/logsZC\022A/v2/{parent=billingAccounts/*/locations/*/buckets/*/views/*}/logs'
  _LOGGINGSERVICEV2.methods_by_name['TailLogEntries']._options = None
  _LOGGINGSERVICEV2.methods_by_name['TailLogEntries']._serialized_options = b'\202\323\344\223\002\025\"\020/v2/entries:tail:\001*'
  _globals['_DELETELOGREQUEST']._serialized_start=327
  _globals['_DELETELOGREQUEST']._serialized_end=399
  _globals['_WRITELOGENTRIESREQUEST']._serialized_start=402
  _globals['_WRITELOGENTRIESREQUEST']._serialized_end=760
  _globals['_WRITELOGENTRIESREQUEST_LABELSENTRY']._serialized_start=715
  _globals['_WRITELOGENTRIESREQUEST_LABELSENTRY']._serialized_end=760
  _globals['_WRITELOGENTRIESRESPONSE']._serialized_start=762
  _globals['_WRITELOGENTRIESRESPONSE']._serialized_end=787
  _globals['_WRITELOGENTRIESPARTIALERRORS']._serialized_start=790
  _globals['_WRITELOGENTRIESPARTIALERRORS']._serialized_end=990
  _globals['_WRITELOGENTRIESPARTIALERRORS_LOGENTRYERRORSENTRY']._serialized_start=917
  _globals['_WRITELOGENTRIESPARTIALERRORS_LOGENTRYERRORSENTRY']._serialized_end=990
  _globals['_LISTLOGENTRIESREQUEST']._serialized_start=993
  _globals['_LISTLOGENTRIESREQUEST']._serialized_end=1169
  _globals['_LISTLOGENTRIESRESPONSE']._serialized_start=1171
  _globals['_LISTLOGENTRIESRESPONSE']._serialized_end=1266
  _globals['_LISTMONITOREDRESOURCEDESCRIPTORSREQUEST']._serialized_start=1268
  _globals['_LISTMONITOREDRESOURCEDESCRIPTORSREQUEST']._serialized_end=1358
  _globals['_LISTMONITOREDRESOURCEDESCRIPTORSRESPONSE']._serialized_start=1361
  _globals['_LISTMONITOREDRESOURCEDESCRIPTORSRESPONSE']._serialized_end=1499
  _globals['_LISTLOGSREQUEST']._serialized_start=1502
  _globals['_LISTLOGSREQUEST']._serialized_end=1680
  _globals['_LISTLOGSRESPONSE']._serialized_start=1682
  _globals['_LISTLOGSRESPONSE']._serialized_end=1744
  _globals['_TAILLOGENTRIESREQUEST']._serialized_start=1747
  _globals['_TAILLOGENTRIESREQUEST']._serialized_end=1875
  _globals['_TAILLOGENTRIESRESPONSE']._serialized_start=1878
  _globals['_TAILLOGENTRIESRESPONSE']._serialized_end=2229
  _globals['_TAILLOGENTRIESRESPONSE_SUPPRESSIONINFO']._serialized_start=2036
  _globals['_TAILLOGENTRIESRESPONSE_SUPPRESSIONINFO']._serialized_end=2229
  _globals['_TAILLOGENTRIESRESPONSE_SUPPRESSIONINFO_REASON']._serialized_start=2163
  _globals['_TAILLOGENTRIESRESPONSE_SUPPRESSIONINFO_REASON']._serialized_end=2229
  _globals['_LOGGINGSERVICEV2']._serialized_start=2232
  _globals['_LOGGINGSERVICEV2']._serialized_end=4001
