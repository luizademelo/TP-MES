
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from envoy.config.core.v3 import config_source_pb2 as envoy_dot_config_dot_core_dot_v3_dot_config__source__pb2
from google.protobuf import duration_pb2 as google_dot_protobuf_dot_duration__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n:envoy/extensions/filters/http/on_demand/v3/on_demand.proto\x12*envoy.extensions.filters.http.on_demand.v3\x1a(envoy/config/core/v3/config_source.proto\x1a\x1egoogle/protobuf/duration.proto\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x92\x01\n\x0bOnDemandCds\x12<\n\x06source\x18\x01 \x01(\x0b\x32\".envoy.config.core.v3.ConfigSourceB\x08\xfa\x42\x05\x8a\x01\x02\x10\x01\x12\x19\n\x11resources_locator\x18\x02 \x01(\t\x12*\n\x07timeout\x18\x03 \x01(\x0b\x32\x19.google.protobuf.Duration\"\x89\x01\n\x08OnDemand\x12\x46\n\x05odcds\x18\x01 \x01(\x0b\x32\x37.envoy.extensions.filters.http.on_demand.v3.OnDemandCds:5\x9a\xc5\x88\x1e\x30\n.envoy.config.filter.http.on_demand.v2.OnDemand\"X\n\x0ePerRouteConfig\x12\x46\n\x05odcds\x18\x01 \x01(\x0b\x32\x37.envoy.extensions.filters.http.on_demand.v3.OnDemandCdsB\xb2\x01\n8io.envoyproxy.envoy.extensions.filters.http.on_demand.v3B\rOnDemandProtoP\x01Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/on_demand/v3;on_demandv3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.filters.http.on_demand.v3.on_demand_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n8io.envoyproxy.envoy.extensions.filters.http.on_demand.v3B\rOnDemandProtoP\001Z]github.com/envoyproxy/go-control-plane/envoy/extensions/filters/http/on_demand/v3;on_demandv3\272\200\310\321\006\002\020\002'
  _ONDEMANDCDS.fields_by_name['source']._options = None
  _ONDEMANDCDS.fields_by_name['source']._serialized_options = b'\372B\005\212\001\002\020\001'
  _ONDEMAND._options = None
  _ONDEMAND._serialized_options = b'\232\305\210\0360\n.envoy.config.filter.http.on_demand.v2.OnDemand'
  _globals['_ONDEMANDCDS']._serialized_start=272
  _globals['_ONDEMANDCDS']._serialized_end=418
  _globals['_ONDEMAND']._serialized_start=421
  _globals['_ONDEMAND']._serialized_end=558
  _globals['_PERROUTECONFIG']._serialized_start=560
  _globals['_PERROUTECONFIG']._serialized_end=648
