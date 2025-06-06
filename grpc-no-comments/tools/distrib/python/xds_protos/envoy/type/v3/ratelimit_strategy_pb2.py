
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.v3 import ratelimit_unit_pb2 as envoy_dot_type_dot_v3_dot_ratelimit__unit__pb2
from envoy.type.v3 import token_bucket_pb2 as envoy_dot_type_dot_v3_dot_token__bucket__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&envoy/type/v3/ratelimit_strategy.proto\x12\renvoy.type.v3\x1a\"envoy/type/v3/ratelimit_unit.proto\x1a envoy/type/v3/token_bucket.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x9e\x03\n\x11RateLimitStrategy\x12N\n\x0c\x62lanket_rule\x18\x01 \x01(\x0e\x32,.envoy.type.v3.RateLimitStrategy.BlanketRuleB\x08\xfa\x42\x05\x82\x01\x02\x10\x01H\x00\x12V\n\x16requests_per_time_unit\x18\x02 \x01(\x0b\x32\x34.envoy.type.v3.RateLimitStrategy.RequestsPerTimeUnitH\x00\x12\x32\n\x0ctoken_bucket\x18\x03 \x01(\x0b\x32\x1a.envoy.type.v3.TokenBucketH\x00\x1ap\n\x13RequestsPerTimeUnit\x12\x1e\n\x16requests_per_time_unit\x18\x01 \x01(\x04\x12\x39\n\ttime_unit\x18\x02 \x01(\x0e\x32\x1c.envoy.type.v3.RateLimitUnitB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"*\n\x0b\x42lanketRule\x12\r\n\tALLOW_ALL\x10\x00\x12\x0c\n\x08\x44\x45NY_ALL\x10\x01\x42\x0f\n\x08strategy\x12\x03\xf8\x42\x01\x42\x84\x01\n\x1bio.envoyproxy.envoy.type.v3B\x16RatelimitStrategyProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.v3.ratelimit_strategy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\033io.envoyproxy.envoy.type.v3B\026RatelimitStrategyProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/type/v3;typev3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _RATELIMITSTRATEGY_REQUESTSPERTIMEUNIT.fields_by_name['time_unit']._options = None
  _RATELIMITSTRATEGY_REQUESTSPERTIMEUNIT.fields_by_name['time_unit']._serialized_options = b'\372B\005\202\001\002\020\001'
  _RATELIMITSTRATEGY.oneofs_by_name['strategy']._options = None
  _RATELIMITSTRATEGY.oneofs_by_name['strategy']._serialized_options = b'\370B\001'
  _RATELIMITSTRATEGY.fields_by_name['blanket_rule']._options = None
  _RATELIMITSTRATEGY.fields_by_name['blanket_rule']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_RATELIMITSTRATEGY']._serialized_start=217
  _globals['_RATELIMITSTRATEGY']._serialized_end=631
  _globals['_RATELIMITSTRATEGY_REQUESTSPERTIMEUNIT']._serialized_start=458
  _globals['_RATELIMITSTRATEGY_REQUESTSPERTIMEUNIT']._serialized_end=570
  _globals['_RATELIMITSTRATEGY_BLANKETRULE']._serialized_start=572
  _globals['_RATELIMITSTRATEGY_BLANKETRULE']._serialized_end=614
