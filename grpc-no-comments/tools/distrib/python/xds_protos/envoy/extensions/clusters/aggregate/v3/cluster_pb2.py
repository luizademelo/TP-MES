
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n4envoy/extensions/clusters/aggregate/v3/cluster.proto\x12&envoy.extensions.clusters.aggregate.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"h\n\rClusterConfig\x12\x1a\n\x08\x63lusters\x18\x01 \x03(\tB\x08\xfa\x42\x05\x92\x01\x02\x08\x01:;\x9a\xc5\x88\x1e\x36\n4envoy.config.cluster.aggregate.v2alpha.ClusterConfigB\xa9\x01\n4io.envoyproxy.envoy.extensions.clusters.aggregate.v3B\x0c\x43lusterProtoP\x01ZYgithub.com/envoyproxy/go-control-plane/envoy/extensions/clusters/aggregate/v3;aggregatev3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.extensions.clusters.aggregate.v3.cluster_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n4io.envoyproxy.envoy.extensions.clusters.aggregate.v3B\014ClusterProtoP\001ZYgithub.com/envoyproxy/go-control-plane/envoy/extensions/clusters/aggregate/v3;aggregatev3\272\200\310\321\006\002\020\002'
  _CLUSTERCONFIG.fields_by_name['clusters']._options = None
  _CLUSTERCONFIG.fields_by_name['clusters']._serialized_options = b'\372B\005\222\001\002\010\001'
  _CLUSTERCONFIG._options = None
  _CLUSTERCONFIG._serialized_options = b'\232\305\210\0366\n4envoy.config.cluster.aggregate.v2alpha.ClusterConfig'
  _globals['_CLUSTERCONFIG']._serialized_start=187
  _globals['_CLUSTERCONFIG']._serialized_end=291
