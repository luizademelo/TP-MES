
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.ratelimit import ratelimit_pb2 as envoy_dot_api_dot_v2_dot_ratelimit_dot_ratelimit__pb2
from envoy.config.ratelimit.v2 import rls_pb2 as envoy_dot_config_dot_ratelimit_dot_v2_dot_rls__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n:envoy/config/filter/network/rate_limit/v2/rate_limit.proto\x12)envoy.config.filter.network.rate_limit.v2\x1a&envoy/api/v2/ratelimit/ratelimit.proto\x1a#envoy/config/ratelimit/v2/rls.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xae\x02\n\tRateLimit\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x17\n\x06\x64omain\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12J\n\x0b\x64\x65scriptors\x18\x03 \x03(\x0b\x32+.envoy.api.v2.ratelimit.RateLimitDescriptorB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12*\n\x07timeout\x18\x04 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x19\n\x11\x66\x61ilure_mode_deny\x18\x05 \x01(\x08\x12W\n\x12rate_limit_service\x18\x06 \x01(\x0b\x32\x31.envoy.config.ratelimit.v2.RateLimitServiceConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\xe7\x01\n7io.envoyproxy.envoy.config.filter.network.rate_limit.v2B\x0eRateLimitProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/config/filter/network/rate_limit/v2;rate_limitv2\xf2\x98\xfe\x8f\x05/\x12-envoy.extensions.filters.network.ratelimit.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.network.rate_limit.v2.rate_limit_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.config.filter.network.rate_limit.v2B\016RateLimitProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/config/filter/network/rate_limit/v2;rate_limitv2\362\230\376\217\005/\022-envoy.extensions.filters.network.ratelimit.v3\272\200\310\321\006\002\020\001'
  _RATELIMIT.fields_by_name['stat_prefix']._options = None
  _RATELIMIT.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMIT.fields_by_name['domain']._options = None
  _RATELIMIT.fields_by_name['domain']._serialized_options = b'\372B\004r\002 \001'
  _RATELIMIT.fields_by_name['descriptors']._options = None
  _RATELIMIT.fields_by_name['descriptors']._serialized_options = b'\372B\005\222\001\002\010\001'
  _RATELIMIT.fields_by_name['rate_limit_service']._options = None
  _RATELIMIT.fields_by_name['rate_limit_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_RATELIMIT']._serialized_start=303
  _globals['_RATELIMIT']._serialized_end=605
