
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.servicecontrol.v1 import log_entry_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_log__entry__pb2
from google.api.servicecontrol.v1 import metric_value_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_metric__value__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,google/api/servicecontrol/v1/operation.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a,google/api/servicecontrol/v1/log_entry.proto\x1a/google/api/servicecontrol/v1/metric_value.proto\x1a\x19google/protobuf/any.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\xb9\x04\n\tOperation\x12\x14\n\x0coperation_id\x18\x01 \x01(\t\x12\x16\n\x0eoperation_name\x18\x02 \x01(\t\x12\x13\n\x0b\x63onsumer_id\x18\x03 \x01(\t\x12.\n\nstart_time\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12,\n\x08\x65nd_time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x43\n\x06labels\x18\x06 \x03(\x0b\x32\x33.google.api.servicecontrol.v1.Operation.LabelsEntry\x12G\n\x11metric_value_sets\x18\x07 \x03(\x0b\x32,.google.api.servicecontrol.v1.MetricValueSet\x12;\n\x0blog_entries\x18\x08 \x03(\x0b\x32&.google.api.servicecontrol.v1.LogEntry\x12\x46\n\nimportance\x18\x0b \x01(\x0e\x32\x32.google.api.servicecontrol.v1.Operation.Importance\x12(\n\nextensions\x18\x10 \x03(\x0b\x32\x14.google.protobuf.Any\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\x1f\n\nImportance\x12\x07\n\x03LOW\x10\x00\x12\x08\n\x04HIGH\x10\x01\x42\xe9\x01\n com.google.api.servicecontrol.v1B\x0eOperationProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xf8\x01\x01\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.operation_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\016OperationProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\370\001\001\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _OPERATION_LABELSENTRY._options = None
  _OPERATION_LABELSENTRY._serialized_options = b'8\001'
  _globals['_OPERATION']._serialized_start=234
  _globals['_OPERATION']._serialized_end=803
  _globals['_OPERATION_LABELSENTRY']._serialized_start=725
  _globals['_OPERATION_LABELSENTRY']._serialized_end=770
  _globals['_OPERATION_IMPORTANCE']._serialized_start=772
  _globals['_OPERATION_IMPORTANCE']._serialized_end=803
