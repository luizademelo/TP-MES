
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nHenvoy/config/filter/http/grpc_http1_reverse_bridge/v2alpha1/config.proto\x12;envoy.config.filter.http.grpc_http1_reverse_bridge.v2alpha1\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"K\n\x0c\x46ilterConfig\x12\x1d\n\x0c\x63ontent_type\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12\x1c\n\x14withhold_grpc_frames\x18\x02 \x01(\x08\"(\n\x14\x46ilterConfigPerRoute\x12\x10\n\x08\x64isabled\x18\x01 \x01(\x08\x42\x88\x02\nIio.envoyproxy.envoy.config.filter.http.grpc_http1_reverse_bridge.v2alpha1B\x0b\x43onfigProtoP\x01Zbgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/grpc_http1_reverse_bridge/v2alpha1\xf2\x98\xfe\x8f\x05<\x12:envoy.extensions.filters.http.grpc_http1_reverse_bridge.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.filter.http.grpc_http1_reverse_bridge.v2alpha1.config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nIio.envoyproxy.envoy.config.filter.http.grpc_http1_reverse_bridge.v2alpha1B\013ConfigProtoP\001Zbgithub.com/envoyproxy/go-control-plane/envoy/config/filter/http/grpc_http1_reverse_bridge/v2alpha1\362\230\376\217\005<\022:envoy.extensions.filters.http.grpc_http1_reverse_bridge.v3\272\200\310\321\006\002\020\001'
  _FILTERCONFIG.fields_by_name['content_type']._options = None
  _FILTERCONFIG.fields_by_name['content_type']._serialized_options = b'\372B\004r\002 \001'
  _globals['_FILTERCONFIG']._serialized_start=225
  _globals['_FILTERCONFIG']._serialized_end=300
  _globals['_FILTERCONFIGPERROUTE']._serialized_start=302
  _globals['_FILTERCONFIGPERROUTE']._serialized_end=342
