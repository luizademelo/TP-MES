
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nRenvoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.proto\x12\x33\x65nvoy.extensions.transport_sockets.http_11_proxy.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\"_\n\x1cHttp11ProxyUpstreamTransport\x12?\n\x10transport_socket\x18\x01 \x01(\x0b\x32%.envoy.config.core.v3.TransportSocketB\xd5\x01\nAio.envoyproxy.envoy.extensions.transport_sockets.http_11_proxy.v3B\x1aUpstreamHttp11ConnectProtoP\x01Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/http_11_proxy/v3;http_11_proxyv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.http_11_proxy.v3.upstream_http_11_connect_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nAio.envoyproxy.envoy.extensions.transport_sockets.http_11_proxy.v3B\032UpstreamHttp11ConnectProtoP\001Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/http_11_proxy/v3;http_11_proxyv3\272\200\310\321\006\002\020\002'
  _globals['_HTTP11PROXYUPSTREAMTRANSPORT']._serialized_start=203
  _globals['_HTTP11PROXYUPSTREAMTRANSPORT']._serialized_end=298
