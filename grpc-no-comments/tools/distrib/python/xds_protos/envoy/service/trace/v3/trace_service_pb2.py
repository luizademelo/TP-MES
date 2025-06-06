
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from opencensus.proto.trace.v1 import trace_pb2 as opencensus_dot_proto_dot_trace_dot_v1_dot_trace__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*envoy/service/trace/v3/trace_service.proto\x12\x16\x65nvoy.service.trace.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a%opencensus/proto/trace/v1/trace.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"J\n\x14StreamTracesResponse:2\x9a\xc5\x88\x1e-\n+envoy.service.trace.v2.StreamTracesResponse\"\xc4\x02\n\x13StreamTracesMessage\x12J\n\nidentifier\x18\x01 \x01(\x0b\x32\x36.envoy.service.trace.v3.StreamTracesMessage.Identifier\x12.\n\x05spans\x18\x02 \x03(\x0b\x32\x1f.opencensus.proto.trace.v1.Span\x1a~\n\nIdentifier\x12\x32\n\x04node\x18\x01 \x01(\x0b\x32\x1a.envoy.config.core.v3.NodeB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01:<\x9a\xc5\x88\x1e\x37\n5envoy.service.trace.v2.StreamTracesMessage.Identifier:1\x9a\xc5\x88\x1e,\n*envoy.service.trace.v2.StreamTracesMessage2}\n\x0cTraceService\x12m\n\x0cStreamTraces\x12+.envoy.service.trace.v3.StreamTracesMessage\x1a,.envoy.service.trace.v3.StreamTracesResponse\"\x00(\x01\x42\x8a\x01\n$io.envoyproxy.envoy.service.trace.v3B\x11TraceServiceProtoP\x01ZEgithub.com/envoyproxy/go-control-plane/envoy/service/trace/v3;tracev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.trace.v3.trace_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.service.trace.v3B\021TraceServiceProtoP\001ZEgithub.com/envoyproxy/go-control-plane/envoy/service/trace/v3;tracev3\272\200\310\321\006\002\020\002'
  _STREAMTRACESRESPONSE._options = None
  _STREAMTRACESRESPONSE._serialized_options = b'\232\305\210\036-\n+envoy.service.trace.v2.StreamTracesResponse'
  _STREAMTRACESMESSAGE_IDENTIFIER.fields_by_name['node']._options = None
  _STREAMTRACESMESSAGE_IDENTIFIER.fields_by_name['node']._serialized_options = b'\372B\005\212\001\002\020\001'
  _STREAMTRACESMESSAGE_IDENTIFIER._options = None
  _STREAMTRACESMESSAGE_IDENTIFIER._serialized_options = b'\232\305\210\0367\n5envoy.service.trace.v2.StreamTracesMessage.Identifier'
  _STREAMTRACESMESSAGE._options = None
  _STREAMTRACESMESSAGE._serialized_options = b'\232\305\210\036,\n*envoy.service.trace.v2.StreamTracesMessage'
  _globals['_STREAMTRACESRESPONSE']._serialized_start=233
  _globals['_STREAMTRACESRESPONSE']._serialized_end=307
  _globals['_STREAMTRACESMESSAGE']._serialized_start=310
  _globals['_STREAMTRACESMESSAGE']._serialized_end=634
  _globals['_STREAMTRACESMESSAGE_IDENTIFIER']._serialized_start=457
  _globals['_STREAMTRACESMESSAGE_IDENTIFIER']._serialized_end=583
  _globals['_TRACESERVICE']._serialized_start=636
  _globals['_TRACESERVICE']._serialized_end=761
