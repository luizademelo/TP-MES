
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/admin/v2alpha/metrics.proto\x12\x13\x65nvoy.admin.v2alpha\x1a\x1dudpa/annotations/status.proto\"\x81\x01\n\x0cSimpleMetric\x12\x34\n\x04type\x18\x01 \x01(\x0e\x32&.envoy.admin.v2alpha.SimpleMetric.Type\x12\r\n\x05value\x18\x02 \x01(\x04\x12\x0c\n\x04name\x18\x03 \x01(\t\"\x1e\n\x04Type\x12\x0b\n\x07\x43OUNTER\x10\x00\x12\t\n\x05GAUGE\x10\x01\x42w\n!io.envoyproxy.envoy.admin.v2alphaB\x0cMetricsProtoP\x01Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v2alpha.metrics_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!io.envoyproxy.envoy.admin.v2alphaB\014MetricsProtoP\001Z:github.com/envoyproxy/go-control-plane/envoy/admin/v2alpha\272\200\310\321\006\002\020\001'
  _globals['_SIMPLEMETRIC']._serialized_start=90
  _globals['_SIMPLEMETRIC']._serialized_end=219
  _globals['_SIMPLEMETRIC_TYPE']._serialized_start=189
  _globals['_SIMPLEMETRIC_TYPE']._serialized_end=219
