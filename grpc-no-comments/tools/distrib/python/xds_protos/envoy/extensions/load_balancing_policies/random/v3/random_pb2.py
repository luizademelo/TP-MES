
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.extensions.load_balancing_policies.common.v3 import common_pb2 as envoy_dot_extensions_dot_load__balancing__policies_dot_common_dot_v3_dot_common__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?envoy/extensions/load_balancing_policies/random/v3/random.proto\x12\x32\x65nvoy.extensions.load_balancing_policies.random.v3\x1a?envoy/extensions/load_balancing_policies/common/v3/common.proto\x1a\x1dudpa/annotations/status.proto\"j\n\x06Random\x12`\n\x12locality_lb_config\x18\x01 \x01(\x0b\x32\x44.envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfigB\xbd\x01\n@io.envoyproxy.envoy.extensions.load_balancing_policies.random.v3B\x0bRandomProtoP\x01Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/random/v3;randomv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.load_balancing_policies.random.v3.random_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n@io.envoyproxy.envoy.extensions.load_balancing_policies.random.v3B\013RandomProtoP\001Zbgithub.com/envoyproxy/go-control-plane/envoy/extensions/load_balancing_policies/random/v3;randomv3\272\200\310\321\006\002\020\002'
  _globals['_RANDOM']._serialized_start=215
  _globals['_RANDOM']._serialized_end=321
