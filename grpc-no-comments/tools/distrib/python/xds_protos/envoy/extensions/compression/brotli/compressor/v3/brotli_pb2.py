
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n>envoy/extensions/compression/brotli/compressor/v3/brotli.proto\x12\x31\x65nvoy.extensions.compression.brotli.compressor.v3\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xcf\x03\n\x06\x42rotli\x12\x36\n\x07quality\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02\x18\x0b\x12\x65\n\x0c\x65ncoder_mode\x18\x02 \x01(\x0e\x32\x45.envoy.extensions.compression.brotli.compressor.v3.Brotli.EncoderModeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12<\n\x0bwindow_bits\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\t\xfa\x42\x06*\x04\x18\x18(\n\x12\x41\n\x10input_block_bits\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\t\xfa\x42\x06*\x04\x18\x18(\x10\x12>\n\nchunk_size\x18\x05 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\x80\x04(\x80 \x12(\n disable_literal_context_modeling\x18\x06 \x01(\x08\";\n\x0b\x45ncoderMode\x12\x0b\n\x07\x44\x45\x46\x41ULT\x10\x00\x12\x0b\n\x07GENERIC\x10\x01\x12\x08\n\x04TEXT\x10\x02\x12\x08\n\x04\x46ONT\x10\x03\x42\xbf\x01\n?io.envoyproxy.envoy.extensions.compression.brotli.compressor.v3B\x0b\x42rotliProtoP\x01Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/brotli/compressor/v3;compressorv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.compression.brotli.compressor.v3.brotli_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n?io.envoyproxy.envoy.extensions.compression.brotli.compressor.v3B\013BrotliProtoP\001Zegithub.com/envoyproxy/go-control-plane/envoy/extensions/compression/brotli/compressor/v3;compressorv3\272\200\310\321\006\002\020\002'
  _BROTLI.fields_by_name['quality']._options = None
  _BROTLI.fields_by_name['quality']._serialized_options = b'\372B\004*\002\030\013'
  _BROTLI.fields_by_name['encoder_mode']._options = None
  _BROTLI.fields_by_name['encoder_mode']._serialized_options = b'\372B\005\202\001\002\020\001'
  _BROTLI.fields_by_name['window_bits']._options = None
  _BROTLI.fields_by_name['window_bits']._serialized_options = b'\372B\006*\004\030\030(\n'
  _BROTLI.fields_by_name['input_block_bits']._options = None
  _BROTLI.fields_by_name['input_block_bits']._serialized_options = b'\372B\006*\004\030\030(\020'
  _BROTLI.fields_by_name['chunk_size']._options = None
  _BROTLI.fields_by_name['chunk_size']._serialized_options = b'\372B\t*\007\030\200\200\004(\200 '
  _globals['_BROTLI']._serialized_start=206
  _globals['_BROTLI']._serialized_end=669
  _globals['_BROTLI_ENCODERMODE']._serialized_start=610
  _globals['_BROTLI_ENCODERMODE']._serialized_end=669
