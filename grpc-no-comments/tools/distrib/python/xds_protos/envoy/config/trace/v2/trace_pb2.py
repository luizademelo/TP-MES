
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.trace.v2 import datadog_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_datadog__pb2
from envoy.config.trace.v2 import dynamic_ot_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_dynamic__ot__pb2
from envoy.config.trace.v2 import http_tracer_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_http__tracer__pb2
from envoy.config.trace.v2 import lightstep_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_lightstep__pb2
from envoy.config.trace.v2 import service_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_service__pb2
from envoy.config.trace.v2 import zipkin_pb2 as envoy_dot_config_dot_trace_dot_v2_dot_zipkin__pb2

from envoy.config.trace.v2.datadog_pb2 import *
from envoy.config.trace.v2.dynamic_ot_pb2 import *
from envoy.config.trace.v2.http_tracer_pb2 import *
from envoy.config.trace.v2.lightstep_pb2 import *
from envoy.config.trace.v2.service_pb2 import *
from envoy.config.trace.v2.zipkin_pb2 import *

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/config/trace/v2/trace.proto\x12\x15\x65nvoy.config.trace.v2\x1a#envoy/config/trace/v2/datadog.proto\x1a&envoy/config/trace/v2/dynamic_ot.proto\x1a\'envoy/config/trace/v2/http_tracer.proto\x1a%envoy/config/trace/v2/lightstep.proto\x1a#envoy/config/trace/v2/service.proto\x1a\"envoy/config/trace/v2/zipkin.protoBy\n#io.envoyproxy.envoy.config.trace.v2B\nTraceProtoP\x01ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2P\x00P\x01P\x02P\x03P\x04P\x05\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.trace.v2.trace_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n#io.envoyproxy.envoy.config.trace.v2B\nTraceProtoP\001ZDgithub.com/envoyproxy/go-control-plane/envoy/config/trace/v2;tracev2'
