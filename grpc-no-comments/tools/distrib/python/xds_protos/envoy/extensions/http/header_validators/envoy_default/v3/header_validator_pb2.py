
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nOenvoy/extensions/http/header_validators/envoy_default/v3/header_validator.proto\x12\x38\x65nvoy.extensions.http.header_validators.envoy_default.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xd5\x08\n\x15HeaderValidatorConfig\x12\x84\x01\n\x16http1_protocol_options\x18\x01 \x01(\x0b\x32\x64.envoy.extensions.http.header_validators.envoy_default.v3.HeaderValidatorConfig.Http1ProtocolOptions\x12\x93\x01\n\x1euri_path_normalization_options\x18\x02 \x01(\x0b\x32k.envoy.extensions.http.header_validators.envoy_default.v3.HeaderValidatorConfig.UriPathNormalizationOptions\x12\x1d\n\x15restrict_http_methods\x18\x03 \x01(\x08\x12\x95\x01\n\x1fheaders_with_underscores_action\x18\x04 \x01(\x0e\x32l.envoy.extensions.http.header_validators.envoy_default.v3.HeaderValidatorConfig.HeadersWithUnderscoresAction\x12 \n\x18strip_fragment_from_path\x18\x05 \x01(\x08\x1a\xbf\x03\n\x1bUriPathNormalizationOptions\x12\x1f\n\x17skip_path_normalization\x18\x01 \x01(\x08\x12\x1c\n\x14skip_merging_slashes\x18\x02 \x01(\x08\x12\xbd\x01\n path_with_escaped_slashes_action\x18\x03 \x01(\x0e\x32\x88\x01.envoy.extensions.http.header_validators.envoy_default.v3.HeaderValidatorConfig.UriPathNormalizationOptions.PathWithEscapedSlashesActionB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"\xa0\x01\n\x1cPathWithEscapedSlashesAction\x12#\n\x1fIMPLEMENTATION_SPECIFIC_DEFAULT\x10\x00\x12\x12\n\x0eKEEP_UNCHANGED\x10\x01\x12\x12\n\x0eREJECT_REQUEST\x10\x02\x12\x19\n\x15UNESCAPE_AND_REDIRECT\x10\x03\x12\x18\n\x14UNESCAPE_AND_FORWARD\x10\x04\x1a\x34\n\x14Http1ProtocolOptions\x12\x1c\n\x14\x61llow_chunked_length\x18\x01 \x01(\x08\"N\n\x1cHeadersWithUnderscoresAction\x12\t\n\x05\x41LLOW\x10\x00\x12\x12\n\x0eREJECT_REQUEST\x10\x01\x12\x0f\n\x0b\x44ROP_HEADER\x10\x02\x42\xd9\x01\nFio.envoyproxy.envoy.extensions.http.header_validators.envoy_default.v3B\x14HeaderValidatorProtoP\x01Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/http/header_validators/envoy_default/v3;envoy_defaultv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.header_validators.envoy_default.v3.header_validator_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nFio.envoyproxy.envoy.extensions.http.header_validators.envoy_default.v3B\024HeaderValidatorProtoP\001Zogithub.com/envoyproxy/go-control-plane/envoy/extensions/http/header_validators/envoy_default/v3;envoy_defaultv3\272\200\310\321\006\002\020\002'
  _HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS.fields_by_name['path_with_escaped_slashes_action']._options = None
  _HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS.fields_by_name['path_with_escaped_slashes_action']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_HEADERVALIDATORCONFIG']._serialized_start=198
  _globals['_HEADERVALIDATORCONFIG']._serialized_end=1307
  _globals['_HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS']._serialized_start=726
  _globals['_HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS']._serialized_end=1173
  _globals['_HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS_PATHWITHESCAPEDSLASHESACTION']._serialized_start=1013
  _globals['_HEADERVALIDATORCONFIG_URIPATHNORMALIZATIONOPTIONS_PATHWITHESCAPEDSLASHESACTION']._serialized_end=1173
  _globals['_HEADERVALIDATORCONFIG_HTTP1PROTOCOLOPTIONS']._serialized_start=1175
  _globals['_HEADERVALIDATORCONFIG_HTTP1PROTOCOLOPTIONS']._serialized_end=1227
  _globals['_HEADERVALIDATORCONFIG_HEADERSWITHUNDERSCORESACTION']._serialized_start=1229
  _globals['_HEADERVALIDATORCONFIG_HEADERSWITHUNDERSCORESACTION']._serialized_end=1307
