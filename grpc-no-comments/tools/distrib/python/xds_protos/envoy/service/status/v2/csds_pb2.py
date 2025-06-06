
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.admin.v2alpha import config_dump_pb2 as envoy_dot_admin_dot_v2alpha_dot_config__dump__pb2
from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from envoy.type.matcher import node_pb2 as envoy_dot_type_dot_matcher_dot_node__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"envoy/service/status/v2/csds.proto\x12\x17\x65nvoy.service.status.v2\x1a%envoy/admin/v2alpha/config_dump.proto\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a\x1d\x65nvoy/type/matcher/node.proto\x1a\x1cgoogle/api/annotations.proto\x1a\x1dudpa/annotations/status.proto\"M\n\x13\x43lientStatusRequest\x12\x36\n\rnode_matchers\x18\x01 \x03(\x0b\x32\x1f.envoy.type.matcher.NodeMatcher\"\xea\x02\n\x0cPerXdsConfig\x12\x35\n\x06status\x18\x01 \x01(\x0e\x32%.envoy.service.status.v2.ConfigStatus\x12\x43\n\x0flistener_config\x18\x02 \x01(\x0b\x32(.envoy.admin.v2alpha.ListenersConfigDumpH\x00\x12\x41\n\x0e\x63luster_config\x18\x03 \x01(\x0b\x32\'.envoy.admin.v2alpha.ClustersConfigDumpH\x00\x12=\n\x0croute_config\x18\x04 \x01(\x0b\x32%.envoy.admin.v2alpha.RoutesConfigDumpH\x00\x12J\n\x13scoped_route_config\x18\x05 \x01(\x0b\x32+.envoy.admin.v2alpha.ScopedRoutesConfigDumpH\x00\x42\x10\n\x0eper_xds_config\"p\n\x0c\x43lientConfig\x12%\n\x04node\x18\x01 \x01(\x0b\x32\x17.envoy.api.v2.core.Node\x12\x39\n\nxds_config\x18\x02 \x03(\x0b\x32%.envoy.service.status.v2.PerXdsConfig\"M\n\x14\x43lientStatusResponse\x12\x35\n\x06\x63onfig\x18\x01 \x03(\x0b\x32%.envoy.service.status.v2.ClientConfig*K\n\x0c\x43onfigStatus\x12\x0b\n\x07UNKNOWN\x10\x00\x12\n\n\x06SYNCED\x10\x01\x12\x0c\n\x08NOT_SENT\x10\x02\x12\t\n\x05STALE\x10\x03\x12\t\n\x05\x45RROR\x10\x04\x32\xb2\x02\n\x1c\x43lientStatusDiscoveryService\x12w\n\x12StreamClientStatus\x12,.envoy.service.status.v2.ClientStatusRequest\x1a-.envoy.service.status.v2.ClientStatusResponse\"\x00(\x01\x30\x01\x12\x98\x01\n\x11\x46\x65tchClientStatus\x12,.envoy.service.status.v2.ClientStatusRequest\x1a-.envoy.service.status.v2.ClientStatusResponse\"&\x82\xd3\xe4\x93\x02 \"\x1b/v2/discovery:client_status:\x01*B\x85\x01\n%io.envoyproxy.envoy.service.status.v2B\tCsdsProtoP\x01ZGgithub.com/envoyproxy/go-control-plane/envoy/service/status/v2;statusv2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.status.v2.csds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.service.status.v2B\tCsdsProtoP\001ZGgithub.com/envoyproxy/go-control-plane/envoy/service/status/v2;statusv2\272\200\310\321\006\002\020\001'
  _CLIENTSTATUSDISCOVERYSERVICE.methods_by_name['FetchClientStatus']._options = None
  _CLIENTSTATUSDISCOVERYSERVICE.methods_by_name['FetchClientStatus']._serialized_options = b'\202\323\344\223\002 \"\033/v2/discovery:client_status:\001*'
  _globals['_CONFIGSTATUS']._serialized_start=861
  _globals['_CONFIGSTATUS']._serialized_end=936
  _globals['_CLIENTSTATUSREQUEST']._serialized_start=224
  _globals['_CLIENTSTATUSREQUEST']._serialized_end=301
  _globals['_PERXDSCONFIG']._serialized_start=304
  _globals['_PERXDSCONFIG']._serialized_end=666
  _globals['_CLIENTCONFIG']._serialized_start=668
  _globals['_CLIENTCONFIG']._serialized_end=780
  _globals['_CLIENTSTATUSRESPONSE']._serialized_start=782
  _globals['_CLIENTSTATUSRESPONSE']._serialized_end=859
  _globals['_CLIENTSTATUSDISCOVERYSERVICE']._serialized_start=939
  _globals['_CLIENTSTATUSDISCOVERYSERVICE']._serialized_end=1245
