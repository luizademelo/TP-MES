
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n4envoy/config/cluster/aggregate/v2alpha/cluster.proto\x12&envoy.config.cluster.aggregate.v2alpha\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"+\n\rClusterConfig\x12\x1a\n\x08\x63lusters\x18\x01 \x03(\tB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x42\xcb\x01\n4io.envoyproxy.envoy.config.cluster.aggregate.v2alphaB\x0c\x43lusterProtoP\x01ZMgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/aggregate/v2alpha\xf2\x98\xfe\x8f\x05(\x12&envoy.extensions.clusters.aggregate.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.config.cluster.aggregate.v2alpha.cluster_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n4io.envoyproxy.envoy.config.cluster.aggregate.v2alphaB\014ClusterProtoP\001ZMgithub.com/envoyproxy/go-control-plane/envoy/config/cluster/aggregate/v2alpha\362\230\376\217\005(\022&envoy.extensions.clusters.aggregate.v3\272\200\310\321\006\002\020\001'
  _CLUSTERCONFIG.fields_by_name['clusters']._options = None
  _CLUSTERCONFIG.fields_by_name['clusters']._serialized_options = b'\372B\005\222\001\002\010\001'
  _globals['_CLUSTERCONFIG']._serialized_start=184
  _globals['_CLUSTERCONFIG']._serialized_end=227
