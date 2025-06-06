
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from envoy.annotations import resource_pb2 as envoy_dot_annotations_dot_resource__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/service/listener/v3/lds.proto\x12\x19\x65nvoy.service.listener.v3\x1a*envoy/service/discovery/v3/discovery.proto\x1a\x1cgoogle/api/annotations.proto\x1a envoy/annotations/resource.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"(\n\x08LdsDummy:\x1c\x9a\xc5\x88\x1e\x17\n\x15\x65nvoy.api.v2.LdsDummy2\xce\x03\n\x18ListenerDiscoveryService\x12}\n\x0e\x44\x65ltaListeners\x12\x31.envoy.service.discovery.v3.DeltaDiscoveryRequest\x1a\x32.envoy.service.discovery.v3.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x12t\n\x0fStreamListeners\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"\x00(\x01\x30\x01\x12\x91\x01\n\x0e\x46\x65tchListeners\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"\"\x82\xd3\xe4\x93\x02\x1c\"\x17/v3/discovery:listeners:\x01*\x1a)\x8a\xa4\x96\xf3\x07#\n!envoy.config.listener.v3.ListenerB\x8a\x01\n\'io.envoyproxy.envoy.service.listener.v3B\x08LdsProtoP\x01ZKgithub.com/envoyproxy/go-control-plane/envoy/service/listener/v3;listenerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.listener.v3.lds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\'io.envoyproxy.envoy.service.listener.v3B\010LdsProtoP\001ZKgithub.com/envoyproxy/go-control-plane/envoy/service/listener/v3;listenerv3\272\200\310\321\006\002\020\002'
  _LDSDUMMY._options = None
  _LDSDUMMY._serialized_options = b'\232\305\210\036\027\n\025envoy.api.v2.LdsDummy'
  _LISTENERDISCOVERYSERVICE._options = None
  _LISTENERDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\007#\n!envoy.config.listener.v3.Listener'
  _LISTENERDISCOVERYSERVICE.methods_by_name['FetchListeners']._options = None
  _LISTENERDISCOVERYSERVICE.methods_by_name['FetchListeners']._serialized_options = b'\202\323\344\223\002\034\"\027/v3/discovery:listeners:\001*'
  _globals['_LDSDUMMY']._serialized_start=240
  _globals['_LDSDUMMY']._serialized_end=280
  _globals['_LISTENERDISCOVERYSERVICE']._serialized_start=283
  _globals['_LISTENERDISCOVERYSERVICE']._serialized_end=745
