
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+envoy/config/listener/v2/api_listener.proto\x12\x18\x65nvoy.config.listener.v2\x1a\x19google/protobuf/any.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"9\n\x0b\x41piListener\x12*\n\x0c\x61pi_listener\x18\x01 \x01(\x0b\x32\x14.google.protobuf.AnyB\xb0\x01\n&io.envoyproxy.envoy.config.listener.v2B\x10\x41piListenerProtoP\x01ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v2;listenerv2\xf2\x98\xfe\x8f\x05\x1a\x12\x18\x65nvoy.config.listener.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.listener.v2.api_listener_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.config.listener.v2B\020ApiListenerProtoP\001ZJgithub.com/envoyproxy/go-control-plane/envoy/config/listener/v2;listenerv2\362\230\376\217\005\032\022\030envoy.config.listener.v3\272\200\310\321\006\002\020\001'
  _globals['_APILISTENER']._serialized_start=163
  _globals['_APILISTENER']._serialized_end=220
