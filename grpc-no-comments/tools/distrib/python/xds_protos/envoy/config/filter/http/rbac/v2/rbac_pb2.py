
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.rbac.v2 import rbac_pb2 as envoy_dot_config_dot_rbac_dot_v2_dot_rbac__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+envoy/config/filter/http/rbac/v2/rbac.proto\x12 envoy.config.filter.http.rbac.v2\x1a\x1f\x65nvoy/config/rbac/v2/rbac.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"c\n\x04RBAC\x12)\n\x05rules\x18\x01 \x01(\x0b\x32\x1a.envoy.config.rbac.v2.RBAC\x12\x30\n\x0cshadow_rules\x18\x02 \x01(\x0b\x32\x1a.envoy.config.rbac.v2.RBAC\"J\n\x0cRBACPerRoute\x12\x34\n\x04rbac\x18\x02 \x01(\x0b\x32&.envoy.config.filter.http.rbac.v2.RBACJ\x04\x08\x01\x10\x02\x42\xc2\x01\n.io.envoyproxy.envoy.config.filter.http.rbac.v2B\tRbacProtoP\x01ZNgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/rbac/v2;rbacv2\xf2\x98\xfe\x8f\x05\'\x12%envoy.extensions.filters.http.rbac.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.rbac.v2.rbac_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n.io.envoyproxy.envoy.config.filter.http.rbac.v2B\tRbacProtoP\001ZNgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/rbac/v2;rbacv2\362\230\376\217\005\'\022%envoy.extensions.filters.http.rbac.v3\272\200\310\321\006\002\020\001'
  _globals['_RBAC']._serialized_start=177
  _globals['_RBAC']._serialized_end=276
  _globals['_RBACPERROUTE']._serialized_start=278
  _globals['_RBACPERROUTE']._serialized_end=352
