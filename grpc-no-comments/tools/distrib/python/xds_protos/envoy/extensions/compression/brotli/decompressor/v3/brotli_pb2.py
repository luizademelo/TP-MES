
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@envoy/extensions/compression/brotli/decompressor/v3/brotli.proto\x12\x33\x65nvoy.extensions.compression.brotli.decompressor.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"r\n\x06\x42rotli\x12(\n disable_ring_buffer_reallocation\x18\x01 \x01(\x08\x12>\n\nchunk_size\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\x80\x04(\x80 B\xc5\x01\nAio.envoyproxy.envoy.extensions.compression.brotli.decompressor.v3B\x0b\x42rotliProtoP\x01Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/brotli/decompressor/v3;decompressorv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.compression.brotli.decompressor.v3.brotli_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nAio.envoyproxy.envoy.extensions.compression.brotli.decompressor.v3B\013BrotliProtoP\001Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/brotli/decompressor/v3;decompressorv3\272\200\310\321\006\002\020\002'
  _BROTLI.fields_by_name['chunk_size']._options = None
  _BROTLI.fields_by_name['chunk_size']._serialized_options = b'\372B\t*\007\030\200\200\004(\200 '
  _globals['_BROTLI']._serialized_start=209
  _globals['_BROTLI']._serialized_end=323
