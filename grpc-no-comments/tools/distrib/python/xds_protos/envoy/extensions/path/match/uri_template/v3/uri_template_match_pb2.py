
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDenvoy/extensions/path/match/uri_template/v3/uri_template_match.proto\x12+envoy.extensions.path.match.uri_template.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\";\n\x16UriTemplateMatchConfig\x12!\n\rpath_template\x18\x01 \x01(\tB\n\xfa\x42\x07r\x05\x10\x01\x18\x80\x02\x42\xbf\x01\n9io.envoyproxy.envoy.extensions.path.match.uri_template.v3B\x15UriTemplateMatchProtoP\x01Zagithub.com/envoyproxy/go-control-plane/envoy/extensions/path/match/uri_template/v3;uri_templatev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.path.match.uri_template.v3.uri_template_match_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n9io.envoyproxy.envoy.extensions.path.match.uri_template.v3B\025UriTemplateMatchProtoP\001Zagithub.com/envoyproxy/go-control-plane/envoy/extensions/path/match/uri_template/v3;uri_templatev3\272\200\310\321\006\002\020\002'
  _URITEMPLATEMATCHCONFIG.fields_by_name['path_template']._options = None
  _URITEMPLATEMATCHCONFIG.fields_by_name['path_template']._serialized_options = b'\372B\007r\005\020\001\030\200\002'
  _globals['_URITEMPLATEMATCHCONFIG']._serialized_start=173
  _globals['_URITEMPLATEMATCHCONFIG']._serialized_end=232
