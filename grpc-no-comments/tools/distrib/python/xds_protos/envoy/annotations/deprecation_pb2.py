
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/annotations/deprecation.proto\x12\x11\x65nvoy.annotations\x1a google/protobuf/descriptor.proto:?\n\x15\x64isallowed_by_default\x12\x1d.google.protobuf.FieldOptions\x18\xe7\xad\xaeZ \x01(\x08:E\n\x1b\x64\x65precated_at_minor_version\x12\x1d.google.protobuf.FieldOptions\x18\xf2\xe8\x80K \x01(\t:H\n\x1a\x64isallowed_by_default_enum\x12!.google.protobuf.EnumValueOptions\x18\xf5\xce\xb6! \x01(\x08:N\n deprecated_at_minor_version_enum\x12!.google.protobuf.EnumValueOptions\x18\xc1\xbe\xb3V \x01(\tB:Z8github.com/envoyproxy/go-control-plane/envoy/annotationsb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.annotations.deprecation_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'Z8github.com/envoyproxy/go-control-plane/envoy/annotations'
