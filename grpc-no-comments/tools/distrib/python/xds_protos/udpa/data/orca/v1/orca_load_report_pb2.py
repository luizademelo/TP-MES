
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(udpa/data/orca/v1/orca_load_report.proto\x12\x11udpa.data.orca.v1\x1a\x17validate/validate.proto\"\x9a\x03\n\x0eOrcaLoadReport\x12\x30\n\x0f\x63pu_utilization\x18\x01 \x01(\x01\x42\x17\xfa\x42\x14\x12\x12\x19\x00\x00\x00\x00\x00\x00\xf0?)\x00\x00\x00\x00\x00\x00\x00\x00\x12\x30\n\x0fmem_utilization\x18\x02 \x01(\x01\x42\x17\xfa\x42\x14\x12\x12\x19\x00\x00\x00\x00\x00\x00\xf0?)\x00\x00\x00\x00\x00\x00\x00\x00\x12\x0b\n\x03rps\x18\x03 \x01(\x04\x12H\n\x0crequest_cost\x18\x04 \x03(\x0b\x32\x32.udpa.data.orca.v1.OrcaLoadReport.RequestCostEntry\x12\x65\n\x0butilization\x18\x05 \x03(\x0b\x32\x32.udpa.data.orca.v1.OrcaLoadReport.UtilizationEntryB\x1c\xfa\x42\x19\x9a\x01\x16*\x14\x12\x12\x19\x00\x00\x00\x00\x00\x00\xf0?)\x00\x00\x00\x00\x00\x00\x00\x00\x1a\x32\n\x10RequestCostEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x01:\x02\x38\x01\x1a\x32\n\x10UtilizationEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x01:\x02\x38\x01\x42\x64\n!com.github.udpa.udpa.data.orca.v1B\x13OrcaLoadReportProtoP\x01Z(github.com/cncf/xds/go/udpa/data/orca/v1b\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'udpa.data.orca.v1.orca_load_report_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n!com.github.udpa.udpa.data.orca.v1B\023OrcaLoadReportProtoP\001Z(github.com/cncf/xds/go/udpa/data/orca/v1'
  _ORCALOADREPORT_REQUESTCOSTENTRY._options = None
  _ORCALOADREPORT_REQUESTCOSTENTRY._serialized_options = b'8\001'
  _ORCALOADREPORT_UTILIZATIONENTRY._options = None
  _ORCALOADREPORT_UTILIZATIONENTRY._serialized_options = b'8\001'
  _ORCALOADREPORT.fields_by_name['cpu_utilization']._options = None
  _ORCALOADREPORT.fields_by_name['cpu_utilization']._serialized_options = b'\372B\024\022\022\031\000\000\000\000\000\000\360?)\000\000\000\000\000\000\000\000'
  _ORCALOADREPORT.fields_by_name['mem_utilization']._options = None
  _ORCALOADREPORT.fields_by_name['mem_utilization']._serialized_options = b'\372B\024\022\022\031\000\000\000\000\000\000\360?)\000\000\000\000\000\000\000\000'
  _ORCALOADREPORT.fields_by_name['utilization']._options = None
  _ORCALOADREPORT.fields_by_name['utilization']._serialized_options = b'\372B\031\232\001\026*\024\022\022\031\000\000\000\000\000\000\360?)\000\000\000\000\000\000\000\000'
  _globals['_ORCALOADREPORT']._serialized_start=89
  _globals['_ORCALOADREPORT']._serialized_end=499
  _globals['_ORCALOADREPORT_REQUESTCOSTENTRY']._serialized_start=397
  _globals['_ORCALOADREPORT_REQUESTCOSTENTRY']._serialized_end=447
  _globals['_ORCALOADREPORT_UTILIZATIONENTRY']._serialized_start=449
  _globals['_ORCALOADREPORT_UTILIZATIONENTRY']._serialized_end=499
