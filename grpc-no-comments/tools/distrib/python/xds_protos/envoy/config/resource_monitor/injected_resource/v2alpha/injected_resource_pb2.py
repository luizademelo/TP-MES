
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nOenvoy/config/resource_monitor/injected_resource/v2alpha/injected_resource.proto\x12\x37\x65nvoy.config.resource_monitor.injected_resource.v2alpha\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"3\n\x16InjectedResourceConfig\x12\x19\n\x08\x66ilename\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x42\xc8\x01\nEio.envoyproxy.envoy.config.resource_monitor.injected_resource.v2alphaB\x15InjectedResourceProtoP\x01Z^github.com/envoyproxy/go-control-plane/envoy/config/resource_monitor/injected_resource/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.resource_monitor.injected_resource.v2alpha.injected_resource_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.config.resource_monitor.injected_resource.v2alphaB\025InjectedResourceProtoP\001Z^github.com/envoyproxy/go-control-plane/envoy/config/resource_monitor/injected_resource/v2alpha\272\200\310\321\006\002\020\002'
  _INJECTEDRESOURCECONFIG.fields_by_name['filename']._options = None
  _INJECTEDRESOURCECONFIG.fields_by_name['filename']._serialized_options = b'\372B\004r\002 \001'
  _globals['_INJECTEDRESOURCECONFIG']._serialized_start=196
  _globals['_INJECTEDRESOURCECONFIG']._serialized_end=247
