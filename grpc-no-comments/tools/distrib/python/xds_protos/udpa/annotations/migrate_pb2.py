
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import descriptor_pb2 as google_dot_protobuf_dot_descriptor__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1eudpa/annotations/migrate.proto\x12\x10udpa.annotations\x1a google/protobuf/descriptor.proto\"#\n\x11MigrateAnnotation\x12\x0e\n\x06rename\x18\x01 \x01(\t\"A\n\x16\x46ieldMigrateAnnotation\x12\x0e\n\x06rename\x18\x01 \x01(\t\x12\x17\n\x0foneof_promotion\x18\x02 \x01(\t\"0\n\x15\x46ileMigrateAnnotation\x12\x17\n\x0fmove_to_package\x18\x02 \x01(\t:`\n\x0fmessage_migrate\x12\x1f.google.protobuf.MessageOptions\x18\x8e\xe3\xffQ \x01(\x0b\x32#.udpa.annotations.MigrateAnnotation:a\n\rfield_migrate\x12\x1d.google.protobuf.FieldOptions\x18\x8e\xe3\xffQ \x01(\x0b\x32(.udpa.annotations.FieldMigrateAnnotation:Z\n\x0c\x65num_migrate\x12\x1c.google.protobuf.EnumOptions\x18\x8e\xe3\xffQ \x01(\x0b\x32#.udpa.annotations.MigrateAnnotation:e\n\x12\x65num_value_migrate\x12!.google.protobuf.EnumValueOptions\x18\x8e\xe3\xffQ \x01(\x0b\x32#.udpa.annotations.MigrateAnnotation:^\n\x0c\x66ile_migrate\x12\x1c.google.protobuf.FileOptions\x18\x8e\xe3\xffQ \x01(\x0b\x32\'.udpa.annotations.FileMigrateAnnotationB$Z\"github.com/cncf/xds/go/annotationsb\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'udpa.annotations.migrate_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'Z\"github.com/cncf/xds/go/annotations'
  _globals['_MIGRATEANNOTATION']._serialized_start=86
  _globals['_MIGRATEANNOTATION']._serialized_end=121
  _globals['_FIELDMIGRATEANNOTATION']._serialized_start=123
  _globals['_FIELDMIGRATEANNOTATION']._serialized_end=188
  _globals['_FILEMIGRATEANNOTATION']._serialized_start=190
  _globals['_FILEMIGRATEANNOTATION']._serialized_end=238
