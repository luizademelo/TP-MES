
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import extension_pb2 as envoy_dot_config_dot_core_dot_v3_dot_extension__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nHenvoy/extensions/filters/http/stateful_session/v3/stateful_session.proto\x12\x31\x65nvoy.extensions.filters.http.stateful_session.v3\x1a$envoy/config/core/v3/extension.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"d\n\x0fStatefulSession\x12\x41\n\rsession_state\x18\x01 \x01(\x0b\x32*.envoy.config.core.v3.TypedExtensionConfig\x12\x0e\n\x06strict\x18\x02 \x01(\x08\"\xa7\x01\n\x17StatefulSessionPerRoute\x12\x1b\n\x08\x64isabled\x18\x01 \x01(\x08\x42\x07\xfa\x42\x04j\x02\x08\x01H\x00\x12^\n\x10stateful_session\x18\x02 \x01(\x0b\x32\x42.envoy.extensions.filters.http.stateful_session.v3.StatefulSessionH\x00\x42\x0f\n\x08override\x12\x03\xf8\x42\x01\x42\xce\x01\n?io.envoyproxy.envoy.extensions.filters.http.stateful_session.v3B\x14StatefulSessionProtoP\x01Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/stateful_session/v3;stateful_sessionv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.stateful_session.v3.stateful_session_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.filters.http.stateful_session.v3B\024StatefulSessionProtoP\001Zkgithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/stateful_session/v3;stateful_sessionv3\272\200\310\321\006\002\020\002'
  _STATEFULSESSIONPERROUTE.oneofs_by_name['override']._options = None
  _STATEFULSESSIONPERROUTE.oneofs_by_name['override']._serialized_options = b'\370B\001'
  _STATEFULSESSIONPERROUTE.fields_by_name['disabled']._options = None
  _STATEFULSESSIONPERROUTE.fields_by_name['disabled']._serialized_options = b'\372B\004j\002\010\001'
  _globals['_STATEFULSESSION']._serialized_start=221
  _globals['_STATEFULSESSION']._serialized_end=321
  _globals['_STATEFULSESSIONPERROUTE']._serialized_start=324
  _globals['_STATEFULSESSIONPERROUTE']._serialized_end=491
