
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.data.tap.v2alpha import http_pb2 as envoy_dot_data_dot_tap_dot_v2alpha_dot_http__pb2
from envoy.data.tap.v2alpha import transport_pb2 as envoy_dot_data_dot_tap_dot_v2alpha_dot_transport__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/data/tap/v2alpha/wrapper.proto\x12\x16\x65nvoy.data.tap.v2alpha\x1a!envoy/data/tap/v2alpha/http.proto\x1a&envoy/data/tap/v2alpha/transport.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xea\x02\n\x0cTraceWrapper\x12H\n\x13http_buffered_trace\x18\x01 \x01(\x0b\x32).envoy.data.tap.v2alpha.HttpBufferedTraceH\x00\x12W\n\x1bhttp_streamed_trace_segment\x18\x02 \x01(\x0b\x32\x30.envoy.data.tap.v2alpha.HttpStreamedTraceSegmentH\x00\x12L\n\x15socket_buffered_trace\x18\x03 \x01(\x0b\x32+.envoy.data.tap.v2alpha.SocketBufferedTraceH\x00\x12[\n\x1dsocket_streamed_trace_segment\x18\x04 \x01(\x0b\x32\x32.envoy.data.tap.v2alpha.SocketStreamedTraceSegmentH\x00\x42\x0c\n\x05trace\x12\x03\xf8\x42\x01\x42}\n$io.envoyproxy.envoy.data.tap.v2alphaB\x0cWrapperProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/data/tap/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.data.tap.v2alpha.wrapper_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.data.tap.v2alphaB\014WrapperProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/data/tap/v2alpha\272\200\310\321\006\002\020\001'
  _TRACEWRAPPER.oneofs_by_name['trace']._options = None
  _TRACEWRAPPER.oneofs_by_name['trace']._serialized_options = b'\370B\001'
  _globals['_TRACEWRAPPER']._serialized_start=196
  _globals['_TRACEWRAPPER']._serialized_end=558
