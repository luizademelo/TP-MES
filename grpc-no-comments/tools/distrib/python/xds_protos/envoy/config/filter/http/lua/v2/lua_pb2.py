
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)envoy/config/filter/http/lua/v2/lua.proto\x12\x1f\x65nvoy.config.filter.http.lua.v2\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"#\n\x03Lua\x12\x1c\n\x0binline_code\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x42\xbd\x01\n-io.envoyproxy.envoy.config.filter.http.lua.v2B\x08LuaProtoP\x01ZLgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/lua/v2;luav2\xf2\x98\xfe\x8f\x05&\x12$envoy.extensions.filters.http.lua.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.lua.v2.lua_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n-io.envoyproxy.envoy.config.filter.http.lua.v2B\010LuaProtoP\001ZLgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/lua/v2;luav2\362\230\376\217\005&\022$envoy.extensions.filters.http.lua.v3\272\200\310\321\006\002\020\001'
  _LUA.fields_by_name['inline_code']._options = None
  _LUA.fields_by_name['inline_code']._serialized_options = b'\372B\004r\002 \001'
  _globals['_LUA']._serialized_start=166
  _globals['_LUA']._serialized_end=201
