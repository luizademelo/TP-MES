
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.type.http.v3 import cookie_pb2 as envoy_dot_type_dot_http_dot_v3_dot_cookie__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n=envoy/extensions/http/stateful_session/cookie/v3/cookie.proto\x12\x30\x65nvoy.extensions.http.stateful_session.cookie.v3\x1a\x1f\x65nvoy/type/http/v3/cookie.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"O\n\x17\x43ookieBasedSessionState\x12\x34\n\x06\x63ookie\x18\x01 \x01(\x0b\x32\x1a.envoy.type.http.v3.CookieB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\xb9\x01\n>io.envoyproxy.envoy.extensions.http.stateful_session.cookie.v3B\x0b\x43ookieProtoP\x01Z`github.com/envoyproxy/go-control-plane/envoy/extensions/http/stateful_session/cookie/v3;cookiev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.stateful_session.cookie.v3.cookie_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.http.stateful_session.cookie.v3B\013CookieProtoP\001Z`github.com/envoyproxy/go-control-plane/envoy/extensions/http/stateful_session/cookie/v3;cookiev3\272\200\310\321\006\002\020\002'
  _COOKIEBASEDSESSIONSTATE.fields_by_name['cookie']._options = None
  _COOKIEBASEDSESSIONSTATE.fields_by_name['cookie']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_COOKIEBASEDSESSIONSTATE']._serialized_start=204
  _globals['_COOKIEBASEDSESSIONSTATE']._serialized_end=283
