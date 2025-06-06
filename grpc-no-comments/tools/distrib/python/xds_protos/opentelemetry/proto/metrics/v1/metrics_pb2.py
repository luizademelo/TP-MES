
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from opentelemetry.proto.common.v1 import common_pb2 as opentelemetry_dot_proto_dot_common_dot_v1_dot_common__pb2
from opentelemetry.proto.resource.v1 import resource_pb2 as opentelemetry_dot_proto_dot_resource_dot_v1_dot_resource__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,opentelemetry/proto/metrics/v1/metrics.proto\x12\x1eopentelemetry.proto.metrics.v1\x1a*opentelemetry/proto/common/v1/common.proto\x1a.opentelemetry/proto/resource/v1/resource.proto\"\xca\x01\n\x0fResourceMetrics\x12;\n\x08resource\x18\x01 \x01(\x0b\x32).opentelemetry.proto.resource.v1.Resource\x12\x66\n\x1finstrumentation_library_metrics\x18\x02 \x03(\x0b\x32=.opentelemetry.proto.metrics.v1.InstrumentationLibraryMetrics\x12\x12\n\nschema_url\x18\x03 \x01(\t\"\xc4\x01\n\x1dInstrumentationLibraryMetrics\x12V\n\x17instrumentation_library\x18\x01 \x01(\x0b\x32\x35.opentelemetry.proto.common.v1.InstrumentationLibrary\x12\x37\n\x07metrics\x18\x02 \x03(\x0b\x32&.opentelemetry.proto.metrics.v1.Metric\x12\x12\n\nschema_url\x18\x03 \x01(\t\"\xf6\x03\n\x06Metric\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\x12\x0c\n\x04unit\x18\x03 \x01(\t\x12\x41\n\tint_gauge\x18\x04 \x01(\x0b\x32(.opentelemetry.proto.metrics.v1.IntGaugeB\x02\x18\x01H\x00\x12\x36\n\x05gauge\x18\x05 \x01(\x0b\x32%.opentelemetry.proto.metrics.v1.GaugeH\x00\x12=\n\x07int_sum\x18\x06 \x01(\x0b\x32&.opentelemetry.proto.metrics.v1.IntSumB\x02\x18\x01H\x00\x12\x32\n\x03sum\x18\x07 \x01(\x0b\x32#.opentelemetry.proto.metrics.v1.SumH\x00\x12I\n\rint_histogram\x18\x08 \x01(\x0b\x32,.opentelemetry.proto.metrics.v1.IntHistogramB\x02\x18\x01H\x00\x12>\n\thistogram\x18\t \x01(\x0b\x32).opentelemetry.proto.metrics.v1.HistogramH\x00\x12:\n\x07summary\x18\x0b \x01(\x0b\x32\'.opentelemetry.proto.metrics.v1.SummaryH\x00\x42\x06\n\x04\x64\x61ta\"M\n\x05Gauge\x12\x44\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32/.opentelemetry.proto.metrics.v1.NumberDataPoint\"\xba\x01\n\x03Sum\x12\x44\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32/.opentelemetry.proto.metrics.v1.NumberDataPoint\x12W\n\x17\x61ggregation_temporality\x18\x02 \x01(\x0e\x32\x36.opentelemetry.proto.metrics.v1.AggregationTemporality\x12\x14\n\x0cis_monotonic\x18\x03 \x01(\x08\"\xad\x01\n\tHistogram\x12G\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32\x32.opentelemetry.proto.metrics.v1.HistogramDataPoint\x12W\n\x17\x61ggregation_temporality\x18\x02 \x01(\x0e\x32\x36.opentelemetry.proto.metrics.v1.AggregationTemporality\"P\n\x07Summary\x12\x45\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32\x30.opentelemetry.proto.metrics.v1.SummaryDataPoint\"\xb4\x02\n\x0fNumberDataPoint\x12;\n\nattributes\x18\x07 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\x12\x41\n\x06labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValueB\x02\x18\x01\x12\x1c\n\x14start_time_unix_nano\x18\x02 \x01(\x06\x12\x16\n\x0etime_unix_nano\x18\x03 \x01(\x06\x12\x13\n\tas_double\x18\x04 \x01(\x01H\x00\x12\x10\n\x06\x61s_int\x18\x06 \x01(\x10H\x00\x12;\n\texemplars\x18\x05 \x03(\x0b\x32(.opentelemetry.proto.metrics.v1.ExemplarB\x07\n\x05value\"\xd3\x02\n\x12HistogramDataPoint\x12;\n\nattributes\x18\t \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\x12\x41\n\x06labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValueB\x02\x18\x01\x12\x1c\n\x14start_time_unix_nano\x18\x02 \x01(\x06\x12\x16\n\x0etime_unix_nano\x18\x03 \x01(\x06\x12\r\n\x05\x63ount\x18\x04 \x01(\x06\x12\x0b\n\x03sum\x18\x05 \x01(\x01\x12\x15\n\rbucket_counts\x18\x06 \x03(\x06\x12\x17\n\x0f\x65xplicit_bounds\x18\x07 \x03(\x01\x12;\n\texemplars\x18\x08 \x03(\x0b\x32(.opentelemetry.proto.metrics.v1.Exemplar\"\xf3\x02\n\x10SummaryDataPoint\x12;\n\nattributes\x18\x07 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\x12\x41\n\x06labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValueB\x02\x18\x01\x12\x1c\n\x14start_time_unix_nano\x18\x02 \x01(\x06\x12\x16\n\x0etime_unix_nano\x18\x03 \x01(\x06\x12\r\n\x05\x63ount\x18\x04 \x01(\x06\x12\x0b\n\x03sum\x18\x05 \x01(\x01\x12Y\n\x0fquantile_values\x18\x06 \x03(\x0b\x32@.opentelemetry.proto.metrics.v1.SummaryDataPoint.ValueAtQuantile\x1a\x32\n\x0fValueAtQuantile\x12\x10\n\x08quantile\x18\x01 \x01(\x01\x12\r\n\x05value\x18\x02 \x01(\x01\"\x87\x02\n\x08\x45xemplar\x12\x44\n\x13\x66iltered_attributes\x18\x07 \x03(\x0b\x32\'.opentelemetry.proto.common.v1.KeyValue\x12J\n\x0f\x66iltered_labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValueB\x02\x18\x01\x12\x16\n\x0etime_unix_nano\x18\x02 \x01(\x06\x12\x13\n\tas_double\x18\x03 \x01(\x01H\x00\x12\x10\n\x06\x61s_int\x18\x06 \x01(\x10H\x00\x12\x0f\n\x07span_id\x18\x04 \x01(\x0c\x12\x10\n\x08trace_id\x18\x05 \x01(\x0c\x42\x07\n\x05value\"\xd6\x01\n\x0cIntDataPoint\x12=\n\x06labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValue\x12\x1c\n\x14start_time_unix_nano\x18\x02 \x01(\x06\x12\x16\n\x0etime_unix_nano\x18\x03 \x01(\x06\x12\r\n\x05value\x18\x04 \x01(\x10\x12>\n\texemplars\x18\x05 \x03(\x0b\x32+.opentelemetry.proto.metrics.v1.IntExemplar:\x02\x18\x01\"Q\n\x08IntGauge\x12\x41\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32,.opentelemetry.proto.metrics.v1.IntDataPoint:\x02\x18\x01\"\xbe\x01\n\x06IntSum\x12\x41\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32,.opentelemetry.proto.metrics.v1.IntDataPoint\x12W\n\x17\x61ggregation_temporality\x18\x02 \x01(\x0e\x32\x36.opentelemetry.proto.metrics.v1.AggregationTemporality\x12\x14\n\x0cis_monotonic\x18\x03 \x01(\x08:\x02\x18\x01\"\x9c\x02\n\x15IntHistogramDataPoint\x12=\n\x06labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValue\x12\x1c\n\x14start_time_unix_nano\x18\x02 \x01(\x06\x12\x16\n\x0etime_unix_nano\x18\x03 \x01(\x06\x12\r\n\x05\x63ount\x18\x04 \x01(\x06\x12\x0b\n\x03sum\x18\x05 \x01(\x10\x12\x15\n\rbucket_counts\x18\x06 \x03(\x06\x12\x17\n\x0f\x65xplicit_bounds\x18\x07 \x03(\x01\x12>\n\texemplars\x18\x08 \x03(\x0b\x32+.opentelemetry.proto.metrics.v1.IntExemplar:\x02\x18\x01\"\xb7\x01\n\x0cIntHistogram\x12J\n\x0b\x64\x61ta_points\x18\x01 \x03(\x0b\x32\x35.opentelemetry.proto.metrics.v1.IntHistogramDataPoint\x12W\n\x17\x61ggregation_temporality\x18\x02 \x01(\x0e\x32\x36.opentelemetry.proto.metrics.v1.AggregationTemporality:\x02\x18\x01\"\xa3\x01\n\x0bIntExemplar\x12\x46\n\x0f\x66iltered_labels\x18\x01 \x03(\x0b\x32-.opentelemetry.proto.common.v1.StringKeyValue\x12\x16\n\x0etime_unix_nano\x18\x02 \x01(\x06\x12\r\n\x05value\x18\x03 \x01(\x10\x12\x0f\n\x07span_id\x18\x04 \x01(\x0c\x12\x10\n\x08trace_id\x18\x05 \x01(\x0c:\x02\x18\x01*\x8c\x01\n\x16\x41ggregationTemporality\x12\'\n#AGGREGATION_TEMPORALITY_UNSPECIFIED\x10\x00\x12!\n\x1d\x41GGREGATION_TEMPORALITY_DELTA\x10\x01\x12&\n\"AGGREGATION_TEMPORALITY_CUMULATIVE\x10\x02\x42t\n!io.opentelemetry.proto.metrics.v1B\x0cMetricsProtoP\x01Z?github.com/open-telemetry/opentelemetry-proto/gen/go/metrics/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opentelemetry.proto.metrics.v1.metrics_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.opentelemetry.proto.metrics.v1B\014MetricsProtoP\001Z?github.com/open-telemetry/opentelemetry-proto/gen/go/metrics/v1'
  _METRIC.fields_by_name['int_gauge']._options = None
  _METRIC.fields_by_name['int_gauge']._serialized_options = b'\030\001'
  _METRIC.fields_by_name['int_sum']._options = None
  _METRIC.fields_by_name['int_sum']._serialized_options = b'\030\001'
  _METRIC.fields_by_name['int_histogram']._options = None
  _METRIC.fields_by_name['int_histogram']._serialized_options = b'\030\001'
  _NUMBERDATAPOINT.fields_by_name['labels']._options = None
  _NUMBERDATAPOINT.fields_by_name['labels']._serialized_options = b'\030\001'
  _HISTOGRAMDATAPOINT.fields_by_name['labels']._options = None
  _HISTOGRAMDATAPOINT.fields_by_name['labels']._serialized_options = b'\030\001'
  _SUMMARYDATAPOINT.fields_by_name['labels']._options = None
  _SUMMARYDATAPOINT.fields_by_name['labels']._serialized_options = b'\030\001'
  _EXEMPLAR.fields_by_name['filtered_labels']._options = None
  _EXEMPLAR.fields_by_name['filtered_labels']._serialized_options = b'\030\001'
  _INTDATAPOINT._options = None
  _INTDATAPOINT._serialized_options = b'\030\001'
  _INTGAUGE._options = None
  _INTGAUGE._serialized_options = b'\030\001'
  _INTSUM._options = None
  _INTSUM._serialized_options = b'\030\001'
  _INTHISTOGRAMDATAPOINT._options = None
  _INTHISTOGRAMDATAPOINT._serialized_options = b'\030\001'
  _INTHISTOGRAM._options = None
  _INTHISTOGRAM._serialized_options = b'\030\001'
  _INTEXEMPLAR._options = None
  _INTEXEMPLAR._serialized_options = b'\030\001'
  _globals['_AGGREGATIONTEMPORALITY']._serialized_start=4033
  _globals['_AGGREGATIONTEMPORALITY']._serialized_end=4173
  _globals['_RESOURCEMETRICS']._serialized_start=173
  _globals['_RESOURCEMETRICS']._serialized_end=375
  _globals['_INSTRUMENTATIONLIBRARYMETRICS']._serialized_start=378
  _globals['_INSTRUMENTATIONLIBRARYMETRICS']._serialized_end=574
  _globals['_METRIC']._serialized_start=577
  _globals['_METRIC']._serialized_end=1079
  _globals['_GAUGE']._serialized_start=1081
  _globals['_GAUGE']._serialized_end=1158
  _globals['_SUM']._serialized_start=1161
  _globals['_SUM']._serialized_end=1347
  _globals['_HISTOGRAM']._serialized_start=1350
  _globals['_HISTOGRAM']._serialized_end=1523
  _globals['_SUMMARY']._serialized_start=1525
  _globals['_SUMMARY']._serialized_end=1605
  _globals['_NUMBERDATAPOINT']._serialized_start=1608
  _globals['_NUMBERDATAPOINT']._serialized_end=1916
  _globals['_HISTOGRAMDATAPOINT']._serialized_start=1919
  _globals['_HISTOGRAMDATAPOINT']._serialized_end=2258
  _globals['_SUMMARYDATAPOINT']._serialized_start=2261
  _globals['_SUMMARYDATAPOINT']._serialized_end=2632
  _globals['_SUMMARYDATAPOINT_VALUEATQUANTILE']._serialized_start=2582
  _globals['_SUMMARYDATAPOINT_VALUEATQUANTILE']._serialized_end=2632
  _globals['_EXEMPLAR']._serialized_start=2635
  _globals['_EXEMPLAR']._serialized_end=2898
  _globals['_INTDATAPOINT']._serialized_start=2901
  _globals['_INTDATAPOINT']._serialized_end=3115
  _globals['_INTGAUGE']._serialized_start=3117
  _globals['_INTGAUGE']._serialized_end=3198
  _globals['_INTSUM']._serialized_start=3201
  _globals['_INTSUM']._serialized_end=3391
  _globals['_INTHISTOGRAMDATAPOINT']._serialized_start=3394
  _globals['_INTHISTOGRAMDATAPOINT']._serialized_end=3678
  _globals['_INTHISTOGRAM']._serialized_start=3681
  _globals['_INTHISTOGRAM']._serialized_end=3864
  _globals['_INTEXEMPLAR']._serialized_start=3867
  _globals['_INTEXEMPLAR']._serialized_end=4030
