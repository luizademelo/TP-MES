
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nZenvoy/extensions/internal_redirect/allow_listed_routes/v3/allow_listed_routes_config.proto\x12\x39\x65nvoy.extensions.internal_redirect.allow_listed_routes.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"D\n\x17\x41llowListedRoutesConfig\x12)\n\x13\x61llowed_route_names\x18\x01 \x03(\tB\x0c\xfa\x42\t\x92\x01\x06\"\x04r\x02\x10\x01\x42\xe9\x01\nGio.envoyproxy.envoy.extensions.internal_redirect.allow_listed_routes.v3B\x1c\x41llowListedRoutesConfigProtoP\x01Zvgithub.com/envoyproxy/go-control-plane/envoy/extensions/internal_redirect/allow_listed_routes/v3;allow_listed_routesv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.internal_redirect.allow_listed_routes.v3.allow_listed_routes_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nGio.envoyproxy.envoy.extensions.internal_redirect.allow_listed_routes.v3B\034AllowListedRoutesConfigProtoP\001Zvgithub.com/envoyproxy/go-control-plane/envoy/extensions/internal_redirect/allow_listed_routes/v3;allow_listed_routesv3\272\200\310\321\006\002\020\002'
  _ALLOWLISTEDROUTESCONFIG.fields_by_name['allowed_route_names']._options = None
  _ALLOWLISTEDROUTESCONFIG.fields_by_name['allowed_route_names']._serialized_options = b'\372B\t\222\001\006\"\004r\002\020\001'
  _globals['_ALLOWLISTEDROUTESCONFIG']._serialized_start=209
  _globals['_ALLOWLISTEDROUTESCONFIG']._serialized_end=277
