
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from google.rpc import status_pb2 as google_dot_rpc_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/service/redis_auth/v3/redis_external_auth.proto\x12\x1b\x65nvoy.service.redis_auth.v3\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x17google/rpc/status.proto\x1a\x1dudpa/annotations/status.proto\"C\n\x1dRedisProxyExternalAuthRequest\x12\x10\n\x08username\x18\x01 \x01(\t\x12\x10\n\x08password\x18\x02 \x01(\t\"\x85\x01\n\x1eRedisProxyExternalAuthResponse\x12\"\n\x06status\x18\x01 \x01(\x0b\x32\x12.google.rpc.Status\x12.\n\nexpiration\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x0f\n\x07message\x18\x03 \x01(\t2\xa4\x01\n\x16RedisProxyExternalAuth\x12\x89\x01\n\x0c\x41uthenticate\x12:.envoy.service.redis_auth.v3.RedisProxyExternalAuthRequest\x1a;.envoy.service.redis_auth.v3.RedisProxyExternalAuthResponse\"\x00\x42\x9e\x01\n)io.envoyproxy.envoy.service.redis_auth.v3B\x16RedisExternalAuthProtoP\x01ZOgithub.com/envoyproxy/go-control-plane/envoy/service/redis_auth/v3;redis_authv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.redis_auth.v3.redis_external_auth_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n)io.envoyproxy.envoy.service.redis_auth.v3B\026RedisExternalAuthProtoP\001ZOgithub.com/envoyproxy/go-control-plane/envoy/service/redis_auth/v3;redis_authv3\272\200\310\321\006\002\020\002'
  _globals['_REDISPROXYEXTERNALAUTHREQUEST']._serialized_start=175
  _globals['_REDISPROXYEXTERNALAUTHREQUEST']._serialized_end=242
  _globals['_REDISPROXYEXTERNALAUTHRESPONSE']._serialized_start=245
  _globals['_REDISPROXYEXTERNALAUTHRESPONSE']._serialized_end=378
  _globals['_REDISPROXYEXTERNALAUTH']._serialized_start=381
  _globals['_REDISPROXYEXTERNALAUTH']._serialized_end=545
