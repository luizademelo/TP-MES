
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from contrib.envoy.extensions.filters.network.rocketmq_proxy.v3 import route_pb2 as contrib_dot_envoy_dot_extensions_dot_filters_dot_network_dot_rocketmq__proxy_dot_v3_dot_route__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nOcontrib/envoy/extensions/filters/network/rocketmq_proxy/v3/rocketmq_proxy.proto\x12\x32\x65nvoy.extensions.filters.network.rocketmq_proxy.v3\x1a\x46\x63ontrib/envoy/extensions/filters/network/rocketmq_proxy/v3/route.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xe0\x01\n\rRocketmqProxy\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\\\n\x0croute_config\x18\x02 \x01(\x0b\x32\x46.envoy.extensions.filters.network.rocketmq_proxy.v3.RouteConfiguration\x12=\n\x1atransient_object_life_span\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x14\n\x0c\x64\x65velop_mode\x18\x04 \x01(\x08\x42\xd4\x01\n@io.envoyproxy.envoy.extensions.filters.network.rocketmq_proxy.v3B\x12RocketmqProxyProtoP\x01Zrgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/rocketmq_proxy/v3;rocketmq_proxyv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.filters.network.rocketmq_proxy.v3.rocketmq_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.filters.network.rocketmq_proxy.v3B\022RocketmqProxyProtoP\001Zrgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/rocketmq_proxy/v3;rocketmq_proxyv3\272\200\310\321\006\002\020\002'
  _ROCKETMQPROXY.fields_by_name['stat_prefix']._options = None
  _ROCKETMQPROXY.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_ROCKETMQPROXY']._serialized_start=296
  _globals['_ROCKETMQPROXY']._serialized_end=520
