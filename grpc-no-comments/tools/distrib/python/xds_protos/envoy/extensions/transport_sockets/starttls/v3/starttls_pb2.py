
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.transport_sockets.raw_buffer.v3 import raw_buffer_pb2 as envoy_dot_extensions_dot_transport__sockets_dot_raw__buffer_dot_v3_dot_raw__buffer__pb2
from envoy.extensions.transport_sockets.tls.v3 import tls_pb2 as envoy_dot_extensions_dot_transport__sockets_dot_tls_dot_v3_dot_tls__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n=envoy/extensions/transport_sockets/starttls/v3/starttls.proto\x12.envoy.extensions.transport_sockets.starttls.v3\x1a\x41\x65nvoy/extensions/transport_sockets/raw_buffer/v3/raw_buffer.proto\x1a\x33\x65nvoy/extensions/transport_sockets/tls/v3/tls.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xd4\x01\n\x0eStartTlsConfig\x12\\\n\x17\x63leartext_socket_config\x18\x01 \x01(\x0b\x32;.envoy.extensions.transport_sockets.raw_buffer.v3.RawBuffer\x12\x64\n\x11tls_socket_config\x18\x02 \x01(\x0b\x32?.envoy.extensions.transport_sockets.tls.v3.DownstreamTlsContextB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\"\xda\x01\n\x16UpstreamStartTlsConfig\x12\\\n\x17\x63leartext_socket_config\x18\x01 \x01(\x0b\x32;.envoy.extensions.transport_sockets.raw_buffer.v3.RawBuffer\x12\x62\n\x11tls_socket_config\x18\x02 \x01(\x0b\x32=.envoy.extensions.transport_sockets.tls.v3.UpstreamTlsContextB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\xb9\x01\n<io.envoyproxy.envoy.extensions.transport_sockets.starttls.v3B\rStarttlsProtoP\x01Z`github.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/starttls/v3;starttlsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.transport_sockets.starttls.v3.starttls_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n<io.envoyproxy.envoy.extensions.transport_sockets.starttls.v3B\rStarttlsProtoP\001Z`github.com/envoyproxy/go-control-plane/envoy/extensions/transport_sockets/starttls/v3;starttlsv3\272\200\310\321\006\002\020\002'
  _STARTTLSCONFIG.fields_by_name['tls_socket_config']._options = None
  _STARTTLSCONFIG.fields_by_name['tls_socket_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _UPSTREAMSTARTTLSCONFIG.fields_by_name['tls_socket_config']._options = None
  _UPSTREAMSTARTTLSCONFIG.fields_by_name['tls_socket_config']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_STARTTLSCONFIG']._serialized_start=290
  _globals['_STARTTLSCONFIG']._serialized_end=502
  _globals['_UPSTREAMSTARTTLSCONFIG']._serialized_start=505
  _globals['_UPSTREAMSTARTTLSCONFIG']._serialized_end=723
