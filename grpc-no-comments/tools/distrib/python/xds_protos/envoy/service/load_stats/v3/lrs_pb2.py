
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.config.endpoint.v3 import load_report_pb2 as envoy_dot_config_dot_endpoint_dot_v3_dot_load__report__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/service/load_stats/v3/lrs.proto\x12\x1b\x65nvoy.service.load_stats.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a*envoy/config/endpoint/v3/load_report.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"\xb0\x01\n\x10LoadStatsRequest\x12(\n\x04node\x18\x01 \x01(\x0b\x32\x1a.envoy.config.core.v3.Node\x12=\n\rcluster_stats\x18\x02 \x03(\x0b\x32&.envoy.config.endpoint.v3.ClusterStats:3\x9a\xc5\x88\x1e.\n,envoy.service.load_stats.v2.LoadStatsRequest\"\xd7\x01\n\x11LoadStatsResponse\x12\x10\n\x08\x63lusters\x18\x01 \x03(\t\x12\x19\n\x11send_all_clusters\x18\x04 \x01(\x08\x12:\n\x17load_reporting_interval\x18\x02 \x01(\x0b\x32\x19.google.protobuf.Duration\x12#\n\x1breport_endpoint_granularity\x18\x03 \x01(\x08:4\x9a\xc5\x88\x1e/\n-envoy.service.load_stats.v2.LoadStatsResponse2\x8e\x01\n\x14LoadReportingService\x12v\n\x0fStreamLoadStats\x12-.envoy.service.load_stats.v3.LoadStatsRequest\x1a..envoy.service.load_stats.v3.LoadStatsResponse\"\x00(\x01\x30\x01\x42\x90\x01\n)io.envoyproxy.envoy.service.load_stats.v3B\x08LrsProtoP\x01ZOgithub.com/envoyproxy/go-control-plane/envoy/service/load_stats/v3;load_statsv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.load_stats.v3.lrs_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n)io.envoyproxy.envoy.service.load_stats.v3B\010LrsProtoP\001ZOgithub.com/envoyproxy/go-control-plane/envoy/service/load_stats/v3;load_statsv3\272\200\310\321\006\002\020\002'
  _LOADSTATSREQUEST._options = None
  _LOADSTATSREQUEST._serialized_options = b'\232\305\210\036.\n,envoy.service.load_stats.v2.LoadStatsRequest'
  _LOADSTATSRESPONSE._options = None
  _LOADSTATSRESPONSE._serialized_options = b'\232\305\210\036/\n-envoy.service.load_stats.v2.LoadStatsResponse'
  _globals['_LOADSTATSREQUEST']._serialized_start=246
  _globals['_LOADSTATSREQUEST']._serialized_end=422
  _globals['_LOADSTATSRESPONSE']._serialized_start=425
  _globals['_LOADSTATSRESPONSE']._serialized_end=640
  _globals['_LOADREPORTINGSERVICE']._serialized_start=643
  _globals['_LOADREPORTINGSERVICE']._serialized_end=785
