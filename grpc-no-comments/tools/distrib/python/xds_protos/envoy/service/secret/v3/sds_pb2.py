
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from envoy.annotations import resource_pb2 as envoy_dot_annotations_dot_resource__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/service/secret/v3/sds.proto\x12\x17\x65nvoy.service.secret.v3\x1a*envoy/service/discovery/v3/discovery.proto\x1a\x1cgoogle/api/annotations.proto\x1a envoy/annotations/resource.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\"6\n\x08SdsDummy:*\x9a\xc5\x88\x1e%\n#envoy.service.discovery.v2.SdsDummy2\xd3\x03\n\x16SecretDiscoveryService\x12{\n\x0c\x44\x65ltaSecrets\x12\x31.envoy.service.discovery.v3.DeltaDiscoveryRequest\x1a\x32.envoy.service.discovery.v3.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x12r\n\rStreamSecrets\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"\x00(\x01\x30\x01\x12\x8d\x01\n\x0c\x46\x65tchSecrets\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\" \x82\xd3\xe4\x93\x02\x1a\"\x15/v3/discovery:secrets:\x01*\x1a\x38\x8a\xa4\x96\xf3\x07\x32\n0envoy.extensions.transport_sockets.tls.v3.SecretB\x84\x01\n%io.envoyproxy.envoy.service.secret.v3B\x08SdsProtoP\x01ZGgithub.com/envoyproxy/go-control-plane/envoy/service/secret/v3;secretv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.secret.v3.sds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n%io.envoyproxy.envoy.service.secret.v3B\010SdsProtoP\001ZGgithub.com/envoyproxy/go-control-plane/envoy/service/secret/v3;secretv3\272\200\310\321\006\002\020\002'
  _SDSDUMMY._options = None
  _SDSDUMMY._serialized_options = b'\232\305\210\036%\n#envoy.service.discovery.v2.SdsDummy'
  _SECRETDISCOVERYSERVICE._options = None
  _SECRETDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\0072\n0envoy.extensions.transport_sockets.tls.v3.Secret'
  _SECRETDISCOVERYSERVICE.methods_by_name['FetchSecrets']._options = None
  _SECRETDISCOVERYSERVICE.methods_by_name['FetchSecrets']._serialized_options = b'\202\323\344\223\002\032\"\025/v3/discovery:secrets:\001*'
  _globals['_SDSDUMMY']._serialized_start=236
  _globals['_SDSDUMMY']._serialized_end=290
  _globals['_SECRETDISCOVERYSERVICE']._serialized_start=293
  _globals['_SECRETDISCOVERYSERVICE']._serialized_end=760
