
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1c\x65nvoy/admin/v3/metrics.proto\x12\x0e\x65nvoy.admin.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xa5\x01\n\x0cSimpleMetric\x12/\n\x04type\x18\x01 \x01(\x0e\x32!.envoy.admin.v3.SimpleMetric.Type\x12\r\n\x05value\x18\x02 \x01(\x04\x12\x0c\n\x04name\x18\x03 \x01(\t\"\x1e\n\x04Type\x12\x0b\n\x07\x43OUNTER\x10\x00\x12\t\n\x05GAUGE\x10\x01:\'\x9a\xc5\x88\x1e\"\n envoy.admin.v2alpha.SimpleMetricBu\n\x1cio.envoyproxy.envoy.admin.v3B\x0cMetricsProtoP\x01Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.admin.v3.metrics_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\034io.envoyproxy.envoy.admin.v3B\014MetricsProtoP\001Z=github.com/envoyproxy/go-control-plane/envoy/admin/v3;adminv3\272\200\310\321\006\002\020\002'
  _SIMPLEMETRIC._options = None
  _SIMPLEMETRIC._serialized_options = b'\232\305\210\036\"\n envoy.admin.v2alpha.SimpleMetric'
  _globals['_SIMPLEMETRIC']._serialized_start=115
  _globals['_SIMPLEMETRIC']._serialized_end=280
  _globals['_SIMPLEMETRIC_TYPE']._serialized_start=209
  _globals['_SIMPLEMETRIC_TYPE']._serialized_end=239
