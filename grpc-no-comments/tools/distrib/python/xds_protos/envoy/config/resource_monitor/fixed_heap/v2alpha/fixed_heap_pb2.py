
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nAenvoy/config/resource_monitor/fixed_heap/v2alpha/fixed_heap.proto\x12\x30\x65nvoy.config.resource_monitor.fixed_heap.v2alpha\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"7\n\x0f\x46ixedHeapConfig\x12$\n\x13max_heap_size_bytes\x18\x01 \x01(\x04\x42\x07\xfa\x42\x04\x32\x02 \x00\x42\xb3\x01\n>io.envoyproxy.envoy.config.resource_monitor.fixed_heap.v2alphaB\x0e\x46ixedHeapProtoP\x01ZWgithub.com/envoyproxy/go-control-plane/envoy/config/resource_monitor/fixed_heap/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.resource_monitor.fixed_heap.v2alpha.fixed_heap_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n>io.envoyproxy.envoy.config.resource_monitor.fixed_heap.v2alphaB\016FixedHeapProtoP\001ZWgithub.com/envoyproxy/go-control-plane/envoy/config/resource_monitor/fixed_heap/v2alpha\272\200\310\321\006\002\020\002'
  _FIXEDHEAPCONFIG.fields_by_name['max_heap_size_bytes']._options = None
  _FIXEDHEAPCONFIG.fields_by_name['max_heap_size_bytes']._serialized_options = b'\372B\0042\002 \000'
  _globals['_FIXEDHEAPCONFIG']._serialized_start=175
  _globals['_FIXEDHEAPCONFIG']._serialized_end=230
