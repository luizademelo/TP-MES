
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGenvoy/extensions/bootstrap/internal_listener/v3/internal_listener.proto\x12/envoy.extensions.bootstrap.internal_listener.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"T\n\x10InternalListener\x12@\n\x0e\x62uffer_size_kb\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\n\xfa\x42\x07*\x05\x18\x80@(\x01\x42\xcc\x01\n=io.envoyproxy.envoy.extensions.bootstrap.internal_listener.v3B\x15InternalListenerProtoP\x01Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/bootstrap/internal_listener/v3;internal_listenerv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.bootstrap.internal_listener.v3.internal_listener_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n=io.envoyproxy.envoy.extensions.bootstrap.internal_listener.v3B\025InternalListenerProtoP\001Zjgithub.com/envoyproxy/go-control-plane/envoy/extensions/bootstrap/internal_listener/v3;internal_listenerv3\272\200\310\321\006\002\020\002'
  _INTERNALLISTENER.fields_by_name['buffer_size_kb']._options = None
  _INTERNALLISTENER.fields_by_name['buffer_size_kb']._serialized_options = b'\372B\007*\005\030\200@(\001'
  _globals['_INTERNALLISTENER']._serialized_start=212
  _globals['_INTERNALLISTENER']._serialized_end=296
