
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5envoy/config/transport_socket/alts/v2alpha/alts.proto\x12*envoy.config.transport_socket.alts.v2alpha\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"J\n\x04\x41lts\x12#\n\x12handshaker_service\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x1d\n\x15peer_service_accounts\x18\x02 \x03(\tB\xd4\x01\n8io.envoyproxy.envoy.config.transport_socket.alts.v2alphaB\tAltsProtoP\x01ZQgithub.com/envoyproxy/go-control-plane/envoy/config/transport_socket/alts/v2alpha\xf2\x98\xfe\x8f\x05,\x12*envoy.extensions.transport_sockets.alts.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.transport_socket.alts.v2alpha.alts_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.config.transport_socket.alts.v2alphaB\tAltsProtoP\001ZQgithub.com/envoyproxy/go-control-plane/envoy/config/transport_socket/alts/v2alpha\362\230\376\217\005,\022*envoy.extensions.transport_sockets.alts.v3\272\200\310\321\006\002\020\001'
  _ALTS.fields_by_name['handshaker_service']._options = None
  _ALTS.fields_by_name['handshaker_service']._serialized_options = b'\372B\004r\002 \001'
  _globals['_ALTS']._serialized_start=189
  _globals['_ALTS']._serialized_end=263
