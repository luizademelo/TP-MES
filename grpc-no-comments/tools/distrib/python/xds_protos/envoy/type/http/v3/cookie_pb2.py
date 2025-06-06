
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x65nvoy/type/http/v3/cookie.proto\x12\x12\x65nvoy.type.http.v3\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"_\n\x06\x43ookie\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x30\n\x03ttl\x18\x02 \x01(\x0b\x32\x19.google.protobuf.DurationB\x08\xfa\x42\x05\xaa\x01\x02\x32\x00\x12\x0c\n\x04path\x18\x03 \x01(\tB{\n io.envoyproxy.envoy.type.http.v3B\x0b\x43ookieProtoP\x01Z@github.com/envoyproxy/go-control-plane/envoy/type/http/v3;httpv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.http.v3.cookie_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n io.envoyproxy.envoy.type.http.v3B\013CookieProtoP\001Z@github.com/envoyproxy/go-control-plane/envoy/type/http/v3;httpv3\272\200\310\321\006\002\020\002'
  _COOKIE.fields_by_name['name']._options = None
  _COOKIE.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _COOKIE.fields_by_name['ttl']._options = None
  _COOKIE.fields_by_name['ttl']._serialized_options = b'\372B\005\252\001\0022\000'
  _globals['_COOKIE']._serialized_start=143
  _globals['_COOKIE']._serialized_end=238
