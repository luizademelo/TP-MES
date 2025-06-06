
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9envoy/extensions/dynamic_modules/v3/dynamic_modules.proto\x12#envoy.extensions.dynamic_modules.v3\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"B\n\x13\x44ynamicModuleConfig\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x14\n\x0c\x64o_not_close\x18\x03 \x01(\x08\x42\xb8\x01\n1io.envoyproxy.envoy.extensions.dynamic_modules.v3B\x13\x44ynamicModulesProtoP\x01Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/dynamic_modules/v3;dynamic_modulesv3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.dynamic_modules.v3.dynamic_modules_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n1io.envoyproxy.envoy.extensions.dynamic_modules.v3B\023DynamicModulesProtoP\001Z\\github.com/envoyproxy/go-control-plane/envoy/extensions/dynamic_modules/v3;dynamic_modulesv3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _DYNAMICMODULECONFIG.fields_by_name['name']._options = None
  _DYNAMICMODULECONFIG.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_DYNAMICMODULECONFIG']._serialized_start=187
  _globals['_DYNAMICMODULECONFIG']._serialized_end=253
