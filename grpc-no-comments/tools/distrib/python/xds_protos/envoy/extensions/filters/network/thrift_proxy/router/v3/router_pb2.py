
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDenvoy/extensions/filters/network/thrift_proxy/router/v3/router.proto\x12\x37\x65nvoy.extensions.filters.network.thrift_proxy.router.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\x8a\x01\n\x06Router\x12\x46\n\"close_downstream_on_upstream_error\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue:8\x9a\xc5\x88\x1e\x33\n1envoy.config.filter.thrift.router.v2alpha1.RouterB\xc7\x01\nEio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.router.v3B\x0bRouterProtoP\x01Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/router/v3;routerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.network.thrift_proxy.router.v3.router_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.extensions.filters.network.thrift_proxy.router.v3B\013RouterProtoP\001Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/network/thrift_proxy/router/v3;routerv3\272\200\310\321\006\002\020\002'
  _ROUTER._options = None
  _ROUTER._serialized_options = b'\232\305\210\0363\n1envoy.config.filter.thrift.router.v2alpha1.Router'
  _globals['_ROUTER']._serialized_start=228
  _globals['_ROUTER']._serialized_end=366
