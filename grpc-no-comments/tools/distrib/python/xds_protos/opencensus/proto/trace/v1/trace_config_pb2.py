
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,opencensus/proto/trace/v1/trace_config.proto\x12\x19opencensus.proto.trace.v1\"\x87\x03\n\x0bTraceConfig\x12L\n\x13probability_sampler\x18\x01 \x01(\x0b\x32-.opencensus.proto.trace.v1.ProbabilitySamplerH\x00\x12\x46\n\x10\x63onstant_sampler\x18\x02 \x01(\x0b\x32*.opencensus.proto.trace.v1.ConstantSamplerH\x00\x12O\n\x15rate_limiting_sampler\x18\x03 \x01(\x0b\x32..opencensus.proto.trace.v1.RateLimitingSamplerH\x00\x12 \n\x18max_number_of_attributes\x18\x04 \x01(\x03\x12!\n\x19max_number_of_annotations\x18\x05 \x01(\x03\x12$\n\x1cmax_number_of_message_events\x18\x06 \x01(\x03\x12\x1b\n\x13max_number_of_links\x18\x07 \x01(\x03\x42\t\n\x07sampler\"1\n\x12ProbabilitySampler\x12\x1b\n\x13samplingProbability\x18\x01 \x01(\x01\"\xa6\x01\n\x0f\x43onstantSampler\x12M\n\x08\x64\x65\x63ision\x18\x01 \x01(\x0e\x32;.opencensus.proto.trace.v1.ConstantSampler.ConstantDecision\"D\n\x10\x43onstantDecision\x12\x0e\n\nALWAYS_OFF\x10\x00\x12\r\n\tALWAYS_ON\x10\x01\x12\x11\n\rALWAYS_PARENT\x10\x02\"\"\n\x13RateLimitingSampler\x12\x0b\n\x03qps\x18\x01 \x01(\x03\x42\x92\x01\n\x1cio.opencensus.proto.trace.v1B\x10TraceConfigProtoP\x01ZBgithub.com/census-instrumentation/opencensus-proto/gen-go/trace/v1\xea\x02\x19OpenCensus.Proto.Trace.V1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'opencensus.proto.trace.v1.trace_config_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.opencensus.proto.trace.v1B\020TraceConfigProtoP\001ZBgithub.com/census-instrumentation/opencensus-proto/gen-go/trace/v1\352\002\031OpenCensus.Proto.Trace.V1'
  _globals['_TRACECONFIG']._serialized_start=76
  _globals['_TRACECONFIG']._serialized_end=467
  _globals['_PROBABILITYSAMPLER']._serialized_start=469
  _globals['_PROBABILITYSAMPLER']._serialized_end=518
  _globals['_CONSTANTSAMPLER']._serialized_start=521
  _globals['_CONSTANTSAMPLER']._serialized_end=687
  _globals['_CONSTANTSAMPLER_CONSTANTDECISION']._serialized_start=619
  _globals['_CONSTANTSAMPLER_CONSTANTDECISION']._serialized_end=687
  _globals['_RATELIMITINGSAMPLER']._serialized_start=689
  _globals['_RATELIMITINGSAMPLER']._serialized_end=723
