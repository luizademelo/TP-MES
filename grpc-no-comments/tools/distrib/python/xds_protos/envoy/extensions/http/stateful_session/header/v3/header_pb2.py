
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n=envoy/extensions/http/stateful_session/header/v3/header.proto\x12\x30\x65nvoy.extensions.http.stateful_session.header.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"0\n\x17HeaderBasedSessionState\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xb9\x01\n>io.envoyproxy.envoy.extensions.http.stateful_session.header.v3B\x0bHeaderProtoP\x01Z`github.com/envoyproxy/go-control-plane/envoy/extensions/http/stateful_session/header/v3;headerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.http.stateful_session.header.v3.header_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.http.stateful_session.header.v3B\013HeaderProtoP\001Z`github.com/envoyproxy/go-control-plane/envoy/extensions/http/stateful_session/header/v3;headerv3\272\200\310\321\006\002\020\002'
  _HEADERBASEDSESSIONSTATE.fields_by_name['name']._options = None
  _HEADERBASEDSESSIONSTATE.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_HEADERBASEDSESSIONSTATE']._serialized_start=171
  _globals['_HEADERBASEDSESSIONSTATE']._serialized_end=219
