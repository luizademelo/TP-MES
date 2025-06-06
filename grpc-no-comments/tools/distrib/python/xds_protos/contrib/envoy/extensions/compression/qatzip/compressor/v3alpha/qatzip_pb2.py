
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nKcontrib/envoy/extensions/compression/qatzip/compressor/v3alpha/qatzip.proto\x12\x36\x65nvoy.extensions.compression.qatzip.compressor.v3alpha\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x84\x04\n\x06Qatzip\x12\x42\n\x11\x63ompression_level\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\t\xfa\x42\x06*\x04\x18\t(\x01\x12y\n\x14hardware_buffer_size\x18\x02 \x01(\x0e\x32Q.envoy.extensions.compression.qatzip.compressor.v3alpha.Qatzip.HardwareBufferSizeB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\x12H\n\x14input_size_threshold\x18\x03 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\x80 (\x80\x01\x12\x46\n\x12stream_buffer_size\x18\x04 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\xd8\x7f(\x80\x08\x12>\n\nchunk_size\x18\x05 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x0c\xfa\x42\t*\x07\x18\x80\x80\x04(\x80 \"i\n\x12HardwareBufferSize\x12\x0b\n\x07\x44\x45\x46\x41ULT\x10\x00\x12\t\n\x05SZ_4K\x10\x01\x12\t\n\x05SZ_8K\x10\x02\x12\n\n\x06SZ_32K\x10\x03\x12\n\n\x06SZ_64K\x10\x04\x12\x0b\n\x07SZ_128K\x10\x05\x12\x0b\n\x07SZ_512K\x10\x06\x42\xc4\x01\nDio.envoyproxy.envoy.extensions.compression.qatzip.compressor.v3alphaB\x0bQatzipProtoP\x01Zegithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/compression/qatzip/compressor/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.compression.qatzip.compressor.v3alpha.qatzip_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nDio.envoyproxy.envoy.extensions.compression.qatzip.compressor.v3alphaB\013QatzipProtoP\001Zegithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/compression/qatzip/compressor/v3alpha\272\200\310\321\006\002\020\002'
  _QATZIP.fields_by_name['compression_level']._options = None
  _QATZIP.fields_by_name['compression_level']._serialized_options = b'\372B\006*\004\030\t(\001'
  _QATZIP.fields_by_name['hardware_buffer_size']._options = None
  _QATZIP.fields_by_name['hardware_buffer_size']._serialized_options = b'\372B\005\202\001\002\020\001'
  _QATZIP.fields_by_name['input_size_threshold']._options = None
  _QATZIP.fields_by_name['input_size_threshold']._serialized_options = b'\372B\t*\007\030\200\200 (\200\001'
  _QATZIP.fields_by_name['stream_buffer_size']._options = None
  _QATZIP.fields_by_name['stream_buffer_size']._serialized_options = b'\372B\t*\007\030\200\330\177(\200\010'
  _QATZIP.fields_by_name['chunk_size']._options = None
  _QATZIP.fields_by_name['chunk_size']._serialized_options = b'\372B\t*\007\030\200\200\004(\200 '
  _globals['_QATZIP']._serialized_start=224
  _globals['_QATZIP']._serialized_end=740
  _globals['_QATZIP_HARDWAREBUFFERSIZE']._serialized_start=635
  _globals['_QATZIP_HARDWAREBUFFERSIZE']._serialized_end=740
