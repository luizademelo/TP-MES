
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from envoy.annotations import resource_pb2 as envoy_dot_annotations_dot_resource__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from envoy.api.v2 import listener_pb2 as envoy_dot_api_dot_v2_dot_listener__pb2

from envoy.api.v2.listener_pb2 import *

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x16\x65nvoy/api/v2/lds.proto\x12\x0c\x65nvoy.api.v2\x1a\x1c\x65nvoy/api/v2/discovery.proto\x1a\x1cgoogle/api/annotations.proto\x1a envoy/annotations/resource.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x1b\x65nvoy/api/v2/listener.proto\"\n\n\x08LdsDummy2\xed\x02\n\x18ListenerDiscoveryService\x12\x61\n\x0e\x44\x65ltaListeners\x12#.envoy.api.v2.DeltaDiscoveryRequest\x1a$.envoy.api.v2.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x12X\n\x0fStreamListeners\x12\x1e.envoy.api.v2.DiscoveryRequest\x1a\x1f.envoy.api.v2.DiscoveryResponse\"\x00(\x01\x30\x01\x12u\n\x0e\x46\x65tchListeners\x12\x1e.envoy.api.v2.DiscoveryRequest\x1a\x1f.envoy.api.v2.DiscoveryResponse\"\"\x82\xd3\xe4\x93\x02\x1c\"\x17/v2/discovery:listeners:\x01*\x1a\x1d\x8a\xa4\x96\xf3\x07\x17\n\x15\x65nvoy.api.v2.ListenerB\x8c\x01\n\x1aio.envoyproxy.envoy.api.v2B\x08LdsProtoP\x01Z9github.com/envoyproxy/go-control-plane/envoy/api/v2;apiv2\xf2\x98\xfe\x8f\x05\x1b\x12\x19\x65nvoy.service.listener.v3\xba\x80\xc8\xd1\x06\x02\x10\x01P\x05\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.lds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\032io.envoyproxy.envoy.api.v2B\010LdsProtoP\001Z9github.com/envoyproxy/go-control-plane/envoy/api/v2;apiv2\362\230\376\217\005\033\022\031envoy.service.listener.v3\272\200\310\321\006\002\020\001'
  _LISTENERDISCOVERYSERVICE._options = None
  _LISTENERDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\007\027\n\025envoy.api.v2.Listener'
  _LISTENERDISCOVERYSERVICE.methods_by_name['FetchListeners']._options = None
  _LISTENERDISCOVERYSERVICE.methods_by_name['FetchListeners']._serialized_options = b'\202\323\344\223\002\034\"\027/v2/discovery:listeners:\001*'
  _globals['_LDSDUMMY']._serialized_start=226
  _globals['_LDSDUMMY']._serialized_end=236
  _globals['_LISTENERDISCOVERYSERVICE']._serialized_start=239
  _globals['_LISTENERDISCOVERYSERVICE']._serialized_end=604
