
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1fxds/annotations/v3/status.proto\x12\x12xds.annotations.v3\x1a google/protobuf/descriptor.proto\"0\n\x14\x46ileStatusAnnotation\x12\x18\n\x10work_in_progress\x18\x01 \x01(\x08\"3\n\x17MessageStatusAnnotation\x12\x18\n\x10work_in_progress\x18\x01 \x01(\x08\"1\n\x15\x46ieldStatusAnnotation\x12\x18\n\x10work_in_progress\x18\x01 \x01(\x08\"v\n\x10StatusAnnotation\x12\x18\n\x10work_in_progress\x18\x01 \x01(\x08\x12H\n\x16package_version_status\x18\x02 \x01(\x0e\x32(.xds.annotations.v3.PackageVersionStatus*]\n\x14PackageVersionStatus\x12\x0b\n\x07UNKNOWN\x10\x00\x12\n\n\x06\x46ROZEN\x10\x01\x12\n\n\x06\x41\x43TIVE\x10\x02\x12 \n\x1cNEXT_MAJOR_VERSION_CANDIDATE\x10\x03:^\n\x0b\x66ile_status\x12\x1c.google.protobuf.FileOptions\x18\xea\xc8\x94l \x01(\x0b\x32(.xds.annotations.v3.FileStatusAnnotation:g\n\x0emessage_status\x12\x1f.google.protobuf.MessageOptions\x18\xea\xc8\x94l \x01(\x0b\x32+.xds.annotations.v3.MessageStatusAnnotation:a\n\x0c\x66ield_status\x12\x1d.google.protobuf.FieldOptions\x18\xea\xc8\x94l \x01(\x0b\x32).xds.annotations.v3.FieldStatusAnnotationB+Z)github.com/cncf/xds/go/xds/annotations/v3b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.annotations.v3.status_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'Z)github.com/cncf/xds/go/xds/annotations/v3'
  _globals['_PACKAGEVERSIONSTATUS']._serialized_start=363
  _globals['_PACKAGEVERSIONSTATUS']._serialized_end=456
  _globals['_FILESTATUSANNOTATION']._serialized_start=89
  _globals['_FILESTATUSANNOTATION']._serialized_end=137
  _globals['_MESSAGESTATUSANNOTATION']._serialized_start=139
  _globals['_MESSAGESTATUSANNOTATION']._serialized_end=190
  _globals['_FIELDSTATUSANNOTATION']._serialized_start=192
  _globals['_FIELDSTATUSANNOTATION']._serialized_end=241
  _globals['_STATUSANNOTATION']._serialized_start=243
  _globals['_STATUSANNOTATION']._serialized_end=361
