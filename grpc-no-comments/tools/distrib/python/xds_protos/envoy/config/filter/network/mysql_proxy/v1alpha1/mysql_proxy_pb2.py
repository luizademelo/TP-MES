
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nBenvoy/config/filter/network/mysql_proxy/v1alpha1/mysql_proxy.proto\x12\x30\x65nvoy.config.filter.network.mysql_proxy.v1alpha1\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\">\n\nMySQLProxy\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x12\n\naccess_log\x18\x02 \x01(\tB\xeb\x01\n>io.envoyproxy.envoy.config.filter.network.mysql_proxy.v1alpha1B\x0fMysqlProxyProtoP\x01ZWgithub.com/envoyproxy/go-control-plane/envoy/config/filter/network/mysql_proxy/v1alpha1\xf2\x98\xfe\x8f\x05\x31\x12/envoy.extensions.filters.network.mysql_proxy.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.network.mysql_proxy.v1alpha1.mysql_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.config.filter.network.mysql_proxy.v1alpha1B\017MysqlProxyProtoP\001ZWgithub.com/envoyproxy/go-control-plane/envoy/config/filter/network/mysql_proxy/v1alpha1\362\230\376\217\0051\022/envoy.extensions.filters.network.mysql_proxy.v3\272\200\310\321\006\002\020\001'
  _MYSQLPROXY.fields_by_name['stat_prefix']._options = None
  _MYSQLPROXY.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002 \001'
  _globals['_MYSQLPROXY']._serialized_start=208
  _globals['_MYSQLPROXY']._serialized_end=270
