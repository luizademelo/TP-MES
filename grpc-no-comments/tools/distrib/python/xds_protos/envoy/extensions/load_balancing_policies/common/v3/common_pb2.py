
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import base_pb2 as envoy_dot_config_dot_core_dot_v3_dot_base__pb2
from envoy.type.v3 import percent_pb2 as envoy_dot_type_dot_v3_dot_percent__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?envoy/extensions/load_balancing_policies/common/v3/common.proto\x12\x32\x65nvoy.extensions.load_balancing_policies.common.v3\x1a\x1f\x65nvoy/config/core/v3/base.proto\x1a\x1b\x65nvoy/type/v3/percent.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1egoogle/protobuf/wrappers.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xed\x03\n\x10LocalityLbConfig\x12v\n\x14zone_aware_lb_config\x18\x01 \x01(\x0b\x32V.envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig.ZoneAwareLbConfigH\x00\x12\x84\x01\n\x1blocality_weighted_lb_config\x18\x02 \x01(\x0b\x32].envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig.LocalityWeightedLbConfigH\x00\x1a\x9b\x01\n\x11ZoneAwareLbConfig\x12/\n\x0frouting_enabled\x18\x01 \x01(\x0b\x32\x16.envoy.type.v3.Percent\x12\x36\n\x10min_cluster_size\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt64Value\x12\x1d\n\x15\x66\x61il_traffic_on_panic\x18\x03 \x01(\x08\x1a\x1a\n\x18LocalityWeightedLbConfigB \n\x19locality_config_specifier\x12\x03\xf8\x42\x01\"\xb4\x01\n\x0fSlowStartConfig\x12\x34\n\x11slow_start_window\x18\x01 \x01(\x0b\x32\x19.google.protobuf.Duration\x12\x37\n\naggression\x18\x02 \x01(\x0b\x32#.envoy.config.core.v3.RuntimeDouble\x12\x32\n\x12min_weight_percent\x18\x03 \x01(\x0b\x32\x16.envoy.type.v3.Percent\"\x81\x01\n\x19\x43onsistentHashingLbConfig\x12 \n\x18use_hostname_for_hashing\x18\x01 \x01(\x08\x12\x42\n\x13hash_balance_factor\x18\x02 \x01(\x0b\x32\x1c.google.protobuf.UInt32ValueB\x07\xfa\x42\x04*\x02(dB\xbd\x01\n@io.envoyproxy.envoy.extensions.load_balancing_policies.common.v3B\x0b\x43ommonProtoP\x01Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/common/v3;commonv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.common.v3.common_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.load_balancing_policies.common.v3B\013CommonProtoP\001Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/common/v3;commonv3\272\200\310\321\006\002\020\002'
  _LOCALITYLBCONFIG.oneofs_by_name['locality_config_specifier']._options = None
  _LOCALITYLBCONFIG.oneofs_by_name['locality_config_specifier']._serialized_options = b'\370B\001'
  _CONSISTENTHASHINGLBCONFIG.fields_by_name['hash_balance_factor']._options = None
  _CONSISTENTHASHINGLBCONFIG.fields_by_name['hash_balance_factor']._serialized_options = b'\372B\004*\002(d'
  _globals['_LOCALITYLBCONFIG']._serialized_start=302
  _globals['_LOCALITYLBCONFIG']._serialized_end=795
  _globals['_LOCALITYLBCONFIG_ZONEAWARELBCONFIG']._serialized_start=578
  _globals['_LOCALITYLBCONFIG_ZONEAWARELBCONFIG']._serialized_end=733
  _globals['_LOCALITYLBCONFIG_LOCALITYWEIGHTEDLBCONFIG']._serialized_start=735
  _globals['_LOCALITYLBCONFIG_LOCALITYWEIGHTEDLBCONFIG']._serialized_end=761
  _globals['_SLOWSTARTCONFIG']._serialized_start=798
  _globals['_SLOWSTARTCONFIG']._serialized_end=978
  _globals['_CONSISTENTHASHINGLBCONFIG']._serialized_start=981
  _globals['_CONSISTENTHASHINGLBCONFIG']._serialized_end=1110
