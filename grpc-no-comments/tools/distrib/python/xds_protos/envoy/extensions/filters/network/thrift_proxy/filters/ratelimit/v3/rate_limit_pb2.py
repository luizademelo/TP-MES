
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.ratelimit.v3 import rls_pb2 as envoy_dot_config_dot_ratelimit_dot_v3_dot_rls__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nSenvoy/extensions/filters/network/thrift_proxy/filters/ratelimit/v3/rate_limit.proto\x12\x42\x65nvoy.extensions.filters.network.thrift_proxy.filters.ratelimit.v3\x1a#envoy/config/ratelimit/v3/rls.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x9d\x02\n\tRateLimit\x12\x17\n\x06\x64omain\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x16\n\x05stage\x18\x02 \x01(\rB\x07\xfa\x42\x04*\x02\x18\n\x12*\n\x07timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x19\n\x11\x66\x61ilure_mode_deny\x18\x04 \x01(\x08\x12W\n\x12rate_limit_service\x18\x05 \x01(\x0b\x32\x31.envoy.config.ratelimit.v3.RateLimitServiceConfigB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01:?\x9a\xc5\x88\x1e:\n8envoy.config.filter.thrift.rate_limit.v2alpha1.RateLimitB\xe3\x01\nPio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.filters.ratelimit.v3B\x0eRateLimitProtoP\x01Zugithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/filters/ratelimit/v3;ratelimitv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.thrift_proxy.filters.ratelimit.v3.rate_limit_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nPio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.filters.ratelimit.v3B\016RateLimitProtoP\001Zugithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/filters/ratelimit/v3;ratelimitv3\272\200\310\321\006\002\020\002'
  _RATELIMIT.fields_by_name['domain']._options = None
  _RATELIMIT.fields_by_name['domain']._serialized_options = b'\372B\004r\002\020\001'
  _RATELIMIT.fields_by_name['stage']._options = None
  _RATELIMIT.fields_by_name['stage']._serialized_options = b'\372B\004*\002\030\n'
  _RATELIMIT.fields_by_name['rate_limit_service']._options = None
  _RATELIMIT.fields_by_name['rate_limit_service']._serialized_options = b'\372B\005\212\001\002\020\001'
  _RATELIMIT._options = None
  _RATELIMIT._serialized_options = b'\232\305\210\036:\n8envoy.config.filter.thrift.rate_limit.v2alpha1.RateLimit'
  _globals['_RATELIMIT']._serialized_start=316
  _globals['_RATELIMIT']._serialized_end=601
