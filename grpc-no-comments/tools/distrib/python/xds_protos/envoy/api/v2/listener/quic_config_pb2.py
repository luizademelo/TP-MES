
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/api/v2/listener/quic_config.proto\x12\x15\x65nvoy.api.v2.listener\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"\xc1\x01\n\x13QuicProtocolOptions\x12<\n\x16max_concurrent_streams\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32Value\x12/\n\x0cidle_timeout\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\x12;\n\x18\x63rypto_handshake_timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.DurationB\xd5\x01\n#io.envoyproxy.envoy.api.v2.listenerB\x0fQuicConfigProtoP\x01Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\xaa\x02\x17\x45nvoy.Api.V2.ListenerNS\xea\x02\x1a\x45nvoy::Api::V2::ListenerNS\xf2\x98\xfe\x8f\x05\x1a\x12\x18\x65nvoy.config.listener.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.listener.quic_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.api.v2.listenerB\017QuicConfigProtoP\001Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\252\002\027Envoy.Api.V2.ListenerNS\352\002\032Envoy::Api::V2::ListenerNS\362\230\376\217\005\032\022\030envoy.config.listener.v3\272\200\310\321\006\002\020\001'
  _globals['_QUICPROTOCOLOPTIONS']._serialized_start=194
  _globals['_QUICPROTOCOLOPTIONS']._serialized_end=387
