
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.api import client_pb2 as google_dot_api_dot_client__pb2
from google.api import distribution_pb2 as google_dot_api_dot_distribution__pb2
from google.api import field_behavior_pb2 as google_dot_api_dot_field__behavior__pb2
from google.api import metric_pb2 as google_dot_api_dot_metric__pb2
from google.api import resource_pb2 as google_dot_api_dot_resource__pb2
from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'google/logging/v2/logging_metrics.proto\x12\x11google.logging.v2\x1a\x1cgoogle/api/annotations.proto\x1a\x17google/api/client.proto\x1a\x1dgoogle/api/distribution.proto\x1a\x1fgoogle/api/field_behavior.proto\x1a\x17google/api/metric.proto\x1a\x19google/api/resource.proto\x1a\x1bgoogle/protobuf/empty.proto\x1a\x1fgoogle/protobuf/timestamp.proto\"\xbd\x05\n\tLogMetric\x12\x11\n\x04name\x18\x01 \x01(\tB\x03\xe0\x41\x02\x12\x18\n\x0b\x64\x65scription\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x13\n\x06\x66ilter\x18\x03 \x01(\tB\x03\xe0\x41\x02\x12\x18\n\x0b\x62ucket_name\x18\r \x01(\tB\x03\xe0\x41\x01\x12\x15\n\x08\x64isabled\x18\x0c \x01(\x08\x42\x03\xe0\x41\x01\x12<\n\x11metric_descriptor\x18\x05 \x01(\x0b\x32\x1c.google.api.MetricDescriptorB\x03\xe0\x41\x01\x12\x1c\n\x0fvalue_extractor\x18\x06 \x01(\tB\x03\xe0\x41\x01\x12P\n\x10label_extractors\x18\x07 \x03(\x0b\x32\x31.google.logging.v2.LogMetric.LabelExtractorsEntryB\x03\xe0\x41\x01\x12\x43\n\x0e\x62ucket_options\x18\x08 \x01(\x0b\x32&.google.api.Distribution.BucketOptionsB\x03\xe0\x41\x01\x12\x34\n\x0b\x63reate_time\x18\t \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12\x34\n\x0bupdate_time\x18\n \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x03\xe0\x41\x03\x12<\n\x07version\x18\x04 \x01(\x0e\x32\'.google.logging.v2.LogMetric.ApiVersionB\x02\x18\x01\x1a\x36\n\x14LabelExtractorsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\x1c\n\nApiVersion\x12\x06\n\x02V2\x10\x00\x12\x06\n\x02V1\x10\x01:J\xea\x41G\n logging.googleapis.com/LogMetric\x12#projects/{project}/metrics/{metric}\"\x8d\x01\n\x15ListLogMetricsRequest\x12\x43\n\x06parent\x18\x01 \x01(\tB3\xe0\x41\x02\xfa\x41-\n+cloudresourcemanager.googleapis.com/Project\x12\x17\n\npage_token\x18\x02 \x01(\tB\x03\xe0\x41\x01\x12\x16\n\tpage_size\x18\x03 \x01(\x05\x42\x03\xe0\x41\x01\"`\n\x16ListLogMetricsResponse\x12-\n\x07metrics\x18\x01 \x03(\x0b\x32\x1c.google.logging.v2.LogMetric\x12\x17\n\x0fnext_page_token\x18\x02 \x01(\t\"T\n\x13GetLogMetricRequest\x12=\n\x0bmetric_name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogMetric\"\x85\x01\n\x16\x43reateLogMetricRequest\x12\x38\n\x06parent\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\x12 logging.googleapis.com/LogMetric\x12\x31\n\x06metric\x18\x02 \x01(\x0b\x32\x1c.google.logging.v2.LogMetricB\x03\xe0\x41\x02\"\x8a\x01\n\x16UpdateLogMetricRequest\x12=\n\x0bmetric_name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogMetric\x12\x31\n\x06metric\x18\x02 \x01(\x0b\x32\x1c.google.logging.v2.LogMetricB\x03\xe0\x41\x02\"W\n\x16\x44\x65leteLogMetricRequest\x12=\n\x0bmetric_name\x18\x01 \x01(\tB(\xe0\x41\x02\xfa\x41\"\n logging.googleapis.com/LogMetric2\xae\x08\n\x10MetricsServiceV2\x12\x97\x01\n\x0eListLogMetrics\x12(.google.logging.v2.ListLogMetricsRequest\x1a).google.logging.v2.ListLogMetricsResponse\"0\xda\x41\x06parent\x82\xd3\xe4\x93\x02!\x12\x1f/v2/{parent=projects/*}/metrics\x12\x92\x01\n\x0cGetLogMetric\x12&.google.logging.v2.GetLogMetricRequest\x1a\x1c.google.logging.v2.LogMetric\"<\xda\x41\x0bmetric_name\x82\xd3\xe4\x93\x02(\x12&/v2/{metric_name=projects/*/metrics/*}\x12\x9b\x01\n\x0f\x43reateLogMetric\x12).google.logging.v2.CreateLogMetricRequest\x1a\x1c.google.logging.v2.LogMetric\"?\xda\x41\rparent,metric\x82\xd3\xe4\x93\x02)\"\x1f/v2/{parent=projects/*}/metrics:\x06metric\x12\xa7\x01\n\x0fUpdateLogMetric\x12).google.logging.v2.UpdateLogMetricRequest\x1a\x1c.google.logging.v2.LogMetric\"K\xda\x41\x12metric_name,metric\x82\xd3\xe4\x93\x02\x30\x1a&/v2/{metric_name=projects/*/metrics/*}:\x06metric\x12\x92\x01\n\x0f\x44\x65leteLogMetric\x12).google.logging.v2.DeleteLogMetricRequest\x1a\x16.google.protobuf.Empty\"<\xda\x41\x0bmetric_name\x82\xd3\xe4\x93\x02(*&/v2/{metric_name=projects/*/metrics/*}\x1a\x8d\x02\xca\x41\x16logging.googleapis.com\xd2\x41\xf0\x01https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.read,https://www.googleapis.com/auth/logging.writeB\xb9\x01\n\x15\x63om.google.logging.v2B\x13LoggingMetricsProtoP\x01Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\xf8\x01\x01\xaa\x02\x17Google.Cloud.Logging.V2\xca\x02\x17Google\\Cloud\\Logging\\V2\xea\x02\x1aGoogle::Cloud::Logging::V2b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.logging.v2.logging_metrics_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\025com.google.logging.v2B\023LoggingMetricsProtoP\001Z5cloud.google.com/go/logging/apiv2/loggingpb;loggingpb\370\001\001\252\002\027Google.Cloud.Logging.V2\312\002\027Google\\Cloud\\Logging\\V2\352\002\032Google::Cloud::Logging::V2'
  _LOGMETRIC_LABELEXTRACTORSENTRY._options = None
  _LOGMETRIC_LABELEXTRACTORSENTRY._serialized_options = b'8\001'
  _LOGMETRIC.fields_by_name['name']._options = None
  _LOGMETRIC.fields_by_name['name']._serialized_options = b'\340A\002'
  _LOGMETRIC.fields_by_name['description']._options = None
  _LOGMETRIC.fields_by_name['description']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['filter']._options = None
  _LOGMETRIC.fields_by_name['filter']._serialized_options = b'\340A\002'
  _LOGMETRIC.fields_by_name['bucket_name']._options = None
  _LOGMETRIC.fields_by_name['bucket_name']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['disabled']._options = None
  _LOGMETRIC.fields_by_name['disabled']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['metric_descriptor']._options = None
  _LOGMETRIC.fields_by_name['metric_descriptor']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['value_extractor']._options = None
  _LOGMETRIC.fields_by_name['value_extractor']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['label_extractors']._options = None
  _LOGMETRIC.fields_by_name['label_extractors']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['bucket_options']._options = None
  _LOGMETRIC.fields_by_name['bucket_options']._serialized_options = b'\340A\001'
  _LOGMETRIC.fields_by_name['create_time']._options = None
  _LOGMETRIC.fields_by_name['create_time']._serialized_options = b'\340A\003'
  _LOGMETRIC.fields_by_name['update_time']._options = None
  _LOGMETRIC.fields_by_name['update_time']._serialized_options = b'\340A\003'
  _LOGMETRIC.fields_by_name['version']._options = None
  _LOGMETRIC.fields_by_name['version']._serialized_options = b'\030\001'
  _LOGMETRIC._options = None
  _LOGMETRIC._serialized_options = b'\352AG\n logging.googleapis.com/LogMetric\022#projects/{project}/metrics/{metric}'
  _LISTLOGMETRICSREQUEST.fields_by_name['parent']._options = None
  _LISTLOGMETRICSREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A-\n+cloudresourcemanager.googleapis.com/Project'
  _LISTLOGMETRICSREQUEST.fields_by_name['page_token']._options = None
  _LISTLOGMETRICSREQUEST.fields_by_name['page_token']._serialized_options = b'\340A\001'
  _LISTLOGMETRICSREQUEST.fields_by_name['page_size']._options = None
  _LISTLOGMETRICSREQUEST.fields_by_name['page_size']._serialized_options = b'\340A\001'
  _GETLOGMETRICREQUEST.fields_by_name['metric_name']._options = None
  _GETLOGMETRICREQUEST.fields_by_name['metric_name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogMetric'
  _CREATELOGMETRICREQUEST.fields_by_name['parent']._options = None
  _CREATELOGMETRICREQUEST.fields_by_name['parent']._serialized_options = b'\340A\002\372A\"\022 logging.googleapis.com/LogMetric'
  _CREATELOGMETRICREQUEST.fields_by_name['metric']._options = None
  _CREATELOGMETRICREQUEST.fields_by_name['metric']._serialized_options = b'\340A\002'
  _UPDATELOGMETRICREQUEST.fields_by_name['metric_name']._options = None
  _UPDATELOGMETRICREQUEST.fields_by_name['metric_name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogMetric'
  _UPDATELOGMETRICREQUEST.fields_by_name['metric']._options = None
  _UPDATELOGMETRICREQUEST.fields_by_name['metric']._serialized_options = b'\340A\002'
  _DELETELOGMETRICREQUEST.fields_by_name['metric_name']._options = None
  _DELETELOGMETRICREQUEST.fields_by_name['metric_name']._serialized_options = b'\340A\002\372A\"\n logging.googleapis.com/LogMetric'
  _METRICSSERVICEV2._options = None
  _METRICSSERVICEV2._serialized_options = b'\312A\026logging.googleapis.com\322A\360\001https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/cloud-platform.read-only,https://www.googleapis.com/auth/logging.admin,https://www.googleapis.com/auth/logging.read,https://www.googleapis.com/auth/logging.write'
  _METRICSSERVICEV2.methods_by_name['ListLogMetrics']._options = None
  _METRICSSERVICEV2.methods_by_name['ListLogMetrics']._serialized_options = b'\332A\006parent\202\323\344\223\002!\022\037/v2/{parent=projects/*}/metrics'
  _METRICSSERVICEV2.methods_by_name['GetLogMetric']._options = None
  _METRICSSERVICEV2.methods_by_name['GetLogMetric']._serialized_options = b'\332A\013metric_name\202\323\344\223\002(\022&/v2/{metric_name=projects/*/metrics/*}'
  _METRICSSERVICEV2.methods_by_name['CreateLogMetric']._options = None
  _METRICSSERVICEV2.methods_by_name['CreateLogMetric']._serialized_options = b'\332A\rparent,metric\202\323\344\223\002)\"\037/v2/{parent=projects/*}/metrics:\006metric'
  _METRICSSERVICEV2.methods_by_name['UpdateLogMetric']._options = None
  _METRICSSERVICEV2.methods_by_name['UpdateLogMetric']._serialized_options = b'\332A\022metric_name,metric\202\323\344\223\0020\032&/v2/{metric_name=projects/*/metrics/*}:\006metric'
  _METRICSSERVICEV2.methods_by_name['DeleteLogMetric']._options = None
  _METRICSSERVICEV2.methods_by_name['DeleteLogMetric']._serialized_options = b'\332A\013metric_name\202\323\344\223\002(*&/v2/{metric_name=projects/*/metrics/*}'
  _globals['_LOGMETRIC']._serialized_start=296
  _globals['_LOGMETRIC']._serialized_end=997
  _globals['_LOGMETRIC_LABELEXTRACTORSENTRY']._serialized_start=837
  _globals['_LOGMETRIC_LABELEXTRACTORSENTRY']._serialized_end=891
  _globals['_LOGMETRIC_APIVERSION']._serialized_start=893
  _globals['_LOGMETRIC_APIVERSION']._serialized_end=921
  _globals['_LISTLOGMETRICSREQUEST']._serialized_start=1000
  _globals['_LISTLOGMETRICSREQUEST']._serialized_end=1141
  _globals['_LISTLOGMETRICSRESPONSE']._serialized_start=1143
  _globals['_LISTLOGMETRICSRESPONSE']._serialized_end=1239
  _globals['_GETLOGMETRICREQUEST']._serialized_start=1241
  _globals['_GETLOGMETRICREQUEST']._serialized_end=1325
  _globals['_CREATELOGMETRICREQUEST']._serialized_start=1328
  _globals['_CREATELOGMETRICREQUEST']._serialized_end=1461
  _globals['_UPDATELOGMETRICREQUEST']._serialized_start=1464
  _globals['_UPDATELOGMETRICREQUEST']._serialized_end=1602
  _globals['_DELETELOGMETRICREQUEST']._serialized_start=1604
  _globals['_DELETELOGMETRICREQUEST']._serialized_end=1691
  _globals['_METRICSSERVICEV2']._serialized_start=1694
  _globals['_METRICSSERVICEV2']._serialized_end=2764
