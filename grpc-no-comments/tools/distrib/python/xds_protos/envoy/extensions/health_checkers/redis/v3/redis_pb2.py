
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/extensions/health_checkers/redis/v3/redis.proto\x12)envoy.extensions.health_checkers.redis.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"G\n\x05Redis\x12\x0b\n\x03key\x18\x01 \x01(\t:1\x9a\xc5\x88\x1e,\n*envoy.config.health_checker.redis.v2.RedisB\xa9\x01\n7io.envoyproxy.envoy.extensions.health_checkers.redis.v3B\nRedisProtoP\x01ZXgithub.com/envoyproxy/go-control-plane/envoy/extensions/health_checkers/redis/v3;redisv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.health_checkers.redis.v3.redis_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.health_checkers.redis.v3B\nRedisProtoP\001ZXgithub.com/envoyproxy/go-control-plane/envoy/extensions/health_checkers/redis/v3;redisv3\272\200\310\321\006\002\020\002'
  _REDIS._options = None
  _REDIS._serialized_options = b'\232\305\210\036,\n*envoy.config.health_checker.redis.v2.Redis'
  _globals['_REDIS']._serialized_start=166
  _globals['_REDIS']._serialized_end=237
