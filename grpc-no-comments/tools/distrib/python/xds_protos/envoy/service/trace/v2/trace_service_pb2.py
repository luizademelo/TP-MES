
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2.core import base_pb2 as envoy_dot_api_dot_v2_dot_core_dot_base__pb2
try:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2
except AttributeError:
  envoy_dot_api_dot_v2_dot_core_dot_socket__option__pb2 = envoy_dot_api_dot_v2_dot_core_dot_base__pb2.envoy.api.v2.core.socket_option_pb2
from opencensus.proto.trace.v1 import trace_pb2 as opencensus_dot_proto_dot_trace_dot_v1_dot_trace__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*envoy/service/trace/v2/trace_service.proto\x12\x16\x65nvoy.service.trace.v2\x1a\x1c\x65nvoy/api/v2/core/base.proto\x1a%opencensus/proto/trace/v1/trace.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x16\n\x14StreamTracesResponse\"\xd0\x01\n\x13StreamTracesMessage\x12J\n\nidentifier\x18\x01 \x01(\x0b\x32\x36.envoy.service.trace.v2.StreamTracesMessage.Identifier\x12.\n\x05spans\x18\x02 \x03(\x0b\x32\x1f.opencensus.proto.trace.v1.Span\x1a=\n\nIdentifier\x12/\n\x04node\x18\x01 \x01(\x0b\x32\x17.envoy.api.v2.core.NodeB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x32}\n\x0cTraceService\x12m\n\x0cStreamTraces\x12+.envoy.service.trace.v2.StreamTracesMessage\x1a,.envoy.service.trace.v2.StreamTracesResponse\"\x00(\x01\x42\x8a\x01\n$io.envoyproxy.envoy.service.trace.v2B\x11TraceServiceProtoP\x01ZEgithub.com/envoyproxy/go-control-plane/envoy/service/trace/v2;tracev2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.trace.v2.trace_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.service.trace.v2B\021TraceServiceProtoP\001ZEgithub.com/envoyproxy/go-control-plane/envoy/service/trace/v2;tracev2\272\200\310\321\006\002\020\001'
  _STREAMTRACESMESSAGE_IDENTIFIER.fields_by_name['node']._options = None
  _STREAMTRACESMESSAGE_IDENTIFIER.fields_by_name['node']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_STREAMTRACESRESPONSE']._serialized_start=195
  _globals['_STREAMTRACESRESPONSE']._serialized_end=217
  _globals['_STREAMTRACESMESSAGE']._serialized_start=220
  _globals['_STREAMTRACESMESSAGE']._serialized_end=428
  _globals['_STREAMTRACESMESSAGE_IDENTIFIER']._serialized_start=367
  _globals['_STREAMTRACESMESSAGE_IDENTIFIER']._serialized_end=428
  _globals['_TRACESERVICE']._serialized_start=430
  _globals['_TRACESERVICE']._serialized_end=555
