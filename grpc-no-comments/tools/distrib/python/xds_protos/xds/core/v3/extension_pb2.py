
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from validate import validate_pb2 as validate_dot_validate__pb2
from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1bxds/core/v3/extension.proto\x12\x0bxds.core.v3\x1a\x17validate/validate.proto\x1a\x19google/protobuf/any.proto\"c\n\x14TypedExtensionConfig\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x34\n\x0ctyped_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.AnyB\x08\xfa\x42\x05\xa2\x01\x02\x08\x01\x42N\n\x16\x63om.github.xds.core.v3B\x0e\x45xtensionProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.extension_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\016ExtensionProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3'
  _TYPEDEXTENSIONCONFIG.fields_by_name['name']._options = None
  _TYPEDEXTENSIONCONFIG.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _TYPEDEXTENSIONCONFIG.fields_by_name['typed_config']._options = None
  _TYPEDEXTENSIONCONFIG.fields_by_name['typed_config']._serialized_options = b'\372B\005\242\001\002\010\001'
  _globals['_TYPEDEXTENSIONCONFIG']._serialized_start=96
  _globals['_TYPEDEXTENSIONCONFIG']._serialized_end=195
