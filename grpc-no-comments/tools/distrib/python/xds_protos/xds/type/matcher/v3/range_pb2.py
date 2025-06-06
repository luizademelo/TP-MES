
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.type.v3 import range_pb2 as xds_dot_type_dot_v3_dot_range__pb2
from xds.type.matcher.v3 import matcher_pb2 as xds_dot_type_dot_matcher_dot_v3_dot_matcher__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1fxds/type/matcher/v3/range.proto\x12\x13xds.type.matcher.v3\x1a\x17xds/type/v3/range.proto\x1a!xds/type/matcher/v3/matcher.proto\x1a\x17validate/validate.proto\"\xdb\x01\n\x11Int64RangeMatcher\x12K\n\x0erange_matchers\x18\x01 \x03(\x0b\x32\x33.xds.type.matcher.v3.Int64RangeMatcher.RangeMatcher\x1ay\n\x0cRangeMatcher\x12\x31\n\x06ranges\x18\x01 \x03(\x0b\x32\x17.xds.type.v3.Int64RangeB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x36\n\x08on_match\x18\x02 \x01(\x0b\x32$.xds.type.matcher.v3.Matcher.OnMatch\"\xdb\x01\n\x11Int32RangeMatcher\x12K\n\x0erange_matchers\x18\x01 \x03(\x0b\x32\x33.xds.type.matcher.v3.Int32RangeMatcher.RangeMatcher\x1ay\n\x0cRangeMatcher\x12\x31\n\x06ranges\x18\x01 \x03(\x0b\x32\x17.xds.type.v3.Int32RangeB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x36\n\x08on_match\x18\x02 \x01(\x0b\x32$.xds.type.matcher.v3.Matcher.OnMatch\"\xde\x01\n\x12\x44oubleRangeMatcher\x12L\n\x0erange_matchers\x18\x01 \x03(\x0b\x32\x34.xds.type.matcher.v3.DoubleRangeMatcher.RangeMatcher\x1az\n\x0cRangeMatcher\x12\x32\n\x06ranges\x18\x01 \x03(\x0b\x32\x18.xds.type.v3.DoubleRangeB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12\x36\n\x08on_match\x18\x02 \x01(\x0b\x32$.xds.type.matcher.v3.Matcher.OnMatchBZ\n\x1e\x63om.github.xds.type.matcher.v3B\nRangeProtoP\x01Z*github.com/cncf/xds/go/xds/type/matcher/v3b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.type.matcher.v3.range_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.github.xds.type.matcher.v3B\nRangeProtoP\001Z*github.com/cncf/xds/go/xds/type/matcher/v3'
  _INT64RANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._options = None
  _INT64RANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._serialized_options = b'\372B\005\222\001\002\010\001'
  _INT32RANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._options = None
  _INT32RANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._serialized_options = b'\372B\005\222\001\002\010\001'
  _DOUBLERANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._options = None
  _DOUBLERANGEMATCHER_RANGEMATCHER.fields_by_name['ranges']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_INT64RANGEMATCHER']._serialized_start=142
  _globals['_INT64RANGEMATCHER']._serialized_end=361
  _globals['_INT64RANGEMATCHER_RANGEMATCHER']._serialized_start=240
  _globals['_INT64RANGEMATCHER_RANGEMATCHER']._serialized_end=361
  _globals['_INT32RANGEMATCHER']._serialized_start=364
  _globals['_INT32RANGEMATCHER']._serialized_end=583
  _globals['_INT32RANGEMATCHER_RANGEMATCHER']._serialized_start=462
  _globals['_INT32RANGEMATCHER_RANGEMATCHER']._serialized_end=583
  _globals['_DOUBLERANGEMATCHER']._serialized_start=586
  _globals['_DOUBLERANGEMATCHER']._serialized_end=808
  _globals['_DOUBLERANGEMATCHER_RANGEMATCHER']._serialized_start=686
  _globals['_DOUBLERANGEMATCHER_RANGEMATCHER']._serialized_end=808
