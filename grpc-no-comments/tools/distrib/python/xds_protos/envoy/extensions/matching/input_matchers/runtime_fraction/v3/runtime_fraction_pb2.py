
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nSenvoy/extensions/matching/input_matchers/runtime_fraction/v3/runtime_fraction.proto\x12<envoy.extensions.matching.input_matchers.runtime_fraction.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"s\n\x0fRuntimeFraction\x12R\n\x10runtime_fraction\x18\x01 \x01(\x0b\x32..envoy.config.core.v3.RuntimeFractionalPercentB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x0c\n\x04seed\x18\x02 \x01(\x04\x42\xe4\x01\nJio.envoyproxy.envoy.extensions.matching.input_matchers.runtime_fraction.v3B\x14RuntimeFractionProtoP\x01Zvgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/runtime_fraction/v3;runtime_fractionv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.matching.input_matchers.runtime_fraction.v3.runtime_fraction_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nJio.envoyproxy.envoy.extensions.matching.input_matchers.runtime_fraction.v3B\024RuntimeFractionProtoP\001Zvgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/runtime_fraction/v3;runtime_fractionv3\272\200\310\321\006\002\020\002'
  _RUNTIMEFRACTION.fields_by_name['runtime_fraction']._options = None
  _RUNTIMEFRACTION.fields_by_name['runtime_fraction']._serialized_options = b'\372B\005\212\001\002\020\001'
  _globals['_RUNTIMEFRACTION']._serialized_start=238
  _globals['_RUNTIMEFRACTION']._serialized_end=353
