
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/envoy/api/v2/listener/udp_listener_config.proto\x12\x15\x65nvoy.api.v2.listener\x1a\x19google/protobuf/any.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\"\x9a\x01\n\x11UdpListenerConfig\x12\x19\n\x11udp_listener_name\x18\x01 \x01(\t\x12-\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x02\x18\x01H\x00\x12,\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x42\r\n\x0b\x63onfig_type\"\x1c\n\x1a\x41\x63tiveRawUdpListenerConfigB\xdc\x01\n#io.envoyproxy.envoy.api.v2.listenerB\x16UdpListenerConfigProtoP\x01Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\xaa\x02\x17\x45nvoy.Api.V2.ListenerNS\xea\x02\x1a\x45nvoy::Api::V2::ListenerNS\xf2\x98\xfe\x8f\x05\x1a\x12\x18\x65nvoy.config.listener.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.listener.udp_listener_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.api.v2.listenerB\026UdpListenerConfigProtoP\001Z<github.com/envoyproxy/go-control-plane/envoy/api/v2/listener\252\002\027Envoy.Api.V2.ListenerNS\352\002\032Envoy::Api::V2::ListenerNS\362\230\376\217\005\032\022\030envoy.config.listener.v3\272\200\310\321\006\002\020\001'
  _UDPLISTENERCONFIG.fields_by_name['config']._options = None
  _UDPLISTENERCONFIG.fields_by_name['config']._serialized_options = b'\030\001'
  _globals['_UDPLISTENERCONFIG']._serialized_start=195
  _globals['_UDPLISTENERCONFIG']._serialized_end=349
  _globals['_ACTIVERAWUDPLISTENERCONFIG']._serialized_start=351
  _globals['_ACTIVERAWUDPLISTENERCONFIG']._serialized_end=379
