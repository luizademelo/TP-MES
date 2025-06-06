
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.rbac.v2 import rbac_pb2 as envoy_dot_config_dot_rbac_dot_v2_dot_rbac__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n.envoy/config/filter/network/rbac/v2/rbac.proto\x12#envoy.config.filter.network.rbac.v2\x1a\x1f\x65nvoy/config/rbac/v2/rbac.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x95\x02\n\x04RBAC\x12)\n\x05rules\x18\x01 \x01(\x0b\x32\x1a.envoy.config.rbac.v2.RBAC\x12\x30\n\x0cshadow_rules\x18\x02 \x01(\x0b\x32\x1a.envoy.config.rbac.v2.RBAC\x12\x1c\n\x0bstat_prefix\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12S\n\x10\x65nforcement_type\x18\x04 \x01(\x0e\x32\x39.envoy.config.filter.network.rbac.v2.RBAC.EnforcementType\"=\n\x0f\x45nforcementType\x12\x1a\n\x16ONE_TIME_ON_FIRST_BYTE\x10\x00\x12\x0e\n\nCONTINUOUS\x10\x01\x42\xcb\x01\n1io.envoyproxy.envoy.config.filter.network.rbac.v2B\tRbacProtoP\x01ZQgithub.com/envoyproxy/go-control-plane/envoy/config/filter/network/rbac/v2;rbacv2\xf2\x98\xfe\x8f\x05*\x12(envoy.extensions.filters.network.rbac.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.network.rbac.v2.rbac_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n1io.envoyproxy.envoy.config.filter.network.rbac.v2B\tRbacProtoP\001ZQgithub.com/envoyproxy/go-control-plane/envoy/config/filter/network/rbac/v2;rbacv2\362\230\376\217\005*\022(envoy.extensions.filters.network.rbac.v3\272\200\310\321\006\002\020\001'
  _RBAC.fields_by_name['stat_prefix']._options = None
  _RBAC.fields_by_name['stat_prefix']._serialized_options = b'\372B\004r\002 \001'
  _globals['_RBAC']._serialized_start=209
  _globals['_RBAC']._serialized_end=486
  _globals['_RBAC_ENFORCEMENTTYPE']._serialized_start=425
  _globals['_RBAC_ENFORCEMENTTYPE']._serialized_end=486
