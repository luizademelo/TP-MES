
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nKenvoy/extensions/resource_monitors/cpu_utilization/v3/cpu_utilization.proto\x12\x35\x65nvoy.extensions.resource_monitors.cpu_utilization.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xcd\x01\n\x14\x43puUtilizationConfig\x12~\n\x04mode\x18\x01 \x01(\x0e\x32\x66.envoy.extensions.resource_monitors.cpu_utilization.v3.CpuUtilizationConfig.UtilizationComputeStrategyB\x08\xfa\x42\x05\x82\x01\x02\x10\x01\"5\n\x1aUtilizationComputeStrategy\x12\x08\n\x04HOST\x10\x00\x12\r\n\tCONTAINER\x10\x01\x42\xd4\x01\nCio.envoyproxy.envoy.extensions.resource_monitors.cpu_utilization.v3B\x13\x43puUtilizationProtoP\x01Zngithub.com/envoyproxy/go-control-plane/envoy/extensions/resource_monitors/cpu_utilization/v3;cpu_utilizationv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.resource_monitors.cpu_utilization.v3.cpu_utilization_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nCio.envoyproxy.envoy.extensions.resource_monitors.cpu_utilization.v3B\023CpuUtilizationProtoP\001Zngithub.com/envoyproxy/go-control-plane/envoy/extensions/resource_monitors/cpu_utilization/v3;cpu_utilizationv3\272\200\310\321\006\002\020\002'
  _CPUUTILIZATIONCONFIG.fields_by_name['mode']._options = None
  _CPUUTILIZATIONCONFIG.fields_by_name['mode']._serialized_options = b'\372B\005\202\001\002\020\001'
  _globals['_CPUUTILIZATIONCONFIG']._serialized_start=191
  _globals['_CPUUTILIZATIONCONFIG']._serialized_end=396
  _globals['_CPUUTILIZATIONCONFIG_UTILIZATIONCOMPUTESTRATEGY']._serialized_start=343
  _globals['_CPUUTILIZATIONCONFIG_UTILIZATIONCOMPUTESTRATEGY']._serialized_end=396
