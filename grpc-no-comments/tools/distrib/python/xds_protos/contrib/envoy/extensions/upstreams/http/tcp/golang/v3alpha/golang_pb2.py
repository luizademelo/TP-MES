
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from xds.annotations.v3 import status_pb2 as xds_dot_annotations_dot_v3_dot_status__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGcontrib/envoy/extensions/upstreams/http/tcp/golang/v3alpha/golang.proto\x12\x32\x65nvoy.extensions.upstreams.http.tcp.golang.v3alpha\x1a\x19google/protobuf/any.proto\x1a\x1fxds/annotations/v3/status.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x8f\x01\n\x06\x43onfig\x12\x1b\n\nlibrary_id\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x1d\n\x0clibrary_path\x18\x02 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12\x1c\n\x0bplugin_name\x18\x03 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12+\n\rplugin_config\x18\x04 \x01(\x0b\x32\x14.google.protobuf.AnyB\xc4\x01\n@io.envoyproxy.envoy.extensions.upstreams.http.tcp.golang.v3alphaB\x0bGolangProtoP\x01Zagithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/upstreams/http/tcp/golang/v3alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\xd2\xc6\xa4\xe1\x06\x02\x08\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'contrib.envoy.extensions.upstreams.http.tcp.golang.v3alpha.golang_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.upstreams.http.tcp.golang.v3alphaB\013GolangProtoP\001Zagithub.com/envoyproxy/go-control-plane/contrib/envoy/extensions/upstreams/http/tcp/golang/v3alpha\272\200\310\321\006\002\020\002\322\306\244\341\006\002\010\001'
  _CONFIG.fields_by_name['library_id']._options = None
  _CONFIG.fields_by_name['library_id']._serialized_options = b'\372B\004r\002\020\001'
  _CONFIG.fields_by_name['library_path']._options = None
  _CONFIG.fields_by_name['library_path']._serialized_options = b'\372B\004r\002\020\001'
  _CONFIG.fields_by_name['plugin_name']._options = None
  _CONFIG.fields_by_name['plugin_name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_CONFIG']._serialized_start=244
  _globals['_CONFIG']._serialized_end=387
