
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from opencensus.proto.resource.v1 import resource_pb2 as opencensus_dot_proto_dot_resource_dot_v1_dot_resource__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)opencensus/proto/metrics/v1/metrics.proto\x12\x1bopencensus.proto.metrics.v1\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a+opencensus/proto/resource/v1/resource.proto\"\xc9\x01\n\x06Metric\x12H\n\x11metric_descriptor\x18\x01 \x01(\x0b\x32-.opencensus.proto.metrics.v1.MetricDescriptor\x12;\n\ntimeseries\x18\x02 \x03(\x0b\x32\'.opencensus.proto.metrics.v1.TimeSeries\x12\x38\n\x08resource\x18\x03 \x01(\x0b\x32&.opencensus.proto.resource.v1.Resource\"\xec\x02\n\x10MetricDescriptor\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\x12\x0c\n\x04unit\x18\x03 \x01(\t\x12@\n\x04type\x18\x04 \x01(\x0e\x32\x32.opencensus.proto.metrics.v1.MetricDescriptor.Type\x12\x39\n\nlabel_keys\x18\x05 \x03(\x0b\x32%.opencensus.proto.metrics.v1.LabelKey\"\xa9\x01\n\x04Type\x12\x0f\n\x0bUNSPECIFIED\x10\x00\x12\x0f\n\x0bGAUGE_INT64\x10\x01\x12\x10\n\x0cGAUGE_DOUBLE\x10\x02\x12\x16\n\x12GAUGE_DISTRIBUTION\x10\x03\x12\x14\n\x10\x43UMULATIVE_INT64\x10\x04\x12\x15\n\x11\x43UMULATIVE_DOUBLE\x10\x05\x12\x1b\n\x17\x43UMULATIVE_DISTRIBUTION\x10\x06\x12\x0b\n\x07SUMMARY\x10\x07\",\n\x08LabelKey\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\"\xb4\x01\n\nTimeSeries\x12\x33\n\x0fstart_timestamp\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12=\n\x0clabel_values\x18\x02 \x03(\x0b\x32\'.opencensus.proto.metrics.v1.LabelValue\x12\x32\n\x06points\x18\x03 \x03(\x0b\x32\".opencensus.proto.metrics.v1.Point\".\n\nLabelValue\x12\r\n\x05value\x18\x01 \x01(\t\x12\x11\n\thas_value\x18\x02 \x01(\x08\"\x80\x02\n\x05Point\x12-\n\ttimestamp\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x15\n\x0bint64_value\x18\x02 \x01(\x03H\x00\x12\x16\n\x0c\x64ouble_value\x18\x03 \x01(\x01H\x00\x12L\n\x12\x64istribution_value\x18\x04 \x01(\x0b\x32..opencensus.proto.metrics.v1.DistributionValueH\x00\x12\x42\n\rsummary_value\x18\x05 \x01(\x0b\x32).opencensus.proto.metrics.v1.SummaryValueH\x00\x42\x07\n\x05value\"\xc2\x05\n\x11\x44istributionValue\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12\x0b\n\x03sum\x18\x02 \x01(\x01\x12 \n\x18sum_of_squared_deviation\x18\x03 \x01(\x01\x12T\n\x0e\x62ucket_options\x18\x04 \x01(\x0b\x32<.opencensus.proto.metrics.v1.DistributionValue.BucketOptions\x12\x46\n\x07\x62uckets\x18\x05 \x03(\x0b\x32\x35.opencensus.proto.metrics.v1.DistributionValue.Bucket\x1a\x8e\x01\n\rBucketOptions\x12Y\n\x08\x65xplicit\x18\x01 \x01(\x0b\x32\x45.opencensus.proto.metrics.v1.DistributionValue.BucketOptions.ExplicitH\x00\x1a\x1a\n\x08\x45xplicit\x12\x0e\n\x06\x62ounds\x18\x01 \x03(\x01\x42\x06\n\x04type\x1a\x62\n\x06\x42ucket\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12I\n\x08\x65xemplar\x18\x02 \x01(\x0b\x32\x37.opencensus.proto.metrics.v1.DistributionValue.Exemplar\x1a\xdb\x01\n\x08\x45xemplar\x12\r\n\x05value\x18\x01 \x01(\x01\x12-\n\ttimestamp\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12]\n\x0b\x61ttachments\x18\x03 \x03(\x0b\x32H.opencensus.proto.metrics.v1.DistributionValue.Exemplar.AttachmentsEntry\x1a\x32\n\x10\x41ttachmentsEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\"\xa8\x03\n\x0cSummaryValue\x12*\n\x05\x63ount\x18\x01 \x01(\x0b\x32\x1b.google.protobuf.Int64Value\x12)\n\x03sum\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.DoubleValue\x12\x44\n\x08snapshot\x18\x03 \x01(\x0b\x32\x32.opencensus.proto.metrics.v1.SummaryValue.Snapshot\x1a\xfa\x01\n\x08Snapshot\x12*\n\x05\x63ount\x18\x01 \x01(\x0b\x32\x1b.google.protobuf.Int64Value\x12)\n\x03sum\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.DoubleValue\x12_\n\x11percentile_values\x18\x03 \x03(\x0b\x32\x44.opencensus.proto.metrics.v1.SummaryValue.Snapshot.ValueAtPercentile\x1a\x36\n\x11ValueAtPercentile\x12\x12\n\npercentile\x18\x01 \x01(\x01\x12\r\n\x05value\x18\x02 \x01(\x01\x42\x94\x01\n\x1eio.opencensus.proto.metrics.v1B\x0cMetricsProtoP\x01ZDgithub.com/census-instrumentation/opencensus-proto/gen-go/metrics/v1\xea\x02\x1bOpenCensus.Proto.Metrics.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.metrics.v1.metrics_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036io.opencensus.proto.metrics.v1B\014MetricsProtoP\001ZDgithub.com/census-instrumentation/opencensus-proto/gen-go/metrics/v1\352\002\033OpenCensus.Proto.Metrics.V1'
  _DISTRIBUTIONVALUE_EXEMPLAR_ATTACHMENTSENTRY._options = None
  _DISTRIBUTIONVALUE_EXEMPLAR_ATTACHMENTSENTRY._serialized_options = b'8\001'
  _globals['_METRIC']._serialized_start=185
  _globals['_METRIC']._serialized_end=386
  _globals['_METRICDESCRIPTOR']._serialized_start=389
  _globals['_METRICDESCRIPTOR']._serialized_end=753
  _globals['_METRICDESCRIPTOR_TYPE']._serialized_start=584
  _globals['_METRICDESCRIPTOR_TYPE']._serialized_end=753
  _globals['_LABELKEY']._serialized_start=755
  _globals['_LABELKEY']._serialized_end=799
  _globals['_TIMESERIES']._serialized_start=802
  _globals['_TIMESERIES']._serialized_end=982
  _globals['_LABELVALUE']._serialized_start=984
  _globals['_LABELVALUE']._serialized_end=1030
  _globals['_POINT']._serialized_start=1033
  _globals['_POINT']._serialized_end=1289
  _globals['_DISTRIBUTIONVALUE']._serialized_start=1292
  _globals['_DISTRIBUTIONVALUE']._serialized_end=1998
  _globals['_DISTRIBUTIONVALUE_BUCKETOPTIONS']._serialized_start=1534
  _globals['_DISTRIBUTIONVALUE_BUCKETOPTIONS']._serialized_end=1676
  _globals['_DISTRIBUTIONVALUE_BUCKETOPTIONS_EXPLICIT']._serialized_start=1642
  _globals['_DISTRIBUTIONVALUE_BUCKETOPTIONS_EXPLICIT']._serialized_end=1668
  _globals['_DISTRIBUTIONVALUE_BUCKET']._serialized_start=1678
  _globals['_DISTRIBUTIONVALUE_BUCKET']._serialized_end=1776
  _globals['_DISTRIBUTIONVALUE_EXEMPLAR']._serialized_start=1779
  _globals['_DISTRIBUTIONVALUE_EXEMPLAR']._serialized_end=1998
  _globals['_DISTRIBUTIONVALUE_EXEMPLAR_ATTACHMENTSENTRY']._serialized_start=1948
  _globals['_DISTRIBUTIONVALUE_EXEMPLAR_ATTACHMENTSENTRY']._serialized_end=1998
  _globals['_SUMMARYVALUE']._serialized_start=2001
  _globals['_SUMMARYVALUE']._serialized_end=2425
  _globals['_SUMMARYVALUE_SNAPSHOT']._serialized_start=2175
  _globals['_SUMMARYVALUE_SNAPSHOT']._serialized_end=2425
  _globals['_SUMMARYVALUE_SNAPSHOT_VALUEATPERCENTILE']._serialized_start=2371
  _globals['_SUMMARYVALUE_SNAPSHOT_VALUEATPERCENTILE']._serialized_end=2425
