
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nWenvoy/extensions/matching/input_matchers/consistent_hashing/v3/consistent_hashing.proto\x12>envoy.extensions.matching.input_matchers.consistent_hashing.v3\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"M\n\x11\x43onsistentHashing\x12\x11\n\tthreshold\x18\x01 \x01(\r\x12\x17\n\x06modulo\x18\x02 \x01(\rB\x07\xfa\x42\x04*\x02 \x00\x12\x0c\n\x04seed\x18\x03 \x01(\x04\x42\xec\x01\nLio.envoyproxy.envoy.extensions.matching.input_matchers.consistent_hashing.v3B\x16\x43onsistentHashingProtoP\x01Zzgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/consistent_hashing/v3;consistent_hashingv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.matching.input_matchers.consistent_hashing.v3.consistent_hashing_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nLio.envoyproxy.envoy.extensions.matching.input_matchers.consistent_hashing.v3B\026ConsistentHashingProtoP\001Zzgithub.com/envoyproxy/go-control-plane/envoy/extensions/matching/input_matchers/consistent_hashing/v3;consistent_hashingv3\272\200\310\321\006\002\020\002'
  _CONSISTENTHASHING.fields_by_name['modulo']._options = None
  _CONSISTENTHASHING.fields_by_name['modulo']._serialized_options = b'\372B\004*\002 \000'
  _globals['_CONSISTENTHASHING']._serialized_start=211
  _globals['_CONSISTENTHASHING']._serialized_end=288
