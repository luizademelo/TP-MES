
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from xds.data.orca.v3 import orca_load_report_pb2 as xds_dot_data_dot_orca_dot_v3_dot_orca__load__report__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1exds/service/orca/v3/orca.proto\x12\x13xds.service.orca.v3\x1a\'xds/data/orca/v3/orca_load_report.proto\x1a\x1egoogle/protobuf/duration.proto\"g\n\x15OrcaLoadReportRequest\x12\x32\n\x0freport_interval\x18\x01 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x1a\n\x12request_cost_names\x18\x02 \x03(\t2u\n\x0eOpenRcaService\x12\x63\n\x11StreamCoreMetrics\x12*.xds.service.orca.v3.OrcaLoadReportRequest\x1a .xds.data.orca.v3.OrcaLoadReport0\x01\x42Y\n\x1e\x63om.github.xds.service.orca.v3B\tOrcaProtoP\x01Z*github.com/cncf/xds/go/xds/service/orca/v3b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xds.service.orca.v3.orca_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\036com.github.xds.service.orca.v3B\tOrcaProtoP\001Z*github.com/cncf/xds/go/xds/service/orca/v3'
  _globals['_ORCALOADREPORTREQUEST']._serialized_start=128
  _globals['_ORCALOADREPORTREQUEST']._serialized_end=231
  _globals['_OPENRCASERVICE']._serialized_start=233
  _globals['_OPENRCASERVICE']._serialized_end=350
