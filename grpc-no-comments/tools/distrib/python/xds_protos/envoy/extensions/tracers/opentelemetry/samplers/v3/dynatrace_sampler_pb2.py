
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import http_service_pb2 as envoy_dot_config_dot_core_dot_v3_dot_http__service__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nJenvoy/extensions/tracers/opentelemetry/samplers/v3/dynatrace_sampler.proto\x12\x32\x65nvoy.extensions.tracers.opentelemetry.samplers.v3\x1a\'envoy/config/core/v3/http_service.proto\x1a\x1dudpa/annotations/status.proto\"\x94\x01\n\x16\x44ynatraceSamplerConfig\x12\x0e\n\x06tenant\x18\x01 \x01(\t\x12\x12\n\ncluster_id\x18\x02 \x01(\x05\x12\x37\n\x0chttp_service\x18\x03 \x01(\x0b\x32!.envoy.config.core.v3.HttpService\x12\x1d\n\x15root_spans_per_minute\x18\x04 \x01(\rB\xc9\x01\n@io.envoyproxy.envoy.extensions.tracers.opentelemetry.samplers.v3B\x15\x44ynatraceSamplerProtoP\x01Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/samplers/v3;samplersv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.tracers.opentelemetry.samplers.v3.dynatrace_sampler_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.tracers.opentelemetry.samplers.v3B\025DynatraceSamplerProtoP\001Zdgithub.com/envoyproxy/go-control-plane/envoy/extensions/tracers/opentelemetry/samplers/v3;samplersv3\272\200\310\321\006\002\020\002'
  _globals['_DYNATRACESAMPLERCONFIG']._serialized_start=203
  _globals['_DYNATRACESAMPLERCONFIG']._serialized_end=351
