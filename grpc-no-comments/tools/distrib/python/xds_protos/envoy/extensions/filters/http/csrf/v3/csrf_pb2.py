
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.type.matcher.v3 import string_pb2 as envoy_dot_type_dot_matcher_dot_v3_dot_string__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n0envoy/extensions/filters/http/csrf/v3/csrf.proto\x12%envoy.extensions.filters.http.csrf.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\"envoy/type/matcher/v3/string.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x9c\x02\n\nCsrfPolicy\x12P\n\x0e\x66ilter_enabled\x18\x01 \x01(\x0b\x32..envoy.config.core.v3.RuntimeFractionalPercentB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x46\n\x0eshadow_enabled\x18\x02 \x01(\x0b\x32..envoy.config.core.v3.RuntimeFractionalPercent\x12@\n\x12\x61\x64\x64itional_origins\x18\x03 \x03(\x0b\x32$.envoy.type.matcher.v3.StringMatcher:2\x9a\xc5\x88\x1e-\n+envoy.config.filter.http.csrf.v2.CsrfPolicyB\x9f\x01\n3io.envoyproxy.envoy.extensions.filters.http.csrf.v3B\tCsrfProtoP\x01ZSgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/csrf/v3;csrfv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.csrf.v3.csrf_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n3io.envoyproxy.envoy.extensions.filters.http.csrf.v3B\tCsrfProtoP\001ZSgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/csrf/v3;csrfv3\272\200\310\321\006\002\020\002'
  _CSRFPOLICY.fields_by_name['filter_enabled']._options = None
  _CSRFPOLICY.fields_by_name['filter_enabled']._serialized_options = b'\372B\005\212\001\002\020\001'
  _CSRFPOLICY._options = None
  _CSRFPOLICY._serialized_options = b'\232\305\210\036-\n+envoy.config.filter.http.csrf.v2.CsrfPolicy'
  _globals['_CSRFPOLICY']._serialized_start=252
  _globals['_CSRFPOLICY']._serialized_end=536
