
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nLenvoy/extensions/http/header_formatters/preserve_case/v3/preserve_case.proto\x12\x38\x65nvoy.extensions.http.header_formatters.preserve_case.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa0\x02\n\x1bPreserveCaseFormatterConfig\x12\x1d\n\x15\x66orward_reason_phrase\x18\x01 \x01(\x08\x12\xa4\x01\n\x1f\x66ormatter_type_on_envoy_headers\x18\x02 \x01(\x0e\x32q.envoy.extensions.http.header_formatters.preserve_case.v3.PreserveCaseFormatterConfig.FormatterTypeOnEnvoyHeadersB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\";\n\x1b\x46ormatterTypeOnEnvoyHeaders\x12\x0b\n\x07\x44\x45\x46\x41ULT\x10\x00\x12\x0f\n\x0bPROPER_CASE\x10\x01\x42\xd6\x01\nFio.envoyproxy.envoy.extensions.http.header_formatters.preserve_case.v3B\x11PreserveCaseProtoP\x01Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/http/header_formatters/preserve_case/v3;preserve_casev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.header_formatters.preserve_case.v3.preserve_case_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nFio.envoyproxy.envoy.extensions.http.header_formatters.preserve_case.v3B\021PreserveCaseProtoP\001Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/http/header_formatters/preserve_case/v3;preserve_casev3\272\200\310\321\006\002\020\002'
  _PRESERVECASEFORMATTERCONFIG.fields_by_name['formatter_type_on_envoy_headers']._options = None
  _PRESERVECASEFORMATTERCONFIG.fields_by_name['formatter_type_on_envoy_headers']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_PRESERVECASEFORMATTERCONFIG']._serialized_start=195
  _globals['_PRESERVECASEFORMATTERCONFIG']._serialized_end=483
  _globals['_PRESERVECASEFORMATTERCONFIG_FORMATTERTYPEONENVOYHEADERS']._serialized_start=424
  _globals['_PRESERVECASEFORMATTERCONFIG_FORMATTERTYPEONENVOYHEADERS']._serialized_end=483
