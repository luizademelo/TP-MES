
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'envoy/config/trace/v2/http_tracer.proto\x12\x15\x65nvoy.config.trace.v2\x1a\x19google/protobuf/any.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc8\x01\n\x07Tracing\x12\x31\n\x04http\x18\x01 \x01(\x0b\x32#.envoy.config.trace.v2.Tracing.Http\x1a\x89\x01\n\x04Http\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12-\n\x06\x63onfig\x18\x02 \x01(\x0b\x32\x17.google.protobuf.StructB\x02\x18\x01H\x00\x12,\n\x0ctyped_config\x18\x03 \x01(\x0b\x32\x14.google.protobuf.AnyH\x00\x42\r\n\x0b\x63onfig_typeB\x86\x01\n#io.envoyproxy.envoy.config.trace.v2B\x0fHttpTracerProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.http_tracer_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\017HttpTracerProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _TRACING_HTTP.fields_by_name['name']._options = None
  _TRACING_HTTP.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _TRACING_HTTP.fields_by_name['config']._options = None
  _TRACING_HTTP.fields_by_name['config']._serialized_options = b'\030\001'
  _globals['_TRACING']._serialized_start=180
  _globals['_TRACING']._serialized_end=380
  _globals['_TRACING_HTTP']._serialized_start=243
  _globals['_TRACING_HTTP']._serialized_end=380
