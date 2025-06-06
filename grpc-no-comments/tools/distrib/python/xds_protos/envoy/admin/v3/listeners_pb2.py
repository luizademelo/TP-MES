
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1e\x65nvoy/admin/v3/listeners.proto\x12\x0e\x65nvoy.admin.v3\x1a\"envoy/config/core/v3/address.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"l\n\tListeners\x12\x39\n\x11listener_statuses\x18\x01 \x03(\x0b\x32\x1e.envoy.admin.v3.ListenerStatus:$\x9a\xc5\x88\x1e\x1f\n\x1d\x65nvoy.admin.v2alpha.Listeners\"\xc2\x01\n\x0eListenerStatus\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x34\n\rlocal_address\x18\x02 \x01(\x0b\x32\x1d.envoy.config.core.v3.Address\x12\x41\n\x1a\x61\x64\x64itional_local_addresses\x18\x03 \x03(\x0b\x32\x1d.envoy.config.core.v3.Address:)\x9a\xc5\x88\x1e$\n\"envoy.admin.v2alpha.ListenerStatusBw\n\x1cio.envoyproxy.envoy.admin.v3B\x0eListenersProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.listeners_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\016ListenersProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
  _LISTENERS._options = None
  _LISTENERS._serialized_options = b'\232\305\210\036\037\n\035envoy.admin.v2alpha.Listeners'
  _LISTENERSTATUS._options = None
  _LISTENERSTATUS._serialized_options = b'\232\305\210\036$\n\"envoy.admin.v2alpha.ListenerStatus'
  _globals['_LISTENERS']._serialized_start=152
  _globals['_LISTENERS']._serialized_end=260
  _globals['_LISTENERSTATUS']._serialized_start=263
  _globals['_LISTENERSTATUS']._serialized_end=457
