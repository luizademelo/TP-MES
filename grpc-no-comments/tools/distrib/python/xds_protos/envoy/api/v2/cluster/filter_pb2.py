
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from google.protobuf import any_pb2 as google_dot_protobuf_dot_any__pb2
from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n!envoy/api/v2/cluster/filter.proto\x12\x14\x65nvoy.api.v2.cluster\x1a\x19google/protobuf/any.proto\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"K\n\x06\x46ilter\x12\x15\n\x04name\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12*\n\x0ctyped_config\x18\x02 \x01(\x0b\x32\x14.google.protobuf.AnyB\xcc\x01\n\"io.envoyproxy.envoy.api.v2.clusterB\x0b\x46ilterProtoP\x01Z;github.com/envoyproxy/go-control-plane/envoy/api/v2/cluster\xaa\x02\x16\x45nvoy.Api.V2.ClusterNS\xea\x02\x19\x45nvoy::Api::V2::ClusterNS\xf2\x98\xfe\x8f\x05\x19\x12\x17\x65nvoy.config.cluster.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.api.v2.cluster.filter_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n\"io.envoyproxy.envoy.api.v2.clusterB\013FilterProtoP\001Z;github.com/envoyproxy/go-control-plane/envoy/api/v2/cluster\252\002\026Envoy.Api.V2.ClusterNS\352\002\031Envoy::Api::V2::ClusterNS\362\230\376\217\005\031\022\027envoy.config.cluster.v3\272\200\310\321\006\002\020\001'
  _FILTER.fields_by_name['name']._options = None
  _FILTER.fields_by_name['name']._serialized_options = b'\372B\004r\002 \001'
  _globals['_FILTER']._serialized_start=174
  _globals['_FILTER']._serialized_end=249
