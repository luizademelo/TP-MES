
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.api.v2 import discovery_pb2 as envoy_dot_api_dot_v2_dot_discovery__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/service/discovery/v2/ads.proto\x12\x1a\x65nvoy.service.discovery.v2\x1a\x1c\x65nvoy/api/v2/discovery.proto\x1a\x1dudpa/annotations/status.proto\"\n\n\x08\x41\x64sDummy2\xed\x01\n\x1a\x41ggregatedDiscoveryService\x12\x62\n\x19StreamAggregatedResources\x12\x1e.envoy.api.v2.DiscoveryRequest\x1a\x1f.envoy.api.v2.DiscoveryResponse\"\x00(\x01\x30\x01\x12k\n\x18\x44\x65ltaAggregatedResources\x12#.envoy.api.v2.DeltaDiscoveryRequest\x1a$.envoy.api.v2.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x42\x8d\x01\n(io.envoyproxy.envoy.service.discovery.v2B\x08\x41\x64sProtoP\x01ZMgithub.com/envoyproxy/go-control-plane/envoy/service/discovery/v2;discoveryv2\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.discovery.v2.ads_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n(io.envoyproxy.envoy.service.discovery.v2B\010AdsProtoP\001ZMgithub.com/envoyproxy/go-control-plane/envoy/service/discovery/v2;discoveryv2\272\200\310\321\006\002\020\001'
  _globals['_ADSDUMMY']._serialized_start=129
  _globals['_ADSDUMMY']._serialized_end=139
  _globals['_AGGREGATEDDISCOVERYSERVICE']._serialized_start=142
  _globals['_AGGREGATEDDISCOVERYSERVICE']._serialized_end=379
