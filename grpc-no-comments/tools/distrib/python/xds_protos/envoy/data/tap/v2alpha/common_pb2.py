
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/data/tap/v2alpha/common.proto\x12\x16\x65nvoy.data.tap.v2alpha\x1a\x1dudpa/annotations/status.proto\"O\n\x04\x42ody\x12\x12\n\x08\x61s_bytes\x18\x01 \x01(\x0cH\x00\x12\x13\n\tas_string\x18\x02 \x01(\tH\x00\x12\x11\n\ttruncated\x18\x03 \x01(\x08\x42\x0b\n\tbody_typeB|\n$io.envoyproxy.envoy.data.tap.v2alphaB\x0b\x43ommonProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/data/tap/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.data.tap.v2alpha.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.data.tap.v2alphaB\013CommonProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/data/tap/v2alpha\272\200\310\321\006\002\020\001'
  _globals['_BODY']._serialized_start=94
  _globals['_BODY']._serialized_end=173
