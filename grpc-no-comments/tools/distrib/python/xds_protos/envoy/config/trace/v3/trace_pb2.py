
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.trace.v3 import datadog_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_datadog__pb2
from envoy.config.trace.v3 import dynamic_ot_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_dynamic__ot__pb2
from envoy.config.trace.v3 import http_tracer_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_http__tracer__pb2
from envoy.config.trace.v3 import lightstep_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_lightstep__pb2
from envoy.config.trace.v3 import opentelemetry_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_opentelemetry__pb2
from envoy.config.trace.v3 import service_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_service__pb2
from envoy.config.trace.v3 import zipkin_pb2 as envoy_dot_config_dot_trace_dot_v3_dot_zipkin__pb2

from envoy.config.trace.v3.datadog_pb2 import *
from envoy.config.trace.v3.dynamic_ot_pb2 import *
from envoy.config.trace.v3.http_tracer_pb2 import *
from envoy.config.trace.v3.lightstep_pb2 import *
from envoy.config.trace.v3.opentelemetry_pb2 import *
from envoy.config.trace.v3.service_pb2 import *
from envoy.config.trace.v3.zipkin_pb2 import *

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/config/trace/v3/trace.proto\x12\x15\x65nvoy.config.trace.v3\x1a#envoy/config/trace/v3/datadog.proto\x1a&envoy/config/trace/v3/dynamic_ot.proto\x1a\'envoy/config/trace/v3/http_tracer.proto\x1a%envoy/config/trace/v3/lightstep.proto\x1a)envoy/config/trace/v3/opentelemetry.proto\x1a#envoy/config/trace/v3/service.proto\x1a\"envoy/config/trace/v3/zipkin.protoBy\n#io.envoyproxy.envoy.config.trace.v3B\nTraceProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3P\x00P\x01P\x02P\x03P\x04P\x05P\x06\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v3.trace_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v3B\nTraceProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v3;tracev3'
