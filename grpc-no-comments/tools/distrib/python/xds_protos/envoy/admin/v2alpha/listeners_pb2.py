
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import address_pb2 as envoy_dot_api_dot_v2_dot_core_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/admin/v2alpha/listeners.proto\x12\x13\x65nvoy.admin.v2alpha\x1a\x1f\x65nvoy/api/v2/core/address.proto\x1a\x1dudpa/annotations/status.proto\"K\n\tListeners\x12>\n\x11listener_statuses\x18\x01 \x03(\x0b\x32#.envoy.admin.v2alpha.ListenerStatus\"Q\n\x0eListenerStatus\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x31\n\rlocal_address\x18\x02 \x01(\x0b\x32\x1a.envoy.api.v2.core.AddressBy\n!io.envoyproxy.envoy.admin.v2alphaB\x0eListenersProtoP\x01Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v2alpha.listeners_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.envoyproxy.envoy.admin.v2alphaB\016ListenersProtoP\001Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\272\200\310\321\006\002\020\001'
  _globals['_LISTENERS']._serialized_start=124
  _globals['_LISTENERS']._serialized_end=199
  _globals['_LISTENERSTATUS']._serialized_start=201
  _globals['_LISTENERSTATUS']._serialized_end=282
