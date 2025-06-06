
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/admin/v3/config_dump_shared.proto\x12\x0e\x65nvoy.admin.v3\x1a\x19google/protobuf/any.proto\x1a\x1fgoogle/protobuf/timestamp.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xd7\x01\n\x12UpdateFailureState\x12\x32\n\x14\x66\x61iled_configuration\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x37\n\x13last_update_attempt\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x0f\n\x07\x64\x65tails\x18\x03 \x01(\t\x12\x14\n\x0cversion_info\x18\x04 \x01(\t:-\x9a\xc5\x88\x1e(\n&envoy.admin.v2alpha.UpdateFailureState\"\xbe\x08\n\x13ListenersConfigDump\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12L\n\x10static_listeners\x18\x02 \x03(\x0b\x32\x32.envoy.admin.v3.ListenersConfigDump.StaticListener\x12N\n\x11\x64ynamic_listeners\x18\x03 \x03(\x0b\x32\x33.envoy.admin.v3.ListenersConfigDump.DynamicListener\x1a\xa9\x01\n\x0eStaticListener\x12&\n\x08listener\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:=\x9a\xc5\x88\x1e\x38\n6envoy.admin.v2alpha.ListenersConfigDump.StaticListener\x1a\xcb\x01\n\x14\x44ynamicListenerState\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12&\n\x08listener\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:C\x9a\xc5\x88\x1e>\n<envoy.admin.v2alpha.ListenersConfigDump.DynamicListenerState\x1a\xc8\x03\n\x0f\x44ynamicListener\x12\x0c\n\x04name\x18\x01 \x01(\t\x12N\n\x0c\x61\x63tive_state\x18\x02 \x01(\x0b\x32\x38.envoy.admin.v3.ListenersConfigDump.DynamicListenerState\x12O\n\rwarming_state\x18\x03 \x01(\x0b\x32\x38.envoy.admin.v3.ListenersConfigDump.DynamicListenerState\x12P\n\x0e\x64raining_state\x18\x04 \x01(\x0b\x32\x38.envoy.admin.v3.ListenersConfigDump.DynamicListenerState\x12\x37\n\x0b\x65rror_state\x18\x05 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x06 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus:>\x9a\xc5\x88\x1e\x39\n7envoy.admin.v2alpha.ListenersConfigDump.DynamicListener:.\x9a\xc5\x88\x1e)\n\'envoy.admin.v2alpha.ListenersConfigDump\"\xab\x06\n\x12\x43lustersConfigDump\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12I\n\x0fstatic_clusters\x18\x02 \x03(\x0b\x32\x30.envoy.admin.v3.ClustersConfigDump.StaticCluster\x12R\n\x17\x64ynamic_active_clusters\x18\x03 \x03(\x0b\x32\x31.envoy.admin.v3.ClustersConfigDump.DynamicCluster\x12S\n\x18\x64ynamic_warming_clusters\x18\x04 \x03(\x0b\x32\x31.envoy.admin.v3.ClustersConfigDump.DynamicCluster\x1a\xa5\x01\n\rStaticCluster\x12%\n\x07\x63luster\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:;\x9a\xc5\x88\x1e\x36\n4envoy.admin.v2alpha.ClustersConfigDump.StaticCluster\x1a\xb3\x02\n\x0e\x44ynamicCluster\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12%\n\x07\x63luster\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x0b\x65rror_state\x18\x04 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x05 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus:<\x9a\xc5\x88\x1e\x37\n5envoy.admin.v2alpha.ClustersConfigDump.DynamicCluster:-\x9a\xc5\x88\x1e(\n&envoy.admin.v2alpha.ClustersConfigDump\"\xd9\x05\n\x10RoutesConfigDump\x12P\n\x14static_route_configs\x18\x02 \x03(\x0b\x32\x32.envoy.admin.v3.RoutesConfigDump.StaticRouteConfig\x12R\n\x15\x64ynamic_route_configs\x18\x03 \x03(\x0b\x32\x33.envoy.admin.v3.RoutesConfigDump.DynamicRouteConfig\x1a\xb0\x01\n\x11StaticRouteConfig\x12*\n\x0croute_config\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:=\x9a\xc5\x88\x1e\x38\n6envoy.admin.v2alpha.RoutesConfigDump.StaticRouteConfig\x1a\xbe\x02\n\x12\x44ynamicRouteConfig\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12*\n\x0croute_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x0b\x65rror_state\x18\x04 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x05 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus:>\x9a\xc5\x88\x1e\x39\n7envoy.admin.v2alpha.RoutesConfigDump.DynamicRouteConfig:+\x9a\xc5\x88\x1e&\n$envoy.admin.v2alpha.RoutesConfigDump\"\xe1\x06\n\x16ScopedRoutesConfigDump\x12\x64\n\x1binline_scoped_route_configs\x18\x01 \x03(\x0b\x32?.envoy.admin.v3.ScopedRoutesConfigDump.InlineScopedRouteConfigs\x12\x66\n\x1c\x64ynamic_scoped_route_configs\x18\x02 \x03(\x0b\x32@.envoy.admin.v3.ScopedRoutesConfigDump.DynamicScopedRouteConfigs\x1a\xda\x01\n\x18InlineScopedRouteConfigs\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x32\n\x14scoped_route_configs\x18\x02 \x03(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp:J\x9a\xc5\x88\x1e\x45\nCenvoy.admin.v2alpha.ScopedRoutesConfigDump.InlineScopedRouteConfigs\x1a\xe8\x02\n\x19\x44ynamicScopedRouteConfigs\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\x0cversion_info\x18\x02 \x01(\t\x12\x32\n\x14scoped_route_configs\x18\x03 \x03(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x04 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x0b\x65rror_state\x18\x05 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x06 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus:K\x9a\xc5\x88\x1e\x46\nDenvoy.admin.v2alpha.ScopedRoutesConfigDump.DynamicScopedRouteConfigs:1\x9a\xc5\x88\x1e,\n*envoy.admin.v2alpha.ScopedRoutesConfigDump\"\xcd\x04\n\x13\x45ndpointsConfigDump\x12Y\n\x17static_endpoint_configs\x18\x02 \x03(\x0b\x32\x38.envoy.admin.v3.EndpointsConfigDump.StaticEndpointConfig\x12[\n\x18\x64ynamic_endpoint_configs\x18\x03 \x03(\x0b\x32\x39.envoy.admin.v3.EndpointsConfigDump.DynamicEndpointConfig\x1aw\n\x14StaticEndpointConfig\x12-\n\x0f\x65ndpoint_config\x18\x01 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x1a\x84\x02\n\x15\x44ynamicEndpointConfig\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12-\n\x0f\x65ndpoint_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x0b\x65rror_state\x18\x04 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x05 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus\"\xbc\x03\n\x0e\x45\x63\x64sConfigDump\x12\x45\n\x0c\x65\x63\x64s_filters\x18\x01 \x03(\x0b\x32/.envoy.admin.v3.EcdsConfigDump.EcdsFilterConfig\x1a\xb7\x02\n\x10\x45\x63\x64sFilterConfig\x12\x14\n\x0cversion_info\x18\x01 \x01(\t\x12)\n\x0b\x65\x63\x64s_filter\x18\x02 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x03 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12\x37\n\x0b\x65rror_state\x18\x04 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12;\n\rclient_status\x18\x05 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus::\x9a\xc5\x88\x1e\x35\n3envoy.admin.v2alpha.EcdsConfigDump.EcdsFilterConfig:)\x9a\xc5\x88\x1e$\n\"envoy.admin.v2alpha.EcdsConfigDump*~\n\x14\x43lientResourceStatus\x12\x0b\n\x07UNKNOWN\x10\x00\x12\r\n\tREQUESTED\x10\x01\x12\x12\n\x0e\x44OES_NOT_EXIST\x10\x02\x12\t\n\x05\x41\x43KED\x10\x03\x12\n\n\x06NACKED\x10\x04\x12\x12\n\x0eRECEIVED_ERROR\x10\x05\x12\x0b\n\x07TIMEOUT\x10\x06\x42~\n\x1cio.envoyproxy.envoy.admin.v3B\x15\x43onfigDumpSharedProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.config_dump_shared_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\025ConfigDumpSharedProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
  _UPDATEFAILURESTATE._options = None
  _UPDATEFAILURESTATE._serialized_options = b'\232\305\210\036(\n&envoy.admin.v2alpha.UpdateFailureState'
  _LISTENERSCONFIGDUMP_STATICLISTENER._options = None
  _LISTENERSCONFIGDUMP_STATICLISTENER._serialized_options = b'\232\305\210\0368\n6envoy.admin.v2alpha.ListenersConfigDump.StaticListener'
  _LISTENERSCONFIGDUMP_DYNAMICLISTENERSTATE._options = None
  _LISTENERSCONFIGDUMP_DYNAMICLISTENERSTATE._serialized_options = b'\232\305\210\036>\n<envoy.admin.v2alpha.ListenersConfigDump.DynamicListenerState'
  _LISTENERSCONFIGDUMP_DYNAMICLISTENER._options = None
  _LISTENERSCONFIGDUMP_DYNAMICLISTENER._serialized_options = b'\232\305\210\0369\n7envoy.admin.v2alpha.ListenersConfigDump.DynamicListener'
  _LISTENERSCONFIGDUMP._options = None
  _LISTENERSCONFIGDUMP._serialized_options = b'\232\305\210\036)\n\'envoy.admin.v2alpha.ListenersConfigDump'
  _CLUSTERSCONFIGDUMP_STATICCLUSTER._options = None
  _CLUSTERSCONFIGDUMP_STATICCLUSTER._serialized_options = b'\232\305\210\0366\n4envoy.admin.v2alpha.ClustersConfigDump.StaticCluster'
  _CLUSTERSCONFIGDUMP_DYNAMICCLUSTER._options = None
  _CLUSTERSCONFIGDUMP_DYNAMICCLUSTER._serialized_options = b'\232\305\210\0367\n5envoy.admin.v2alpha.ClustersConfigDump.DynamicCluster'
  _CLUSTERSCONFIGDUMP._options = None
  _CLUSTERSCONFIGDUMP._serialized_options = b'\232\305\210\036(\n&envoy.admin.v2alpha.ClustersConfigDump'
  _ROUTESCONFIGDUMP_STATICROUTECONFIG._options = None
  _ROUTESCONFIGDUMP_STATICROUTECONFIG._serialized_options = b'\232\305\210\0368\n6envoy.admin.v2alpha.RoutesConfigDump.StaticRouteConfig'
  _ROUTESCONFIGDUMP_DYNAMICROUTECONFIG._options = None
  _ROUTESCONFIGDUMP_DYNAMICROUTECONFIG._serialized_options = b'\232\305\210\0369\n7envoy.admin.v2alpha.RoutesConfigDump.DynamicRouteConfig'
  _ROUTESCONFIGDUMP._options = None
  _ROUTESCONFIGDUMP._serialized_options = b'\232\305\210\036&\n$envoy.admin.v2alpha.RoutesConfigDump'
  _SCOPEDROUTESCONFIGDUMP_INLINESCOPEDROUTECONFIGS._options = None
  _SCOPEDROUTESCONFIGDUMP_INLINESCOPEDROUTECONFIGS._serialized_options = b'\232\305\210\036E\nCenvoy.admin.v2alpha.ScopedRoutesConfigDump.InlineScopedRouteConfigs'
  _SCOPEDROUTESCONFIGDUMP_DYNAMICSCOPEDROUTECONFIGS._options = None
  _SCOPEDROUTESCONFIGDUMP_DYNAMICSCOPEDROUTECONFIGS._serialized_options = b'\232\305\210\036F\nDenvoy.admin.v2alpha.ScopedRoutesConfigDump.DynamicScopedRouteConfigs'
  _SCOPEDROUTESCONFIGDUMP._options = None
  _SCOPEDROUTESCONFIGDUMP._serialized_options = b'\232\305\210\036,\n*envoy.admin.v2alpha.ScopedRoutesConfigDump'
  _ECDSCONFIGDUMP_ECDSFILTERCONFIG._options = None
  _ECDSCONFIGDUMP_ECDSFILTERCONFIG._serialized_options = b'\232\305\210\0365\n3envoy.admin.v2alpha.EcdsConfigDump.EcdsFilterConfig'
  _ECDSCONFIGDUMP._options = None
  _ECDSCONFIGDUMP._serialized_options = b'\232\305\210\036$\n\"envoy.admin.v2alpha.EcdsConfigDump'
  _globals['_CLIENTRESOURCESTATUS']._serialized_start=4945
  _globals['_CLIENTRESOURCESTATUS']._serialized_end=5071
  _globals['_UPDATEFAILURESTATE']._serialized_start=186
  _globals['_UPDATEFAILURESTATE']._serialized_end=401
  _globals['_LISTENERSCONFIGDUMP']._serialized_start=404
  _globals['_LISTENERSCONFIGDUMP']._serialized_end=1490
  _globals['_LISTENERSCONFIGDUMP_STATICLISTENER']._serialized_start=608
  _globals['_LISTENERSCONFIGDUMP_STATICLISTENER']._serialized_end=777
  _globals['_LISTENERSCONFIGDUMP_DYNAMICLISTENERSTATE']._serialized_start=780
  _globals['_LISTENERSCONFIGDUMP_DYNAMICLISTENERSTATE']._serialized_end=983
  _globals['_LISTENERSCONFIGDUMP_DYNAMICLISTENER']._serialized_start=986
  _globals['_LISTENERSCONFIGDUMP_DYNAMICLISTENER']._serialized_end=1442
  _globals['_CLUSTERSCONFIGDUMP']._serialized_start=1493
  _globals['_CLUSTERSCONFIGDUMP']._serialized_end=2304
  _globals['_CLUSTERSCONFIGDUMP_STATICCLUSTER']._serialized_start=1782
  _globals['_CLUSTERSCONFIGDUMP_STATICCLUSTER']._serialized_end=1947
  _globals['_CLUSTERSCONFIGDUMP_DYNAMICCLUSTER']._serialized_start=1950
  _globals['_CLUSTERSCONFIGDUMP_DYNAMICCLUSTER']._serialized_end=2257
  _globals['_ROUTESCONFIGDUMP']._serialized_start=2307
  _globals['_ROUTESCONFIGDUMP']._serialized_end=3036
  _globals['_ROUTESCONFIGDUMP_STATICROUTECONFIG']._serialized_start=2494
  _globals['_ROUTESCONFIGDUMP_STATICROUTECONFIG']._serialized_end=2670
  _globals['_ROUTESCONFIGDUMP_DYNAMICROUTECONFIG']._serialized_start=2673
  _globals['_ROUTESCONFIGDUMP_DYNAMICROUTECONFIG']._serialized_end=2991
  _globals['_SCOPEDROUTESCONFIGDUMP']._serialized_start=3039
  _globals['_SCOPEDROUTESCONFIGDUMP']._serialized_end=3904
  _globals['_SCOPEDROUTESCONFIGDUMP_INLINESCOPEDROUTECONFIGS']._serialized_start=3272
  _globals['_SCOPEDROUTESCONFIGDUMP_INLINESCOPEDROUTECONFIGS']._serialized_end=3490
  _globals['_SCOPEDROUTESCONFIGDUMP_DYNAMICSCOPEDROUTECONFIGS']._serialized_start=3493
  _globals['_SCOPEDROUTESCONFIGDUMP_DYNAMICSCOPEDROUTECONFIGS']._serialized_end=3853
  _globals['_ENDPOINTSCONFIGDUMP']._serialized_start=3907
  _globals['_ENDPOINTSCONFIGDUMP']._serialized_end=4496
  _globals['_ENDPOINTSCONFIGDUMP_STATICENDPOINTCONFIG']._serialized_start=4114
  _globals['_ENDPOINTSCONFIGDUMP_STATICENDPOINTCONFIG']._serialized_end=4233
  _globals['_ENDPOINTSCONFIGDUMP_DYNAMICENDPOINTCONFIG']._serialized_start=4236
  _globals['_ENDPOINTSCONFIGDUMP_DYNAMICENDPOINTCONFIG']._serialized_end=4496
  _globals['_ECDSCONFIGDUMP']._serialized_start=4499
  _globals['_ECDSCONFIGDUMP']._serialized_end=4943
  _globals['_ECDSCONFIGDUMP_ECDSFILTERCONFIG']._serialized_start=4589
  _globals['_ECDSCONFIGDUMP_ECDSFILTERCONFIG']._serialized_end=4900
