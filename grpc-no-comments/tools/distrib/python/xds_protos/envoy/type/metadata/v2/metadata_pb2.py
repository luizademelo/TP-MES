
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import migrate_pb2 as udpa_dot_annotations_dot_migrate__pb2
from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/type/metadata/v2/metadata.proto\x12\x16\x65nvoy.type.metadata.v2\x1a\x1eudpa/annotations/migrate.proto\x1a\x1dudpa/annotations/status.proto\x1a\x17validate/validate.proto\"\xa3\x01\n\x0bMetadataKey\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01\x12G\n\x04path\x18\x02 \x03(\x0b\x32/.envoy.type.metadata.v2.MetadataKey.PathSegmentB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1a\x35\n\x0bPathSegment\x12\x16\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02 \x01H\x00\x42\x0e\n\x07segment\x12\x03\xf8\x42\x01\"\xbc\x02\n\x0cMetadataKind\x12?\n\x07request\x18\x01 \x01(\x0b\x32,.envoy.type.metadata.v2.MetadataKind.RequestH\x00\x12;\n\x05route\x18\x02 \x01(\x0b\x32*.envoy.type.metadata.v2.MetadataKind.RouteH\x00\x12?\n\x07\x63luster\x18\x03 \x01(\x0b\x32,.envoy.type.metadata.v2.MetadataKind.ClusterH\x00\x12\x39\n\x04host\x18\x04 \x01(\x0b\x32).envoy.type.metadata.v2.MetadataKind.HostH\x00\x1a\t\n\x07Request\x1a\x07\n\x05Route\x1a\t\n\x07\x43luster\x1a\x06\n\x04HostB\x0b\n\x04kind\x12\x03\xf8\x42\x01\x42\xa7\x01\n$io.envoyproxy.envoy.type.metadata.v2B\rMetadataProtoP\x01ZHgithub.com/envoyproxy/go-control-plane/envoy/type/metadata/v2;metadatav2\xf2\x98\xfe\x8f\x05\x18\x12\x16\x65nvoy.type.metadata.v3\xba\x80\xc8\xd1\x06\x02\x10\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.metadata.v2.metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.type.metadata.v2B\rMetadataProtoP\001ZHgithub.com/envoyproxy/go-control-plane/envoy/type/metadata/v2;metadatav2\362\230\376\217\005\030\022\026envoy.type.metadata.v3\272\200\310\321\006\002\020\001'
  _METADATAKEY_PATHSEGMENT.oneofs_by_name['segment']._options = None
  _METADATAKEY_PATHSEGMENT.oneofs_by_name['segment']._serialized_options = b'\370B\001'
  _METADATAKEY_PATHSEGMENT.fields_by_name['key']._options = None
  _METADATAKEY_PATHSEGMENT.fields_by_name['key']._serialized_options = b'\372B\004r\002 \001'
  _METADATAKEY.fields_by_name['key']._options = None
  _METADATAKEY.fields_by_name['key']._serialized_options = b'\372B\004r\002 \001'
  _METADATAKEY.fields_by_name['path']._options = None
  _METADATAKEY.fields_by_name['path']._serialized_options = b'\372B\005\222\001\002\010\001'
  _METADATAKIND.oneofs_by_name['kind']._options = None
  _METADATAKIND.oneofs_by_name['kind']._serialized_options = b'\370B\001'
  _globals['_METADATAKEY']._serialized_start=154
  _globals['_METADATAKEY']._serialized_end=317
  _globals['_METADATAKEY_PATHSEGMENT']._serialized_start=264
  _globals['_METADATAKEY_PATHSEGMENT']._serialized_end=317
  _globals['_METADATAKIND']._serialized_start=320
  _globals['_METADATAKIND']._serialized_end=636
  _globals['_METADATAKIND_REQUEST']._serialized_start=586
  _globals['_METADATAKIND_REQUEST']._serialized_end=595
  _globals['_METADATAKIND_ROUTE']._serialized_start=597
  _globals['_METADATAKIND_ROUTE']._serialized_end=604
  _globals['_METADATAKIND_CLUSTER']._serialized_start=606
  _globals['_METADATAKIND_CLUSTER']._serialized_end=615
  _globals['_METADATAKIND_HOST']._serialized_start=617
  _globals['_METADATAKIND_HOST']._serialized_end=623
