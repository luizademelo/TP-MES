
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nKenvoy/extensions/matching/common_inputs/environment_variable/v3/input.proto\x12?envoy.extensions.matching.common_inputs.environment_variable.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\x1f\n\x06\x43onfig\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x42\xe4\x01\nMio.envoyproxy.envoy.extensions.matching.common_inputs.environment_variable.v3B\nInputProtoP\x01Z}github.com/envoyproxy/go-control-plane/envoy/extensions/matching/common_inputs/environment_variable/v3;environment_variablev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.matching.common_inputs.environment_variable.v3.input_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nMio.envoyproxy.envoy.extensions.matching.common_inputs.environment_variable.v3B\nInputProtoP\001Z}github.com/envoyproxy/go-control-plane/envoy/extensions/matching/common_inputs/environment_variable/v3;environment_variablev3\272\200\310\321\006\002\020\002'
  _CONFIG.fields_by_name['name']._options = None
  _CONFIG.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _globals['_CONFIG']._serialized_start=200
  _globals['_CONFIG']._serialized_end=231
