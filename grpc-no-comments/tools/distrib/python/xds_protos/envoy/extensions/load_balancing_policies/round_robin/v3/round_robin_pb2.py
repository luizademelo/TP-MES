
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.load_balancing_policies.common.v3 import common_pb2 as envoy_dot_extensions_dot_load__balancing__policies_dot_common_dot_v3_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nIenvoy/extensions/load_balancing_policies/round_robin/v3/round_robin.proto\x12\x37\x65nvoy.extensions.load_balancing_policies.round_robin.v3\x1a?envoy/extensions/load_balancing_policies/common/v3/common.proto\x1a\x1dudpa/annotations/status.proto\"\xce\x01\n\nRoundRobin\x12^\n\x11slow_start_config\x18\x01 \x01(\x0b\x32\x43.envoy.extensions.load_balancing_policies.common.v3.SlowStartConfig\x12`\n\x12locality_lb_config\x18\x02 \x01(\x0b\x32\x44.envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfigB\xd0\x01\nEio.envoyproxy.envoy.extensions.load_balancing_policies.round_robin.v3B\x0fRoundRobinProtoP\x01Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/round_robin/v3;round_robinv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.round_robin.v3.round_robin_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\nEio.envoyproxy.envoy.extensions.load_balancing_policies.round_robin.v3B\017RoundRobinProtoP\001Zlgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/round_robin/v3;round_robinv3\272\200\310\321\006\002\020\002'
  _globals['_ROUNDROBIN']._serialized_start=231
  _globals['_ROUNDROBIN']._serialized_end=437
