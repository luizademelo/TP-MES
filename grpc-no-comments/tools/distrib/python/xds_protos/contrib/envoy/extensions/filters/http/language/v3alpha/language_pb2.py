
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nEcontrib/envoy/extensions/filters/http/language/v3alpha/language.proto\x12.envoy.extensions.filters.http.language.v3alpha\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"w\n\x08Language\x12!\n\x10\x64\x65\x66\x61ult_language\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x02\x12-\n\x13supported_languages\x18\x02 \x03(\tB\x10\xfa\x42\r\x92\x01\n\x08\x01\x18\x01\"\x04r\x02\x10\x02\x12\x19\n\x11\x63lear_route_cache\x18\x03 \x01(\x08\x42\xb6\x01\n<io.envoyproxy.envoy.extensions.filters.http.language.v3alphaB\rLanguageProtoP\x01Z]github.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/http/language/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.filters.http.language.v3alpha.language_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n<io.envoyproxy.envoy.extensions.filters.http.language.v3alphaB\rLanguageProtoP\001Z]github.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/http/language/v3alpha\272\200\310\321\006\002\020\002'
  _LANGUAGE.fields_by_name['default_language']._options = None
  _LANGUAGE.fields_by_name['default_language']._serialized_options = b'\372B\004r\002\020\002'
  _LANGUAGE.fields_by_name['supported_languages']._options = None
  _LANGUAGE.fields_by_name['supported_languages']._serialized_options = b'\372B\r\222\001\n\010\001\030\001\"\004r\002\020\002'
  _globals['_LANGUAGE']._serialized_start=177
  _globals['_LANGUAGE']._serialized_end=296
