
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/extensions/filters/udp/udp_proxy/v3/route.proto\x12)envoy.extensions.filters.udp.udp_proxy.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"!\n\x05Route\x12\x18\n\x07\x63luster\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xad\x01\n7io.envoyproxy.envoy.extensions.filters.udp.udp_proxy.v3B\nRouteProtoP\x01Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/filters/udp/udp_proxy/v3;udp_proxyv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.udp.udp_proxy.v3.route_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n7io.envoyproxy.envoy.extensions.filters.udp.udp_proxy.v3B\nRouteProtoP\001Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/filters/udp/udp_proxy/v3;udp_proxyv3\272\200\310\321\006\002\020\002'
  _ROUTE.fields_by_name['cluster']._options = None
  _ROUTE.fields_by_name['cluster']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_ROUTE']._serialized_start=156
  _globals['_ROUTE']._serialized_end=189
