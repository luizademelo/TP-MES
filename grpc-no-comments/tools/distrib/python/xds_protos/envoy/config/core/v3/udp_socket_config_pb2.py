
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,envoy/config/core/v3/udp_socket_config.proto\x12\x14\x65nvoy.config.core.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x8a\x01\n\x0fUdpSocketConfig\x12G\n\x14max_rx_datagram_size\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\x0b\xfa\x42\x08\x32\x06\x10\x80\x80\x04 \x00\x12.\n\nprefer_gro\x18\x02 \x01(\x0b\x32\x1a.google.protobuf.BoolValueB\x88\x01\n\"io.envoyproxy.envoy.config.core.v3B\x14UdpSocketConfigProtoP\x01ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.core.v3.udp_socket_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.config.core.v3B\024UdpSocketConfigProtoP\001ZBgithub.com/envoyproxy/go-control-plane/envoy/config/core/v3;corev3\272\200\310\321\006\002\020\002'
  _UDPSOCKETCONFIG.fields_by_name['max_rx_datagram_size']._options = None
  _UDPSOCKETCONFIG.fields_by_name['max_rx_datagram_size']._serialized_options = b'\372B\0102\006\020\200\200\004 \000'
  _globals['_UDPSOCKETCONFIG']._serialized_start=159
  _globals['_UDPSOCKETCONFIG']._serialized_end=297
