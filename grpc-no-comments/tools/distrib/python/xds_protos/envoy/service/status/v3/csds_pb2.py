
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.admin.v3 import config_dump_shared_pb2 as envoy_dot_admin_dot_v3_dot_config__dump__shared__pb2
from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.type.matcher.v3 import node_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_node__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import timestamp_pb2 as google_dot_protobuf_dot_timestamp__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"envoy/service/status/v3/csds.proto\x12\x17\x65nvoy.service.status.v3\x1a\'envoy/admin/v3/config_dump_shared.proto\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a envoy/type/matcher/v3/node.proto\x1a\x1cgoogle/api/annotations.proto\x1a\x19google/protobuf/any.proto\x1a\x1fgoogle/protobuf/timestamp.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xd1\x01\n\x13\x43lientStatusRequest\x12\x39\n\rnode_matchers\x18\x01 \x03(\x0b\x32\".envoy.type.matcher.v3.NodeMatcher\x12(\n\x04node\x18\x02 \x01(\x0b\x32\x1a.envoy.config.core.v3.Node\x12!\n\x19\x65xclude_resource_contents\x18\x03 \x01(\x08:2\x9a\xc5\x88\x1e-\n+envoy.service.status.v2.ClientStatusRequest\"\x94\x04\n\x0cPerXdsConfig\x12\x35\n\x06status\x18\x01 \x01(\x0e\x32%.envoy.service.status.v3.ConfigStatus\x12O\n\rclient_status\x18\x07 \x01(\x0e\x32+.envoy.service.status.v3.ClientConfigStatusB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12>\n\x0flistener_config\x18\x02 \x01(\x0b\x32#.envoy.admin.v3.ListenersConfigDumpH\x00\x12<\n\x0e\x63luster_config\x18\x03 \x01(\x0b\x32\".envoy.admin.v3.ClustersConfigDumpH\x00\x12\x38\n\x0croute_config\x18\x04 \x01(\x0b\x32 .envoy.admin.v3.RoutesConfigDumpH\x00\x12\x45\n\x13scoped_route_config\x18\x05 \x01(\x0b\x32&.envoy.admin.v3.ScopedRoutesConfigDumpH\x00\x12>\n\x0f\x65ndpoint_config\x18\x06 \x01(\x0b\x32#.envoy.admin.v3.EndpointsConfigDumpH\x00:+\x9a\xc5\x88\x1e&\n$envoy.service.status.v2.PerXdsConfigB\x10\n\x0eper_xds_config\"\x8f\x05\n\x0c\x43lientConfig\x12(\n\x04node\x18\x01 \x01(\x0b\x32\x1a.envoy.config.core.v3.Node\x12\x46\n\nxds_config\x18\x02 \x03(\x0b\x32%.envoy.service.status.v3.PerXdsConfigB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0\x12S\n\x13generic_xds_configs\x18\x03 \x03(\x0b\x32\x36.envoy.service.status.v3.ClientConfig.GenericXdsConfig\x12\x14\n\x0c\x63lient_scope\x18\x04 \x01(\t\x1a\xf4\x02\n\x10GenericXdsConfig\x12\x10\n\x08type_url\x18\x01 \x01(\t\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x14\n\x0cversion_info\x18\x03 \x01(\t\x12(\n\nxds_config\x18\x04 \x01(\x0b\x32\x14.google.protobuf.Any\x12\x30\n\x0clast_updated\x18\x05 \x01(\x0b\x32\x1a.google.protobuf.Timestamp\x12<\n\rconfig_status\x18\x06 \x01(\x0e\x32%.envoy.service.status.v3.ConfigStatus\x12;\n\rclient_status\x18\x07 \x01(\x0e\x32$.envoy.admin.v3.ClientResourceStatus\x12\x37\n\x0b\x65rror_state\x18\x08 \x01(\x0b\x32\".envoy.admin.v3.UpdateFailureState\x12\x1a\n\x12is_static_resource\x18\t \x01(\x08:+\x9a\xc5\x88\x1e&\n$envoy.service.status.v2.ClientConfig\"\x82\x01\n\x14\x43lientStatusResponse\x12\x35\n\x06\x63onfig\x18\x01 \x03(\x0b\x32%.envoy.service.status.v3.ClientConfig:3\x9a\xc5\x88\x1e.\n,envoy.service.status.v2.ClientStatusResponse*K\n\x0c\x43onfigStatus\x12\x0b\n\x07UNKNOWN\x10\x00\x12\n\n\x06SYNCED\x10\x01\x12\x0c\n\x08NOT_SENT\x10\x02\x12\t\n\x05STALE\x10\x03\x12\t\n\x05\x45RROR\x10\x04*~\n\x12\x43lientConfigStatus\x12\x12\n\x0e\x43LIENT_UNKNOWN\x10\x00\x12\x14\n\x10\x43LIENT_REQUESTED\x10\x01\x12\x10\n\x0c\x43LIENT_ACKED\x10\x02\x12\x11\n\rCLIENT_NACKED\x10\x03\x12\x19\n\x15\x43LIENT_RECEIVED_ERROR\x10\x04\x32\xb2\x02\n\x1c\x43lientStatusDiscoveryService\x12w\n\x12StreamClientStatus\x12,.envoy.service.status.v3.ClientStatusRequest\x1a-.envoy.service.status.v3.ClientStatusResponse\"\x00(\x01\x30\x01\x12\x98\x01\n\x11\x46\x65tchClientStatus\x12,.envoy.service.status.v3.ClientStatusRequest\x1a-.envoy.service.status.v3.ClientStatusResponse\"&\x82\xd3\xe4\x93\x02 \"\x1b/v3/discovery:client_status:\x01*B\x85\x01\n%io.envoyproxy.envoy.service.status.v3B\tCsdsProtoP\x01ZGgithub.com/envoyproxy/go-control-plane/envoy/service/status/v3;statusv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.status.v3.csds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.service.status.v3B\tCsdsProtoP\001ZGgithub.com/envoyproxy/go-control-plane/envoy/service/status/v3;statusv3\272\200\310\321\006\002\020\002'
  _CLIENTSTATUSREQUEST._options = None
  _CLIENTSTATUSREQUEST._serialized_options = b'\232\305\210\036-\n+envoy.service.status.v2.ClientStatusRequest'
  _PERXDSCONFIG.fields_by_name['client_status']._options = None
  _PERXDSCONFIG.fields_by_name['client_status']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _PERXDSCONFIG._options = None
  _PERXDSCONFIG._serialized_options = b'\232\305\210\036&\n$envoy.service.status.v2.PerXdsConfig'
  _CLIENTCONFIG.fields_by_name['xds_config']._options = None
  _CLIENTCONFIG.fields_by_name['xds_config']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _CLIENTCONFIG._options = None
  _CLIENTCONFIG._serialized_options = b'\232\305\210\036&\n$envoy.service.status.v2.ClientConfig'
  _CLIENTSTATUSRESPONSE._options = None
  _CLIENTSTATUSRESPONSE._serialized_options = b'\232\305\210\036.\n,envoy.service.status.v2.ClientStatusResponse'
  _CLIENTSTATUSDISCOVERYSERVICE.methods_by_name['FetchClientStatus']._options = None
  _CLIENTSTATUSDISCOVERYSERVICE.methods_by_name['FetchClientStatus']._serialized_options = b'\202\323\344\223\002 \"\033/v3/discovery:client_status:\001*'
  _globals['_CONFIGSTATUS']._serialized_start=1902
  _globals['_CONFIGSTATUS']._serialized_end=1977
  _globals['_CLIENTCONFIGSTATUS']._serialized_start=1979
  _globals['_CLIENTCONFIGSTATUS']._serialized_end=2105
  _globals['_CLIENTSTATUSREQUEST']._serialized_start=365
  _globals['_CLIENTSTATUSREQUEST']._serialized_end=574
  _globals['_PERXDSCONFIG']._serialized_start=577
  _globals['_PERXDSCONFIG']._serialized_end=1109
  _globals['_CLIENTCONFIG']._serialized_start=1112
  _globals['_CLIENTCONFIG']._serialized_end=1767
  _globals['_CLIENTCONFIG_GENERICXDSCONFIG']._serialized_start=1350
  _globals['_CLIENTCONFIG_GENERICXDSCONFIG']._serialized_end=1722
  _globals['_CLIENTSTATUSRESPONSE']._serialized_start=1770
  _globals['_CLIENTSTATUSRESPONSE']._serialized_end=1900
  _globals['_CLIENTSTATUSDISCOVERYSERVICE']._serialized_start=2108
  _globals['_CLIENTSTATUSDISCOVERYSERVICE']._serialized_end=2414
