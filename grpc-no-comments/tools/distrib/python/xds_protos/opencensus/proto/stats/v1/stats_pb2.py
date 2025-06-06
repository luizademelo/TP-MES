
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%opencensus/proto/stats/v1/stats.proto\x12\x19opencensus.proto.stats.v1\x1a\x1fgoogle/protobuf/timestamp.proto\"!\n\x03Tag\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t\"\xa6\x01\n\x07Measure\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\x12\x0c\n\x04unit\x18\x03 \x01(\t\x12\x35\n\x04type\x18\x04 \x01(\x0e\x32\'.opencensus.proto.stats.v1.Measure.Type\"3\n\x04Type\x12\x14\n\x10TYPE_UNSPECIFIED\x10\x00\x12\t\n\x05INT64\x10\x01\x12\n\n\x06\x44OUBLE\x10\x02\"\xb9\x03\n\x04View\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x13\n\x0b\x64\x65scription\x18\x02 \x01(\t\x12\x33\n\x07measure\x18\x03 \x01(\x0b\x32\".opencensus.proto.stats.v1.Measure\x12\x0f\n\x07\x63olumns\x18\x04 \x03(\t\x12H\n\x11\x63ount_aggregation\x18\x05 \x01(\x0b\x32+.opencensus.proto.stats.v1.CountAggregationH\x00\x12\x44\n\x0fsum_aggregation\x18\x06 \x01(\x0b\x32).opencensus.proto.stats.v1.SumAggregationH\x00\x12Q\n\x16last_value_aggregation\x18\x07 \x01(\x0b\x32/.opencensus.proto.stats.v1.LastValueAggregationH\x00\x12V\n\x18\x64istribution_aggregation\x18\x08 \x01(\x0b\x32\x32.opencensus.proto.stats.v1.DistributionAggregationH\x00\x42\r\n\x0b\x61ggregation\"\x12\n\x10\x43ountAggregation\"\x10\n\x0eSumAggregation\"\x16\n\x14LastValueAggregation\"0\n\x17\x44istributionAggregation\x12\x15\n\rbucket_bounds\x18\x01 \x03(\x01\"\xb1\x01\n\x0bMeasurement\x12,\n\x04tags\x18\x01 \x03(\x0b\x32\x1e.opencensus.proto.stats.v1.Tag\x12\x14\n\x0cmeasure_name\x18\x02 \x01(\t\x12\x16\n\x0c\x64ouble_value\x18\x03 \x01(\x01H\x00\x12\x13\n\tint_value\x18\x04 \x01(\x03H\x00\x12(\n\x04time\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.TimestampB\x07\n\x05valueB\x8c\x01\n\x1cio.opencensus.proto.stats.v1B\nStatsProtoP\x01ZBgithub.com/census-instrumentation/opencensus-proto/gen-go/stats/v1\xea\x02\x19OpenCensus.Proto.Stats.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.stats.v1.stats_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.opencensus.proto.stats.v1B\nStatsProtoP\001ZBgithub.com/census-instrumentation/opencensus-proto/gen-go/stats/v1\352\002\031OpenCensus.Proto.Stats.V1'
  _globals['_TAG']._serialized_start=101
  _globals['_TAG']._serialized_end=134
  _globals['_MEASURE']._serialized_start=137
  _globals['_MEASURE']._serialized_end=303
  _globals['_MEASURE_TYPE']._serialized_start=252
  _globals['_MEASURE_TYPE']._serialized_end=303
  _globals['_VIEW']._serialized_start=306
  _globals['_VIEW']._serialized_end=747
  _globals['_COUNTAGGREGATION']._serialized_start=749
  _globals['_COUNTAGGREGATION']._serialized_end=767
  _globals['_SUMAGGREGATION']._serialized_start=769
  _globals['_SUMAGGREGATION']._serialized_end=785
  _globals['_LASTVALUEAGGREGATION']._serialized_start=787
  _globals['_LASTVALUEAGGREGATION']._serialized_end=809
  _globals['_DISTRIBUTIONAGGREGATION']._serialized_start=811
  _globals['_DISTRIBUTIONAGGREGATION']._serialized_end=859
  _globals['_MEASUREMENT']._serialized_start=862
  _globals['_MEASUREMENT']._serialized_end=1039
