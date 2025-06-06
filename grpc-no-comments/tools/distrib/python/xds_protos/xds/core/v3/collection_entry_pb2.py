
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.core.v3 import resource_locator_pb2 as xds_dot_core_dot_v3_dot_resource__locator__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"xds/core/v3/collection_entry.proto\x12\x0bxds.core.v3\x1a\x19google/protobuf/any.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\"xds/core/v3/resource_locator.proto\x1a\x17validate/validate.proto\"\x93\x02\n\x0f\x43ollectionEntry\x12/\n\x07locator\x18\x01 \x01(\x0b\x32\x1c.xds.core.v3.ResourceLocatorH\x00\x12@\n\x0cinline_entry\x18\x02 \x01(\x0b\x32(.xds.core.v3.CollectionEntry.InlineEntryH\x00\x1ar\n\x0bInlineEntry\x12*\n\x04name\x18\x01 \x01(\tB\x1c\xfa\x42\x19r\x17\x32\x15^[0-9a-zA-Z_\\-\\.~:]+$\x12\x0f\n\x07version\x18\x02 \x01(\t\x12&\n\x08resource\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyB\x19\n\x12resource_specifier\x12\x03\xf8\x42\x01\x42\\\n\x16\x63om.github.xds.core.v3B\x14\x43ollectionEntryProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.collection_entry_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\024CollectionEntryProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3\322\306\244\341\006\002\010\001'
  _COLLECTIONENTRY_INLINEENTRY.fields_by_name['name']._options = None
  _COLLECTIONENTRY_INLINEENTRY.fields_by_name['name']._serialized_options = b'\372B\031r\0272\025^[0-9a-zA-Z_\\-\\.~:]+$'
  _COLLECTIONENTRY.oneofs_by_name['resource_specifier']._options = None
  _COLLECTIONENTRY.oneofs_by_name['resource_specifier']._serialized_options = b'\370B\001'
  _globals['_COLLECTIONENTRY']._serialized_start=173
  _globals['_COLLECTIONENTRY']._serialized_end=448
  _globals['_COLLECTIONENTRY_INLINEENTRY']._serialized_start=307
  _globals['_COLLECTIONENTRY_INLINEENTRY']._serialized_end=421
