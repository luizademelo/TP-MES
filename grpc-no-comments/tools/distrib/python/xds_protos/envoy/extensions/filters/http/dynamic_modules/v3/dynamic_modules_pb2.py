
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.dynamic_modules.v3 import dynamic_modules_pb2 as envoy_dot_extensions_dot_dynamic__modules_dot_v3_dot_dynamic__modules__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nFenvoy/extensions/filters/http/dynamic_modules/v3/dynamic_modules.proto\x12\x30\x65nvoy.extensions.filters.http.dynamic_modules.v3\x1a\x39\x65nvoy/extensions/dynamic_modules/v3/dynamic_modules.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\"\x9a\x01\n\x13\x44ynamicModuleFilter\x12W\n\x15\x64ynamic_module_config\x18\x01 \x01(\x0b\x32\x38.envoy.extensions.dynamic_modules.v3.DynamicModuleConfig\x12\x13\n\x0b\x66ilter_name\x18\x02 \x01(\t\x12\x15\n\rfilter_config\x18\x03 \x01(\tB\xd2\x01\n>io.envoyproxy.envoy.extensions.filters.http.dynamic_modules.v3B\x13\x44ynamicModulesProtoP\x01Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/dynamic_modules/v3;dynamic_modulesv3\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.dynamic_modules.v3.dynamic_modules_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.extensions.filters.http.dynamic_modules.v3B\023DynamicModulesProtoP\001Zigithub.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/dynamic_modules/v3;dynamic_modulesv3\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _globals['_DYNAMICMODULEFILTER']._serialized_start=248
  _globals['_DYNAMICMODULEFILTER']._serialized_end=402
