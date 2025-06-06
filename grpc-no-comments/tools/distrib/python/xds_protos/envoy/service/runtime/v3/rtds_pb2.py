
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.service.discovery.v3 import discovery_pb2 as envoy_dot_service_dot_discovery_dot_v3_dot_discovery__pb2
from google.api import annotations_pb2 as google_dot_api_dot_annotations__pb2
from google.protobuf import struct_pb2 as google_dot_protobuf_dot_struct__pb2
from envoy.annotations import resource_pb2 as envoy_dot_annotations_dot_resource__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n#envoy/service/runtime/v3/rtds.proto\x12\x18\x65nvoy.service.runtime.v3\x1a*envoy/service/discovery/v3/discovery.proto\x1a\x1cgoogle/api/annotations.proto\x1a\x1cgoogle/protobuf/struct.proto\x1a envoy/annotations/resource.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"8\n\tRtdsDummy:+\x9a\xc5\x88\x1e&\n$envoy.service.discovery.v2.RtdsDummy\"s\n\x07Runtime\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12&\n\x05layer\x18\x02 \x01(\x0b\x32\x17.google.protobuf.Struct:)\x9a\xc5\x88\x1e$\n\"envoy.service.discovery.v2.Runtime2\xc4\x03\n\x17RuntimeDiscoveryService\x12r\n\rStreamRuntime\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\"\x00(\x01\x30\x01\x12{\n\x0c\x44\x65ltaRuntime\x12\x31.envoy.service.discovery.v3.DeltaDiscoveryRequest\x1a\x32.envoy.service.discovery.v3.DeltaDiscoveryResponse\"\x00(\x01\x30\x01\x12\x8d\x01\n\x0c\x46\x65tchRuntime\x12,.envoy.service.discovery.v3.DiscoveryRequest\x1a-.envoy.service.discovery.v3.DiscoveryResponse\" \x82\xd3\xe4\x93\x02\x1a\"\x15/v3/discovery:runtime:\x01*\x1a(\x8a\xa4\x96\xf3\x07\"\n envoy.service.runtime.v3.RuntimeB\x88\x01\n&io.envoyproxy.envoy.service.runtime.v3B\tRtdsProtoP\x01ZIgithub.com/envoyproxy/go-control-plane/envoy/service/runtime/v3;runtimev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.service.runtime.v3.rtds_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n&io.envoyproxy.envoy.service.runtime.v3B\tRtdsProtoP\001ZIgithub.com/envoyproxy/go-control-plane/envoy/service/runtime/v3;runtimev3\272\200\310\321\006\002\020\002'
  _RTDSDUMMY._options = None
  _RTDSDUMMY._serialized_options = b'\232\305\210\036&\n$envoy.service.discovery.v2.RtdsDummy'
  _RUNTIME.fields_by_name['name']._options = None
  _RUNTIME.fields_by_name['name']._serialized_options = b'\372B\004r\002\020\001'
  _RUNTIME._options = None
  _RUNTIME._serialized_options = b'\232\305\210\036$\n\"envoy.service.discovery.v2.Runtime'
  _RUNTIMEDISCOVERYSERVICE._options = None
  _RUNTIMEDISCOVERYSERVICE._serialized_options = b'\212\244\226\363\007\"\n envoy.service.runtime.v3.Runtime'
  _RUNTIMEDISCOVERYSERVICE.methods_by_name['FetchRuntime']._options = None
  _RUNTIMEDISCOVERYSERVICE.methods_by_name['FetchRuntime']._serialized_options = b'\202\323\344\223\002\032\"\025/v3/discovery:runtime:\001*'
  _globals['_RTDSDUMMY']._serialized_start=294
  _globals['_RTDSDUMMY']._serialized_end=350
  _globals['_RUNTIME']._serialized_start=352
  _globals['_RUNTIME']._serialized_end=467
  _globals['_RUNTIMEDISCOVERYSERVICE']._serialized_start=470
  _globals['_RUNTIMEDISCOVERYSERVICE']._serialized_end=922
