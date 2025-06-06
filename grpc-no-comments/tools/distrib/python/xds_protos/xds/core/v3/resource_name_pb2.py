
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from xds.core.v3 import context_params_pb2 as xds_dot_core_dot_v3_dot_context__params__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1fxds/core/v3/resource_name.proto\x12\x0bxds.core.v3\x1a\x1fxds/annotations/v3/status.proto\x1a xds/core/v3/context_params.proto\x1a\x17validate/validate.proto\"z\n\x0cResourceName\x12\n\n\x02id\x18\x01 \x01(\t\x12\x11\n\tauthority\x18\x02 \x01(\t\x12\x1e\n\rresource_type\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12+\n\x07\x63ontext\x18\x04 \x01(\x0b\x32\x1a.xds.core.v3.ContextParamsBY\n\x16\x63om.github.xds.core.v3B\x11ResourceNameProtoP\x01Z\"github.com/cncf/xds/go/xds/core/v3\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.core.v3.resource_name_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\026com.github.xds.core.v3B\021ResourceNameProtoP\001Z\"github.com/cncf/xds/go/xds/core/v3\322\306\244\341\006\002\010\001'
  _RESOURCENAME.fields_by_name['resource_type']._options = None
  _RESOURCENAME.fields_by_name['resource_type']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_RESOURCENAME']._serialized_start=140
  _globals['_RESOURCENAME']._serialized_end=262
