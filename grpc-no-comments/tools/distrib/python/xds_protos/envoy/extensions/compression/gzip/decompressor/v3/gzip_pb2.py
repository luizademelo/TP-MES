
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n<envoy/extensions/compression/gzip/decompressor/v3/gzip.proto\x12\x31\x65nvoy.extensions.compression.gzip.decompressor.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc9\x01\n\x04Gzip\x12<\n\x0bwindow_bits\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\t\xfa\x42\x06*\x04\x18\x0f(\t\x12>\n\nchunk_size\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\x80\x04(\x80 \x12\x43\n\x11max_inflate_ratio\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\n\xfa\x42\x07*\x05\x18\x88\x08(\x01\x42\xbf\x01\n?io.envoyproxy.envoy.extensions.compression.gzip.decompressor.v3B\tGzipProtoP\x01Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/gzip/decompressor/v3;decompressorv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.compression.gzip.decompressor.v3.gzip_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.compression.gzip.decompressor.v3B\tGzipProtoP\001Zggithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/gzip/decompressor/v3;decompressorv3\272\200\310\321\006\002\020\002'
  _GZIP.fields_by_name['window_bits']._options = None
  _GZIP.fields_by_name['window_bits']._serialized_options = b'\372B\006*\004\030\017(\t'
  _GZIP.fields_by_name['chunk_size']._options = None
  _GZIP.fields_by_name['chunk_size']._serialized_options = b'\372B\t*\007\030\200\200\004(\200 '
  _GZIP.fields_by_name['max_inflate_ratio']._options = None
  _GZIP.fields_by_name['max_inflate_ratio']._serialized_options = b'\372B\007*\005\030\210\010(\001'
  _globals['_GZIP']._serialized_start=204
  _globals['_GZIP']._serialized_end=405
