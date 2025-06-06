
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api.servicecontrol.v1 import distribution_pb2 as google_dot_api_dot_servicecontrol_dot_v1_dot_distribution__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/google/api/servicecontrol/v1/metric_value.proto\x12\x1cgoogle.api.servicecontrol.v1\x1a/google/api/servicecontrol/v1/distribution.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\x91\x03\n\x0bMetricValue\x12\x45\n\x06labels\x18\x01 \x03(\x0b\x32\x35.google.api.servicecontrol.v1.MetricValue.LabelsEntry\x12.\n\nstart_time\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12,\n\x08\x65nd_time\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x14\n\nbool_value\x18\x04 \x01(\x08H\x00\x12\x15\n\x0bint64_value\x18\x05 \x01(\x03H\x00\x12\x16\n\x0c\x64ouble_value\x18\x06 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x07 \x01(\tH\x00\x12H\n\x12\x64istribution_value\x18\x08 \x01(\x0b\x32*.google.api.servicecontrol.v1.DistributionH\x00\x1a-\n\x0bLabelsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x42\x07\n\x05value\"g\n\x0eMetricValueSet\x12\x13\n\x0bmetric_name\x18\x01 \x01(\t\x12@\n\rmetric_values\x18\x02 \x03(\x0b\x32).google.api.servicecontrol.v1.MetricValueB\xee\x01\n com.google.api.servicecontrol.v1B\x13MetricValueSetProtoP\x01ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\xf8\x01\x01\xaa\x02\x1eGoogle.Cloud.ServiceControl.V1\xca\x02\x1eGoogle\\Cloud\\ServiceControl\\V1\xea\x02!Google::Cloud::ServiceControl::V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.servicecontrol.v1.metric_value_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n com.google.api.servicecontrol.v1B\023MetricValueSetProtoP\001ZJcloud.google.com/go/servicecontrol/apiv1/servicecontrolpb;servicecontrolpb\370\001\001\252\002\036Google.Cloud.ServiceControl.V1\312\002\036Google\\Cloud\\ServiceControl\\V1\352\002!Google::Cloud::ServiceControl::V1'
  _METRICVALUE_LABELSENTRY._options = None
  _METRICVALUE_LABELSENTRY._serialized_options = b'8\001'
  _globals['_METRICVALUE']._serialized_start=164
  _globals['_METRICVALUE']._serialized_end=565
  _globals['_METRICVALUE_LABELSENTRY']._serialized_start=511
  _globals['_METRICVALUE_LABELSENTRY']._serialized_end=556
  _globals['_METRICVALUESET']._serialized_start=567
  _globals['_METRICVALUESET']._serialized_end=670
