
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import grpc_method_list_pb2 as envoy_dot_api_dot_v2_dot_core_dot_grpc__method__list__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n8envoy/config/filter/http/grpc_stats/v2alpha/config.proto\x12+envoy.config.filter.http.grpc_stats.v2alpha\x1a(envoy/api/v2/core/grpc_method_list.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"\xd3\x01\n\x0c\x46ilterConfig\x12\x19\n\x11\x65mit_filter_state\x18\x01 \x01(\x08\x12N\n!individual_method_stats_allowlist\x18\x02 \x01(\x0b\x32!.envoy.api.v2.core.GrpcMethodListH\x00\x12;\n\x15stats_for_all_methods\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.BoolValueH\x00\x42\x1b\n\x19per_method_stat_specifier\"M\n\x0c\x46ilterObject\x12\x1d\n\x15request_message_count\x18\x01 \x01(\x04\x12\x1e\n\x16response_message_count\x18\x02 \x01(\x04\x42\xd9\x01\n9io.envoyproxy.envoy.config.filter.http.grpc_stats.v2alphaB\x0b\x43onfigProtoP\x01ZRgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/grpc_stats/v2alpha\xf2\x98\xfe\x8f\x05-\x12+envoy.extensions.filters.http.grpc_stats.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.grpc_stats.v2alpha.config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.config.filter.http.grpc_stats.v2alphaB\013ConfigProtoP\001ZRgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/grpc_stats/v2alpha\362\230\376\217\005-\022+envoy.extensions.filters.http.grpc_stats.v3\272\200\310\321\006\002\020\001'
  _globals['_FILTERCONFIG']._serialized_start=243
  _globals['_FILTERCONFIG']._serialized_end=454
  _globals['_FILTEROBJECT']._serialized_start=456
  _globals['_FILTEROBJECT']._serialized_end=533
