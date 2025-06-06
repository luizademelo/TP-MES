
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nTcontrib/envoy/extensions/filters/network/postgres_proxy/v3alpha/postgres_proxy.proto\x12\x37\x65nvoy.extensions.filters.network.postgres_proxy.v3alpha\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x87\x02\n\rPostgresProxy\x12\x1c\n\x0bstat_prefix\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x36\n\x12\x65nable_sql_parsing\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x15\n\rterminate_ssl\x18\x03 \x01(\x08\x12\x64\n\x0cupstream_ssl\x18\x04 \x01(\x0e\x32N.envoy.extensions.filters.network.postgres_proxy.v3alpha.PostgresProxy.SSLMode\"#\n\x07SSLMode\x12\x0b\n\x07\x44ISABLE\x10\x00\x12\x0b\n\x07REQUIRE\x10\x01\x42\xcf\x01\nEio.envoyproxy.envoy.extensions.filters.network.postgres_proxy.v3alphaB\x12PostgresProxyProtoP\x01Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/postgres_proxy/v3alpha\xba\x80\xc8\xd1\x06\x04\x08\x01\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.filters.network.postgres_proxy.v3alpha.postgres_proxy_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.extensions.filters.network.postgres_proxy.v3alphaB\022PostgresProxyProtoP\001Zfgithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/postgres_proxy/v3alpha\272\200\310\321\006\004\010\001\020\002'
  _POSTGRESPROXY.fields_by_name['stat_prefix']._options = None
  _POSTGRESPROXY.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_POSTGRESPROXY']._serialized_start=234
  _globals['_POSTGRESPROXY']._serialized_end=497
  _globals['_POSTGRESPROXY_SSLMODE']._serialized_start=462
  _globals['_POSTGRESPROXY_SSLMODE']._serialized_end=497
