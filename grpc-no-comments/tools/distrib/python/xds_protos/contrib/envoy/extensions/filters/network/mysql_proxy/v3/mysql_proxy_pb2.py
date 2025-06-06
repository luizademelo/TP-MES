
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nIcontrib/envoy/extensions/filters/network/mysql_proxy/v3/mysql_proxy.proto\x12/envoy.extensions.filters.network.mysql_proxy.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x82\x01\n\nMySQLProxy\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x12\n\naccess_log\x18\x02 \x01(\t:B\x9a\xc5\x88\x1e=\n;envoy.config.filter.network.mysql_proxy.v1alpha1.MySQLProxyB\xc8\x01\n=io.envoyproxy.envoy.extensions.filters.network.mysql_proxy.v3B\x0fMysqlProxyProtoP\x01Zlgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/mysql_proxy/v3;mysql_proxyv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.filters.network.mysql_proxy.v3.mysql_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n=io.envoyproxy.envoy.extensions.filters.network.mysql_proxy.v3B\017MysqlProxyProtoP\001Zlgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/mysql_proxy/v3;mysql_proxyv3\272\200\310\321\006\002\020\002'
  _MYSQLPROXY.fields_by_name['stat_prefix']._options = None
  _MYSQLPROXY.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _MYSQLPROXY._options = None
  _MYSQLPROXY._serialized_options = b'\232\305\210\036=\n;envoy.config.filter.network.mysql_proxy.v1alpha1.MySQLProxy'
  _globals['_MYSQLPROXY']._serialized_start=218
  _globals['_MYSQLPROXY']._serialized_end=348
