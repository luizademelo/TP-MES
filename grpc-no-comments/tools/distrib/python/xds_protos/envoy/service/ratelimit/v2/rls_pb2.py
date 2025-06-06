
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from envoy.api.v2.ratelimit import ratelimit_pb2 as envoy_dot_api_dot_v2_dot_ratelimit_dot_ratelimit__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/service/ratelimit/v2/rls.proto\x12\x1a\x65nvoy.service.ratelimit.v2\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a&envoy/api/v2/ratelimit/ratelimit.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"y\n\x10RateLimitRequest\x12\x0e\n\x06\x64omain\x18\x01 \x01(\t\x12@\n\x0b\x64\x65scriptors\x18\x02 \x03(\x0b\x32+.envoy.api.v2.ratelimit.RateLimitDescriptor\x12\x13\n\x0bhits_addend\x18\x03 \x01(\r\"\xf1\x05\n\x11RateLimitResponse\x12H\n\x0coverall_code\x18\x01 \x01(\x0e\x32\x32.envoy.service.ratelimit.v2.RateLimitResponse.Code\x12P\n\x08statuses\x18\x02 \x03(\x0b\x32>.envoy.service.ratelimit.v2.RateLimitResponse.DescriptorStatus\x12P\n\x07headers\x18\x03 \x03(\x0b\x32\x1e.envoy.api.v2.core.HeaderValueB\x1f\xf2\x98\xfe\x8f\x05\x19\n\x17response_headers_to_add\x12>\n\x16request_headers_to_add\x18\x04 \x03(\x0b\x32\x1e.envoy.api.v2.core.HeaderValue\x1a\xc0\x01\n\tRateLimit\x12\x0c\n\x04name\x18\x03 \x01(\t\x12\x19\n\x11requests_per_unit\x18\x01 \x01(\r\x12J\n\x04unit\x18\x02 \x01(\x0e\x32<.envoy.service.ratelimit.v2.RateLimitResponse.RateLimit.Unit\">\n\x04Unit\x12\x0b\n\x07UNKNOWN\x10\x00\x12\n\n\x06SECOND\x10\x01\x12\n\n\x06MINUTE\x10\x02\x12\x08\n\x04HOUR\x10\x03\x12\x07\n\x03\x44\x41Y\x10\x04\x1a\xbd\x01\n\x10\x44\x65scriptorStatus\x12@\n\x04\x63ode\x18\x01 \x01(\x0e\x32\x32.envoy.service.ratelimit.v2.RateLimitResponse.Code\x12N\n\rcurrent_limit\x18\x02 \x01(\x0b\x32\x37.envoy.service.ratelimit.v2.RateLimitResponse.RateLimit\x12\x17\n\x0flimit_remaining\x18\x03 \x01(\r\"+\n\x04\x43ode\x12\x0b\n\x07UNKNOWN\x10\x00\x12\x06\n\x02OK\x10\x01\x12\x0e\n\nOVER_LIMIT\x10\x02\x32\x84\x01\n\x10RateLimitService\x12p\n\x0fShouldRateLimit\x12,.envoy.service.ratelimit.v2.RateLimitRequest\x1a-.envoy.service.ratelimit.v2.RateLimitResponse\"\x00\x42\x8d\x01\n(io.envoyproxy.envoy.service.ratelimit.v2B\x08RlsProtoP\x01ZMgithub.com/envoyproxy/go-control-plane/envoy/service/ratelimit/v2;ratelimitv2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.ratelimit.v2.rls_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(io.envoyproxy.envoy.service.ratelimit.v2B\010RlsProtoP\001ZMgithub.com/envoyproxy/go-control-plane/envoy/service/ratelimit/v2;ratelimitv2\272\200\310\321\006\002\020\001'
  _RATELIMITRESPONSE.fields_by_name['headers']._options = None
  _RATELIMITRESPONSE.fields_by_name['headers']._serialized_options = b'\362\230\376\217\005\031\n\027response_headers_to_add'
  _globals['_RATELIMITREQUEST']._serialized_start=201
  _globals['_RATELIMITREQUEST']._serialized_end=322
  _globals['_RATELIMITRESPONSE']._serialized_start=325
  _globals['_RATELIMITRESPONSE']._serialized_end=1078
  _globals['_RATELIMITRESPONSE_RATELIMIT']._serialized_start=649
  _globals['_RATELIMITRESPONSE_RATELIMIT']._serialized_end=841
  _globals['_RATELIMITRESPONSE_RATELIMIT_UNIT']._serialized_start=779
  _globals['_RATELIMITRESPONSE_RATELIMIT_UNIT']._serialized_end=841
  _globals['_RATELIMITRESPONSE_DESCRIPTORSTATUS']._serialized_start=844
  _globals['_RATELIMITRESPONSE_DESCRIPTORSTATUS']._serialized_end=1033
  _globals['_RATELIMITRESPONSE_CODE']._serialized_start=1035
  _globals['_RATELIMITRESPONSE_CODE']._serialized_end=1078
  _globals['_RATELIMITSERVICE']._serialized_start=1081
  _globals['_RATELIMITSERVICE']._serialized_end=1213
