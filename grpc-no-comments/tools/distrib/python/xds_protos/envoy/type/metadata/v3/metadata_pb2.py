
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder

_sym_db = _symbol_database.Default()

from udpa.annotations import status_pb2 as udpa_dot_annotations_dot_status__pb2
from udpa.annotations import versioning_pb2 as udpa_dot_annotations_dot_versioning__pb2
from validate import validate_pb2 as validate_dot_validate__pb2

DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n%envoy/type/metadata/v3/metadata.proto\x12\x16\x65nvoy.type.metadata.v3\x1a\x1dudpa/annotations/status.proto\x1a!udpa/annotations/versioning.proto\x1a\x17validate/validate.proto\"\x85\x02\n\x0bMetadataKey\x12\x14\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01\x12G\n\x04path\x18\x02 \x03(\x0b\x32/.envoy.type.metadata.v3.MetadataKey.PathSegmentB\x08\xfa\x42\x05\x92\x01\x02\x08\x01\x1al\n\x0bPathSegment\x12\x16\n\x03key\x18\x01 \x01(\tB\x07\xfa\x42\x04r\x02\x10\x01H\x00:5\x9a\xc5\x88\x1e\x30\n.envoy.type.metadata.v2.MetadataKey.PathSegmentB\x0e\n\x07segment\x12\x03\xf8\x42\x01:)\x9a\xc5\x88\x1e$\n\"envoy.type.metadata.v2.MetadataKey\"\xb3\x04\n\x0cMetadataKind\x12?\n\x07request\x18\x01 \x01(\x0b\x32,.envoy.type.metadata.v3.MetadataKind.RequestH\x00\x12;\n\x05route\x18\x02 \x01(\x0b\x32*.envoy.type.metadata.v3.MetadataKind.RouteH\x00\x12?\n\x07\x63luster\x18\x03 \x01(\x0b\x32,.envoy.type.metadata.v3.MetadataKind.ClusterH\x00\x12\x39\n\x04host\x18\x04 \x01(\x0b\x32).envoy.type.metadata.v3.MetadataKind.HostH\x00\x1a=\n\x07Request:2\x9a\xc5\x88\x1e-\n+envoy.type.metadata.v2.MetadataKind.Request\x1a\x39\n\x05Route:0\x9a\xc5\x88\x1e+\n)envoy.type.metadata.v2.MetadataKind.Route\x1a=\n\x07\x43luster:2\x9a\xc5\x88\x1e-\n+envoy.type.metadata.v2.MetadataKind.Cluster\x1a\x37\n\x04Host:/\x9a\xc5\x88\x1e*\n(envoy.type.metadata.v2.MetadataKind.Host:*\x9a\xc5\x88\x1e%\n#envoy.type.metadata.v2.MetadataKindB\x0b\n\x04kind\x12\x03\xf8\x42\x01\x42\x89\x01\n$io.envoyproxy.envoy.type.metadata.v3B\rMetadataProtoP\x01ZHgithub.com/envoyproxy/go-control-plane/envoy/type/metadata/v3;metadatav3\xba\x80\xc8\xd1\x06\x02\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'envoy.type.metadata.v3.metadata_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  DESCRIPTOR._serialized_options = b'\n$io.envoyproxy.envoy.type.metadata.v3B\rMetadataProtoP\001ZHgithub.com/envoyproxy/go-control-plane/envoy/type/metadata/v3;metadatav3\272\200\310\321\006\002\020\002'
  _METADATAKEY_PATHSEGMENT.oneofs_by_name['segment']._options = None
  _METADATAKEY_PATHSEGMENT.oneofs_by_name['segment']._serialized_options = b'\370B\001'
  _METADATAKEY_PATHSEGMENT.fields_by_name['key']._options = None
  _METADATAKEY_PATHSEGMENT.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _METADATAKEY_PATHSEGMENT._options = None
  _METADATAKEY_PATHSEGMENT._serialized_options = b'\232\305\210\0360\n.envoy.type.metadata.v2.MetadataKey.PathSegment'
  _METADATAKEY.fields_by_name['key']._options = None
  _METADATAKEY.fields_by_name['key']._serialized_options = b'\372B\004r\002\020\001'
  _METADATAKEY.fields_by_name['path']._options = None
  _METADATAKEY.fields_by_name['path']._serialized_options = b'\372B\005\222\001\002\010\001'
  _METADATAKEY._options = None
  _METADATAKEY._serialized_options = b'\232\305\210\036$\n\"envoy.type.metadata.v2.MetadataKey'
  _METADATAKIND_REQUEST._options = None
  _METADATAKIND_REQUEST._serialized_options = b'\232\305\210\036-\n+envoy.type.metadata.v2.MetadataKind.Request'
  _METADATAKIND_ROUTE._options = None
  _METADATAKIND_ROUTE._serialized_options = b'\232\305\210\036+\n)envoy.type.metadata.v2.MetadataKind.Route'
  _METADATAKIND_CLUSTER._options = None
  _METADATAKIND_CLUSTER._serialized_options = b'\232\305\210\036-\n+envoy.type.metadata.v2.MetadataKind.Cluster'
  _METADATAKIND_HOST._options = None
  _METADATAKIND_HOST._serialized_options = b'\232\305\210\036*\n(envoy.type.metadata.v2.MetadataKind.Host'
  _METADATAKIND.oneofs_by_name['kind']._options = None
  _METADATAKIND.oneofs_by_name['kind']._serialized_options = b'\370B\001'
  _METADATAKIND._options = None
  _METADATAKIND._serialized_options = b'\232\305\210\036%\n#envoy.type.metadata.v2.MetadataKind'
  _globals['_METADATAKEY']._serialized_start=157
  _globals['_METADATAKEY']._serialized_end=418
  _globals['_METADATAKEY_PATHSEGMENT']._serialized_start=267
  _globals['_METADATAKEY_PATHSEGMENT']._serialized_end=375
  _globals['_METADATAKIND']._serialized_start=421
  _globals['_METADATAKIND']._serialized_end=984
  _globals['_METADATAKIND_REQUEST']._serialized_start=687
  _globals['_METADATAKIND_REQUEST']._serialized_end=748
  _globals['_METADATAKIND_ROUTE']._serialized_start=750
  _globals['_METADATAKIND_ROUTE']._serialized_end=807
  _globals['_METADATAKIND_CLUSTER']._serialized_start=809
  _globals['_METADATAKIND_CLUSTER']._serialized_end=870
  _globals['_METADATAKIND_HOST']._serialized_start=872
  _globals['_METADATAKIND_HOST']._serialized_end=927
