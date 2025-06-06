
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

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/service/route/v3/srds.proto\x12\x16\x65nvoy.service.route.v3\x1a*envoy/service/discovery/v3/discovery.proto\x1a\x1cgoogle/api/annotations.proto\x1a envoy/annotations/resource.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"*\n\tSrdsDummy:\x1d\x9a\xc5\x88\x1e\x18\n\x16\x65nvoy.api.v2.SrdsDummy2\xed\x03\n\x1cScopedRoutesDiscoveryService\x12w\n\x12StreamScopedRoutes\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"\x00(\x01\x30\x01\x12\x80\x01\n\x11\x44\x65ltaScopedRoutes\x12\x31.envoy.service.discovery.v3.DeltaDiscoveryRequest\x1a\x32.envoy.service.discovery.v3.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x12\x98\x01\n\x11\x46\x65tchScopedRoutes\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"&\x82\xd3\xe4\x93\x02 \"\x1b/v3/discovery:scoped-routes:\x01*\x1a\x36\x8a\xa4\x96\xf3\x07\x30\n.envoy.config.route.v3.ScopedRouteConfigurationB\x82\x01\n$io.envoyproxy.envoy.service.route.v3B\tSrdsProtoP\x01ZEgithub.com/envoyproxy/go-control-plane/envoy/service/route/v3;routev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.route.v3.srds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.service.route.v3B\tSrdsProtoP\001ZEgithub.com/envoyproxy/go-control-plane/envoy/service/route/v3;routev3\272\200\310\321\006\002\020\002'
  _SRDSDUMMY._options = None
  _SRDSDUMMY._serialized_options = b'\232\305\210\036\030\n\026envoy.api.v2.SrdsDummy'
  _SCOPEDROUTESDISCOVERYSERVICE._options = None
  _SCOPEDROUTESDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\0070\n.envoy.config.route.v3.ScopedRouteConfiguration'
  _SCOPEDROUTESDISCOVERYSERVICE.methods_by_name['FetchScopedRoutes']._options = None
  _SCOPEDROUTESDISCOVERYSERVICE.methods_by_name['FetchScopedRoutes']._serialized_options = b'\202\323\344\223\002 \"\033/v3/discovery:scoped-routes:\001*'
  _globals['_SRDSDUMMY']._serialized_start=235
  _globals['_SRDSDUMMY']._serialized_end=277
  _globals['_SCOPEDROUTESDISCOVERYSERVICE']._serialized_start=280
  _globals['_SCOPEDROUTESDISCOVERYSERVICE']._serialized_end=773
