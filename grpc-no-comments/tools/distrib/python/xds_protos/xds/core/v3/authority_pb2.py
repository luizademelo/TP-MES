
# source: xds/core/v3/authority.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1bxds/core/v3/authority.proto\x12\x0bxds.core.v3\x1a\x1fxds/annotations/v3/status.proto\x1a\x17validate/validate.proto\"\"\n\tAuthority\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42V\n\x16\x63om.github.xds.core.v3B\x0e\x41uthorityProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.authority_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\016AuthorityProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3\322\306\244\341\006\002\010\001'
  _AUTHORITY.fields_by_name['name']._options = None
  _AUTHORITY.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_AUTHORITY']._serialized_start=102
  _globals['_AUTHORITY']._serialized_end=136
