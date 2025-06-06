
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2
from envoy.annotations import resource_pb2 as envoy_dot_annotations_dot_resource__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n$envoy/service/endpoint/v3/leds.proto\x12\x19\x65nvoy.service.endpoint.v3\x1a*envoy/service/discovery/v3/discovery.proto\x1a envoy/annotations/resource.proto\x1a\x1dudpa/annotations/status.proto\"\x0b\n\tLedsDummy2\xd7\x01\n LocalityEndpointDiscoveryService\x12\x85\x01\n\x16\x44\x65ltaLocalityEndpoints\x12\x31.envoy.service.discovery.v3.DeltaDiscoveryRequest\x1a\x32.envoy.service.discovery.v3.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x1a+\x8a\xa4\x96\xf3\x07%\n#envoy.config.endpoint.v3.LbEndpointB\x8b\x01\n\'io.envoyproxy.envoy.service.endpoint.v3B\tLedsProtoP\x01ZKgithub.com/envoyproxy/go-control-plane/envoy/service/endpoint/v3;endpointv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.endpoint.v3.leds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\'io.envoyproxy.envoy.service.endpoint.v3B\tLedsProtoP\001ZKgithub.com/envoyproxy/go-control-plane/envoy/service/endpoint/v3;endpointv3\272\200\310\321\006\002\020\002'
  _LOCALITYENDPOINTDISCOVERYSERVICE._options = None
  _LOCALITYENDPOINTDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\007%\n#envoy.config.endpoint.v3.LbEndpoint'
  _globals['_LEDSDUMMY']._serialized_start=176
  _globals['_LEDSDUMMY']._serialized_end=187
  _globals['_LOCALITYENDPOINTDISCOVERYSERVICE']._serialized_start=190
  _globals['_LOCALITYENDPOINTDISCOVERYSERVICE']._serialized_end=405
