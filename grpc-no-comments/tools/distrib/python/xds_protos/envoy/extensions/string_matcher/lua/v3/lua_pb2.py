
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n0envoy/extensions/string_matcher/lua/v3/lua.proto\x12&envoy.extensions.string_matcher.lua.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"F\n\x03Lua\x12?\n\x0bsource_code\x18\x01 \x01(\x0b\x32 .envoy.config.core.v3.DataSourceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x42\x9f\x01\n4io.envoyproxy.envoy.extensions.string_matcher.lua.v3B\x08LuaProtoP\x01ZSgithub.com/envoyproxy/go-control-plane/envoy/extensions/string_matcher/lua/v3;luav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.string_matcher.lua.v3.lua_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n4io.envoyproxy.envoy.extensions.string_matcher.lua.v3B\010LuaProtoP\001ZSgithub.com/envoyproxy/go-control-plane/envoy/extensions/string_matcher/lua/v3;luav3\272\200\310\321\006\002\020\002'
  _LUA.fields_by_name['source_code']._options = None
  _LUA.fields_by_name['source_code']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_LUA']._serialized_start=181
  _globals['_LUA']._serialized_end=251
