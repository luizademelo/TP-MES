
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import address_pb2 as envoy_dot_config_dot_core_dot_v3_dot_address__pb2
from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from envoy.config.route.v3 import route_components_pb2 as envoy_dot_config_dot_route_dot_v3_dot_route__components__pb2
from envoy.type.matcher.v3 import filter_state_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_filter__state__pb2
from envoy.type.matcher.v3 import metadata_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_metadata__pb2
from envoy.type.matcher.v3 import path_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_path__pb2
from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from envoy.type.v3 import range_pb2 as envoy_dot_type_dot_v3_dot_range__pb2
from google.api.expr.v1alpha1 import checked_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_checked__pb2
from google.api.expr.v1alpha1 import syntax_pb2 as google_dot_api_dot_expr_dot_v1alpha1_dot_syntax__pb2
from envoy.annotations import deprecation_pb2 as envoy_dot_annotations_dot_deprecation__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/config/rbac/v3/rbac.proto\x12\x14\x65nvoy.config.rbac.v3\x1a\"envoy/config/core/v3/address.proto\x1a$envoy/config/core/v3/extension.proto\x1a,envoy/config/route/v3/route_components.proto\x1a(envoy/type/matcher/v3/filter_state.proto\x1a$envoy/type/matcher/v3/metadata.proto\x1a envoy/type/matcher/v3/path.proto\x1a\"envoy/type/matcher/v3/string.proto\x1a\x19\x65nvoy/type/v3/range.proto\x1a&google/api/expr/v1alpha1/checked.proto\x1a%google/api/expr/v1alpha1/syntax.proto\x1a#envoy/annotations/deprecation.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\xf5\x05\n\x04RBAC\x12;\n\x06\x61\x63tion\x18\x01 \x01(\x0e\x32!.envoy.config.rbac.v3.RBAC.ActionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12:\n\x08policies\x18\x02 \x03(\x0b\x32(.envoy.config.rbac.v3.RBAC.PoliciesEntry\x12M\n\x15\x61udit_logging_options\x18\x03 \x01(\x0b\x32..envoy.config.rbac.v3.RBAC.AuditLoggingOptions\x1a\x8b\x03\n\x13\x41uditLoggingOptions\x12`\n\x0f\x61udit_condition\x18\x01 \x01(\x0e\x32=.envoy.config.rbac.v3.RBAC.AuditLoggingOptions.AuditConditionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12X\n\x0elogger_configs\x18\x02 \x03(\x0b\x32@.envoy.config.rbac.v3.RBAC.AuditLoggingOptions.AuditLoggerConfig\x1aj\n\x11\x41uditLoggerConfig\x12@\n\x0c\x61udit_logger\x18\x01 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x13\n\x0bis_optional\x18\x02 \x01(\x08\"L\n\x0e\x41uditCondition\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x07ON_DENY\x10\x01\x12\x0c\n\x08ON_ALLOW\x10\x02\x12\x15\n\x11ON_DENY_AND_ALLOW\x10\x03\x1aM\n\rPoliciesEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12+\n\x05value\x18\x02 \x01(\x0b\x32\x1c.envoy.config.rbac.v3.Policy:\x02\x38\x01\"&\n\x06\x41\x63tion\x12\t\n\x05\x41LLOW\x10\x00\x12\x08\n\x04\x44\x45NY\x10\x01\x12\x07\n\x03LOG\x10\x02: \x9a\xc5\x88\x1e\x1b\n\x19\x65nvoy.config.rbac.v2.RBAC\"\xdd\x02\n\x06Policy\x12?\n\x0bpermissions\x18\x01 \x03(\x0b\x32 .envoy.config.rbac.v3.PermissionB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12=\n\nprincipals\x18\x02 \x03(\x0b\x32\x1f.envoy.config.rbac.v3.PrincipalB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x12O\n\tcondition\x18\x03 \x01(\x0b\x32\x1e.google.api.expr.v1alpha1.ExprB\x1c\xf2\x98\xfe\x8f\x05\x16\x12\x14\x65xpression_specifier\x12^\n\x11\x63hecked_condition\x18\x04 \x01(\x0b\x32%.google.api.expr.v1alpha1.CheckedExprB\x1c\xf2\x98\xfe\x8f\x05\x16\x12\x14\x65xpression_specifier:\"\x9a\xc5\x88\x1e\x1d\n\x1b\x65nvoy.config.rbac.v2.Policy\"\xa6\x01\n\x0fSourcedMetadata\x12J\n\x10metadata_matcher\x18\x01 \x01(\x0b\x32&.envoy.type.matcher.v3.MetadataMatcherB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12G\n\x0fmetadata_source\x18\x02 \x01(\x0e\x32$.envoy.config.rbac.v3.MetadataSourceB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"\xd7\x07\n\nPermission\x12\x39\n\tand_rules\x18\x01 \x01(\x0b\x32$.envoy.config.rbac.v3.Permission.SetH\x00\x12\x38\n\x08or_rules\x18\x02 \x01(\x0b\x32$.envoy.config.rbac.v3.Permission.SetH\x00\x12\x16\n\x03\x61ny\x18\x03 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12\x36\n\x06header\x18\x04 \x01(\x0b\x32$.envoy.config.route.v3.HeaderMatcherH\x00\x12\x36\n\x08url_path\x18\n \x01(\x0b\x32\".envoy.type.matcher.v3.PathMatcherH\x00\x12\x39\n\x0e\x64\x65stination_ip\x18\x05 \x01(\x0b\x32\x1f.envoy.config.core.v3.CidrRangeH\x00\x12%\n\x10\x64\x65stination_port\x18\x06 \x01(\rB\t\xfa\x42\x06*\x04\x18\xff\xff\x03H\x00\x12;\n\x16\x64\x65stination_port_range\x18\x0b \x01(\x0b\x32\x19.envoy.type.v3.Int32RangeH\x00\x12G\n\x08metadata\x18\x07 \x01(\x0b\x32&.envoy.type.matcher.v3.MetadataMatcherB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\x34\n\x08not_rule\x18\x08 \x01(\x0b\x32 .envoy.config.rbac.v3.PermissionH\x00\x12\x45\n\x15requested_server_name\x18\t \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcherH\x00\x12=\n\x07matcher\x18\x0c \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfigH\x00\x12\x42\n\x0curi_template\x18\r \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfigH\x00\x12\x41\n\x10sourced_metadata\x18\x0e \x01(\x0b\x32%.envoy.config.rbac.v3.SourcedMetadataH\x00\x1al\n\x03Set\x12\x39\n\x05rules\x18\x01 \x03(\x0b\x32 .envoy.config.rbac.v3.PermissionB\x08\xfa\x42\x05\x92\x01\x02\x08\x01:*\x9a\xc5\x88\x1e%\n#envoy.config.rbac.v2.Permission.Set:&\x9a\xc5\x88\x1e!\n\x1f\x65nvoy.config.rbac.v2.PermissionB\x0b\n\x04rule\x12\x03\xf8\x42\x01\"\xb1\x08\n\tPrincipal\x12\x36\n\x07\x61nd_ids\x18\x01 \x01(\x0b\x32#.envoy.config.rbac.v3.Principal.SetH\x00\x12\x35\n\x06or_ids\x18\x02 \x01(\x0b\x32#.envoy.config.rbac.v3.Principal.SetH\x00\x12\x16\n\x03\x61ny\x18\x03 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12\x46\n\rauthenticated\x18\x04 \x01(\x0b\x32-.envoy.config.rbac.v3.Principal.AuthenticatedH\x00\x12\x41\n\tsource_ip\x18\x05 \x01(\x0b\x32\x1f.envoy.config.core.v3.CidrRangeB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12;\n\x10\x64irect_remote_ip\x18\n \x01(\x0b\x32\x1f.envoy.config.core.v3.CidrRangeH\x00\x12\x34\n\tremote_ip\x18\x0b \x01(\x0b\x32\x1f.envoy.config.core.v3.CidrRangeH\x00\x12\x36\n\x06header\x18\x06 \x01(\x0b\x32$.envoy.config.route.v3.HeaderMatcherH\x00\x12\x36\n\x08url_path\x18\t \x01(\x0b\x32\".envoy.type.matcher.v3.PathMatcherH\x00\x12G\n\x08metadata\x18\x07 \x01(\x0b\x32&.envoy.type.matcher.v3.MetadataMatcherB\x0b\x18\x01\x92\xc7\x86\xd8\x04\x03\x33.0H\x00\x12\x41\n\x0c\x66ilter_state\x18\x0c \x01(\x0b\x32).envoy.type.matcher.v3.FilterStateMatcherH\x00\x12\x31\n\x06not_id\x18\x08 \x01(\x0b\x32\x1f.envoy.config.rbac.v3.PrincipalH\x00\x12\x41\n\x10sourced_metadata\x18\r \x01(\x0b\x32%.envoy.config.rbac.v3.SourcedMetadataH\x00\x1ah\n\x03Set\x12\x36\n\x03ids\x18\x01 \x03(\x0b\x32\x1f.envoy.config.rbac.v3.PrincipalB\x08\xfa\x42\x05\x92\x01\x02\x08\x01:)\x9a\xc5\x88\x1e$\n\"envoy.config.rbac.v2.Principal.Set\x1a\x88\x01\n\rAuthenticated\x12<\n\x0eprincipal_name\x18\x02 \x01(\x0b\x32$.envoy.type.matcher.v3.StringMatcher:3\x9a\xc5\x88\x1e.\n,envoy.config.rbac.v2.Principal.AuthenticatedJ\x04\x08\x01\x10\x02:%\x9a\xc5\x88\x1e \n\x1e\x65nvoy.config.rbac.v2.PrincipalB\x11\n\nidentifier\x12\x03\xf8\x42\x01\"R\n\x06\x41\x63tion\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x31\n\x06\x61\x63tion\x18\x02 \x01(\x0e\x32!.envoy.config.rbac.v3.RBAC.Action*(\n\x0eMetadataSource\x12\x0b\n\x07\x44YNAMIC\x10\x00\x12\t\n\x05ROUTE\x10\x01\x42}\n\"io.envoyproxy.envoy.config.rbac.v3B\tRbacProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/rbac/v3;rbacv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.rbac.v3.rbac_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.rbac.v3B\tRbacProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/rbac/v3;rbacv3\272\200\310\321\006\002\020\002'
  _RBAC_AUDITLOGGINGOPTIONS.fields_by_name['audit_condition']._options = None
  _RBAC_AUDITLOGGINGOPTIONS.fields_by_name['audit_condition']._serialized_options = b'\372B\005\202\001\002\020\001'
  _RBAC_POLICIESENTRY._options = None
  _RBAC_POLICIESENTRY._serialized_options = b'8\001'
  _RBAC.fields_by_name['action']._options = None
  _RBAC.fields_by_name['action']._serialized_options = b'\372B\005\202\001\002\020\001'
  _RBAC._options = None
  _RBAC._serialized_options = b'\232\305\210\036\033\n\031envoy.config.rbac.v2.RBAC'
  _POLICY.fields_by_name['permissions']._options = None
  _POLICY.fields_by_name['permissions']._serialized_options = b'\372B\005\222\001\002\010\001'
  _POLICY.fields_by_name['principals']._options = None
  _POLICY.fields_by_name['principals']._serialized_options = b'\372B\005\222\001\002\010\001'
  _POLICY.fields_by_name['condition']._options = None
  _POLICY.fields_by_name['condition']._serialized_options = b'\362\230\376\217\005\026\022\024expression_specifier'
  _POLICY.fields_by_name['checked_condition']._options = None
  _POLICY.fields_by_name['checked_condition']._serialized_options = b'\362\230\376\217\005\026\022\024expression_specifier'
  _POLICY._options = None
  _POLICY._serialized_options = b'\232\305\210\036\035\n\033envoy.config.rbac.v2.Policy'
  _SOURCEDMETADATA.fields_by_name['metadata_matcher']._options = None
  _SOURCEDMETADATA.fields_by_name['metadata_matcher']._serialized_options = b'\372B\005\212\001\002\020\001'
  _SOURCEDMETADATA.fields_by_name['metadata_source']._options = None
  _SOURCEDMETADATA.fields_by_name['metadata_source']._serialized_options = b'\372B\005\202\001\002\020\001'
  _PERMISSION_SET.fields_by_name['rules']._options = None
  _PERMISSION_SET.fields_by_name['rules']._serialized_options = b'\372B\005\222\001\002\010\001'
  _PERMISSION_SET._options = None
  _PERMISSION_SET._serialized_options = b'\232\305\210\036%\n#envoy.config.rbac.v2.Permission.Set'
  _PERMISSION.oneofs_by_name['rule']._options = None
  _PERMISSION.oneofs_by_name['rule']._serialized_options = b'\370B\001'
  _PERMISSION.fields_by_name['any']._options = None
  _PERMISSION.fields_by_name['any']._serialized_options = b'\372B\004j\002\010\001'
  _PERMISSION.fields_by_name['destination_port']._options = None
  _PERMISSION.fields_by_name['destination_port']._serialized_options = b'\372B\006*\004\030\377\377\003'
  _PERMISSION.fields_by_name['metadata']._options = None
  _PERMISSION.fields_by_name['metadata']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _PERMISSION._options = None
  _PERMISSION._serialized_options = b'\232\305\210\036!\n\037envoy.config.rbac.v2.Permission'
  _PRINCIPAL_SET.fields_by_name['ids']._options = None
  _PRINCIPAL_SET.fields_by_name['ids']._serialized_options = b'\372B\005\222\001\002\010\001'
  _PRINCIPAL_SET._options = None
  _PRINCIPAL_SET._serialized_options = b'\232\305\210\036$\n\"envoy.config.rbac.v2.Principal.Set'
  _PRINCIPAL_AUTHENTICATED._options = None
  _PRINCIPAL_AUTHENTICATED._serialized_options = b'\232\305\210\036.\n,envoy.config.rbac.v2.Principal.Authenticated'
  _PRINCIPAL.oneofs_by_name['identifier']._options = None
  _PRINCIPAL.oneofs_by_name['identifier']._serialized_options = b'\370B\001'
  _PRINCIPAL.fields_by_name['any']._options = None
  _PRINCIPAL.fields_by_name['any']._serialized_options = b'\372B\004j\002\010\001'
  _PRINCIPAL.fields_by_name['source_ip']._options = None
  _PRINCIPAL.fields_by_name['source_ip']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _PRINCIPAL.fields_by_name['metadata']._options = None
  _PRINCIPAL.fields_by_name['metadata']._serialized_options = b'\030\001\222\307\206\330\004\0033.0'
  _PRINCIPAL._options = None
  _PRINCIPAL._serialized_options = b'\232\305\210\036 \n\036envoy.config.rbac.v2.Principal'
  _ACTION.fields_by_name['name']._options = None
  _ACTION.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_METADATASOURCE']._serialized_start=4020
  _globals['_METADATASOURCE']._serialized_end=4060
  _globals['_RBAC']._serialized_start=594
  _globals['_RBAC']._serialized_end=1351
  _globals['_RBAC_AUDITLOGGINGOPTIONS']._serialized_start=803
  _globals['_RBAC_AUDITLOGGINGOPTIONS']._serialized_end=1198
  _globals['_RBAC_AUDITLOGGINGOPTIONS_AUDITLOGGERCONFIG']._serialized_start=1014
  _globals['_RBAC_AUDITLOGGINGOPTIONS_AUDITLOGGERCONFIG']._serialized_end=1120
  _globals['_RBAC_AUDITLOGGINGOPTIONS_AUDITCONDITION']._serialized_start=1122
  _globals['_RBAC_AUDITLOGGINGOPTIONS_AUDITCONDITION']._serialized_end=1198
  _globals['_RBAC_POLICIESENTRY']._serialized_start=1200
  _globals['_RBAC_POLICIESENTRY']._serialized_end=1277
  _globals['_RBAC_ACTION']._serialized_start=1279
  _globals['_RBAC_ACTION']._serialized_end=1317
  _globals['_POLICY']._serialized_start=1354
  _globals['_POLICY']._serialized_end=1703
  _globals['_SOURCEDMETADATA']._serialized_start=1706
  _globals['_SOURCEDMETADATA']._serialized_end=1872
  _globals['_PERMISSION']._serialized_start=1875
  _globals['_PERMISSION']._serialized_end=2858
  _globals['_PERMISSION_SET']._serialized_start=2697
  _globals['_PERMISSION_SET']._serialized_end=2805
  _globals['_PRINCIPAL']._serialized_start=2861
  _globals['_PRINCIPAL']._serialized_end=3934
  _globals['_PRINCIPAL_SET']._serialized_start=3633
  _globals['_PRINCIPAL_SET']._serialized_end=3737
  _globals['_PRINCIPAL_AUTHENTICATED']._serialized_start=3740
  _globals['_PRINCIPAL_AUTHENTICATED']._serialized_end=3876
  _globals['_ACTION']._serialized_start=3936
  _globals['_ACTION']._serialized_end=4018
