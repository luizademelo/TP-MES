
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.load_balancing_policies.common.v3 import common_pb2 as envoy_dot_extensions_dot_load__balancing__policies_dot_common_dot_v3_dot_common__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?envoy/extensions/load_balancing_policies/maglev/v3/maglev.proto\x12\x32\x65nvoy.extensions.load_balancing_policies.maglev.v3\x1a?envoy/extensions/load_balancing_policies/common/v3/common.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xc0\x02\n\x06Maglev\x12<\n\ntable_size\x18\x01 \x01(\x0b\x32\x1c.google.protobuf.UInt64ValueB\n\xfa\x42\x07\x32\x05\x18\xcb\x96\xb1\x02\x12s\n\x1c\x63onsistent_hashing_lb_config\x18\x02 \x01(\x0b\x32M.envoy.extensions.load_balancing_policies.common.v3.ConsistentHashingLbConfig\x12\x82\x01\n\x1blocality_weighted_lb_config\x18\x03 \x01(\x0b\x32].envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig.LocalityWeightedLbConfigB\xbd\x01\n@io.envoyproxy.envoy.extensions.load_balancing_policies.maglev.v3B\x0bMaglevProtoP\x01Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/maglev/v3;maglevv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.maglev.v3.maglev_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.load_balancing_policies.maglev.v3B\013MaglevProtoP\001Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/maglev/v3;maglevv3\272\200\310\321\006\002\020\002'
  _MAGLEV.fields_by_name['table_size']._options = None
  _MAGLEV.fields_by_name['table_size']._serialized_options = b'\372B\0072\005\030\313\226\261\002'
  _globals['_MAGLEV']._serialized_start=273
  _globals['_MAGLEV']._serialized_end=593
