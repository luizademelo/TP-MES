
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.core.v3 import resource_name_pb2 as xds_dot_core_dot_v3_dot_resource__name__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1axds/core/v3/resource.proto\x12\x0bxds.core.v3\x1a\x19google/protobuf/any.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1fxds/core/v3/resource_name.proto\"l\n\x08Resource\x12\'\n\x04name\x18\x01 \x01(\x0b\x32\x19.xds.core.v3.ResourceName\x12\x0f\n\x07version\x18\x02 \x01(\t\x12&\n\x08resource\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyBU\n\x16\x63om.github.xds.core.v3B\rResourceProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.resource_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\rResourceProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3\322\306\244\341\006\002\010\001'
  _globals['_RESOURCE']._serialized_start=136
  _globals['_RESOURCE']._serialized_end=244
