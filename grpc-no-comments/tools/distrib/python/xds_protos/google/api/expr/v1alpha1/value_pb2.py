
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$google/api/expr/v1alpha1/value.proto\x12\x18google.api.expr.v1alpha1\x1a\x19google/protobuf/any.proto\x1a\x1cgoogle/protobuf/struct.proto\"\xc0\x03\n\x05Value\x12\x30\n\nnull_value\x18\x01 \x01(\x0e\x32\x1a.google.protobuf.NullValueH\x00\x12\x14\n\nbool_value\x18\x02 \x01(\x08H\x00\x12\x15\n\x0bint64_value\x18\x03 \x01(\x03H\x00\x12\x16\n\x0cuint64_value\x18\x04 \x01(\x04H\x00\x12\x16\n\x0c\x64ouble_value\x18\x05 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x06 \x01(\tH\x00\x12\x15\n\x0b\x62ytes_value\x18\x07 \x01(\x0cH\x00\x12\x39\n\nenum_value\x18\t \x01(\x0b\x32#.google.api.expr.v1alpha1.EnumValueH\x00\x12,\n\x0cobject_value\x18\n \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x12\x37\n\tmap_value\x18\x0b \x01(\x0b\x32\".google.api.expr.v1alpha1.MapValueH\x00\x12\x39\n\nlist_value\x18\x0c \x01(\x0b\x32#.google.api.expr.v1alpha1.ListValueH\x00\x12\x14\n\ntype_value\x18\x0f \x01(\tH\x00\x42\x06\n\x04kind\"(\n\tEnumValue\x12\x0c\n\x04type\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x05\"<\n\tListValue\x12/\n\x06values\x18\x01 \x03(\x0b\x32\x1f.google.api.expr.v1alpha1.Value\"\xac\x01\n\x08MapValue\x12\x39\n\x07\x65ntries\x18\x01 \x03(\x0b\x32(.google.api.expr.v1alpha1.MapValue.Entry\x1a\x65\n\x05\x45ntry\x12,\n\x03key\x18\x01 \x01(\x0b\x32\x1f.google.api.expr.v1alpha1.Value\x12.\n\x05value\x18\x02 \x01(\x0b\x32\x1f.google.api.expr.v1alpha1.ValueBm\n\x1c\x63om.google.api.expr.v1alpha1B\nValueProtoP\x01Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\xf8\x01\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'google.api.expr.v1alpha1.value_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034com.google.api.expr.v1alpha1B\nValueProtoP\001Z<google.golang.org/genproto/googleapis/api/expr/v1alpha1;expr\370\001\001'
  _globals['_VALUE']._serialized_start=124
  _globals['_VALUE']._serialized_end=572
  _globals['_ENUMVALUE']._serialized_start=574
  _globals['_ENUMVALUE']._serialized_end=614
  _globals['_LISTVALUE']._serialized_start=616
  _globals['_LISTVALUE']._serialized_end=676
  _globals['_MAPVALUE']._serialized_start=679
  _globals['_MAPVALUE']._serialized_end=851
  _globals['_MAPVALUE_ENTRY']._serialized_start=750
  _globals['_MAPVALUE_ENTRY']._serialized_end=851
