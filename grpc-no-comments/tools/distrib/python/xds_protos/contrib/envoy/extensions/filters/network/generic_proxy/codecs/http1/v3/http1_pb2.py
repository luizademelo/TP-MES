
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nRcontrib/envoy/extensions/filters/network/generic_proxy/codecs/http1/v3/http1.proto\x12>envoy.extensions.filters.network.generic_proxy.codecs.http1.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\"\x80\x01\n\x10Http1CodecConfig\x12\x35\n\x11single_frame_mode\x18\x01 \x01(\x0b\x32\x1a.google.protobuf.BoolValue\x12\x35\n\x0fmax_buffer_size\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\xe3\x01\nLio.envoyproxy.envoy.extensions.filters.network.generic_proxy.codecs.http1.v3B\nHttp1ProtoP\x01Zugithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/generic_proxy/codecs/http1/v3;http1v3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.filters.network.generic_proxy.codecs.http1.v3.http1_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nLio.envoyproxy.envoy.extensions.filters.network.generic_proxy.codecs.http1.v3B\nHttp1ProtoP\001Zugithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/filters/network/generic_proxy/codecs/http1/v3;http1v3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _globals['_HTTP1CODECCONFIG']._serialized_start=247
  _globals['_HTTP1CODECCONFIG']._serialized_end=375
