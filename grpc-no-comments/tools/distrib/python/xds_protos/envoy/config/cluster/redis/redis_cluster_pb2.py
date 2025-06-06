
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n.envoy/config/cluster/redis/redis_cluster.proto\x12\x1a\x65nvoy.config.cluster.redis\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xe9\x02\n\x12RedisClusterConfig\x12\x41\n\x14\x63luster_refresh_rate\x18\x01 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x12\x44\n\x17\x63luster_refresh_timeout\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02*\x00\x12<\n\x19redirect_refresh_interval\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12@\n\x1aredirect_refresh_threshold\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12!\n\x19\x66\x61ilure_refresh_threshold\x18\x05 \x01(\r\x12\'\n\x1fhost_degraded_refresh_threshold\x18\x06 \x01(\rB\x8a\x01\n(io.envoyproxy.envoy.config.cluster.redisB\x11RedisClusterProtoP\x01ZAgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/redis\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.cluster.redis.redis_cluster_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(io.envoyproxy.envoy.config.cluster.redisB\021RedisClusterProtoP\001ZAgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/redis\272\200\310\321\006\002\020\001'
  _REDISCLUSTERCONFIG.fields_by_name['cluster_refresh_rate']._options = None
  _REDISCLUSTERCONFIG.fields_by_name['cluster_refresh_rate']._serialized_options = b'\372B\005\252\001\002*\000'
  _REDISCLUSTERCONFIG.fields_by_name['cluster_refresh_timeout']._options = None
  _REDISCLUSTERCONFIG.fields_by_name['cluster_refresh_timeout']._serialized_options = b'\372B\005\252\001\002*\000'
  _globals['_REDISCLUSTERCONFIG']._serialized_start=199
  _globals['_REDISCLUSTERCONFIG']._serialized_end=560
