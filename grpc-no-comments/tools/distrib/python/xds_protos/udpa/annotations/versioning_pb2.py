
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!udpa/annotations/versioning.proto\x12\x10udpa.annotations\x1a google/protobuf/descriptor.proto\"5\n\x14VersioningAnnotation\x12\x1d\n\x15previous_message_type\x18\x01 \x01(\t:^\n\nversioning\x12\x1f.google.protobuf.MessageOptions\x18\xd3\x88\xe1\x03 \x01(\x0b\x32&.udpa.annotations.VersioningAnnotationB$Z\"github.com/cncf/xds/go/annotationsb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'udpa.annotations.versioning_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'Z\"github.com/cncf/xds/go/annotations'
  _globals['_VERSIONINGANNOTATION']._serialized_start=89
  _globals['_VERSIONINGANNOTATION']._serialized_end=142
